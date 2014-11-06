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
#include <stdlib.h>
#include <string.h>

#include <algorithm>

#include "scriptix.h"
#include "system.h"

using namespace Scriptix;

#include "parser.h"

int
System::AddFunctionTag (NameID name)
{
	// allocate
	tags.push_back(name);
	return SXE_OK;
}

bool
System::ValidFunctionTag (NameID name) 
{
	// search tags
	return (std::find(tags.begin(), tags.end(), name) != tags.end());
}


void
ParserState::Error(const std::string& msg)
{
	if (system->error_hook != NULL) {
		system->error_hook (file ? ((String*)file)->GetCStr(): "<input>", line, msg.c_str());
	}
}

Scriptix::ParserState::ParserState(System* s_system) : funcs(), returns(), blocks(), gnames()
{
	system = s_system;
	nodes = NULL;
	file = new String(system, "<input>");
	last_file = NULL;
	last_line = 1;
	line = 1;
	globals = NULL;
}

Scriptix::ParserState::~ParserState(void)
{
	ParserNode* nnext;

	while (nodes != NULL) {
		nnext = nodes->inext;
		delete nodes;
		nodes = nnext;
	}

	while (!funcs.empty()) {
		delete funcs.front();
		funcs.erase(funcs.begin());
	}

	while (!extends.empty()) {
		while (!extends.back()->methods.empty()) {
			delete extends.back()->methods.back();
			extends.back()->methods.pop_back();
		}
		delete extends.back();
		extends.pop_back();
	}

	/* free jumps */
	while (!blocks.empty())
		PopBlock ();
}

ParserFunction *
Scriptix::ParserState::AddFunc(NameID name, const NameList& args, NameID varg, ParserNode* body, NameID tag, bool pub)
{
	ParserFunction *func = new ParserFunction();
	if (!func)
		return NULL;

	func->name = name;
	func->vars = args; /* arguments become variables... */
	func->varg = varg;
	func->body = body;
	func->pub = pub;
	func->tag = tag;

	funcs.push_back(func);

	return func;
}

// add a new type extension
ParserExtend*
Scriptix::ParserState::AddExtend(Type* type)
{
	ParserExtend* extend = new ParserExtend();
	if (extend == NULL)
		return NULL;

	extend->type = type;

	extends.push_back(extend);
	return extend;
}

// add a function to a typ extension
ParserFunction*
Scriptix::ParserState::AddExtendFunc(NameID name, const NameList& args, NameID varg, ParserNode* body)
{
	if (extends.empty())
		return NULL;

	ParserFunction* func = new ParserFunction();
	if (!func)
		return NULL;

	func->name = name;
	func->vars = args; /* arguments become variables... */
	func->varg = varg;
	func->body = body;
	func->pub = false;
	func->tag = 0;

	extends.back()->methods.push_back(func);
	return func;
}

// add block to state
bool
ParserState::PushBlock (Function* func)
{
	ParserBlock *block = new ParserBlock;
	if (!block)
		return false;

	// data
	block->func = func;
	block->start = func->count;

	blocks.push_back(block);

	return true;
}

// pop block from state
void
ParserState::PopBlock (void)
{
	if (blocks.empty())
		return;

	// breaks
	while (!blocks.back()->breaks.empty()) {
		blocks.back()->func->nodes[blocks.back()->breaks.front()] = (long)blocks.back()->func->count - blocks.back()->breaks.front();
		blocks.back()->breaks.erase(blocks.back()->breaks.begin());
	}

	// continues
	while (!blocks.back()->continues.empty()) {
		blocks.back()->func->nodes[blocks.back()->continues.front()] = (long)blocks.back()->start - blocks.back()->continues.front();
		blocks.back()->continues.erase(blocks.back()->continues.begin());
	}

	blocks.pop_back();
}

// add a break command
bool
ParserState::AddBreak (void)
{
	if (blocks.empty()) {
		Error("Break outside of loop");
		return false;
	}
	
	blocks.back()->func->AddOpcode(system, OP_JUMP);
	blocks.back()->breaks.push_back(blocks.back()->func->count);
	blocks.back()->func->AddOparg(system, 0);

	return true;
}

// add a break command when test is true
bool
ParserState::AddBreakOnTrue (void)
{
	if (blocks.empty()) {
		Error("Break outside of loop");
		return false;
	}
	
	blocks.back()->func->AddOpcode(system, OP_TJUMP);
	blocks.back()->breaks.push_back(blocks.back()->func->count);
	blocks.back()->func->AddOparg(system, 0);

	return true;
}

// add a break command when test is fasle
bool
ParserState::AddBreakOnFalse (void)
{
	if (blocks.empty()) {
		Error("Break outside of loop");
		return false;
	}
	
	blocks.back()->func->AddOpcode(system, OP_FJUMP);
	blocks.back()->breaks.push_back(blocks.back()->func->count);
	blocks.back()->func->AddOparg(system, 0);

	return true;
}

// add a contineu command
bool
ParserState::AddContinue (void)
{
	if (blocks.empty()) {
		Error("Continue outside of loop");
		return false;
	}

	blocks.back()->func->AddOpcode(system, OP_JUMP);
	blocks.back()->func->AddOparg(system, (long)blocks.back()->start - blocks.back()->func->count);

	return true;
}

long
ParserState::AddVar(ParserFunction* func, NameID id)
{
	func->vars.push_back(id);
	return func->vars.size() - 1;
}

long
ParserState::GetVar(ParserFunction* func, NameID id)
{
	if (func->vars.empty()) {
		return -1;
	} else {
		size_t index = 0;
		while (index < func->vars.size()) {
			if (func->vars[index] == id)
				return index;
			++ index;
		}
		return -1;
	}
}

void
ParserState::SetGlobal(NameID id, Value* value)
{
	if (GetGlobal(id) >= 0) {
		Error("Redefined global");
		return;
	}

	if (globals == NULL) {
		globals = new Array(system, 1, &value);
	} else {
		List::Append(system, globals, value);
	}
	gnames.push_back(id);
}

long
ParserState::GetGlobal(NameID id)
{
	size_t index;
	for (index = 0; index < gnames.size(); ++ index) {
		if (gnames[index] == id) {
			return index;
		}
	}
	return -1;
}

ParserNode::ParserNode(Scriptix::ParserState* s_info,
		int s_type,
		ParserNode* s_node0,
		ParserNode* s_node1,
		ParserNode* s_node2,
		ParserNode* s_node3,
		NameID s_name0,
		NameID s_name1,
		Value* s_value,
		int s_op)
{
	info = s_info;
	type = s_type;
	next = NULL;
	
	file = info->file;
	line = info->line;

	inext = info->nodes;
	info->nodes = this;

	parts.nodes[0] = s_node0;
	parts.nodes[1] = s_node1;
	parts.nodes[2] = s_node2;
	parts.nodes[3] = s_node3;
	parts.names[0] = s_name0;
	parts.names[1] = s_name1;
	parts.value = s_value;
	parts.op = s_op;
}

ParserNode* 
ParserNode::Append(ParserNode* node) {
	ParserNode* i;

	for (i = this; i->next != NULL; i = i->next)
		;
	i->next = node;

	return this;
}
