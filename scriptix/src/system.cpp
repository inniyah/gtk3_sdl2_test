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

#include <iostream>

#include "scriptix.h"
#include "config.h"

using namespace Scriptix;

namespace Scriptix {
	extern const TypeDef String_Type;
	extern const TypeDef Number_Type;
	extern const TypeDef Iterator_Type;
	extern const TypeDef Function_Type;
	extern const TypeDef Array_Type;
	extern const TypeDef TypeValue_Type;
}

System::System (void) : globals(), funcs(), types(), script_path()
{
	data_chunk = DEF_DATA_CHUNK;
	context_chunk = DEF_CONTEXT_CHUNK;
	block_chunk = DEF_BLOCK_CHUNK;
	array_chunk = DEF_ARRAY_CHUNK;

	run_length = DEF_RUN_LENGTH;

	t_value = AddType(&Value_Type);
	t_string = AddType(&String_Type);
	t_number = AddType(&Number_Type);
	t_function = AddType(&Function_Type);
	t_iterator = AddType(&Iterator_Type);
	t_array = AddType(&Array_Type);
	t_type = AddType(&TypeValue_Type);
	t_struct = AddType(&Scriptix::Struct_Type);
	t_script_class = AddType(&Scriptix::ScriptClass_Type);
}

void
System::HandleError (const BaseString& file, size_t line, const BaseString& msg) {
	std::cerr << "Scriptix: " << file << ':' << line << ": " << msg << std::endl;
}

int
System::SetOption (sx_option_type opt, long value) {
	switch (opt) {
		case OPT_BLOCKCHUNK:
			block_chunk = value;
			return SXE_OK;
		case OPT_DATACHUNK:
			data_chunk = value;
			return SXE_OK;
		case OPT_CONTEXTCHUNK:
			context_chunk = value;
			return SXE_OK;
		case OPT_RUNLENGTH:
			run_length = value;
			return SXE_OK;
		case OPT_ARRAYCHUNK:
			array_chunk = value;
			return SXE_OK;
		default:
			/* unknown option */
			return SXE_INVALID;
	}
}

int
System::SetOption (sx_option_type opt, const BaseString& value) {
	switch (opt) {
		case OPT_PATH:
			script_path = value;
			return SXE_OK;
		default:
			/* unknown option */
			return SXE_INVALID;
	}
}

// VERSION STRING
const char*
Scriptix::Version (void)
{
	return SX_VERSION;
}

// NON-THREAD-LOCAL SYSTEM OBJECT 
namespace Scriptix {
	namespace _internal {
		System* _System = NULL;
	}
}

// INITIALIZE SCRIPTIX
System*
Scriptix::Initialize (System* s_system)
{
	// delete current system
	delete _internal::_System;
	// use default if necessary
	if (s_system == NULL)
		s_system = new System();
	// set as system
	_internal::_System = s_system;

	return _internal::_System;
}
