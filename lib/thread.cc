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

#include <stdarg.h>

#include "scriptix.h"

using namespace Scriptix;

void
System::AddThread (Thread* thread)
{
	thread->next = threads;
	if (thread->next)
		thread->next->prev = thread;
	threads = thread;
	++ valid_threads;
}

void
System::EndThread (Thread* thread) {
	if (thread->prev == NULL) {
		threads = thread->next;
	} else {
		thread->prev->next = thread->next;
	}
	if (thread->next != NULL) {
		thread->next->prev = thread->prev;
	}
	-- valid_threads;

	delete thread;
}

Thread::Thread (System* sys, int fl) {
	static size_t _free_id = 0; // ID tag for threads

	system = sys;
	flags = fl;
	ret = NULL;
	state = STATE_READY;
	id = ++_free_id;
	next = NULL;
	prev = NULL;
}

int
Thread::PushFrame (Function* func, size_t argc, Value* argv[], int flags) {
	Array* var_args;
	Value** items;
	size_t ai; // arg index

	// argc items array (ick)
	if (func->varc != 0) {
		items = (Value**)GC_MALLOC(func->varc * sizeof(Value*));
		if (items == NULL) {
			return SXE_NOMEM;
		}
		memset (items, 0, func->varc * sizeof(Value*));
	} else {
		items = NULL;
	}

	// push new frame
	frames.resize(frames.size() + 1);
	Frame& frame = frames.back();

	frame.top = data_stack.size() >= argc ? data_stack.size() - argc : 0;
	frame.flags = flags;
	frame.argc = argc;
	frame.func = func;
	frame.items = items;

	// define variables for non-cfuncs
	if (func->cfunc == NULL && func->cmethod == NULL) {
		size_t ni = 0; // name index
		ai = 0; // start of args

		// fill func args with arg list
		while (ai < argc && ni < func->argc) {
			items[ni++] = argv[ai++];
		}

		// var arg
		if (func->varg) {
			if (argc > func->argc) {
				var_args = new Array(system, argc - func->argc, NULL);
				if (var_args != NULL) {
					// remaining frame params
					while (ai < argc) {
						var_args->Append(system, argv[ai++]);
					}

					items[ni++] = var_args;
				}
			 } else {
				 items[ni++] = new Array (system, 0, NULL);
			 }
		}
	// if this is the first frame (new thread) force data on stack - FIXME< ugly hack
	} else {
		for (size_t i = 0; i < argc; ++i)
			PushValue(argv[i]);
	}

	return SXE_OK;
}

Value*
Thread::Invoke (Function* func, size_t argc, Value* argv[]) {
	Value* retval;

	if (PushFrame(func, argc, argv, CFLAG_BREAK) != SXE_OK)
		return NULL;

	system->NestedRun(this, &retval);

	return retval;
}

void
Thread::PopFrame (void) {
	Frame& frame = frames.back();

	// GC_FREE var items
	if (frame.items != NULL)
		GC_FREE (frame.items);

	// unwind data stack 
	data_stack.resize(frame.top);

	// pop the frame
	frames.pop_back();
}

int
Thread::Exit (Value* retval) {
	// already exited?
	if (state != STATE_RUNNING && state != STATE_READY) {
		return SXE_NOTREADY;
	}

	// push return value
	PushValue(retval);

	// set state
	state = STATE_FINISHED;

	return SXE_OK;
}
