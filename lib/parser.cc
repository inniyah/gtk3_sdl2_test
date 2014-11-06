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

#include "scriptix.h"
#include "system.h"

using namespace Scriptix;

#include "parser.h"

int
System::AddFunctionTag (const char* name)
{
	// allocate
	Tag* tag = new Tag();
	if (tag == NULL)
		return SXE_NOMEM;

	// copy name
	tag->name = strdup(name);
	if (tag->name == NULL) {
		delete tag;
		return SXE_NOMEM;
	}

	// add to list
	tag->next = tags;
	tags = tag;

	return SXE_OK;
}

bool
System::ValidFunctionTag (const char *name) 
{
	// search tags
	Tag* tag = tags;
	while (tag != NULL) {
		if (!strcmp (name, tag->name))
			return true;
		tag = tag->next;
	}

	return false;
}


void
ParserState::Error(const char *msg)
{
	if (system->error_hook != NULL) {
		system->error_hook (file ? ((String*)file)->GetStr(): "<input>", line, msg);
	}
}

Scriptix::ParserState::ParserState(System* s_system)
{
	system = s_system;
	nodes = NULL;
	funcs = NULL;
	blocks = NULL;
	file = String::Create(system, "<input>");
	last_file = NULL;
	last_line = 1;
	line = 1;
	globals = NULL;
	gnames = NULL;
}

Scriptix::ParserState::~ParserState(void)
{
	ParserNode* nnext;
	ParserFunction *fnext;

	while (nodes != NULL) {
		nnext = nodes->inext;
		free (nodes);
		nodes = nnext;
	}

	while (funcs != NULL) {
		fnext = funcs->next;
		DelFunc (funcs);
		funcs = fnext;
	}

	/* free jumps */
	while (blocks)
		PopBlock ();

	/* free global names */
	if (gnames)
		sx_free_namelist (gnames);
}

ParserFunction *
Scriptix::ParserState::AddFunc(sx_name_id name, sx_name_id* args, sx_name_id varg, ParserNode* body, const char *tag, char pub)
{
	ParserFunction *func = (ParserFunction*)malloc (sizeof (ParserFunction));
	if (!func)
		return NULL;

	func->name = name;
	func->vars = args; /* arguments become variables... */
	func->varg = varg;
	func->body = body;
	func->pub = pub;
	func->tag = NULL;
	if (tag)
		func->tag = strdup (tag);

	func->next = funcs;
	funcs = func;

	return func;
}

void
Scriptix::ParserState::DelFunc(ParserFunction* func)
{
	if (func->tag)
		free (func->tag);
	if (func->vars)
		free (func->vars);
	free (func);
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

	block->next = blocks;
	blocks = block;

	return true;
}

// pop block from state
void
ParserState::PopBlock (void)
{
	ParserBlock *bnext;

	if (!blocks)
		return;

	// breaks
	while (!blocks->breaks.empty()) {
		blocks->func->nodes[blocks->breaks.front()] = (long)blocks->func->count - blocks->breaks.front();
		blocks->breaks.erase(blocks->breaks.begin());
	}

	// continues
	while (!blocks->continues.empty()) {
		blocks->func->nodes[blocks->continues.front()] = (long)blocks->start - blocks->continues.front();
		blocks->continues.erase(blocks->continues.begin());
	}

	bnext = blocks->next;
	delete blocks;
	blocks = bnext;
}

// add a break command
bool
ParserState::AddBreak (void)
{
	if (!blocks) {
		Error("Break outside of loop");
		return false;
	}
	
	blocks->func->AddOpcode(system, SX_OP_JUMP);
	blocks->breaks.push_back(blocks->func->count);
	blocks->func->AddOparg(system, 0);

	return true;
}

// add a break command when test is true
bool
ParserState::AddBreakOnTrue (void)
{
	if (!blocks) {
		Error("Break outside of loop");
		return false;
	}
	
	blocks->func->AddOpcode(system, SX_OP_TJUMP);
	blocks->breaks.push_back(blocks->func->count);
	blocks->func->AddOparg(system, 0);

	return true;
}

// add a break command when test is fasle
bool
ParserState::AddBreakOnFalse (void)
{
	if (!blocks) {
		Error("Break outside of loop");
		return false;
	}
	
	blocks->func->AddOpcode(system, SX_OP_FJUMP);
	blocks->breaks.push_back(blocks->func->count);
	blocks->func->AddOparg(system, 0);

	return true;
}

// add a contineu command
bool
ParserState::AddContinue (void)
{
	if (!blocks) {
		Error("Continue outside of loop");
		return false;
	}

	blocks->func->AddOpcode(system, SX_OP_JUMP);
	blocks->func->AddOparg(system, (long)blocks->start - blocks->func->count);

	return true;
}

long
ParserState::AddVar(ParserFunction* func, sx_name_id id)
{
	if (func->vars == NULL) {
		func->vars = sx_new_namelist (system, 1, id);
		return 0;
	} else {
		func->vars = sx_namelist_append (system, func->vars, id);
		return sx_sizeof_namelist(func->vars) - 1;
	}
}

long
ParserState::GetVar(ParserFunction* func, sx_name_id id)
{
	if (func->vars == NULL) {
		return -1;
	} else {
		long index = 0;
		while (func->vars[index] != 0) {
			if (func->vars[index] == id)
				return index;
			++ index;
		}
		return -1;
	}
}

void
ParserState::SetGlobal(sx_name_id id, Value* value)
{
	if (GetGlobal(id) >= 0) {
		Error("Redefined global");
		return;
	}

	if (globals == NULL) {
		globals = new Array(system, 1, &value);
		gnames = sx_new_namelist(system, 1, id);
	} else {
		List::Append(system, globals, value);
		gnames = sx_namelist_append(system, gnames, id);
	}
}

long
ParserState::GetGlobal(sx_name_id id)
{
	size_t index;
	for (index = 0; index < sx_sizeof_namelist(gnames); ++ index) {
		if (gnames[index] == id) {
			return index;
		}
	}
	return -1;
}

ParserNode*
sxp_new_node (Scriptix::ParserState* info,
		int type,
		ParserNode* node0,
		ParserNode* node1,
		ParserNode* node2,
		ParserNode* node3,
		sx_name_id name0,
		sx_name_id name1,
		Value* value,
		int op)
{
	ParserNode* node = (ParserNode*)malloc (sizeof (ParserNode));
	if (node == NULL)
		return NULL;

	node->info = info;
	node->type = type;
	node->next = NULL;
	
	node->file = info->file;
	node->line = info->line;

	node->inext = info->nodes;
	info->nodes = node;

	node->parts.nodes[0] = node0;
	node->parts.nodes[1] = node1;
	node->parts.nodes[2] = node2;
	node->parts.nodes[3] = node3;
	node->parts.names[0] = name0;
	node->parts.names[1] = name1;
	node->parts.value = value;
	node->parts.op = op;

	return node;
}

ParserNode* 
sxp_append (ParserNode* base, ParserNode* add) {
	ParserNode* i;

	if (base == NULL)
		return NULL;

	for (i = base; i->next != NULL; i = i->next)
		;
	i->next = add;

	return base;
}
