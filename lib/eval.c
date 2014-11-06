/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, AwesomePlay Productions, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "scriptix.h"

__INLINE__ int sx_call_func (SX_THREAD *thread, SX_VALUE *func, unsigned int argc, SX_VALUE *self);
__INLINE__ int value_to_int (SX_VALUE *value);

int
sx_call_func (SX_THREAD *thread, SX_VALUE *func, unsigned int argc, SX_VALUE *self) {
	int i;

	if (!SX_ISFUNC (func)) {
		sx_push_value (thread, sx_new_nil ());
		return thread->state;
	}

	sx_push_call (thread, func->data.func.body, self, SX_CFLAG_HARD);

	if (self != NULL) {
		sx_define_var (thread, sx_self_id, self, SX_SCOPE_LOCAL);
	}

	if (SX_ISARRAY (func->data.func.args)) {
		for (i = 0; i < argc && i < func->data.func.args->data.array.count; i ++) {
			sx_define_var (thread, SX_TOINT (func->data.func.args->data.array.list[i]), sx_get_value (thread, thread->data - argc + i), SX_SCOPE_LOCAL);
		}
		for (; i < func->data.func.args->data.array.count; i ++) {
			sx_define_var (thread, SX_TOINT (func->data.func.args->data.array.list[i]), sx_new_nil (), SX_SCOPE_LOCAL);
		}
	}

	return thread->state;
}

int
value_to_int (SX_VALUE *value) {
	switch (sx_type_of (value)) {
		case SX_VALUE_NUM:
			return SX_TOINT (value);
			break;
		case SX_VALUE_STRING:
			if (value->data.str.len > 0) {
				return atoi (value->data.str.str);
			} else {
				return 0;
			}
			break;
		default:
			return 0;
			break;
	}
}

int
sx_eval (SX_THREAD *thread, unsigned int max) {
	unsigned int count;
	unsigned int i;
	unsigned int op_count = max;
	int op;
	int step;
	SX_VALUE *loop, *name;
	SX_VALUE *ret, *value;
	SX_VAR *var;
	SX_CALL *call;

	while (thread->call > 0) {
		call = &thread->call_stack[thread->call - 1];

		if (call->state == 0) { /* step on initialized call */
			++ call->op_ptr;
		}

		while (call->op_ptr < call->block->data.block.count && (thread->state == SX_STATE_RUN || call->state > 0) && (max == 0 || op_count > 0)) {
			if (call->state == -1) { /* START state */
				call->state = 0; /* DEFAULT state */
				call->top = thread->data;
			}

			op = call->block->data.block.nodes[call->op_ptr].op;

			if (op == 0) {
				sx_push_value (thread, call->block->data.block.nodes[call->op_ptr].value);
				++ call->op_ptr;
				continue;
			}

			switch (op) {
				case SX_OP_IF:
					if (sx_is_true (sx_get_value (thread, -3))) {
						sx_push_call (thread, sx_get_value (thread, -2), NULL, 0);
						sx_pop_value (thread, -3, 3);
					} else {
						if (sx_get_value (thread, -1) != NULL) {
							sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
							sx_pop_value (thread, -3, 3);
						}
					}
					break;
				case SX_OP_WHILE:
					switch (call->state) {
						case 3: /* pop last value -> fallthru */
							sx_pop_value (thread, -1, 1);
						case 0: /* ENTER -> fallthru */
						case 1: /* perform test */
							call->state = 2;
							sx_push_call (thread, sx_get_value (thread, -2), NULL, 0);
							break;
						case 2: /* test, check state, run body, looping to 3 */
							if (thread->state != SX_STATE_RUN) {
								sx_pop_value (thread, -3, 2);
								if (thread->state == SX_STATE_BREAK) {
									thread->state = SX_STATE_RUN;
								}
								call->state = 0;
							} else if (!sx_is_true (sx_get_value (thread, -1))) {
								sx_pop_value (thread, -2, 2);
								sx_push_value (thread, sx_new_nil ());
								call->state = 0;
							} else {
								sx_pop_value (thread, -1, 1);
								sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
								call->state = 3;
							}
							break;
					}
					break;
				case SX_OP_FOR:
					/* FIXME - doesn't catch BREAK */
					switch (call->state) {
						case 0: /* initialize */
							step = value_to_int (sx_get_value (thread, -2));
							loop = sx_get_value (thread, -3);
							if (SX_ISARRAY (loop)) {
								if (loop->data.array.count == 0) {
									sx_pop_value (thread, -4, 4);
									sx_push_value (thread, sx_new_nil ());
									break;
								}
								i = (step > 0) ? 0 : (loop->data.array.count - 1);
								sx_push_value (thread, sx_new_num (i));
								sx_push_value (thread, sx_new_nil ());
								call->state = 1;
							} else if (SX_ISRANGE (loop)) {
								sx_push_value (thread, sx_new_num (loop->data.range.start));
								sx_push_value (thread, sx_new_nil ());
								call->state = 3;
							} else {
								/* FIXME: raise error */
								sx_pop_value (thread, -4, 4);
								sx_push_value (thread, sx_new_nil ());
							}
							break;
						case 1: /* setup loop for iteration of array */
							call->state = 2;
							i = value_to_int (sx_get_value (thread, -2));
							sx_pop_value (thread, -2, 2);
							name = sx_get_value (thread, -4);
							loop = sx_get_value (thread, -3);
							step = value_to_int (sx_get_value (thread, -2));
							sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
							sx_define_var (thread, SX_TOINT(name), loop->data.array.list[i], SX_SCOPE_LOCAL);
							i += step;
							sx_push_value (thread, sx_new_num (i));
							break;
						case 2: /* attempt loop */
							step = value_to_int (sx_get_value (thread, -4));
							loop = sx_get_value (thread, -5);
							i = value_to_int (sx_get_value (thread, -2));
							if ((step > 0) ? (i < loop->data.array.count) : (i >= 0)) {
								call->state = 1;
							} else {
								sx_pop_value (thread, -4, 3);
								call->state = 0;
							}
							break;
						case 3: /* do iteration for range */
							i = value_to_int (sx_get_value (thread, -2));
							loop = sx_get_value (thread, -5);
							step = value_to_int (sx_get_value (thread, -4));
							if (step > 0 ? (i > loop->data.range.end) : (i < loop->data.range.end)) {
								/* end loop */
								sx_pop_value (thread, -6, 5);
								call->state = 0;
								break;
							}
							sx_pop_value (thread, -2, 2);
							name = sx_get_value (thread, -4);
							sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
							sx_define_var (thread, SX_TOINT(name), sx_new_num (i), SX_SCOPE_LOCAL);
							i += step;
							sx_push_value (thread, sx_new_num (i));
							break;
					}
					break;
				case SX_OP_TRY:
					if (!call->state) { /* try block */
						call->state = 1;
						sx_push_call (thread, sx_get_value (thread, -3), NULL, 0);
					} else { /* attempt catch, or just fall thru */
						call->state = 0;
						if (thread->state != SX_STATE_ERROR) {
							sx_pop_value (thread, -4, 3);
						} else {
							loop = sx_get_value (thread, -3);
							sx_push_call (thread, sx_get_value (thread, -2), NULL, 0);
							ret = sx_get_value (thread, -1);
							if (SX_ISARRAY(loop)) {
								var = NULL;
								for (i = 0; i < loop->data.array.count; i += 2) {
									var = sx_get_var (thread, SX_TOINT(loop->data.array.list[i]), SX_SCOPE_DEF);
									if (sx_class_is_a (ret, var->value)) {
										sx_define_var (thread, SX_TOINT(loop->data.array.list[i + 1]), ret, SX_SCOPE_LOCAL);
										break;

									}
									var = NULL;
								}
								if (var == NULL) { /* no found it, or not accepted it */
									sx_pop_value (thread, -4, 3);
									break;
								}
							} else {
								sx_define_var (thread, sx_error_id, ret, SX_SCOPE_LOCAL);
							}
							thread->state = SX_STATE_RUN;
							sx_pop_value (thread, -4, 4);
						}
					}
					break;
				case SX_OP_BREAK:
					if (thread->state == SX_STATE_RUN) {
						thread->state = SX_STATE_BREAK;
					}
					break;
				case SX_OP_EVAL:
					sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_RETURN:
					if (thread->state == SX_STATE_RUN || thread->state == SX_STATE_BREAK) {
						thread->state = SX_STATE_RETURN;
					}
					break;
				case SX_OP_RAISE:
					thread->state = SX_STATE_ERROR;
					break;
				case SX_OP_AND:
					if (!sx_is_true (sx_get_value (thread, -2))) {
						sx_pop_value (thread, -1, 1);
					} else {
						sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
						sx_pop_value (thread, -2, 2);
					}
					break;
				case SX_OP_OR:
					if (sx_is_true (sx_get_value (thread, -2))) {
						sx_pop_value (thread, -1, 1);
					} else {
						sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
						sx_pop_value (thread, -2, 2);
					}
					break;
				case SX_OP_STMT:
					call->stmt = sx_get_value (thread, -1);
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_ADD:
					sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, -2)) + value_to_int (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_SUBTRACT:
					sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, -2)) - value_to_int (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_MULTIPLY:
					sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, -2)) * value_to_int (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_DIVIDE:
					sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, -2)) / value_to_int (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEGATE:
					sx_push_value (thread, sx_new_num (- value_to_int (sx_get_value (thread, -1))));
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_CALL:
					count = value_to_int (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					value = sx_get_value (thread, -count - 1);
					if (SX_ISFUNC (value)) {
						if (value->data.func.cfunc != NULL) {
							sx_push_value (thread, value->data.func.cfunc (thread, NULL, count, thread->data - count));
							sx_pop_value (thread, -2 - count, count + 1);
						} else {
							sx_call_func (thread, value, count, NULL);
							sx_pop_value (thread, -1 - count, count + 1);
						}
					} else {
						sx_pop_value (thread, -1 - count, count + 1);
						/* FIXME: raise error */
						sx_push_value (thread, sx_new_nil ());
					}
					break;
				case SX_OP_GT:
					sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, -2), sx_get_value (thread, -1)) > 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_LT:
					sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, -2), sx_get_value (thread, -1)) < 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_GTE:
					sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, -2), sx_get_value (thread, -1)) >= 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_LTE:
					sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, -2), sx_get_value (thread, -1)) <= 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_EQUAL:
					sx_push_value (thread, sx_new_num (sx_are_equal (sx_get_value (thread, -2), sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEQUAL:
					sx_push_value (thread, sx_new_num (!sx_are_equal (sx_get_value (thread, -2), sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NOT:
					sx_push_value (thread, sx_new_num (!sx_is_true (sx_get_value (thread, -1))));
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_LOOKUP:
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_TOINT (sx_get_value (thread, -1)));
					sx_pop_value (thread, -2, 2);
					if (var) {
						sx_push_value (thread, var->value);
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					break;
				case SX_OP_ASSIGN:
					ret = sx_get_value (thread, -2);
					sx_define_var (thread, SX_TOINT (sx_get_value (thread, -3)), ret, SX_TOINT (sx_get_value (thread, -1)));
					sx_push_value (thread, ret);
					sx_pop_value (thread, -4, 3);
					break;
				case SX_OP_INDEX:
					value = sx_get_value (thread, -1);
					if (SX_ISNUM (value)) {
						sx_push_value (thread, sx_get_index (thread->system, sx_get_value (thread, -2), SX_TOINT (value)));
					} else if (SX_ISRANGE (value)) {
						sx_push_value (thread, sx_get_section (thread->system, sx_get_value (thread, -2), value->data.range.start, value->data.range.end));
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_PREINCREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_SCOPE_DEF);
					if (var) {
						ret = var->value = sx_new_num (value_to_int (var->value) + value_to_int (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_POSTINCREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_SCOPE_DEF);
					if (var) {
						ret = var->value;
						var->value = sx_new_num (value_to_int (var->value) + value_to_int (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_PREDECREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_SCOPE_DEF);
					if (var) {
						ret = var->value = sx_new_num (value_to_int (var->value) - value_to_int (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_POSTDECREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_SCOPE_DEF);
					if (var) {
						ret = var->value;
						var->value = sx_new_num (value_to_int (var->value) - value_to_int (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEWARRAY:
					count = value_to_int (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					if (count > 0) {
						sx_push_value (thread, sx_new_stack_array (thread, count, thread->data - count));
					} else {
						sx_push_value (thread, sx_new_array (thread->system, 0, NULL));
					}
					sx_pop_value (thread, -1 - count, count);
					break;
				case SX_OP_SETINDEX:
					ret = sx_new_nil ();
					if (SX_ISARRAY (sx_get_value (thread, -3)) && SX_ISNUM(sx_get_value (thread, -2))) {
						if (SX_TOINT(sx_get_value (thread, -2)) >= 0) {
							if (SX_TOINT (sx_get_value (thread, -2)) < sx_get_value (thread, -3)->data.array.count) {
								sx_get_value (thread, -3)->data.array.list[SX_TOINT(sx_get_value (thread, -2))] = sx_get_value (thread, -1);
								ret = sx_get_value (thread, -1);
							}
						} else {
							if (-SX_TOINT (sx_get_value (thread, -2)) < sx_get_value (thread, -3)->data.array.count) {
								sx_get_value (thread, -3)->data.array.list[SX_TOINT(sx_get_value (thread, -2))] = sx_get_value (thread, -1);
								ret = sx_get_value (thread, -1);
							}
						}
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -4, 3);
					break;
				case SX_OP_SETMEMBER:
					ret = sx_new_nil ();
					if (SX_ISCLASS (sx_get_value (thread, -3))) {
						if (sx_set_member (thread->system, sx_get_value (thread, -3), SX_TOINT(sx_get_value (thread, -2)), sx_get_value (thread, -1))) {
							ret = sx_get_value (thread, -1);
						}
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -4, 3);
					break;
				case SX_OP_SIZEOF:
					if (SX_ISARRAY(sx_get_value (thread, -1))) {
						sx_push_value (thread, sx_new_num (sx_get_value (thread, -1)->data.array.count));
					} else if (SX_ISSTRING(sx_get_value (thread, -1))) {
						sx_push_value (thread, sx_new_num (sx_get_value (thread, -1)->data.str.len));
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_NEWCLASS:
					if (!call->state) { /* init */
						value = sx_get_value (thread, -2);
						if (SX_ISCLASS (value)) {
							ret = sx_new_class (thread->system, value);
						} else {
							ret = sx_new_class (thread->system, NULL);
						}

						value = sx_get_value (thread, -1);
						sx_push_value (thread, ret);

						if (SX_ISBLOCK (value)) {
							call->state = 1;
							sx_push_call (thread, value, ret, 0);
						}

						sx_pop_value (thread, -3, 2);
					} else { /* cleanup */
						sx_pop_value (thread, -1, 1);
						call->state = 0;
					}
					break;
				case SX_OP_MEMBER:
					if (SX_ISCLASS (sx_get_value (thread, -2))) {
						value = sx_get_member (sx_get_value (thread, -2), SX_TOINT(sx_get_value (thread, -1)));
						sx_push_value (thread, value);
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEWINSTANCE:
					if (call->state == 0) { /* start */
						if (SX_ISCLASS (sx_get_value (thread, -1))) {
							ret = sx_new_class (thread->system, sx_get_value (thread, -1));
							if (ret) {
								sx_push_value (thread, ret);
								sx_pop_value (thread, -2, 1);
								value = sx_get_member (ret, sx_init_id);
								if (SX_ISFUNC (value)) {
									if (value->data.func.cfunc != NULL) {
										value->data.func.cfunc (thread, ret, 0, thread->data);
									} else {
										call->state = 1;
										sx_call_func (thread, value, 0, ret);
									}
								}
							} else {
								/* FIXME: raise error */
								sx_pop_value (thread, -1, 1);
								sx_push_value (thread, sx_new_nil ());
							}
						} else {
							sx_pop_value (thread, -1, 1);
							var = sx_get_system_var (thread->system, sx_etype_id);
							if (var != NULL) {
								sx_push_value (thread, var->value);
							} else {
								sx_push_value (thread, sx_new_nil ());
							}
							thread->state = SX_STATE_ERROR;
						}
					} else { /* cleanup init() */
						sx_pop_value (thread, -1, 1);
						call->state = 0;
					}
					break;
				case SX_OP_ISA:
					sx_push_value (thread, sx_new_num (sx_class_is_a (sx_get_value (thread, -2), sx_get_value (thread, -1))));
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_TYPEOF:
					sx_push_value (thread, sx_new_num (sx_type_of (sx_get_value (thread, -1))));
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_NEWFUNC:
					sx_push_value (thread, sx_new_func (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1)));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_METHOD:
					count = value_to_int (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					ret = sx_get_member (sx_get_value (thread, -count - 2), SX_TOINT(sx_get_value (thread, -count - 1)));
					if (SX_ISFUNC (ret)) {
						if (ret->data.func.cfunc != NULL) {
							sx_push_value (thread, ret->data.func.cfunc (thread, sx_get_value (thread, -count - 2), count, thread->data - count));
							sx_pop_value (thread, -3 - count, count + 2);
						} else {
							sx_call_func (thread, ret, count, sx_get_value (thread, -count - 2));
							sx_pop_value (thread, -2 - count, count + 2);
						}
					} else {
						sx_pop_value (thread, -2 - count, count + 2);
						/* FIXME: raise error */
						sx_push_value (thread, sx_new_nil ());
					}
					break;
				case SX_OP_NEWRANGE:
					sx_push_value (thread, sx_new_range (thread->system, value_to_int (sx_get_value (thread, -2)), value_to_int (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
			}

			/* recalculate call; may have changed */
			call = &thread->call_stack[thread->call - 1];

			/* DEFAULT state - safe to break, or next op */
			if (call->state == 0) {
				/* exit out of function on thread switch */
				if (max) {
					if (-- op_count == 0) {
						thread->state = SX_STATE_SWITCH;
						return thread->state;
					}
				}

				/* call next op */
				++ call->op_ptr;
			}
		}

		if (thread->state == SX_STATE_RUN) {
			sx_push_value (thread, call->stmt);
		}

		if (call->flags & SX_CFLAG_HARD) {
			if (thread->state == SX_STATE_BREAK || thread->state == SX_STATE_RETURN) {
				thread->state = SX_STATE_RUN;
			}
		}

		if (thread->data > call->top + 1) {
			sx_pop_value (thread, call->top, thread->data - call->top - 1);
		}

		sx_pop_call (thread);
	}

	return thread->state;
}

int
sx_run_thread (SX_THREAD *thread, unsigned int max) {
	if (thread->state == SX_STATE_READY) {
		thread->state = SX_STATE_RUN;
		thread->ret = sx_new_nil ();

		sx_push_call (thread, thread->main, NULL, SX_CFLAG_HARD);
	} else if (thread->state != SX_STATE_RUN) {
		return thread->state;
	}

	sx_eval (thread, max);

	if (thread->data > 0) {
		thread->ret = sx_get_value (thread, 0);
	}

	switch (thread->state) {
		case SX_STATE_ERROR:
			fprintf (stderr, "Uncaught exception\n");
			break;
		case SX_STATE_RUN:
		case SX_STATE_BREAK:
		case SX_STATE_RETURN:
			thread->state = SX_STATE_EXIT;
			break;
		case SX_STATE_SWITCH:
			thread->state = SX_STATE_RUN;
			break;
	}

	return thread->state;
}
