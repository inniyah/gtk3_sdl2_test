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

#define VM_DEBUG 0
#undef HAVE_ALLOCA

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
	{ "NEWARRAY", 1 },
	{ "TYPECAST", 0 },
	{ "STRINGCAST", 0 },
	{ "INTCAST", 0 },
	{ "SETINDEX", 0 },
	{ "METHOD", 2 },
	{ "SETFILE", 0 },
	{ "SETLINE", 1 },
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
	{ "NEW", 0 },
	{ "COPY", 1 },
};

Value*
Thread::InvokeCFunc (Function* invoked, size_t argc)
{
	Value** argv;
	Value* ret;
	size_t i;
	size_t count;

	// find largest of argc/func->argc
	if (argc > invoked->argc)
		count = argc;
	else
		count = invoked->argc;

	// allocate argv
	argv = NULL;
	if (count) {
#if defined(HAVE_ALLOCA)
		argv = (Value**)alloca (count * sizeof (Value*));
#else
		argv = (Value**)GC_MALLOC(count * sizeof (Value*));
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
	ret = NULL;
	if (invoked->cfunc)
		ret = invoked->cfunc (this, count, argv);
	else if (invoked->cmethod && count > 0)
		ret = invoked->cmethod (this, argv[0], count - 1, &argv[1]);

#if !defined(HAVE_ALLOCA)
	if (argv != NULL) {
		// free array
		GC_FREE (argv);
	}
#endif

	return ret;
}

int
Thread::Eval (void) {
	unsigned long count;
	unsigned long op_count = system->GetRunLength();
	int op;
	Value* ret;
	Value* value;
	Frame* cframe;
	const Type* type;
	Function* method;
	NameID name;

	while (!frames.empty()) {
run_code:
		cframe = &GetFrame();

		// working on a C function
		if (cframe->func->cfunc || cframe->func->cmethod) {
			ret = Thread::ret = InvokeCFunc (cframe->func, cframe->argc);
			PopFrame();
			PushValue(ret);
			continue;
		}

		while (cframe->op_ptr < cframe->func->count && state == STATE_RUNNING) {
			op = GetOpArg();

			// DEBUG
			#if VM_DEBUG
			std::cout << '[' << op << "]\t" << OpCodeDefs[op].name << '\t' << std::endl;
			#endif

			switch(op) {
			/* ----- OPERATORS ----- */
				case OP_PUSH:
					PushValue((Value*)GetOpArg());
					continue;
				case OP_ADD:
					value = GetValue(2);
					// add a number + something?
					if (Value::IsA<Number>(system, value)) {
						ret = Number::Create (Number::ToInt(value) + Number::ToInt(GetValue()));
						PopValue(2);
						PushValue(ret);
					// add a string + something?
					} else if (Value::IsA<String>(system, value)) {
						Value* second = Value::ToString(system, GetValue());
						if (second) {
							ret = new String(system, ((String*)value)->GetStr() + ((String*)second)->GetStr());
							PopValue(2);
							PushValue(ret);
						} else {
							// just leave first value on stack
							PopValue();
						}
					// not supported...
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Value being added is not a number or string");
					}
					break;
				case OP_SUBTRACT:
					ret = Number::Create (Number::ToInt (GetValue(2)) - Number::ToInt (GetValue()));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_MULTIPLY:
					ret = Number::Create (Number::ToInt (GetValue(2)) * Number::ToInt (GetValue()));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_DIVIDE:
					// divide by 0 check
					if (Number::ToInt(GetValue()) == 0) {
						PopValue(2);
						RaiseError(SXE_DIVZERO, "Division by zero");
					} else {
						ret = Number::Create (Number::ToInt (GetValue(2)) / Number::ToInt (GetValue()));
						PopValue(2);
						PushValue(ret);
					}
					break;
				case OP_NEGATE:
					ret = Number::Create (- Number::ToInt (GetValue()));
					PopValue();
					PushValue(ret);
					break;
				case OP_INVOKE:
					count = GetOpArg();
					value = GetValue();
					PopValue();

					if (!Value::IsA<Function>(system, value)) {
						PopValue(count);
						RaiseError(SXE_BADTYPE, "Invoked data is not a function");
						break;
					}

					if (((Function*)value)->cfunc != NULL) {
						ret = InvokeCFunc(((Function*)value), count);
						PopValue(count);
						PushValue(ret);
						break;
					}

					PushFrame(((Function*)value), count);
					goto run_code; // jump to executation stage
				case OP_GT:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue()) > 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_LT:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue()) < 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_GTE:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue()) >= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_LTE:
					ret = Number::Create (Value::Compare (system, GetValue(2), GetValue()) <= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_EQUAL:
					ret = Number::Create (Value::Equal (system, GetValue(2), GetValue()));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_NEQUAL:
					ret = Number::Create (!Value::Equal (system, GetValue(2), GetValue()));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_NOT:
					ret = Number::Create (!Value::True (system, GetValue()));
					PopValue();
					PushValue(ret);
					break;
				case OP_LOOKUP:
					PushValue(cframe->items[GetOpArg()]);
					break;
				case OP_ASSIGN:
					cframe->items[GetOpArg()] = GetValue();
					break;
				case OP_INDEX:
					value = GetValue(2);
					if (Value::IsA<List>(system, value)) {
						ret = ((List*)value)->GetIndex (system, GetValue());
						PopValue(2);
						PushValue(ret);
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Instance is not a list type in index operation");
					}
					break;
				case OP_NEWARRAY:
					count = GetOpArg();
					if (count > 0) {
						ret = new Array(system, count, &data_stack[data_stack.size() - count]);
						PopValue(count);
					} else {
						ret = new Array(system);
					}
					PushValue(ret);
					break;
				case OP_TYPECAST:
					// get type
					value = GetValue();
					type = ((TypeValue*)value)->GetTypePtr();

					// get value
					value = GetValue(2);
					if (Value::IsA (system, value, type)) {
						// pop type
						PopValue();
					} else {
						// push NULL/false value
						PopValue(2);
						PushValue(NULL);
					}
					break;
				case OP_STRINGCAST:
					// get value
					value = GetValue();
					PopValue();
					PushValue(Value::ToString(system, value));
					break;
				case OP_INTCAST:
					// get value
					value = GetValue();
					PopValue();
					PushValue(Value::ToInt(system, value));
					break;
				case OP_SETINDEX:
					value = GetValue(3);
					if (Value::IsA<List>(system, value)) {
						ret = ((List*)value)->SetIndex (system, GetValue(2), GetValue());
						PopValue(3);
						PushValue(ret);
					} else {
						PopValue(3);
						RaiseError(SXE_BADTYPE, "Instance is not a list type in set index operation");
					}
					break;
				case OP_METHOD:
					name = GetOpArg();
					count = GetOpArg();
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
					if (method->cmethod != NULL) {
						if (count < method->argc) {
							PopValue(count + 1);
							type = Value::TypeOf(system, value);
							RaiseError(SXE_UNDEFINED, "Too few arguments to method '%s' on type '%s'", IDToName (name), IDToName(type->GetName()));
							break;
						}
						ret = InvokeCFunc (method, count + 1);
						PopValue(count + 1);
						PushValue(ret);
					} else {
						PushFrame(method, count + 1);
						goto run_code; // jump to executation stage
					}
					break;
				case OP_SETFILE:
					value = GetValue();
					PopValue();
					if (Value::IsA<String>(system, value)) {
						cframe->file = (String*)value;
					} else {
						RaiseError(SXE_BADTYPE, "Tried to set filename to a non-string");
						break;
					}

					// DEBUG
					#if VM_DEBUG
					std::cout << "  Line: " << cframe->file->GetStr() << ':' << cframe->line << " in " << IDToName(cframe->func->id) << "()" << std::endl;
					#endif

					break;
				case OP_SETLINE:
					cframe->line = GetOpArg();

					// DEBUG
					#if VM_DEBUG
					std::cout << "  Line: " << cframe->line << std::endl;
					#endif

					break;
				case OP_NEXTLINE:
					++ cframe->line;

					// DEBUG
					#if VM_DEBUG
					std::cout << "  Line: " << cframe->line << std::endl;
					#endif

					break;
				case OP_JUMP:
					cframe->op_ptr += GetOpArg() - 1;
					break;
				case OP_POP:
					PopValue();
					break;
				case OP_TEST:
					if (Value::True (system, GetValue()))
						cframe->flags |= CFLAG_TTRUE;
					else
						cframe->flags &= ~CFLAG_TTRUE;
					break;
				case OP_TJUMP:
					if (cframe->flags & CFLAG_TTRUE) {
						cframe->op_ptr += GetOpArg() - 1;
					} else {
						++cframe->op_ptr;
					}
					break;
				case OP_FJUMP:
					if ((cframe->flags & CFLAG_TTRUE) == 0) {
						cframe->op_ptr += GetOpArg() - 1;
					} else {
						++cframe->op_ptr;
					}
					break;
				case OP_STATIC_METHOD:
					name = GetOpArg();
					count = GetOpArg();
					value = GetValue(); // the type
					PopValue();

					if (!Value::IsA<TypeValue>(system, value)) {
						PopValue(count);
						RaiseError(SXE_NILCALL, "Value is not a type for method call");
						break;
					}
					type = ((TypeValue*)value)->GetTypePtr();
					method = type->GetStaticMethod(name);
					if (method == NULL) {
						PopValue(count);
						RaiseError(SXE_UNDEFINED, "Static method '%s' on type '%s' does not exist", IDToName (name), IDToName(type->GetName()));
						break;
					}

					if (method->cmethod != NULL) {
						if (count < method->argc) {
							PopValue(count);
							RaiseError(SXE_UNDEFINED, "Too few arguments to static method '%s' on type '%s' (%d or %d)", IDToName (name), IDToName(type->GetName()), count, (long)method->argc);
							break;
						}
						ret = InvokeCFunc(method, count);
						PopValue(count);
						PushValue(ret);
					} else {
						PushFrame(method, count);
						goto run_code; // jump to executation stage
					}
					break;
				case OP_YIELD:
					// break - switch
					return state;
					break;
				case OP_IN:
					value = GetValue(2);
					if (Value::IsA<List>(system, value)) {
						if (((List*)value)->Has (system, GetValue())) {
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
				case OP_SET_MEMBER:
					value = GetValue(2);
					name = GetOpArg();
					if (Value::IsA<Struct>(system, value)) {
						((Struct*)value)->SetMember(system, name, GetValue());
						PopValue();
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Attempt to get member value on non-structure");
					}
					break;
				case OP_GET_MEMBER:
					value = GetValue();
					name = GetOpArg();
					PopValue();
					if (Value::IsA<Struct>(system, value)) {
						ret = ((Struct*)value)->GetMember(system, name);
						PushValue(ret);
					} else {
						RaiseError(SXE_BADTYPE, "Attempt to get member value on non-structure");
					}
					break;
				case OP_ITER:
					name = GetOpArg();
					value = GetValue();
					// have we a nil?
					if (value == NULL) {
						// remove true flag
						cframe->flags &= ~CFLAG_TTRUE;
					// have we an iterator?
					} else if (Value::IsA<Iterator>(system, value)) {
						// get next
						if (!((Iterator*)value)->Next(system, value)) {
							// remove true flag
							cframe->flags &= ~CFLAG_TTRUE;
						} else {
							// set variable
							cframe->items[name] = value;
							cframe->flags |= CFLAG_TTRUE;
						}
					// have we a list?
					} else if (Value::IsA<List>(system, value)) {
						// generate iterator
						value = List::GetIter(system, (List*)value);
						if (!value) {
							// remove true flag
							cframe->flags &= ~CFLAG_TTRUE;
						} else {
							PopValue();
							PushValue(value);
						}

						// get next
						if (!((Iterator*)value)->Next(system, value)) {
							// remove true flag
							cframe->flags &= ~CFLAG_TTRUE;
						} else {
							// set variable
							cframe->items[name] = value;
							cframe->flags |= CFLAG_TTRUE;
						}
					// bad type
					} else {
						PopValue(); // remove type
						RaiseError(SXE_BADTYPE, "Value is not an iterator or a list");
					}
					break;
				case OP_NEW:
					value = GetValue();
					PopValue();
					if (Value::IsA<TypeValue>(system, value)) {
						type = ((TypeValue*)value)->GetTypePtr();
						PushValue(type->Construct(system));
					} else {
						RaiseError(SXE_BADTYPE, "Value given to new is not a type");
					}
					break;
				case OP_COPY:
					PushValue(GetValue(GetOpArg()));
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

		// pop frame, push return value
		ret = Thread::ret = GetValue();
		PopFrame();
		PushValue(ret);

		// reset state ; if we should break, return as well
		if (cframe->flags & CFLAG_BREAK) {
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

	if (!data_stack.empty() && state == STATE_FAILED) {
		// return error code
		return Number::ToInt(ret);
	}

	// got here, we're OK
	return SXE_OK;
}
