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
sx_clear_value (SX_SYSTEM system, SX_VALUE value, SX_TYPE type) {
	value->type = type;
	value->next = system->gc_list;
	system->gc_list = value;
	++system->gc_count;
}

void
sx_free_value (SX_SYSTEM system, SX_VALUE value) {
	SX_TYPE type;

	if (value == NULL || ((long)(value)) & SX_NUM_MARK) {
		return;
	}

	type = sx_type_of (system, value);
	if (type && type && type->fdel) {
		type->fdel (system, value);
		sx_free (value);
	} else {
		sx_free (value);
	}
}

int
sx_is_true (SX_SYSTEM system, SX_VALUE value) {
	SX_TYPE type;

	if (value == NULL) {
		return 0;
	}

	if (SX_ISNUM (system, value)) {
		return SX_TOINT (value) != 0;
	}

	type = sx_type_of (system, value);
	if (type && type && type->ftrue) {
		return type->ftrue (system, value);
	}

	return 1;
}

int
sx_are_equal (SX_SYSTEM system, SX_VALUE one, SX_VALUE two) {
	SX_TYPE type;

	if (one == two) {
		return 1;
	}

	if (one == NULL) {
		return 0;
	}

	type = sx_type_of (system, one);

	if (type == NULL) {
		return 0;
	}
	
	if (type != sx_type_of (system, two)) {
		return 0;
	}

	if (type && type && type->fequal) {
		return type->fequal (system, one, two);
	} else {
		return 0;
	}
}

int
sx_compare (SX_SYSTEM system, SX_VALUE one, SX_VALUE two) {
	SX_TYPE type;

	if (one == two) {
		return 0;
	}

	if (one == NULL || two == NULL) {
		return 0;
	}

	if (SX_ISNUM (system, one) && SX_ISNUM (system, two)) {
		int n1 = SX_TOINT(one);
		int n2 = SX_TOINT(two);
		return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
	}

	type = sx_type_of (system, one);

	if (type == NULL) {
		return 0;
	}
	
	if (type != sx_type_of (system, two)) {
		return 0;
	}

	if (type && type && type->fcompare) {
		return type->fcompare (system, one, two);
	} else {
		return 0;
	}
}

int
sx_is_in (SX_SYSTEM system, SX_VALUE cont, SX_VALUE value) {
	if (cont != NULL) {
		SX_TYPE type = sx_type_of (system, cont);
		if (type && type->fisin) {
			return type->fisin(system, cont, value);
		}
	}
	return 0;
}

SX_VALUE 
sx_get_index (SX_SYSTEM system, SX_VALUE cont, long index) {
	if (cont != NULL) {
		SX_TYPE type = sx_type_of (system, cont);
		if (type && type->fgetindex) {
			return type->fgetindex (system, cont, index);
		}
	}
	return NULL;
}

SX_VALUE 
sx_set_index (SX_SYSTEM system, SX_VALUE cont, long index, SX_VALUE value) {
	if (cont != NULL) {
		SX_TYPE type = sx_type_of (system, cont);
		if (type && type->fsetindex) {
			return type->fsetindex (system, cont, index, value);
		}
	}
	return NULL;
}

SX_VALUE 
sx_append (SX_SYSTEM system, SX_VALUE base, SX_VALUE add) {
	if (base != NULL) {
		SX_TYPE type = sx_type_of (system, base);
		if (type && type->fappend) {
			return type->fappend (system, base, add);
		}
	}
	return NULL;
}


void
sx_print_value (SX_SYSTEM system, SX_VALUE value) {
	SX_TYPE type;

	if (value == NULL) {
		system->print_hook ("<nil>");
		return;
	}

	if (((long)value) & SX_NUM_MARK) {
		system->print_hook ("%li", SX_TOINT (value));
		return;
	}

	type = sx_type_of (system, value);
	if (type) {
		if (type && type->fprint) {
			type->fprint (system, value);
		} else {
			system->print_hook ("<%s:%p>", sx_name_id_to_name (type->id), value);
		}
	} else {
		system->print_hook ("<unknown!:%p>", value);
	}
}

void
sx_mark_value (SX_SYSTEM system, SX_VALUE value) {
	SX_TYPE type;
	if (value == NULL || SX_ISNUM (system, value)) {
		return;
	}

	/* stuff the GC mark onto the type pointer */
	(long)value->type|= 0x01; 

	type = sx_type_of (system, value);
	if (type && type && type->fmark) {
		type->fmark (system, value);
	}
}

SX_VALUE 
sx_to_num (SX_SYSTEM system, SX_VALUE value) {
	SX_TYPE type;
	if (value == NULL) {
		return sx_new_num (0);
	} else if (((long)value) & SX_NUM_MARK) {
		return value;
	}

	type = sx_type_of (system, value);
	if (type && type && type->ftonum) {
		return type->ftonum (system, value);
	} else {
		return sx_new_num (0);
	}
}

SX_VALUE 
sx_to_str (SX_SYSTEM system, SX_VALUE value) {
	SX_TYPE type;
	if (value == NULL) {
		return sx_new_str (system, "");
	} else if (SX_ISSTRING (system, value)) {
		return value;
	}

	type = sx_type_of (system, value);
	if (type && type && type->ftostr) {
		return type->ftostr (system, value);
	} else {
		return sx_new_str (system, "");
	}
}
