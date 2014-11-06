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

#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "scriptix.h"
#include "system.h"

/* internal block stuff */

void
_sx_block_mark (SX_SYSTEM *system, SX_VALUE *value) {
	unsigned int i;
	for (i = 0; i < value->data.block.count; ++ i) {
		if (value->data.block.nodes[i].op == 0) {
			sx_mark_value (system, value->data.block.nodes[i].value);
		}
	}
}

void
_sx_block_del (SX_SYSTEM *system, SX_VALUE *value) {
	if (value->data.block.nodes != NULL) {
		sx_free (value->data.block.nodes);
	}
	sx_free (value);
}

SX_CLASS *
sx_init_block (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("block"));
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fmark = _sx_block_mark;
	klass->core->fdel = _sx_block_del;

	return klass;
}

SX_VALUE *
sx_new_block (SX_SYSTEM *system) {
	SX_VALUE *value = (SX_VALUE *)sx_malloc (system, sizeof (SX_VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->klass = system->cblock;
	value->members = NULL;
	value->data.block.nodes = NULL;
	value->data.block.count = 0;
	value->data.block.size = 0;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}

SX_VALUE *
sx_add_to_block (SX_SYSTEM *system, SX_VALUE *block, SX_VALUE *value, int op) {
	struct _scriptix_node *sx_new_nodes;

	if (SX_ISBLOCK (system, block)) {
		if (block->data.block.count == block->data.block.size) {
			sx_lock_value (block);
			sx_lock_value (value);
			sx_new_nodes = sx_malloc (system, sizeof (struct _scriptix_node) * (block->data.block.count + SX_BLOCK_CHUNK));
			sx_unlock_value (block);
			sx_unlock_value (value);
			if (sx_new_nodes == NULL) {
				return sx_new_nil ();
			}

			if (block->data.block.nodes != NULL) {
				memcpy (sx_new_nodes, block->data.block.nodes, sizeof (struct _scriptix_node) * block->data.block.count);
				sx_free (block->data.block.nodes);
			}
			block->data.block.nodes = sx_new_nodes;
			block->data.block.size += SX_BLOCK_CHUNK;
		}
		block->data.block.nodes[block->data.block.count].value = value;
		block->data.block.nodes[block->data.block.count].op = op;
		++ block->data.block.count;
		return block;
	} else {
		return sx_new_nil ();
	}
}
