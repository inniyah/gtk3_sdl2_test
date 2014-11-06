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

static
void
_sxp_node_error (SXP_NODE* node, const char *msg, ...)
{
	char buffer[512];
	va_list va;

	va_start (va, msg);
	vsnprintf (buffer, sizeof(buffer), msg, va);
	va_end (va);

	if (node->info->system->error_hook != NULL) {
		node->info->system->error_hook (node->file ? ((String*)node->file)->GetStr() : "<input>", node->line, buffer);
	}
}

static
int
_sxp_count (SXP_NODE *node) {
	int i = 0;
	while (node != NULL) {
		++ i;
		node = node->next;
	}
	return i;
}

static
void
_sxp_put_line (SXP_FUNC* func, SXP_NODE *node) {
	func->func->AddValue(node->info->system, (Value*)node->file);
	func->func->AddValue(node->info->system, Number::Create (node->line));
	func->func->AddCode(node->info->system, SX_OP_SETFILELINE);
}

static
int
_sxp_comp (SXP_FUNC* func, SXP_NODE *node) {
	/* for the jumps necessary */
	unsigned long pos;
	unsigned long pos2;
	unsigned long pos3;

	while (node != NULL) {
		if (node->file != node->info->last_file) {
			_sxp_put_line (func, node);
		} else if (node->line == node->info->last_line + 1) {
			func->func->AddCode(node->info->system, SX_OP_NEXTLINE);
		} else if (node->line != node->info->last_line) {
			_sxp_put_line (func, node);
		}

		node->info->last_file = node->file;
		node->info->last_line = node->line;

		switch (node->type) {
			case SXP_MATH:
				if (_sxp_comp (func, node->data.math.left))
					return 1; /* failed */
				if (_sxp_comp (func, node->data.math.right))
					return 1; /* failed */
				func->func->AddCode(node->info->system, (sx_op_type)node->data.math.op);
				break;
			case SXP_DATA:
				func->func->AddValue(node->info->system, node->data.data);
				break;
			case SXP_NEGA:
				if (_sxp_comp (func, node->data.node))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_NEGATE);
				break;
			case SXP_NOT:
				if (_sxp_comp (func, node->data.node))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_NOT);
				break;
			case SXP_OR:
				if (_sxp_comp (func, node->data.logic.left))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_TEST);
				pos = func->func->count;
				func->func->AddValue(node->info->system, SX_NIL);
				func->func->AddCode(node->info->system, SX_OP_TJUMP);
				func->func->AddCode(node->info->system, SX_OP_POP);
				if (_sxp_comp (func, node->data.logic.right))
					return 1; /* failed */
				func->func->nodes[pos + 1] = (long)Number::Create (func->func->count);
				break;
			case SXP_AND:
				if (_sxp_comp (func, node->data.logic.left))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_TEST);
				pos = func->func->count;
				func->func->AddValue(node->info->system, SX_NIL);
				func->func->AddCode(node->info->system, SX_OP_FJUMP);
				func->func->AddCode(node->info->system, SX_OP_POP);
				if (_sxp_comp (func, node->data.logic.right))
					return 1; /* failed */
				func->func->nodes[pos + 1] = (long)Number::Create (func->func->count);
				break;
			case SXP_CALL:
				if (_sxp_comp (func, node->data.call.args))
					return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (_sxp_count (node->data.call.args)));
				if (_sxp_comp (func, node->data.call.expr))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_CALL);
				break;
			case SXP_LOOK:
			{
				Value* lfunc;
				SXP_FUNC* dfunc;
				Value* gval;
				char found = 0;
				long index;

				/* do variable lookup */
				index = sxp_get_var (node->info, func, node->data.name);
				if (index >= 0) {
					func->func->AddValue(node->info->system, Number::Create (index));
					func->func->AddCode(node->info->system, SX_OP_LOOKUP);
					break;
				}

				/* search for function */
				for (dfunc = node->info->funcs; dfunc != NULL; dfunc = dfunc->next) {
					if (dfunc->name == node->data.name) {
						func->func->AddValue(node->info->system, SX_TOVALUE(dfunc->func));
						found = 1;
						break;
					}
				}
				/* found, done, ok */
				if (found) {
					break;
				}

				/* external function? */
				lfunc = node->info->system->GetFunction(node->data.name);
				if (lfunc) {
					/* add function */
					func->func->AddValue(node->info->system, lfunc);
					break;
				}

				/* global variable? */
				index = sxp_get_global (node->info, node->data.name);
				if (index >= 0) {
					func->func->AddValue(node->info->system, node->info->globals);
					func->func->AddValue(node->info->system, Number::Create(index));
					func->func->AddCode(node->info->system, SX_OP_INDEX);
					break;
				}

				/* global constant? */
				gval = node->info->system->GetGlobal(node->data.name);
				if (gval) {
					func->func->AddValue(node->info->system, gval);
					break;
				}

				/* failure... */
				_sxp_node_error (node, "Unknown identifier '%s'", IDToName (node->data.name));
				return 1;
			}
			case SXP_ASSI:
			{
				long index = sxp_get_var (node->info, func, node->data.assi.name);
				if (index < 0) {
					/* global variable? */
					index = sxp_get_global (node->info, node->data.name);
					if (index >= 0) {
						/* do a lookup */
						func->func->AddValue(node->info->system, SX_TOVALUE(node->info->globals));
						func->func->AddValue(node->info->system, Number::Create(index));
						if (_sxp_comp (func, node->data.assi.node))
							return 1; /* failed */
						func->func->AddCode(node->info->system, SX_OP_SETINDEX);
						break;
						
					}
					index = sxp_add_var (node->info, func, node->data.assi.name);
				}
				func->func->AddValue(node->info->system, Number::Create (index));
				if (_sxp_comp (func, node->data.assi.node))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_ASSIGN);
				break;
			}
			case SXP_STMT:
				if (_sxp_comp (func, node->data.node))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_POP);
				break;
			case SXP_IF:
				if (_sxp_comp (func, node->data.ifd.test))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_TEST);
				func->func->AddCode(node->info->system, SX_OP_POP);
				pos = func->func->count;
				func->func->AddValue(node->info->system, SX_NIL);
				func->func->AddCode(node->info->system, SX_OP_FJUMP);
				if (_sxp_comp (func, node->data.ifd.th))
					return 1; /* failed */ /* then */
				if (node->data.ifd.el) { /* else */
					pos2 = func->func->count;
					func->func->AddValue(node->info->system, SX_NIL);
					func->func->AddCode(node->info->system, SX_OP_JUMP);
					func->func->nodes[pos + 1] = (long)Number::Create (func->func->count);
					if (_sxp_comp (func, node->data.ifd.el))
						return 1; /* failed */
					func->func->nodes[pos2 + 1] = (long)Number::Create (func->func->count);
				} else {
					func->func->nodes[pos + 1] = (long)Number::Create (func->func->count);
				}
				break;
			case SXP_WHIL:
				sxp_push_block (node->info);
				pos = func->func->count;
				_sxp_put_line (func, node);
				switch (node->data.whil.type) {
					case SXP_W_WD:
						/* while... do - test true, loop */
						if (_sxp_comp (func, node->data.whil.test))
							return 1; /* failed */
						func->func->AddCode(node->info->system, SX_OP_TEST);
						func->func->AddCode(node->info->system, SX_OP_POP);
						pos2 = func->func->count;
						func->func->AddValue(node->info->system, SX_NIL);
						func->func->AddCode(node->info->system, SX_OP_FJUMP);
						if (_sxp_comp (func, node->data.whil.block))
							return 1; /* failed */
						func->func->AddValue(node->info->system, Number::Create (pos));
						func->func->AddCode(node->info->system, SX_OP_JUMP);
						func->func->nodes[pos2 + 1] = (long)Number::Create (func->func->count);
						break;
					case SXP_W_UD:
						/* until... do - test false, loop */
						if (_sxp_comp (func, node->data.whil.test))
							return 1; /* failed */
						func->func->AddCode(node->info->system, SX_OP_TEST);
						func->func->AddCode(node->info->system, SX_OP_POP);
						pos2 = func->func->count;
						func->func->AddValue(node->info->system, SX_NIL);
						func->func->AddCode(node->info->system, SX_OP_TJUMP);
						if (_sxp_comp (func, node->data.whil.block))
							return 1; /* failed */
						func->func->AddValue(node->info->system, Number::Create (pos));
						func->func->AddCode(node->info->system, SX_OP_JUMP);
						func->func->nodes[pos2 + 1] = (long)Number::Create (func->func->count);
						break;
					case SXP_W_DW:
						/* do... while - loop, test true */
						if (_sxp_comp (func, node->data.whil.block))
							return 1; /* failed */
						if (_sxp_comp (func, node->data.whil.test))
							return 1; /* failed */
						func->func->AddCode(node->info->system, SX_OP_TEST);
						func->func->AddCode(node->info->system, SX_OP_POP);
						func->func->AddValue(node->info->system, Number::Create (pos));
						func->func->AddCode(node->info->system, SX_OP_TJUMP);
						break;
					case SXP_W_DU:
						/* do... until - loop, test false */
						if (_sxp_comp (func, node->data.whil.block))
							return 1; /* failed */
						if (_sxp_comp (func, node->data.whil.test))
							return 1; /* failed */
						func->func->AddCode(node->info->system, SX_OP_TEST);
						func->func->AddCode(node->info->system, SX_OP_POP);
						func->func->AddValue(node->info->system, Number::Create (pos));
						func->func->AddCode(node->info->system, SX_OP_FJUMP);
						break;
					case SXP_W_PE:
						/* permanent loop - loop */
						if (_sxp_comp (func, node->data.whil.block))
							return 1; /* failed */
						func->func->AddValue(node->info->system, Number::Create (pos));
						func->func->AddCode(node->info->system, SX_OP_JUMP);
						break;
				}
				sxp_pop_block (node->info, func->func, func->func->count, pos);
				break;
			case SXP_SET:
				if (_sxp_comp (func, node->data.set.array))
					return 1; /* failed */
				if (_sxp_comp (func, node->data.set.index))
					return 1; /* failed */
				if (_sxp_comp (func, node->data.set.node))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_SETINDEX);
				break;
			case SXP_INDX:
				if (_sxp_comp (func, node->data.set.array))
					return 1; /* failed */
				if (_sxp_comp (func, node->data.set.index))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_INDEX);
				break;
			case SXP_ARRY:
				if (_sxp_comp (func, node->data.node))
					return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (_sxp_count (node->data.node)));
				func->func->AddCode(node->info->system, SX_OP_NEWARRAY);
				break;
			case SXP_ASSC:
				if (_sxp_comp (func, node->data.node))
					return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (_sxp_count (node->data.node) / 2)); // half the nodes
				func->func->AddCode(node->info->system, SX_OP_NEWASSOC);
				break;
			case SXP_PRIC:
			{
				long index;
				/* do variable lookup */
				index = sxp_get_var (node->info, func, node->data.name);
				/* FIXME: error for undefined... */

				func->func->AddValue(node->info->system, Number::Create (index));
				if (_sxp_comp (func, node->data.inc.amount))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_PREINCREMENT);
				break;
			}
			case SXP_POIC:
			{
				long index;
				/* do variable lookup */
				index = sxp_get_var (node->info, func, node->data.name);
				/* FIXME: error for undefined... */

				func->func->AddValue(node->info->system, Number::Create (index));
				if (_sxp_comp (func, node->data.inc.amount))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_POSTINCREMENT);
				break;
			}
			case SXP_RETR:
				if (node->data.node) {
					if (_sxp_comp (func, node->data.node))
						return 1; /* failed */
				 } else
					func->func->AddValue(node->info->system, SX_NIL);
				sxp_new_return (node->info, func->func->count);
				func->func->AddValue(node->info->system, SX_NIL);
				func->func->AddCode(node->info->system, SX_OP_JUMP);
				break;
			case SXP_BRAK:
				sxp_new_break (node->info, func->func->count);
				func->func->AddValue(node->info->system, SX_NIL);
				func->func->AddCode(node->info->system, SX_OP_JUMP);
				break;
			case SXP_CONT:
				sxp_new_continue (node->info, func->func->count);
				func->func->AddValue(node->info->system, SX_NIL);
				func->func->AddCode(node->info->system, SX_OP_JUMP);
				break;
			case SXP_METH:
				if (node->data.meth.node)
					if (_sxp_comp (func, node->data.meth.node))
						return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (_sxp_count (node->data.meth.node)));
				if (_sxp_comp (func, node->data.meth.base))
					return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (node->data.meth.name));
				func->func->AddCode(node->info->system, SX_OP_METHOD);
				break;
			case SXP_CAST:
				if (_sxp_comp (func, node->data.cast.node))
					return 1; /* failed */
				func->func->AddValue(node->info->system, new TypeValue (node->info->system, node->info->system->GetType(node->data.cast.name)));
				func->func->AddCode(node->info->system, SX_OP_TYPECAST);
				break;
			case SXP_CFOR:
				sxp_push_block (node->info);
				if (_sxp_comp (func, node->data.cfor.start))
					return 1; /* failed */
				pos = func->func->count;
				_sxp_put_line (func, node);
				if (_sxp_comp (func, node->data.cfor.test))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_TEST);
				func->func->AddCode(node->info->system, SX_OP_POP);
				pos2 = func->func->count;
				func->func->AddValue(node->info->system, SX_NIL);
				func->func->AddCode(node->info->system, SX_OP_FJUMP);
				if (_sxp_comp (func, node->data.cfor.body))
					return 1; /* failed */
				pos3 = func->func->count;
				if (_sxp_comp (func, node->data.cfor.inc))
					return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (pos));
				func->func->AddCode(node->info->system, SX_OP_JUMP);
				func->func->nodes[pos2 + 1] = (long)Number::Create (func->func->count);
				sxp_pop_block (node->info, func->func, func->func->count, pos3);
				break;
			case SXP_SMET:
				if (node->data.smet.args)
					if (_sxp_comp (func, node->data.smet.args))
						return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (_sxp_count (node->data.smet.args)));
				func->func->AddValue(node->info->system, new TypeValue (node->info->system, node->info->system->GetType(node->data.smet.type)));
				func->func->AddValue(node->info->system, Number::Create (node->data.smet.func));
				func->func->AddCode(node->info->system, SX_OP_STATIC_METHOD);
				break;
			case SXP_YELD:
				func->func->AddCode(node->info->system, SX_OP_YIELD);
				break;
			case SXP_IN:
				// first put in list to check
				if (node->data.logic.right) {
					if (_sxp_comp (func, node->data.logic.right))
						return 1; /* failed */
				} else {
					func->func->AddValue(node->info->system, SX_NIL);
				}
				// then put in item to check for
				if (node->data.logic.left) {
					if (_sxp_comp (func, node->data.logic.left))
						return 1; /* failed */
				} else {
					func->func->AddValue(node->info->system, SX_NIL);
				}
				// set op
				func->func->AddCode(node->info->system, SX_OP_IN);
				break;
			case SXP_NEW:
				func->func->AddValue(node->info->system, Number::Create (0));
				func->func->AddValue(node->info->system, new TypeValue (node->info->system, node->info->system->GetType(node->data.name)));
				func->func->AddValue(node->info->system, Number::Create (NameToID("new")));
				func->func->AddCode(node->info->system, SX_OP_STATIC_METHOD);
				break;
			case SXP_AFNC:
				func->func->AddValue(node->info->system, SX_TOVALUE(node->data.func->func));
				break;
			case SXP_CLOS:
				if (_sxp_comp (func, node->data.clos.args))
					return 1; /* failed */
				func->func->AddValue(node->info->system, Number::Create (_sxp_count (node->data.clos.args)));
				func->func->AddValue(node->info->system, SX_TOVALUE(node->data.clos.func->func));
				func->func->AddCode(node->info->system, SX_OP_CLOSURE);
				break;
			case SXP_NAME_DATA:
				func->func->AddValue(node->info->system, Number::Create(node->data.name));
				break;
			case SXP_SET_MEMBER:
				// object
				if (_sxp_comp (func, node->data.nodes.nodea))
					return 1; /* failed */
				// member name
				if (_sxp_comp (func, node->data.nodes.nodeb))
					return 1; /* failed */
				// value
				if (_sxp_comp (func, node->data.nodes.nodec))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_SET_MEMBER);
				break;
			case SXP_GET_MEMBER:
				// object
				if (_sxp_comp (func, node->data.nodes.nodea))
					return 1; /* failed */
				// member name
				if (_sxp_comp (func, node->data.nodes.nodeb))
					return 1; /* failed */
				func->func->AddCode(node->info->system, SX_OP_GET_MEMBER);
				break;

			case SXP_NOOP:
				/* ignore */
				break;
		}
		node = node->next;
	}

	return 0;
}

int
sxp_compile (SXP_INFO *info) {
	SXP_FUNC *func;

	/* make function data */
	for (func = info->funcs; func != NULL; func = func->next) {
		func->func = new Function (info->system, func->name, sx_sizeof_namelist(func->vars), func->varg);
		if (!func->func) {
			sxp_error (info, "Failed to create function");
			return 1;
		}
	}

	/* compile blocks */
	for (func = info->funcs; func != NULL; func = func->next) {
		if (func->varg)
			func->vars = sx_namelist_append(info->system, func->vars, func->varg);
		func->body = sxp_transform (func->body);
		if (_sxp_comp (func, func->body))
			return 1; /* failed */
		func->func->AddValue(info->system, SX_NIL);
		sxp_do_returns (info, func->func, func->func->count);
		func->func->varc = sx_sizeof_namelist(func->vars);
	}

	/* everything went right, publicize */
	for (func = info->funcs; func != NULL; func = func->next) {
		/* make public if public */
		if (func->pub)
			info->system->AddFunction(func->func);
	}

	/* everything went right, tag callbacks */
	for (func = info->funcs; func != NULL; func = func->next) {
		/* gotta tag?  call back */
		if (func->tag)
			info->system->HandleFunctionTag (func->tag, func->func);
	}

	return 0;
}
