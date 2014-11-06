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

__INLINE__
SX_VAR *
_sx_search_call (SX_CALL *call, sx_name_id id) {
	SX_VAR *var;

	for (var = call->vars; var != NULL; var = var->next) {
		if (id == var->id) {
			return var;
		}
	}

	return NULL;
}

SX_VALUE *
sx_define_var (SX_THREAD *thread, sx_name_id id, SX_VALUE *value, sx_scope_type scope) {
	SX_VAR *var;

	if (scope == SX_SCOPE_CLASS) {
		if (SX_ISOBJECT (thread->system, thread->call_stack[thread->call - 1].klass)) {
			var = sx_set_member (thread->system, (SX_OBJECT *)thread->call_stack[thread->call - 1].klass, id, value);
			return var->value;
		} else {
			return sx_new_nil ();
		}
	}

	var = sx_get_var (thread, id, scope);
	if (var != NULL) {
		var->value = value;
		return value;
	}

	sx_lock_value (value);
	var = (SX_VAR *)sx_malloc (thread->system, sizeof (SX_VAR));
	sx_unlock_value (value);
	
	if (var == NULL) {
		return NULL;
	}

	var->id = id;
	var->value = value;
	var->flags = 0;

	var->next = thread->call_stack[thread->call - 1].vars;
	thread->call_stack[thread->call - 1].vars = var;

	return value;
}

SX_VAR *
sx_get_var (SX_THREAD *thread, sx_name_id id, sx_scope_type scope) {
	SX_VAR *var;

	/* local search only */
	if (scope == SX_SCOPE_LOCAL) {
		return _sx_search_call (&thread->call_stack[thread->call - 1], id);
	}

	/* default - search thru calls until top/hard call break */
	if (scope == SX_SCOPE_DEF) {
		var = _sx_search_call (&thread->call_stack[thread->call - 1], id);
		if (var != NULL) {
			return var;
		}

		if (thread->call > 1) {
			var = _sx_search_call (&thread->call_stack[0], id);
			if (var != NULL) {
				return var;
			}
		}
	}

	if (SX_ISOBJECT (thread->system, thread->call_stack[thread->call - 1].klass)) {
		var = sx_find_member (thread->system, (SX_OBJECT *)thread->call_stack[thread->call - 1].klass, id);
		if (var != NULL) {
			return var;
		}
	}

	return NULL;
}

void
sx_free_var (SX_VAR *var) {
	sx_free (var);
}
