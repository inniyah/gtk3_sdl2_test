/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003, 2004  AwesomePlay Productions, Inc.
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

#ifndef SCRIPTIX_FUNCTION_H
#define SCRIPTIX_FUNCTION_H

#include "scriptix/sysdep.h"

namespace Scriptix {

/**
 * Function.
 * The basis of Scriptix execution.
 * @note Cannot sub-class.
 */
class Function : public Value {
	SX_TYPEDEF

	public:
	Function (System* system);
	Function (System* system, NameID id, size_t argc, bool varg); // argc is minimum arg count
	Function (System* system, NameID id, size_t argc, bool varg, sx_cfunc func); // argc is minimum arg count
	Function (System* system, NameID id, size_t argc, bool varg, sx_cmethod method); // argc is minimum arg count

	NameID id; // name of function
	size_t argc; // number of arguments to function
	size_t varc; // number of variables in function
	intptr_t* nodes; // byte codes
	size_t count; // number of valid bytecode nodes
	size_t size; // size of nodes
	bool varg; // name of variable argument - FIXME: should be a flag or something
	sx_cfunc cfunc; // c function pointer (for cfuncs)
	sx_cmethod cmethod; // c method pointer (for cmethods)
	SecurityLevel access; // access privilegs for this function

	// Build byte-codes
	public:
	int AddValue (System* system, Value* value);
	inline int AddOpcode (System* system, sx_op_type code) { return AddOparg(system,code); } // same thing
	int AddOparg (System* system, long arg);
};

} // namespace Scriptix

#endif
