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

void
_sx_object_mark (SX_SYSTEM *system, SX_OBJECT *value) {
	SX_VAR *var;

	for (var = value->members; var != NULL; var = var->next) {
		sx_mark_value (system, var->value);
	}

	if (value->mark_func != NULL) {
		value->mark_func (system, value);
	}
}

void
_sx_object_del (SX_SYSTEM *system, SX_OBJECT *value) {
	SX_VAR *rnext;

	while (value->members) {
		rnext = value->members->next;
		sx_free_var (value->members);
		value->members = rnext;
	}

	if (value->del_func != NULL) {
		value->del_func (system, value);
	}
}

SX_CLASS *
sx_init_object (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("Object"), NULL);
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fmark = (sx_class_mark)_sx_object_mark;
	klass->core->fdel = (sx_class_del)_sx_object_del;

	return klass;
}

SX_OBJECT *
sx_new_object (SX_SYSTEM *system, SX_CLASS *parent) {
	SX_OBJECT *value;
	unsigned long i, c;

	if (!sx_class_is_a (system, parent, system->cobject)) {
		return NULL;
	}

	value = sx_malloc (system, sizeof (SX_OBJECT));
	sx_clear_value (system, (SX_VALUE *)value, parent);

	value->members = NULL;
	value->data = NULL;
	value->mark_func = NULL;
	value->del_func = NULL;

	if (value == NULL) {
		return NULL;
	}

	/* define members */
	while (parent != NULL) {
		c = sx_sizeof_namelist (parent->members);
		for (i = 0; i < c; ++ i) {
			sx_set_member (system, value, parent->members[i], NULL);
		}
		parent = parent->par;
	}

	return value;
}

SX_VAR *
sx_set_member (SX_SYSTEM *system, SX_OBJECT *obj, sx_name_id id, SX_VALUE *value) {
	SX_VAR *var;

	for (var = obj->members; var != NULL; var = var->next) {
		if (id == var->id) {
			var->value = value;
			return var;
		}
	}

	sx_lock_value ((SX_VALUE *)obj);
	sx_lock_value (value);

	var = (SX_VAR *)sx_malloc (system, sizeof (SX_VAR));

	sx_unlock_value (value);
	sx_unlock_value ((SX_VALUE *)obj);

	if (var == NULL) {
		return NULL;
	}

	var->id = id;
	var->value = value;
	var->next = obj->members;
	obj->members = var;

	return var;
}

SX_VALUE *
sx_get_member (SX_SYSTEM *system, SX_OBJECT *obj, sx_name_id id) {
	SX_VAR *var;

	var = sx_find_member (system, obj, id);
	if (var != NULL) {
		return var->value;
	} else {
		return sx_new_nil ();
	}
}

SX_VAR *
sx_find_member (SX_SYSTEM *system, SX_OBJECT *obj, sx_name_id id) {
	SX_VAR *var;

	if (obj == NULL || ((long)obj) & SX_NUM_MARK) {
		return NULL;
	}

	for (var = obj->members; var != NULL; var = var->next) {
		if (id == var->id) {
			return var;
		}
	}

	return NULL;
}
