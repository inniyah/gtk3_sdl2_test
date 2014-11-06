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

Thread::Thread (System* sys, Invocable* called, unsigned char fl, size_t argc, Value* argv[]) {
	static size_t _free_id = 0; // ID tag for threads

	system = sys;
	flags = fl;
	call_stack = NULL;
	call_size = 0;
	call = 0;
	data_stack = NULL;
	data_size = 0;
	data = 0;
	ret = NULL;
	state = SX_STATE_READY;
	id = ++_free_id;
	next = NULL;
	prev = NULL;

	PushCall(called, argc, argv, 0);

	system->AddThread (this);
}

Thread::Thread (System* sys, Invocable* called, unsigned char flags, size_t argc, ...) {
	Value* argv[20]; // 20 sounds a good max: FIXME: make this a define somewhere
	size_t i;
	va_list va;

	if (argc > 20) {
		// FIXME: SXE_BOUNDS error
		Thread (sys, called, flags, 0, NULL);
		state = SX_STATE_FAILED;
	} else if (argc > 0) {
		va_start (va, argc);
		for (i = 0; i <= argc; ++ i) {
			argv[i] = va_arg (va, Value* );
		}
		va_end (va);

		Thread (sys, called, flags, argc, argv);
	} else {
		Thread (sys, called, flags, 0, NULL);
	}
}

Thread::~Thread (void) {
	while (call > 0) {
		PopCall();
	}

	if (data_stack != NULL) {
		free (data_stack);
	}
	if (call_stack != NULL) {
		free (call_stack);
	}
}

void
Thread::Mark (void)
{
	if (ret)
		Value::Mark (ret);

	for (size_t i = 0; i < call; ++ i) {
		Value::Mark (call_stack[i].func);
		Value::Mark (call_stack[i].file);
		for (size_t ii = 0; ii < call_stack[i].func->varc; ++ ii) {
			Value::Mark (call_stack[i].items[ii]);
		}
	}

	for (size_t i = 0; i < data; ++ i)
		Value::Mark (data_stack[i]);
}

int
Thread::PushCall (Invocable* called, size_t argc, Value* argv[], unsigned char flags) {
	Function* func;
	Array* var_args;
	Value** items;
	size_t ai; // arg index
	char closure = 0;

	// is it a closure or a func?
	if (Value::IsA<Function>(called)) {
		func = (Function*)called;
	} else {
		closure = 1;
		func = ((Closure*)called)->GetFunc();
	}

	if (func->varc != 0) {
		items = (Value**)malloc(func->varc * sizeof(Value*));
		if (items == NULL) {
			return SXE_NOMEM;
		}
		memset (items, 0, func->varc * sizeof(Value*));
	} else {
		items = NULL;
	}

	if (call == call_size) {
		Call* sx_new_stack = (Call*)realloc (call_stack, (call_size + system->GetContextChunk()) * sizeof (Call));
		if (sx_new_stack == NULL) {
			return SXE_NOMEM;
		}
		call_stack = sx_new_stack;
		call_size += system->GetContextChunk();
	}

	call_stack[call].file = NULL;
	call_stack[call].line = 1;
	call_stack[call].op_ptr = 0;
	call_stack[call].top = data >= argc ? data - argc : 0;
	call_stack[call].flags = flags;
	call_stack[call].argc = argc;
	call_stack[call].func = func;
	call_stack[call].items = items;

	++ call;

	// define variables for non-cfuncs
	if (func->cfunc == NULL) {
		size_t ni = 0; // name index
		ai = 0; // start of args

		if (closure) {
			size_t ci = 0; // closure index

			// loop to fill up non-closure args
			while (ai < func->argc && ni < func->argc - ((Closure*)called)->GetArgs()->GetCount()) {
				items[ni++] = argv[ai++];
			}

			// fill up to beginning of closure args
			while (ni < func->argc - ((Closure*)called)->GetArgs()->GetCount()) {
				items[ni++] = NULL;
			}

			// do closure values
			while (ci < ((Closure*)called)->GetArgs()->GetCount() && ni < func->argc) {
				items[ni++] = ((Closure*)called)->GetArgs()->GetIndex(ci ++);
			}
		} else {
			// fill func args with arg list
			while (ai < argc && ni < func->argc) {
				items[ni++] = argv[ai++];
			}

			// fill up arg list
			while (ni < func->argc) {
				items[ni++] = NULL;
			}
		}

		// var arg
		if (func->varg) {
			if (argc > func->argc) {
				var_args = new Array(system, argc - func->argc, NULL);
				if (var_args != NULL) {
					// remaining call params
					while (ai < argc) {
						var_args->Append(system, argv[ai++]);
					}

					items[ni++] = var_args;
				}
			 } else {
				 items[ni++] = new Array (system, 0, NULL);
			 }
		}
	}

	return SXE_OK;
}

Value*
Thread::Invoke (Invocable* called, size_t argc, Value* argv[]) {
	Value* retval;

	if (PushCall(called, argc, argv, SX_CFLAG_BREAK) != SXE_OK)
		return NULL;

	system->NestedRun(this, &retval);

	return retval;
}

Value*
Thread::Invoke (Invocable* called, size_t argc, ...)
{
	va_list va;
	Value** argv;
	Value* retval;
	size_t i;

	if (argc) {
#ifdef HAVE_ALLOCA
		argv = (Value**)alloca (argc * sizeof (Value*));
#else
		argv = (Value**)malloc (argc * sizeof (Value*));
#endif
		if (argv == NULL) {
			// FIXME: error code
			return NULL;
		}

		va_start (va, argc);
		for (i = 0; i < argc; ++ i) {
			argv[i] = va_arg (va, Value*);
		}
		va_end (va);
	} else {
		argv = NULL;
	}

	if (PushCall(called, argc, argv, SX_CFLAG_BREAK) != SXE_OK) {
#ifndef HAVE_ALLOCA
		if (argv != NULL)
			free (argv);
#endif
		return NULL;
	}

	system->NestedRun(this, &retval);

#ifndef HAVE_ALLOCA
	if (argv != NULL)
		free (argv);
#endif

	return retval;
}

void
Thread::PopCall (void) {
	if (call > 0) {
		-- call;

		// free var items
		if (call_stack[call].items)
			free (call_stack[call].items);

		// unwind stack 
		data = call_stack[call].top;

		// push return
		PushValue(ret);
	}
}
