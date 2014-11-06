/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, AwesomePlay Productions, Inc.
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
#include <malloc.h>

#include "scriptix.h"
#include "parser.h"

void
sxp_error (SXP_INFO *info, const char *msg) {
	if (info->system->error_hook != NULL) {
		char buffer[512];
		snprintf (buffer, 512, "File %s, line %d: %s", SX_TOSTRING (info->last_file)->str, info->last_line, msg);
		info->system->error_hook (buffer);
	} else {
		fprintf (stderr, "Scriptix Error: File %s, line %d: %s\n", SX_TOSTRING (info->last_file)->str, info->last_line, msg);
	}
}

SXP_INFO *
sxp_new_info (SX_SYSTEM *system) {
	SXP_INFO *info = sx_malloc (system, sizeof (SXP_INFO));
	if (!info)
		return NULL;

	info->system = system;
	info->nodes = NULL;
	info->classes = NULL;
	info->funcs = NULL;
	info->blocks = NULL;
	info->file = sx_new_str (system, "<input>");
	info->last_file = NULL;
	info->last_line = 1;
	info->line = 1;

	return info;
}

void
sxp_del_info (SXP_INFO *info) {
	SXP_NODE *nnext;
	SXP_CLASS *cnext;
	SXP_FUNC *fnext;

	while (info->nodes != NULL) {
		nnext = info->nodes->inext;
		sx_free (info->nodes);
		info->nodes = nnext;
	}

	while (info->classes != NULL) {
		cnext = info->classes->next;
		sxp_del_class (info->classes);
		info->classes = cnext;
	}

	while (info->funcs != NULL) {
		fnext = info->funcs->next;
		sxp_del_func (info->funcs);
		info->funcs = fnext;
	}

	/* free jumps */
	while (info->blocks)
		sxp_pop_block (info, NULL, 0, 0);

	sx_free (info);
}

SXP_CLASS *
sxp_new_class (SXP_INFO *info, sx_name_id name, sx_name_id parent) {
	SXP_CLASS *klass = sx_malloc (info->system, sizeof (SXP_CLASS));
	if (!klass)
		return NULL;

	klass->info = info;
	klass->methods = NULL;
	klass->static_methods = NULL;
	klass->name = name;
	klass->parent = parent;
	klass->next = info->classes;
	info->classes = klass;

	return klass;
}

void
sxp_add_method (SXP_CLASS *klass, sx_name_id name, SX_ARRAY *args, SXP_NODE *body) {
	SXP_FUNC *func = sx_malloc (klass->info->system, sizeof (SXP_FUNC));
	if (!func)
		return;

	func->name = name;
	func->args = args;
	func->body = body;

	func->next = klass->methods;
	klass->methods = func;
}

void
sxp_add_static_method (SXP_CLASS *klass, sx_name_id name, SX_ARRAY *args, SXP_NODE *body) {
	SXP_FUNC *func = sx_malloc (klass->info->system, sizeof (SXP_FUNC));
	if (!func)
		return;

	func->name = name;
	func->args = args;
	func->body = body;

	func->next = klass->static_methods;
	klass->static_methods = func;
}

void
sxp_del_class (SXP_CLASS *klass) {
	SXP_FUNC *next;

	while (klass->methods) {
		next = klass->methods->next;
		sx_free (klass->methods);
		klass->methods = next;
	}

	while (klass->static_methods) {
		next = klass->static_methods->next;
		sx_free (klass->static_methods);
		klass->static_methods = next;
	}

	sx_free (klass);
}

SXP_FUNC *
sxp_new_func (SXP_INFO *info, sx_name_id name, SX_ARRAY *args, SXP_NODE *body) {
	SXP_FUNC *func = sx_malloc (info->system, sizeof (SXP_FUNC));
	if (!func)
		return NULL;

	func->name = name;
	func->args = args;
	func->body = body;

	func->next = info->funcs;
	info->funcs = func;

	return func;
}

void
sxp_del_func (SXP_FUNC *func) {
	sx_free (func);
}

SXP_JUMP *
sxp_new_break (SXP_INFO *info, unsigned long loc) {
	SXP_JUMP *jump;
	
	if (!info->blocks) {
		sxp_error (info, "Break outside of loop");
		return NULL;
	}
	
	jump = sx_malloc (info->system, sizeof (SXP_JUMP));
	if (jump == NULL)
		return NULL;

	jump->loc = loc;

	jump->next = info->blocks->breaks;
	info->blocks->breaks = jump;

	return jump;
}

SXP_JUMP *
sxp_new_continue (SXP_INFO *info, unsigned long loc) {
	SXP_JUMP *jump;

	if (!info->blocks) {
		sxp_error (info, "Continue outside of loop");
		return NULL;
	}
	
	jump = sx_malloc (info->system, sizeof (SXP_JUMP));
	if (jump == NULL)
		return NULL;

	jump->loc = loc;

	jump->next = info->blocks->continues;
	info->blocks->continues = jump;

	return jump;
}

SXP_JUMP *
sxp_new_return (SXP_INFO *info, unsigned long loc) {
	SXP_JUMP *jump = sx_malloc (info->system, sizeof (SXP_JUMP));
	if (jump == NULL)
		return NULL;

	jump->loc = loc;

	jump->next = info->returns;
	info->returns = jump;

	return jump;
}

SXP_BLOCK *
sxp_push_block (SXP_INFO *info) {
	SXP_BLOCK *block = sx_malloc (info->system, sizeof (SXP_BLOCK));
	if (!block)
		return NULL;

	block->continues = NULL;
	block->breaks = NULL;

	block->next = info->blocks;
	info->blocks = block;

	return block;
}

void
sxp_pop_block (SXP_INFO *info, SX_BLOCK *block, unsigned long bloc, unsigned long cloc) {
	SXP_JUMP *next;
	SXP_BLOCK *bnext;

	if (!info->blocks)
		return;

	while (info->blocks->breaks) {
		next = info->blocks->breaks->next;
		if (block)
			block->nodes[info->blocks->breaks->loc].value = sx_new_num ((long)bloc);
		sx_free (info->blocks->breaks);
		info->blocks->breaks = next;
	}

	while (info->blocks->continues) {
		next = info->blocks->continues->next;
		if (block)
			block->nodes[info->blocks->continues->loc].value = sx_new_num ((long)cloc);
		sx_free (info->blocks->continues);
		info->blocks->continues = next;
	}

	bnext = info->blocks->next;
	sx_free (info->blocks);
	info->blocks = bnext;
}

void
sxp_do_returns (SXP_INFO *info, SX_BLOCK *block, unsigned long loc) {
	SXP_JUMP *next;

	while (info->returns) {
		next = info->returns->next;
		if (block)
			block->nodes[info->returns->loc].value = sx_new_num ((long)loc);
		sx_free (info->returns);
		info->returns = next;
	}
}

/* allocate */
SXP_NODE *
_sxp_new_node (SXP_INFO *info, int type) {
	SXP_NODE *node = sx_malloc (info->system, sizeof (SXP_NODE));
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

SXP_NODE *
sxp_new_math (SXP_INFO *info, int op, SXP_NODE *left, SXP_NODE *right) {
	SXP_NODE *node = _sxp_new_node (info, SXP_MATH);

	node->data.math.op = op;
	node->data.math.left = left;
	node->data.math.right = right;

	return node;
}

SXP_NODE *
sxp_new_data (SXP_INFO *info, SX_VALUE *value) {
	SXP_NODE *node = _sxp_new_node (info, SXP_DATA);
	node->data.data = value;
	return node;
}

SXP_NODE *
sxp_new_nodet (SXP_INFO *info, SXP_NODE *node, int t) {
	SXP_NODE *ret = _sxp_new_node (info, t);
	ret->data.node = node;
	return ret;
}

SXP_NODE *
sxp_new_logic (SXP_INFO *info, SXP_NODE *left, SXP_NODE *right, int t) {
	SXP_NODE *ret = _sxp_new_node (info, t);
	ret->data.logic.left = left;
	ret->data.logic.right = right;
	return ret;
}

SXP_NODE *
sxp_new_call (SXP_INFO *info, sx_name_id name, SXP_NODE *args) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_CALL);
	ret->data.call.name = name;
	ret->data.call.args = args;
	return ret;
}

SXP_NODE *
sxp_new_name (SXP_INFO *info, sx_name_id name, int scope) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_NAME);
	ret->data.name.name = name;
	ret->data.name.scope = scope;
	return ret;
}

SXP_NODE *
sxp_new_assi (SXP_INFO *info, sx_name_id name, int scope, SXP_NODE *node) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_ASSI);
	ret->data.assi.name = name;
	ret->data.assi.scope = scope;
	ret->data.assi.node = node;
	return ret;
}

SXP_NODE *
sxp_new_stmt (SXP_INFO *info, SXP_NODE *node) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_STMT);
	ret->data.node = node;
	return ret;
}

SXP_NODE *
sxp_new_if (SXP_INFO *info, SXP_NODE *test, SXP_NODE *th, SXP_NODE *el) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_IF);
	ret->data.ifd.test = test;
	ret->data.ifd.el = el;
	ret->data.ifd.th = th;
	return ret;
}

SXP_NODE *
sxp_new_whil (SXP_INFO *info, SXP_NODE *test, SXP_NODE *block, int type) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_WHIL);
	ret->data.whil.test = test;
	ret->data.whil.block = block;
	ret->data.whil.type = type;
	return ret;
}

SXP_NODE *
sxp_new_set (SXP_INFO *info, SXP_NODE *array, SXP_NODE *index, SXP_NODE *value) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_SET);
	ret->data.set.array = array;
	ret->data.set.index = index;
	ret->data.set.node = value;
	return ret;
}

SXP_NODE *
sxp_new_indx (SXP_INFO *info, SXP_NODE *array, SXP_NODE *index) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_INDX);
	ret->data.set.array = array;
	ret->data.set.index = index;
	return ret;
}

SXP_NODE *
sxp_new_setm (SXP_INFO *info, SXP_NODE *base, sx_name_id name, SXP_NODE *value) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_SETM);
	ret->data.setm.base = base;
	ret->data.setm.name = name;
	ret->data.setm.node = value;
	return ret;
}

SXP_NODE *
sxp_new_getm (SXP_INFO *info, SXP_NODE *base, sx_name_id name) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_GETM);
	ret->data.getm.base = base;
	ret->data.getm.name = name;
	return ret;
}

SXP_NODE *
sxp_new_inc (SXP_INFO *info, sx_name_id name, SXP_NODE *amount, int type) {
	SXP_NODE *ret = _sxp_new_node (info, type);
	ret->data.inc.name = name;
	ret->data.inc.amount = amount;
	return ret;
}

SXP_NODE *
sxp_new_retr (SXP_INFO *info, SXP_NODE *node) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_RETR);
	ret->data.node = node;
	return ret;
}

SXP_NODE *
sxp_new_brak (SXP_INFO *info) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_BRAK);
	return ret;
}

SXP_NODE *
sxp_new_cont (SXP_INFO *info) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_CONT);
	return ret;
}

SXP_NODE *
sxp_new_klass (SXP_INFO *info, SXP_NODE *base, sx_name_id name, SXP_NODE *node, int type) {
	SXP_NODE *ret = _sxp_new_node (info, type);
	ret->data.klass.base = base;
	ret->data.klass.name = name;
	ret->data.klass.node = node;
	return ret;
}

SXP_NODE *
sxp_new_isa (SXP_INFO *info, SXP_NODE *node, sx_name_id name) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_ISA);
	ret->data.isa.node = node;
	ret->data.isa.name = name;
	return ret;
}

SXP_NODE *
sxp_new_rais (SXP_INFO *info, sx_name_id name, SXP_NODE *node) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_RAIS);
	ret->data.rais.name = name;
	ret->data.rais.node = node;
	return ret;
}

SXP_NODE *
sxp_new_try (SXP_INFO *info, SX_VALUE *names, SXP_NODE *body, SXP_NODE *rescue) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_TRY);
	ret->data.tryd.names = names;
	ret->data.tryd.body = body;
	ret->data.tryd.rescue = rescue;
	return ret;
}

SXP_NODE *
sxp_new_for (SXP_INFO *info, sx_name_id name, SXP_NODE *node, SXP_NODE *body) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_FOR);
	ret->data.ford.name = name;
	ret->data.ford.node = node;
	ret->data.ford.body = body;
	return ret;
}

SXP_NODE *
sxp_new_cfor (SXP_INFO *info, SXP_NODE *start, SXP_NODE *test, SXP_NODE *inc, SXP_NODE *body) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_CFOR);
	ret->data.cfor.start = start;
	ret->data.cfor.test = test;
	ret->data.cfor.inc = inc;
	ret->data.cfor.body = body;
	return ret;
}

SXP_NODE *
sxp_new_smet (SXP_INFO *info, sx_name_id klass, sx_name_id func, SXP_NODE *args) {
	SXP_NODE *ret = _sxp_new_node (info, SXP_SMET);
	ret->data.smet.klass = klass;
	ret->data.smet.func = func;
	ret->data.smet.args = args;
	return ret;
}

SXP_NODE *
sxp_append (SXP_NODE *base, SXP_NODE *add) {
	SXP_NODE *i;

	if (base == NULL)
		return NULL;

	for (i = base; i->next != NULL; i = i->next)
		;
	i->next = add;

	return base;
}

int
_sxp_count (SXP_NODE *node) {
	int i = 0;
	while (node != NULL) {
		++ i;
		node = node->next;
	}
	return i;
}

void
_sxp_put_line (SX_VALUE *block, SXP_NODE *node) {
	sx_add_value (node->info->system, block, node->file);
	sx_add_value (node->info->system, block, sx_new_num (node->line));
	sx_add_stmt (node->info->system, block, SX_OP_SETFILELINE);
}

void
_sxp_comp (SX_VALUE *block, SXP_NODE *node) {
	/* for the jumps necessary */
	unsigned int pos;
	unsigned int pos2;
	unsigned int pos3;
	SX_VALUE *nblock;

	if (node == NULL)
		return;

	if (node->file != node->info->last_file) {
		_sxp_put_line (block, node);
	} else if (node->line == node->info->last_line + 1) {
		sx_add_stmt (node->info->system, block, SX_OP_NEXTLINE);
	} else if (node->line != node->info->last_line) {
		_sxp_put_line (block, node);
	}

	node->info->last_file = node->file;
	node->info->last_line = node->line;

	switch (node->type) {
		case SXP_MATH:
			_sxp_comp (block, node->data.math.left);
			_sxp_comp (block, node->data.math.right);
			sx_add_stmt (node->info->system, block, node->data.math.op);
			break;
		case SXP_DATA:
			sx_add_value (node->info->system, block, node->data.data);
			break;
		case SXP_NEGA:
			_sxp_comp (block, node->data.node);
			sx_add_stmt (node->info->system, block, SX_OP_NEGATE);
			break;
		case SXP_NOT:
			_sxp_comp (block, node->data.node);
			sx_add_stmt (node->info->system, block, SX_OP_NOT);
			break;
		case SXP_OR:
			_sxp_comp (block, node->data.logic.left);
			sx_add_stmt (node->info->system, block, SX_OP_TEST);
			pos = ((SX_BLOCK *)block)->count;
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_TJUMP);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			_sxp_comp (block, node->data.logic.right);
			((SX_BLOCK *)block)->nodes[pos].value = sx_new_num (((SX_BLOCK *)block)->count);
			break;
		case SXP_AND:
			_sxp_comp (block, node->data.logic.left);
			sx_add_stmt (node->info->system, block, SX_OP_TEST);
			pos = ((SX_BLOCK *)block)->count;
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_FJUMP);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			_sxp_comp (block, node->data.logic.right);
			((SX_BLOCK *)block)->nodes[pos].value = sx_new_num (((SX_BLOCK *)block)->count);
			break;
		case SXP_CALL:
			_sxp_comp (block, node->data.call.args);
			sx_add_value (node->info->system, block, sx_new_num (_sxp_count (node->data.call.args)));
			sx_add_value (node->info->system, block, sx_new_num (node->data.call.name));
			sx_add_stmt (node->info->system, block, SX_OP_CALL);
			break;
		case SXP_NAME:
			sx_add_value (node->info->system, block, sx_new_num (node->data.name.name));
			sx_add_value (node->info->system, block, sx_new_num (node->data.name.scope));
			sx_add_stmt (node->info->system, block, SX_OP_LOOKUP);
			break;
		case SXP_ASSI:
			sx_add_value (node->info->system, block, sx_new_num (node->data.assi.name));
			sx_add_value (node->info->system, block, sx_new_num (node->data.assi.scope));
			_sxp_comp (block, node->data.assi.node);
			sx_add_stmt (node->info->system, block, SX_OP_ASSIGN);
			break;
		case SXP_STMT:
			_sxp_comp (block, node->data.node);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			break;
		case SXP_IF:
			_sxp_comp (block, node->data.ifd.test);
			sx_add_stmt (node->info->system, block, SX_OP_TEST);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			pos = ((SX_BLOCK *)block)->count;
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_FJUMP);
			_sxp_comp (block, node->data.ifd.th); /* then */
			((SX_BLOCK *)block)->nodes[pos].value = sx_new_num (((SX_BLOCK *)block)->count);
			if (node->data.ifd.el) { /* else */
				pos2 = ((SX_BLOCK *)block)->count;
				sx_add_value (node->info->system, block, NULL);
				sx_add_stmt (node->info->system, block, SX_OP_JUMP);
				((SX_BLOCK *)block)->nodes[pos].value = sx_new_num (((SX_BLOCK *)block)->count);
				_sxp_comp (block, node->data.ifd.el);
				((SX_BLOCK *)block)->nodes[pos2].value = sx_new_num (((SX_BLOCK *)block)->count);
			} else {
				((SX_BLOCK *)block)->nodes[pos].value = sx_new_num (((SX_BLOCK *)block)->count);
			}
			break;
		case SXP_WHIL:
			sxp_push_block (node->info);
			pos = ((SX_BLOCK *)block)->count;
			_sxp_put_line (block, node);
			switch (node->data.whil.type) {
				case SXP_W_WD:
					_sxp_comp (block, node->data.whil.test);
					sx_add_stmt (node->info->system, block, SX_OP_TEST);
					sx_add_stmt (node->info->system, block, SX_OP_POP);
					pos2 = ((SX_BLOCK *)block)->count;
					sx_add_value (node->info->system, block, NULL);
					sx_add_stmt (node->info->system, block, SX_OP_FJUMP);
					_sxp_comp (block, node->data.whil.block);
					sx_add_value (node->info->system, block, sx_new_num (pos));
					sx_add_stmt (node->info->system, block, SX_OP_JUMP);
					((SX_BLOCK *)block)->nodes[pos2].value = sx_new_num (((SX_BLOCK *)block)->count);
					break;
				case SXP_W_UD:
					_sxp_comp (block, node->data.whil.test);
					sx_add_stmt (node->info->system, block, SX_OP_TEST);
					sx_add_stmt (node->info->system, block, SX_OP_POP);
					pos2 = ((SX_BLOCK *)block)->count;
					sx_add_value (node->info->system, block, NULL);
					sx_add_stmt (node->info->system, block, SX_OP_TJUMP);
					_sxp_comp (block, node->data.whil.block);
					sx_add_value (node->info->system, block, sx_new_num (pos));
					sx_add_stmt (node->info->system, block, SX_OP_JUMP);
					((SX_BLOCK *)block)->nodes[pos2].value = sx_new_num (((SX_BLOCK *)block)->count);
					break;
				case SXP_W_DW:
					_sxp_comp (block, node->data.whil.block);
					_sxp_comp (block, node->data.whil.test);
					sx_add_stmt (node->info->system, block, SX_OP_TEST);
					sx_add_stmt (node->info->system, block, SX_OP_POP);
					sx_add_value (node->info->system, block, sx_new_num (pos));
					sx_add_stmt (node->info->system, block, SX_OP_TJUMP);
					break;
				case SXP_W_DU:
					_sxp_comp (block, node->data.whil.block);
					_sxp_comp (block, node->data.whil.test);
					sx_add_stmt (node->info->system, block, SX_OP_TEST);
					sx_add_stmt (node->info->system, block, SX_OP_POP);
					sx_add_value (node->info->system, block, sx_new_num (pos));
					sx_add_stmt (node->info->system, block, SX_OP_FJUMP);
					break;
			}
			sxp_pop_block (node->info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count, pos);
			break;
		case SXP_SET:
			_sxp_comp (block, node->data.set.array);
			_sxp_comp (block, node->data.set.index);
			_sxp_comp (block, node->data.set.node);
			sx_add_stmt (node->info->system, block, SX_OP_SETINDEX);
			break;
		case SXP_INDX:
			_sxp_comp (block, node->data.set.array);
			_sxp_comp (block, node->data.set.index);
			sx_add_stmt (node->info->system, block, SX_OP_INDEX);
			break;
		case SXP_ARRY:
			_sxp_comp (block, node->data.node);
			sx_add_value (node->info->system, block, sx_new_num (_sxp_count (node->data.node)));
			sx_add_stmt (node->info->system, block, SX_OP_NEWARRAY);
			break;
		case SXP_SETM:
			_sxp_comp (block, node->data.setm.base);
			sx_add_value (node->info->system, block, sx_new_num (node->data.setm.name));
			_sxp_comp (block, node->data.setm.node);
			sx_add_stmt (node->info->system, block, SX_OP_SETMEMBER);
			break;
		case SXP_GETM:
			_sxp_comp (block, node->data.getm.base);
			sx_add_value (node->info->system, block, sx_new_num (node->data.getm.name));
			sx_add_stmt (node->info->system, block, SX_OP_MEMBER);
			break;
		case SXP_PRIC:
			sx_add_value (node->info->system, block, sx_new_num (node->data.inc.name));
			_sxp_comp (block, node->data.inc.amount);
			sx_add_stmt (node->info->system, block, SX_OP_PREINCREMENT);
			break;
		case SXP_POIC:
			sx_add_value (node->info->system, block, sx_new_num (node->data.inc.name));
			_sxp_comp (block, node->data.inc.amount);
			sx_add_stmt (node->info->system, block, SX_OP_POSTINCREMENT);
			break;
		case SXP_RETR:
			if (node->data.node)
				_sxp_comp (block, node->data.node);
			else
				sx_add_value (node->info->system, block, NULL);
			sxp_new_return (node->info, ((SX_BLOCK*)block)->count);
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_JUMP);
			break;
		case SXP_BRAK:
			sxp_new_break (node->info, ((SX_BLOCK*)block)->count);
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_JUMP);
			break;
		case SXP_CONT:
			sxp_new_continue (node->info, ((SX_BLOCK*)block)->count);
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_JUMP);
			break;
		case SXP_METH:
			if (node->data.klass.node)
				_sxp_comp (block, node->data.klass.node);
			sx_add_value (node->info->system, block, sx_new_num (_sxp_count (node->data.klass.node)));
			_sxp_comp (block, node->data.klass.base);
			sx_add_value (node->info->system, block, sx_new_num (node->data.klass.name));
			sx_add_stmt (node->info->system, block, SX_OP_METHOD);
			break;
		case SXP_MEMB:
			_sxp_comp (block, node->data.klass.base);
			sx_add_value (node->info->system, block, sx_new_num (node->data.klass.name));
			sx_add_stmt (node->info->system, block, SX_OP_MEMBER);
			break;
		case SXP_NEWC:
			sx_add_value (node->info->system, block, NULL);
			if (node->data.klass.node)
				_sxp_comp (block, node->data.klass.node);
			sx_add_value (node->info->system, block, sx_new_num (_sxp_count (node->data.klass.node)));
			sx_add_value (node->info->system, block, sx_new_num (node->data.klass.name));
			sx_add_stmt (node->info->system, block, SX_OP_NEWINSTANCE);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			break;
		case SXP_ISA:
			_sxp_comp (block, node->data.isa.node);
			sx_add_value (node->info->system, block, sx_new_num (node->data.klass.name));
			sx_add_stmt (node->info->system, block, SX_OP_ISA);
			break;
		case SXP_RAIS:
			sx_add_value (node->info->system, block, sx_new_num (node->data.rais.name));
			if (node->data.rais.node)
				_sxp_comp (block, node->data.rais.node);
			else
				sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_RAISE);
			break;
		case SXP_TRY:
			nblock = sx_new_block (node->info->system);
			_sxp_comp (nblock, node->data.tryd.body);
			sx_add_value (node->info->system, block, nblock);
			sx_add_value (node->info->system, block, node->data.tryd.names);
			nblock = sx_new_block (node->info->system);
			_sxp_comp (nblock, node->data.tryd.rescue);
			sx_add_value (node->info->system, block, nblock);
			sx_add_stmt (node->info->system, block, SX_OP_TRY);
			break;
		case SXP_FOR:
			sxp_push_block (node->info);
			sx_add_value (node->info->system, block, sx_new_num (node->data.ford.name));
			_sxp_comp (block, node->data.ford.node);
			sx_add_value (node->info->system, block, NULL);
			pos = ((SX_BLOCK *)block)->count;
			_sxp_put_line (block, node);
			sx_add_stmt (node->info->system, block, SX_OP_FOR);
			pos2 = ((SX_BLOCK *)block)->count;
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_FJUMP);
			_sxp_comp (block, node->data.ford.body);
			sx_add_value (node->info->system, block, sx_new_num (pos));
			sx_add_stmt (node->info->system, block, SX_OP_JUMP);
			((SX_BLOCK *)block)->nodes[pos2].value = sx_new_num (((SX_BLOCK *)block)->count);
			sxp_pop_block (node->info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count, pos);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			break;
		case SXP_CFOR:
			sxp_push_block (node->info);
			_sxp_comp (block, node->data.cfor.start);
			pos = ((SX_BLOCK *)block)->count;
			_sxp_put_line (block, node);
			_sxp_comp (block, node->data.cfor.test);
			sx_add_stmt (node->info->system, block, SX_OP_TEST);
			sx_add_stmt (node->info->system, block, SX_OP_POP);
			pos2 = ((SX_BLOCK *)block)->count;
			sx_add_value (node->info->system, block, NULL);
			sx_add_stmt (node->info->system, block, SX_OP_FJUMP);
			_sxp_comp (block, node->data.cfor.body);
			pos3 = ((SX_BLOCK *)block)->count;
			_sxp_comp (block, node->data.cfor.inc);
			sx_add_value (node->info->system, block, sx_new_num (pos));
			sx_add_stmt (node->info->system, block, SX_OP_JUMP);
			((SX_BLOCK *)block)->nodes[pos2].value = sx_new_num (((SX_BLOCK *)block)->count);
			sxp_pop_block (node->info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count, pos3);
			break;
		case SXP_SMET:
			if (node->data.smet.args)
				_sxp_comp (block, node->data.smet.args);
			sx_add_value (node->info->system, block, sx_new_num (_sxp_count (node->data.smet.args)));
			sx_add_value (node->info->system, block, sx_new_num (node->data.smet.klass));
			sx_add_value (node->info->system, block, sx_new_num (node->data.smet.func));
			sx_add_stmt (node->info->system, block, SX_OP_STATIC_METHOD);
			break;
	}
	if (node->next)
		_sxp_comp (block, node->next);
}

int
_sxp_build_class (SXP_CLASS *klassd) {
	SX_CLASS *klass;
	SXP_FUNC *func;
	SX_VALUE *block;

	if (klassd->next)
		if (!_sxp_build_class (klassd->next))
			return 0;

	if (klassd->parent) {
		klass = sx_get_class (klassd->info->system, klassd->parent);
		if (!klass) {
			sxp_error (klassd->info, "Invalid base class");
			return 0;
		}
	} else {
		klass = NULL;
	}

	klass = sx_new_class (klassd->info->system, klassd->name, klass);
	if (!klass) {
		sxp_error (klassd->info, "Failed to create class");
		return 0;
	}

	for (func = klassd->methods; func != NULL; func = func->next) {
		block = sx_new_block (klassd->info->system);
		if (!block) {
			sxp_error (klassd->info, "Failed to create block");
			return 0;
		}
		_sxp_comp (block, func->body);
		sx_add_value (klassd->info->system, block, NULL);
		sxp_do_returns (klassd->info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count);
		sx_add_method (klassd->info->system, klass, func->name, func->args, (SX_BLOCK *)block);
	}

	for (func = klassd->static_methods; func != NULL; func = func->next) {
		block = sx_new_block (klassd->info->system);
		if (!block) {
			sxp_error (klassd->info, "Failed to create block");
			return 0;
		}
		_sxp_comp (block, func->body);
		sx_add_value (klassd->info->system, block, NULL);
		sxp_do_returns (klassd->info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count);
		sx_add_static_method (klassd->info->system, klass, func->name, func->args, (SX_BLOCK *)block);
	}

	return 1;
}

int
sxp_compile (SXP_INFO *info) {
	SX_VALUE *block;
	SXP_FUNC *func;

	if (info->classes)
		if (!_sxp_build_class (info->classes))
			return 1;

	for (func = info->funcs; func != NULL; func = func->next) {
		block = sx_new_block (info->system);
		if (!block) {
			sxp_error (info, "Failed to create block");
			return 1;
		}
		_sxp_comp (block, func->body);
		sx_add_value (info->system, block, NULL);
		sxp_do_returns (info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count);
		sx_new_func (info->system, func->name, (SX_ARRAY *)func->args, (SX_BLOCK *)block);
	}

	return 0;
}
