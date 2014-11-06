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
	std::cerr << "Unhandled error: " << file << ':' << line << ": " << str << std::endl;
}

System::System (void)
{
	funcs = NULL;

	globals.resize(0);
	types.resize(0);

	tags = NULL;

	pools = NULL;

	threads = NULL;
	cur_thread = NULL;

	data_chunk = SX_DEF_DATA_CHUNK;
	context_chunk = SX_DEF_CONTEXT_CHUNK;
	block_chunk = SX_DEF_BLOCK_CHUNK;
	array_chunk = SX_DEF_ARRAY_CHUNK;
	script_path = NULL;

	error_hook = _sx_default_error_hook;

	valid_threads = 0;
	run_length = SX_DEF_RUN_LENGTH;

	AddType (String::GetType());
	AddType (Number::GetType());
	AddType (Function::GetType());
	AddType (Array::GetType());
	AddType (Assoc::GetType());
	AddType (TypeValue::GetType());
	AddType (List::GetType());
	AddType (Struct::GetType());

	// FIXME: error checking
	InitStdlib();

	// Add root to GC
	SGC::System::AddRoot (this);
}


System::~System (void)
{
	Thread* tnext;
	Tag* gnext;

	globals.resize(0);

	while (threads != NULL) {
		tnext = threads->next;
		delete threads;
		threads = tnext;
	}

	while (tags != NULL) {
		gnext = tags->next;
		if (tags->name) {
			free (tags->name);
		}
		delete tags;
		tags = gnext;
	}

	while (pools != NULL)
		PopPool ();

	types.resize(0);

	// remove root
	SGC::System::RemoveRoot(this);
}

int
System::SetOption (sx_option_type opt, long value) {
	switch (opt) {
		case SX_OPT_BLOCKCHUNK:
			block_chunk = value;
			return SXE_OK;
		case SX_OPT_DATACHUNK:
			data_chunk = value;
			return SXE_OK;
		case SX_OPT_CONTEXTCHUNK:
			context_chunk = value;
			return SXE_OK;
		case SX_OPT_RUNLENGTH:
			run_length = value;
			return SXE_OK;
		case SX_OPT_ARRAYCHUNK:
			array_chunk = value;
			return SXE_OK;
		default:
			/* unknown option */
			return SXE_INVALID;
	}
}

int
System::SetOption (sx_option_type opt, const char* value) {
	switch (opt) {
		case SX_OPT_PATH:
			if (script_path) {
				free (script_path);
				script_path = NULL;
			}
			if (value) {
				script_path = strdup(value);
				if (script_path == NULL)
					return SXE_NOMEM;
			}
			return SXE_OK;
		default:
			/* unknown option */
			return SXE_INVALID;
	}
}

void
System::Mark (void)
{
	for (std::vector<Global>::iterator i = globals.begin(); i != globals.end(); ++i)
		Value::Mark(i->value);

	for (Thread* thread = threads; thread != NULL; thread = thread->next)
		thread->Mark();

	for (Function* func = funcs; func != NULL; func = func->fnext)
		Value::Mark (func);

	for (Pool* pool = pools; pool != NULL; pool = pool->next)
		for (size_t i = 0; i < pool->argc; ++i)
			Value::Mark(pool->argv[i]);
}

int
System::PushPool (size_t argc, Value** argv)
{
	if (argc > 0 && argv == NULL)
		return SXE_INVALID;

	Pool* pool = new Pool();
	if (pool == NULL)
		return SXE_NOMEM;

	pool->next = pools;
	pools = pool;
	pool->argc = argc;
	pool->argv = argv;

	// mark everything in pool - for safety
	while (argc > 0) {
		Value::Mark(argv[argc - 1]);
		-- argc;
	}

	return SXE_OK;
}

void
System::PopPool (void)
{
	if (pools) {
		Pool* pool = pools;
		pools = pools->next;
		delete pool;
	}
}

// VERSION STRING
const char*
Scriptix::Version (void)
{
	return SX_VERSION;
}
