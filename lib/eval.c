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
__INLINE__ VALUE *eval_expr (THREAD *thread, char op, unsigned int argc, unsigned int top);
int eval_node (THREAD *thread, int op, int count);

int
call_func (THREAD *thread, VALUE *func, unsigned int argc, unsigned int top, VALUE *self) {
	int i;

	if (!IS_FUNC (func)) {
		push_value (thread, new_nil ());
		return thread->state;
	}

	if (push_context (thread, func, CFLAG_HARD) == NULL) {
		push_value (thread, new_nil ());
		return thread->state;
	}

	if (self != NULL) {
		define_local_var (thread, new_str (thread->system, "self"), self);
	}

	if (IS_ARRAY (func->data.func.args)) {
		for (i = 0; i < argc && i < func->data.func.args->data.array.count; i ++) {
			if (IS_STRING (func->data.func.args->data.array.list[i]) && func->data.func.args->data.array.list[i]->data.str.len > 0) {
				define_local_var (thread, func->data.func.args->data.array.list[i], get_value (thread, top + i));
			}
		}
		for (; i < func->data.func.args->data.array.count; i ++) {
			if (IS_STRING (func->data.func.args->data.array.list[i]) && func->data.func.args->data.array.list[i]->data.str.len > 0) {
				define_local_var (thread, func->data.func.args->data.array.list[i], new_nil ());
			}
		}
	}

	eval (thread, func->data.func.body);

	if (thread->state == STATE_BREAK || thread->state == STATE_RETURN) {
		thread->state = STATE_RUN;
	}

	pop_context (thread);

	return thread->state;
}

VALUE *
eval_expr (THREAD *thread, char op, unsigned int argc, unsigned int top) {
	VALUE *ret, *value;
	VAR *var;

	ret = new_nil ();

	switch (op) {
		case OP_ADD:
			ret = new_num (value_to_int (get_value (thread, top)) + value_to_int (get_value (thread, top + 1)));
			break;
		case OP_SUBTRACT:
			ret = new_num (value_to_int (get_value (thread, top)) - value_to_int (get_value (thread, top + 1)));
			break;
		case OP_MULTIPLY:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) * value_to_int (get_value (thread, top + 1)));
			}
			break;
		case OP_DIVIDE:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) / value_to_int (get_value (thread, top + 1)));
			}
			break;
		case OP_NEGATE:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (- TO_INT (get_value (thread, top)));
			}
			break;
		case OP_CALL:
			if (IS_FUNC (get_value (thread, top))) {
				call_func (thread, get_value (thread, top), argc - 1, top + 1, NULL);
				ret = get_value (thread, -1);
				return ret;
			} else if (IS_CFUNC (get_value (thread, top))) {
				ret = get_value (thread, top)->data.cfunc (thread, NULL, argc - 1, top + 1);
				push_value (thread, ret);
				return ret;
			}
			break;
		case OP_GT:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) > value_to_int (get_value (thread, top + 1)));
			} else if (type_of (get_value (thread, top)) == VALUE_STRING) {
				if (type_of (get_value (thread, top + 1)) == VALUE_NUM) {
					ret = new_num (get_value (thread, top)->data.str.len > TO_INT (get_value (thread, top + 1)));
				} else if (type_of (get_value (thread, top + 1)) == VALUE_STRING) {
					ret = new_num (get_value (thread, top)->data.str.len > get_value (thread, top + 1)->data.str.len);
				}
			}
			break;
		case OP_LT:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) < value_to_int (get_value (thread, top + 1)));
			} else if (type_of (get_value (thread, top)) == VALUE_STRING) {
				if (type_of (get_value (thread, top + 1)) == VALUE_NUM) {
					ret = new_num (get_value (thread, top)->data.str.len < TO_INT (get_value (thread, top + 1)));
				} else if (type_of (get_value (thread, top + 1)) == VALUE_STRING) {
					ret = new_num (get_value (thread, top)->data.str.len < get_value (thread, top + 1)->data.str.len);
				}
			}
			break;
		case OP_GTE:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) >= value_to_int (get_value (thread, top + 1)));
			} else if (type_of (get_value (thread, top)) == VALUE_STRING) {
				if (type_of (get_value (thread, top + 1)) == VALUE_NUM) {
					ret = new_num (get_value (thread, top)->data.str.len >= TO_INT (get_value (thread, top + 1)));
				} else if (type_of (get_value (thread, top + 1)) == VALUE_STRING) {
					ret = new_num (get_value (thread, top)->data.str.len >= get_value (thread, top + 1)->data.str.len);
				}
			}
			break;
		case OP_LTE:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) <= value_to_int (get_value (thread, top + 1)));
			} else if (type_of (get_value (thread, top)) == VALUE_STRING) {
				if (type_of (get_value (thread, top + 1)) == VALUE_NUM) {
					ret = new_num (get_value (thread, top)->data.str.len <= TO_INT (get_value (thread, top + 1)));
				} else if (type_of (get_value (thread, top + 1)) == VALUE_STRING) {
					ret = new_num (get_value (thread, top)->data.str.len <= get_value (thread, top + 1)->data.str.len);
				}
			}
			break;
		case OP_EQUAL:
			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) == value_to_int (get_value (thread, top + 1)));
			}

			if (type_of (get_value (thread, top)) == VALUE_STRING) {
				if (!IS_STRING (get_value (thread, top + 1))) {
					ret = new_nil ();
				} else if (get_value (thread, top)->data.str.len != get_value (thread, top + 1)->data.str.len) {
					ret = new_nil ();
				} else if (get_value (thread, top)->data.str.len == 0) {
					ret = new_num (1);
				} else if (!strcasecmp (get_value (thread, top)->data.str.str, get_value (thread, top + 1)->data.str.str)) {
					ret = new_num (1);
				}
			}
			break;
		case OP_NEQUAL:
			if (type_of (get_value (thread, top)) != type_of (get_value (thread, top + 1))) {
				ret = new_num (1);
			}

			if (type_of (get_value (thread, top)) == VALUE_NUM) {
				ret = new_num (TO_INT (get_value (thread, top)) != TO_INT (get_value (thread, top + 1)));
			}

			if (type_of (get_value (thread, top)) == VALUE_STRING) {
				if (get_value (thread, top)->data.str.len != get_value (thread, top + 1)->data.str.len) {
					ret = new_num (1);
				}

				if (get_value (thread, top)->data.str.len == 0) {
					ret = new_nil ();
				}

				if (strcasecmp (get_value (thread, top)->data.str.str, get_value (thread, top + 1)->data.str.str)) {
					ret = new_num (1);
				}
			}
			break;
		case OP_NOT:
			if (!is_true (get_value (thread, top))) {
				ret = new_num (1);
			} else {
				ret = new_nil ();
			}
			break;
		case OP_LOOKUP:
			var = NULL;
			if (argc == 1) {
				if (type_of (get_value (thread, top)) == VALUE_STRING && get_value (thread, top)->data.str.len > 0) {
					var = do_get_var (thread, get_value (thread, top), SCOPE_DEF);
				}
			} else if (argc == 2) {
				if (type_of (get_value (thread, top + 1)) == VALUE_STRING && get_value (thread, top + 1)->data.str.len > 0) {
					var = do_get_var (thread, get_value (thread, top + 1), TO_INT (get_value (thread, top)));
				}
			}
			if (var) {
				ret = var->value;
			}
			break;
		case OP_ASSIGN:
			if (argc == 2) {
				if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
					ret = get_value (thread, top + 1);
					do_define_var (thread, get_value (thread, top), get_value (thread, top + 1), SCOPE_DEF);
				}
			} else {
				if (IS_STRING (get_value (thread, top + 1)) && get_value (thread, top + 1)->data.str.len > 0) {
					ret = get_value (thread, top + 2);
					do_define_var (thread, get_value (thread, top + 1), get_value (thread, top + 2), TO_INT (get_value (thread, top)));
				}
			}
			break;
		case OP_INDEX:
			if (IS_ARRAY (get_value (thread, top)) && IS_NUM (get_value (thread, top + 1))) {
				if (TO_INT (get_value (thread, top + 1)) >= 0 && TO_INT (get_value (thread, top + 1)) < get_value (thread, top)->data.array.count) {
					ret = get_value (thread, top)->data.array.list[TO_INT (get_value (thread, top + 1))];
				}
			}
			break;
		case OP_PREINCREMENT:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
				var = get_var (thread, get_value (thread, top));
				if (var) {
					if (argc == 2) {
						ret = var->value = new_num (value_to_int (var->value) + value_to_int (get_value (thread, top + 1)));
					} else {
						ret = var->value = new_num (value_to_int (var->value) + 1);
					}
				}
			}
			break;
		case OP_POSTINCREMENT:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
				var = get_var (thread, get_value (thread, top));
				if (var) {
					ret = var->value;
					if (argc == 2) {
						var->value = new_num (value_to_int (var->value) + value_to_int (get_value (thread, top + 1)));
					} else {
						var->value = new_num (value_to_int (var->value) + 1);
					}
				}
			}
			break;
		case OP_PREDECREMENT:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
				var = get_var (thread, get_value (thread, top));
				if (var) {
					if (argc == 2) {
						ret = var->value = new_num (value_to_int (var->value) - value_to_int (get_value (thread, top + 1)));
					} else {
						ret = var->value = new_num (value_to_int (var->value) - 1);
					}
				}
			}
			break;
		case OP_POSTDECREMENT:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
				var = get_var (thread, get_value (thread, top));
				if (var) {
					ret = var->value;
					if (argc == 2) {
						var->value = new_num (value_to_int (var->value) - value_to_int (get_value (thread, top + 1)));
					} else {
						var->value = new_num (value_to_int (var->value) - 1);
					}
				}
			}
			break;
		case OP_NEWARRAY:
			ret = new_stack_array (thread, argc, top);
			break;
		case OP_SETINDEX:
			if (IS_ARRAY (get_value (thread, top)) && IS_NUM(get_value (thread, top + 1))) {
				if (TO_INT(get_value (thread, top + 1)) >= 0) {
					if (TO_INT (get_value (thread, top + 1)) < get_value (thread, top)->data.array.count) {
						get_value (thread, top)->data.array.list[TO_INT(get_value (thread, top + 1))] = get_value (thread, top + 2);
						ret = get_value (thread, top + 2);
					}
				} else {
					if (-TO_INT (get_value (thread, top + 1)) < get_value (thread, top)->data.array.count) {
						get_value (thread, top)->data.array.list[TO_INT(get_value (thread, top + 1))] = get_value (thread, top + 2);
						ret = get_value (thread, top + 2);
					}
				}
			}
			break;
		case OP_SETMEMBER:
			if (IS_CLASS (get_value (thread, top)) && IS_STRING (get_value (thread, top + 1)) && get_value (thread, top + 1)->data.str.len > 0) {
				if (set_member (thread->system, get_value (thread, top), get_value (thread, top + 1), get_value (thread, top + 2))) {
					ret = get_value (thread, top + 2);
				}
			}
			break;
		case OP_SIZEOF:
			if (IS_ARRAY(get_value (thread, top))) {
				ret = new_num (get_value (thread, top)->data.array.count);
			} else if (IS_STRING(get_value (thread, top))) {
				ret = new_num (get_value (thread, top)->data.str.len);
			}
			break;
		case OP_NEWCLASS:
			if (argc == 2) {
				ret = new_class (thread->system, get_value (thread, top));
				if (push_context (thread, get_value (thread, top + 1), 0) != NULL) {
					eval (thread, get_value (thread, top + 1));
					pop_value (thread, -1, 1);

					/* cheat, steal arguments */
					ret->data.klass.members = thread->context_stack[thread->context - 1].vars;
					thread->context_stack[thread->context - 1].vars = NULL;
					pop_context (thread);
				}
			} else {
				ret = new_class (thread->system, NULL);
				if (push_context (thread, get_value (thread, top), 0) != NULL) {
					eval (thread, get_value (thread, top));
					pop_value (thread, -1, 1);

					/* cheat, steal arguments */
					ret->data.klass.members = thread->context_stack[thread->context - 1].vars;
					thread->context_stack[thread->context - 1].vars = NULL;
					pop_context (thread);
				}
			}
			break;
		case OP_MEMBER:
			if (IS_CLASS (get_value (thread, top))) {
				ret = get_member (get_value (thread, top), get_value (thread, top + 1));
			}
			break;
		case OP_NEWINSTANCE:
			if (argc > 0 && IS_CLASS (get_value (thread, top))) {
				ret = new_class (thread->system, get_value (thread, top));
				if (ret) {
					value = get_member (ret, new_str (thread->system, "init"));
					if (IS_FUNC (value)) {
						call_func (thread, value, 0, top + 2, ret);
						pop_value (thread, -1, 1);
					} else if (IS_CFUNC (value)) {
						value->data.cfunc (thread, ret, 0, top + 2);
					}
				}
			}
			break;
		case OP_ISA:
			ret = new_num (class_is_a (get_value (thread, top), get_value (thread, top + 1)));
			break;
		case OP_TYPEOF:
			ret = new_num (type_of (get_value (thread, top)));
			break;
		case OP_NEWFUNC:
			ret = new_func (thread->system, get_value (thread, top), get_value (thread, top + 1));
			break;
		case OP_METHOD:
			ret = get_member (get_value (thread, top), get_value (thread, top + 1));
			if (IS_FUNC (ret)) {
				call_func (thread, ret, argc - 2, top + 2, get_value (thread, top));
				ret = get_value (thread, -1);
				return ret;
			} else if (IS_CFUNC (ret)) {
				ret = ret->data.cfunc (thread, get_value (thread, top), argc - 2, top + 2);
				push_value (thread, ret);
				return ret;
			}
			break;
		case OP_NEWRANGE:
			ret = new_range (thread->system, value_to_int (get_value (thread, top)), value_to_int (get_value (thread, top + 1)));
			break;
	}

	push_value (thread, ret);
	return ret;
}

int
value_to_int (VALUE *value) {
	switch (type_of (value)) {
		case VALUE_NUM:
			return TO_INT (value);
			break;
		case VALUE_STRING:
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
eval_node (THREAD *thread, int op, int count) {
	unsigned int i;
	int step;
	VALUE *loop, *name;

	if (op >= 100) { /* special operator */
		switch (op) {
			case OP_IF:
				if (is_true (get_value (thread, -3))) {
					eval (thread, get_value (thread, -2));
				} else {
					eval (thread, get_value (thread, -1));
				}
				break;
			case OP_WHILE:
				push_context (thread, get_value (thread, -1), 0);
				while (thread->state == STATE_RUN) {
					if (eval (thread, get_value (thread, -2)) != STATE_RUN) {
						break;
					}
					if (!is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 2);
						break;
					}
					pop_value (thread, -1, 1);
					if (eval (thread, get_value (thread, -1)) != STATE_RUN) {
						break;
					}
					pop_value (thread, -1, 1);
				}
				pop_context (thread);
				if (thread->state == STATE_BREAK) {
					thread->state = STATE_RUN;
				} else if (thread->state == STATE_RUN) {
					push_value (thread, new_nil ());
				}
				break;
			case OP_FOR:
				if (count == 4) {
					name = get_value (thread, -4);
					loop = get_value (thread, -3);
					step = value_to_int (get_value (thread, -2));
				} else {
					name = get_value (thread, -3);
					loop = get_value (thread, -2);
					step = 1;
				}
				if (IS_ARRAY (loop)) {
					if (loop->data.array.count == 0) {
						push_value (thread, new_nil ());
						break;
					}
					push_context (thread, get_value (thread, -1), 0);
					i = (step > 0) ? 0 : (loop->data.array.count - 1);
					push_value (thread, new_nil ());
					do {
						pop_value (thread, -1, 1);
						define_local_var (thread, name, loop->data.array.list[i]);
						if (eval (thread, get_value (thread, -1)) != STATE_RUN) {
							break;
						}
						i += step;
					} while ((step > 0) ? (i < loop->data.array.count) : (i >= 0));
					pop_context (thread);
				} else if (IS_RANGE (loop)) {
					push_context (thread, get_value (thread, -1), 0);
					push_value (thread, new_nil ());
					for (i = loop->data.range.start; step > 0 ? (i <= loop->data.range.end) : (i >= loop->data.range.end); i += step) {
						pop_value (thread, -1, 1);
						define_local_var (thread, name, new_num (i));
						if (eval (thread, get_value (thread, -1)) != STATE_RUN) {
							break;
						}
					}
					pop_context (thread);
				} else {
					push_value (thread, new_nil ());
					/* raise error */
					break;
				}

				if (thread->state == STATE_BREAK) {
					thread->state = STATE_RUN;
				}
				break;
			case OP_TRY:
				push_context (thread, get_value (thread, -2), 0);
				if (eval (thread, get_value (thread, -2)) != STATE_RUN) {
					if (thread->state != STATE_ERROR) {
						pop_context (thread);
						break;
					}
					thread->state = STATE_RUN;
					define_local_var (thread, new_str (thread->system, "error"), get_value (thread, -1));
					pop_value (thread, -1, 1);
					thread->context_stack[thread->context - 1].block = get_value (thread, -1);
					eval (thread, get_value (thread, -1));
				}
				pop_context (thread);
				break;
			case OP_BREAK:
				if (count == 0) {
					push_value (thread, new_nil ());
				} else {
					push_value (thread, get_value (thread, -1));
				}
				if (thread->state == STATE_RUN) {
					thread->state = STATE_BREAK;
				}
				break;
			case OP_EVAL:
				push_context (thread, get_value (thread, -1), 0);
				eval (thread, get_value (thread, -1));
				pop_context (thread);
				break;
			case OP_RETURN:
				if (count == 0) {
					push_value (thread, new_nil ());
				} else {
					push_value (thread, get_value (thread, -1));
				}
				if (thread->state == STATE_RUN || thread->state == STATE_BREAK) {
					thread->state = STATE_RETURN;
				}
				break;
			case OP_RAISE:
				push_value (thread, get_value (thread, -1));
				thread->state = STATE_ERROR;
				break;
			case OP_AND:
				eval (thread, get_value (thread, -2));
				if (!is_true (get_value (thread, -1))) {
					pop_value (thread, -1, 1);
					push_value (thread, new_nil ());
					break;
				}
				eval (thread, get_value (thread, -1));
				if (!is_true (get_value (thread, -1))) {
					push_value (thread, new_nil ());
				} else {
					push_value (thread, new_num (1));
				}
				pop_value (thread, -2, 1);
				break;
			case OP_OR:
				eval (thread, get_value (thread, -2));
				if (is_true (get_value (thread, -1))) {
					pop_value (thread, -1, 1);
					push_value (thread, new_num (1));
					break;
				}
				eval (thread, get_value (thread, -1));
				if (!is_true (get_value (thread, -1))) {
					push_value (thread, new_nil ());
				} else {
					push_value (thread, new_num (1));
				}
				pop_value (thread, -2, 1);
				break;
			case OP_POP:
				pop_value (thread, -1, 1);
				break;
		}
	} else { /* normal operator */
		eval_expr (thread, op, count, thread->data - count);
	}

	pop_value (thread, -1 - count, count);

	return thread->state;
}

int
eval (THREAD *thread, VALUE *block) {
	struct _scriptix_node *node;

	if (!IS_BLOCK (block)) {
		push_value (thread, block);
		return thread->state;
	}

	lock_value (block);

	for (node = block->data.nodes; node != NULL; node = node->next) {
		if (node->op == 0) {
			push_value (thread, node->value);
		} else {
			if (eval_node (thread, node->op, node->count) != STATE_RUN) {
				break;
			}
		}
	}

	unlock_value (block);

	return thread->state;
}

int
run_thread (THREAD *thread) {
	thread->state = STATE_RUN;
	thread->ret = new_nil ();

	push_context (thread, thread->main, 0);
	eval (thread, thread->main);
	pop_context (thread);

	thread->ret = get_value (thread, 0);
	pop_value (thread, -1, 1);

	if (thread->state == STATE_RUN || thread->state == STATE_BREAK || thread->state == STATE_RETURN) {
		thread->state = STATE_EXIT;
	}

	return thread->state;
}
