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

SX_TYPE 
sx_init_object (SX_SYSTEM system) {
	SX_TYPE type;

	type = sx_new_type (system, "Object");
	if (type == NULL) {
		return NULL;
	}

	return type;
}

SX_TYPE 
sx_new_object_type (SX_SYSTEM system, const char *name, SX_TYPE parent) {
	SX_TYPE type;

	type = sx_malloc (sizeof (struct scriptix_type));
	if (type == NULL) {
		sx_free (type);
		return NULL;
	}
	memset (type, 0, sizeof (struct scriptix_type));

	type->id = sx_name_to_id (name);
	type->refs = 1;
	if (parent) {
		type->parent = parent;
	} else {
		type->parent = system->cobject;
	}
	type->next = system->types;
	system->types = type;

	return type;
}

SX_OBJECT 
sx_new_object (SX_SYSTEM system, SX_TYPE parent, void *data) {
	SX_OBJECT value;

	if (!sx_type_is_a (system, parent, system->cobject)) {
		return NULL;
	}

	value = sx_malloc (sizeof (struct scriptix_object));
	sx_clear_value (system, (SX_VALUE )value, parent);

	value->data = data;

	return value;
}
