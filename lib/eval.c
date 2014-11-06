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

int call_func (THREAD *thread, VALUE *func, unsigned int argc, unsigned int top, VALUE *self);
int value_to_int (VALUE *value);
int eval_node (THREAD *thread, NODE *node);

int
call_func (THREAD *thread, VALUE *func, unsigned int argc, unsigned int top, VALUE *self) {
	int i;

	if (!IS_FUNC (func)) {
		push_value (thread, new_nil ());
		return thread->state;
	}

	if (push_context (thread, func) == NULL) {
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
add_values (THREAD *thread, VALUE *one, VALUE *two) {
	VALUE *ret = NULL;
	char *str;

	if (type_of (one) == VALUE_NUM) {
		ret = new_num (TO_INT (one) + value_to_int (two));
	} else if (IS_STRING (one)) {
		if (IS_STRING (two)) {
			ret = new_str (thread->system, NULL);

			str = (char *)sx_malloc (thread->system, one->data.str.len + two->data.str.len + 1);
			if (str == NULL) {
				thread->state = STATE_ERROR;
				return new_nil ();
			}
			str[0] = 0;

			if (one->data.str.len) {
				strcat (str, one->data.str.str);
			}
			if (two->data.str.len) {
				strcat (str, two->data.str.str);
			}

			ret->data.str.str = str;
			ret->data.str.len = one->data.str.len + two->data.str.len;

		} else if (IS_NUM (two)) {
			ret = new_str (thread->system, NULL);

			str = (char *)sx_malloc (thread->system, one->data.str.len + 20 + 1); /* 20 max digits */
			if (str == NULL) {
				thread->state = STATE_ERROR;
				return new_nil ();
			}
			str[0] = 0;

			if (one->data.str.len) {
				strcat (str, one->data.str.str);
			}

			snprintf (str + one->data.str.len, 20, "%lu", TO_INT (two));

			ret->data.str.str = str;
			ret->data.str.len = strlen (str);;
		} else if (IS_NIL (two)) {
			ret = one;
		}
	}

	return ret;
}

VALUE *
eval_expr (THREAD *thread, char op, unsigned int argc, unsigned int top) {
	VALUE *ret, *value;
	VAR *var;

	ret = new_nil ();

	switch (op) {
		case OP_ADD:
			if (argc >= 2) {
				ret = add_values (thread, get_value (thread, top), get_value (thread, top + 1));
			}
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
				if (argc > 2) {
					call_func (thread, get_value (thread, top), argc - 2, top + 2, get_value (thread, top + 1));
				} else if (argc > 1) {
					call_func (thread, get_value (thread, top), 0, top + 2, get_value (thread, top + 1));
				} else {
					call_func (thread, get_value (thread, top), 0, top + 1, NULL);
				}
				ret = get_value (thread, -1);
				pop_value (thread, -1, 1);
			} else if (IS_CFUNC (get_value (thread, top))) {
				if (argc > 2) {
					ret = get_value (thread, top)->data.cfunc (thread, get_value (thread, top + 1), argc - 2, top + 2);
				} else if (argc > 1) {
					ret = get_value (thread, top)->data.cfunc (thread, get_value (thread, top + 1), 0, top + 2);
				} else {
					ret = get_value (thread, top)->data.cfunc (thread, new_nil (), 0, top + 1);
				}
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
			if (type_of (get_value (thread, top)) == VALUE_STRING && get_value (thread, top)->data.str.len > 0) {
				ret = do_lookup_var (thread, get_value (thread, top)->data.str.str, TO_INT (get_value (thread, top + 1)));
			}
			break;
		case OP_ASSIGN:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0 && argc > 1) {
				ret = get_value (thread, top + 1);
				do_define_var (thread, get_value (thread, top), get_value (thread, top + 1), TO_INT (get_value (thread, top + 2)));
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
				var = get_var (thread, get_value (thread, top)->data.str.str, SCOPE_DEF);
				if (var) {
					ret = var->value = add_values (thread, var->value, get_value (thread, top + 1));
				}
			}
			break;
		case OP_POSTINCREMENT:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
				var = get_var (thread, get_value (thread, top)->data.str.str, SCOPE_DEF);
				if (var) {
					ret = var->value;
					var->value = add_values (thread, var->value, get_value (thread, top + 1));
				}
			}
			break;
		case OP_PREDECREMENT:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
				var = get_var (thread, get_value (thread, top)->data.str.str, SCOPE_DEF);
				if (var) {
					ret = var->value = new_num (value_to_int (var->value) - value_to_int (get_value (thread, top + 1)));
				}
			}
			break;
		case OP_POSTDECREMENT:
			if (IS_STRING (get_value (thread, top)) && get_value (thread, top)->data.str.len > 0) {
				var = get_var (thread, get_value (thread, top)->data.str.str, SCOPE_DEF);
				if (var) {
					ret = var->value;
					var->value = new_num (value_to_int (var->value) - value_to_int (get_value (thread, top + 1)));
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
				if (set_member (thread->system, get_value (thread, top), get_value (thread, top + 1)->data.str.str, get_value (thread, top + 2))) {
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
			if (argc > 0 && IS_CLASS (get_value (thread, top))) {
				ret = new_class (thread->system, get_value (thread, top));
			} else {
				ret = new_class (thread->system, NULL);
			}
			if (argc > 1 && IS_BLOCK (get_value (thread, top + 1))) {
				if (push_context (thread, get_value (thread, top + 1)) != NULL) {
					eval (thread, get_value (thread, top + 1));

					/* cheat, steal arguments */
					ret->data.klass.members = thread->context_stack[thread->context - 1].vars;
					thread->context_stack[thread->context - 1].vars = NULL;
					pop_context (thread);
					pop_value (thread, -1, 1);
				}
			}
			break;
		case OP_MEMBER:
			if (IS_CLASS (get_value (thread, top)) && IS_STRING (get_value (thread, top + 1)) && get_value (thread, top + 1)->data.str.len > 0) {
				ret = get_member (get_value (thread, top), get_value (thread, top + 1)->data.str.str);
			}
			break;
		case OP_NEWINSTANCE:
			if (argc > 0 && IS_CLASS (get_value (thread, top))) {
				ret = new_class (thread->system, get_value (thread, top));
				if (ret) {
					value = get_member (ret, "init");
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
	}

	push_value (thread, ret);
	return ret;
}

int
eval_for (THREAD *thread, NODE *node) {
	int i;
	VALUE *loop;

	if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
		return thread->state;
	}
	if (!IS_STRING (get_value (thread, -1))) {
		pop_value (thread, -1, 1);
		push_value (thread, new_nil ());
		/* raise error */
		return thread->state;
	}
	if (eval_node (thread, node->data.expr.nodes[2]) != STATE_RUN) {
		pop_value (thread, -2, 1);
		return thread->state;
	}
	if (eval_node (thread, node->data.expr.nodes[1]) != STATE_RUN) {
		pop_value (thread, -3, 2);
		return thread->state;
	}
	loop = get_value (thread, -1);
	if (IS_ARRAY (loop)) {
		if (loop->data.array.count == 0) {
			pop_value (thread, -3, 3);
			push_value (thread, new_nil ());
			return thread->state;
		}
		push_context (thread, get_value (thread, -2));
		i = 0;
		do {
			if (i > 0) {
				pop_value (thread, -1, 1);
			}
			define_local_var (thread, get_value (thread, -3), loop->data.array.list[i]);
			if (eval (thread, get_value (thread, -2)) != STATE_RUN) {
				break;
			}
			++ i;
		} while (i < loop->data.array.count);
	} else if (IS_RANGE (get_value (thread, -1))) {
		push_value (thread, new_nil ());
		for (i = loop->data.range.start; loop->data.range.step > 0 ? (i <= loop->data.range.end) : (i >= loop->data.range.end); i += loop->data.range.step) {
			pop_value (thread, -1, 1);
			define_local_var (thread, get_value (thread, -3), new_num (i));
			if (eval (thread, get_value (thread, -2)) != STATE_RUN) {
				break;
			}
		}
		return thread->state;
	} else {
		pop_value (thread, -3, 3);
		push_value (thread, new_nil ());
		/* raise error */
		return thread->state;
	}

	pop_value (thread, -4, 3);
	pop_context (thread);
	if (thread->state == STATE_BREAK) {
		thread->state = STATE_RUN;
	}
	return thread->state;
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
eval_node (THREAD *thread, NODE *node) {
	unsigned int top;
	unsigned int i;

	if (node == NULL) {
		push_value (thread, new_nil ());
		return thread->state;
	}

	top = thread->data;

	switch (node->type) {
		case NODE_VALUE:
			push_value (thread, node->data.value);
			break;
		case NODE_EXPR:
			switch (node->data.expr.op) {
				case OP_IF:
					if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
						break;
					}
					if (is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 1);
						if (eval_node (thread, node->data.expr.nodes[1]) != STATE_RUN) {
							break;
						}
						eval (thread, get_value (thread, -1));
						pop_value (thread, -2, 1);
					} else if (node->data.expr.count > 2) {
						pop_value (thread, -1, 1);
						if (eval_node (thread, node->data.expr.nodes[2]) != STATE_RUN) {
							break;
						}
						eval (thread, get_value (thread, -1));
						pop_value (thread, -2, 1);
					} else {
						pop_value (thread, -1, 1);
						push_value (thread, new_nil ());
					}
					break;
				case OP_WHILE:
					if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
						break;
					}
					if (!is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 1);
						push_value (thread, new_nil ());
						break;
					}
					while (thread->state == STATE_RUN) {
						pop_value (thread, -1, 1);
						if (eval_node (thread, node->data.expr.nodes[1]) != STATE_RUN) {
							if (thread->state == STATE_BREAK) {
								thread->state = STATE_RUN;
							}
						}
						if (eval (thread, get_value (thread, -1)) != STATE_RUN) {
							pop_value (thread, -2, 1);
							if (thread->state == STATE_BREAK) {
								thread->state = STATE_RUN;
								break;
							}
						}
						pop_value (thread, -2, 1);
						if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
							pop_value (thread, -2, 1);
							break;
						}
						if (!is_true (get_value (thread, -1))) {
							pop_value (thread, -1, 1);
							break;
						}
					}
					break;
				case OP_UNTIL:
					if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
						break;
					}
					if (is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 1);
						push_value (thread, new_nil ());
						break;
					}
					while (thread->state == STATE_RUN) {
						pop_value (thread, -1, 1);
						if (eval_node (thread, node->data.expr.nodes[1]) != STATE_RUN) {
							if (thread->state == STATE_BREAK) {
								thread->state = STATE_RUN;
							}
						}
						if (eval (thread, get_value (thread, -1)) != STATE_RUN) {
							pop_value (thread, -2, 1);
							if (thread->state == STATE_BREAK) {
								thread->state = STATE_RUN;
								break;
							}
						}
						pop_value (thread, -2, 1);
						if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
							pop_value (thread, -2, 1);
							break;
						}
						if (is_true (get_value (thread, -1))) {
							pop_value (thread, -1, 1);
							break;
						}
					}
					break;
				case OP_TRY:
					if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
						break;
					}
					push_context (thread, get_value (thread, -1));
					if (eval (thread, get_value (thread, -1)) != STATE_RUN) {
						pop_value (thread, -2, 1);
						if (thread->state != STATE_ERROR) {
							pop_context (thread);
							break;
						}
						thread->state = STATE_RUN;
						if (eval_node (thread, node->data.expr.nodes[1]) != STATE_RUN) {
							pop_value (thread, -2, 1);
							pop_context (thread);
							break;
						}
						define_local_var (thread, new_str (thread->system, "error"), get_value (thread, -2));
						eval (thread, get_value (thread, -1));
						pop_value (thread, -3, 2);
					}
					pop_context (thread);
					pop_value (thread, -2, 1);
					break;
				case OP_FOR:
					eval_for (thread, node);
					break;
				case OP_BREAK:
					if (node->data.expr.count > 0) {
						eval_node (thread, node->data.expr.nodes[0]);
					} else {
						push_value (thread, new_nil ());
					}
					if (thread->state == STATE_RUN) {
						thread->state = STATE_BREAK;
					}
					break;
				case OP_EVAL:
					if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
						break;
					}
					push_context (thread, get_value (thread, -1));
					eval (thread, get_value (thread, -1));
					pop_context (thread);
					pop_value (thread, -2, 1);
					break;
				case OP_RETURN:
					if (node->data.expr.count > 0) {
						eval_node (thread, node->data.expr.nodes[0]);
					} else {
						push_value (thread, new_nil ());
					}
					if (thread->state == STATE_RUN || thread->state == STATE_BREAK) {
						thread->state = STATE_RETURN;
					}
					break;
				case OP_RAISE:
					eval_node (thread, node->data.expr.nodes[0]);
					thread->state = STATE_ERROR;
					break;
				case OP_AND:
					if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
						return thread->state;
					}
					if (!is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 1);
						push_value (thread, new_nil ());
						return thread->state;
					}
					pop_value (thread, -1, 1);
					if (eval_node (thread, node->data.expr.nodes[1]) != STATE_RUN) {
						return thread->state;
					}
					if (is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 1);
						push_value (thread, new_num (1));
					} else {
						pop_value (thread, -1, 1);
						push_value (thread, new_nil ());
					}
					break;
				case OP_OR:
					if (eval_node (thread, node->data.expr.nodes[0]) != STATE_RUN) {
						return thread->state;
					}
					if (is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 1);
						push_value (thread, new_nil ());
						return thread->state;
					}
					pop_value (thread, -1, 1);
					if (eval_node (thread, node->data.expr.nodes[1]) != STATE_RUN) {
						return thread->state;
					}
					if (is_true (get_value (thread, -1))) {
						pop_value (thread, -1, 1);
						push_value (thread, new_num (1));
					} else {
						pop_value (thread, -1, 1);
						push_value (thread, new_nil ());
					}
					break;
				default:
					for (i = 0; i < node->data.expr.count; i ++) {
						if (eval_node (thread, node->data.expr.nodes[i]) != STATE_RUN) {
							pop_value (thread, top, i);
							return thread->state;
						}
					}
					eval_expr (thread, node->data.expr.op, i, top);
					pop_value (thread, top, node->data.expr.count);
					break;
			}
			break;
	}

	return thread->state;
}

int
eval (THREAD *thread, VALUE *block) {
	NODE *node;

	if (!IS_BLOCK (block)) {
		push_value (thread, block);
		return thread->state;
	}

	lock_value (block);

	push_value (thread, new_nil ());

	for (node = block->data.nodes; node != NULL; node = node->next) {
		pop_value (thread, -1, 1);
		if (eval_node (thread, node) != STATE_RUN) {
			break;
		}
	}

	unlock_value (block);

	return thread->state;
}

int
run_thread (THREAD *thread) {
	thread->state = STATE_RUN;
	thread->ret = new_nil ();

	eval (thread, thread->main);

	thread->ret = get_value (thread, 0);
	pop_value (thread, -1, 1);

	if (thread->state == STATE_RUN || thread->state == STATE_BREAK || thread->state == STATE_RETURN) {
		thread->state = STATE_EXIT;
	}

	return thread->state;
}
