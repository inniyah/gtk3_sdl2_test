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

static void sxp_transform_node (SXP_NODE** node);

static
void
sxp_do_transform (SXP_NODE** node_ptr)
{
	SXP_NODE* node = *node_ptr;
	if (node == NULL)
		return;

	switch (node->type) {
		/* pre-perform math */
		case SXP_MATH:
			sxp_transform_node (&node->data.math.left);
			sxp_transform_node (&node->data.math.right);
			if (node->data.math.left->type == SXP_DATA &&
					SX_ISNUM(node->info->system, node->data.math.left->data.data) &&
					node->data.math.right->type == SXP_DATA &&
					SX_ISNUM(node->info->system, node->data.math.right->data.data)) {
				int left = sx_toint(node->data.math.left->data.data);
				int right = sx_toint(node->data.math.right->data.data);
				switch (node->data.math.op) {
					case SX_OP_ADD:
						node->type = SXP_DATA;
						node->data.data = sx_new_num (left + right);
						break;
					case SX_OP_SUBTRACT:
						node->type = SXP_DATA;
						node->data.data = sx_new_num (left - right);
						break;
					case SX_OP_MULTIPLY:
						node->type = SXP_DATA;
						node->data.data = sx_new_num (left * right);
						break;
					case SX_OP_DIVIDE:
						if (right == 0) {
							sxp_error (node->info, "Division by zero");
						} else {
							*node_ptr = sxp_new_data (node->info, sx_new_num (left / right));
							node->type = SXP_MATH;
							node->data.data = sx_new_num (left / right);
						}
						break;
				}
			}
			break;
		/* breaks, returns, and continues have nothing afterwards */
		case SXP_BRAK:
		case SXP_RETR:
		case SXP_CONT:
			/* remove next pointer */
			node->next = NULL;
			break;
		/* statements must be expanded */
		case SXP_STMT:
			sxp_transform_node (&node->data.node);
			break;
		/* if - turn into a block if true, or cut if false */
		case SXP_IF:
			sxp_transform_node (&node->data.ifd.test);
			if (node->data.ifd.test->type == SXP_DATA) {
				SXP_NODE* block = NULL;
				/* is always true */
				if (sx_is_true (node->info->system, node->data.ifd.test->data.data)) {
					block = node->data.ifd.th;
				} else {
					block = node->data.ifd.el;
				}
				if (block) {
					/* append next to block list, update current */
					sxp_append (block, node->next);
					*node_ptr = block;
				} else {
					node->type = SXP_NOOP;
				}
			} else {
				/* transform block */
				sxp_transform_node (&node->data.ifd.th);
				sxp_transform_node (&node->data.ifd.el);
			}
			break;
		/* while/until/do loops - test is true, perma loop, false, noop */
		case SXP_WHIL:
			sxp_transform_node (&node->data.ifd.test);
			if (node->data.whil.test->type == SXP_DATA) {
				/* is always true */
				if (sx_is_true (node->info->system, node->data.ifd.test->data.data)) {
					node->data.whil.type = SXP_W_PE;
				/* always false */
				} else {
					node->type = SXP_NOOP;
				}
			} else {
				/* transform block */
				sxp_transform_node (&node->data.whil.block);
			}
			break;
		default:
			/* do nothing */
			break;
	}
}

static
void
sxp_transform_node (SXP_NODE** node)
{
	SXP_NODE* ret = sxp_transform(*node);
	*node = ret;
}

SXP_NODE*
sxp_transform (SXP_NODE* node)
{
	SXP_NODE* last = NULL;
	SXP_NODE* ret = NULL;

	while (node != NULL) {
		/* do transform */
		sxp_do_transform (&node);

		/* if the last's next is not the current node
		 * (i.e., it changed), update the last next pointer to the
		 * new node */
		if (last != NULL && last->next != node)
			last->next = node;

		/* if we have no return pointer, update it */
		if (ret == NULL)
			ret = node;

		/* looping update */
		last = node;
		node = node->next;
	}

	return ret;
}
