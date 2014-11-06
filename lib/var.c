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


VALUE *
sx_define_cfunc (SYSTEM *system, char *name, VALUE *(*func)(THREAD *, VALUE *, unsigned int, unsigned int)) {
	VALUE *cfunc = sx_new_cfunc (system, func);
	if (cfunc == NULL) {
		return NULL;
	}

	return sx_define_system_var (system, sx_name_to_id (name), cfunc);
}

VALUE *
sx_define_var (THREAD *thread, unsigned int id, VALUE *value, int scope) {
	VAR *var;

	if (scope == SX_SCOPE_GLOBAL) {
		return sx_define_system_var (thread->system, id, value);
	}

	var = sx_get_var (thread, id, scope);
	if (var != NULL) {
		var->value = value;
		return value;
	}

	sx_lock_value (value);
	var = (VAR *)sx_malloc (thread->system, sizeof (VAR));
	sx_unlock_value (value);
	
	if (var == NULL) {
		return NULL;
	}

	var->id = id;
	var->value = value;

	if (scope == SX_SCOPE_THREAD) {
		var->next = thread->context_stack[0].vars;
		thread->context_stack[0].vars = var;
	} else {
		var->next = thread->context_stack[thread->context - 1].vars;
		thread->context_stack[thread->context - 1].vars = var;
	}

	return value;
}

VALUE *
sx_define_system_var (SYSTEM *system, unsigned int id, VALUE *value) {
	VAR *var;

	for (var = system->vars; var != NULL; var = var->next) {
		if (id == var->id) {
			var->value = value;
			return value;
		}
	}

	sx_lock_value (value);
	var = (VAR *)sx_malloc (system, sizeof (VAR));
	sx_unlock_value (value);

	if (var == NULL) {
		return NULL;
	}

	var->id = id;
	var->value = value;
	var->next = system->vars;
	system->vars = var;

	return value;
}

VAR *
sx_get_var (THREAD *thread, unsigned int id, int scope) {
	VAR *var;
	int c = 0;

	/* local search only */
	if (scope == SX_SCOPE_LOCAL) {
		for (var = thread->context_stack[thread->context - 1].vars; var != NULL; var = var->next) {
			if (id == var->id) {
				return var;
			}
		}
		return NULL;
	}

	/* thread search only */
	if (scope == SX_SCOPE_THREAD) {
		for (var = thread->context_stack[0].vars; var != NULL; var = var->next) {
			if (id == var->id) {
				return var;
			}
		}
		return NULL;
	}

	/* default - search thru contexts until top/hard context break */
	if (scope == SX_SCOPE_DEF) {
		for (c = thread->context - 1; c >= 0; -- c) {
			for (var = thread->context_stack[c].vars; var != NULL; var = var->next) {
				if (id == var->id) {
					return var;
				}
			}
			if ((thread->context_stack[c].flags & SX_CFLAG_HARD) != 0 && c != 0) {
				c = 1; /* next loop, c will == 0, thus scan thread scope */
			}
		}
	}

	/* only get here on system or def search */
	return sx_get_system_var (thread->system, id);
}

VAR *
sx_get_system_var (SYSTEM *system, unsigned int id) {
	VAR *var;
	for (var = system->vars; var != NULL; var = var->next) {
		if (id == var->id) {
			return var;
		}
	}
	return NULL;
}
