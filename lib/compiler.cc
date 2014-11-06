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

#include <stdio.h>
#include <stdarg.h>

#include "scriptix.h"
using namespace Scriptix;

#include "parser.h"

#define _test(expr) {if(!(expr)) return false;}

static
void
_sxp_node_error (ParserNode* node, const char *msg, ...)
{
	char buffer[512];
	va_list va;

	va_start (va, msg);
	vsnprintf (buffer, sizeof(buffer), msg, va);
	va_end (va);

	if (node->info->system->error_hook != NULL) {
		node->info->system->error_hook (node->file ? ((String*)node->file)->GetCStr() : "<input>", node->line, buffer);
	}
}

static
int
_sxp_count (ParserNode *node) {
	int i = 0;
	while (node != NULL) {
		++ i;
		node = node->next;
	}
	return i;
}

static
void
_sxp_put_line (ParserFunction* func, ParserNode *node) {
	func->func->AddValue(node->info->system, (Value*)node->file);
	func->func->AddValue(node->info->system, Number::Create (node->line));
	func->func->AddOpcode(node->info->system, SX_OP_SETFILELINE);
}

bool
ParserState::CompileNode (ParserFunction* func, ParserNode *node) {
	// for the jumps necessary
	unsigned long pos;
	unsigned long pos2;

	while (node != NULL) {
		// output debug info
		if (node->file != last_file) {
			_sxp_put_line (func, node);
		} else if (node->line == last_line + 1) {
			func->func->AddOpcode(system, SX_OP_NEXTLINE);
		} else if (node->line != last_line) {
			_sxp_put_line (func, node);
		}

		// store line
		last_file = node->file;
		last_line = node->line;

		switch (node->type) {
			case SXP_MATH:
				_test(CompileNode (func, node->parts.nodes[0]))
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(system, (sx_op_type)node->parts.op);
				break;
			case SXP_DATA:
				func->func->AddValue(system, node->parts.value);
				break;
			case SXP_NEGATE:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_NEGATE);
				break;
			case SXP_NOT:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_NOT);
				break;
			case SXP_OR:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_TEST);
				func->func->AddOpcode(system, SX_OP_TJUMP);
				pos = func->func->count;
				func->func->AddOparg(system, 0);
				func->func->AddOpcode(system, SX_OP_POP);
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->nodes[pos] = func->func->count - pos;
				break;
			case SXP_AND:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_TEST);
				func->func->AddOpcode(system, SX_OP_FJUMP);
				pos = func->func->count;
				func->func->AddOparg(system, 0);
				func->func->AddOpcode(system, SX_OP_POP);
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->nodes[pos] = func->func->count - pos;
				break;
			case SXP_INVOKE:
				_test(CompileNode (func, node->parts.nodes[1]))
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_INVOKE);
				func->func->AddOparg (system, _sxp_count (node->parts.nodes[1]));
				break;
			case SXP_LOOKUP:
			{
				Value* lfunc;
				ParserFunction* dfunc;
				Value* gval;
				char found = 0;
				long index;

				// do variable lookup
				index = GetVar(func, node->parts.names[0]);
				if (index >= 0) {
					func->func->AddOpcode(system, SX_OP_LOOKUP);
					func->func->AddOparg(system, index);
					break;
				}

				// search for function
				for (dfunc = funcs; dfunc != NULL; dfunc = dfunc->next) {
					if (dfunc->name == node->parts.names[0]) {
						func->func->AddValue(system, SX_TOVALUE(dfunc->func));
						found = 1;
						break;
					}
				}
				// found, done, ok
				if (found) {
					break;
				}

				// external function?
				lfunc = system->GetFunction(node->parts.names[0]);
				if (lfunc) {
					// add function
					func->func->AddValue(system, lfunc);
					break;
				}

				// global variable?
				index = GetGlobal(node->parts.names[0]);
				if (index >= 0) {
					func->func->AddValue(system, globals);
					func->func->AddValue(system, Number::Create(index));
					func->func->AddOpcode(system, SX_OP_INDEX);
					break;
				}

				// global constant?
				gval = system->GetGlobal(node->parts.names[0]);
				if (gval) {
					func->func->AddValue(system, gval);
					break;
				}

				// failure...
				_sxp_node_error (node, "Unknown identifier '%s'", IDToName (node->parts.names[0]));
				return false;
			}
			case SXP_ASSIGN:
			{
				long index = GetVar(func, node->parts.names[0]);
				if (index < 0) {
					// global variable?
					index = GetGlobal(node->parts.names[0]);
					if (index >= 0) {
						// do a lookup
						func->func->AddValue(system, SX_TOVALUE(globals));
						func->func->AddValue(system, Number::Create(index));
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(system, SX_OP_SETINDEX);
						break;
						
					}
					index = AddVar(func, node->parts.names[0]);
				}
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_ASSIGN);
				func->func->AddOparg(system, index);
				break;
			}
			case SXP_STATEMENT:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_POP);
				break;
			case SXP_IF:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_TEST);
				func->func->AddOpcode(system, SX_OP_POP);
				func->func->AddOpcode(system, SX_OP_FJUMP);
				pos = func->func->count;
				func->func->AddOparg(system, 0);
				_test(CompileNode (func, node->parts.nodes[1]))
				if (node->parts.nodes[2]) { // else
					func->func->AddOpcode(system, SX_OP_JUMP);
					pos2 = func->func->count;
					func->func->AddOparg(system, 0);
					func->func->nodes[pos] = func->func->count - pos;
					_test(CompileNode (func, node->parts.nodes[2]))
					func->func->nodes[pos2] = func->func->count - pos2;
				} else {
					func->func->nodes[pos] = func->func->count - pos;
				}
				break;
			case SXP_LOOP:
				PushBlock(func->func);
				_sxp_put_line (func, node);
				switch (node->parts.op) {
					case SXP_LOOP_WHILE:
						// while... do - test true, loop
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(system, SX_OP_TEST);
						func->func->AddOpcode(system, SX_OP_POP);
						_test(AddBreakOnFalse())
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(AddContinue())
						break;
					case SXP_LOOP_UNTIL:
						// until... do - test false, loop
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(system, SX_OP_TEST);
						func->func->AddOpcode(system, SX_OP_POP);
						_test(AddBreakOnTrue())
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(AddContinue())
						break;
					case SXP_LOOP_DOWHILE:
						// do... while - loop, test true
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(system, SX_OP_TEST);
						func->func->AddOpcode(system, SX_OP_POP);
						func->func->AddOpcode(system, SX_OP_TJUMP);
						func->func->AddOparg(system, BlockStart() - func->func->count);
						break;
					case SXP_LOOP_DOUNTIL:
						// do... until - loop, test false
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(CompileNode (func, node->parts.nodes[0]))
						func->func->AddOpcode(system, SX_OP_TEST);
						func->func->AddOpcode(system, SX_OP_POP);
						func->func->AddOpcode(system, SX_OP_FJUMP);
						func->func->AddOparg(system, BlockStart() - func->func->count);
						break;
					case SXP_LOOP_FOREVER:
						// permanent loop - loop
						_test(CompileNode (func, node->parts.nodes[1]))
						_test(AddContinue())
						break;
				}
				PopBlock();
				break;
			case SXP_SETINDEX:
				_test(CompileNode (func, node->parts.nodes[0]))
				_test(CompileNode (func, node->parts.nodes[1]))
				_test(CompileNode (func, node->parts.nodes[2]))
				func->func->AddOpcode(system, SX_OP_SETINDEX);
				break;
			case SXP_GETINDEX:
				_test(CompileNode (func, node->parts.nodes[0]))
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(system, SX_OP_INDEX);
				break;
			case SXP_ARRAY:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_NEWARRAY);
				func->func->AddOparg(system, _sxp_count(node->parts.nodes[0]));
				break;
			case SXP_PREINC:
			{
				long index;
				// do variable lookup
				index = GetVar(func, node->parts.names[0]);
				if (index < 0) {
					_sxp_node_error (node, "Undefined variable '%s'", IDToName (node->parts.names[0]));
					break;
				}

				func->func->AddValue(system, Number::Create (index));
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_PREINCREMENT);
				break;
			}
			case SXP_POSTINC:
			{
				long index;
				// do variable lookup
				index = GetVar(func, node->parts.names[0]);
				if (index < 0) {
					_sxp_node_error (node, "Undefined variable '%s'", IDToName (node->parts.names[0]));
					break;
				}

				func->func->AddValue(system, Number::Create (index));
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_POSTINCREMENT);
				break;
			}
			case SXP_RETURN:
				if (node->parts.nodes[0] != NULL)
					_test(CompileNode (func, node->parts.nodes[0]))
				else
					func->func->AddValue(system, SX_NIL);
				func->func->AddOpcode(system, SX_OP_JUMP);
				returns.push_back(func->func->count);
				func->func->AddOparg(system, 0);
				break;
			case SXP_BREAK:
				_test(AddBreak())
				break;
			case SXP_CONTINUE:
				_test(AddContinue())
				break;
			case SXP_METHOD:
				if (node->parts.nodes[1])
					_test(CompileNode (func, node->parts.nodes[1]))
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_METHOD);
				func->func->AddOparg (system, node->parts.names[0]);
				func->func->AddOparg (system, _sxp_count (node->parts.nodes[1]));
				break;
			case SXP_CAST:
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddValue(system, new TypeValue (system, system->GetType(node->parts.names[0])));
				func->func->AddOpcode(system, SX_OP_TYPECAST);
				break;
			case SXP_FOR:
				// setup
				_test(CompileNode (func, node->parts.nodes[0]))
				// skip first increment
				func->func->AddOpcode(system, SX_OP_JUMP);
				pos = func->func->count;
				func->func->AddOparg(system, 0);
				// begin loop
				_test(PushBlock(func->func));
				// increment
				_test(CompileNode (func, node->parts.nodes[2]))
				func->func->nodes[pos] = func->func->count - pos;
				_sxp_put_line (func, node);
				// loop test
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(system, SX_OP_TEST);
				func->func->AddOpcode(system, SX_OP_POP);
				_test(AddBreakOnFalse())
				// body
				_test(CompileNode (func, node->parts.nodes[3]))
				// loop
				_test(AddContinue())
				// end
				PopBlock();
				break;
			case SXP_SMETHOD:
				if (node->parts.nodes[0])
					_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddValue(system, new TypeValue (system, system->GetType(node->parts.names[0])));
				func->func->AddOpcode(system, SX_OP_STATIC_METHOD);
				func->func->AddOparg (system, node->parts.names[1]);
				func->func->AddOparg(system, _sxp_count (node->parts.nodes[0]));
				break;
			case SXP_YIELD:
				func->func->AddOpcode(system, SX_OP_YIELD);
				break;
			case SXP_IN:
				// first put in list to check
				if (node->parts.nodes[1]) {
					_test(CompileNode (func, node->parts.nodes[1]))
				} else {
					func->func->AddValue(system, SX_NIL);
				}
				// then put in item to check for
				if (node->parts.nodes[0]) {
					_test(CompileNode (func, node->parts.nodes[0]))
				} else {
					func->func->AddValue(system, SX_NIL);
				}
				// set op
				func->func->AddOpcode(system, SX_OP_IN);
				break;
			case SXP_NEW:
				func->func->AddValue(system, new TypeValue (system, system->GetType(node->parts.names[0])));
				func->func->AddOpcode(system, SX_OP_STATIC_METHOD);
				func->func->AddOparg(system, NameToID("new"));
				func->func->AddOparg(system, 0);
				break;
			case SXP_SETMEMBER:
				// object
				_test(CompileNode (func, node->parts.nodes[0]))
				// value
				_test(CompileNode (func, node->parts.nodes[1]))
				func->func->AddOpcode(system, SX_OP_SET_MEMBER);
				func->func->AddOparg(system, node->parts.names[0]);
				break;
			case SXP_GETMEMBER:
				// object
				_test(CompileNode (func, node->parts.nodes[0]))
				func->func->AddOpcode(system, SX_OP_GET_MEMBER);
				func->func->AddOparg(system, node->parts.names[0]);
				break;
			case SXP_FOREACH:
			{
				// set variable
				long index = GetVar(func, node->parts.names[0]);
				if (index < 0) {
					index = AddVar(func, node->parts.names[0]);
				}

				// set iterator object
				_test(CompileNode (func, node->parts.nodes[0]))
				// set start
				PushBlock(func->func);
				// iterator call
				func->func->AddOpcode(system, SX_OP_ITER);
				func->func->AddOparg(system, index);
				// jump on end
				_test(AddBreakOnFalse())
				// body
				_test(CompileNode (func, node->parts.nodes[1]))
				// jump to begin
				_test(AddContinue())
				// end
				PopBlock();
				func->func->AddOpcode(system, SX_OP_POP);
				break;
			}
			case SXP_CONCAT:
				_test(CompileNode (func, node->parts.nodes[0]));
				_test(CompileNode (func, node->parts.nodes[1]));
				func->func->AddOpcode(system, SX_OP_CONCAT);
				break;

			// NOOP - special
			case SXP_NOOP:
				// ignore
				break;
		}
		node = node->next;
	}

	return true;
}

int
Scriptix::ParserState::Compile(void) {
	ParserFunction *func;

	// make function data
	for (func = funcs; func != NULL; func = func->next) {
		func->func = new Function (system, func->name, sx_sizeof_namelist(func->vars), func->varg);
		if (!func->func) {
			Error("Failed to create function");
			return -1;
		}
	}

	// compile blocks
	for (func = funcs; func != NULL; func = func->next) {
		if (func->varg)
			func->vars = sx_namelist_append(system, func->vars, func->varg);
		func->body = sxp_transform (func->body);
		if (!CompileNode (func, func->body))
			return -1; // failed
		func->func->AddValue(system, SX_NIL);

		// return calls
		while (!returns.empty()) {
			func->func->nodes[returns.front()] = (long)func->func->count - returns.front();
			returns.erase(returns.begin());
		}

		// variable count
		func->func->varc = sx_sizeof_namelist(func->vars);
	}

	// everything went right, publicize
	for (func = funcs; func != NULL; func = func->next) {
		// make public if public
		if (func->pub)
			system->AddFunction(func->func);
	}

	// everything went right, tag callbacks
	for (func = funcs; func != NULL; func = func->next) {
		// gotta tag?  call back
		if (func->tag)
			system->HandleFunctionTag (func->tag, func->func);
	}

	return 0;
}
