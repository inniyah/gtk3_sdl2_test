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
#include <stdlib.h>

#include "scriptix.h"

/* globals */
VALUE *
sx_new_str (SYSTEM *system, char *str) {
	VALUE *value;
	unsigned int len;
	
	if (str == NULL) {
		len = 0;
		value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	} else {
		len = strlen (str);
		value = (VALUE *)sx_malloc (system, sizeof (VALUE) + (len + 1) * sizeof (char));
	}
	
	if (value == NULL) {
		return NULL;
	}

	value->type = SX_VALUE_STRING;
	if (str == NULL) {
		value->data.str.len = 0;
	} else {
		value->data.str.len = strlen (str);
		strcpy (value->data.str.str, str);
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}

VALUE *
sx_new_str_len (SYSTEM *system, char *str, unsigned int len) {
	VALUE *value;
	
	value = (VALUE *)sx_malloc (system, sizeof (VALUE) + (len + 1) * sizeof (char));
	if (value == NULL) {
		return NULL;
	}

	value->data.str.len = len;

	value->type = SX_VALUE_STRING;
	if (str != NULL) {
		strncpy (value->data.str.str, str, len);
		SX_TOSTR(value)[len] = '\0';
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}

VALUE *
sx_new_block (SYSTEM *system) {
	VALUE *value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = SX_VALUE_BLOCK;
	value->data.block.nodes = NULL;
	value->data.block.count = 0;
	value->data.block.size = 0;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}

VALUE *
sx_new_func (SYSTEM *system, VALUE *args, VALUE *body) {
	VALUE *value;

	if (!SX_ISBLOCK (body)) {
		return NULL;
	}
	if (!SX_ISNIL (args) && !SX_ISARRAY (args)) {
		return NULL;
	}
	
	value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = SX_VALUE_FUNC;
	value->data.func.args = args;
	value->data.func.body = body;
	value->locks = 0;
	value->gc_next = NULL;
	value->flags = 0;

	sx_add_gc_value (system, value);

	return value;
}

VALUE *
sx_new_cfunc (SYSTEM *system, VALUE *(*cfunc)(THREAD *, VALUE *self, unsigned int argc, unsigned int top)) {
	VALUE *value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = SX_VALUE_CFUNC;
	value->data.cfunc = cfunc;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}

VALUE *
sx_new_array (SYSTEM *system, unsigned int argc, VALUE **argv) {
	VALUE *value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = SX_VALUE_ARRAY;
	value->data.array.count = argc;
	value->data.array.size = argc;
	if (argc > 0) {
		if (argv != NULL) {
			value->data.array.list = sx_dupmem (system, argv, argc * sizeof (VALUE *));
			if (value->data.array.list == NULL) {
				sx_free_value (value);
				return NULL;
			}
		} else {
			value->data.array.list = sx_malloc (system, argc * sizeof (VALUE *));
			if (value->data.array.list == NULL) {
				sx_free_value (value);
				return NULL;
			}
			memset (value->data.array.list, 0, argc * sizeof (VALUE *));
		}
	} else {
		value->data.array.list = NULL;
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);
	

	return value;
}

VALUE *
sx_new_stack_array (THREAD *thread, unsigned int argc, unsigned int top) {
	unsigned int i;
	VALUE *value = (VALUE *)sx_malloc (thread->system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = SX_VALUE_ARRAY;
	value->data.array.count = argc;
	value->data.array.size = argc;
	if (argc > 0) {
		value->data.array.list = sx_malloc (thread->system, argc * sizeof (VALUE *));
		if (value->data.array.list == NULL) {
			sx_free_value (value);
			return NULL;
		}

		for (i = 0; i < argc; i ++) {
			value->data.array.list[i] = sx_get_value (thread, top + i);
		}
	} else {
		value->data.array.list = NULL;
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (thread->system, value);

	return value;
}

VALUE *
sx_new_range (SYSTEM *system, int start, int end) {
	VALUE *value;

	value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = SX_VALUE_RANGE;
	value->data.range.start = start;
	value->data.range.end = end;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	sx_add_gc_value (system, value);

	return value;
}

void
sx_free_value (VALUE *value) {
	VAR *rnext;

	if (SX_ISNIL (value) || SX_ISNUM (value)) {
		return;
	}

	if (SX_ISBLOCK (value)) {
		if (value->data.block.nodes != NULL) {
			sx_free (value->data.block.nodes);
		}
	} else if (SX_ISARRAY (value)) {
		if (value->data.array.count > 0) {
			sx_free (value->data.array.list);
		}
	} else if (SX_ISCLASS (value)) {
		while (value->data.klass.members) {
			rnext = value->data.klass.members->next;
			sx_free_var (value->data.klass.members);
			value->data.klass.members = rnext;
		}
		if (value->data.klass.free_data) {
			value->data.klass.free_data (value->data.klass.data);
		}
	}

	sx_free (value);
}

int
sx_is_true (VALUE *value) {
	if (value == NULL) {
		return 0;
	}

	if (SX_ISNUM (value) && SX_TOINT (value) != 0) {
		return 1;
	}
	if (SX_ISSTRING (value) && value->data.str.len > 0) {
		return 1;
	}

	return 0;
}

int
sx_are_equal (VALUE *one, VALUE *two) {
	if (one == two) {
		return 1;
	}

	if (sx_type_of (one) != sx_type_of (two)) {
		return 0;
	}

	switch (sx_type_of (one)) {
		case SX_VALUE_STRING:
			if (one->data.str.len != two->data.str.len) {
				return 0;
			}
			if (one->data.str.len == 0) {
				return 1;
			}
			return !strcmp (one->data.str.str, two->data.str.str);
			break;
		case SX_VALUE_FUNC:
			return one->data.func.args == two->data.func.args && one->data.func.body == two->data.func.body;
			break;
		case SX_VALUE_CFUNC:
			return one->data.cfunc == two->data.cfunc;
			break;
		case SX_VALUE_RANGE:
			return one->data.range.start == two->data.range.start && one->data.range.end == two->data.range.end;
			break;
		default:
			/* everything else must be *exact* value match, handled by pointer compare aboue */
			return 0;
			break;
	}
}

int
sx_compare (VALUE *one, VALUE *two) {
	int n1, n2;

	if (one == two) {
		return 0;
	}
	if (sx_type_of (one) != sx_type_of (two)) {
		return 0;
	}

	switch (sx_type_of (one)) {
		case SX_VALUE_NUM:
			n1 = SX_TOINT(one);
			n2 = SX_TOINT(two);
			return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
		case SX_VALUE_STRING:
			if (one->data.str.len < two->data.str.len) {
				return -1;
			} else if (one->data.str.len > two->data.str.len) {
				return 1;
			}
			if (one->data.str.len == 0) {
				return 0;
			}
			return strcmp (one->data.str.str, two->data.str.str);
			break;
		case SX_VALUE_RANGE:
			n1 = one->data.range.end - one->data.range.start;
			n2 = two->data.range.end - two->data.range.start;
			n1 = n1 < 0 ? -n1 : n1;
			n2 = n2 < 0 ? -n2 : n2;
			return n1 < n2 ? -1 : n1 > n2 ? 1 : 0;
			break;
		default:
			/* everything else must be *exact* value match, handled by pointer compare aboue */
			return 0;
			break;
	}
}

VALUE *
sx_add_to_block (SYSTEM *system, VALUE *block, VALUE *value, int op, unsigned int count) {
	struct _scriptix_node *sx_new_nodes;

	if (SX_ISBLOCK (block)) {
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
		block->data.block.nodes[block->data.block.count].count = count;
		++ block->data.block.count;
		return block;
	} else {
		return sx_new_nil ();
	}
}

VALUE *
sx_get_index (SYSTEM *system, VALUE *cont, int index) {
	unsigned int len;

	if (SX_ISSTRING (cont)) {
		len = cont->data.str.len;
		if (len == 0) {
			return sx_new_str (system, NULL);
		}
		if (index < 0) {
			index += len;
			if (index < 0) {
				index = 0;
			}
		}
		if (index >= len) {
			index = len - 1;
		}
		
		return sx_new_str_len (system, cont->data.str.str + index, 1);
	} else if (SX_ISARRAY (cont)) {
		len = cont->data.array.count;
		if (len == 0) {
			return sx_new_nil ();
		}
		if (index < 0) {
			index += len;
			if (index < 0) {
				index = 0;
			}
		}
		if (index >= len) {
			index = len - 1;
		}
		
		return cont->data.array.list[index];
	} else {
		return sx_new_nil ();
	}
}

VALUE *
sx_get_section (SYSTEM *system, VALUE *base, int start, int end) {
	unsigned int len;
	if (SX_ISSTRING (base)) {
		len = base->data.str.len;
		if (len == 0) {
			return sx_new_str (system, NULL);
		}
		if (start < 0) {
			start += len;
			if (start < 0) {
				start = 0;
			}
		}
		if (start >= len) {
			start = len - 1;
		}
		if (end < 0) {
			end += len;
			if (start < 0) {
				start = 0;
			}
		}
		if (end >= len) {
			end = len - 1;
		}
		return sx_new_str_len (system, base->data.str.str + start, end - start + 1);
	} else {
		return sx_new_nil ();
	}
}

void
sx_print_value (VALUE *value) {
	int i;

	switch (sx_type_of (value)) {
		case SX_VALUE_NIL:
			printf ("(nil)");
			break;
		case SX_VALUE_NUM:
			printf ("%li", SX_TOINT (value));
			break;
		case SX_VALUE_STRING:
			if (value->data.str.len > 0) {
				printf ("%s", value->data.str.str);
			}
			break;
		case SX_VALUE_BLOCK:
			printf ("<block:%p>", value);
			break;
		case SX_VALUE_FUNC:
			printf ("<func:%p>", value);
			break;
		case SX_VALUE_CFUNC:
			printf ("<cfunc:%p>", value);
			break;
		case SX_VALUE_CLASS:
			printf ("<class:%p>", value);
			break;
		case SX_VALUE_ARRAY:
			if (value->data.array.count > 0) {
				printf ("{");
				sx_print_value (value->data.array.list[0]);
				for (i = 1; i < value->data.array.count; i ++) {
					printf (",");
					sx_print_value (value->data.array.list[i]);
				}
				printf ("}");
			} else {
				printf ("{}");
			}
			break;
		case SX_VALUE_RANGE:
			printf ("(%d..%d)", value->data.range.start, value->data.range.end);
			break;
		default:
			printf ("<unknown:%d/%p>", sx_type_of (value), value);
			break;
	}
}

void
sx_lock_value (VALUE *value) {
	if (!SX_ISNUM (value) && !SX_ISNIL (value)) {
		++ value->locks;
	}
}

void
sx_unlock_value (VALUE *value) {
	if (!SX_ISNUM (value) && !SX_ISNIL (value) && value->locks > 0) {
		-- value->locks;
	}
}

void
sx_mark_value (SYSTEM *system, VALUE *value) {
	VAR *var;
	unsigned int i;

	switch (sx_type_of (value)) {
		case SX_VALUE_CFUNC:
		case SX_VALUE_STRING:
		case SX_VALUE_RANGE:
			value->flags |= SX_VFLAG_MARK;
			break;
		case SX_VALUE_BLOCK:
			value->flags |= SX_VFLAG_MARK;
			for (i = 0; i < value->data.block.count; ++ i) {
				if (value->data.block.nodes[i].op == 0) {
					sx_mark_value (system, value->data.block.nodes[i].value);
				}
			}
			break;
		case SX_VALUE_FUNC:
			value->flags |= SX_VFLAG_MARK;
			sx_mark_value (system, value->data.func.args);
			sx_mark_value (system, value->data.func.body);
			break;
		case SX_VALUE_ARRAY:
			value->flags |= SX_VFLAG_MARK;
			for (i = 0; i < value->data.array.count; ++ i) {
				sx_mark_value (system, value->data.array.list[i]);
			}
			break;
		case SX_VALUE_CLASS:
			if (value->data.klass.ref_data) {
				value->data.klass.ref_data (system, value->data.klass.data);
			}
			sx_mark_value (system, value->data.klass.parent);
			for (var = value->data.klass.members; var != NULL; var = var->next) {
				sx_mark_value (system, var->value);
			}
			break;
	}
}
