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
_sx_default_error_hook (char *str) {
	if (str) {
		fprintf (stderr, "Unhandled error: %s\n", str);
	}
}

SX_SYSTEM *
sx_create_system (int argc, char **argv) {
	SX_VALUE *args;
	SX_SYSTEM *system = (SX_SYSTEM *)sx_malloc (NULL, sizeof (SX_SYSTEM));
	if (system == NULL) {
		return system;
	}

	system->threads = NULL;
	system->vars = NULL;
	system->classes = NULL;
	system->gc_values = NULL;
	system->flags = 0;
	system->gc_count = 0;
	system->gc_thresh = SX_GC_THRESH;
	system->gc_hook = NULL;
	system->print_hook = (sx_print_hook)printf;
	system->error_hook = _sx_default_error_hook;
	system->valid_threads = 0;

	sx_init_ids ();

	system->cstring = sx_init_string (system);
	system->cfixnum = sx_new_core_class (system, sx_name_to_id ("FixNum"));
	system->cerror = sx_init_error (system);
	system->cblock = sx_init_block (system);
	system->carray = sx_init_array (system);
	system->cfunction = sx_init_function (system);
	system->crange = sx_init_range (system);

	sx_define_system_var (system, sx_name_to_id ("SX_VERSION"), sx_new_str (system, SX_VERSION));

	args = sx_new_array (system, argc, NULL);
	for (-- argc; argc >= 0; -- argc) {
		args->data.array.list[argc] = sx_new_str (system, argv[argc]);
	}
	sx_define_system_var (system, sx_argv_id, args);

	sx_new_class (system, sx_NameError, system->cerror);
	sx_new_class (system, sx_TypeError, system->cerror);
	sx_new_class (system, sx_MemError, system->cerror);
	sx_new_class (system, sx_StackError, system->cerror);
	sx_new_class (system, sx_ArgumentError, system->cerror);

	return system;
}

void
sx_free_system (SX_SYSTEM *system) {
	SX_THREAD *tnext;
	SX_VAR *rnext;
	SX_VALUE *vnext;

	while (system->threads != NULL) {
		tnext = system->threads->next;
		sx_free_thread (system->threads);
		system->threads = tnext;
	}

	while (system->vars) {
		rnext = system->vars->next;
		sx_free_var (system->vars);
		system->vars = rnext;
	}

	while (system->gc_values) {
		vnext = system->gc_values->gc_next;
		sx_free_value (system, system->gc_values);
		system->gc_values = vnext;
	}

	sx_free (system);
}

void
sx_add_gc_value (SX_SYSTEM *system, SX_VALUE *value) {
	if (system == NULL) {
		return;
	}
	
	if (SX_ISNUM (system, value) || SX_ISNIL (system, value)) {
		return;
	}

	if (value->gc_next != NULL) {
		return;
	}

	value->gc_next = system->gc_values;
	system->gc_values = value;
	if (++ system->gc_count >= system->gc_thresh) {
		sx_lock_value (value);
		sx_run_gc (system);
		sx_unlock_value (value);
	}
}

void
sx_run_gc (SX_SYSTEM *system) {
	SX_THREAD *thread;
	SX_VAR *var;
	SX_VALUE *value, *last;

	if (system->flags & SX_SFLAG_GCOFF) {
		return;
	}

	if (system->gc_hook != NULL) {
		system->gc_hook (system);
	}

	for (var = system->vars; var != NULL; var = var->next) {
		sx_mark_value (system, var->value);
	}

	for (thread = system->threads; thread != NULL; thread = thread->next) {
		sx_mark_thread (thread);
	}

	value = system->gc_values;
	while (value != NULL) {
		if ((value->flags & SX_VFLAG_MARK) == 0 && value->locks > 0) {
			sx_mark_value (system, value);
		}
		value = value->gc_next;
	}

	last = NULL;
	value = system->gc_values;
	while (value != NULL) {
		if ((value->flags & SX_VFLAG_MARK) == 0) {
			-- system->gc_count;
			if (last) {
				last->gc_next = value->gc_next;
				sx_free_value (system, value);
				value = last->gc_next;
			} else {
				system->gc_values = value->gc_next;
				sx_free_value (system, value);
				value = system->gc_values;
			}
		} else {
			value->flags &= ~SX_VFLAG_MARK;
			last = value;
			value = value->gc_next;
		}
	}

	system->gc_thresh = system->gc_count >= SX_GC_THRESH ? system->gc_count * 2 : SX_GC_THRESH;
}

void
sx_run (SX_SYSTEM *system, unsigned int max) {
	SX_THREAD *thread, *last;
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
			case SX_STATE_RUN:
				/* ERROR: wtf? */

				/* fall thry */
			default:
				thread = thread->next;
				break;
		}
	}
}

SX_VALUE *
sx_run_until (SX_SYSTEM *system, sx_thread_id id) {
	SX_THREAD *thread, *last;
	SX_VALUE *ret = NULL;
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
				case SX_STATE_RUN:
					/* ERROR: wtf? */

					/* fall thry */
				default:
					thread = thread->next;
					break;
			}
		}
	}

	return NULL;
}
