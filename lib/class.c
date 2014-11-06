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
sx_new_class (SX_SYSTEM *system, sx_name_id id, SX_CLASS *parent) {
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
	klass->next = system->classes;
	system->classes = klass;

	return klass;
}

SX_CLASS *
sx_new_core_class (SX_SYSTEM *system, sx_name_id id) {
	SX_CLASS *klass;

	klass = sx_malloc (system, sizeof (SX_CLASS));
	if (klass == NULL) {
		return NULL;
	}

	klass->core = sx_malloc (system, sizeof (struct _scriptix_core));
	if (klass->core == NULL) {
		sx_free (klass);
		return NULL;
	}

	klass->id = id;
	klass->par = NULL;
	klass->methods = NULL;
	klass->next = system->classes;
	system->classes = klass;

	memset (klass->core, 0, sizeof (struct _scriptix_core));

	return klass;
}

void
sx_mark_class (SX_SYSTEM *system, SX_CLASS *klass) {
	SX_VAR *var;

	for (var = klass->methods; var != NULL; var = var->next) {
		sx_mark_value (system, var->value);
	}
}

void
sx_free_class (SX_CLASS *class) {
	SX_VAR *nmethod;

	if (class->par == NULL && class->core != NULL) {
		sx_free (class->core);
	}

	while (class->methods != NULL) {
		nmethod = class->methods->next;
		sx_free_var (class->methods);
		class->methods = nmethod;
	}

	sx_free (class);
}

SX_CLASS *
sx_get_class (SX_SYSTEM *system, sx_name_id id) {
	SX_CLASS *klass;

	for (klass = system->classes; klass != NULL; klass = klass->next) {
		if (klass->id == id) {
			return klass;
		}
	}

	return NULL;
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

SX_VALUE *
sx_new_object (SX_SYSTEM *system, SX_CLASS *parent) {
	SX_VALUE *value;

	if (parent && parent->core && parent->core->fnew) {
		value = parent->core->fnew (system, parent);
	} else {
		value = (SX_VALUE *)sx_malloc (system, sizeof (SX_VALUE));
		sx_clear_value (system, value, parent);
	}

	if (value == NULL) {
		return NULL;
	}

	return value;
}

SX_VALUE *
sx_set_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id, SX_VALUE *method) {
	SX_VAR *var;

	for (var = klass->methods; var != NULL; var = var->next) {
		if (var->id == id) {
			var->value = method;
			return method;
		}
	}

	sx_lock_value (method);
	var = (SX_VAR *)sx_malloc (system, sizeof (SX_VAR));
	sx_unlock_value (method);

	if (var == NULL) {
		return NULL;
	}

	var->id = id;
	var->value = method;
	var->next = klass->methods;
	klass->methods = var;

	return method;
}

SX_VALUE *
sx_get_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id) {
	SX_VAR *var;
	while (klass != NULL) {
		for (var = klass->methods; var != NULL; var = var->next) {
			if (var->id == id) {
				return var->value;
			}
		}
		klass = klass->par;
	}

	return NULL;
}

int
sx_value_is_a (SX_SYSTEM *system, SX_VALUE *value, SX_CLASS *par) {
	SX_CLASS *klass;

	for (klass = sx_class_of (system, value); klass != NULL; klass = klass->next) {
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

SX_VAR *
sx_set_member (SX_SYSTEM *system, SX_VALUE *klass, sx_name_id id, SX_VALUE *value) {
	SX_VAR *var;

	if (klass == NULL || ((long)klass) & SX_NUM_MARK) {
		return NULL;
	}

	for (var = klass->members; var != NULL; var = var->next) {
		if (id == var->id) {
			var->value = value;
			return var;
		}
	}

	sx_lock_value (klass);
	sx_lock_value (value);

	var = (SX_VAR *)sx_malloc (system, sizeof (SX_VAR));

	sx_unlock_value (klass);
	sx_unlock_value (value);

	if (var == NULL) {
		return NULL;
	}

	var->id = id;
	var->value = value;
	var->next = klass->members;
	klass->members = var;

	return var;
}

SX_VALUE *
sx_get_member (SX_SYSTEM *system, SX_VALUE *klass, sx_name_id id) {
	SX_VAR *var;

	var = sx_find_member (system, klass, id);
	if (var != NULL) {
		return var->value;
	} else {
		return sx_new_nil ();
	}
}

SX_VAR *
sx_find_member (SX_SYSTEM *system, SX_VALUE *klass, sx_name_id id) {
	SX_VAR *var;

	if (klass == NULL || ((long)klass) & SX_NUM_MARK) {
		return NULL;
	}

	for (var = klass->members; var != NULL; var = var->next) {
		if (id == var->id) {
			return var;
		}
	}

	return NULL;
}
