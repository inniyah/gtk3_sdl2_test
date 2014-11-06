/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003, 2004, 2005  AwesomePlay Productions, Inc.
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

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "scriptix.h"
#include "system.h"

using namespace Scriptix;

static
const char *sx_error_names[] =
{
	"OK",
	"Out of memory",
	"Invalid type",
	"Undefined",
	"Nil call",
	"Invalid operator",
	"Out of bounds",
	"Not ready",
	"Invalid request",
	"Disabled",
	"Busy",
	"Internal error",
	"Incorrect arguments",
	"Already exists",
	"Divide by zero",
	NULL
};

int
System::RaiseError (int err, const char *format, ...) {
	char buf[256]; /* big enough */
	va_list va;

	va_start (va, format);
	vsnprintf (buf, sizeof(buf), format, va);
	va_end (va);
	if (!frames.empty())
		HandleError (GetFrame().GetFile() ? GetFrame().GetFile()->GetCStr(): "n/a", GetFrame().GetLine(), buf);
	else
		HandleError ("n/a", 0, buf);

	PushValue(Number::Create(err));
	state = STATE_FAILED;
	return state;
}

int
System::RaiseArgError (const char* func, const char* arg, const char* type)
{
	return RaiseError(SXE_BADARGS, "Argument '%s' to '%s' is not a '%s'", arg, func, type);
}

int
System::RaiseSecurityError (const char* func)
{
	return RaiseError(SXE_BADARGS, "System does not have security access for '%s'", func);
}

const char *
Scriptix::StrError (sx_err_type err)
{
	/* out of bounds */
	if (err < 0 || (size_t)err >= sizeof(sx_error_names)/sizeof(sx_error_names[0]))
		return NULL;

	/* return name */
	return sx_error_names[err];
}
