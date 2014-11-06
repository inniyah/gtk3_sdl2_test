/*
 * Scriptix - Lite-weight scripting longerface
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

#include <string.h>
#include <iostream>

#include "scriptix.h"

using namespace Scriptix;

int
System::AddFunction (Function* function)
{
	funcs[function->id] = function;
	return SXE_OK;
}

Function*
System::GetFunction (NameID id)
{
	FunctionList::iterator i = funcs.find(id);
	if (i != funcs.end())
		return i->second;
	else
		return NULL;
}

// FUNCTION IMPLEMENTATION
SX_NOMETHODS(Function)

namespace Scriptix {
	SX_TYPEIMPL(Function, "Function", Value, SX_TYPECREATENONE(Function))
}

Function::Function (NameID s_id, size_t s_argc, bool s_varg) : Value()
{
	cfunc = NULL;
	varg = s_varg;
	varc = s_argc + (s_varg ? 1 : 0);
	nodes = NULL;
	count = 0;
	size = 0;
	argc = s_argc;
	id = s_id;
	access = SEC_DEFAULTS; // just defaults
}

Function::Function (NameID s_id, size_t s_argc, bool s_varg, sx_cfunc s_cfunc) : Value()
{
	cfunc = s_cfunc;
	varg = s_varg;
	varc = s_argc + (s_varg ? 1 : 0);
	nodes = NULL;
	count = 0;
	size = 0;
	argc = s_argc;
	id = s_id;
	access = ~0; // all privs; it's a C func
}

const TypeInfo*
Function::GetType () const {
	return GetSystem()->GetFunctionType();
}

int
Function::AddValue (Value* value) {
	intptr_t* sx_new_nodes;

	/* need at least two open places */
	if (size == 0 || count >= size - 1) {
		sx_new_nodes = (intptr_t*)GC_REALLOC (nodes, sizeof (long) * (size + GetSystem()->GetBlockChunk()));
		if (sx_new_nodes == NULL)
			return SXE_NOMEM;
		nodes = sx_new_nodes;
		size += GetSystem()->GetBlockChunk();
	}
	nodes[count++] = OP_PUSH;
	nodes[count++] = (long)value;

	return SXE_OK;
}

int
Function::AddOpcode (sx_op_type value) {
	intptr_t* sx_new_nodes;

	/* need at least two open places */
	if (size == 0 || count >= size - 1) {
		sx_new_nodes = (intptr_t*)GC_REALLOC (nodes, sizeof (long) * (size + GetSystem()->GetBlockChunk()));
		if (sx_new_nodes == NULL)
			return SXE_NOMEM;
		nodes = sx_new_nodes;
		size += GetSystem()->GetBlockChunk();
	}
	nodes[count++] = value;

	return SXE_OK;
}

int
Function::AddOparg (long value) {
	intptr_t* sx_new_nodes;

	/* need at least two open places */
	if (size == 0 || count >= size - 1) {
		sx_new_nodes = (intptr_t*)GC_REALLOC (nodes, sizeof (long) * (size + GetSystem()->GetBlockChunk()));
		if (sx_new_nodes == NULL)
			return SXE_NOMEM;
		nodes = sx_new_nodes;
		size += GetSystem()->GetBlockChunk();
	}
	nodes[count++] = value;

	return SXE_OK;
}

size_t
Function::GetLineOf (size_t op_ptr) {
	// no function body?
	if (count == 0)
		return 0;

	// bounds-check
	if (op_ptr >= count)
		op_ptr = count - 1;

	// loop until we find op code's line
	DebugMetaData* d_ptr = debug;
	for (size_t c_op = d_ptr->span; op_ptr >= c_op; c_op += d_ptr->span)
		++d_ptr;
	return d_ptr->line;
}
