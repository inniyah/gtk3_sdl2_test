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
sx_start_thread (SX_SYSTEM *system, sx_script_id id) {
	SX_SCRIPT *script;

	for (script = system->scripts; script != NULL; script = script->next) {
		if (script->id == id) {
			return sx_create_thread (system, script->block);
		}
	}

	return NULL;
}

SX_THREAD *
sx_create_thread (SX_SYSTEM *system, SX_VALUE *block) {
	SX_THREAD *thread;

	if (!SX_ISBLOCK (block)) {
		return NULL;
	}

	sx_lock_value (block);
	
	thread = (SX_THREAD *)sx_malloc (system, sizeof (SX_THREAD));
	if (thread == NULL) {
		/* FIXME: error */
		return NULL;
	}

	sx_unlock_value (block);

	thread->system = system;
	thread->main = block;
	thread->next = system->threads;
	thread->call_stack = NULL;
	thread->call_size = 0;
	thread->call = 0;
	thread->cur_class = NULL;
	thread->data_stack = NULL;
	thread->data_size = 0;
	thread->data = 0;
	thread->ret = NULL;
	thread->state = SX_STATE_READY;
	system->threads = thread;
	++ system->valid_threads;

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
	if (thread->main) {
		sx_mark_value (thread->system, thread->main);
	}

	for (i = 0; i < thread->call; ++ i) {
		if (thread->call_stack[i].block != NULL) {
			sx_mark_value (thread->system, thread->call_stack[i].block);
		}
		if (thread->call_stack[i].stmt != NULL) {
			sx_mark_value (thread->system, thread->call_stack[i].block);
		}
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

	sx_mark_value (thread->system, thread->main);
}

SX_THREAD *
sx_push_call (SX_THREAD *thread, SX_VALUE *block, SX_VALUE *klass, unsigned char flags) {
	SX_CALL *sx_new_stack;

	if (thread->call == thread->call_size) {
		sx_lock_value (block);
		sx_new_stack = sx_malloc (thread->system, (thread->call_size + SX_CONTEXT_CHUNK) * sizeof (SX_CALL));
		sx_unlock_value (block);
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
	thread->call_stack[thread->call].flags = flags;
	thread->call_stack[thread->call].block = block;
	thread->call_stack[thread->call].op_ptr = 0;
	thread->call_stack[thread->call].top = thread->data;
	thread->call_stack[thread->call].state = -1; /* START state */
	thread->call_stack[thread->call].stmt = NULL;
	++ thread->call;

	if (klass != NULL) {
		thread->cur_class = klass;
	} else if (flags & SX_CFLAG_HARD) {
		thread->cur_class = NULL;
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

		-- thread->call;

		/* FIXME; stack shrinking */
	}

	/* reset cur_class */
	thread->cur_class = NULL;
	for (i = thread->call - 1; i >= 0; -- i) {
		if (thread->call_stack[i].klass != NULL) {
			thread->cur_class = thread->call_stack[i].klass;
			break;
		}
		if (thread->call_stack[i].flags & SX_CFLAG_HARD && i != 0) {
			i = 1; /* will be - on next iteration */
		}
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
	if (index >= 0 && index < thread->data) {
		return thread->data_stack[index];
	} else if (index < 0 && (-index) - 1 < thread->data) {
		return thread->data_stack[index + thread->data];
	} else {
		return sx_new_nil ();
	}
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
