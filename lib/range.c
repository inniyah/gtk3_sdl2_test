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
#include <string.h>
#include <stdlib.h>

#include "scriptix.h"
#include "system.h"

SX_VALUE *
_sx_range_new (SX_SYSTEM *system, SX_CLASS *klass) {
	SX_RANGE *value;

	value = (SX_RANGE *)sx_malloc (system, sizeof (SX_RANGE));
	if (value == NULL) {
		return NULL;
	}

	value->start = 0;
	value->end = 0;

	sx_clear_value (system, &value->header, system->crange);

	return (SX_VALUE *)value;
}

void
_sx_range_print (SX_SYSTEM *system, SX_RANGE *value) {
	system->print_hook ("(%d..%d)", value->start, value->end);
}

int
_sx_range_equal (SX_SYSTEM *system, SX_RANGE *one, SX_RANGE *two) {
	return one->start == two->start && one->end == two->end;
}

int
_sx_range_compare (SX_SYSTEM *system, SX_RANGE *one, SX_RANGE *two) {
	int n1 = one->end - one->start;
	int n2 = two->end - two->start;
	n1 = n1 < 0 ? -n1 : n1;
	n2 = n2 < 0 ? -n2 : n2;
	return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
}

SX_CLASS *
sx_init_range (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("Range"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fnew = (sx_class_new)_sx_range_new;
	klass->core->fprint = (sx_class_print)_sx_range_print;
	klass->core->fequal = (sx_class_equal)_sx_range_equal;
	klass->core->fcompare = (sx_class_compare)_sx_range_compare;

	return klass;
}

SX_VALUE *
sx_new_range (SX_SYSTEM *system, int start, int end) {
	SX_RANGE *value;

	value = (SX_RANGE *)sx_malloc (system, sizeof (SX_RANGE));
	if (value == NULL) {
		return NULL;
	}

	value->start = start;
	value->end = end;

	sx_clear_value (system, &value->header, system->crange);

	return (SX_VALUE *)value;
}
