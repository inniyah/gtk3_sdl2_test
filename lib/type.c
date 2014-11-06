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
sx_new_type (SX_SYSTEM system, const char *name) {
	SX_TYPE type;

	type = sx_malloc (sizeof (struct scriptix_type));
	if (type == NULL) {
		sx_free (type);
		return NULL;
	}
	memset (type, 0, sizeof (struct scriptix_type));

	type->id = sx_name_to_id (name);
	type->refs = 1;
	type->parent = NULL;
	type->next = system->types;
	system->types = type;

	return type;
}

SX_METHOD 
sx_get_method (SX_SYSTEM system, SX_TYPE type, sx_name_id id) {
	SX_METHOD method;

	while (type != NULL) {
		for (method = type->methods; method != NULL; method = method->next) {
			if (method->id == id) {
				return method;
			}
		}
		type = type->parent;
	}

	return NULL;
}

SX_METHOD 
sx_add_method (SX_SYSTEM system, SX_TYPE type, const char *name, unsigned long argc, int varg, sx_cfunc method_func) {
	SX_METHOD method;

	if (type == NULL || method_func == NULL || name == NULL) {
		return NULL;
	}

	method = sx_malloc (sizeof (struct scriptix_method));
	if (method == NULL) {
		return NULL;
	}

	method->id = sx_name_to_id (name);
	method->argc = argc;
	method->varg = varg;
	method->method = method_func;

	method->next = type->methods;
	type->methods = method;

	return method;
}

SX_METHOD 
sx_get_static_method (SX_SYSTEM system, SX_TYPE type, sx_name_id id) {
	SX_METHOD method;

	while (type != NULL) {
		for (method = type->static_methods; method != NULL; method = method->next) {
			if (method->id == id) {
				return method;
			}
		}
		type = type->parent;
	}

	return NULL;
}

SX_METHOD 
sx_add_static_method (SX_SYSTEM system, SX_TYPE type, const char *name, unsigned long argc, int varg, sx_cfunc method_func) {
	SX_METHOD method;

	if (type == NULL || method_func == NULL || name == NULL) {
		return NULL;
	}

	method = sx_malloc (sizeof (struct scriptix_method));
	if (method == NULL) {
		return NULL;
	}

	method->id = sx_name_to_id (name);
	method->argc = argc;
	method->varg = varg;
	method->method = method_func;

	method->next = type->static_methods;
	type->static_methods = method;

	return method;
}

SX_TYPE 
sx_type_is_a (SX_SYSTEM system, SX_TYPE base, SX_TYPE par) {
	while (base != NULL) {
		if (base == par)
			return base;
		base = base->parent;
	}

	return NULL;
}

SX_VALUE 
sx_value_is_a (SX_SYSTEM system, SX_VALUE base, SX_TYPE par) {
	return sx_type_is_a (system, base->type, par) ? base : NULL;
}

SX_TYPE 
sx_get_type (SX_SYSTEM system, sx_name_id id) {
	SX_TYPE type;

	for (type = system->types; type != NULL; type = type->next) {
		if (type->id == id) {
			return type;
		}
	}

	return NULL;
}
