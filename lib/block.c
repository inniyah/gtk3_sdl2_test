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

SX_VALUE *
_sx_block_new (SX_SYSTEM *system, SX_CLASS *klass) {
	SX_BLOCK *value = (SX_BLOCK *)sx_malloc (system, sizeof (SX_BLOCK));
	if (value == NULL) {
		return NULL;
	}

	value->nodes = NULL;
	value->count = 0;
	value->size = 0;

	sx_clear_value (system, &value->header, klass);

	return (SX_VALUE *)value;
}

void
_sx_block_mark (SX_SYSTEM *system, SX_BLOCK *value) {
	unsigned int i;
	for (i = 0; i < value->count; ++ i) {
		if (value->nodes[i].op == 0) {
			sx_mark_value (system, value->nodes[i].value);
		}
	}
}

void
_sx_block_del (SX_SYSTEM *system, SX_BLOCK *value) {
	if (value->nodes != NULL) {
		sx_free (value->nodes);
	}
	sx_free (value);
}

SX_CLASS *
sx_init_block (SX_SYSTEM *system) {
	SX_CLASS *klass;

	klass = sx_new_core_class (system, sx_name_to_id ("block"), NULL);
	if (klass == NULL) {
		return NULL;
	}

	klass->core->fnew = (sx_class_new)_sx_block_new;
	klass->core->fmark = (sx_class_mark)_sx_block_mark;
	klass->core->fdel = (sx_class_del)_sx_block_del;

	return klass;
}

SX_VALUE *
sx_new_block (SX_SYSTEM *system) {
	SX_BLOCK *value = (SX_BLOCK *)sx_malloc (system, sizeof (SX_BLOCK));
	if (value == NULL) {
		return NULL;
	}

	value->nodes = NULL;
	value->count = 0;
	value->size = 0;

	sx_clear_value (system, &value->header, system->cblock);

	return (SX_VALUE *)value;
}

SX_VALUE *
sx_add_to_block (SX_SYSTEM *system, SX_VALUE *block, SX_VALUE *value, sx_op_type op) {
	struct _scriptix_node *sx_new_nodes;

	if (SX_ISBLOCK (system, block)) {
		if (SX_TOBLOCK(block)->count == SX_TOBLOCK(block)->size) {
			sx_lock_value (block);
			sx_lock_value (value);
			sx_new_nodes = sx_malloc (system, sizeof (struct _scriptix_node) * (SX_TOBLOCK(block)->count + system->block_chunk));
			sx_unlock_value (block);
			sx_unlock_value (value);
			if (sx_new_nodes == NULL) {
				return sx_new_nil ();
			}

			if (SX_TOBLOCK(block)->nodes != NULL) {
				memcpy (sx_new_nodes, SX_TOBLOCK(block)->nodes, sizeof (struct _scriptix_node) * SX_TOBLOCK(block)->count);
				sx_free (SX_TOBLOCK(block)->nodes);
			}
			SX_TOBLOCK(block)->nodes = sx_new_nodes;
			SX_TOBLOCK(block)->size += system->block_chunk;
		}
		SX_TOBLOCK(block)->nodes[SX_TOBLOCK(block)->count].value = value;
		SX_TOBLOCK(block)->nodes[SX_TOBLOCK(block)->count].op = op;
		++ SX_TOBLOCK(block)->count;
		return block;
	} else {
		return sx_new_nil ();
	}
}
