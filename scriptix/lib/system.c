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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "scriptix.h"
#include "config.h"

static
void
_sx_default_error_hook (const char *file, unsigned int line, const char *str) {
	fprintf (stderr, "Unhandled error: %s:%d: %s\n", file, line,str);
}

SX_SYSTEM 
sx_create_system (void) {
	SX_SYSTEM system = (SX_SYSTEM )sx_malloc (sizeof (struct scriptix_system));
	if (system == NULL) {
		return system;
	}

	system->threads = NULL;
	system->funcs = NULL;
	system->types = NULL;
	system->tags = NULL;
	system->gc_list = NULL;
	system->flags = 0;
	system->gc_count = 0;
	system->gc_hook = NULL;
	system->cur_gc_thresh = SX_DEF_GC_THRESH;
	system->print_hook = (sx_print_hook)printf;
	system->error_hook = _sx_default_error_hook;
	system->valid_threads = 0;
	system->globals = NULL;
	system->run_length = SX_DEF_RUN_LENGTH;

	system->data_chunk = SX_DEF_DATA_CHUNK;
	system->context_chunk = SX_DEF_CONTEXT_CHUNK;
	system->block_chunk = SX_DEF_BLOCK_CHUNK;
	system->gc_thresh = SX_DEF_GC_THRESH;

	sx_init_ids ();

	if ((system->cstring = sx_init_string (system)) == NULL) {
		sx_free_system (system);
		return NULL;
	}
	if ((system->cint = sx_init_int (system)) == NULL) {
		sx_free_system (system);
		return NULL;
	}
	if ((system->cblock = sx_init_block (system)) == NULL) {
		sx_free_system (system);
		return NULL;
	}
	if ((system->carray = sx_init_array (system)) == NULL) {
		sx_free_system (system);
		return NULL;
	}
	if ((system->cobject = sx_init_object (system)) == NULL) {
		sx_free_system (system);
		return NULL;
	}
	if ((system->cfunction = sx_init_function (system)) == NULL) {
		sx_free_system (system);
		return NULL;
	}
	if ((system->cclosure = sx_init_closure (system)) == NULL) {
		sx_free_system (system);
		return NULL;
	}

	return system;
}

void
sx_free_system (SX_SYSTEM system) {
	SX_THREAD tnext;
	SX_VALUE vnext;
	SX_TYPE ynext;
	SX_VAR rnext;
	struct _scriptix_tag* gnext;

	while (system->globals) {
		rnext = system->globals->next;
		sx_free_var (rnext);
		system->globals = rnext;
	}

	while (system->threads != NULL) {
		tnext = system->threads->next;
		sx_free_thread (system->threads);
		system->threads = tnext;
	}

	while (system->gc_list) {
		vnext = system->gc_list->next;
		sx_free_value (system, system->gc_list);
		system->gc_list = vnext;
	}

	while (system->types != NULL) {
		ynext = system->types->next;
		sx_free (system->types);
		system->types = ynext;
	}

	while (system->tags != NULL) {
		gnext = system->tags->next;
		if (system->tags->tag) {
			sx_free (system->tags->tag);
		}
		sx_free (system->tags);
		system->tags = gnext;
	}

	sx_free (system);
}

int
sx_runable (SX_SYSTEM system) {
	return system->valid_threads != 0;
}

int
sx_set_option (SX_SYSTEM system, sx_option_type opt, long value) {
	switch (opt) {
		case SX_OPT_GCTHRESH:
			system->gc_thresh = value;
			return 0;
		case SX_OPT_BLOCKCHUNK:
			system->block_chunk = value;
			return 0;
		case SX_OPT_DATACHUNK:
			system->data_chunk = value;
			return 0;
		case SX_OPT_CONTEXTCHUNK:
			system->context_chunk = value;
			return 0;
		case SX_OPT_RUNLENGTH:
			system->run_length = value;
			return 0;
		default:
			/* unknown option */
			return 1;
	}
}

int
sx_run (SX_SYSTEM system) {
	SX_THREAD thread, next;

	thread = system->threads;
	while (thread != NULL) {
		sx_run_thread (thread, system->run_length);
		if (thread->state == SX_STATE_FINISHED || thread->state == SX_STATE_FAILED) {
			next = thread->next;
			sx_end_thread (thread);
			thread = next;
		} else {
			thread = thread->next;
		}
	}

	return SXE_OK;
}

int
sx_wait (SX_SYSTEM system, sx_thread_id id, int *retval) {
	SX_THREAD thread, next;

	/* check existance of valid thread */
	if (id == 0) {
		return SXE_BOUNDS;
	}
	for (thread = system->threads; thread != NULL && thread->id != id; thread = thread->next)
		;
	if (thread == NULL) {
		return SXE_UNDEFINED;
	}

	if (retval)
		*retval = 0;

	thread = system->threads;
	while (thread != NULL) { /* will break if we have no threads */
		sx_run_thread (thread, system->run_length);
		if (thread->state == SX_STATE_FINISHED || thread->state == SX_STATE_FAILED) {
			/* our thread? */
			if (thread->id == id) {
				/* return value */
				if (retval) {
					if (SX_ISNUM (thread->system, thread->ret)) {
						*retval = sx_toint (thread->ret);
					}
				}

				sx_end_thread (thread);
				return SXE_OK;
			}

			next = thread->next;
			sx_end_thread (thread);
			thread = next;
		} else {
			thread = thread->next;
		}

		/* end of list? restart */
		if (thread == NULL) {
			thread = system->threads;
		}
	}

	return SXE_OK;
}

int
sx_nested_run (SX_THREAD cur_thread, SX_VALUE* retval) {
	SX_THREAD thread, next;

	if (retval)
		*retval = NULL;

	/* not running? invalid... */
	if (cur_thread->state != SX_STATE_RUNNING)
		return SXE_NOTREADY;

	/* set ready state so it can run */
	cur_thread->state = SX_STATE_READY;

	thread = cur_thread->system->threads;
	while (thread != NULL) { /* will break if we have no threads */
		sx_run_thread (thread, thread->system->run_length);
		if (thread->state == SX_STATE_FINISHED || thread->state == SX_STATE_FAILED) {
			/* our thread? */
			if (thread == cur_thread) {
				/* return value */
				if (retval) {
					*retval = thread->ret;
				}

				sx_end_thread (thread);
				return SXE_INTERNAL;
			}

			next = thread->next;
			sx_end_thread (thread);
			thread = next;
		} else if (thread->state == SX_STATE_RETURN) {
			/* our thread? */
			if (thread == cur_thread) {
				thread->state = SX_STATE_RUNNING;
				/* return value */
				if (retval) {
					*retval = thread->ret;
				}

				return SXE_OK;
			}
		} else {
			thread = thread->next;
		}

		/* end of list? restart */
		if (thread == NULL) {
			thread = cur_thread->system->threads;
		}
	}

	return SXE_OK;
}

int
sx_run_gc (SX_SYSTEM system) {
	SX_THREAD thread;
	SX_VALUE value, last;
	SX_FUNC func;
	SX_VAR var;

	if (system->flags & SX_SFLAG_GCOFF) {
		return SXE_DISABLED;
	}

	if (system->gc_hook != NULL) {
		system->gc_hook (system);
	}

	for (var = system->globals; var != NULL; var = var->next) {
		sx_mark_value (system, var->value);
	}

	for (thread = system->threads; thread != NULL; thread = thread->next) {
		sx_mark_thread (thread);
	}

	for (func = system->funcs; func != NULL; func = func->next) {
		sx_mark_value (system, (SX_VALUE)func);
	}

	last = NULL;
	value = system->gc_list;
	while (value != NULL) {
		/* check the GC mark stored in the type pointer */
		if (((long)value->type & 0x01) == 0) {
			-- system->gc_count;
			if (last) {
				last->next = value->next;
				sx_free_value (system, value);
				value = last->next;
			} else {
				system->gc_list = value->next;
				sx_free_value (system, value);
				value = system->gc_list;
			}
		} else {
			(long)value->type &= ~0x01;
			last = value;
			value = value->next;
		}
	}

	system->cur_gc_thresh = system->gc_count >= system->gc_thresh ? system->gc_count * 2 : system->gc_thresh;

	return SXE_OK;
}
