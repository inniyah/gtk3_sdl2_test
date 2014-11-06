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
SX_VALUE *
_sx_str_new (SX_SYSTEM *system, SX_CLASS *klass) {
	SX_STRING *value;
	
	value = (SX_STRING *)sx_malloc (system, sizeof (SX_STRING));
	if (value == NULL) {
		return NULL;
	}

	sx_clear_value (system, &value->header, klass);

	value->len = 0;

	return (SX_VALUE*)value;
}

void
_sx_str_print (SX_SYSTEM *system, SX_STRING *str) {
	if (str->len > 0) {
		system->print_hook ("%s", str->str);
	}
}

SX_VALUE *
_sx_str_to_num (SX_SYSTEM *system, SX_STRING *str) {
	if (str->len > 0) {
		return sx_new_num (atoi (str->str));
	} else {
		return sx_new_num (0);
	}
}

int
_sx_str_equal (SX_SYSTEM *system, SX_STRING *one, SX_STRING *two) {
	if (one->len != two->len) {
		return 0;
	}
	if (one->len == 0) {
		return 1;
	}
	return !strcmp (one->str, two->str);
}

int
_sx_str_compare (SX_SYSTEM *system, SX_STRING *one, SX_STRING *two) {
	if (one->len < two->len) {
		return -1;
	} else if (one->len > two->len) {
		return 1;
	}
	if (one->len == 0) {
		return 0;
	}
	return strcmp (one->str, two->str);
}

int
_sx_str_true (SX_SYSTEM *system, SX_STRING *value) {
	return value->len > 0;
}

SX_VALUE *
_sx_str_get_index (SX_SYSTEM *system, SX_STRING *value, int index) {
	if (value->len == 0) {
		return sx_new_str (system, NULL);
	}
	if (index < 0) {
		index += value->len;
		if (index < 0) {
			index = 0;
		}
	}
	if (index >= value->len) {
		index = value->len - 1;
	}
	
	return sx_new_str_len (system, value->str + index, 1);
}

SX_VALUE *
_sx_str_get_section (SX_SYSTEM *system, SX_STRING *string, int start, int end) {
	if (string->len == 0) {
		return sx_new_str (system, NULL);
	}
	if (start < 0) {
		start += string->len;
		if (start < 0) {
			start = 0;
		}
	}
	if (start >= string->len) {
		start = string->len - 1;
	}
	if (end < 0) {
		end += string->len;
		if (start < 0) {
			start = 0;
		}
	}
	if (end >= string->len) {
		end = string->len - 1;
	}
	return sx_new_str_len (system, string->str + start, end - start + 1);
}

SX_CLASS *
sx_init_string (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("String"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fnew = (sx_class_new)_sx_str_new;
	klass->core->fprint = (sx_class_print)_sx_str_print;
	klass->core->ftonum = (sx_class_to_num)_sx_str_to_num;
	klass->core->fequal = (sx_class_equal)_sx_str_equal;
	klass->core->fcompare = (sx_class_compare)_sx_str_compare;
	klass->core->ftrue = (sx_class_true)_sx_str_true;
	klass->core->fgetindex = (sx_class_get_index)_sx_str_get_index;
	klass->core->fgetsection = (sx_class_get_section)_sx_str_get_section;

	return klass;
}

SX_VALUE *
sx_new_str (SX_SYSTEM *system, const char *str) {
	SX_STRING *value;
	unsigned int len;
	
	if (str == NULL) {
		len = 0;
		value = (SX_STRING *)sx_malloc (system, sizeof (SX_STRING));
	} else {
		len = strlen (str);
		value = (SX_STRING *)sx_malloc (system, sizeof (SX_STRING) + (len + 1) * sizeof (char));
	}
	
	if (value == NULL) {
		return NULL;
	}

	sx_clear_value (system, &value->header, system->cstring);

	if (str == NULL) {
		value->len = 0;
	} else {
		value->len = strlen (str);
		strcpy (value->str, str);
	}

	return (SX_VALUE*)value;
}

SX_VALUE *
sx_new_str_len (SX_SYSTEM *system, const char *str, unsigned int len) {
	SX_STRING *value;
	
	value = (SX_STRING *)sx_malloc (system, sizeof (SX_STRING) + (len + 1) * sizeof (char));
	if (value == NULL) {
		return NULL;
	}

	value->len = len;

	sx_clear_value (system, &value->header, system->cstring);

	if (str != NULL) {
		strncpy (value->str, str, len);
		value->str[len] = '\0';
	}

	return (SX_VALUE *)value;
}
