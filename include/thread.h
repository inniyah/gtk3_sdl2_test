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

#ifndef SCRIPTIX_THREAD_H
#define SCRIPTIX_THREAD_H

#include <vector>

namespace Scriptix {

// id types
typedef size_t ThreadID;

// Thread flags
typedef enum {
	TFLAG_PREEMPT = (1 << 0), // pre-emptable threading
} sx_thread_flags;

// Call-stack flags
typedef enum {
	CFLAG_TTRUE = (1 << 0),
	CFLAG_BREAK = (1 << 1),
} sx_call_flags;

// Thread states
typedef enum {
	STATE_READY = 0,	// ready to run
	STATE_RUNNING,		// currentl running
	STATE_FINISHED,		// execution complete
	STATE_FAILED,		// runtime error
	STATE_RETURN,		// in return
} sx_state_type;

class Frame {
	private:
	Function* func;
	String* file;
	Value** items;
	size_t op_ptr;
	size_t top;
	size_t line;
	size_t argc;
	int flags;
	SecurityLevel access;

	public:
	Frame(void) : func(NULL), file(NULL), items(NULL), op_ptr(0), top(0), line(1), argc(0), flags(0), access(0) {}

	// Thread works on us extensively
	friend class Thread;
};

/**
 * Thread.
 * A thread contains a current execution context.
 */
class Thread : public GC::Collectable {
	public:
	// Contructor/destructor
	Thread (class System* system, SecurityLevel sl, int flags);

	// Misc
	inline ThreadID GetID(void) const { return id; }

	// Get system
	inline class System* GetSystem(void) const { return system; }

	// Raise an error condition
	int RaiseError (int err, const char *format, ...);
	int RaiseArgError (const char* func, const char* arg, const char* type);
	int RaiseSecurityError (const char* func);

	// exit thread
	int Exit (Value* retval);

	// Fetch stack item from end (args) - INLINE for speed
	inline Value* GetValue (size_t index) { return data_stack[data_stack.size() - index]; }
	// Same as GetValue(1):
	inline Value* GetValue (void) { return data_stack.back(); }

	// Fetch item from frame stack for op atrgs; "eats" arg
	inline int GetOpArg (void) { return GetFrame().func->nodes[GetFrame().op_ptr++]; }

	// Security level
	inline SecurityLevel get_security (void) const { return GetFrame().access; }
	inline bool has_access (SecurityLevel access) const { return GetFrame().access & access; }

	// Invoke a frameable
	Value* Invoke (Function* func, size_t argc, Value* array[]);

	private:
	// various stuffs
	class System* system;
	Value* ret;
	ThreadID id;
	int state;
	unsigned char flags;

	// function frame stack
	typedef GC::vector<Frame> FrameStack;
	FrameStack frames;

	// data stack
	typedef GC::vector<Value*> DataStack;
	DataStack data_stack;

	// list pointers
	Thread* prev;
	Thread* next;

	// Evaluate the thread - run it
	int Eval (void);
	int Run (void);

	// Evaluation helpers
	inline Value* InvokeCFunc (Function* cfunc, size_t argc);

	// Manipulate data stack - INLINE for speed
	inline int
	PushValue (Value* value) {
		data_stack.push_back(value);
		return SXE_OK;
	}
	inline void PopValue (size_t len = 1) { data_stack.resize(data_stack.size() - len); }

	// Manipulate data stack
	int PushFrame (Function* func, size_t argc, Value* argv[], int flags);
	int PushFrame (Value* object, NameID method, size_t argc, Value* argv[], int flags);
	void PopFrame (void);
	inline int PushFrame (Function* func, size_t argc) { return PushFrame (func, argc, &data_stack[data_stack.size() - argc], 0); }
	inline Frame& GetFrame (void) { return frames.back(); }
	inline const Frame& GetFrame (void) const { return frames.back(); }

	// System can control me
	friend class System;
};

} // namespace Scriptix

#endif
