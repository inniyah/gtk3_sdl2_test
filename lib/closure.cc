/*
 * Scriptix - Lite-weight scripting longerface
 * Copyright (c) 2002, 2003  AwesomePlay Productions, Inc.
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

using namespace Scriptix;

SX_TYPEIMPL(Closure, "Closure", Invocable)

SX_NOMETHODS(Closure)

SX_NOSMETHODS(Closure)

void
Closure::MarkChildren (void) {
	if (func != NULL)
		Value::Mark (func);
	if (args != NULL)
		Value::Mark (args);
}

#if 0

Type* 
sx_init_closure (System* system) {
	Type* type;

	type = sx_new_type (system, "Closure");
	if (type == NULL) {
		return NULL;
	}

	type->fmark = (sx_type_mark)_sx_closure_mark;

	return type;
}

Value*
sx_new_closure (System* system, Value* func, size_t argc, Value* args[])
{
	Value* arglist;
	Closure* value;

	if (!Value::IsA<Function>(func)) {
		/* FIXME: ERROR: TYPE */
		return SX_NIL;
	}
	
	arglist = sx_new_array (system, argc, args);

	value = (Closure* )malloc ( sizeof (Closure));
	if (value == NULL) {
		/* FIXME: ERROR: MEM */
		return SX_NIL;
	}

	value->func = SX_TOFUNC(func);
	value->args = SX_TOARRAY(arglist);

	sx_clear_value (system, value, system->ClosureType());

	return SX_TOVALUE(value);
}

#endif
