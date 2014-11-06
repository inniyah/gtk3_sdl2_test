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

SX_CLASS *
sx_new_class (SX_SYSTEM *system, sx_name_id id, sx_name_id *members, SX_CLASS *parent) {
	SX_CLASS *klass;

	klass = sx_malloc (system, sizeof (SX_CLASS));
	if (klass == NULL) {
		return NULL;
	}

	klass->id = id;
	klass->par = parent;
	if (parent != NULL) {
		klass->core = parent->core;
	} else {
		klass->core = NULL;
	}
	klass->methods = NULL;
	klass->static_methods = NULL;
	klass->members = members;
	klass->refs = 1;
	klass->next = NULL;

	return klass;
}

SX_CLASS *
sx_new_core_class (SX_SYSTEM *system, sx_name_id id, sx_name_id *members) {
	SX_CLASS *klass;

	klass = sx_new_class (system, id, members, NULL);

	klass->core = sx_malloc (system, sizeof (struct _scriptix_core));
	if (klass->core == NULL) {
		sx_free (klass);
		return NULL;
	}

	memset (klass->core, 0, sizeof (struct _scriptix_core));

	sx_add_class (system->core, klass);

	return klass;
}

unsigned long
sx_ref_class (SX_CLASS *klass) {
	return ++ klass->refs;
}

unsigned long
sx_unref_class (SX_CLASS *klass) {
	if ((-- klass->refs) == 0) {
		sx_free_class (klass);
		return 0;
	} else {
		return klass->refs;
	}
}

void
sx_mark_class (SX_SYSTEM *system, SX_CLASS *klass) {
	SX_FUNC *func;

	for (func = klass->methods; func != NULL; func = func->next) {
		sx_mark_func (system, func);
	}
	
	for (func = klass->static_methods; func != NULL; func = func->next) {
		sx_mark_func (system, func);
	}
}

void
sx_free_class (SX_CLASS *class) {
	SX_FUNC *nmethod;

	if (class->par == NULL && class->core != NULL) {
		sx_free (class->core);
	}

	while (class->methods != NULL) {
		nmethod = class->methods->next;
		sx_unref_func (class->methods);
		class->methods = nmethod;
	}

	while (class->static_methods != NULL) {
		nmethod = class->static_methods->next;
		sx_unref_func (class->static_methods);
		class->static_methods = nmethod;
	}

	if (class->members) {
		sx_free_namelist (class->members);
	}

	sx_free (class);
}

SX_CLASS *
sx_top_class_of (SX_SYSTEM *system, SX_VALUE *value) {
	SX_CLASS *klass;

	if (value == NULL) {
		return NULL;
	}

	if (((long)value) & SX_NUM_MARK) {
		return system->cfixnum;
	}

	for (klass = value->klass; klass != NULL && klass->par != NULL; klass = klass->par)
		;

	return klass;
}

SX_FUNC *
sx_get_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id) {
	SX_FUNC *method;
	while (klass != NULL) {
		for (method = klass->methods; method != NULL; method = method->next) {
			if (method->id == id) {
				return method;
			}
		}
		klass = klass->par;
	}

	return NULL;
}

SX_FUNC *
sx_add_method (SX_SYSTEM *system, SX_CLASS *klass, SX_FUNC *func) {
	if (klass == NULL || func == NULL) {
		return NULL;
	}

	sx_ref_func (func);
	func->next = klass->methods;
	klass->methods = func;

	return func;
}

SX_FUNC *
sx_get_static_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id) {
	SX_FUNC *method;
	while (klass != NULL) {
		for (method = klass->static_methods; method != NULL; method = method->next) {
			if (method->id == id) {
				return method;
			}
		}
		klass = klass->par;
	}

	return NULL;
}

SX_FUNC *
sx_add_static_method (SX_SYSTEM *system, SX_CLASS *klass, SX_FUNC *func) {
	if (klass == NULL || func == NULL) {
		return NULL;
	}

	sx_ref_func (func);
	func->next = klass->static_methods;
	klass->static_methods = func;

	return func;
}

int
sx_value_is_a (SX_SYSTEM *system, SX_VALUE *value, SX_CLASS *par) {
	SX_CLASS *klass;

	for (klass = sx_class_of (system, value); klass != NULL; klass = klass->par) {
		if (klass == par) {
			return 1;
		}
	}
	return 0;
}

int
sx_class_is_a (SX_SYSTEM *system, SX_CLASS *klass, SX_CLASS *par) {
	while (klass != NULL) {
		if (klass == par) {
			return 1;
		}
		klass = klass->par;
	}
	return 0;
}
