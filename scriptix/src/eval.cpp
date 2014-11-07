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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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

#include "scriptix.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace Scriptix;

OpCode Scriptix::OpCodeDefs[] = {
	{ "PUSH", 1 },
	{ "ADD", 0 },
	{ "SUBTRACT", 0 },
	{ "MULTIPLY", 0 },
	{ "DIVIDE", 0 },
	{ "NEGATE", 0 },
	{ "INVOKE", 1 },
	{ "CONCAT", 0 },
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

int
System::PushFrame (Function* func, size_t argc, Value* argv[]) {
	// check number of args
	if (argc < func->argc)
		return RaiseError(SXE_BADARGS, "Invalid number of arguments (%u of %u) to %s at %s:%lu", argc, func->argc, IDToName(func->id), func->file->GetCStr(), func->GetLineOf(0));

	// new access level
	SecurityLevel access = func->access;
	if (!frames.empty())
		access &= frames.back().access;

	// push new frame
	frames.resize(frames.size() + 1);
	Frame& frame = frames.back();

	frame.top = data_stack.size() - (argv == NULL ? argc : 0);
	frame.flags = 0;
	frame.argc = argc;
	frame.func = func;
	frame.access = access;

	// define variables for non-cfuncs
	Value** arglist = argv ? argv : &data_stack[data_stack.size() - argc];

	// C function
	if (func->cfunc) {
		frame.items = (Value**)GC_MALLOC(argc * sizeof(Value*));
		memcpy(frame.items, arglist, argc * sizeof(Value*));

	// Scriptix function
	} else {
		// argc items array (ick)
		Value** items = NULL;
		if (func->varc != 0) {
			items = (Value**)GC_MALLOC(func->varc * sizeof(Value*));
			if (items == NULL)
				return SXE_NOMEM;
			memset (items, 0, func->varc * sizeof(Value*));
		}

		// fill func args with arg list
		if (func->argc > 0)
			memcpy(items, arglist, sizeof(Value*) * func->argc);

		// var arg array
		if (func->varg && func->count) {
			Array* var_args = new Array(argc - func->argc, NULL);
			if (argc > func->argc)
				for (size_t i = func->argc; i < argc; ++i)
					var_args->Append(arglist[i]);
			items[func->argc] = var_args;
		}

		frame.items = items;
	}

	return SXE_OK;
}

void
System::PopFrame (void) {
	Frame& frame = frames.back();

	// unwind data stack 
	data_stack.resize(frame.top);

	// pop the frame
	frames.pop_back();
}

int
System::Invoke (Value* self, NameID method, size_t argc, Value* argv[], Value** retval)
{
	if (self == NULL) {
		if (retval != NULL)
			*retval = NULL;
		return SXE_NILCALL;
	}

	Function* func = Value::TypeOf(self)->GetMethod(method);
	if (func == NULL) {
		if (retval != NULL)
			*retval = NULL;
		return SXE_UNDEFINED;
	}

	Value* nargv[argc + 1];
	nargv[0] = self;
	memcpy(&nargv[1], argv, argc * sizeof(Value*));

	return Invoke(func, argc + 1, nargv, retval);
}

int
System::Invoke (Function* function, size_t argc, Value* argv[], Value** retval)
{
	// define types here to speed up loop
	unsigned long count;
	int op;
	int err;
	long index;
	Value* ret;
	Value* value;
	const TypeInfo* type;
	Function* method;
	NameID name;
	size_t frame_top;

	if ((err = PushFrame(function, argc, argv)) != SXE_OK)
		return err;

	state = STATE_RUNNING;
	frame_top = frames.size();

	while (frames.size() >= frame_top) {
run_code:
		// break processing if no longer running
		if (state != STATE_RUNNING)
			break;

		// working on a C function
		if (GetFrame().func->cfunc) {
			ret = GetFrame().func->cfunc(GetFrame().argc, GetFrame().items);
			PopFrame();
			PushValue(ret);
			continue;
		}

		while (GetFrame().op_ptr < GetFrame().func->count) {
			op = GetOpArg();

			// DEBUG
			// std::cout << GetFrame().func->file->GetCStr() << ':' << GetFrame().func->GetLineOf(GetFrame().op_ptr) << " [" << op << "]\t" << OpCodeDefs[op].name << "\tD:" << data_stack.size() << "\tF:" << frames.size() << std::endl;

			switch(op) {
			/* ----- OPERATORS ----- */
				case OP_PUSH:
					PushValue((Value*)GetOpArg());
					continue;
				case OP_ADD:
					ret = Number::Create (Number::ToInt (GetValue(2)) + Number::ToInt (GetValue()));
					PopValue(2);
					PushValue(ret);
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

					if (!Value::IsA<Function>(value)) {
						PopValue(count);
						RaiseError(SXE_BADTYPE, "Invoked data is not a function");
						break;
					}

					PushFrame(((Function*)value), count, NULL);
					goto run_code; // jump to executation stage
				case OP_CONCAT:
					value = Value::ToString(GetValue(2));
					if (value != NULL) {
						Value* second = Value::ToString(GetValue());
						PopValue(2);
						if (second) {
							ret = new String(((String*)value)->GetStr() + ((String*)second)->GetStr());
							PushValue(ret);
						} else {
							PushValue(NULL);
						}
					// not supported...
					} else {
						PopValue(2);
						PushValue(NULL);
					}
					break;
				case OP_GT:
					ret = Number::Create (Value::Compare (GetValue(2), GetValue()) > 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_LT:
					ret = Number::Create (Value::Compare (GetValue(2), GetValue()) < 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_GTE:
					ret = Number::Create (Value::Compare (GetValue(2), GetValue()) >= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_LTE:
					ret = Number::Create (Value::Compare (GetValue(2), GetValue()) <= 0);
					PopValue(2);
					PushValue(ret);
					break;
				case OP_EQUAL:
					ret = Number::Create (Value::Equal (GetValue(2), GetValue()));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_NEQUAL:
					ret = Number::Create (!Value::Equal (GetValue(2), GetValue()));
					PopValue(2);
					PushValue(ret);
					break;
				case OP_NOT:
					ret = Number::Create (!Value::True (GetValue()));
					PopValue();
					PushValue(ret);
					break;
				case OP_LOOKUP:
					PushValue(GetFrame().items[GetOpArg()]);
					break;
				case OP_ASSIGN:
					GetFrame().items[GetOpArg()] = GetValue();
					break;
				case OP_INDEX:
					value = GetValue(2);
					index = Number::ToInt(Value::ToInt(GetValue()));
					if (Value::IsA<Array>(value)) {
						ret = ((Array*)value)->GetIndex(index);
						PopValue(2);
						PushValue(ret);
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Instance is not an array type in index operation");
					}
					break;
				case OP_NEWARRAY:
					count = GetOpArg();
					if (count > 0) {
						ret = new Array(count, &data_stack[data_stack.size() - count]);
						PopValue(count);
					} else {
						ret = new Array;
					}
					PushValue(ret);
					break;
				case OP_TYPECAST:
					// get type
					value = GetValue();
					type = ((TypeValue*)value)->GetTypePtr();

					// get value
					value = GetValue(2);
					if (Value::IsA (value, type)) {
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
					PushValue(Value::ToString(value));
					break;
				case OP_INTCAST:
					// get value
					value = GetValue();
					PopValue();
					PushValue(Value::ToInt(value));
					break;
				case OP_SETINDEX:
					value = GetValue(3);
					index = Number::ToInt(Value::ToInt(GetValue(2)));
					if (Value::IsA<Array>(value)) {
						ret = ((Array*)value)->SetIndex (index, GetValue());
						PopValue(3);
						PushValue(ret);
					} else {
						PopValue(3);
						RaiseError(SXE_BADTYPE, "Instance is not an array type in set index operation");
					}
					break;
				case OP_METHOD:
					name = GetOpArg();
					count = GetOpArg() + 1;
					value = GetValue(count); // the type

					if (value == NULL) {
						PopValue(count);
						RaiseError(SXE_NILCALL, "Value is nil for method call");
						break;
					}
					type = Value::TypeOf(value);
					if (type == NULL) {
						PopValue(count);
						RaiseError(SXE_NILCALL, "Value has no type for method call");
						break;
					}
					method = type->GetMethod(name);
					if (method == NULL) {
						PopValue(count);
						type = Value::TypeOf(value);
						RaiseError(SXE_UNDEFINED, "Method '%s' on type '%s' does not exist", IDToName (name), IDToName(type->GetName()));
						break;
					}

					PushFrame(method, count, NULL);
					goto run_code; // jump to executation stage
				case OP_JUMP:
					op = GetOpArg();
					GetFrame().op_ptr += op - 1;
					break;
				case OP_POP:
					PopValue();
					break;
				case OP_TEST:
					if (Value::True (GetValue()))
						GetFrame().flags |= CFLAG_TTRUE;
					else
						GetFrame().flags &= ~CFLAG_TTRUE;
					break;
				case OP_TJUMP:
					op = GetOpArg();
					if (GetFrame().flags & CFLAG_TTRUE)
						GetFrame().op_ptr += op - 1;
					break;
				case OP_FJUMP:
					op = GetOpArg();
					if ((GetFrame().flags & CFLAG_TTRUE) == 0)
						GetFrame().op_ptr += op - 1;
					break;
				case OP_YIELD:
					// break - switch
					return state;
					break;
				case OP_IN:
					value = GetValue(2);
					if (Value::IsA<Array>(value)) {
						if (((Array*)value)->Has (GetValue())) {
							PopValue(2);
							PushValue(Number::Create(1));
						} else {
							PopValue(2);
							PushValue(NULL);
						}
					} else {
						PopValue(2);
						RaiseError(SXE_BADTYPE, "Instance is not an array type in has operation");
					}
					break;
				case OP_SET_MEMBER:
					value = GetValue(2);
					name = GetOpArg();
					if (Value::IsA<Struct>(value)) {
						((Struct*)value)->SetMember(name, GetValue());
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
					if (Value::IsA<Struct>(value)) {
						ret = ((Struct*)value)->GetMember(name);
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
						GetFrame().flags &= ~CFLAG_TTRUE;
					// have we an iterator?
					} else if (Value::IsA<Iterator>(value)) {
						// get next
						if (!((Iterator*)value)->Next(value)) {
							// remove true flag
							GetFrame().flags &= ~CFLAG_TTRUE;
						} else {
							// set variable
							GetFrame().items[name] = value;
							GetFrame().flags |= CFLAG_TTRUE;
						}
					// have we an array?
					} else if (Value::IsA<Array>(value)) {
						// generate iterator
						value = Array::GetIter((Array*)value);
						if (!value) {
							// remove true flag
							GetFrame().flags &= ~CFLAG_TTRUE;
						} else {
							PopValue();
							PushValue(value);
						}

						// get next
						if (!((Iterator*)value)->Next(value)) {
							// remove true flag
							GetFrame().flags &= ~CFLAG_TTRUE;
						} else {
							// set variable
							GetFrame().items[name] = value;
							GetFrame().flags |= CFLAG_TTRUE;
						}
					// bad type
					} else {
						PopValue(); // remove type
						RaiseError(SXE_BADTYPE, "Value is not an iterator or an array");
					}
					break;
				case OP_NEW:
					value = GetValue();
					PopValue();
					if (Value::IsA<TypeValue>(value)) {
						type = ((TypeValue*)value)->GetTypePtr();
						PushValue(type->Construct());
					} else {
						RaiseError(SXE_BADTYPE, "Value given to new is not a type");
					}
					break;
				case OP_COPY:
					PushValue(GetValue(GetOpArg()));
					break;
			}
		}

		// pop frame, push return value
		ret = GetValue();
		PopFrame();
		PushValue(ret);
	}

	// return value
	ret = GetValue();
	PopValue();

	// pop any extra frames (if we broke early)
	while (frames.size() > frame_top)
		PopFrame();

	// set return value
	if (retval != NULL)
		*retval = ret;

	// error occured?
	err = SXE_OK;
	if (state == STATE_FAILED)
		err = Number::ToInt(GetValue());

	// pop value, return error code
	return err;
}
