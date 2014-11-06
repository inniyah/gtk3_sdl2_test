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

#include "scriptix.h"
#include "parser.h"

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
		case SXP_SUPR:
			_sxp_comp (block, node->data.call.args);
			sx_add_value (node->info->system, block, sx_new_num (_sxp_count (node->data.call.args)));
			sx_add_stmt (node->info->system, block, SX_OP_SUPER);
			break;
		case SXP_YELD:
			sx_add_stmt (node->info->system, block, SX_OP_YIELD);
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
	sx_name_id *names;

	if (klassd->next)
		if (!_sxp_build_class (klassd->next))
			return 0;

	if (klassd->parent) {
		klass = sx_get_class (klassd->info->module, klassd->parent);
		if (!klass) {
			sxp_error (klassd->info, "Invalid base class");
			return 0;
		}
	} else {
		klass = klassd->info->system->cobject;
	}

	names = sx_new_namelist_from_array (klassd->info->system, klassd->members);
	klass = sx_new_class (klassd->info->system, klassd->name, names, klass);
	if (!klass) {
		sxp_error (klassd->info, "Failed to create class");
		return 0;
	} else {
		sx_add_class (klassd->info->module, klass);
	}

	for (func = klassd->methods; func != NULL; func = func->next) {
		names = sx_new_namelist_from_array (klassd->info->system, func->args);
		block = sx_new_block (klassd->info->system);
		if (!block) {
			sxp_error (klassd->info, "Failed to create block");
			sx_free_namelist (names);
			return 0;
		}
		_sxp_comp (block, func->body);
		sx_add_value (klassd->info->system, block, NULL);
		sxp_do_returns (klassd->info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count);
		sx_add_method (klassd->info->system, klass, sx_new_func (klassd->info->system, func->name, names, func->varg, (SX_BLOCK *)block));
		sx_free_namelist (names);
	}

	for (func = klassd->static_methods; func != NULL; func = func->next) {
		names = sx_new_namelist_from_array (klassd->info->system, func->args);
		block = sx_new_block (klassd->info->system);
		if (!block) {
			sxp_error (klassd->info, "Failed to create block");
			sx_free_namelist (names);
			return 0;
		}
		_sxp_comp (block, func->body);
		sx_add_value (klassd->info->system, block, NULL);
		sxp_do_returns (klassd->info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count);
		sx_add_static_method (klassd->info->system, klass, sx_new_func (klassd->info->system, func->name, names, func->varg, (SX_BLOCK *)block));
		sx_free_namelist (names);
	}

	return 1;
}

int
sxp_compile (SXP_INFO *info) {
	SX_VALUE *block;
	SXP_FUNC *func;
	SX_FUNC *nfunc;
	sx_name_id *names;

	if (info->classes)
		if (!_sxp_build_class (info->classes))
			return 1;

	for (func = info->funcs; func != NULL; func = func->next) {
		names = sx_new_namelist_from_array (info->system, func->args);
		block = sx_new_block (info->system);
		if (!block) {
			sxp_error (info, "Failed to create block");
			if (names)
				sx_free_namelist (names);
			return 1;
		}
		_sxp_comp (block, func->body);
		sx_add_value (info->system, block, NULL);
		sxp_do_returns (info, (SX_BLOCK *)block, ((SX_BLOCK *)block)->count);
		nfunc = sx_new_func (info->system, func->name, names, func->varg, (SX_BLOCK *)block);
		sx_free_namelist (names);
		if (nfunc != NULL) {
			sx_add_func (info->module, nfunc);
		} else {
			sxp_error (info, "Failed to create function");
			return 1;
		}
	}

	return 0;
}
