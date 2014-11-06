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

#include <stdlib.h>

#include "scriptix.h"

/* helper functions */
void
_sx_error_print (SX_SYSTEM *system, SX_VALUE *value) {
	system->print_hook ("<Exception %s# %s:%d", sx_name_id_to_name (value->data.error.id), SX_TOSTR (system, value->data.error.file), value->data.error.line);
	if (!SX_ISNIL (system, value->data.error.data)) {
		system->print_hook (" <");
		sx_print_value (system, value->data.error.data);
		system->print_hook (">");
	}
	system->print_hook (">");
}

void
_sx_error_mark (SX_SYSTEM *system, SX_VALUE *value) {
	sx_mark_value (system, value->data.error.file);
	sx_mark_value (system, value->data.error.data);
}

SX_CLASS *
sx_init_error (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("Error"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fprint = _sx_error_print;
	klass->core->fmark = _sx_error_mark;

	return klass;
}

int
sx_raise_error (SX_THREAD *thread, sx_name_id eid, char *str) {
	SX_VALUE *value;

	if (str != NULL) {
		value = sx_new_str (thread->system, str);
	} else {
		value = NULL;
	}

	sx_push_value (thread, sx_new_error (thread, eid, value));
	thread->state = SX_STATE_ERROR;
	return thread->state;
}

SX_VALUE *
sx_new_error (SX_THREAD *thread, sx_name_id id, SX_VALUE *value) {
	SX_VALUE *error;

	sx_lock_value (value);
	error = sx_malloc (thread->system, sizeof (SX_VALUE));
	sx_unlock_value (value);
	if (error == NULL) {
		return NULL;
	}

	error->klass = sx_get_class (thread->system, id);
	error->members = NULL;

	if (sx_top_class_of (thread->system, error) != thread->system->cerror) {
		sx_free (error);
		return NULL;
	}

	error->data.error.id = id;
	error->data.error.line = thread->line;
	error->data.error.file = thread->file;
	error->data.error.data = value;

	error->locks = 0;
	error->flags = 0;
	error->gc_next = NULL;

	sx_add_gc_value (thread->system, error);

	return error;
}
