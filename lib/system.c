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


SYSTEM *
create_system (int argc, char **argv) {
	VALUE *args;
	SYSTEM *system = (SYSTEM *)sx_malloc (NULL, sizeof (SYSTEM));
	if (system == NULL) {
		return system;
	}

	system->threads = NULL;
	system->vars = NULL;
	system->gc_values = NULL;
	system->flags = 0;
	system->gc_count = 0;
	system->gc_thresh = GC_THRESH_SIZE;

	define_global_var (system, new_str (system, "VERSION"), new_str (system, SCRIPTIX_VERSION));
	define_global_var (system, new_str (system, "argc"), new_num (argc));

	args = new_array (system, argc, NULL);
	for (-- argc; argc >= 0; -- argc) {
		args->data.array.list[argc] = new_str (system, argv[argc]);
	}
	define_global_var (system, new_str (system, "argv"), args);

	return system;
}

void
free_system (SYSTEM *system) {
	THREAD *tnext;
	VAR *rnext;
	VALUE *vnext;

	while (system->threads != NULL) {
		tnext = system->threads->next;
		free_thread (system->threads);
		system->threads = tnext;
	}

	while (system->vars) {
		rnext = system->vars->next;
		free_var (system->vars);
		system->vars = rnext;
	}

	while (system->gc_values) {
		vnext = system->gc_values->gc_next;
		free_value (system->gc_values);
		system->gc_values = vnext;
	}

	sx_free (system);
}

void
run_gc (SYSTEM *system) {
	THREAD *thread;
	VAR *var;
	VALUE *value, *last;

	if (system->flags & SFLAG_GCOFF) {
		return;
	}

	for (var = system->vars; var != NULL; var = var->next) {
		mark_value (system, var->name);
		mark_value (system, var->value);
	}

	for (thread = system->threads; thread != NULL; thread = thread->next) {
		mark_thread (thread);
	}

	value = system->gc_values;
	while (value != NULL) {
		if ((value->flags & VFLAG_MARK) == 0 && value->locks > 0) {
			mark_value (system, value);
		}
		value = value->gc_next;
	}

	last = NULL;
	value = system->gc_values;
	while (value != NULL) {
		if ((value->flags & VFLAG_MARK) == 0) {
			-- system->gc_count;
			if (last) {
				last->gc_next = value->gc_next;
				free_value (value);
				value = last->gc_next;
			} else {
				system->gc_values = value->gc_next;
				free_value (value);
				value = system->gc_values;
			}
		} else {
			value->flags &= ~VFLAG_MARK;
			last = value;
			value = value->gc_next;
		}
	}

	system->gc_thresh = system->gc_count >= GC_THRESH_SIZE ? system->gc_count * 2 : GC_THRESH_SIZE;
}
