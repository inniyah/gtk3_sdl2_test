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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "scriptix.h"
#include "system.h"

static
SX_VALUE
_sx_array_new (SX_SYSTEM system, SX_TYPE type)
{
	return (SX_VALUE)sx_new_array (system, 0, NULL);
}

static
void
_sx_array_print (SX_SYSTEM system, SX_ARRAY value) {
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

static
void
_sx_array_mark (SX_SYSTEM system, SX_ARRAY value) {
	unsigned long i;
	for (i = 0; i < value->count; ++ i) {
		sx_mark_value (system, value->list[i]);
	}
}

static
void
_sx_array_del (SX_SYSTEM system, SX_ARRAY value) {
	if (value->count > 0) {
		sx_free (value->list);
	}
}

static
int
_sx_array_true (SX_SYSTEM system, SX_ARRAY value) {
	return value->count > 0;
}

static
SX_VALUE 
_sx_array_get_index (SX_SYSTEM system, SX_ARRAY value, long index) {
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

static
SX_VALUE 
_sx_array_set_index (SX_SYSTEM system, SX_ARRAY array, long index, SX_VALUE value) {
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

static
SX_VALUE 
_sx_array_append (SX_SYSTEM system, SX_ARRAY array, SX_VALUE add) {
	SX_VALUE *nlist;

	if (array->count > 0) {
		nlist = (SX_VALUE *)sx_malloc ( (array->count + 1) * sizeof (SX_VALUE ));
		if (nlist == NULL) {
			return NULL;
		}
		memcpy (nlist, array->list, array->count * sizeof (SX_VALUE ));
		sx_free (array->list);
		array->list = nlist;
		array->list[array->count] = add;
		array->count += 1;
	} else {
		array->list = (SX_VALUE *)sx_malloc ( sizeof (SX_VALUE ));
		if (array->list == NULL) {
			return NULL;
		}
		array->list[0] = add;
		array->count = 1;
	}

	return (SX_VALUE )array;
}

static
int
_sx_array_is_in (SX_SYSTEM system, SX_ARRAY array, SX_VALUE value) {
	unsigned long i;
	for (i = 0; i < array->count; ++ i) {
		if (sx_are_equal (system, array->list[i], value)) {
			return 1;
		}
	}
	return 0;
}

/* methods */

static
SX_DEFINE_CFUNC(_sx_array_method_length) {
	*sx_ret = sx_new_num (((SX_ARRAY )sx_self)->count);
}

static
SX_DEFINE_CFUNC(_sx_array_method_append) {
	*sx_ret = _sx_array_append (sx_thread->system, (SX_ARRAY)sx_self, sx_argv[0]);
}

static
SX_DEFINE_CFUNC(_sx_array_method_remove) {
	unsigned long i;
	for (i = 0; i < ((SX_ARRAY)sx_self)->count; ++ i) {
		if (sx_are_equal (sx_thread->system, ((SX_ARRAY)sx_self)->list[i], sx_argv[0])) {
			memcpy (&((SX_ARRAY)sx_self)->list[i], &((SX_ARRAY)sx_self)->list[i + 1], (((SX_ARRAY)sx_self)->count - i - 1) * sizeof (SX_VALUE ));
			-- ((SX_ARRAY)sx_self)->count;
			*sx_ret = sx_new_num (1);
			return;
		}
	}
}

static
SX_DEFINE_CFUNC(_sx_array_method_foreach) {
	unsigned long i;
	SX_VALUE call = sx_argv[0];

	if (!SX_ISINVOCABLE(sx_thread->system, call)) {
		sx_raise_error (sx_thread, SXE_BADARGS, "Argument passed to Array.for_each() is not a function");
		return;
	}

	for (i = 0; i < ((SX_ARRAY)sx_self)->count; ++ i) {
		sx_invoke (sx_thread, call, 1, &((SX_ARRAY)sx_self)->list[i]);
	}
}

/* init */

SX_TYPE 
sx_init_array (SX_SYSTEM system) {
	SX_TYPE type;

	type = sx_new_type (system, "Array");
	if (type == NULL) {
		return NULL;
	}

	type->fprint = (sx_type_print)_sx_array_print;
	type->fmark = (sx_type_mark)_sx_array_mark;
	type->fdel = (sx_type_del)_sx_array_del;
	type->ftrue = (sx_type_true)_sx_array_true;
	type->fgetindex = (sx_type_get_index)_sx_array_get_index;
	type->fsetindex = (sx_type_set_index)_sx_array_set_index;
	type->fappend = (sx_type_append)_sx_array_append;
	type->fisin = (sx_type_is_in)_sx_array_is_in;
	type->fnew = (sx_type_new)_sx_array_new;

	sx_add_method (system, type, "length", 0, 0, _sx_array_method_length);
	sx_add_method (system, type, "append", 1, 0, _sx_array_method_append);
	sx_add_method (system, type, "remove", 1, 0, _sx_array_method_remove);
	sx_add_method (system, type, "foreach", 1, 0, _sx_array_method_foreach);

	return type;
}

SX_ARRAY
sx_new_array (SX_SYSTEM system, unsigned long argc, SX_VALUE *argv) {
	SX_ARRAY value = (SX_ARRAY )sx_malloc ( sizeof (struct scriptix_array));
	if (value == NULL) {
		return NULL;
	}

	value->count = argc;
	value->size = argc;
	if (argc > 0) {
		if (argv != NULL) {
			value->list = sx_dupmem ( argv, argc * sizeof (SX_ARRAY ));
			if (value->list == NULL) {
				sx_free (value);
				return NULL;
			}
		} else {
			value->list = sx_malloc ( argc * sizeof (SX_ARRAY ));
			if (value->list == NULL) {
				sx_free (value);
				return NULL;
			}
			memset (value->list, 0, argc * sizeof (SX_ARRAY ));
		}
	} else {
		value->list = NULL;
	}

	sx_clear_value (system, &value->header, system->carray);

	return value;
}

SX_ARRAY
sx_new_stack_array (SX_THREAD thread, unsigned long argc, long top) {
	long i;
	SX_ARRAY value = (SX_ARRAY )sx_malloc ( sizeof (struct scriptix_array));
	if (value == NULL) {
		return NULL;
	}

	value->count = argc;
	value->size = argc;
	if (argc > 0) {
		value->list = sx_malloc ( argc * sizeof (SX_ARRAY ));
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

	return value;
}
