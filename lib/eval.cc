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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// AIX requires this to be the first thing in the file. 
#ifndef __GNUC__
# if HAVE_ALLOCA_H
#  include <alloca.h>
# else
#  ifdef _AIX
	#pragma alloca // indentation intentional
#  else
#   ifndef alloca // predefined by HP cc +Olibcalls
char *alloca ();
#   endif
#  endif
# endif
#endif


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "scriptix.h"

using namespace Scriptix;

Value*
Thread::InvokeMethod (Value* self, const Method* method, size_t argc)
{
	Value** argv;
	Value* ret;
	size_t i;
	size_t count;

	// find largest of argc/func->argc
	if (argc > method->argc)
		count = argc;
	else
		count = method->argc;

	// allocate argv
	argv = NULL;
	if (count) {
#if defined(HAVE_ALLOCA)
		argv = (Value**)alloca (count * sizeof (Value*));
#else
		argv = (Value**)malloc (count * sizeof (Value*));
#endif
		if (argv == NULL) {
			// FIXME: SXE_NOMEM error
			return NULL;
		}
		memset (argv, 0, count * sizeof(Value*));

		// copy args
		for (i = argc; i > 0; --i) // FIXME: make faster
			argv[argc - i] = GetValue(i);
	}

	// invoke
	ret = method->method (this, self, count, argv);

	if (argv != NULL) {
#if !defined(HAVE_ALLOCA)
		// free array
		free (argv);
#endif
	}

	return ret;
}

Value*
Thread::InvokeCFunc (Function* cfunc, size_t argc)
{
	Value** argv;
	Value* ret;
	size_t i;
	size_t count;

	// find largest of argc/func->argc
	if (argc > cfunc->argc)
		count = argc;
	else
		count = cfunc->argc;

	// allocate argv
	argv = NULL;
	if (count) {
#if defined(HAVE_ALLOCA)
		argv = (Value**)alloca (count * sizeof (Value*));
#else
		argv = (Value**)malloc (count * sizeof (Value*));
#endif
		if (argv == NULL) {
			// FIXME: SXE_NOMEM error
			return NULL;
		}
		memset (argv, 0, count * sizeof(Value*));

		// copy args
		for (i = argc; i > 0; --i) // FIXME: make faster
			argv[argc - i] = GetValue(i);
	}

	// invoke
	ret = cfunc->cfunc (this, count, argv);

	if (argv != NULL) {
#if !defined(HAVE_ALLOCA)
		// free array
		free (argv);
#endif
	}

	return ret;
}

int
Thread::Eval (void) {
	unsigned long count;
	unsigned long op_count = system->GetRunLength();
	unsigned long index;
	int op;
	Value* ret;
	Value* value;
	Call* curcall;
	const Type* type;
	const Method* method;
	sx_name_id name;

	while (call > 0) {
run_code:
		curcall = &call_stack[call - 1];

		// time to run the gc?
		if (SGC::System::NeedGC())
			SGC::System::Collect();

		// working on a C function
		if (curcall->func->cfunc) {
			count = data;

			Thread::ret = curcall->func->cfunc (this, curcall->argc, &data_stack[curcall->top]);
			PopCall();
			continue;
		}

		while (curcall->op_ptr < curcall->func->count && state == SX_STATE_RUNNING) {
			// store op for faster access
			op = curcall->func->nodes[curcall->op_ptr];

			// push value - quicker than rest of loop
			if (op == SX_OP_PUSH) {
				PushValue((Value*)curcall->func->nodes[curcall->op_ptr + 1]);
				curcall->op_ptr += 2;
				continue;
			}

			// next op
			++ curcall->op_ptr;

			switch (op) {
				case SX_OP_ADD:
					ret = Number::Create (Number::ToInt (GetValue(2)) + Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_SUBTRACT:
					ret = Number::Create (Number::ToInt (GetValue(2)) - Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_MULTIPLY:
					ret = Number::Create (Number::ToInt (GetValue(2)) * Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_DIVIDE:
					ret = Number::Create (Number::ToInt (GetValue(2)) / Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_NEGATE:
					ret = Number::Create (- Number::ToInt (GetValue(1)));
					PopValue(1);
					PushValue(ret);
					break;
				case SX_OP_CALL:
					count = Number::ToInt (GetValue(2));
					value = GetValue(1);
					PopValue(2);

					if (!Value::IsA<Invocable>(value)) {
						PopValue(count);
						RaiseError(SXE_BADTYPE, "Invoked data is not a function");
						break;
					}

					if (Value::IsA<Function>(value) && SX_TOFUNC(value)->cfunc != NULL) {
						ret = InvokeCFunc(SX_TOFUNC(value), count);
						PopValue(count);
						PushValue(ret);
						break;
					}

					PushCall(SX_TOINVOCABLE(value), count);
					goto run_code; // jump to executation stage
					break;
				case SX_OP_GT:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) > 0);
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_LT:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) < 0);
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_GTE:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) >= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_LTE:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) <= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_EQUAL:
					ret = Number::Create (Value::Equal (system, GetValue(2), GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_NEQUAL:
					ret = Number::Create (!Value::Equal (system, GetValue(2), GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case SX_OP_NOT:
					ret = Number::Create (!Value::True (system, GetValue(1)));
					PopValue(1);
					PushValue(ret);
					break;
				case SX_OP_LOOKUP:
					index = Number::ToInt(GetValue(1));
					if (index < 0 || index >= curcall->func->varc) {
						RaiseError(SXE_BOUNDS, "Variable index out of allowable range (%lu/%lu)", index, curcall->func->varc);
					} else {
						PopValue(1);
						PushValue(curcall->items[index]);
					}
					break;
				case SX_OP_ASSIGN:
					ret = GetValue(1);
					index = Number::ToInt(GetValue(2));
					if (index < 0 || index >= curcall->func->varc) {
						RaiseError(SXE_BOUNDS, "Variable index out of allowable range (%lu/%lu)", index, curcall->func->varc);
					} else {
						curcall->items[index] = ret;
						PopValue(2); // FIXME: optimize, shouldn't pop the value then push back on
						PushValue(ret);
					}
					break;
				case SX_OP_INDEX:
					value = GetValue(2);
					if (Value::IsA<List>(value)) {
						ret = ((List*)value)->GetIndex (system, GetValue(1));
						PopValue(2);
						PushValue(ret);
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Instance is not a list type in index operation");
					}
					break;
				case SX_OP_PREINCREMENT:
					ret = NULL;
					index = Number::ToInt(GetValue(2));
					if (index < 0 || index >= curcall->func->varc) {
						RaiseError(SXE_BOUNDS, "Variable index out of allowable range (%lu/%lu)", index, curcall->func->varc);
					} else {
						ret = curcall->items[index] = Number::Create (Number::ToInt (curcall->items[index]) + Number::ToInt (GetValue(1)));
						PopValue(2);
						PushValue(ret);
					}
					break;
				case SX_OP_POSTINCREMENT:
					ret = NULL;
					index = Number::ToInt(GetValue(2));
					if (index < 0 || index >= curcall->func->varc) {
						PopValue(2);
						RaiseError(SXE_BOUNDS, "Variable index out of allowable range (%lu/%lu)", index, curcall->func->varc);
					} else {
						ret = curcall->items[index];
						curcall->items[index] = Number::Create (Number::ToInt (curcall->items[index]) + Number::ToInt (GetValue(1)));
						PopValue(2);
						PushValue(ret);
					}
					break;
				case SX_OP_NEWARRAY:
					count = Number::ToInt (GetValue(1));
					PopValue(1);
					if (count > 0) {
						ret = new Array(system, count, &data_stack[data - count]);
					} else {
						ret = new Array(system);
					}
					PopValue(count);
					PushValue(ret);
					break;
				case SX_OP_NEWASSOC:
					count = Number::ToInt (GetValue(1));
					PopValue(1);
					if (count > 0) {
						ret = new Assoc (system, count, &data_stack[data - (count*2)]);
					} else {
						ret = new Assoc (system);
					}
					PopValue(count * 2);
					PushValue (ret);
					break;
				case SX_OP_SETINDEX:
					value = GetValue(3);
					if (Value::IsA<List>(value)) {
						ret = ((List*)value)->SetIndex (system, GetValue(2), GetValue(1));
						PopValue(3);
						PushValue(ret);
					} else {
						PopValue(3);
						RaiseError(SXE_BADTYPE, "Instance is not a list type in set index operation");
					}
					break;
				case SX_OP_TYPECAST:
					// get type
					value = GetValue(1);
					type = SX_TOTYPE(value)->GetTypePtr();

					// get value
					value = GetValue(2);
					if (Value::IsA (value, type)) {
						// pop type
						PopValue(1);
					} else {
						// push NULL/false value
						PopValue(2);
						PushValue(NULL);
					}
					break;
				case SX_OP_METHOD:
					count = Number::ToInt (GetValue(3));
					value = GetValue(2); // the type
					name = Number::ToInt (GetValue(1));
					PopValue(3);

					if (value == NULL) {
						RaiseError(SXE_NILCALL, "Value is nil for method call");
						break;
					}
					method = Value::GetMethod(value, name);
					if (method == NULL) {
						PopValue(count);
						type = Value::TypeOf(value);
						RaiseError(SXE_UNDEFINED, "Method '%s' on type '%s' does not exist", IDToName (name), type->name);
						break;
					}
					if (count < method->argc) {
						PopValue(count);
						type = Value::TypeOf(value);
						RaiseError(SXE_UNDEFINED, "Too few arguments to method '%s' on type '%s' (%d or %d)", IDToName (name), type->name, count, (long)method->argc);
						break;
					}
					ret = InvokeMethod (value, method, count);
					PopValue(count);
					PushValue(ret);
					break;
				case SX_OP_STATIC_METHOD:
					count = Number::ToInt (GetValue(3));
					value = GetValue(2); // the type
					name = Number::ToInt (GetValue(1));
					PopValue(3);

					if (!Value::IsA<TypeValue>(value)) {
						RaiseError(SXE_NILCALL, "Value is not a type for method call");
						break;
					}
					type = SX_TOTYPE(value)->GetTypePtr();
					method = type->GetStaticMethod(name);
					if (method == NULL) {
						PopValue(count);
						RaiseError(SXE_UNDEFINED, "Static method '%s' on type '%s' does not exist", IDToName (name), type->name);
						break;
					}
					if (count < method->argc) {
						PopValue(count);
						RaiseError(SXE_UNDEFINED, "Too few arguments to static method '%s' on type '%s' (%d or %d)", IDToName (name), type->name, count, (long)method->argc);
						break;
					}
					ret = InvokeMethod(NULL, method, count);
					PopValue(count);
					PushValue(ret);
					break;
				case SX_OP_SETFILELINE:
					value = GetValue(2);
					if (Value::IsA<String>(value)) {
						curcall->file = (String*)value;
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Tried to set filename to a non-string");
						break;
					}
					value = GetValue(1);
					if (Value::IsA<Number>(value)) {
						curcall->line = Number::ToInt (value);
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Tried to set file line to a non-number");
						break;
					}
					PopValue(2);
					break;
				case SX_OP_NEXTLINE:
					++ curcall->line;
					break;
				case SX_OP_POP:
					PopValue(1);
					break;
				case SX_OP_JUMP:
					curcall->op_ptr = Number::ToInt (GetValue(1));
					PopValue(1);
					break;
				case SX_OP_TEST:
					if (Value::True (system, GetValue(1)))
						curcall->flags |= SX_CFLAG_TTRUE;
					else
						curcall->flags &= ~SX_CFLAG_TTRUE;
					break;
				case SX_OP_TJUMP:
					if (curcall->flags & SX_CFLAG_TTRUE) {
						curcall->op_ptr = Number::ToInt (GetValue(1));
					}
					PopValue(1);
					break;
				case SX_OP_FJUMP:
					if ((curcall->flags & SX_CFLAG_TTRUE) == 0) {
						curcall->op_ptr = Number::ToInt (GetValue(1));
					}
					PopValue(1);
					break;
				case SX_OP_YIELD:
					// break - switch
					return state;
					break;
				case SX_OP_IN:
					value = GetValue(2);
					if (Value::IsA<List>(value)) {
						if (((List*)value)->Has (system, GetValue(1))) {
							PopValue(2);
							PushValue(Number::Create(1));
						} else {
							PopValue(2);
							PushValue(NULL);
						}
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Instance is not a list type in has operation");
					}
					break;
				case SX_OP_CLOSURE:
					count = Number::ToInt (GetValue(2));
					value = GetValue(1);
					PopValue(2);
					if (Value::IsA<Function>(value)) {
						Array* argv = new Array(system, count, &data_stack[data - count]);
						PopValue(count);
						PushValue(new Closure (system, (Function*)value, argv));
					} else {
						PopValue(count);
						RaiseError(SXE_BADTYPE, "Closure value is not a function");
					}
					break;
				case SX_OP_GET_MEMBER:
					value = GetValue(2);
					name = Number::ToInt(GetValue(1));
					PopValue(2);
					if (Value::IsA<Struct>(value)) {
						ret = ((Struct*)value)->GetMember(system, name);
						PushValue(ret);
					} else {
						RaiseError(SXE_BADTYPE, "Attempt to get member value on non-structure");
					}
					break;
				case SX_OP_SET_MEMBER:
					value = GetValue(3);
					name = Number::ToInt(GetValue(2));
					if (Value::IsA<Struct>(value)) {
						((Struct*)value)->SetMember(system, name, GetValue(1));
						PopValue(3);
						PushValue(value);
					} else {
						PopValue(3);
						RaiseError(SXE_BADTYPE, "Attempt to get member value on non-structure");
					}
					break;
			}

			// exit out of function on thread switch
			if ((flags & SX_TFLAG_PREEMPT) && (state == SX_STATE_RUNNING)) {
				if (-- op_count == 0) {
					// berak - switch
					return state;
				}
			}
		}

		// reset state ; if we should break, return as well
		Thread::ret = GetValue(1);
		PopCall();
		if (curcall->flags & SX_CFLAG_BREAK) {
			if (state != SX_STATE_FAILED)
				state = SX_STATE_RETURN;
			return state;
		}
	}

	// we finished
	state = SX_STATE_FINISHED;

	return state;
}

int
Thread::Run (void) {
	if (state != SX_STATE_READY) {
		return SXE_NOTREADY;
	}

	state = SX_STATE_RUNNING;
	Eval();
	if (state == SX_STATE_RUNNING)
		state = SX_STATE_READY;

	if (data > 0 && state == SX_STATE_FAILED) {
		// return error code
		return Number::ToInt(ret);
	}

	// got here, we're OK
	return SXE_OK;
}
