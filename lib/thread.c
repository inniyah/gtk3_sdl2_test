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

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>

#include "scriptix.h"

SX_THREAD *
sx_create_thread (SX_SYSTEM *system, SX_FUNC *func, SX_ARRAY *argv) {
	SX_THREAD *thread;
	static unsigned int _free_id = 0; /* ID tag for threads */
	unsigned long i;

	sx_lock_value ((SX_VALUE *)argv);
	
	thread = (SX_THREAD *)sx_malloc (system, sizeof (SX_THREAD));

	sx_unlock_value ((SX_VALUE *)argv);

	if (thread == NULL) {
		return NULL;
	}

	thread->system = system;
	thread->next = system->threads;
	thread->call_stack = NULL;
	thread->call_size = 0;
	thread->call = 0;
	thread->data_stack = NULL;
	thread->data_size = 0;
	thread->data = 0;
	thread->ret = NULL;
	thread->state = SX_STATE_RUN;
	thread->line = 1;
	thread->file = NULL;
	thread->id = ++_free_id;
	system->threads = thread;
	++ system->valid_threads;

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
sx_end_thread (SX_THREAD *thread) {
	SX_THREAD *t;

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

SX_THREAD *
sx_create_thread_v (SX_SYSTEM *system, SX_FUNC *func, unsigned int argc, ...) {
	SX_VALUE *array;
	SX_VALUE *value;
	unsigned int i;
	va_list va;

	if (argc > 0) {
		va_start (va, argc);
		for (i = 0; i <= argc; ++ i) {
			value = va_arg (va, SX_VALUE *);
			sx_lock_value (value);
		}
		va_end (va);
		array = sx_new_array (system, argc, NULL);
		va_start (va, argc);
		for (i = 0; i <= argc; ++ i) {
			value = va_arg (va, SX_VALUE *);
			((SX_ARRAY *)array)->list[i] = value;
			sx_unlock_value (value);
		}
		va_end (va);

		return sx_create_thread (system, func, (SX_ARRAY *)array);
	} else {
		return sx_create_thread (system, func, NULL);
	}
}

void
sx_free_thread (SX_THREAD *thread) {
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
sx_mark_thread (SX_THREAD *thread) {
	unsigned int i;
	SX_VAR *var;

	if (thread->ret) {
		sx_mark_value (thread->system, thread->ret);
	}
	if (thread->file) {
		sx_mark_value (thread->system, thread->file);
	}

	for (i = 0; i < thread->call; ++ i) {
		sx_mark_func (thread->system, thread->call_stack[i].func);
		if (thread->call_stack[i].klass != NULL) {
			sx_mark_value (thread->system, thread->call_stack[i].klass);
		}
		for (var = thread->call_stack[i].vars; var != NULL; var = var->next) {
			sx_mark_value (thread->system, var->value);
		}
	}

	for (i = 0; i < thread->data; ++ i) {
		sx_mark_value (thread->system, thread->data_stack[i]);
	}
}

SX_THREAD *
sx_push_call (SX_THREAD *thread, SX_FUNC *func, SX_VALUE *klass, unsigned long argc) {
	SX_CALL *sx_new_stack;
	unsigned int i;

	if (thread->call == thread->call_size) {
		sx_lock_value (klass);
		sx_new_stack = sx_malloc (thread->system, (thread->call_size + SX_CONTEXT_CHUNK) * sizeof (SX_CALL));
		sx_unlock_value (klass);
		if (sx_new_stack == NULL) {
			return NULL;
		}
		if (thread->call_stack != NULL) {
			memcpy (sx_new_stack, thread->call_stack, thread->call_size * sizeof (SX_CALL));
			sx_free (thread->call_stack);
		}
		thread->call_size += SX_CONTEXT_CHUNK;
		thread->call_stack = sx_new_stack;
	}

	thread->call_stack[thread->call].vars = NULL;
	thread->call_stack[thread->call].klass = klass;
	thread->call_stack[thread->call].file = NULL;
	thread->call_stack[thread->call].line = 1;
	thread->call_stack[thread->call].func = func;
	thread->call_stack[thread->call].op_ptr = 0;
	thread->call_stack[thread->call].top = thread->data - argc;
	thread->call_stack[thread->call].state = -1; /* START state */
	thread->call_stack[thread->call].test = 0;
	thread->call_stack[thread->call].argc = argc;
	++ thread->call;

	if (klass) {
		sx_define_var (thread, sx_self_id, klass, SX_SCOPE_LOCAL);
	}

	/* define variables */
	if (func->args != NULL) {
		for (i = 0; i < argc && i < func->args->count; ++ i) {
			sx_define_var (thread, SX_TOINT (func->args->list[i]), sx_get_value (thread, -argc + i), SX_SCOPE_LOCAL);
		}
	}

	return thread;
}

SX_THREAD *
sx_pop_call (SX_THREAD *thread) {
	SX_VAR *rnext;
	int i;

	if (thread->call > 0) {
		i = thread->call - 1;
		while (thread->call_stack[i].vars) {
			rnext = thread->call_stack[i].vars->next;
			sx_free_var (thread->call_stack[i].vars);
			thread->call_stack[i].vars = rnext;
		}

		/* pop stack  */
		if (thread->data > thread->call_stack[i].top + 1) {
			sx_pop_value (thread, thread->call_stack[i].top, thread->data - thread->call_stack[i].top - 1);
		}

		-- thread->call;
	}

	return thread;
}

SX_VALUE *
sx_push_value (SX_THREAD *thread, SX_VALUE *value) {
	SX_VALUE **sx_new_stack;

	if (thread->data == thread->data_size) {
		sx_lock_value (value);
		sx_new_stack = sx_malloc (thread->system, (thread->data_size + SX_DATA_CHUNK) * sizeof (SX_VALUE *));
		sx_unlock_value (value);
		if (sx_new_stack == NULL) {
			return sx_new_nil ();
		}
		memcpy (sx_new_stack, thread->data_stack, thread->data_size * sizeof (SX_VALUE *));
		thread->data_size += SX_DATA_CHUNK;
		sx_free (thread->data_stack);
		thread->data_stack = sx_new_stack;
	}

	thread->data_stack[thread->data ++] = value;

	return value;
}

SX_VALUE *
sx_get_value (SX_THREAD *thread, int index) {
	if (index >= 0) {
		index += thread->call_stack[thread->call - 1].top;
		if (index < thread->data) {
			return thread->data_stack[index];
		}
	} else if (index < 0 && (-index) - 1 < thread->data) {
		return thread->data_stack[index + thread->data];
	}

	return sx_new_nil ();
}

void
sx_pop_value (SX_THREAD *thread, int start, unsigned int len) {
	if (start < 0) {
		start += thread->data;
	}

	if (start < 0 || start >= thread->data || len == 0) {
		return;
	}

	if (start + len >= thread->data) {
		len = thread->data - start;
	}

	memcpy (&thread->data_stack[start], &thread->data_stack[start + len], (thread->data - start - len) * sizeof (SX_VALUE *));

	thread->data -= len;
}
