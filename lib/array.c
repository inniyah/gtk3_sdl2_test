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

void
_sx_array_print (SX_SYSTEM *system, SX_ARRAY *value) {
	unsigned long i;
	if (value->count > 0) {
		system->print_hook ("[");
		sx_print_value (system, value->list[0]);
		for (i = 1; i < value->count; i ++) {
			system->print_hook (",");
			sx_print_value (system, value->list[i]);
		}
		system->print_hook ("]");
	} else {
		system->print_hook ("[]");
	}
}

void
_sx_array_mark (SX_SYSTEM *system, SX_ARRAY *value) {
	unsigned long i;
	for (i = 0; i < value->count; ++ i) {
		sx_mark_value (system, value->list[i]);
	}
}

void
_sx_array_del (SX_SYSTEM *system, SX_ARRAY *value) {
	if (value->count > 0) {
		sx_free (value->list);
	}
	sx_free (value);
}

int
_sx_array_true (SX_SYSTEM *system, SX_ARRAY *value) {
	return value->count > 0;
}

SX_VALUE *
_sx_array_get_index (SX_SYSTEM *system, SX_ARRAY *value, long index) {
	if (value->count == 0) {
		return sx_new_nil ();
	}
	if (index < 0) {
		index += value->count;
		if (index < 0) {
			index = 0;
		}
	}
	if (index >= value->count) {
		index = value->count - 1;
	}
	
	return value->list[index];
}

SX_VALUE *
_sx_array_set_index (SX_SYSTEM *system, SX_ARRAY *array, long index, SX_VALUE *value) {
	if (array->count == 0) {
		return sx_new_nil ();
	}
	if (index < 0) {
		index += array->count;
		if (index < 0) {
			index = 0;
		}
	}
	if (index >= array->count) {
		index = array->count - 1;
	}
	
	return array->list[index] = value;
}

SX_VALUE *
_sx_array_append (SX_SYSTEM *system, SX_ARRAY *array, SX_VALUE *add) {
	SX_VALUE **nlist;

	if (array->count > 0) {
		sx_lock_value ((SX_VALUE *)array);
		sx_lock_value (add);
		nlist = (SX_VALUE **)sx_malloc (system, (array->count + 1) * sizeof (SX_VALUE *));
		sx_unlock_value (add);
		sx_unlock_value ((SX_VALUE *)array);
		if (nlist == NULL) {
			return NULL;
		}
		memcpy (nlist, array->list, array->count * sizeof (SX_VALUE *));
		sx_free (array->list);
		array->list = nlist;
		array->list[array->count] = add;
		array->count += 1;
	} else {
		sx_lock_value ((SX_VALUE *)array);
		sx_lock_value (add);
		array->list = (SX_VALUE **)sx_malloc (system, sizeof (SX_VALUE *));
		sx_unlock_value (add);
		sx_unlock_value ((SX_VALUE *)array);
		if (array->list == NULL) {
			return NULL;
		}
		array->list[0] = add;
		array->count = 1;
	}

	return (SX_VALUE *)array;
}

/* methods */

SX_DEFINE_CFUNC(_sx_array_length) {
	sx_push_value (sx_thread, sx_new_num (((SX_ARRAY *)sx_self)->count));
}

SX_CLASS *
sx_init_array (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("array"), NULL);
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fprint = (sx_class_print)_sx_array_print;
	klass->core->fmark = (sx_class_mark)_sx_array_mark;
	klass->core->fdel = (sx_class_del)_sx_array_del;
	klass->core->ftrue = (sx_class_true)_sx_array_true;
	klass->core->fgetindex = (sx_class_get_index)_sx_array_get_index;
	klass->core->fsetindex = (sx_class_set_index)_sx_array_set_index;
	klass->core->fappend = (sx_class_append)_sx_array_append;

	sx_add_method (system, klass, sx_new_cfunc (system, sx_name_to_id ("length"), 0, 0, _sx_array_length));

	return klass;
}

SX_VALUE *
sx_new_array (SX_SYSTEM *system, unsigned long argc, SX_VALUE **argv) {
	SX_ARRAY *value = (SX_ARRAY *)sx_malloc (system, sizeof (SX_ARRAY));
	if (value == NULL) {
		return NULL;
	}

	value->count = argc;
	value->size = argc;
	if (argc > 0) {
		if (argv != NULL) {
			value->list = sx_dupmem (system, argv, argc * sizeof (SX_ARRAY *));
			if (value->list == NULL) {
				sx_free (value);
				return NULL;
			}
		} else {
			value->list = sx_malloc (system, argc * sizeof (SX_ARRAY *));
			if (value->list == NULL) {
				sx_free (value);
				return NULL;
			}
			memset (value->list, 0, argc * sizeof (SX_ARRAY *));
		}
	} else {
		value->list = NULL;
	}

	sx_clear_value (system, &value->header, system->carray);

	return (SX_VALUE *)value;
}

SX_VALUE *
sx_new_stack_array (SX_THREAD *thread, unsigned long argc, long top) {
	long i;
	SX_ARRAY *value = (SX_ARRAY *)sx_malloc (thread->system, sizeof (SX_ARRAY));
	if (value == NULL) {
		return NULL;
	}

	value->count = argc;
	value->size = argc;
	if (argc > 0) {
		value->list = sx_malloc (thread->system, argc * sizeof (SX_ARRAY *));
		if (value->list == NULL) {
			sx_free (value);
			return NULL;
		}

		for (i = 0; i < argc; i ++) {
			value->list[i] = sx_get_value (thread, top + i);
		}
	} else {
		value->list = NULL;
	}

	sx_clear_value (thread->system, &value->header, thread->system->carray);

	return (SX_VALUE *)value;
}
