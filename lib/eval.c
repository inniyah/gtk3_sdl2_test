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

__INLINE__ int sx_call_func (SX_THREAD *thread, SX_VALUE *self, SX_VALUE *func, unsigned int argc, unsigned int top);
__INLINE__ int sx_call_cfunc (SX_THREAD *thread, SX_VALUE *self, SX_VALUE *func, unsigned int argc, unsigned int top);

int
sx_call_cfunc (SX_THREAD *thread, SX_VALUE *self, SX_VALUE *func, unsigned int argc, unsigned int top) {
	unsigned int otop;

	if (!SX_ISFUNC (thread->system, func) || func->data.func.cfunc == NULL) {
		sx_raise_error (thread, sx_TypeError, "Tried to call a non-function");
		return thread->state = SX_STATE_ERROR;
	}

	sx_lock_value (func);
	sx_lock_value (self);

	otop = thread->data;
	func->data.func.cfunc (thread, self, func->data.func.data, argc, top);

	if (thread->data == otop) { /* no return value pushed */
		sx_push_value (thread, self ? self : func);
	} else if (thread->data > otop + 1) { /* too many values, clear extras */
		sx_pop_value (thread, otop, thread->data - otop - 1);
	}
	
	sx_unlock_value (func);
	sx_unlock_value (self);

	return thread->state;
}

int
sx_call_func (SX_THREAD *thread, SX_VALUE *self, SX_VALUE *func, unsigned int argc, unsigned int top) {
	unsigned int i;

	sx_push_call (thread, func->data.func.body, self, SX_CFLAG_HARD);

	if (self != NULL) {
		sx_define_var (thread, sx_self_id, self, SX_SCOPE_LOCAL);
	}

	if (SX_ISARRAY (thread->system, func->data.func.args)) {
		for (i = 0; i < argc && i < func->data.func.args->data.array.count; i ++) {
			sx_define_var (thread, SX_TOINT (func->data.func.args->data.array.list[i]), sx_get_value (thread, top + i), SX_SCOPE_LOCAL);
		}
		for (; i < func->data.func.args->data.array.count; i ++) {
			sx_define_var (thread, SX_TOINT (func->data.func.args->data.array.list[i]), sx_new_nil (), SX_SCOPE_LOCAL);
		}
	}

	return thread->state;
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
	SX_CLASS *klass;

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
					if (sx_is_true (thread->system, sx_get_value (thread, -3))) {
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
							} else if (!sx_is_true (thread->system, sx_get_value (thread, -1))) {
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
					switch (call->state) {
						case 0: /* initialize */
							step = SX_TOINT (sx_get_value (thread, -2));
							loop = sx_get_value (thread, -3);
							if (SX_ISARRAY (thread->system,loop)) {
								if (loop->data.array.count == 0) {
									sx_pop_value (thread, -4, 4);
									sx_push_value (thread, sx_new_nil ());
									break;
								}
								i = (step > 0) ? 0 : (loop->data.array.count - 1);
								sx_push_value (thread, sx_new_num (i));
								sx_push_value (thread, sx_new_nil ());
								call->state = 1;
							} else if (SX_ISRANGE (thread->system, loop)) {
								sx_push_value (thread, sx_new_num (loop->data.range.start));
								sx_push_value (thread, sx_new_nil ());
								call->state = 3;
							} else {
								sx_pop_value (thread, -4, 4);
								sx_raise_error (thread, sx_TypeError, "Invalid for loop base");
							}
							break;
						case 1: /* setup loop for iteration of array */
							call->state = 2;
							i = SX_TOINT (sx_get_value (thread, -2));
							sx_pop_value (thread, -2, 2);
							name = sx_get_value (thread, -4);
							loop = sx_get_value (thread, -3);
							step = SX_TOINT (sx_get_value (thread, -2));
							sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
							sx_define_var (thread, SX_TOINT(name), loop->data.array.list[i], SX_SCOPE_LOCAL);
							i += step;
							sx_push_value (thread, sx_new_num (i));
							break;
						case 2: /* attempt loop */
							if (thread->state == SX_STATE_BREAK) {
								thread->state = SX_STATE_RUN;
								sx_pop_value (thread, -6, 5);
								call->state = 0;
							} else {
								step = SX_TOINT (sx_get_value (thread, -4));
								loop = sx_get_value (thread, -5);
								i = SX_TOINT (sx_get_value (thread, -2));
								if ((step > 0) ? (i < loop->data.array.count) : (i >= 0)) {
									call->state = 1;
								} else {
									sx_pop_value (thread, -4, 3);
									call->state = 0;
								}
							}
							break;
						case 3: /* do iteration for range */
							if (thread->state == SX_STATE_BREAK) {
								thread->state = SX_STATE_RUN;
								sx_pop_value (thread, -6, 3);
								call->state = 0;
							} else {
								i = SX_TOINT (sx_get_value (thread, -2));
								loop = sx_get_value (thread, -5);
								step = SX_TOINT (sx_get_value (thread, -4));
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
							}
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
							ret = sx_get_value (thread, -1);
							if (SX_ISEXCEPTION(thread->system, ret) && SX_ISARRAY(thread->system, loop)) {
								for (i = 0; i < loop->data.array.count; i += 2) {
									if (ret->data.error.id == SX_TOINT (loop->data.array.list[i])) {
										sx_push_call (thread, sx_get_value (thread, -2), NULL, 0);
										sx_define_var (thread, SX_TOINT(loop->data.array.list[i + 1]), ret, SX_SCOPE_LOCAL);
										break;
									}
								}
								if (i >= loop->data.array.count) { /* no found it, or not accepted it */
									sx_pop_value (thread, -4, 3);
									break;
								}
							} else {
								sx_push_call (thread, sx_get_value (thread, -2), NULL, 0);
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
					value = sx_get_value (thread, -2);
					if (SX_ISNUM (thread->system, value)) {
						ret = sx_new_error (thread, SX_TOINT(value), sx_get_value (thread, -1));
						thread->state = SX_STATE_ERROR;
						sx_push_value (thread, ret);
					} else {
						sx_raise_error (thread, sx_TypeError, "Tried to raise without a name");
					}
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_AND:
					if (!sx_is_true (thread->system, sx_get_value (thread, -2))) {
						sx_pop_value (thread, -1, 1);
					} else {
						sx_push_call (thread, sx_get_value (thread, -1), NULL, 0);
						sx_pop_value (thread, -2, 2);
					}
					break;
				case SX_OP_OR:
					if (sx_is_true (thread->system, sx_get_value (thread, -2))) {
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
					sx_push_value (thread, sx_new_num (SX_TOINT (sx_to_num (thread->system, sx_get_value (thread, -2))) + SX_TOINT (sx_to_num (thread->system, sx_get_value (thread, -1)))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_SUBTRACT:
					sx_push_value (thread, sx_new_num (SX_TOINT (sx_get_value (thread, -2)) - SX_TOINT (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_MULTIPLY:
					sx_push_value (thread, sx_new_num (SX_TOINT (sx_get_value (thread, -2)) * SX_TOINT (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_DIVIDE:
					sx_push_value (thread, sx_new_num (SX_TOINT (sx_get_value (thread, -2)) / SX_TOINT (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEGATE:
					sx_push_value (thread, sx_new_num (- SX_TOINT (sx_get_value (thread, -1))));
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_CALL:
					count = SX_TOINT (sx_get_value (thread, -1));
					value = sx_get_value (thread, -count - 2);
					if (SX_ISFUNC (thread->system, value)) {
						if (value->data.func.cfunc) {
							sx_call_cfunc (thread, NULL, value, count, thread->data - count - 1);
							sx_pop_value (thread, -3 - count, count + 2);
						} else {
							sx_call_func (thread, NULL, value, count, thread->data - count - 1);
							sx_pop_value (thread, -2 - count, count + 2);
						}
					} else {
						sx_pop_value (thread, -2 - count, count + 2);
						sx_raise_error (thread, sx_TypeError, "Tried to call a non-function");
					}
					break;
				case SX_OP_GT:
					sx_push_value (thread, sx_new_num (sx_compare (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1)) > 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_LT:
					sx_push_value (thread, sx_new_num (sx_compare (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1)) < 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_GTE:
					sx_push_value (thread, sx_new_num (sx_compare (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1)) >= 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_LTE:
					sx_push_value (thread, sx_new_num (sx_compare (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1)) <= 0));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_EQUAL:
					sx_push_value (thread, sx_new_num (sx_are_equal (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEQUAL:
					sx_push_value (thread, sx_new_num (!sx_are_equal (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NOT:
					sx_push_value (thread, sx_new_num (!sx_is_true (thread->system, sx_get_value (thread, -1))));
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
					if (SX_ISNUM (thread->system, value)) {
						sx_push_value (thread, sx_get_index (thread->system, sx_get_value (thread, -2), SX_TOINT (value)));
					} else if (SX_ISRANGE (thread->system, value)) {
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
						ret = var->value = sx_new_num (SX_TOINT (var->value) + SX_TOINT (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_POSTINCREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_SCOPE_DEF);
					if (var) {
						ret = var->value;
						var->value = sx_new_num (SX_TOINT (var->value) + SX_TOINT (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_PREDECREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_SCOPE_DEF);
					if (var) {
						ret = var->value = sx_new_num (SX_TOINT (var->value) - SX_TOINT (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_POSTDECREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, -2)), SX_SCOPE_DEF);
					if (var) {
						ret = var->value;
						var->value = sx_new_num (SX_TOINT (var->value) - SX_TOINT (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEWARRAY:
					count = SX_TOINT (sx_get_value (thread, -1));
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
					if (SX_ISARRAY (thread->system, sx_get_value (thread, -3)) && SX_ISNUM(thread->system, sx_get_value (thread, -2))) {
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
					if (sx_set_member (thread->system, sx_get_value (thread, -3), SX_TOINT(sx_get_value (thread, -2)), sx_get_value (thread, -1))) {
						sx_pop_value (thread, -3, 2);
					} else {
						sx_pop_value (thread, -3, 3);
						sx_raise_error (thread, sx_TypeError, "Cannot set member on non-object value");
					}
					break;
				case SX_OP_SIZEOF:
					if (SX_ISARRAY(thread->system, sx_get_value (thread, -1))) {
						sx_push_value (thread, sx_new_num (sx_get_value (thread, -1)->data.array.count));
					} else if (SX_ISSTRING(thread->system, sx_get_value (thread, -1))) {
						sx_push_value (thread, sx_new_num (sx_get_value (thread, -1)->data.str.len));
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_NEWCLASS:
					klass = sx_get_class (thread->system, SX_TOINT (sx_get_value (thread, -3)));
					if (klass != NULL) {
						sx_pop_value (thread, -3, 3);
						sx_raise_error (thread, sx_NameError, "Class name already exists");
						break;
					}

					value = sx_get_value (thread, -2);
					if (SX_ISNUM (thread->system, value)) {
						klass = sx_get_class (thread->system, SX_TOINT (value));
						if (klass != NULL) {
							klass = sx_new_class (thread->system, SX_TOINT (sx_get_value (thread, -3)), klass);
						} else {
							sx_pop_value (thread, -3, 3);
							sx_raise_error (thread, sx_NameError, "Class does not exist for child");
							break;
						}
					} else {
						klass = sx_new_class (thread->system, SX_TOINT (sx_get_value (thread, -3)), NULL);
					}

					value = sx_get_value (thread, -1);
					sx_push_value (thread, NULL);

					if (SX_ISARRAY (thread->system, value)) {
						for (i = 0; i < value->data.array.size; i += 2) {
							sx_set_method (thread->system, klass, SX_TOINT (value->data.array.list[i]), value->data.array.list[i + 1]);
						}
					}

					sx_pop_value (thread, -4, 3);
					break;
				case SX_OP_MEMBER:
					value = sx_get_member (thread->system, sx_get_value (thread, -2), SX_TOINT(sx_get_value (thread, -1)));
					sx_push_value (thread, value);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEWINSTANCE:
					if (call->state == 0) { /* start */
						klass = sx_get_class (thread->system, SX_TOINT(sx_get_value (thread, -1)));
						if (klass != NULL) {
							ret = sx_new_object (thread->system, klass, NULL);
							if (ret) {
								sx_push_value (thread, ret);
								sx_pop_value (thread, -2, 1);
								value = sx_get_member (thread->system, ret, sx_init_id);
								if (SX_ISFUNC (thread->system, value)) {
									if (value->data.func.cfunc) {
										sx_call_cfunc (thread, ret, value, 0, thread->data);
										sx_pop_value (thread, -1, 1);
									} else {
										sx_call_func (thread, ret, value, 0, thread->data);
										call->state = 1;
									}
								}
							} else {
								sx_pop_value (thread, -1, 1);
								sx_raise_error (thread, sx_MemError, "Failed to create object");
							}
						} else {
							sx_pop_value (thread, -1, 1);
							sx_raise_error (thread, sx_NameError, "Class does not exist for instance");
						}
					} else { /* cleanup init() */
						sx_pop_value (thread, -1, 1);
						call->state = 0;
					}
					break;
				case SX_OP_ISA:
					klass = sx_get_class (thread->system, SX_TOINT(sx_get_value (thread, -1)));
					if (klass) {
						sx_push_value (thread, sx_new_num (sx_value_is_a (thread->system, sx_get_value (thread, -2), klass)));
					} else {
						sx_raise_error (thread, sx_NameError, "Parent is not a class");
					}
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEWFUNC:
					sx_push_value (thread, sx_new_func (thread->system, sx_get_value (thread, -2), sx_get_value (thread, -1)));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_METHOD:
					count = SX_TOINT (sx_get_value (thread, -1));
					value = sx_get_value (thread, -count - 3); /* the class */
					klass = sx_class_of (thread->system, value);
					if (klass) {
						ret = sx_get_method (thread->system, klass, SX_TOINT(sx_get_value (thread, -count - 2)));
						if (SX_ISFUNC (thread->system, ret)) {
							if (ret->data.func.cfunc) {
								sx_call_cfunc (thread, value, ret, count, thread->data - count - 1);
								sx_pop_value (thread, -4 - count, count + 3);
							} else {
								sx_call_func (thread, value, ret, count, thread->data - count - 1);
								sx_pop_value (thread, -3 - count, count + 3);
							}
						} else {
							sx_pop_value (thread, -3 - count, count + 3);
							sx_raise_error (thread, sx_TypeError, "Tried to call a member which is a non-function");
						}
					} else {
						sx_pop_value (thread, -3 - count, count + 3);
						sx_raise_error (thread, sx_TypeError, "Tried to call a method on an invalid class");
					}
					break;
				case SX_OP_NEWRANGE:
					sx_push_value (thread, sx_new_range (thread->system, SX_TOINT (sx_get_value (thread, -2)), SX_TOINT (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_SETFILELINE:
					value = sx_get_value (thread, -2);
					if (SX_ISSTRING (thread->system, value)) {
						thread->file = value;
					} else {
						sx_pop_value (thread, -2, 2);
						sx_raise_error (thread, sx_TypeError, "Tried to set filename to a non-string");
						break;
					}
					value = sx_get_value (thread, -1);
					if (SX_ISNUM (thread->system, value)) {
						thread->line = SX_TOINT (value);
					} else {
						sx_pop_value (thread, -2, 2);
						sx_raise_error (thread, sx_TypeError, "Tried to set file line to a non-number");
						break;
					}
					sx_pop_value (thread, -2, 2);
					break;
				case SX_OP_NEXTLINE:
					++ thread->line;
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
	if (thread->state != SX_STATE_RUN) {
		return thread->state;
	}

	sx_eval (thread, max);

	if (thread->data > 0) {
		thread->ret = sx_get_value (thread, 0);
	}

	switch (thread->state) {
		case SX_STATE_ERROR:
			if (thread->system->error_hook != NULL) {
				thread->system->error_hook ("Uncaught exception");
			} else {
				fprintf (stderr, "Uncaught exception\n");
				sx_print_value (thread->system, thread->ret);
			}
			break;
		case SX_STATE_RUN:
		case SX_STATE_RETURN:
			thread->state = SX_STATE_EXIT;
			break;
		case SX_STATE_SWITCH:
			thread->state = SX_STATE_RUN;
			break;
	}

	return thread->state;
}
