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
#include <stdio.h>

#include "scriptix.h"

/* helper functions */
SX_VALUE *
_sx_error_new (SX_SYSTEM *system, SX_CLASS *klass) {
	SX_ERROR *error;

	error = sx_malloc (system, sizeof (SX_ERROR));
	if (error == NULL) {
		return NULL;
	}

	error->file = sx_new_str (system, "<unknown>");
	error->line = 0;
	error->data = NULL;

	sx_clear_value (system, &error->header, klass);

	return (SX_VALUE *)error;
}

void
_sx_error_print (SX_SYSTEM *system, SX_ERROR *value) {
	system->print_hook ("<Exception %s# %s:%d", sx_name_id_to_name (sx_class_of (system, (SX_VALUE *)value)->id), SX_TOSTRING (value->file)->str, value->line);
	if (!SX_ISNIL (system, value->data)) {
		system->print_hook (" <");
		sx_print_value (system, value->data);
		system->print_hook (">");
	}
	system->print_hook (">");
}

void
_sx_error_mark (SX_SYSTEM *system, SX_ERROR *value) {
	sx_mark_value (system, value->file);
	sx_mark_value (system, value->data);
}

SX_VALUE *
_sx_error_tostr (SX_SYSTEM *system, SX_ERROR *value) {
	char buffer[512];

	snprintf (buffer, 512, "<Exception %s# %s:%d%s%s%s>",
			sx_name_id_to_name (sx_class_of (system, (SX_VALUE *)value)->id),
			SX_TOSTRING (value->file)->str,
			value->line,
			value->data ? " <" : "",
			value->data ? SX_TOSTRING (sx_to_str (system, value->data))->str : "", 
			value->data ? ">" : "");

	return sx_new_str (system, buffer);
}

SX_CLASS *
sx_init_error (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("Error"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fnew = (sx_class_new)_sx_error_new;
	klass->core->fprint = (sx_class_print)_sx_error_print;
	klass->core->fmark = (sx_class_mark)_sx_error_mark;
	klass->core->ftostr = (sx_class_to_str)_sx_error_tostr;

	return klass;
}

int
sx_raise_error (SX_THREAD *thread, sx_name_id eid, const char *str) {
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
	SX_ERROR *error;
	SX_CLASS *klass;

	klass = sx_get_class (thread->system, id);
	if (!sx_class_is_a (thread->system, klass, thread->system->cerror)) {
		return NULL;
	}

	sx_lock_value (value);
	error = sx_malloc (thread->system, sizeof (SX_ERROR));
	sx_unlock_value (value);
	if (error == NULL) {
		return NULL;
	}

	error->line = thread->line;
	error->file = thread->file;
	error->data = value;

	sx_clear_value (thread->system, &error->header, klass);

	return (SX_VALUE *)error;
}
