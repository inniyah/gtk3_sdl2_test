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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* AIX requires this to be the first thing in the file.  */
#ifndef __GNUC__
# if HAVE_ALLOCA_H
#  include <alloca.h>
# else
#  ifdef _AIX
	#pragma alloca /* indentation intentional */
#  else
#   ifndef alloca /* predefined by HP cc +Olibcalls */
char *alloca ();
#   endif
#  endif
# endif
#endif


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "scriptix.h"

static
int
_sx_invoke (SX_THREAD thread, SX_VALUE value, unsigned long argc)
{
	SX_VALUE* argv;
	SX_VALUE ret;
	unsigned long i;
	unsigned long count;
	unsigned long cargs;
	SX_FUNC func;

	if (SX_ISCLOSURE(thread->system, value)) {
		func = ((SX_CLOSURE)value)->func;
		cargs = ((SX_CLOSURE)value)->args->count;
	} else {
		func = ((SX_FUNC)value);
		cargs = 0; /* no closure args */
	}

	/* find largest of argc/func->argc */
	if (argc > func->argc + cargs)
		count = argc;
	else
		count = func->argc + cargs;

	/* allocate argv */
#ifdef HAVE_ALLOCA
	argv = (SX_VALUE*)alloca (count * sizeof (SX_VALUE));
#else
	argv = (SX_VALUE*)sx_malloc (count * sizeof (SX_VALUE));
#endif
	if (argv == NULL) {
		return SXE_NOMEM;
	}

	/* copy args */
	for (i = argc; i > 0; --i)
		argv[argc - i] = sx_get_value (thread, -i);

	sx_pop_value (thread, -argc, argc);

	/* handle closure args */
	if (cargs) {
		for (i = 0; i < cargs; ++i) {
			argv[argc + i] = ((SX_CLOSURE)value)->args->list[i];
		}
	}

	/* invoke */
	ret = NULL;
	func->cfunc (thread, NULL, count, argv, &ret);

	sx_push_value (thread, ret);

#ifndef HAVE_ALLOCA
	sx_free (argv);
#endif

	return SXE_OK;
}

int
sx_eval (SX_THREAD thread, unsigned long max) {
	unsigned int count;
	unsigned int op_count = max;
	int op;
	SX_BLOCK block;
	SX_VALUE ret, value;
	SX_VAR var;
	SX_CALL call;
	SX_TYPE type;
	SX_FUNC func;
	SX_METHOD method;
	sx_name_id name;

	while (thread->call > 0) {
run_code:
		call = &thread->call_stack[thread->call - 1];

		/* time to run the gc? */
		if (thread->system->gc_count >= thread->system->gc_thresh) {
			sx_run_gc (thread->system);
		}

		/* working on a C function */
		if (call->func->cfunc) {
			count = thread->data;

			ret = NULL;
			call->func->cfunc (thread, NULL, call->argc, &thread->data_stack[call->top], &ret);
			sx_push_value (thread, ret);
			sx_pop_call (thread);
			continue;
		}

		block = call->func->body;

		while (call->op_ptr < block->count && thread->state == SX_STATE_RUNNING) {
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
				case SX_OP_ADD:
					sx_push_value (thread, sx_new_num (sx_toint (sx_to_num (thread->system, sx_get_value (thread, -2))) + sx_toint (sx_to_num (thread->system, sx_get_value (thread, -1)))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_SUBTRACT:
					sx_push_value (thread, sx_new_num (sx_toint (sx_get_value (thread, -2)) - sx_toint (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_MULTIPLY:
					sx_push_value (thread, sx_new_num (sx_toint (sx_get_value (thread, -2)) * sx_toint (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_DIVIDE:
					sx_push_value (thread, sx_new_num (sx_toint (sx_get_value (thread, -2)) / sx_toint (sx_get_value (thread, -1))));
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEGATE:
					sx_push_value (thread, sx_new_num (- sx_toint (sx_get_value (thread, -1))));
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_CALL:
					count = sx_toint (sx_get_value (thread, -2));
					value = sx_get_value (thread, -1);
					sx_pop_value (thread, -2, 2);
					if (SX_ISINVOCABLE(thread->system, value)) {
						if (SX_ISCFUNC(thread->system, value)) {
							_sx_invoke (thread, value, count);
						} else {
							sx_push_call (thread, value, count);
							/* jump to executation stage */
							goto run_code;
						}
					} else {
						sx_pop_value (thread, -count, count);
						sx_raise_error (thread, SXE_BADTYPE, "Invoked data is not a function");
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
					name = sx_toint (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					if ((var = sx_get_var (thread, name)) != NULL) {
						sx_push_value (thread, var->value);
					} else if ((value = sx_get_global (thread->system, name)) != NULL) {
						sx_push_value (thread, value);
					} else if ((func = sx_get_func (thread->system, name)) != NULL) {
						sx_push_value (thread, (SX_VALUE)func);
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					break;
				case SX_OP_ASSIGN:
					ret = sx_get_value (thread, -1);
					sx_define_var (thread, sx_toint (sx_get_value (thread, -2)), ret);
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_INDEX:
					value = sx_get_value (thread, -1);
					if (SX_ISNUM (thread->system, value)) {
						sx_push_value (thread, sx_get_index (thread->system, sx_get_value (thread, -2), sx_toint (value)));
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_PREINCREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, sx_toint(sx_get_value (thread, -2)));
					if (var) {
						ret = var->value = sx_new_num (sx_toint (var->value) + sx_toint (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_POSTINCREMENT:
					ret = sx_new_nil ();
					var = sx_get_var (thread, sx_toint(sx_get_value (thread, -2)));
					if (var) {
						ret = var->value;
						var->value = sx_new_num (sx_toint (var->value) + sx_toint (sx_get_value (thread, -1)));
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -3, 2);
					break;
				case SX_OP_NEWARRAY:
					count = sx_toint (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					if (count > 0) {
						sx_push_value (thread, (SX_VALUE)sx_new_stack_array (thread, count, -count));
					} else {
						sx_push_value (thread, (SX_VALUE)sx_new_array (thread->system, 0, NULL));
					}
					sx_pop_value (thread, -1 - count, count);
					break;
				case SX_OP_SETINDEX:
					ret = sx_new_nil ();
					if (SX_ISARRAY (thread->system, sx_get_value (thread, -3)) && SX_ISNUM(thread->system, sx_get_value (thread, -2))) {
						if (sx_toint(sx_get_value (thread, -2)) >= 0) {
							if (sx_toint (sx_get_value (thread, -2)) < ((SX_ARRAY)sx_get_value (thread, -3))->count) {
								((SX_ARRAY)sx_get_value (thread, -3))->list[sx_toint(sx_get_value (thread, -2))] = sx_get_value (thread, -1);
								ret = sx_get_value (thread, -1);
							}
						} else {
							if (-sx_toint (sx_get_value (thread, -2)) < ((SX_ARRAY)sx_get_value (thread, -3))->count) {
								((SX_ARRAY)sx_get_value (thread, -3))->list[sx_toint(sx_get_value (thread, -2))] = sx_get_value (thread, -1);
								ret = sx_get_value (thread, -1);
							}
						}
					}
					sx_push_value (thread, ret);
					sx_pop_value (thread, -4, 3);
					break;
				case SX_OP_SIZEOF:
					if (SX_ISARRAY(thread->system, sx_get_value (thread, -1))) {
						sx_push_value (thread, sx_new_num (((SX_ARRAY)sx_get_value (thread, -1))->count));
					} else if (SX_ISSTRING(thread->system, sx_get_value (thread, -1))) {
						sx_push_value (thread, sx_new_num (((SX_STRING)sx_get_value (thread, -1))->len));
					} else {
						sx_push_value (thread, sx_new_nil ());
					}
					sx_pop_value (thread, -2, 1);
					break;
				case SX_OP_TYPECAST:
					value = sx_get_value (thread, -2);
					if (sx_value_is_a (thread->system, value, sx_get_type (thread->system, sx_toint(sx_get_value (thread, -1))))) {
						sx_pop_value (thread, -1, 1);
					} else {
						sx_pop_value (thread, -2, 2);
						sx_push_value (thread, NULL);
					}
					break;
				case SX_OP_METHOD:
					count = sx_toint (sx_get_value (thread, -3));
					value = sx_get_value (thread, -2); /* the type */
					name = sx_toint (sx_get_value (thread, -1));
					sx_pop_value (thread, -3, 3);

					type = sx_type_of (thread->system, value);
					if (type) {
						method = sx_get_method (thread->system, type, name);
						if (method != NULL) {
							ret = NULL;
							method->method (thread, value, count, thread->data_stack + thread->data - count, &ret);
							sx_pop_value (thread, -count, count);
							sx_push_value (thread, ret);
						} else {
							sx_pop_value (thread, -count, count);
							sx_raise_error (thread, SXE_UNDEFINED, "Method '%s' on type '%s' does not exist", sx_name_id_to_name (name), sx_name_id_to_name (type->id));
						}
					} else {
						sx_raise_error (thread, SXE_BADTYPE, "Value is not a type");
					}
					break;
				case SX_OP_STATIC_METHOD:
					count = sx_toint (sx_get_value (thread, -3));
					name = sx_toint (sx_get_value (thread, -2)); /* the type */
					type = sx_get_type (thread->system, name);
					name = sx_toint (sx_get_value (thread, -1));
					sx_pop_value (thread, -3, 3);

					if (type) {
						method = sx_get_static_method (thread->system, type, name);
						if (method != NULL) {
							ret = NULL;
							method->method (thread, NULL, count, thread->data_stack + thread->data - count, &ret);
							sx_pop_value (thread, -count, count);
							sx_push_value (thread, ret);
						} else {
							sx_pop_value (thread, -count, count);
							sx_raise_error (thread, SXE_UNDEFINED, "Static method '%s' on type '%s' does not exist", sx_name_id_to_name (name), sx_name_id_to_name (type->id));
						}
					} else {
						sx_raise_error (thread, SXE_BADTYPE, "Type '%s' does not exist", sx_name_id_to_name (name));
					}
					break;
				case SX_OP_SETFILELINE:
					value = sx_get_value (thread, -2);
					if (SX_ISSTRING (thread->system, value)) {
						call->file = value;
					} else {
						sx_pop_value (thread, -2, 2);
						sx_raise_error (thread, SXE_BADTYPE, "Tried to set filename to a non-string");
						break;
					}
					value = sx_get_value (thread, -1);
					if (SX_ISNUM (thread->system, value)) {
						call->line = sx_toint (value);
					} else {
						sx_pop_value (thread, -2, 2);
						sx_raise_error (thread, SXE_BADTYPE, "Tried to set file line to a non-number");
						break;
					}
					sx_pop_value (thread, -2, 2);
					break;
				case SX_OP_NEXTLINE:
					++ call->line;
					break;
				case SX_OP_POP:
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_JUMP:
					call->op_ptr = sx_toint (sx_get_value (thread, -1));
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_TEST:
					if (sx_is_true (thread->system, sx_get_value (thread, -1)))
						call->flags |= SX_CFLAG_TTRUE;
					else
						call->flags &= ~SX_CFLAG_TTRUE;
					break;
				case SX_OP_TJUMP:
					if (call->flags & SX_CFLAG_TTRUE) {
						call->op_ptr = sx_toint (sx_get_value (thread, -1));
					}
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_FJUMP:
					if ((call->flags & SX_CFLAG_TTRUE) == 0) {
						call->op_ptr = sx_toint (sx_get_value (thread, -1));
					}
					sx_pop_value (thread, -1, 1);
					break;
				case SX_OP_YIELD:
					/* break - switch */
					return thread->state;
					break;
				case SX_OP_IN:
					if (sx_is_in (thread->system, sx_get_value (thread, -1), sx_get_value (thread, -2))) {
						sx_pop_value (thread, -2, 2);
						sx_push_value (thread, sx_new_num (1));
					} else {
						sx_pop_value (thread, -2, 2);
						sx_push_value (thread, NULL);
					}
					break;
				case SX_OP_NEW:
					name = sx_toint (sx_get_value (thread, -1)); /* the type */
					type = sx_get_type (thread->system, name);
					sx_pop_value (thread, -1, 1);
					sx_push_value (thread, sx_type_create_new (thread->system, type));
					break;
				case SX_OP_CLOSURE:
					count = sx_toint (sx_get_value (thread, -2));
					value = sx_get_value (thread, -1);
					sx_pop_value (thread, -2, 2);
					if (SX_ISFUNC(thread->system, value)) {
						value = (SX_VALUE)sx_new_closure (thread->system, (SX_FUNC)value, count, &thread->data_stack[thread->data - count]);
						sx_pop_value (thread, -count, count);
						sx_push_value (thread, value);
					} else {
						sx_pop_value (thread, -count, count);
						sx_raise_error (thread, SXE_BADTYPE, "Closure value is not a function");
					}
					break;
			}

			/* exit out of function on thread switch */
			if (max && thread->state == SX_STATE_RUNNING) {
				if (-- op_count == 0) {
					/* berak - switch */
					return thread->state;
				}
			}
		}

		/* reset state ; if we should break, return as well */
		if (call->flags & SX_CFLAG_BREAK) {
			sx_pop_call (thread);
			if (thread->state != SX_STATE_FAILED)
				thread->state = SX_STATE_RETURN;
			return thread->state;
		} else {
			sx_pop_call (thread);
		}
	}

	/* we finished */
	thread->state = SX_STATE_FINISHED;

	return thread->state;
}

int
sx_run_thread (SX_THREAD thread, unsigned long max) {
	if (thread->state != SX_STATE_READY) {
		return SXE_NOTREADY;
	}

	thread->state = SX_STATE_RUNNING;
	sx_eval (thread, max);
	if (thread->state == SX_STATE_RUNNING)
		thread->state = SX_STATE_READY;

	if (thread->data > 0 && thread->state != SX_STATE_RUNNING) {
		thread->ret = sx_get_value (thread, -1);
		if (thread->state == SX_STATE_FAILED) {
			/* return error code */
			return sx_toint(thread->ret);
		}
	}

	/* got here, we're OK */
	return SXE_OK;
}
