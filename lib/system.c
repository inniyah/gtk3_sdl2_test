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
#include "config.h"

void
_sx_default_error_hook (const char *str) {
	if (str) {
		fprintf (stderr, "Unhandled error: %s\n", str);
	}
}

SX_SYSTEM 
sx_create_system (void) {
	SX_SYSTEM system = (SX_SYSTEM )sx_malloc (sizeof (struct scriptix_system));
	if (system == NULL) {
		return system;
	}

	system->threads = NULL;
	system->modules = NULL;
	system->types = NULL;
	system->gc_list = NULL;
	system->flags = 0;
	system->gc_count = 0;
	system->gc_hook = NULL;
	system->cur_gc_thresh = SX_DEF_GC_THRESH;
	system->print_hook = (sx_print_hook)printf;
	system->error_hook = _sx_default_error_hook;
	system->valid_threads = 0;
	system->globals = NULL;

	system->data_chunk = SX_DEF_DATA_CHUNK;
	system->context_chunk = SX_DEF_CONTEXT_CHUNK;
	system->block_chunk = SX_DEF_BLOCK_CHUNK;
	system->gc_thresh = SX_DEF_GC_THRESH;

	system->core = NULL; /* important line */
	system->core = sx_new_module (system, sx_name_to_id ("Scriptix"), NULL);
	if (system->core == NULL) {
		sx_free_system (system);
		return NULL;
	}
	sx_ref_module (system->core);

	sx_init_ids ();

	system->cstring = sx_init_string (system);
	system->cint = sx_init_int (system);
	system->cblock = sx_init_block (system);
	system->carray = sx_init_array (system);
	system->cobject = sx_init_object (system);

	return system;
}

void
sx_free_system (SX_SYSTEM system) {
	SX_THREAD tnext;
	SX_VALUE vnext;
	SX_MODULE mnext;
	SX_TYPE ynext;
	SX_VAR rnext;

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
	
	while (system->modules) {
		mnext = system->modules->next;
		sx_unref_module (system->modules);
		system->modules = mnext;
	}

	sx_unref_module (system->core);

	while (system->types != NULL) {
		ynext = system->types->next;
		sx_free (system->types);
		system->types = ynext;
	}

	while (system->gc_list) {
		vnext = system->gc_list->next;
		sx_free_value (system, system->gc_list);
		system->gc_list = vnext;
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
		default:
			/* unknown option */
			return 1;
	}
}

void
sx_run (SX_SYSTEM system, unsigned long max) {
	SX_THREAD thread, last;
	int state;

	last = NULL;
	for (thread = system->threads; thread != NULL; ) {
		state = sx_run_thread (thread, max);
		switch (state) {
			case SX_STATE_ERROR:
			case SX_STATE_EXIT:
				if (last != NULL) {
					last->next = thread->next;
					sx_free_thread (thread);
					thread = last->next;
				} else {
					system->threads = thread->next;
					sx_free_thread (thread);
					thread = system->threads;
				}
				-- system->valid_threads;
				break;
			case SX_STATE_SWITCH:
				thread->state = SX_STATE_RUN;
				/* fall thru */
			default:
				thread = thread->next;
				break;
		}
	}
}

SX_VALUE 
sx_run_until (SX_SYSTEM system, sx_thread_id id) {
	SX_THREAD thread, last;
	SX_VALUE ret = NULL;
	int state;

	if (id == 0) {
		return NULL;
	}

	for (thread = system->threads; thread != NULL && thread->id != id; thread = thread->next)
		;

	if (thread == NULL) {
		return NULL;
	}

	while (id != 0) {
		last = NULL;
		for (thread = system->threads; thread != NULL; ) {
			state = sx_run_thread (thread, 1000); 	/* FIXME: conigure value comewhoe */
			switch (state) {
				case SX_STATE_ERROR:
				case SX_STATE_EXIT:
					if (id == thread->id) {
						id = 0; /* mark "return value" */
						ret = thread->ret;
					}

					if (last != NULL) {
						last->next = thread->next;
						sx_free_thread (thread);
						thread = last->next;
					} else {
						system->threads = thread->next;
						sx_free_thread (thread);
						thread = system->threads;
					}
					-- system->valid_threads;

					if (id == 0) {
						return ret;
					}
					break;
				case SX_STATE_SWITCH:
					thread->state = SX_STATE_RUN;
					/* fall thru */
				default:
					thread = thread->next;
					break;
			}
		}
	}

	return NULL;
}

void
sx_run_gc (SX_SYSTEM system) {
	SX_THREAD thread;
	SX_VALUE value, last;
	SX_MODULE module;
	SX_VAR var;

	if (system->flags & SX_SFLAG_GCOFF) {
		return;
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

	for (module = system->modules; module != NULL; module = module->next) {
		sx_mark_module (module);
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
}
