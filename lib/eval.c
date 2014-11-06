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

__INLINE__ int call_func (THREAD *thread, VALUE *func, unsigned int argc, unsigned int top, VALUE *self);
__INLINE__ int value_to_int (VALUE *value);

int
call_func (THREAD *thread, VALUE *func, unsigned int argc, unsigned int top, VALUE *self) {
	int i;

	if (!SX_ISFUNC (func)) {
		sx_push_value (thread, sx_new_nil ());
		return thread->state;
	}

	if (sx_push_context (thread, func, SX_CFLAG_HARD) == NULL) {
		sx_push_value (thread, sx_new_nil ());
		return thread->state;
	}

	if (self != NULL) {
		sx_define_var (thread, sx_name_to_id ("self"), self, SX_SCOPE_LOCAL);
	}

	if (SX_ISARRAY (func->data.func.args)) {
		for (i = 0; i < argc && i < func->data.func.args->data.array.count; i ++) {
			sx_define_var (thread, SX_TOINT (func->data.func.args->data.array.list[i]), sx_get_value (thread, top + i), SX_SCOPE_LOCAL);
		}
		for (; i < func->data.func.args->data.array.count; i ++) {
			sx_define_var (thread, SX_TOINT (func->data.func.args->data.array.list[i]), sx_new_nil (), SX_SCOPE_LOCAL);
		}
	}

	sx_eval (thread, func->data.func.body);

	if (thread->state == SX_STATE_BREAK || thread->state == SX_STATE_RETURN) {
		thread->state = SX_STATE_RUN;
	}

	sx_pop_context (thread);

	return thread->state;
}

int
value_to_int (VALUE *value) {
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
sx_eval (THREAD *thread, VALUE *block) {
	unsigned int node;
	unsigned int count;
	unsigned int i;
	unsigned int top;
	int op;
	int step;
	VALUE *loop, *name;
	VALUE *ret, *value;
	VAR *var;

	if (!SX_ISBLOCK (block)) {
		sx_push_value (thread, block);
		return thread->state;
	}

	sx_lock_value (block);

	for (node = 0; node < block->data.block.count && thread->state == SX_STATE_RUN; ++ node) {
		op = block->data.block.nodes[node].op;
		if (op == 0) {
			sx_push_value (thread, block->data.block.nodes[node].value);
		} else {
			count = block->data.block.nodes[node].count;
			if (op >= 100) { /* special operator */
				switch (op) {
					case SX_OP_IF:
						if (sx_is_true (sx_get_value (thread, -3))) {
							sx_eval (thread, sx_get_value (thread, -2));
						} else {
							sx_eval (thread, sx_get_value (thread, -1));
						}
						break;
					case SX_OP_WHILE:
						sx_push_context (thread, sx_get_value (thread, -1), 0);
						while (thread->state == SX_STATE_RUN) {
							if (sx_eval (thread, sx_get_value (thread, -2)) != SX_STATE_RUN) {
								break;
							}
							if (!sx_is_true (sx_get_value (thread, -1))) {
								sx_pop_value (thread, -1, 2);
								break;
							}
							sx_pop_value (thread, -1, 1);
							if (sx_eval (thread, sx_get_value (thread, -1)) != SX_STATE_RUN) {
								break;
							}
							sx_pop_value (thread, -1, 1);
						}
						sx_pop_context (thread);
						if (thread->state == SX_STATE_BREAK) {
							thread->state = SX_STATE_RUN;
						} else if (thread->state == SX_STATE_RUN) {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_FOR:
						if (count == 4) {
							name = sx_get_value (thread, -4);
							loop = sx_get_value (thread, -3);
							step = value_to_int (sx_get_value (thread, -2));
						} else {
							name = sx_get_value (thread, -3);
							loop = sx_get_value (thread, -2);
							step = 1;
						}
						if (SX_ISARRAY (loop)) {
							if (loop->data.array.count == 0) {
								sx_push_value (thread, sx_new_nil ());
								break;
							}
							sx_push_context (thread, sx_get_value (thread, -1), 0);
							i = (step > 0) ? 0 : (loop->data.array.count - 1);
							sx_push_value (thread, sx_new_nil ());
							do {
								sx_pop_value (thread, -1, 1);
								sx_define_var (thread, SX_TOINT(name), loop->data.array.list[i], SX_SCOPE_LOCAL);
								if (sx_eval (thread, sx_get_value (thread, -1)) != SX_STATE_RUN) {
									break;
								}
								i += step;
							} while ((step > 0) ? (i < loop->data.array.count) : (i >= 0));
							sx_pop_context (thread);
						} else if (SX_ISRANGE (loop)) {
							sx_push_context (thread, sx_get_value (thread, -1), 0);
							sx_push_value (thread, sx_new_nil ());
							for (i = loop->data.range.start; step > 0 ? (i <= loop->data.range.end) : (i >= loop->data.range.end); i += step) {
								sx_pop_value (thread, -1, 1);
								sx_define_var (thread, SX_TOINT(name), sx_new_num (i), SX_SCOPE_LOCAL);
								if (sx_eval (thread, sx_get_value (thread, -1)) != SX_STATE_RUN) {
									break;
								}
							}
							sx_pop_context (thread);
						} else {
							sx_push_value (thread, sx_new_nil ());
							/* raise error */
							break;
						}

						if (thread->state == SX_STATE_BREAK) {
							thread->state = SX_STATE_RUN;
						}
						break;
					case SX_OP_TRY:
						sx_push_context (thread, sx_get_value (thread, -2), 0);
						if (sx_eval (thread, sx_get_value (thread, -2)) != SX_STATE_RUN) {
							if (thread->state != SX_STATE_ERROR) {
								sx_pop_context (thread);
								break;
							}
							thread->state = SX_STATE_RUN;
							sx_define_var (thread, sx_name_to_id ("error"), sx_get_value (thread, -1), SX_SCOPE_LOCAL);
							sx_pop_value (thread, -1, 1);
							thread->context_stack[thread->context - 1].block = sx_get_value (thread, -1);
							sx_eval (thread, sx_get_value (thread, -1));
						}
						sx_pop_context (thread);
						break;
					case SX_OP_BREAK:
						if (count == 0) {
							sx_push_value (thread, sx_new_nil ());
						} else {
							sx_push_value (thread, sx_get_value (thread, -1));
						}
						if (thread->state == SX_STATE_RUN) {
							thread->state = SX_STATE_BREAK;
						}
						break;
					case SX_OP_EVAL:
						sx_push_context (thread, sx_get_value (thread, -1), 0);
						sx_eval (thread, sx_get_value (thread, -1));
						sx_pop_context (thread);
						break;
					case SX_OP_RETURN:
						if (count == 0) {
							sx_push_value (thread, sx_new_nil ());
						} else {
							sx_push_value (thread, sx_get_value (thread, -1));
						}
						if (thread->state == SX_STATE_RUN || thread->state == SX_STATE_BREAK) {
							thread->state = SX_STATE_RETURN;
						}
						break;
					case SX_OP_RAISE:
						sx_push_value (thread, sx_get_value (thread, -1));
						thread->state = SX_STATE_ERROR;
						break;
					case SX_OP_AND:
						sx_eval (thread, sx_get_value (thread, -2));
						if (!sx_is_true (sx_get_value (thread, -1))) {
							sx_pop_value (thread, -1, 1);
							sx_push_value (thread, sx_new_nil ());
							break;
						}
						sx_eval (thread, sx_get_value (thread, -1));
						if (!sx_is_true (sx_get_value (thread, -1))) {
							sx_push_value (thread, sx_new_nil ());
						} else {
							sx_push_value (thread, sx_new_num (1));
						}
						sx_pop_value (thread, -2, 1);
						break;
					case SX_OP_OR:
						sx_eval (thread, sx_get_value (thread, -2));
						if (sx_is_true (sx_get_value (thread, -1))) {
							sx_pop_value (thread, -1, 1);
							sx_push_value (thread, sx_new_num (1));
							break;
						}
						sx_eval (thread, sx_get_value (thread, -1));
						if (!sx_is_true (sx_get_value (thread, -1))) {
							sx_push_value (thread, sx_new_nil ());
						} else {
							sx_push_value (thread, sx_new_num (1));
						}
						sx_pop_value (thread, -2, 1);
						break;
					case SX_OP_POP:
						sx_pop_value (thread, -1, 1);
						break;
				}
			} else { /* normal operator */
				top = thread->data - count;
				switch (op) {
					case SX_OP_ADD:
						sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, top)) + value_to_int (sx_get_value (thread, top + 1))));
						break;
					case SX_OP_SUBTRACT:
						sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, top)) - value_to_int (sx_get_value (thread, top + 1))));
						break;
					case SX_OP_MULTIPLY:
						sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, top)) * value_to_int (sx_get_value (thread, top + 1))));
						break;
					case SX_OP_DIVIDE:
						sx_push_value (thread, sx_new_num (value_to_int (sx_get_value (thread, top)) / value_to_int (sx_get_value (thread, top + 1))));
						break;
					case SX_OP_NEGATE:
						sx_push_value (thread, sx_new_num (- value_to_int (sx_get_value (thread, top))));
						break;
					case SX_OP_CALL:
						if (SX_ISFUNC (sx_get_value (thread, top))) {
							call_func (thread, sx_get_value (thread, top), count - 1, top + 1, NULL);
						} else if (SX_ISCFUNC (sx_get_value (thread, top))) {
							sx_push_value (thread, sx_get_value (thread, top)->data.cfunc (thread, NULL, count - 1, top + 1));
						} else {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_GT:
						sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, top), sx_get_value (thread, top + 1)) > 0));
						break;
					case SX_OP_LT:
						sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, top), sx_get_value (thread, top + 1)) < 0));
						break;
					case SX_OP_GTE:
						sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, top), sx_get_value (thread, top + 1)) >= 0));
						break;
					case SX_OP_LTE:
						sx_push_value (thread, sx_new_num (sx_compare (sx_get_value (thread, top), sx_get_value (thread, top + 1)) <= 0));
						break;
					case SX_OP_EQUAL:
						sx_push_value (thread, sx_new_num (sx_are_equal (sx_get_value (thread, top), sx_get_value (thread, top + 1))));
						break;
					case SX_OP_NEQUAL:
						sx_push_value (thread, sx_new_num (!sx_are_equal (sx_get_value (thread, top), sx_get_value (thread, top + 1))));
						break;
					case SX_OP_NOT:
						sx_push_value (thread, sx_new_num (!sx_is_true (sx_get_value (thread, top))));
						break;
					case SX_OP_LOOKUP:
						var = NULL;
						if (count == 1) {
							var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, top)), SX_SCOPE_DEF);
						} else if (count == 2) {
							var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, top + 1)), SX_TOINT (sx_get_value (thread, top)));
						}
						if (var) {
							sx_push_value (thread, var->value);
						} else {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_ASSIGN:
						ret = sx_new_nil ();
						if (count == 2) {
							ret = sx_get_value (thread, top + 1);
							sx_define_var (thread, SX_TOINT (sx_get_value (thread, top)), sx_get_value (thread, top + 1), SX_SCOPE_DEF);
						} else {
							ret = sx_get_value (thread, top + 2);
							sx_define_var (thread, SX_TOINT (sx_get_value (thread, top + 1)), sx_get_value (thread, top + 2), SX_TOINT (sx_get_value (thread, top)));
						}
						sx_push_value (thread, ret);
						break;
					case SX_OP_INDEX:
						value = sx_get_value (thread, top + 1);
						if (SX_ISNUM (value)) {
							sx_push_value (thread, sx_get_index (thread->system, sx_get_value (thread, top), SX_TOINT (value)));
						} else if (SX_ISRANGE (value)) {
							sx_push_value (thread, sx_get_section (thread->system, sx_get_value (thread, top), value->data.range.start, value->data.range.end));
						} else {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_PREINCREMENT:
						ret = sx_new_nil ();
						var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, top)), SX_SCOPE_DEF);
						if (var) {
							if (count == 2) {
								ret = var->value = sx_new_num (value_to_int (var->value) + value_to_int (sx_get_value (thread, top + 1)));
							} else {
								ret = var->value = sx_new_num (value_to_int (var->value) + 1);
							}
						}
						sx_push_value (thread, ret);
						break;
					case SX_OP_POSTINCREMENT:
						ret = sx_new_nil ();
						var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, top)), SX_SCOPE_DEF);
						if (var) {
							ret = var->value;
							if (count == 2) {
								var->value = sx_new_num (value_to_int (var->value) + value_to_int (sx_get_value (thread, top + 1)));
							} else {
								var->value = sx_new_num (value_to_int (var->value) + 1);
							}
						}
						sx_push_value (thread, ret);
						break;
					case SX_OP_PREDECREMENT:
						ret = sx_new_nil ();
						var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, top)), SX_SCOPE_DEF);
						if (var) {
							if (count == 2) {
								ret = var->value = sx_new_num (value_to_int (var->value) - value_to_int (sx_get_value (thread, top + 1)));
							} else {
								ret = var->value = sx_new_num (value_to_int (var->value) - 1);
							}
						}
						sx_push_value (thread, ret);
						break;
					case SX_OP_POSTDECREMENT:
						ret = sx_new_nil ();
						var = sx_get_var (thread, SX_TOINT(sx_get_value (thread, top)), SX_SCOPE_DEF);
						if (var) {
							ret = var->value;
							if (count == 2) {
								var->value = sx_new_num (value_to_int (var->value) - value_to_int (sx_get_value (thread, top + 1)));
							} else {
								var->value = sx_new_num (value_to_int (var->value) - 1);
							}
						}
						sx_push_value (thread, ret);
						break;
					case SX_OP_NEWARRAY:
						sx_push_value (thread, sx_new_stack_array (thread, count, top));
						break;
					case SX_OP_SETINDEX:
						ret = sx_new_nil ();
						if (SX_ISARRAY (sx_get_value (thread, top)) && SX_ISNUM(sx_get_value (thread, top + 1))) {
							if (SX_TOINT(sx_get_value (thread, top + 1)) >= 0) {
								if (SX_TOINT (sx_get_value (thread, top + 1)) < sx_get_value (thread, top)->data.array.count) {
									sx_get_value (thread, top)->data.array.list[SX_TOINT(sx_get_value (thread, top + 1))] = sx_get_value (thread, top + 2);
									ret = sx_get_value (thread, top + 2);
								}
							} else {
								if (-SX_TOINT (sx_get_value (thread, top + 1)) < sx_get_value (thread, top)->data.array.count) {
									sx_get_value (thread, top)->data.array.list[SX_TOINT(sx_get_value (thread, top + 1))] = sx_get_value (thread, top + 2);
									ret = sx_get_value (thread, top + 2);
								}
							}
						}
						sx_push_value (thread, ret);
						break;
					case SX_OP_SETMEMBER:
						ret = sx_new_nil ();
						if (SX_ISCLASS (sx_get_value (thread, top))) {
							if (sx_set_member (thread->system, sx_get_value (thread, top), SX_TOINT(sx_get_value (thread, top + 1)), sx_get_value (thread, top + 2))) {
								ret = sx_get_value (thread, top + 2);
							}
						}
						sx_push_value (thread, ret);
						break;
					case SX_OP_SIZEOF:
						if (SX_ISARRAY(sx_get_value (thread, top))) {
							sx_push_value (thread, sx_new_num (sx_get_value (thread, top)->data.array.count));
						} else if (SX_ISSTRING(sx_get_value (thread, top))) {
							sx_push_value (thread, sx_new_num (sx_get_value (thread, top)->data.str.len));
						} else {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_NEWCLASS:
						if (count == 2) {
							ret = sx_new_class (thread->system, sx_get_value (thread, top));
							if (sx_push_context (thread, sx_get_value (thread, top + 1), 0) != NULL) {
								sx_eval (thread, sx_get_value (thread, top + 1));
								sx_pop_value (thread, -1, 1);

								/* cheat, steal arguments */
								ret->data.klass.members = thread->context_stack[thread->context - 1].vars;
								thread->context_stack[thread->context - 1].vars = NULL;
								sx_pop_context (thread);
								sx_push_value (thread, ret);
							} else {
								sx_push_value (thread, sx_new_nil ());
							}
						} else {
							ret = sx_new_class (thread->system, NULL);
							if (sx_push_context (thread, sx_get_value (thread, top), 0) != NULL) {
								sx_eval (thread, sx_get_value (thread, top));
								sx_pop_value (thread, -1, 1);

								/* cheat, steal arguments */
								ret->data.klass.members = thread->context_stack[thread->context - 1].vars;
								thread->context_stack[thread->context - 1].vars = NULL;
								sx_pop_context (thread);
								sx_push_value (thread, ret);
							} else {
								sx_push_value (thread, sx_new_nil ());
							}
						}
						break;
					case SX_OP_MEMBER:
						if (SX_ISCLASS (sx_get_value (thread, top))) {
							sx_push_value (thread, sx_get_member (sx_get_value (thread, top), SX_TOINT(sx_get_value (thread, top + 1))));
						} else {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_NEWINSTANCE:
						if (count > 0 && SX_ISCLASS (sx_get_value (thread, top))) {
							ret = sx_new_class (thread->system, sx_get_value (thread, top));
							if (ret) {
								sx_push_value (thread, ret);
								value = sx_get_member (ret, sx_name_to_id ("init"));
								if (SX_ISFUNC (value)) {
									call_func (thread, value, 0, top + 2, ret);
									sx_pop_value (thread, -1, 1);
								} else if (SX_ISCFUNC (value)) {
									value->data.cfunc (thread, ret, 0, top + 2);
								}
							} else {
								sx_push_value (thread, sx_new_nil ());
							}
						} else {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_ISA:
						sx_push_value (thread, sx_new_num (sx_class_is_a (sx_get_value (thread, top), sx_get_value (thread, top + 1))));
						break;
					case SX_OP_TYPEOF:
						sx_push_value (thread, sx_new_num (sx_type_of (sx_get_value (thread, top))));
						break;
					case SX_OP_NEWFUNC:
						sx_push_value (thread, sx_new_func (thread->system, sx_get_value (thread, top), sx_get_value (thread, top + 1)));
						break;
					case SX_OP_METHOD:
						ret = sx_get_member (sx_get_value (thread, top), SX_TOINT(sx_get_value (thread, top + 1)));
						if (SX_ISFUNC (ret)) {
							call_func (thread, ret, count - 2, top + 2, sx_get_value (thread, top));
						} else if (SX_ISCFUNC (ret)) {
							sx_push_value (thread, ret->data.cfunc (thread, sx_get_value (thread, top), count - 2, top + 2));
						} else {
							sx_push_value (thread, sx_new_nil ());
						}
						break;
					case SX_OP_NEWRANGE:
						sx_push_value (thread, sx_new_range (thread->system, value_to_int (sx_get_value (thread, top)), value_to_int (sx_get_value (thread, top + 1))));
						break;
				}
			}

			sx_pop_value (thread, -1 - count, count);
		}
	}

	sx_unlock_value (block);

	return thread->state;
}

int
sx_run_thread (THREAD *thread) {
	thread->state = SX_STATE_RUN;
	thread->ret = sx_new_nil ();

	sx_push_context (thread, thread->main, 0);
	sx_eval (thread, thread->main);
	sx_pop_context (thread);

	thread->ret = sx_get_value (thread, 0);
	sx_pop_value (thread, -1, 1);

	if (thread->state == SX_STATE_RUN || thread->state == SX_STATE_BREAK || thread->state == SX_STATE_RETURN) {
		thread->state = SX_STATE_EXIT;
	}

	return thread->state;
}
