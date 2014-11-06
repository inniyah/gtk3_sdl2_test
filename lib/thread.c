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

THREAD *
sx_create_thread (SYSTEM *system, VALUE *block) {
	THREAD *thread;

	if (!SX_ISBLOCK (block)) {
		return NULL;
	}

	sx_lock_value (block);
	
	thread = (THREAD *)sx_malloc (system, sizeof (THREAD));
	if (thread == NULL) {
		/* FIXME: error */
		return NULL;
	}

	sx_unlock_value (block);

	thread->system = system;
	thread->main = block;
	thread->next = system->threads;
	thread->context_stack = NULL;
	thread->context_size = 0;
	thread->context = 0;
	thread->data_stack = NULL;
	thread->data_size = 0;
	thread->data = 0;
	thread->ret = NULL;
	thread->state = SX_STATE_READY;
	system->threads = thread;

	return thread;
}

void
sx_end_thread (THREAD *thread) {
	THREAD *t;

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

void
sx_free_thread (THREAD *thread) {
	while (thread->context > 0) {
		sx_pop_context (thread);
	}

	sx_free (thread);
}

void
sx_mark_thread (THREAD *thread) {
	unsigned int i;
	VAR *var;

	if (thread->ret) {
		sx_mark_value (thread->system, thread->ret);
	}

	for (i = 0; i < thread->context; i ++) {
		sx_mark_value (thread->system, thread->context_stack[i].block);
		for (var = thread->context_stack[i].vars; var != NULL; var = var->next) {
			sx_mark_value (thread->system, var->name);
			sx_mark_value (thread->system, var->value);
		}
	}

	for (i = 0; i < thread->data; i ++) {
		sx_mark_value (thread->system, thread->data_stack[i]);
	}

	sx_mark_value (thread->system, thread->main);
}

THREAD *
sx_push_context (THREAD *thread, VALUE *block, unsigned char flags) {
	CONTEXT *sx_new_stack;

	if (thread->context == thread->context_size) {
		sx_new_stack = sx_malloc (thread->system, (thread->context_size + SX_CONTEXT_CHUNK) * sizeof (CONTEXT));
		if (sx_new_stack == NULL) {
			return NULL;
		}
		memcpy (sx_new_stack, thread->context_stack, thread->context_size * sizeof (CONTEXT));
		thread->context_size += SX_CONTEXT_CHUNK;
		sx_free (thread->context_stack);
		thread->context_stack = sx_new_stack;
	}

	thread->context_stack[thread->context].vars = NULL;
	thread->context_stack[thread->context].block = block;
	thread->context_stack[thread->context].flags = flags;
	++ thread->context;

	return thread;
}

THREAD *
sx_pop_context (THREAD *thread) {
	VAR *rnext;

	if (thread->context > 0) {
		while (thread->context_stack[thread->context - 1].vars) {
			rnext = thread->context_stack[thread->context - 1].vars->next;
			sx_free_var (thread->context_stack[thread->context - 1].vars);
			thread->context_stack[thread->context - 1].vars = rnext;
		}

		-- thread->context;

		/* FIXME; stack shrinking */
	}

	return thread;
}

VALUE *
sx_push_value (THREAD *thread, VALUE *value) {
	VALUE **sx_new_stack;

	if (thread->data == thread->data_size) {
		sx_lock_value (value);
		sx_new_stack = sx_malloc (thread->system, (thread->data_size + SX_DATA_CHUNK) * sizeof (VALUE *));
		sx_unlock_value (value);
		if (sx_new_stack == NULL) {
			return sx_new_nil ();
		}
		memcpy (sx_new_stack, thread->data_stack, thread->data_size * sizeof (VALUE *));
		thread->data_size += SX_DATA_CHUNK;
		sx_free (thread->data_stack);
		thread->data_stack = sx_new_stack;
	}

	thread->data_stack[thread->data ++] = value;

	return value;
}

VALUE *
sx_get_value (THREAD *thread, int index) {
	if (index >= 0 && index < thread->data) {
		return thread->data_stack[index];
	} else if (index < 0 && (-index) - 1 < thread->data) {
		return thread->data_stack[index + thread->data];
	} else {
		return sx_new_nil ();
	}
}

void
sx_pop_value (THREAD *thread, int start, unsigned int len) {
	unsigned int index;

	if (start < 0) {
		start += thread->data;
	}

	if (start < 0 || start >= thread->data || len == 0) {
		return;
	}

	if (start + len >= thread->data) {
		len = thread->data - start;
	}

	for (index = start; index < start + len; ++ index) {
		thread->data_stack[index] = thread->data_stack[index + len];
	}

	thread->data -= len;
}
