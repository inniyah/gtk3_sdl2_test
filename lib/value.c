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
new_str (SYSTEM *system, char *str) {
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

	value->type = VALUE_STRING;
	if (str == NULL) {
		value->data.str.len = 0;
	} else {
		value->data.str.len = strlen (str);
		strcpy (value->data.str.str, str);
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	add_gc_value (system, value);

	return value;
}

VALUE *
new_block (SYSTEM *system) {
	VALUE *value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_BLOCK;
	value->data.nodes = NULL;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	add_gc_value (system, value);

	return value;
}

VALUE *
new_func (SYSTEM *system, VALUE *args, VALUE *body) {
	VALUE *value;

	if (!IS_BLOCK (body)) {
		return NULL;
	}
	if (!IS_NIL (args) && !IS_ARRAY (args)) {
		return NULL;
	}
	
	value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_FUNC;
	value->data.func.args = args;
	value->data.func.body = body;
	value->locks = 0;
	value->gc_next = NULL;
	value->flags = 0;

	add_gc_value (system, value);

	return value;
}

VALUE *
new_cfunc (SYSTEM *system, VALUE *(*cfunc)(THREAD *, VALUE *self, unsigned int argc, unsigned int top)) {
	VALUE *value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_CFUNC;
	value->data.cfunc = cfunc;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	add_gc_value (system, value);

	return value;
}

VALUE *
new_array (SYSTEM *system, unsigned int argc, VALUE **argv) {
	VALUE *value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_ARRAY;
	value->data.array.count = argc;
	value->data.array.size = argc;
	if (argc > 0) {
		if (argv != NULL) {
			value->data.array.list = sx_dupmem (system, argv, argc * sizeof (VALUE *));
			if (value->data.array.list == NULL) {
				free_value (value);
				return NULL;
			}
		} else {
			value->data.array.list = sx_malloc (system, argc * sizeof (VALUE *));
			if (value->data.array.list == NULL) {
				free_value (value);
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

	add_gc_value (system, value);
	

	return value;
}

VALUE *
new_stack_array (THREAD *thread, unsigned int argc, unsigned int top) {
	unsigned int i;
	VALUE *value = (VALUE *)sx_malloc (thread->system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_ARRAY;
	value->data.array.count = argc;
	value->data.array.size = argc;
	if (argc > 0) {
		value->data.array.list = sx_malloc (thread->system, argc * sizeof (VALUE *));
		if (value->data.array.list == NULL) {
			free_value (value);
			return NULL;
		}

		for (i = 0; i < argc; i ++) {
			value->data.array.list[i] = get_value (thread, top + i);
		}
	} else {
		value->data.array.list = NULL;
	}

	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	add_gc_value (thread->system, value);

	return value;
}

VALUE *
new_class (SYSTEM *system, VALUE *parent) {
	VALUE *value;

	lock_value (parent);
	value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	unlock_value (parent);
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_CLASS;
	value->data.klass.parent = parent;
	value->data.klass.members = NULL;
	value->data.klass.data = NULL;
	value->data.klass.ref_data = NULL;
	value->data.klass.free_data = NULL;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	add_gc_value (system, value);

	return value;
}

VALUE *
new_user_class (SYSTEM *system, VALUE *parent, void *data, void (*free_data)(void *data), void (*ref_data)(SYSTEM *system, void *data)) {
	VALUE *value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_CLASS;
	value->data.klass.parent = parent;
	value->data.klass.members = NULL;
	value->data.klass.data = data;
	value->data.klass.ref_data = ref_data;
	value->data.klass.free_data = free_data;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	add_gc_value (system, value);

	return value;
}

VALUE *
new_range (SYSTEM *system, int start, int end) {
	VALUE *value;

	value = (VALUE *)sx_malloc (system, sizeof (VALUE));
	if (value == NULL) {
		return NULL;
	}

	value->type = VALUE_RANGE;
	value->data.range.start = start;
	value->data.range.end = end;
	value->locks = 0;
	value->flags = 0;
	value->gc_next = NULL;

	add_gc_value (system, value);

	return value;
}

int
class_is_a (VALUE *klass, VALUE *par) {
	if (!IS_CLASS (klass) || !IS_CLASS (par)) {
		return 0;
	}

	while (klass != NULL && klass != par) {
		klass = klass->data.klass.parent;
	}

	return klass != NULL;
}

VAR *
set_member (SYSTEM *system, VALUE *klass, VALUE *name, VALUE *value) {
	VAR *var;

	for (var = klass->data.klass.members; var != NULL; var = var->next) {
		if (are_equal (name, var->name)) {
			var->value = value;
			return var;
		}
	}

	lock_value (klass);
	lock_value (value);
	lock_value (name);

	var = (VAR *)sx_malloc (system, sizeof (VAR));

	unlock_value (klass);
	unlock_value (value);
	unlock_value (name);

	if (var == NULL) {
		return NULL;
	}

	var->name = name;
	var->value = value;
	var->next = klass->data.klass.members;
	klass->data.klass.members = var;

	return var;
}

VALUE *
get_member (VALUE *klass, VALUE *name) {
	VAR *var;

	while (klass != NULL) {
		for (var = klass->data.klass.members; var != NULL; var = var->next) {
			if (are_equal (name, var->name)) {
				return var->value;
			}
		}
		klass = klass->data.klass.parent;
	}

	return new_nil ();
}

void
free_value (VALUE *value) {
	VAR *rnext;
	struct _scriptix_node *next;

	if (IS_NIL (value) || IS_NUM (value)) {
		return;
	}

	if (IS_BLOCK (value)) {
		while (value->data.nodes != NULL) {
			next = value->data.nodes->next;
			sx_free (value->data.nodes);
			value->data.nodes = next;
		}
	} else if (IS_ARRAY (value)) {
		if (value->data.array.count > 0) {
			sx_free (value->data.array.list);
		}
	} else if (IS_CLASS (value)) {
		while (value->data.klass.members) {
			rnext = value->data.klass.members->next;
			free_var (value->data.klass.members);
			value->data.klass.members = rnext;
		}
		if (value->data.klass.free_data) {
			value->data.klass.free_data (value->data.klass.data);
		}
	}

	sx_free (value);
}

int
is_true (VALUE *value) {
	if (value == NULL) {
		return 0;
	}

	if (IS_NUM (value) && TO_INT (value) != 0) {
		return 1;
	}
	if (IS_STRING (value) && value->data.str.len > 0) {
		return 1;
	}

	return 0;
}

int
are_equal (VALUE *one, VALUE *two) {
	if (one == two) {
		return 1;
	}

	if (type_of (one) != type_of (two)) {
		return 0;
	}

	switch (type_of (one)) {
		case VALUE_STRING:
			if (one->data.str.len != two->data.str.len) {
				return 0;
			}
			if (one->data.str.len == 0) {
				return 1;
			}
			return !strcasecmp (one->data.str.str, two->data.str.str);
			break;
		case VALUE_FUNC:
			return one->data.func.args == two->data.func.args && one->data.func.body == two->data.func.body;
			break;
		case VALUE_CFUNC:
			return one->data.cfunc == two->data.cfunc;
			break;
		case VALUE_RANGE:
			return one->data.range.start == two->data.range.start && one->data.range.end == two->data.range.end;
			break;
		default:
			/* everything else must be *exact* value match, handled by pointer compare aboue */
			return 0;
			break;
	}
}

VALUE *
add_value (SYSTEM *system, VALUE *block, VALUE *value) {
	struct _scriptix_node *f;

	if (IS_BLOCK (block)) {
		if (block->data.nodes == NULL) {
			lock_value (value);
			block->data.nodes = sx_malloc (system, sizeof (struct _scriptix_node));
			unlock_value (value);
			if (block->data.nodes == NULL) {
				return new_nil ();
			}
			block->data.nodes->next = NULL;
			block->data.nodes->value = value;
			block->data.nodes->op = 0;
			block->data.nodes->count = 0;
		} else {
			for (f = block->data.nodes; f->next != NULL; f = f->next)
				;
			lock_value (value);
			f->next = sx_malloc (system, sizeof (struct _scriptix_node));
			unlock_value (value);
			if (f->next == NULL) {
				return new_nil ();
			}
			f->next->next = NULL;
			f->next->value = value;
			f->next->op = 0;
			f->next->count = 0;
		}
		return block;
	} else {
		return new_nil ();
	}
}

VALUE *
add_stmt (SYSTEM *system, VALUE *block, int op, unsigned int count) {
	struct _scriptix_node *f;

	if (IS_BLOCK (block)) {
		if (block->data.nodes == NULL) {
			block->data.nodes = sx_malloc (system, sizeof (struct _scriptix_node));
			if (block->data.nodes == NULL) {
				return new_nil ();
			}
			block->data.nodes->next = NULL;
			block->data.nodes->value = NULL;
			block->data.nodes->op = op;
			block->data.nodes->count = count;
		} else {
			for (f = block->data.nodes; f->next != NULL; f = f->next)
				;
			f->next = sx_malloc (system, sizeof (struct _scriptix_node));
			if (f->next == NULL) {
				return new_nil ();
			}
			f->next->next = NULL;
			f->next->value = NULL;
			f->next->op = op;
			f->next->count = count;
		}
		return block;
	} else {
		return new_nil ();
	}
}

void
print_value (VALUE *value) {
	int i;

	switch (type_of (value)) {
		case VALUE_NIL:
			printf ("(nil)");
			break;
		case VALUE_NUM:
			printf ("%li", TO_INT (value));
			break;
		case VALUE_STRING:
			if (value->data.str.len > 0) {
				printf ("%s", value->data.str.str);
			}
			break;
		case VALUE_BLOCK:
			printf ("<block:%p>", value);
			break;
		case VALUE_FUNC:
			printf ("<func:%p>", value);
			break;
		case VALUE_CFUNC:
			printf ("<cfunc:%p>", value);
			break;
		case VALUE_CLASS:
			printf ("<class:%p>", value);
			break;
		case VALUE_ARRAY:
			if (value->data.array.count > 0) {
				printf ("{");
				print_value (value->data.array.list[0]);
				for (i = 1; i < value->data.array.count; i ++) {
					printf (",");
					print_value (value->data.array.list[i]);
				}
				printf ("}");
			} else {
				printf ("{}");
			}
			break;
		case VALUE_RANGE:
			printf ("(%d..%d)", value->data.range.start, value->data.range.end);
			break;
		default:
			printf ("<unknown:%d/%p>", type_of (value), value);
			break;
	}
}

void
lock_value (VALUE *value) {
	if (!IS_NUM (value) && !IS_NIL (value)) {
		++ value->locks;
	}
}

void
unlock_value (VALUE *value) {
	if (!IS_NUM (value) && !IS_NIL (value) && value->locks > 0) {
		-- value->locks;
	}
}

void
mark_value (SYSTEM *system, VALUE *value) {
	VAR *var;
	struct _scriptix_node *node;
	int i;

	switch (type_of (value)) {
		case VALUE_CFUNC:
		case VALUE_STRING:
		case VALUE_RANGE:
		case VALUE_NODE:
			value->flags |= VFLAG_MARK;
			break;
		case VALUE_BLOCK:
			value->flags |= VFLAG_MARK;
			for (node = value->data.nodes; node != NULL; node = node->next) {
				if (node->op == 0) {
					mark_value (system, node->value);
				}
			}
			break;
		case VALUE_FUNC:
			value->flags |= VFLAG_MARK;
			mark_value (system, value->data.func.args);
			mark_value (system, value->data.func.body);
			break;
		case VALUE_ARRAY:
			value->flags |= VFLAG_MARK;
			for (i = 0; i < value->data.array.count; ++ i) {
				mark_value (system, value->data.array.list[i]);
			}
			break;
		case VALUE_CLASS:
			if (value->data.klass.ref_data) {
				value->data.klass.ref_data (system, value->data.klass.data);
			}
			mark_value (system, value->data.klass.parent);
			for (var = value->data.klass.members; var != NULL; var = var->next) {
				mark_value (system, var->value);
			}
			break;
	}
}
