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
#include <ctype.h>

#include "scriptix.h"
#include "system.h"

static
void
_sx_str_print (SX_SYSTEM system, SX_STRING str) {
	if (str->len > 0) {
		system->print_hook ("%.*s", str->len, str->str);
	}
}

static
SX_VALUE 
_sx_str_to_num (SX_SYSTEM system, SX_STRING str) {
	if (str->len > 0) {
		return sx_new_num (atoi (str->str));
	} else {
		return sx_new_num (0);
	}
}

static
int
_sx_str_equal (SX_SYSTEM system, SX_STRING one, SX_STRING two) {
	if (one->len != two->len) {
		return 0;
	}
	if (one->len == 0) {
		return 1;
	}
	return !memcmp (one->str, two->str, one->len * sizeof (char));
}

static
int
_sx_str_compare (SX_SYSTEM system, SX_STRING one, SX_STRING two) {
	if (one->len < two->len) {
		return -1;
	} else if (one->len > two->len) {
		return 1;
	}
	if (one->len == 0) {
		return 0;
	}
	return memcmp (one->str, two->str, one->len * sizeof (char));
}

static
int
_sx_str_true (SX_SYSTEM system, SX_STRING value) {
	return value->len > 0;
}

static
int
_sx_str_is_in (SX_SYSTEM system, SX_STRING string, SX_VALUE value) {
	const char *c;

	if (!SX_ISSTRING (system, value))
		return 0;

	/* blank test - always in */
	if (!SX_TOSTRING(value)->len)
		return 1;
	/* longer - can't be in */
	if (SX_TOSTRING(value)->len > string->len)
		return 0;

	/* scan and check */
	for (c = string->str; *c != '\0'; ++ c) {
		if (!strncasecmp (c, SX_TOSTRING(value)->str, SX_TOSTRING(value)->len))
			return 1;
	}

	return 0;
}

static
SX_VALUE 
_sx_str_get_index (SX_SYSTEM system, SX_STRING value, long index) {
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

/* methods */
static
SX_DEFINE_CFUNC(_sx_str_length) {
	*sx_ret = sx_new_num (SX_TOSTRING (sx_self)->len);
}

static
SX_DEFINE_CFUNC(_sx_str_smethod_concat) {
	unsigned long len, i;

	/* calc length */
	len = 0;
	for (i = 0; i < sx_argc; ++ i) {
		if (SX_ISSTRING (sx_thread->system, sx_argv[i])) {
			len += SX_TOSTRING(sx_argv[i])->len;
		}
	}

	/* allocate string */
	*sx_ret = sx_new_str_len (sx_thread->system, NULL, len);
	if (*sx_ret == NULL) {
		sx_raise_error (sx_thread, "Out of memory");
		return;
	}

	/* copy into */
	len = 0; /* pointer to index */
	for (i = 0; i < sx_argc; ++ i) {
		if (SX_ISSTRING (sx_thread->system, sx_argv[i])) {
			memcpy (SX_TOSTRING(*sx_ret)->str + len, SX_TOSTRING(sx_argv[i])->str, SX_TOSTRING(sx_argv[i])->len * sizeof (char));
			len += SX_TOSTRING(sx_argv[i])->len;
		}
	}

	/* finish */
	SX_TOSTRING(*sx_ret)->str[SX_TOSTRING(*sx_ret)->len] = '\0';
}

static
SX_DEFINE_CFUNC(_sx_str_method_to_num) {
	*sx_ret = _sx_str_to_num (sx_thread->system, (SX_STRING )sx_self);
}

static
SX_DEFINE_CFUNC(_sx_str_method_split) {
	SX_VALUE array;
	const char *c, *needle, *haystack;
	int nlen;

	if (!SX_ISSTRING(sx_thread->system, sx_argv[0])) {
		sx_raise_error (sx_thread, "Argument 1 to String::split() is not a string");
		return;
	}

	haystack = SX_TOSTRING(sx_self)->str;
	needle = SX_TOSTRING(sx_argv[0])->str;
	nlen = strlen (needle);

	array = sx_new_array (sx_thread->system, 0, NULL);
	if (array == NULL) {
		sx_raise_error (sx_thread, "Out of memory");
		return;
	}
	*sx_ret = array;

	/* no needle */
	if (nlen == 0) {
		sx_append (sx_thread->system, array, sx_self);
		return;
	}

	/* find substr */
	for (c = haystack; *c != '\0'; ++ c) {
		if (!strncasecmp (c, needle, strlen (needle))) {
			sx_append (sx_thread->system, array, sx_new_str_len (sx_thread->system, haystack, c - haystack));
			haystack = c + nlen;
		}
	}

	/* append last */
	if (*haystack != '\0') {
		sx_append (sx_thread->system, array, sx_new_str_len (sx_thread->system, haystack, strlen(haystack)));
	}
}

static
SX_DEFINE_CFUNC(_sx_str_method_tolower) {
	unsigned int i;
	*sx_ret = sx_new_str_len (sx_thread->system, SX_TOSTRING(sx_self)->str, SX_TOSTRING(sx_self)->len);
	for (i = 0; i < SX_TOSTRING(sx_self)->len; ++ i) {
		SX_TOSTRING(sx_self)->str[i] = tolower (SX_TOSTRING(sx_self)->str[i]);
	}

}

static
SX_DEFINE_CFUNC(_sx_str_method_toupper) {
	unsigned int i;
	*sx_ret = sx_new_str_len (sx_thread->system, SX_TOSTRING(sx_self)->str, SX_TOSTRING(sx_self)->len);
	for (i = 0; i < SX_TOSTRING(sx_self)->len; ++ i) {
		SX_TOSTRING(sx_self)->str[i] = toupper (SX_TOSTRING(sx_self)->str[i]);
	}

}

/* INIT */

SX_TYPE 
sx_init_string (SX_SYSTEM system) {
	SX_TYPE type;

	type = sx_new_type (system, "String");
	if (type == NULL) {
		return NULL;
	}

	type->fprint = (sx_type_print)_sx_str_print;
	type->ftonum = (sx_type_to_num)_sx_str_to_num;
	type->fequal = (sx_type_equal)_sx_str_equal;
	type->fcompare = (sx_type_compare)_sx_str_compare;
	type->ftrue = (sx_type_true)_sx_str_true;
	type->fgetindex = (sx_type_get_index)_sx_str_get_index;
	type->fisin = (sx_type_is_in)_sx_str_is_in;

	sx_add_method (system, type, "length", 0, 0, _sx_str_length);
	sx_add_method (system, type, "to_num", 0, 0, _sx_str_method_to_num);
	sx_add_method (system, type, "split", 1, 0, _sx_str_method_split);
	sx_add_method (system, type, "tolower", 0, 0, _sx_str_method_tolower);
	sx_add_method (system, type, "toupper", 0, 0, _sx_str_method_toupper);

	sx_add_static_method (system, type, "concat", 2, 1, _sx_str_smethod_concat);

	return type;
}

SX_VALUE 
sx_new_str (SX_SYSTEM system, const char *str) {
	SX_STRING value;
	unsigned long len;
	
	if (str == NULL) {
		len = 0;
		value = (SX_STRING )sx_malloc (sizeof (struct scriptix_string));
	} else {
		len = strlen (str);
		value = (SX_STRING )sx_malloc (sizeof (struct scriptix_string) + (len + 1) * sizeof (char));
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

	return (SX_VALUE )value;
}

SX_VALUE 
sx_new_str_len (SX_SYSTEM system, const char *str, unsigned long len) {
	SX_STRING value;
	
	value = (SX_STRING )sx_malloc (sizeof (struct scriptix_string) + (len + 1) * sizeof (char));
	if (value == NULL) {
		return NULL;
	}

	value->len = len;

	sx_clear_value (system, &value->header, system->cstring);

	if (str != NULL) {
		memcpy (value->str, str, len * sizeof (char));
		value->str[len] = '\0';
	}

	return (SX_VALUE )value;
}
