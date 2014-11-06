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

/* klass helper funcs */
void
_sx_str_print (SX_SYSTEM *system, SX_VALUE *str) {
	if (str->data.str.str != NULL) {
		system->print_hook ("%s", str->data.str.str);
	}
}

SX_VALUE *
_sx_str_to_num (SX_SYSTEM *system, SX_VALUE *str) {
	if (str->data.str.str != NULL) {
		return sx_new_num (atoi (str->data.str.str));
	} else {
		return sx_new_num (0);
	}
}

int
_sx_str_equal (SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two) {
	if (one->data.str.len != two->data.str.len) {
		return 0;
	}
	if (one->data.str.len == 0) {
		return 1;
	}
	return !strcmp (one->data.str.str, two->data.str.str);
}

int
_sx_str_compare (SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two) {
	if (one->data.str.len < two->data.str.len) {
		return -1;
	} else if (one->data.str.len > two->data.str.len) {
		return 1;
	}
	if (one->data.str.len == 0) {
		return 0;
	}
	return strcmp (one->data.str.str, two->data.str.str);
}

SX_CLASS *
sx_init_string (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("String"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fprint = _sx_str_print;
	klass->core->ftonum = _sx_str_to_num;
	klass->core->fequal = _sx_str_equal;
	klass->core->fcompare = _sx_str_compare;

	return klass;
}

SX_VALUE *
sx_new_str (SX_SYSTEM *system, char *str) {
	SX_VALUE *value;
	unsigned int len;
	
	if (str == NULL) {
		len = 0;
		value = (SX_VALUE *)sx_malloc (system, sizeof (SX_VALUE));
	} else {
		len = strlen (str);
		value = (SX_VALUE *)sx_malloc (system, sizeof (SX_VALUE) + (len + 1) * sizeof (char));
	}
	
	if (value == NULL) {
		return NULL;
	}

	value->klass = system->cstring;
	value->members = NULL;
	if (str == NULL) {
		value->data.str.len = 0;
	} else {
		value->data.str.len = strlen (str);
		strcpy (value->data.str.str, str);
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}

SX_VALUE *
sx_new_str_len (SX_SYSTEM *system, char *str, unsigned int len) {
	SX_VALUE *value;
	
	value = (SX_VALUE *)sx_malloc (system, sizeof (SX_VALUE) + (len + 1) * sizeof (char));
	if (value == NULL) {
		return NULL;
	}

	value->data.str.len = len;

	value->klass = system->cstring;
	value->members = NULL;
	if (str != NULL) {
		strncpy (value->data.str.str, str, len);
		SX_TOSTR(system,value)[len] = '\0';
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}
