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
#include <stdlib.h>

#include "scriptix.h"
#include "system.h"

/* internal array stuff */
void
_sx_array_print (SX_SYSTEM *system, SX_VALUE *value) {
	unsigned int i;
	if (value->data.array.count > 0) {
		system->print_hook ("{");
		sx_print_value (system, value->data.array.list[0]);
		for (i = 1; i < value->data.array.count; i ++) {
			system->print_hook (",");
			sx_print_value (system, value->data.array.list[i]);
		}
		system->print_hook ("}");
	} else {
		system->print_hook ("{}");
	}
}

void
_sx_array_mark (SX_SYSTEM *system, SX_VALUE *value) {
	unsigned int i;
	for (i = 0; i < value->data.array.count; ++ i) {
		sx_mark_value (system, value->data.array.list[i]);
	}
}

void
_sx_array_del (SX_SYSTEM *system, SX_VALUE *value) {
	if (value->data.array.count > 0) {
		sx_free (value->data.array.list);
	}
	sx_free (value);
}

SX_CLASS *
sx_init_array (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("array"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fprint = _sx_array_print;
	klass->core->fmark = _sx_array_mark;
	klass->core->fdel = _sx_array_del;

	return klass;
}

SX_VALUE *
sx_new_array (SX_SYSTEM *system, unsigned int argc, SX_VALUE **argv) {
	SX_VALUE *value = (SX_VALUE *)sx_malloc (system, sizeof (SX_VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->klass = system->carray;
	value->members = NULL;
	value->data.array.count = argc;
	value->data.array.size = argc;
	if (argc > 0) {
		if (argv != NULL) {
			value->data.array.list = sx_dupmem (system, argv, argc * sizeof (SX_VALUE *));
			if (value->data.array.list == NULL) {
				sx_free_value (system, value);
				return NULL;
			}
		} else {
			value->data.array.list = sx_malloc (system, argc * sizeof (SX_VALUE *));
			if (value->data.array.list == NULL) {
				sx_free_value (system, value);
				return NULL;
			}
			memset (value->data.array.list, 0, argc * sizeof (SX_VALUE *));
		}
	} else {
		value->data.array.list = NULL;
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);
	

	return value;
}

SX_VALUE *
sx_new_stack_array (SX_THREAD *thread, unsigned int argc, unsigned int top) {
	unsigned int i;
	SX_VALUE *value = (SX_VALUE *)sx_malloc (thread->system, sizeof (SX_VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->klass = thread->system->carray;
	value->members = NULL;
	value->data.array.count = argc;
	value->data.array.size = argc;
	if (argc > 0) {
		value->data.array.list = sx_malloc (thread->system, argc * sizeof (SX_VALUE *));
		if (value->data.array.list == NULL) {
			sx_free_value (thread->system, value);
			return NULL;
		}

		for (i = 0; i < argc; i ++) {
			value->data.array.list[i] = sx_get_value (thread, top + i);
		}
	} else {
		value->data.array.list = NULL;
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (thread->system, value);

	return value;
}
