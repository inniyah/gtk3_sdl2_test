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

OpCode Scriptix::OpCodeDefs[] = {
	{ "PUSH", 1 },
	{ "ADD", 0 },
	{ "SUBTRACT", 0 },
	{ "MULTIPLY", 0 },
	{ "DIVIDE", 0 },
	{ "NEGATE", 0 },
	{ "INVOKE", 1 },
	{ "GT", 0 },
	{ "LT", 0 },
	{ "GTE", 0 },
	{ "LTE", 0 },
	{ "EQUAL", 0 },
	{ "NEQUAL", 0 },
	{ "NOT", 0 },
	{ "LOOKUP", 1 },
	{ "ASSIGN", 1 },
	{ "INDEX", 0 },
	{ "PREINCREMENT", 0 },
	{ "POSTINCREMENT", 0 },
	{ "NEWARRAY", 1 },
	{ "TYPECAST", 0 },
	{ "STRINGCAST", 0 },
	{ "INTCAST", 0 },
	{ "SETINDEX", 0 },
	{ "METHOD", 2 },
	{ "SETFILELINE", 0 },
	{ "NEXTLINE", 0 },
	{ "JUMP", 1 },
	{ "POP", 0 },
	{ "TEST", 0 },
	{ "TJUMP", 1 },
	{ "FJUMP", 1 },
	{ "STATIC_METHOD", 2 },
	{ "YIELD", 0 },
	{ "IN", 0 },
	{ "SET_MEMBER", 1 },
	{ "GET_MEMBER", 1 },
	{ "ITER", 1 },
	{ "CONCAT", 0 },
};

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

#if !defined(HAVE_ALLOCA)
	if (argv != NULL) {
		// free array
		free (argv);
	}
#endif

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

#if !defined(HAVE_ALLOCA)
	if (argv != NULL) {
		// free array
		free (argv);
	}
#endif

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
	Value* value2;
	Call* curcall;
	const Type* type;
	const Method* method;
	NameID name;

	while (call > 0) {
run_code:
		curcall = &call_stack[call - 1];

		// time to run the gc?
		if (SGC::System::NeedGC())
			SGC::System::Collect();

		// working on a C function
		if (curcall->func->cfunc) {
			ret = InvokeCFunc (curcall->func, curcall->argc);
			PopCall();
			PushValue(ret);
			continue;
		}

		while (curcall->op_ptr < curcall->func->count && state == STATE_RUNNING) {
			// store op for faster access
			op = curcall->func->nodes[curcall->op_ptr];

			// push value - quicker than rest of loop
			if (op == OP_PUSH) {
				PushValue((Value*)curcall->func->nodes[curcall->op_ptr + 1]);
				curcall->op_ptr += 2;
				continue;
			}

			// next op
			++ curcall->op_ptr;

			// DEBUG
			// std::cout << op << '\t' << OpCodeDefs[op].name << std::endl;

			switch (op) {
				case OP_ADD:
					ret = Number::Create (Number::ToInt (GetValue(2)) + Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_SUBTRACT:
					ret = Number::Create (Number::ToInt (GetValue(2)) - Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_MULTIPLY:
					ret = Number::Create (Number::ToInt (GetValue(2)) * Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_DIVIDE:
					// divide by 0 check
					if (Number::ToInt(GetValue(1)) == 0) {
						PopValue(2);
						RaiseError(SXE_DIVZERO, "Division by zero");
					} else {
						ret = Number::Create (Number::ToInt (GetValue(2)) / Number::ToInt (GetValue(1)));
						PopValue(2);
						PushValue(ret);
					}
					break;
				case OP_NEGATE:
					ret = Number::Create (- Number::ToInt (GetValue(1)));
					PopValue(1);
					PushValue(ret);
					break;
				case OP_INVOKE:
					count = curcall->func->nodes[curcall->op_ptr++];
					value = GetValue(1);
					PopValue(1);

					if (!Value::IsA<Function>(system, value)) {
						PopValue(count);
						RaiseError(SXE_BADTYPE, "Invoked data is not a function");
						break;
					}

					if (SX_TOFUNC(value)->cfunc != NULL) {
						ret = InvokeCFunc(SX_TOFUNC(value), count);
						PopValue(count);
						PushValue(ret);
						break;
					}

					PushCall(SX_TOFUNC(value), count);
					goto run_code; // jump to executation stage
					break;
				case OP_GT:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) > 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_LT:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) < 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_GTE:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) >= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_LTE:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue(1)) <= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_EQUAL:
					ret = Number::Create (Value::Equal (system, GetValue(2), GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_NEQUAL:
					ret = Number::Create (!Value::Equal (system, GetValue(2), GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_NOT:
					ret = Number::Create (!Value::True (system, GetValue(1)));
					PopValue(1);
					PushValue(ret);
					break;
				case OP_LOOKUP:
					index = curcall->func->nodes[curcall->op_ptr++];
					PushValue(curcall->items[index]);
					break;
				case OP_ASSIGN:
					index = curcall->func->nodes[curcall->op_ptr++];
					curcall->items[index] = GetValue(1);
					break;
				case OP_CONCAT:
					value = GetValue(2);
					value2 = GetValue(1);
					PopValue(2);
					if (!Value::IsA<String>(system, value) || !Value::IsA<String>(system, value2)) {
						RaiseError(SXE_BADTYPE, "Only strings may be used in concatenation");
					} else {
						PushValue(new String(system, ((String*)value)->GetStr() + ((String*)value2)->GetStr()));
					}
					break;
				case OP_INDEX:
					value = GetValue(2);
					if (Value::IsA<List>(system, value)) {
						ret = ((List*)value)->GetIndex (system, GetValue(1));
						PopValue(2);
						PushValue(ret);
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Instance is not a list type in index operation");
					}
					break;
				case OP_PREINCREMENT:
					ret = NULL;
					index = Number::ToInt(GetValue(2));
					ret = curcall->items[index] = Number::Create (Number::ToInt (curcall->items[index]) + Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_POSTINCREMENT:
					ret = NULL;
					index = Number::ToInt(GetValue(2));
					ret = curcall->items[index];
					curcall->items[index] = Number::Create (Number::ToInt (curcall->items[index]) + Number::ToInt (GetValue(1)));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_NEWARRAY:
					count = curcall->func->nodes[curcall->op_ptr++];
					if (count > 0) {
						ret = new Array(system, count, &data_stack[data - count]);
					} else {
						ret = new Array(system);
					}
					PopValue(count);
					PushValue(ret);
					break;
				case OP_SETINDEX:
					value = GetValue(3);
					if (Value::IsA<List>(system, value)) {
						ret = ((List*)value)->SetIndex (system, GetValue(2), GetValue(1));
						PopValue(3);
						PushValue(ret);
					} else {
						PopValue(3);
						RaiseError(SXE_BADTYPE, "Instance is not a list type in set index operation");
					}
					break;
				case OP_TYPECAST:
					// get type
					value = GetValue(1);
					type = SX_TOTYPE(value)->GetTypePtr();

					// get value
					value = GetValue(2);
					if (Value::IsA (system, value, type)) {
						// pop type
						PopValue(1);
					} else {
						// push NULL/false value
						PopValue(2);
						PushValue(NULL);
					}
					break;
				case OP_STRINGCAST:
					// get value
					value = GetValue(1);
					PopValue(1);
					PushValue(Value::ToString(system, value));
					break;
				case OP_INTCAST:
					// get value
					value = GetValue(1);
					PopValue(1);
					PushValue(Value::ToInt(system, value));
					break;
				case OP_METHOD:
					name = curcall->func->nodes[curcall->op_ptr++];
					count = curcall->func->nodes[curcall->op_ptr++];
					value = GetValue(count + 1); // the type

					if (value == NULL) {
						PopValue(count + 1);
						RaiseError(SXE_NILCALL, "Value is nil for method call");
						break;
					}
					type = Value::TypeOf(system, value);
					if (type == NULL) {
						PopValue(count + 1);
						RaiseError(SXE_NILCALL, "Value has no type for method call");
						break;
					}
					method = type->GetMethod(name);
					if (method == NULL) {
						PopValue(count + 1);
						type = Value::TypeOf(system, value);
						RaiseError(SXE_UNDEFINED, "Method '%s' on type '%s' does not exist", IDToName (name), IDToName(type->GetName()));
						break;
					}
					if (method->sxmethod != NULL) {
						PushCall(method->sxmethod, count + 1);
						goto run_code; // jump to executation stage
					} else {
						if (count < method->argc) {
							PopValue(count + 1);
							type = Value::TypeOf(system, value);
							RaiseError(SXE_UNDEFINED, "Too few arguments to method '%s' on type '%s'", IDToName (name), IDToName(type->GetName()));
							break;
						}
						ret = InvokeMethod (value, method, count);
						PopValue(count + 1);
						PushValue(ret);
					}
					break;
				case OP_STATIC_METHOD:
					name = curcall->func->nodes[curcall->op_ptr++];
					count = curcall->func->nodes[curcall->op_ptr++];
					value = GetValue(1); // the type
					PopValue(1);

					if (!Value::IsA<TypeValue>(system, value)) {
						PopValue(count);
						RaiseError(SXE_NILCALL, "Value is not a type for method call");
						break;
					}
					type = SX_TOTYPE(value)->GetTypePtr();
					method = type->GetStaticMethod(name);
					if (method == NULL) {
						PopValue(count);
						RaiseError(SXE_UNDEFINED, "Static method '%s' on type '%s' does not exist", IDToName (name), IDToName(type->GetName()));
						break;
					}

					if (method->sxmethod != NULL) {
						PushCall(method->sxmethod, count);
						goto run_code; // jump to executation stage
					} else {
						if (count < method->argc) {
							PopValue(count);
							RaiseError(SXE_UNDEFINED, "Too few arguments to static method '%s' on type '%s' (%d or %d)", IDToName (name), IDToName(type->GetName()), count, (long)method->argc);
							break;
						}
						ret = InvokeMethod(NULL, method, count);
						PopValue(count);
						PushValue(ret);
					}
					break;
				case OP_SETFILELINE:
					value = GetValue(2);
					if (Value::IsA<String>(system, value)) {
						curcall->file = (String*)value;
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Tried to set filename to a non-string");
						break;
					}
					value = GetValue(1);
					if (Value::IsA<Number>(system, value)) {
						curcall->line = Number::ToInt (value);
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Tried to set file line to a non-number");
						break;
					}
					PopValue(2);
					break;
				case OP_NEXTLINE:
					++ curcall->line;
					break;
				case OP_POP:
					PopValue(1);
					break;
				case OP_TEST:
					if (Value::True (system, GetValue(1)))
						curcall->flags |= CFLAG_TTRUE;
					else
						curcall->flags &= ~CFLAG_TTRUE;
					break;
				case OP_JUMP:
					curcall->op_ptr += curcall->func->nodes[curcall->op_ptr];
					break;
				case OP_TJUMP:
					if (curcall->flags & CFLAG_TTRUE) {
						curcall->op_ptr += curcall->func->nodes[curcall->op_ptr];
					} else {
						++curcall->op_ptr;
					}
					break;
				case OP_FJUMP:
					if ((curcall->flags & CFLAG_TTRUE) == 0) {
						curcall->op_ptr += curcall->func->nodes[curcall->op_ptr];
					} else {
						++curcall->op_ptr;
					}
					break;
				case OP_YIELD:
					// break - switch
					return state;
					break;
				case OP_IN:
					value = GetValue(2);
					if (Value::IsA<List>(system, value)) {
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
				case OP_GET_MEMBER:
					value = GetValue(1);
					name = curcall->func->nodes[curcall->op_ptr++];
					PopValue(1);
					if (Value::IsA<Struct>(system, value)) {
						ret = ((Struct*)value)->GetMember(system, name);
						PushValue(ret);
					} else {
						RaiseError(SXE_BADTYPE, "Attempt to get member value on non-structure");
					}
					break;
				case OP_SET_MEMBER:
					value = GetValue(2);
					name = curcall->func->nodes[curcall->op_ptr++];
					if (Value::IsA<Struct>(system, value)) {
						((Struct*)value)->SetMember(system, name, GetValue(1));
						PopValue(1);
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Attempt to get member value on non-structure");
					}
					break;
				case OP_ITER:
					name = curcall->func->nodes[curcall->op_ptr++];
					value = GetValue(1);
					// have we a nil?
					if (value == NULL) {
						// remove true flag
						curcall->flags &= ~CFLAG_TTRUE;
					// have we an iterator?
					} else if (Value::IsA<Iterator>(system, value)) {
						// get next
						if (!SX_TOITER(value)->Next(system, value)) {
							// remove true flag
							curcall->flags &= ~CFLAG_TTRUE;
						} else {
							// set variable
							curcall->items[name] = value;
							curcall->flags |= CFLAG_TTRUE;
						}
					// have we a list?
					} else if (Value::IsA<List>(system, value)) {
						// generate iterator
						value = List::GetIter(system, (List*)value);
						if (!value) {
							// remove true flag
							curcall->flags &= ~CFLAG_TTRUE;
						} else {
							PopValue(1);
							PushValue(value);
						}

						// get next
						if (!SX_TOITER(value)->Next(system, value)) {
							// remove true flag
							curcall->flags &= ~CFLAG_TTRUE;
						} else {
							// set variable
							curcall->items[name] = value;
							curcall->flags |= CFLAG_TTRUE;
						}
					// bad type
					} else {
						PopValue(1); // remove type
						RaiseError(SXE_BADTYPE, "Value is not an iterator or a list");
					}
					break;
			}

			// exit out of function on thread switch
			if ((flags & TFLAG_PREEMPT) && (state == STATE_RUNNING)) {
				if (-- op_count == 0) {
					// break - switch
					return state;
				}
			}
		}

		// pop call, push return value
		ret = Thread::ret = GetValue(1);
		PopCall();
		PushValue(ret);

		// reset state ; if we should break, return as well
		if (curcall->flags & CFLAG_BREAK) {
			if (state != STATE_FAILED)
				state = STATE_RETURN;
			return state;
		}
	}

	// we finished
	state = STATE_FINISHED;

	return state;
}

int
Thread::Run (void) {
	if (state != STATE_READY) {
		return SXE_NOTREADY;
	}

	state = STATE_RUNNING;
	Eval();
	if (state == STATE_RUNNING)
		state = STATE_READY;

	if (data > 0 && state == STATE_FAILED) {
		// return error code
		return Number::ToInt(ret);
	}

	// got here, we're OK
	return SXE_OK;
}
