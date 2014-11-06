/*
 * Scriptix - Lite-weight scripting interface
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

#include <iostream>

#include "scriptix.h"

using namespace Scriptix;

static
Value*
StdlibPrint (Thread* thread, size_t argc, Value** argv)
{
	unsigned int i;
	for (i = 0; i < argc; i ++) {
		Value::Print (thread->GetSystem(), argv[i]);
	}
	return NULL;
}

static
Value*
StdlibPrintl (Thread* thread, size_t argc, Value** argv)
{
	StdlibPrint (thread, argc, argv);
	std::cout << "\n";
	return NULL;
}

static
Value*
StdlibGetTid (Thread* thread, size_t argc, Value** argv)
{
	return Number::Create ((long)thread >> 2);
}

static
Value*
StdlibLookup (Thread* thread, size_t argc, Value** argv)
{
	if (!Value::IsA<String>(argv[0])) {
		thread->RaiseArgError("lookup", "name", "String");
		return NULL;
	}

	return (Value*)thread->GetSystem()->GetFunction(NameToID(((String*)argv[0])->GetStr()));
}

static
Value*
StdlibFork (Thread* thread, size_t argc, Value** argv) 
{
	if (!Value::IsA<Function>(argv[0])) {
		thread->RaiseArgError("fork", "name", "Function");
		return NULL;
	}

	// FIXME: error on failure
	Thread* nthread = new Thread (thread->GetSystem(), SX_TOFUNC(argv[0]), Number::ToInt (argv[1]), 0, NULL);
	return Number::Create ((long)nthread >> 2);
}

int
System::InitStdlib (void)
{
	if (AddFunction (new Function (this, NameToID("print"), 0, 1, StdlibPrint)))
		return SXE_INTERNAL;
	if (AddFunction (new Function (this, NameToID("print"), 0, 1, StdlibPrint) ))
		return SXE_INTERNAL;
	if (AddFunction (new Function (this, NameToID("printl"), 0, 1, StdlibPrintl) ))
		return SXE_INTERNAL;
	if (AddFunction (new Function (this, NameToID("get_tid"), 0, 0, StdlibGetTid) ))
		return SXE_INTERNAL;
	if (AddFunction (new Function (this, NameToID("lookup"), 1, 0, StdlibLookup) ))
		return SXE_INTERNAL;
	if (AddFunction (new Function (this, NameToID("fork"), 2, 0, StdlibFork) ))
		return SXE_INTERNAL;

	return SXE_OK;
}
