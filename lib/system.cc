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
#include "config.h"

using namespace Scriptix;

static
void
_sx_default_error_hook (const char *file, unsigned int line, const char *str) {
	std::cerr << "Scriptix: " << file << ':' << line << ": " << str << std::endl;
}

System::System (void) : globals(), funcs(), tags(), types(), script_path()
{
	threads = NULL;
	cur_thread = NULL;

	data_chunk = DEF_DATA_CHUNK;
	context_chunk = DEF_CONTEXT_CHUNK;
	block_chunk = DEF_BLOCK_CHUNK;
	array_chunk = DEF_ARRAY_CHUNK;

	error_hook = _sx_default_error_hook;

	valid_threads = 0;
	run_length = DEF_RUN_LENGTH;

	t_string = AddType (String::GetTypeDef());
	t_number = AddType (Number::GetTypeDef());
	t_function = AddType (Function::GetTypeDef());
	t_iterator = AddType (Iterator::GetTypeDef());
	t_list = AddType (List::GetTypeDef());
	t_array = AddType (Array::GetTypeDef());
	t_assoc = AddType (Assoc::GetTypeDef());
	t_type = AddType (TypeValue::GetTypeDef());
	t_struct = AddType (Struct::GetTypeDef());

	// FIXME: error checking
	InitStdlib();
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
System::SetOption (sx_option_type opt, const std::string& value) {
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

Thread*
System::CreateThread (Function* function, size_t argc, Value* argv[], SecurityLevel sl, int flags)
{
	Thread* thread = new Thread(this, sl, flags);
	if (thread == NULL) {
		// SXE_NOMEM
		return NULL;
	}

	if (thread->PushFrame(function, argc, argv, 0) != SXE_OK) {
		delete thread;
		return NULL;
	}

	AddThread(thread);
	return thread;
}
