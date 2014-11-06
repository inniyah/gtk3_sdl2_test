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
_sx_search_call (SX_CALL *call, unsigned int id) {
	SX_VAR *var;

	for (var = call->vars; var != NULL; var = var->next) {
		if (id == var->id) {
			return var;
		}
	}

	return NULL;
}

SX_VALUE *
sx_define_var (SX_THREAD *thread, unsigned int id, SX_VALUE *value, int scope) {
	SX_VAR *var;

	if (scope == SX_SCOPE_GLOBAL) {
		return sx_define_system_var (thread->system, id, value);
	}

	if (scope == SX_SCOPE_CLASS) {
		if (thread->call_stack[thread->call - 1].klass != NULL) {
			var = sx_set_member (thread->system, thread->call_stack[thread->call - 1].klass, id, value);
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

SX_VALUE *
sx_define_system_var (SX_SYSTEM *system, unsigned int id, SX_VALUE *value) {
	SX_VAR *var;

	for (var = system->vars; var != NULL; var = var->next) {
		if (id == var->id) {
			var->value = value;
			return value;
		}
	}

	sx_lock_value (value);
	var = (SX_VAR *)sx_malloc (system, sizeof (SX_VAR));
	sx_unlock_value (value);

	if (var == NULL) {
		return NULL;
	}

	var->id = id;
	var->value = value;
	var->flags = 0;
	var->next = system->vars;
	system->vars = var;

	return value;
}

SX_VAR *
sx_get_var (SX_THREAD *thread, unsigned int id, int scope) {
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

	if (scope != SX_SCOPE_GLOBAL) {
		if (thread->call_stack[thread->call - 1].klass != NULL) {
			var = sx_find_member (thread->system, thread->call_stack[thread->call - 1].klass, id);
			if (var != NULL) {
				return var;
			}
		}
	}

	/* only get here on system or def search */
	if (scope != SX_SCOPE_CLASS) {
		return sx_get_system_var (thread->system, id);
	}

	return NULL;
}

SX_VAR *
sx_get_system_var (SX_SYSTEM *system, unsigned int id) {
	SX_VAR *var;
	for (var = system->vars; var != NULL; var = var->next) {
		if (id == var->id) {
			return var;
		}
	}
	return NULL;
}
