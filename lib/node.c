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
#include <string.h>
#include <stdarg.h>

#include "scriptix.h"


NODE *
new_node (SYSTEM *system, VALUE *value) {
	NODE *node;
	lock_value (value);
	node = (NODE *)sx_malloc (system, sizeof (NODE));
	unlock_value (value);
	if (node == NULL) {
		return NULL;
	}
	

	node->type = NODE_VALUE;
	node->data.value = value;
	node->next = NULL;

	return node;
}

NODE *
new_expr (SYSTEM *system, char op, int count, ...) {
	va_list va;
	int i;
	NODE *node = (NODE *)sx_malloc (system, sizeof (NODE));
	if (node == NULL) {
		return NULL;
	}

	node->type = NODE_EXPR;
	node->data.expr.op = op;
	node->data.expr.count = count;

	node->data.expr.nodes = (NODE **)sx_malloc (system, count * sizeof (NODE *));
	if (node->data.expr.nodes == NULL) {
		sx_free (node);
		return NULL;
	}

	va_start (va, count);
	for (i = 0; i < count; i ++) {
		node->data.expr.nodes[i] = va_arg (va, NODE *);
	}
	va_end (va);

	node->next = NULL;

	return node;
}

void
free_node (NODE *node) {
	unsigned int i;

	if (node->type == NODE_EXPR && node->data.expr.count > 0) {
		for (i = 0; i < node->data.expr.count; ++ i) {
			if (node->data.expr.nodes[i] != NULL && node->data.expr.nodes[i]->type == NODE_EXPR) {
				free_node (node->data.expr.nodes[i]);
			}
		}
		sx_free (node->data.expr.nodes);
	}

	sx_free (node);
}

void
mark_node (SYSTEM *system, NODE *node) {
	unsigned int i;
	if (node->type == NODE_EXPR) {
		for (i = 0; i < node->data.expr.count; ++ i) {
			if (node->data.expr.nodes[i] != NULL) {
				mark_node (system, node->data.expr.nodes[i]);
			}
		}
	} else if (node->type == NODE_VALUE) {
		mark_value (system, node->data.value);
	}
}
