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
sxp_error (SXP_INFO* info, const char *msg) {
	if (info->system->error_hook != NULL) {
		info->system->error_hook (info->file ? ((String*)info->file)->GetStr(): "<input>", info->line, msg);
	}
}

SXP_INFO* 
sxp_new_info (System* system) {
	SXP_INFO* info = (SXP_INFO*)malloc (sizeof (SXP_INFO));
	if (!info)
		return NULL;

	info->system = system;
	info->nodes = NULL;
	info->funcs = NULL;
	info->blocks = NULL;
	info->file = String::Create(system, "<input>");
	info->last_file = NULL;
	info->last_line = 1;
	info->line = 1;
	info->returns = NULL;
	info->globals = NULL;
	info->gnames = NULL;

	return info;
}

void
sxp_del_info (SXP_INFO* info) {
	SXP_NODE* nnext;
	SXP_FUNC *fnext;

	while (info->nodes != NULL) {
		nnext = info->nodes->inext;
		free (info->nodes);
		info->nodes = nnext;
	}

	while (info->funcs != NULL) {
		fnext = info->funcs->next;
		sxp_del_func (info->funcs);
		info->funcs = fnext;
	}

	/* free jumps */
	while (info->blocks)
		sxp_pop_block (info, NULL, 0, 0);

	/* free global names */
	if (info->gnames)
		sx_free_namelist (info->gnames);

	free (info);
}

SXP_FUNC *
sxp_new_func (SXP_INFO* info, sx_name_id name, sx_name_id* args, sx_name_id varg, SXP_NODE* body, const char *tag, char pub) {
	SXP_FUNC *func = (SXP_FUNC*)malloc (sizeof (SXP_FUNC));
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

	func->next = info->funcs;
	info->funcs = func;

	return func;
}

SXP_FUNC *
sxp_new_anon_func (SXP_INFO* info, sx_name_id* args, sx_name_id varg, SXP_NODE* body) {
	SXP_FUNC *func = (SXP_FUNC*)malloc (sizeof (SXP_FUNC));
	if (!func)
		return NULL;

	func->name = 0;
	func->vars = args; /* arguments become variables... */
	func->varg = varg;
	func->body = body;
	func->pub = 0;
	func->tag = NULL;

	func->next = info->funcs;
	info->funcs = func;

	return func;
}

void
sxp_del_func (SXP_FUNC *func) {
	if (func->tag)
		free (func->tag);
	if (func->vars)
		free (func->vars);
	free (func);
}

long
sxp_add_var (SXP_INFO* info, SXP_FUNC* func, sx_name_id id)
{
	if (func->vars == NULL) {
		func->vars = sx_new_namelist (info->system, 1, id);
		return 0;
	} else {
		func->vars = sx_namelist_append (info->system, func->vars, id);
		return sx_sizeof_namelist(func->vars) - 1;
	}
}

long
sxp_get_var (SXP_INFO* info, SXP_FUNC* func, sx_name_id id)
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

SXP_JUMP *
sxp_new_break (SXP_INFO* info, unsigned long loc) {
	SXP_JUMP *jump;
	
	if (!info->blocks) {
		sxp_error (info, "Break outside of loop");
		return NULL;
	}
	
	jump = (SXP_JUMP*)malloc (sizeof (SXP_JUMP));
	if (jump == NULL)
		return NULL;

	jump->loc = loc + 1;

	jump->next = info->blocks->breaks;
	info->blocks->breaks = jump;

	return jump;
}

SXP_JUMP *
sxp_new_continue (SXP_INFO* info, unsigned long loc) {
	SXP_JUMP *jump;

	if (!info->blocks) {
		sxp_error (info, "Continue outside of loop");
		return NULL;
	}
	
	jump = (SXP_JUMP*)malloc (sizeof (SXP_JUMP));
	if (jump == NULL)
		return NULL;

	jump->loc = loc + 1;

	jump->next = info->blocks->continues;
	info->blocks->continues = jump;

	return jump;
}

SXP_JUMP *
sxp_new_return (SXP_INFO* info, unsigned long loc) {
	SXP_JUMP *jump = (SXP_JUMP*)malloc (sizeof (SXP_JUMP));
	if (jump == NULL)
		return NULL;

	jump->loc = loc + 1;

	jump->next = info->returns;
	info->returns = jump;

	return jump;
}

SXP_BLOCK *
sxp_push_block (SXP_INFO* info) {
	SXP_BLOCK *block = (SXP_BLOCK*)malloc (sizeof (SXP_BLOCK));
	if (!block)
		return NULL;

	block->continues = NULL;
	block->breaks = NULL;

	block->next = info->blocks;
	info->blocks = block;

	return block;
}

void
sxp_pop_block (SXP_INFO* info, Function* func, unsigned long bloc, unsigned long cloc) {
	SXP_JUMP *next;
	SXP_BLOCK *bnext;

	if (!info->blocks)
		return;

	while (info->blocks->breaks) {
		next = info->blocks->breaks->next;
		if (func)
			func->nodes[info->blocks->breaks->loc] = (long)Number::Create ((long)bloc);
		free (info->blocks->breaks);
		info->blocks->breaks = next;
	}

	while (info->blocks->continues) {
		next = info->blocks->continues->next;
		if (func)
			func->nodes[info->blocks->continues->loc] = (long)Number::Create ((long)cloc);
		free (info->blocks->continues);
		info->blocks->continues = next;
	}

	bnext = info->blocks->next;
	free (info->blocks);
	info->blocks = bnext;
}

void
sxp_do_returns (SXP_INFO* info, Function* func, unsigned long loc) {
	SXP_JUMP *next;

	while (info->returns) {
		next = info->returns->next;
		if (func)
			func->nodes[info->returns->loc] = (long)Number::Create ((long)loc);
		free (info->returns);
		info->returns = next;
	}
}

void
sxp_set_global (SXP_INFO* info, sx_name_id id, Value* value)
{
	if (sxp_get_global (info, id) >= 0) {
		/* FIXME: error */
		return;
	}

	if (info->globals == NULL) {
		info->globals = new Array(info->system, 1, &value);
		info->gnames = sx_new_namelist(info->system, 1, id);
	} else {
		List::Append(info->system, info->globals, value);
		info->gnames = sx_namelist_append(info->system, info->gnames, id);
	}
}

long
sxp_get_global (SXP_INFO* info, sx_name_id id)
{
	size_t index;
	for (index = 0; index < sx_sizeof_namelist(info->gnames); ++ index) {
		if (info->gnames[index] == id) {
			return index;
		}
	}
	return -1;
}

/* allocate */
SXP_NODE* 
_sxp_new_node (SXP_INFO* info, int type) {
	SXP_NODE* node = (SXP_NODE*)malloc (sizeof (SXP_NODE));
	if (node == NULL)
		return NULL;

	node->info = info;
	node->type = type;
	node->next = NULL;
	node->inext = info->nodes;
	node->file = info->file;
	node->line = info->line;
	info->nodes = node;
	return node;
}

SXP_NODE* 
sxp_new_math (SXP_INFO* info, int op, SXP_NODE* left, SXP_NODE* right) {
	SXP_NODE* node = _sxp_new_node (info, SXP_MATH);

	node->data.math.op = op;
	node->data.math.left = left;
	node->data.math.right = right;

	return node;
}

SXP_NODE* 
sxp_new_data (SXP_INFO* info, Value* value) {
	SXP_NODE* node = _sxp_new_node (info, SXP_DATA);
	node->data.data = value;
	return node;
}

SXP_NODE* 
sxp_new_nega (SXP_INFO* info, SXP_NODE* node) {
	/* hack to speed up negative numbers */
	if (node->type == SXP_DATA && Value::IsA<Number>(node->data.data)) {
		node->data.data = Number::Create (- Number::ToInt (node->data.data));
		return node;
	} else {
		SXP_NODE* ret = _sxp_new_node (info, SXP_NEGA);
		ret->data.node = node;
		return ret;
	}
}

SXP_NODE* 
sxp_new_nodet (SXP_INFO* info, SXP_NODE* node, int t) {
	SXP_NODE* ret = _sxp_new_node (info, t);
	ret->data.node = node;
	return ret;
}

SXP_NODE* 
sxp_new_logic (SXP_INFO* info, SXP_NODE* left, SXP_NODE* right, int t) {
	SXP_NODE* ret = _sxp_new_node (info, t);
	ret->data.logic.left = left;
	ret->data.logic.right = right;
	return ret;
}

SXP_NODE* 
sxp_new_call (SXP_INFO* info, SXP_NODE* expr, SXP_NODE* args) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_CALL);
	ret->data.call.expr = expr;
	ret->data.call.args = args;
	return ret;
}

SXP_NODE* 
sxp_new_assi (SXP_INFO* info, sx_name_id name, SXP_NODE* node) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_ASSI);
	ret->data.assi.name = name;
	ret->data.assi.node = node;
	return ret;
}

SXP_NODE* 
sxp_new_stmt (SXP_INFO* info, SXP_NODE* node) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_STMT);
	ret->data.node = node;
	return ret;
}

SXP_NODE* 
sxp_new_if (SXP_INFO* info, SXP_NODE* test, SXP_NODE* th, SXP_NODE* el) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_IF);
	ret->data.ifd.test = test;
	ret->data.ifd.el = el;
	ret->data.ifd.th = th;
	return ret;
}

SXP_NODE* 
sxp_new_whil (SXP_INFO* info, SXP_NODE* test, SXP_NODE* block, int type) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_WHIL);
	ret->data.whil.test = test;
	ret->data.whil.block = block;
	ret->data.whil.type = type;
	return ret;
}

SXP_NODE* 
sxp_new_set (SXP_INFO* info, SXP_NODE* array, SXP_NODE* index, SXP_NODE* value) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_SET);
	ret->data.set.array = array;
	ret->data.set.index = index;
	ret->data.set.node = value;
	return ret;
}

SXP_NODE* 
sxp_new_indx (SXP_INFO* info, SXP_NODE* array, SXP_NODE* index) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_INDX);
	ret->data.set.array = array;
	ret->data.set.index = index;
	return ret;
}

SXP_NODE* 
sxp_new_inc (SXP_INFO* info, sx_name_id name, SXP_NODE* amount, int type) {
	SXP_NODE* ret = _sxp_new_node (info, type);
	ret->data.inc.name = name;
	ret->data.inc.amount = amount;
	return ret;
}

SXP_NODE* 
sxp_new_retr (SXP_INFO* info, SXP_NODE* node) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_RETR);
	ret->data.node = node;
	return ret;
}

SXP_NODE* 
sxp_new_brak (SXP_INFO* info) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_BRAK);
	return ret;
}

SXP_NODE* 
sxp_new_cont (SXP_INFO* info) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_CONT);
	return ret;
}

SXP_NODE* 
sxp_new_meth (SXP_INFO* info, SXP_NODE* base, sx_name_id name, SXP_NODE* node) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_METH);
	ret->data.meth.base = base;
	ret->data.meth.name = name;
	ret->data.meth.node = node;
	return ret;
}

SXP_NODE* 
sxp_new_cast (SXP_INFO* info, SXP_NODE* node, sx_name_id name) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_CAST);
	ret->data.cast.node = node;
	ret->data.cast.name = name;
	return ret;
}

SXP_NODE* 
sxp_new_cfor (SXP_INFO* info, SXP_NODE* start, SXP_NODE* test, SXP_NODE* inc, SXP_NODE* body) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_CFOR);
	ret->data.cfor.start = start;
	ret->data.cfor.test = test;
	ret->data.cfor.inc = inc;
	ret->data.cfor.body = body;
	return ret;
}

SXP_NODE* 
sxp_new_smet (SXP_INFO* info, sx_name_id type, sx_name_id func, SXP_NODE* args) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_SMET);
	ret->data.smet.type = type;
	ret->data.smet.func = func;
	ret->data.smet.args = args;
	return ret;
}

SXP_NODE* 
sxp_new_supr (SXP_INFO* info, SXP_NODE* args) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_SUPR);
	ret->data.call.args = args;
	return ret;
}

SXP_NODE* 
sxp_new_yeld (SXP_INFO* info) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_YELD);
	return ret;
}

SXP_NODE* 
sxp_new_name_t (SXP_INFO* info, sx_name_id name, int type) {
	SXP_NODE* ret = _sxp_new_node (info, type);
	ret->data.name = name;
	return ret;
}

SXP_NODE*
sxp_new_afnc (SXP_INFO* info, SXP_FUNC* func)
{
	SXP_NODE* ret = _sxp_new_node (info, SXP_AFNC);
	ret->data.func = func;
	return ret;
}

SXP_NODE*
sxp_new_clos (SXP_INFO* info, SXP_FUNC* func, SXP_NODE* args)
{
	SXP_NODE* ret = _sxp_new_node (info, SXP_CLOS);
	ret->data.clos.func = func;
	ret->data.clos.args = args;
	return ret;
}

SXP_NODE*
sxp_new_node (SXP_INFO* info, int op, SXP_NODE* nodea, SXP_NODE* nodeb, SXP_NODE* nodec, SXP_NODE* noded)
{
	SXP_NODE* ret = _sxp_new_node (info, op);
	ret->data.nodes.nodea = nodea;
	ret->data.nodes.nodeb = nodeb;
	ret->data.nodes.nodec = nodec;
	ret->data.nodes.noded = noded;
	return ret;
}

SXP_NODE* 
sxp_new_name (SXP_INFO* info, sx_name_id name) {
	SXP_NODE* ret = _sxp_new_node (info, SXP_NAME_DATA);
	ret->data.name = name;
	return ret;
}

SXP_NODE* 
sxp_append (SXP_NODE* base, SXP_NODE* add) {
	SXP_NODE* i;

	if (base == NULL)
		return NULL;

	for (i = base; i->next != NULL; i = i->next)
		;
	i->next = add;

	return base;
}
