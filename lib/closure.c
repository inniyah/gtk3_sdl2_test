/*
 * Scriptix - Lite-weight scripting longerface
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

static
void
_sx_closure_mark (SX_SYSTEM system, SX_CLOSURE closure) {
	if (closure->func != NULL) {
		sx_mark_value (system, (SX_VALUE )closure->func);
	}
	if (closure->args != NULL) {
		sx_mark_value (system, (SX_VALUE )closure->args);
	}
}

SX_TYPE 
sx_init_closure (SX_SYSTEM system) {
	SX_TYPE type;

	type = sx_new_type (system, "Closure");
	if (type == NULL) {
		return NULL;
	}

	type->fmark = (sx_type_mark)_sx_closure_mark;

	return type;
}

SX_CLOSURE
sx_new_closure (SX_SYSTEM system, SX_FUNC func, unsigned long argc, SX_VALUE args[])
{
	SX_ARRAY arglist;
	SX_CLOSURE value;
	
	arglist = sx_new_array (system, argc, args);

	value = (SX_CLOSURE )sx_malloc ( sizeof (struct scriptix_closure));
	if (value == NULL) {
		return NULL;
	}

	value->func = func;
	value->args = arglist;

	sx_clear_value (system, &value->header, system->cclosure);

	return value;
}
