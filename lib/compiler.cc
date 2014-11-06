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

#include <stdio.h>
#include <stdarg.h>

#include "scriptix.h"
#include "compiler.h"

using namespace Scriptix;
using namespace Scriptix::Compiler;

#define _test(expr) {if(!(expr)) return false;}

static
void
_sxp_node_error (CompilerNode* node, const char *msg, ...)
{
	char buffer[512];
	va_list va;

	va_start (va, msg);
	vsnprintf (buffer, sizeof(buffer), msg, va);
	va_end (va);

	GetSystem()->HandleError (node->file ? ((String*)node->file)->GetCStr() : "<input>", node->line, buffer);
}

static
int
_sxp_count (CompilerNode *node) {
	int i = 0;
	while (node != NULL) {
		++ i;
		node = node->next;
	}
	return i;
}

bool
Scriptix::Compiler::Compiler::CompileNode (CompilerFunction* func, CompilerNode *node) {
	// for the jumps necessary
	unsigned long pos;
	unsigned long pos2;

	while (node != NULL) {
		// update debug info
		if (node->line != last_line) {
			debug.push_back(DebugMetaData(func->func->count - last_op, last_line));
			last_op = func->func->count;
			last_line = node->line;
		}

		// select operations...
		switch (node->type) {
			// no operation
			case SXP_NOOP:
				// ignore
				break;
			// basic mathematical operation (+, /, -, *)
			case SXP_MATH:
				_test(CompileNode (func, node->parts.nodes[0]))
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode((sx_op_type)node->parts.op);
				break;
			// push data onto stack
			case SXP_DATA:
				func->func->AddValue(node->parts.value);
				break;
			// unary negation
			case SXP_NEGATE:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_NEGATE);
				break;
			// unary not operation
			case SXP_NOT:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_NOT);
				break;
			// short-cut or operator
			case SXP_OR:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_TEST);
				func->func->AddOpcode(OP_TJUMP);
				pos = func->func->count;
				func->func->AddOparg(0);
				func->func->AddOpcode(OP_POP);
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->nodes[pos] = func->func->count - pos;
				break;
			// short cut and operation
			case SXP_AND:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_TEST);
				func->func->AddOpcode(OP_FJUMP);
				pos = func->func->count;
				func->func->AddOparg(0);
				func->func->AddOpcode(OP_POP);
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->nodes[pos] = func->func->count - pos;
				break;
			// call a function
			case SXP_INVOKE:
				_test(CompileNode (func, node->parts.nodes[1]))
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_INVOKE);
				func->func->AddOparg (_sxp_count (node->parts.nodes[1]));
				break;
			// retrieve a variable/global
			case SXP_LOOKUP:
			{
				Value* lfunc;
				Value* gval;
				char found = 0;
				long index;

				// do variable lookup
				index = GetVar(func, node->parts.name);
				if (index >= 0) {
					func->func->AddOpcode(OP_LOOKUP);
					func->func->AddOparg(index);
					break;
				}

				// search for function
				for (FunctionList::iterator dfunc = funcs.begin(); dfunc != funcs.end(); ++dfunc) {
					if ((*dfunc)->name == node->parts.name) {
						func->func->AddValue((Value*)((*dfunc)->func));
						found = 1;
						break;
					}
				}
				// found, done, ok
				if (found) {
					break;
				}

				// external function?
				lfunc = GetSystem()->GetFunction(node->parts.name);
				if (lfunc) {
					// add function
					func->func->AddValue(lfunc);
					break;
				}

				// global variable?
				index = GetGlobal(node->parts.name);
				if (index >= 0) {
					func->func->AddValue(globals);
					func->func->AddValue(Number::Create(index));
					func->func->AddOpcode(OP_INDEX);
					break;
				}

				// global constant?
				gval = GetSystem()->GetGlobal(node->parts.name);
				if (gval) {
					func->func->AddValue(gval);
					break;
				}

				// failure...
				_sxp_node_error (node, "Error: Unknown identifier '%s'", IDToName (node->parts.name));
				return false;
			}
			// declare a variable
			case SXP_DECLARE:
			{
				long index;

				// already exists?
				index = GetVar(func, node->parts.name);
				if (index >= 0) {
					_sxp_node_error (node, "Error: Local identifier '%s' already declared", IDToName (node->parts.name));
					return false;
				}

				// create
				index = AddVar(func, node->parts.name);

				// assign
				if (node->parts.nodes[0] != NULL)
					_test(CompileNode (func, node->parts.nodes[0]))
				else
					func->func->AddValue(Nil);
				func->func->AddOpcode(OP_ASSIGN);
				func->func->AddOparg(index);
				break;
			}
			// set a variable
			case SXP_ASSIGN:
			{
				long index = GetVar(func, node->parts.name);
				if (index < 0) {
					// global variable?
					index = GetGlobal(node->parts.name);
					if (index >= 0) {
						// do a lookup
						func->func->AddValue((Value*)globals);
						func->func->AddValue(Number::Create(index));
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(OP_SETINDEX);
						break;
						
					} else {
						_sxp_node_error (node, "Error: Unkown identifier '%s'", IDToName (node->parts.name));
						return false;
					}
				}
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_ASSIGN);
				func->func->AddOparg(index);
				break;
			}
			// pop the return of the expression - single statement
			case SXP_STATEMENT:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_POP);
				break;
			// conditional block
			case SXP_IF:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_TEST);
				func->func->AddOpcode(OP_POP);
				func->func->AddOpcode(OP_FJUMP);
				pos = func->func->count;
				func->func->AddOparg(0);
				_test(CompileNode (func, node->parts.nodes[1]))
				if (node->parts.nodes[2]) { // else
					func->func->AddOpcode(OP_JUMP);
					pos2 = func->func->count;
					func->func->AddOparg(0);
					func->func->nodes[pos] = func->func->count - pos;
					_test(CompileNode (func, node->parts.nodes[2]))
					func->func->nodes[pos2] = func->func->count - pos2;
				} else {
					func->func->nodes[pos] = func->func->count - pos;
				}
				break;
			// a kind of loop
			case SXP_LOOP:
				PushBlock(func->func);
				switch (node->parts.op) {
					case SXP_LOOP_WHILE:
						// while... do - test true, loop
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(OP_TEST);
						func->func->AddOpcode(OP_POP);
						_test(AddBreakOnFalse())
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(AddContinue())
						break;
					case SXP_LOOP_UNTIL:
						// until... do - test false, loop
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(OP_TEST);
						func->func->AddOpcode(OP_POP);
						_test(AddBreakOnTrue())
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(AddContinue())
						break;
					case SXP_LOOP_DOWHILE:
						// do... while - loop, test true
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(OP_TEST);
						func->func->AddOpcode(OP_POP);
						func->func->AddOpcode(OP_TJUMP);
						func->func->AddOparg(BlockStart() - func->func->count);
						break;
					case SXP_LOOP_DOUNTIL:
						// do... until - loop, test false
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(OP_TEST);
						func->func->AddOpcode(OP_POP);
						func->func->AddOpcode(OP_FJUMP);
						func->func->AddOparg(BlockStart() - func->func->count);
						break;
					case SXP_LOOP_FOREVER:
						// permanent loop - loop
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(AddContinue())
						break;
				}
				PopBlock();
				break;
			// set a value in an array
			case SXP_SETINDEX:
				_test(CompileNode (func, node->parts.nodes[0]))
				_test(CompileNode (func, node->parts.nodes[1]))
				_test(CompileNode (func, node->parts.nodes[2]))
				func->func->AddOpcode(OP_SETINDEX);
				break;
			// get a value from an array
			case SXP_GETINDEX:
				_test(CompileNode (func, node->parts.nodes[0]))
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(OP_INDEX);
				break;
			// generate an array from stack value
			case SXP_ARRAY:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_NEWARRAY);
				func->func->AddOparg(_sxp_count(node->parts.nodes[0]));
				break;
			// increment a normal variable, push result
			case SXP_PREOP:
				// normal variable/name
				if (node->parts.nodes[0]->type == SXP_LOOKUP) {
					long index;
					// do variable lookup
					index = GetVar(func, node->parts.nodes[0]->parts.name);
					if (index < 0) {
						_sxp_node_error (node, "Error: Undefined variable '%s'", IDToName (node->parts.name));
						return false;
					}

					// lookup, copy, do op, re-assign
					func->func->AddOpcode(OP_LOOKUP);
					func->func->AddOparg(index);
					_test(CompileNode (func, node->parts.nodes[1]))
					func->func->AddOpcode((sx_op_type)node->parts.op);
					func->func->AddOpcode(OP_ASSIGN);
					func->func->AddOparg(index);
				// list lookup
				} else if (node->parts.nodes[0]->type == SXP_GETINDEX) {
					// setup, copy, get value, do op, re-assign
					_test(CompileNode (func, node->parts.nodes[0]->parts.nodes[0]))
					_test(CompileNode (func, node->parts.nodes[0]->parts.nodes[1]))
					func->func->AddOpcode(OP_COPY);
					func->func->AddOparg(2);
					func->func->AddOpcode(OP_COPY);
					func->func->AddOparg(2);
					func->func->AddOpcode(OP_INDEX);
					_test(CompileNode (func, node->parts.nodes[1]))
					func->func->AddOpcode((sx_op_type)node->parts.op);
					func->func->AddOpcode(OP_SETINDEX);
				// member lookup
				} else if (node->parts.nodes[0]->type == SXP_GETMEMBER) {
					// get, copy, lookup, do op, re-assign
					_test(CompileNode (func, node->parts.nodes[0]->parts.nodes[0]))
					func->func->AddOpcode(OP_COPY);
					func->func->AddOparg(1);
					func->func->AddOpcode(OP_GET_MEMBER);
					func->func->AddOparg(node->parts.nodes[0]->parts.name);
					_test(CompileNode (func, node->parts.nodes[1]))
					func->func->AddOpcode((sx_op_type)node->parts.op);
					func->func->AddOpcode(OP_SET_MEMBER);
					func->func->AddOparg(node->parts.nodes[0]->parts.name);
				// not an lvalue!
				} else {
					_sxp_node_error (node, "Error: Expression is not an lvalue");
					return false;
				}
				break;
			// push a normal variable, then increment its value
			case SXP_POSTOP:
			{
				// normal variable/name
				if (node->parts.nodes[0]->type == SXP_LOOKUP) {
					long index;
					// do variable lookup
					index = GetVar(func, node->parts.nodes[0]->parts.name);
					if (index < 0) {
						_sxp_node_error (node, "Error: Undefined variable '%s'", IDToName (node->parts.name));
						return false;
					}

					// lookup, copy, do op, re-assign
					func->func->AddOpcode(OP_LOOKUP);
					func->func->AddOparg(index);
					func->func->AddOpcode(OP_COPY);
					func->func->AddOparg(1);
					_test(CompileNode (func, node->parts.nodes[1]))
					func->func->AddOpcode((sx_op_type)node->parts.op);
					func->func->AddOpcode(OP_ASSIGN);
					func->func->AddOparg(index);
					func->func->AddOpcode(OP_POP);
				// list lookup
				} else if (node->parts.nodes[0]->type == SXP_GETINDEX) {
					// setup, copy, get value, do op, re-assign
					_test(CompileNode (func, node->parts.nodes[0]->parts.nodes[0]))
					_test(CompileNode (func, node->parts.nodes[0]->parts.nodes[1]))
					func->func->AddOpcode(OP_INDEX);
					func->func->AddOpcode(OP_COPY);
					func->func->AddOparg(1);
					_test(CompileNode (func, node->parts.nodes[1]))
					func->func->AddOpcode((sx_op_type)node->parts.op);
					func->func->AddOpcode(OP_SETINDEX);
					func->func->AddOpcode(OP_POP);
				// member lookup
				} else if (node->parts.nodes[0]->type == SXP_GETMEMBER) {
					// get, copy, lookup, do op, re-assign
					_test(CompileNode (func, node->parts.nodes[0]->parts.nodes[0]))
					func->func->AddOpcode(OP_GET_MEMBER);
					func->func->AddOparg(node->parts.nodes[0]->parts.name);
					func->func->AddOpcode(OP_COPY);
					func->func->AddOparg(1);
					_test(CompileNode (func, node->parts.nodes[1]))
					func->func->AddOpcode((sx_op_type)node->parts.op);
					func->func->AddOpcode(OP_SET_MEMBER);
					func->func->AddOparg(node->parts.nodes[0]->parts.name);
					func->func->AddOpcode(OP_POP);
				// not an lvalue!
				} else {
					_sxp_node_error (node, "Error: Expression is not an lvalue");
					return false;
				}
				break;
			}
			// return from the current call stack
			case SXP_RETURN:
				if (node->parts.nodes[0] != NULL)
					_test(CompileNode (func, node->parts.nodes[0]))
				else
					func->func->AddValue(Nil);
				func->func->AddOpcode(OP_JUMP);
				returns.push_back(func->func->count);
				func->func->AddOparg(0);
				break;
			// break from current loop/block
			case SXP_BREAK:
				_test(AddBreak())
				break;
			// invoke a method on an object
			case SXP_METHOD:
				// value
				_test(CompileNode (func, node->parts.nodes[0]))
				// args
				if (node->parts.nodes[1])
					_test(CompileNode (func, node->parts.nodes[1]))
				// call
				func->func->AddOpcode(OP_METHOD);
				func->func->AddOparg (node->parts.name);
				func->func->AddOparg (_sxp_count (node->parts.nodes[1]));
				break;
			// convert a value into another type if possible
			case SXP_CAST:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddValue(new TypeValue(node->parts.type));
				func->func->AddOpcode(OP_TYPECAST);
				break;
			// special loop with a setup section, test, post-body expression
			case SXP_FOR:
				// setup
				_test(CompileNode (func, node->parts.nodes[0]))
				// skip first increment
				func->func->AddOpcode(OP_JUMP);
				pos = func->func->count;
				func->func->AddOparg(0);
				// begin loop
				_test(PushBlock(func->func));
				// increment
				_test(CompileNode (func, node->parts.nodes[2]))
				func->func->nodes[pos] = func->func->count - pos;
				// loop test
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(OP_TEST);
				func->func->AddOpcode(OP_POP);
				_test(AddBreakOnFalse())
				// body
				_test(CompileNode (func, node->parts.nodes[3]))
				// loop
				_test(AddContinue())
				// end
				PopBlock();
				break;
			// return to start of current loop/block
			case SXP_CONTINUE:
				_test(AddContinue())
				break;
			// break current thread
			case SXP_YIELD:
				func->func->AddOpcode(OP_YIELD);
				break;
			// check if a value is in an array
			case SXP_IN:
				// first put in list to check
				if (node->parts.nodes[1]) {
					_test(CompileNode (func, node->parts.nodes[1]))
				} else {
					func->func->AddValue(Nil);
				}
				// then put in item to check for
				if (node->parts.nodes[0]) {
					_test(CompileNode (func, node->parts.nodes[0]))
				} else {
					func->func->AddValue(Nil);
				}
				// set op
				func->func->AddOpcode(OP_IN);
				break;
			// construct a new object of the specified type
			case SXP_NEW:
				func->func->AddValue(new TypeValue(node->parts.type));
				func->func->AddOpcode(OP_NEW);
				if (node->parts.op) {
					if (node->parts.nodes[0])
						_test(CompileNode(func, node->parts.nodes[0]))
					func->func->AddOpcode(OP_METHOD);
					func->func->AddOparg(NameToID("new"));
					func->func->AddOparg(_sxp_count (node->parts.nodes[0]));
				}
				break;
			// set a Struct member
			case SXP_SETMEMBER:
				// object
				_test(CompileNode (func, node->parts.nodes[0]))
				// value
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(OP_SET_MEMBER);
				func->func->AddOparg(node->parts.name);
				break;
			// retrieve a Struct member
			case SXP_GETMEMBER:
				// object
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_GET_MEMBER);
				func->func->AddOparg(node->parts.name);
				break;
			// iterate over the items in a specialized list
			case SXP_FOREACH:
			{
				// set variable
				long index = GetVar(func, node->parts.name);
				if (index < 0) {
					index = AddVar(func, node->parts.name);
				}

				// set iterator object
				_test(CompileNode (func, node->parts.nodes[0]))
				// set start
				PushBlock(func->func);
				// iterator call
				func->func->AddOpcode(OP_ITER);
				func->func->AddOparg(index);
				// jump on end
				_test(AddBreakOnFalse())
				// body
				_test(CompileNode (func, node->parts.nodes[1]))
				// jump to begin
				_test(AddContinue())
				// end
				PopBlock();
				func->func->AddOpcode(OP_POP);
				break;
			}
			// force a value into a string if possible
			case SXP_STRINGCAST:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_STRINGCAST);
				break;
			// force a value into an int if possible
			case SXP_INTCAST:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(OP_INTCAST);
				break;
			// copy a value
			case SXP_COPY:
				func->func->AddOparg(node->parts.op);
				func->func->AddOpcode(OP_COPY);
				break;
			// concatenate two strings
			case SXP_CONCAT:
				_test(CompileNode (func, node->parts.nodes[0]))
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(OP_CONCAT);
				break;
		}
		node = node->next;
	}

	return true;
}

int
Scriptix::Compiler::Compiler::Compile(void) {
	// make function data
	for (FunctionList::iterator func = funcs.begin(); func != funcs.end(); ++func) {
		(*func)->func = new Function ((*func)->name, ((*func)->vars).size(), (*func)->varg);
		if (!(*func)->func) {
			Error("Failed to create function");
			return -1;
		}
		(*func)->func->access = access;
		(*func)->func->file = file;
	}

	// create type extensions
	for (ExtendList::iterator extend = extends.begin(); extend != extends.end(); ++extend) {
		for (CompilerExtend::MethodList::iterator func = (*extend)->methods.begin(); func != (*extend)->methods.end(); ++func) {
			if ((*extend)->type->GetMethod((*func)->name) != NULL) {
				std::string errmsg = "Attempt to extend type '";
				errmsg += IDToName((*extend)->type->GetName());
				errmsg += "' with method '";
				errmsg += IDToName((*func)->name);
				errmsg += "' which already exists";
				Error(errmsg.c_str());
				return -1;
			}

			// create function
			(*func)->func = new Function ((*func)->name, ((*func)->vars).size(), (*func)->varg);
			if (!(*func)->func) {
				Error("Failed to create function");
				return -1;
			}
			(*func)->func->access = access;
			(*func)->func->file = file;
		}
	}

	// compile blocks
	for (FunctionList::iterator func = funcs.begin(); func != funcs.end(); ++func) {
		// setup vararg
		if ((*func)->varg)
			(*func)->vars.push_back((*func)->varg);

		// optimize
		(*func)->body = sxp_transform ((*func)->body);

		// reset file/line
		debug.clear();
		last_line = line;
		last_op = 0;

		// compile node
		if (!CompileNode (*func, (*func)->body))
			return -1; // failed
		(*func)->func->AddValue(Nil);
		debug.push_back(DebugMetaData((*func)->func->count - last_op, last_line));
		(*func)->func->debug = (DebugMetaData*)GC_MALLOC(sizeof(DebugMetaData) * debug.size());
		memcpy((*func)->func->debug, &debug[0], sizeof(DebugMetaData) * debug.size());

		// return calls
		while (!returns.empty()) {
			(*func)->func->nodes[returns.front()] = (long)(*func)->func->count - returns.front();
			returns.erase(returns.begin());
		}

		// variable count
		(*func)->func->varc = (*func)->vars.size();

		// now check if function is valid with the user handler
		if (handler && !handler->HandleFunction((*func)->func, (*func)->pub)) {
			Error(BaseString("Rejected function ") + IDToName((*func)->name));
			return -1;
		}
	}

	// compile type method extensions
	for (ExtendList::iterator extend = extends.begin(); extend != extends.end(); ++extend) {
		for (CompilerExtend::MethodList::iterator func = (*extend)->methods.begin(); func != (*extend)->methods.end(); ++func) {
			// setup vararg
			if ((*func)->varg)
				(*func)->vars.push_back((*func)->varg);

			// optimize
			(*func)->body = sxp_transform ((*func)->body);

			// reset file/line
			debug.clear();
			last_line = line;
			last_op = 0;

			// compile
			if (!CompileNode (*func, (*func)->body))
				return -1; // failed
			(*func)->func->AddValue(Nil);
			debug.push_back(DebugMetaData((*func)->func->count - last_op, last_line));
			(*func)->func->debug = (DebugMetaData*)GC_MALLOC(sizeof(DebugMetaData) * debug.size());
			memcpy((*func)->func->debug, &debug[0], sizeof(DebugMetaData) * debug.size());

			// return calls
			while (!returns.empty()) {
				(*func)->func->nodes[returns.front()] = (long)(*func)->func->count - returns.front();
				returns.erase(returns.begin());
			}

			// variable count
			(*func)->func->varc = (*func)->vars.size();

			// now check if the method is valid with the user handler
			if (handler && !handler->HandleExtend((*extend)->type, (*func)->func)) {
				Error(BaseString("Rejected extended method ") + IDToName((*func)->name));
				return -1;
			}
		}
	}

	// everything went right, extend types
	for (ExtendList::iterator extend = extends.begin(); extend != extends.end(); ++extend) {
		for (CompilerExtend::MethodList::iterator func = (*extend)->methods.begin(); func != (*extend)->methods.end(); ++func) {
			(*extend)->type->AddMethod((*func)->func->id, (*func)->func);
		}
	}

	// everything went right, publicize
	for (FunctionList::iterator func = funcs.begin(); func != funcs.end(); ++func) {
		// make public if public
		if ((*func)->pub)
			GetSystem()->AddFunction((*func)->func);
	}

	return 0;
}
