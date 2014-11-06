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

int
sx_eval (SX_THREAD *thread, unsigned int max) {
	unsigned int count;
	unsigned int i;
	unsigned int op_count = max;
	int op;
	SX_BLOCK *block;
	SX_VALUE *loop;
	SX_VALUE *ret, *value;
	SX_VAR *var;
	SX_CALL *call;
	SX_CLASS *klass;
	SX_FUNC *func;
	sx_name_id name;

	while (thread->call > 0 && thread->state == SX_STATE_RUN) {
run_code:
		call = &thread->call_stack[thread->call - 1];

		/* working on a C function */
		if (call->func->cfunc) {
			count = thread->data;

			call->func->cfunc (thread, call->klass, call->func->data, call->argc);

			sx_pop_call (thread);
			continue;
		}

		block = call->func->body;

		while (call->op_ptr < block->count && thread->state == SX_STATE_RUN) {
			/* store op for faster access */
			op = block->nodes[call->op_ptr].op;

			/* push value */
			if (op == 0) {
				sx_push_value (thread, block->nodes[call->op_ptr].value);
				++ call->op_ptr;
				continue;
			}

			/* next op */
			++ call->op_ptr;

			switch (op) {
				case SX_OP_FOR:
					name = SX_TOINT (sx_get_value (thread, -3));
					loop = sx_get_value (thread, -2);
					value = sx_get_value (thread, -1);
					if (SX_ISARRAY (thread->system, loop)) {
						call->test = 0;
						if (value == NULL) {
							i = 0;
						} else {
							i = SX_TOINT (value) + 1;
						}
						if (i >= SX_TOARRAY(loop)->count) {
							call->test = 0;
						} else {
							call->test = 1;
							sx_pop_value (thread, -1, 1);
							value = SX_TOARRAY(loop)->list[i];
							sx_push_value (thread, sx_new_num (i));
							sx_define_var (thread, name, value, SX_SCOPE_LOCAL);
						}
					} else {
						sx_pop_value (thread, -3, 3);
						sx_raise_error (thread, sx_TypeError, "Invalid type for loop base");
					}
					break;
				case SX_OP_TRY:
#if 0
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
								for (i = 0; i < SX_TOARRAY(loop)->count; i += 2) {
									klass = sx_get_class (thread->system, SX_TOINT(SX_TOARRAY(loop)->list[i]));
									if (klass && sx_value_is_a (thread->system, ret, klass)) {
										sx_push_call (thread, sx_get_value (thread, -2), NULL, 0);
										sx_define_var (thread, SX_TOINT(SX_TOARRAY(loop)->list[i + 1]), ret, SX_SCOPE_LOCAL);
										break;
									}
								}
								if (i >= SX_TOARRAY(loop)->count) { /* no found it, or not accepted it */
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
#endif
					break;
				case SX_OP_RAISE:
					name = SX_TOINT (sx_get_value (thread, -2));
					value = sx_get_value (thread, -1);
					sx_pop_value (thread, -2, 2);
					ret = sx_new_error (thread, name, value);
					if (ret) {
						thread->state = SX_STATE_ERROR;
						sx_push_value (thread, ret);
					} else {
						sx_raise_error (thread, sx_NameError, "Invalid error name");
					}
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
					count = SX_TOINT (sx_get_value (thread, -2));
					name = SX_TOINT (sx_get_value (thread, -1));
					func = sx_get_func (thread->system, name);
					sx_pop_value (thread, -2, 2);
					if (func != NULL) {
						sx_push_call (thread, func, NULL, count);
						/* jump to executation stage */
						goto run_code;
					} else {
						sx_pop_value (thread, -count, count);
						sx_raise_error (thread, sx_NameError, "Function '%s' does not exist", sx_name_id_to_name (name));
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
					ret = sx_get_value (thread, -1);
					sx_define_var (thread, SX_TOINT (sx_get_value (thread, -3)), ret, SX_TOINT (sx_get_value (thread, -2)));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_INDEX:
					value = sx_get_value (thread, -1);
					if (SX_ISNUM (thread->system, value)) {
						sx_push_value (thread, sx_get_index (thread->system, sx_get_value (thread, -2), SX_TOINT (value)));
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
				case SX_OP_NEWARRAY:
					count = SX_TOINT (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					if (count > 0) {
						sx_push_value (thread, sx_new_stack_array (thread, count, -count));
					} else {
						sx_push_value (thread, sx_new_array (thread->system, 0, NULL));
					}
					sx_pop_value (thread, -1 - count, count);
					break;
				case SX_OP_SETINDEX:
					ret = sx_new_nil ();
					if (SX_ISARRAY (thread->system, sx_get_value (thread, -3)) && SX_ISNUM(thread->system, sx_get_value (thread, -2))) {
						if (SX_TOINT(sx_get_value (thread, -2)) >= 0) {
							if (SX_TOINT (sx_get_value (thread, -2)) < SX_TOARRAY(sx_get_value (thread, -3))->count) {
								SX_TOARRAY(sx_get_value (thread, -3))->list[SX_TOINT(sx_get_value (thread, -2))] = sx_get_value (thread, -1);
								ret = sx_get_value (thread, -1);
							}
						} else {
							if (-SX_TOINT (sx_get_value (thread, -2)) < SX_TOARRAY(sx_get_value (thread, -3))->count) {
								SX_TOARRAY(sx_get_value (thread, -3))->list[SX_TOINT(sx_get_value (thread, -2))] = sx_get_value (thread, -1);
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
						sx_push_value (thread, sx_new_num (SX_TOARRAY(sx_get_value (thread, -1))->count));
					} else if (SX_ISSTRING(thread->system, sx_get_value (thread, -1))) {
						sx_push_value (thread, sx_new_num (SX_TOSTRING (sx_get_value (thread, -1))->len));
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_MEMBER:
					value = sx_get_member (thread->system, sx_get_value (thread, -2), SX_TOINT(sx_get_value (thread, -1)));
					sx_push_value (thread, value);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEWINSTANCE:
					count = SX_TOINT (sx_get_value (thread, -2));
					name = SX_TOINT (sx_get_value (thread, -1));
					klass = sx_get_class (thread->system, name);
					sx_pop_value (thread, -2, 2);
					if (klass != NULL) {
						ret = sx_new_object (thread->system, klass);
						if (ret) {
							/* ugly hack */
							thread->data_stack[thread->data - count - 1] = ret;
							func = sx_get_method (thread->system, klass, sx_init_id);
							if (func) {
								sx_push_call (thread, func, ret, count);
								goto run_code;
							} else {
								sx_pop_value (thread, -count, count);
								sx_push_value (thread, NULL);
							}
						} else {
							sx_pop_value (thread, -count, count);
							sx_raise_error (thread, sx_MemError, "Failed to create object '%s'", sx_name_id_to_name (klass->id));
						}
					} else {
						sx_pop_value (thread, -count, count);
						sx_raise_error (thread, sx_NameError, "Class '%s' does not exist", sx_name_id_to_name (name));
					}
					break;
				case SX_OP_ISA:
					value = sx_get_value (thread, -2);
					klass = sx_get_class (thread->system, SX_TOINT(sx_get_value (thread, -1)));
					sx_pop_value (thread, -2, 2);
					if (klass) {
						sx_push_value (thread, sx_new_num (sx_value_is_a (thread->system, value, klass)));
					} else {
						sx_raise_error (thread, sx_NameError, "Parent is not a class");
					}
					break;
				case SX_OP_METHOD:
					count = SX_TOINT (sx_get_value (thread, -3));
					value = sx_get_value (thread, -2); /* the class */
					name = SX_TOINT (sx_get_value (thread, -1));
					sx_pop_value (thread, -3, 3);

					klass = sx_class_of (thread->system, value);
					if (klass) {
						func = sx_get_method (thread->system, klass, name);
						if (func != NULL) {
							sx_push_call (thread, func, value, count);
							/* jump to executation stage */
							goto run_code;
						} else {
							sx_pop_value (thread, -count, count);
							sx_raise_error (thread, sx_NameError, "Method '%s' on class '%s' does not exist", sx_name_id_to_name (name), sx_name_id_to_name (klass->id));
						}
					} else {
						sx_raise_error (thread, sx_TypeError, "Value is not a class");
					}
					break;
				case SX_OP_STATIC_METHOD:
					count = SX_TOINT (sx_get_value (thread, -3));
					name = SX_TOINT (sx_get_value (thread, -2)); /* the class */
					klass = sx_get_class (thread->system, name);
					name = SX_TOINT (sx_get_value (thread, -1));
					sx_pop_value (thread, -3, 3);

					if (klass) {
						func = sx_get_static_method (thread->system, klass, name);
						if (func != NULL) {
							sx_push_call (thread, func, NULL, count);
							/* jump to executation stage */
							goto run_code;
						} else {
							sx_pop_value (thread, -count, count);
							sx_raise_error (thread, sx_NameError, "Static method '%s' on class '%s' does not exist", sx_name_id_to_name (name), sx_name_id_to_name (klass->id));
						}
					} else {
						sx_raise_error (thread, sx_TypeError, "Class '%s' does not exist", sx_name_id_to_name (name));
					}
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
				case SX_OP_POP:
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_JUMP:
					call->op_ptr = SX_TOINT (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_TEST:
					call->test = sx_is_true (thread->system, sx_get_value (thread, -1));
					break;
				case SX_OP_TJUMP:
					if (call->test) {
						call->op_ptr = SX_TOINT (sx_get_value (thread, -1));
					}
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_FJUMP:
					if (!call->test) {
						call->op_ptr = SX_TOINT (sx_get_value (thread, -1));
					}
					sx_pop_value (thread, -1, 1);
					break;
			}

			/* exit out of function on thread switch */
			if (max && thread->state == SX_STATE_RUN) {
				if (-- op_count == 0) {
					thread->state = SX_STATE_SWITCH;
					return thread->state;
				}
			}
		}

		/* reset state */
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
		thread->ret = sx_get_value (thread, -1);
	}

	switch (thread->state) {
		case SX_STATE_ERROR:
			if (thread->system->error_hook != NULL) {
				SX_VALUE *val = sx_to_str (thread->system, thread->ret);
				if (val) {
					sx_lock_value (val);
					thread->system->error_hook (SX_TOSTRING (val)->str);
					sx_unlock_value (val);
				}
			}
			break;
		case SX_STATE_RUN:
			thread->state = SX_STATE_EXIT;
			break;
	}

	return thread->state;
}
