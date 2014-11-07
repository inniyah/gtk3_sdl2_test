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

#ifndef SCRIPTIX_SYSTEM_H
#define SCRIPTIX_SYSTEM_H

namespace Scriptix {

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

class CompilerHandler : public GC::Collectable {
	public:
	// return false to generate a compilation error
	virtual bool HandleFunction (Function* function, bool is_public) { return true; }
	virtual bool HandleGlobal (NameID id, Value* value, bool is_public) { return true; }
	virtual bool HandleExtend (TypeInfo* type, Function* method) { return true; }
	virtual bool HandleClass (TypeInfo* type) { return true; }

	virtual ~CompilerHandler () {}
};

class System : public GC::Collectable {
	public:
	// Constructor/Destructor
	System (void);
	virtual ~System (void) {}

	// Handle an error
	virtual void HandleError (const BaseString& file, size_t lineno, const BaseString& msg);

	// Add/check types
	TypeInfo* AddType (const TypeDef* type);
	const TypeInfo* GetType (NameID id) const;
	TypeInfo* GetType (NameID id);

	inline const TypeInfo* GetNumberType (void) const { return t_number; }
	inline const TypeInfo* GetStringType (void) const { return t_string; }
	inline const TypeInfo* GetStructType (void) const { return t_struct; }
	inline const TypeInfo* GetIteratorType (void) const { return t_iterator; }
	inline const TypeInfo* GetArrayType (void) const { return t_array; }
	inline const TypeInfo* GetFunctionType (void) const { return t_function; }
	inline const TypeInfo* GetTypeValueType (void) const { return t_type; }
	inline const TypeInfo* GetScriptClassType (void) const { return t_script_class; }

	// Query information
	inline size_t GetRunLength (void) const { return run_length; }
	inline size_t GetDataChunk (void) const { return data_chunk; }
	inline size_t GetContextChunk (void) const { return context_chunk; }
	inline size_t GetBlockChunk (void) const { return block_chunk; }
	inline size_t GetArrayChunk (void) const { return array_chunk; }

	// Set options
	int SetOption (sx_option_type op, long value);
	int SetOption (sx_option_type op, const BaseString& value);

	// Functions
	int AddFunction (Function* function);
	Function* GetFunction (NameID id);

	// Globals
	int AddGlobal (NameID id, Value* value);
	Value* GetGlobal (NameID id) const;

	// Invoke a function
	int Invoke (Function* func, size_t argc, Value* argv[], Value** retval);

	// Invoke a method
	int Invoke (Value* self, NameID method, size_t argc, Value* argv[], Value** retval);

	// Raise an error condition
	int RaiseError (int err, const char *format, ...); // automatic file/line
	int RaiseArgError (const char* func, const char* arg, const char* type);
	int RaiseSecurityError (const char* func);

	// Load/compile scripts
	int LoadFile (const BaseString& filepath, SecurityLevel sl = SEC_DEFAULTS, CompilerHandler* handler = NULL);
	int LoadString (const BaseString& buffer, const BaseString& name, size_t lineno = 1, SecurityLevel sl = SEC_DEFAULTS, CompilerHandler* handler = NULL);

	private:
	// Fetch stack item from end (args) - INLINE for speed
	inline Value* GetValue (size_t index) { return data_stack[data_stack.size() - index]; }
	// Same as GetValue(1):
	inline Value* GetValue (void) { return data_stack.back(); }

	// Fetch item from frame stack for op atrgs; "eats" arg
	inline int GetOpArg (void) { return GetFrame().func->nodes[GetFrame().op_ptr++]; }

	// Manipulate data stack - INLINE for speed
	inline int
	PushValue (Value* value) {
		data_stack.push_back(value);
		return SXE_OK;
	}
	inline void PopValue (size_t len = 1) { data_stack.resize(data_stack.size() - len); }

	// Manipulate data stack
	int PushFrame (Function* func, size_t argc, Value* argv[]);
	void PopFrame (void);
	inline Frame& GetFrame (void) { return frames.back(); }
	inline const Frame& GetFrame (void) const { return frames.back(); }

	// Security level
	inline SecurityLevel GetSecurity (void) const { return GetFrame().access; }
	inline bool HasAccess (SecurityLevel access) const { return GetFrame().access & access; }

	// runtime state
	int state;

	// function frame stack
	typedef GC::vector<Frame> FrameStack;
	FrameStack frames;

	// data stack
	typedef GC::vector<Value*> DataStack;
	DataStack data_stack;

	// global data
	typedef GC::map<NameID,Value*> GlobalList;
	GlobalList globals;

	// public functions
	typedef GC::map<NameID,Function*> FunctionList;
	FunctionList funcs;

	// types
	typedef GC::map<NameID,TypeInfo*> TypeList;
	TypeList types;

	// options
	size_t data_chunk;
	size_t context_chunk;
	size_t block_chunk;
	size_t gc_thresh;
	size_t array_chunk;
	BaseString script_path;

	// options
	size_t run_length;

	// built-in types
	const TypeInfo* t_value;
	const TypeInfo* t_number;
	const TypeInfo* t_string;
	const TypeInfo* t_array;
	const TypeInfo* t_function;
	const TypeInfo* t_type;
	const TypeInfo* t_struct;
	const TypeInfo* t_iterator;
	const TypeInfo* t_script_class;
};

System* Initialize (System*);

namespace _internal {
	extern System* _System;
}

inline System* GetSystem (void) { return _internal::_System; }

} // namespace Scriptix

#endif
