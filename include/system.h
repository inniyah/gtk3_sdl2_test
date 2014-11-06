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

#ifndef SCRIPTIX_SYSTEM_H
#define SCRIPTIX_SYSTEM_H

#include <vector>
#include <map>

namespace Scriptix {

// hook types
typedef void (*sx_gc_hook)(System* system);
typedef void (*sx_error_hook)(const char *file, unsigned int line, const char *str);

// System options
typedef enum {
	OPT_NONE = 0,
	OPT_DATACHUNK,
	OPT_BLOCKCHUNK,
	OPT_CONTEXTCHUNK,
	OPT_RUNLENGTH,
	OPT_ARRAYCHUNK,
	OPT_PATH,
} sx_option_type;

// option defaults
const int DEF_DATA_CHUNK = 50;
const int DEF_CONTEXT_CHUNK = 10;
const int DEF_BLOCK_CHUNK = 10;
const int DEF_ARRAY_CHUNK = 5;
const int DEF_RUN_LENGTH = 1000;

class System : public GC::Collectable {
	private:
	// global data
	typedef GC::map<NameID,Value*> GlobalList;
	GlobalList globals;

	// public functions
	typedef GC::map<NameID,Function*> FunctionList;
	FunctionList funcs;

	// tags feature
	typedef std::vector<NameID> TagList;
	TagList tags;

	// types
	typedef GC::map<NameID,Type*> TypeList;
	TypeList types;

	// threads/scheduler
	Thread* threads;
	Thread* cur_thread;

	// options
	size_t data_chunk;
	size_t context_chunk;
	size_t block_chunk;
	size_t gc_thresh;
	size_t array_chunk;
	std::string script_path;

	// options
	size_t valid_threads;
	size_t run_length;

	// built-in types
	const Type* t_number;
	const Type* t_string;
	const Type* t_array;
	const Type* t_assoc;
	const Type* t_function;
	const Type* t_type;
	const Type* t_list;
	const Type* t_struct;
	const Type* t_iterator;

	// helper functions
	int InitStdlib (void);

	// manager threads
	void AddThread (Thread* thread);
	void EndThread (Thread* thread);

	public:
	// Constructor/Destructor
	System (void);
	virtual ~System (void) {}

	// Hooks
	sx_error_hook error_hook;

	// Add/check types
	Type* AddType (const TypeDef* type);
	const Type* GetType (NameID id) const;
	Type* GetType (NameID id);

	inline const Type* GetNumberType (void) const { return t_number; }
	inline const Type* GetStringType (void) const { return t_string; }
	inline const Type* GetStructType (void) const { return t_struct; }
	inline const Type* GetListType (void) const { return t_list; }
	inline const Type* GetIteratorType (void) const { return t_iterator; }
	inline const Type* GetArrayType (void) const { return t_array; }
	inline const Type* GetAssocType (void) const { return t_assoc; }
	inline const Type* GetFunctionType (void) const { return t_function; }
	inline const Type* GetTypeValueType (void) const { return t_type; }

	// Query information
	inline size_t GetValidThreads (void) const { return valid_threads; }
	inline size_t GetRunLength (void) const { return run_length; }
	inline size_t GetDataChunk (void) const { return data_chunk; }
	inline size_t GetContextChunk (void) const { return context_chunk; }
	inline size_t GetBlockChunk (void) const { return block_chunk; }
	inline size_t GetArrayChunk (void) const { return array_chunk; }

	// Set options
	int SetOption (sx_option_type op, long value);
	int SetOption (sx_option_type op, const std::string& value);

	// Functions
	int AddFunction (Function* function);
	Function* GetFunction (NameID id);

	// Globals
	int AddGlobal (NameID id, Value* value);
	Value* GetGlobal (NameID id) const;

	// Threads
	Thread* CreateThread (Function* func, size_t argc, Value* array[], SecurityLevel sl = SEC_DEFAULTS, int flags = 0);

	// Running threads
	int Run (void);
	int WaitOn (ThreadID id, Value** retval);
	int NestedRun (Thread* thread, Value** retval);

	// Function tags
	int AddFunctionTag (NameID tag);
	bool ValidFunctionTag (NameID tag);
	virtual void HandleFunctionTag (NameID tag, Function* func) {} // over-ride to handle

	// Load/compile scripts
	int LoadFile (const std::string& filepath, SecurityLevel sl = SEC_DEFAULTS);
	int LoadString (const std::string& buffer, const std::string& name, size_t lineno = 1, SecurityLevel sl = SEC_DEFAULTS);

	// FIXME: hacks
	friend Value::Value (const System* system, const Type* type);
};

/**
 * Scriptix version
 * Returns version of Scriptix library.
 * @return version.
 */
const char *Version (void);

} // namespace Scriptix

#endif
