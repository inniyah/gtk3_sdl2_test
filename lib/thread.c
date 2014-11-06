/*
 * Scriptix - Lite-weight scripting longerface
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

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>

#include "scriptix.h"

SX_THREAD 
sx_create_thread (SX_MODULE module, SX_FUNC func, SX_ARRAY argv) {
	SX_THREAD thread;
	static unsigned long _free_id = 0; /* ID tag for threads */
	unsigned long i;

	thread = (SX_THREAD)sx_malloc (sizeof (struct scriptix_thread));

	if (thread == NULL) {
		return NULL;
	}

	thread->module = module;
	thread->system = module->system;
	thread->next = module->system->threads;
	thread->call_stack = NULL;
	thread->call_size = 0;
	thread->call = 0;
	thread->data_stack = NULL;
	thread->data_size = 0;
	thread->data = 0;
	thread->ret = NULL;
	thread->state = SX_STATE_RUN;
	thread->id = ++_free_id;
	module->system->threads = thread;
	++ module->system->valid_threads;

	if (argv != NULL) {
		for (i = 0; i < SX_TOARRAY(argv)->count; ++ i) {
			sx_push_value (thread, argv->list[i]);
		}
		sx_push_call (thread, func, NULL, argv->count);
	} else {
		sx_push_call (thread, func, NULL, 0);
	}

	return thread;
}

void
sx_end_thread (SX_THREAD thread) {
	SX_THREAD t;

	if (thread->system->threads == thread) {
		thread->system->threads = thread->next;
	} else {
		for (t = thread->system->threads; t->next != thread && t->next != NULL; t = t->next)
			;
		if (t->next != NULL) {
			t->next = t->next->next;
		}
	}

	sx_free_thread (thread);
}

SX_THREAD 
sx_create_thread_v (SX_MODULE module, SX_FUNC func, unsigned long argc, ...) {
	SX_VALUE array;
	SX_VALUE value;
	unsigned long i;
	va_list va;

	if (argc > 0) {
		va_start (va, argc);
		for (i = 0; i <= argc; ++ i) {
			value = va_arg (va, SX_VALUE );
		}
		va_end (va);
		array = sx_new_array (module->system, argc, NULL);
		va_start (va, argc);
		for (i = 0; i <= argc; ++ i) {
			value = va_arg (va, SX_VALUE );
			((SX_ARRAY )array)->list[i] = value;
		}
		va_end (va);

		return sx_create_thread (module, func, (SX_ARRAY )array);
	} else {
		return sx_create_thread (module, func, NULL);
	}
}

void
sx_free_thread (SX_THREAD thread) {
	while (thread->call > 0) {
		sx_pop_call (thread);
	}

	if (thread->data_stack != NULL) {
		sx_free (thread->data_stack);
	}
	if (thread->call_stack != NULL) {
		sx_free (thread->call_stack);
	}

	sx_free (thread);
}

void
sx_mark_thread (SX_THREAD thread) {
	unsigned long i;
	SX_VAR var;

	if (thread->ret) {
		sx_mark_value (thread->system, thread->ret);
	}

	for (i = 0; i < thread->call; ++ i) {
		sx_mark_func (thread->system, thread->call_stack[i].func);
		if (thread->call_stack[i].file != NULL) {
			sx_mark_value (thread->system, thread->call_stack[i].file);
		}
		if (thread->call_stack[i].type != NULL) {
			sx_mark_value (thread->system, thread->call_stack[i].type);
		}
		for (var = thread->call_stack[i].vars; var != NULL; var = var->next) {
			sx_mark_value (thread->system, var->value);
		}
	}

	for (i = 0; i < thread->data; ++ i) {
		sx_mark_value (thread->system, thread->data_stack[i]);
	}
}

SX_THREAD 
sx_push_call (SX_THREAD thread, SX_FUNC func, SX_VALUE type, unsigned long argc) {
	SX_CALL sx_new_stack;
	SX_ARRAY var_args;
	unsigned long i;

	if (thread->call == thread->call_size) {
		sx_new_stack = sx_malloc ((thread->call_size + thread->system->context_chunk) * sizeof (struct scriptix_call));
		if (sx_new_stack == NULL) {
			return NULL;
		}
		if (thread->call_stack != NULL) {
			memcpy (sx_new_stack, thread->call_stack, thread->call_size * sizeof (struct scriptix_call));
			sx_free (thread->call_stack);
		}
		thread->call_size += thread->system->context_chunk;
		thread->call_stack = sx_new_stack;
	}

	thread->call_stack[thread->call].vars = NULL;
	thread->call_stack[thread->call].type = type;
	thread->call_stack[thread->call].file = NULL;
	thread->call_stack[thread->call].line = 1;
	thread->call_stack[thread->call].func = func;
	thread->call_stack[thread->call].op_ptr = 0;
	thread->call_stack[thread->call].top = thread->data - argc;
	thread->call_stack[thread->call].state = -1; /* START state */
	thread->call_stack[thread->call].test = 0;
	thread->call_stack[thread->call].argc = argc;
	++ thread->call;

	sx_ref_func (func);

	if (type) {
		sx_define_var (thread, sx_self_id, type);
	}

	/* define variables for non-cfuncs */
	if (func->body != NULL) {
		for (i = 0; i < argc && i < func->argc; ++ i) {
			sx_define_var (thread, func->arg_names[i], sx_get_value (thread, -argc + i));
		}
		/* var arg */
		if (func->var_arg_name) {
			if (argc > func->argc) {
				var_args = (SX_ARRAY )sx_new_array (thread->system, argc - func->argc, NULL);
				if (var_args != NULL) {
					for (; i < argc; ++ i) {
						var_args->list[i - func->argc] = sx_get_value (thread, -argc + i);
					}
					sx_define_var (thread, func->var_arg_name, (SX_VALUE )var_args);
				}
			 } else {
				 sx_define_var (thread, func->var_arg_name, sx_new_array (thread->system, 0, NULL));
			 }
		} else if (func->argc > argc) {
			for (; i < argc; ++ i) {
				sx_define_var (thread, func->arg_names[i], NULL);
			}
		}
	}

	return thread;
}

SX_CALL 
sx_get_call (SX_THREAD thread) {
	return &thread->call_stack[thread->call - 1];
}

SX_THREAD 
sx_pop_call (SX_THREAD thread) {
	SX_VAR rnext;
	long i;

	if (thread->call > 0) {
		i = thread->call - 1;
		while (thread->call_stack[i].vars) {
			rnext = thread->call_stack[i].vars->next;
			sx_free_var (thread->call_stack[i].vars);
			thread->call_stack[i].vars = rnext;
		}

		sx_unref_func (thread->call_stack[i].func);

		/* pop stack  */
		if (thread->data > thread->call_stack[i].top + 1) {
			sx_pop_value (thread, thread->call_stack[i].top, thread->data - thread->call_stack[i].top - 1);
		}

		-- thread->call;
	}

	return thread;
}

SX_VALUE 
sx_push_value (SX_THREAD thread, SX_VALUE value) {
	SX_VALUE *sx_new_stack;

	if (thread->data == thread->data_size) {
		sx_new_stack = sx_malloc ((thread->data_size + thread->system->data_chunk) * sizeof (SX_VALUE ));
		if (sx_new_stack == NULL) {
			return sx_new_nil ();
		}
		memcpy (sx_new_stack, thread->data_stack, thread->data_size * sizeof (SX_VALUE ));
		thread->data_size += thread->system->data_chunk;
		sx_free (thread->data_stack);
		thread->data_stack = sx_new_stack;
	}

	thread->data_stack[thread->data ++] = value;

	return value;
}

SX_VALUE 
sx_get_value (SX_THREAD thread, long index) {
	if (index >= 0) {
		if (thread->call > 0) {
			index += thread->call_stack[thread->call - 1].top;
		}
		if (index < thread->data) {
			return thread->data_stack[index];
		}
	} else if (index < 0 && (-index) - 1 < thread->data) {
		return thread->data_stack[index + thread->data];
	}

	return sx_new_nil ();
}

void
sx_pop_value (SX_THREAD thread, long start, unsigned long len) {
	if (start < 0) {
		start += thread->data;
	}

	if (start < 0 || start >= thread->data || len == 0) {
		return;
	}

	if (start + len >= thread->data) {
		len = thread->data - start;
	}

	memcpy (&thread->data_stack[start], &thread->data_stack[start + len], (thread->data - start - len) * sizeof (SX_VALUE ));

	thread->data -= len;
}
