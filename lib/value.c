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
sx_free_value (SX_SYSTEM *system, SX_VALUE *value) {
	SX_VAR *rnext;
	SX_CLASS *klass;

	if (value == NULL || ((long)(value)) & SX_NUM_MARK) {
		return;
	}

	while (value->members) {
		rnext = value->members->next;
		sx_free_var (value->members);
		value->members = rnext;
	}

	klass = sx_top_class_of (system, value);
	if (klass && klass->core && klass->core->fdel) {
		klass->core->fdel (system, value);
	} else {
		sx_free (value);
	}
}

int
sx_is_true (SX_SYSTEM *system, SX_VALUE *value) {
	if (value == NULL) {
		return 0;
	}

	if (SX_ISNUM (system, value) && SX_TOINT (value) != 0) {
		return 1;
	}
	if (SX_ISSTRING (system, value) && value->data.str.len > 0) {
		return 1;
	}

	return 0;
}

int
sx_are_equal (SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two) {
	SX_CLASS *klass;

	if (one == two) {
		return 1;
	}

	klass = sx_top_class_of (system, one);
	if (klass != sx_top_class_of (system, two)) {
		return 0;
	}

	if (klass && klass->core && klass->core->fequal) {
		return klass->core->fequal (system, one, two);
	} else {
		return 0;
	}
}

int
sx_compare (SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two) {
	SX_CLASS *klass;

	if (one == two) {
		return 0;
	}

	if (one == NULL) {
		return 0;
	}

	if (SX_ISNUM (system, one) && SX_ISNUM (system, two)) {
		int n1 = SX_TOINT(one);
		int n2 = SX_TOINT(two);
		return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
	}

	klass = sx_top_class_of (system, one);
	if (klass != sx_top_class_of (system, two)) {
		return 0;
	}

	if (klass && klass->core && klass->core->fcompare) {
		return klass->core->fcompare (system, one, two);
	} else {
		return 0;
	}
}

SX_VALUE *
sx_get_index (SX_SYSTEM *system, SX_VALUE *cont, int index) {
	unsigned int len;

	if (SX_ISSTRING (system, cont)) {
		len = cont->data.str.len;
		if (len == 0) {
			return sx_new_str (system, NULL);
		}
		if (index < 0) {
			index += len;
			if (index < 0) {
				index = 0;
			}
		}
		if (index >= len) {
			index = len - 1;
		}
		
		return sx_new_str_len (system, cont->data.str.str + index, 1);
	} else if (SX_ISARRAY (system, cont)) {
		len = cont->data.array.count;
		if (len == 0) {
			return sx_new_nil ();
		}
		if (index < 0) {
			index += len;
			if (index < 0) {
				index = 0;
			}
		}
		if (index >= len) {
			index = len - 1;
		}
		
		return cont->data.array.list[index];
	} else {
		return sx_new_nil ();
	}
}

SX_VALUE *
sx_set_index (SX_SYSTEM *system, SX_VALUE *cont, int index, SX_VALUE *value) {
	unsigned int len;

	if (SX_ISARRAY (system, cont)) {
		len = cont->data.array.count;
		if (len == 0) {
			return sx_new_nil ();
		}
		if (index < 0) {
			index += len;
			if (index < 0) {
				index = 0;
			}
		}
		if (index >= len) {
			index = len - 1;
		}
		
		cont->data.array.list[index] = value;
		return value;
	} else {
		return NULL;
	}
}

SX_VALUE *
sx_get_section (SX_SYSTEM *system, SX_VALUE *base, int start, int end) {
	unsigned int len;
	if (SX_ISSTRING (system, base)) {
		len = base->data.str.len;
		if (len == 0) {
			return sx_new_str (system, NULL);
		}
		if (start < 0) {
			start += len;
			if (start < 0) {
				start = 0;
			}
		}
		if (start >= len) {
			start = len - 1;
		}
		if (end < 0) {
			end += len;
			if (start < 0) {
				start = 0;
			}
		}
		if (end >= len) {
			end = len - 1;
		}
		return sx_new_str_len (system, base->data.str.str + start, end - start + 1);
	} else {
		return sx_new_nil ();
	}
}

void
sx_print_value (SX_SYSTEM *system, SX_VALUE *value) {
	SX_CLASS *klass;

	if (value == NULL) {
		system->print_hook ("<nil>");
		return;
	}

	if (((long)value) & SX_NUM_MARK) {
		system->print_hook ("%li", SX_TOINT (value));
		return;
	}

	klass = sx_top_class_of (system, value);
	if (klass) {
		if (klass->core && klass->core->fprint) {
			klass->core->fprint (system, value);
		} else {
			system->print_hook ("<%s:%p>", sx_name_id_to_name (sx_class_of (system, value)->id), value);
		}
	} else {
		system->print_hook ("<unknown!:%p>", value);
	}
}

void
sx_lock_value (SX_VALUE *value) {
	if (!SX_ISNUM (system, value) && !SX_ISNIL (system, value)) {
		++ value->locks;
	}
}

void
sx_unlock_value (SX_VALUE *value) {
	if (!SX_ISNUM (system, value) && !SX_ISNIL (system, value) && value->locks > 0) {
		-- value->locks;
	}
}

void
sx_mark_value (SX_SYSTEM *system, SX_VALUE *value) {
	SX_VAR *var;
	SX_CLASS *klass;

	if (value == NULL || SX_ISNUM (system, value)) {
		return;
	}

	for (var = value->members; var != NULL; var = var->next) {
		sx_mark_value (system, var->value);
	}

	value->flags |= SX_VFLAG_MARK;

	for (klass = value->klass; klass != NULL && klass->par != NULL; klass = klass->par)
		;
	if (klass && klass->core && klass->core->fmark) {
		klass->core->fmark (system, value);
	}
}

SX_VALUE *
sx_to_num (SX_SYSTEM *system, SX_VALUE *value) {
	if (value == NULL) {
		return sx_new_num (0);
	} else if (((long)value) & SX_NUM_MARK) {
		return value;
	} else if (value->klass && value->klass->core && value->klass->core->ftonum) {
		return value->klass->core->ftonum (system, value);
	} else {
		return sx_new_num (0);
	}
}
