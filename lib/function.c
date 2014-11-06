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

/* internal function stuff */
SX_VALUE *
_sx_function_new (SX_SYSTEM *system, SX_CLASS *klass) {
	return NULL;
}

void
_sx_function_mark (SX_SYSTEM *system, SX_FUNC *value) {
	if (value->cfunc == NULL) {
		sx_mark_value (system, value->args);
		sx_mark_value (system, value->body);
	} else {
		if (value->data != NULL) {
			sx_mark_value (system, value->data);
		}
	}
}

int
_sx_function_equal (SX_SYSTEM *system, SX_FUNC *one, SX_FUNC *two) {
	if (one->cfunc != NULL) {
		return one->cfunc == two->cfunc;
	} else {
		return one->args == two->args && one->body == two->body;
	}
}

SX_CLASS *
sx_init_function (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("Function"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fnew = (sx_class_new)_sx_function_new;
	klass->core->fmark = (sx_class_mark)_sx_function_mark;
	klass->core->fequal = (sx_class_equal)_sx_function_equal;

	return klass;
}

SX_VALUE *
sx_new_func (SX_SYSTEM *system, SX_VALUE *args, SX_VALUE *body) {
	SX_FUNC *value;

	if (!SX_ISBLOCK (system, body)) {
		return NULL;
	}
	if (!SX_ISNIL (system, args) && !SX_ISARRAY (system, args)) {
		return NULL;
	}
	
	value = (SX_FUNC *)sx_malloc (system, sizeof (SX_FUNC));
	if (value == NULL) {
		return NULL;
	}

	value->args = args;
	value->body = body;
	value->cfunc = NULL;

	sx_clear_value (system, &value->header, system->cfunction);

	return (SX_VALUE *)value;
}

SX_VALUE *
sx_new_cfunc (SX_SYSTEM *system, sx_cfunc func, SX_VALUE *data) {
	SX_FUNC *value;
	
	sx_lock_value (data);
	value = (SX_FUNC *)sx_malloc (system, sizeof (SX_FUNC));
	sx_unlock_value (data);
	if (value == NULL) {
		return NULL;
	}

	value->cfunc = func;
	value->body = NULL;
	value->args = NULL;
	value->data = data;

	sx_clear_value (system, &value->header, system->cfunction);

	return (SX_VALUE *)value;
}

SX_VALUE *
sx_define_cfunc (SX_SYSTEM *system, const char *name, sx_cfunc func, SX_VALUE *data) {
	SX_VALUE *cfunc = sx_new_cfunc (system, func, data);
	if (cfunc == NULL) {
		return NULL;
	}

	return sx_define_system_var (system, sx_name_to_id (name), cfunc);
}
