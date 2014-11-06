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

#include <string.h>
#include <iostream>

#include "scriptix.h"

using namespace Scriptix;

int
System::AddFunction (Function* function)
{
	function->fnext = funcs;
	funcs = function;
	Value::Mark(function);
	return SXE_OK;
}

Function*
System::GetFunction (NameID id)
{
	Function* function = funcs;
	while (function != NULL) {
		if (function->id == id)
			return function;
		function = function->fnext;
	}
	return NULL;
}

// FUNCTION IMPLEMENTATION
SX_TYPEIMPL(Function, "Function", Value)
SX_NOMETHODS(Function)
SX_NOSMETHODS(Function)

Function::Function (System* system, NameID s_id, size_t s_argc, bool s_varg) : Value(system, system->GetFunctionType())
{
	cfunc = NULL;
	varg = s_varg;
	varc = 0;
	nodes = NULL;
	count = 0;
	size = 0;
	argc = s_argc;
	id = s_id;
	fnext = NULL;
}

Function::Function (System* system, NameID s_id, size_t s_argc, bool s_varg, sx_cfunc s_cfunc) : Value(system, system->GetFunctionType())
{
	cfunc = s_cfunc;
	varg = s_varg;
	varc = 0;
	nodes = NULL;
	count = 0;
	size = 0;
	argc = s_argc;
	id = s_id;
	fnext = NULL;
}

Function::~Function (void)
{
	if (nodes != NULL)
		free (nodes);
}

void
Function::MarkChildren (void)
{
	for (size_t i = 0; i < count; ++ i) {
		if (nodes[i] == OP_PUSH)  // data
			Value::Mark ((Value*)nodes[i + 1]);
		i += OpCodeDefs[nodes[i]].args; // skip args
	}
}

int
Function::AddValue (System* system, Value* value) {
	long* sx_new_nodes;

	/* need at least two open places */
	if (size == 0 || count >= size - 1) {
		sx_new_nodes = (long*)realloc (nodes, sizeof (long) * (size + system->GetBlockChunk()));
		if (sx_new_nodes == NULL)
			return SXE_NOMEM;
		nodes = sx_new_nodes;
		size += system->GetBlockChunk();
	}
	nodes[count++] = OP_PUSH;
	nodes[count++] = (long)value;

	return SXE_OK;
}

int
Function::AddOparg (System* system, long value) {
	long* sx_new_nodes;

	/* need at least two open places */
	if (size == 0 || count >= size - 1) {
		sx_new_nodes = (long*)realloc (nodes, sizeof (long) * (size + system->GetBlockChunk()));
		if (sx_new_nodes == NULL)
			return SXE_NOMEM;
		nodes = sx_new_nodes;
		size += system->GetBlockChunk();
	}
	nodes[count++] = value;

	return SXE_OK;
}
