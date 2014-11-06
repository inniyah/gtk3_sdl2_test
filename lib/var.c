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
define_cfunc (SYSTEM *system, char *name, VALUE *(*func)(THREAD *, VALUE *, unsigned int, unsigned int)) {
	VALUE *cfunc = new_cfunc (system, func);
	if (cfunc == NULL) {
		return NULL;
	}

	return define_global_var (system, new_str (system, name), cfunc);
}

VALUE *
do_define_var (THREAD *thread, VALUE *name, VALUE *value, int scope) {
	VAR *var;

	if (!IS_STRING (name) || name->data.str.len == 0) {
		return NULL;
	}

	if (scope == SCOPE_GLOBAL) {
		return define_global_var (thread->system, name, value);
	}

	if (scope < SCOPE_THREAD && thread->context > 0) {
		for (var = thread->context_stack[thread->context - 1].vars; var != NULL; var = var->next) {
			if (!strcasecmp (var->name->data.str.str, name->data.str.str)) {
				lock_value (value);
				unlock_value (var->value);
				var->value = value;
				unlock_value (value);
				return value;
			}
		}
	}

	if (scope < SCOPE_GLOBAL && (thread->context == 0 || scope != SCOPE_LOCAL)) {
		for (var = thread->vars; var != NULL; var = var->next) {
			if (!strcasecmp (var->name->data.str.str, name->data.str.str)) {
				lock_value (value);
				unlock_value (var->value);
				var->value = value;
				unlock_value (value);
				return value;
			}
		}
	}

	if (scope == SCOPE_DEF || scope == SCOPE_GLOBAL) {
		for (var = thread->system->vars; var != NULL; var = var->next) {
			if (!strcasecmp (var->name->data.str.str, name->data.str.str)) {
				lock_value (value);
				unlock_value (var->value);
				var->value = value;
				unlock_value (value);
				return value;
			}
		}
	}

	lock_value (name);
	lock_value (value);

	var = (VAR *)sx_malloc (thread->system, sizeof (VAR));
	if (var == NULL) {
		unlock_value (value);
		return NULL;
	}

	var->name = name;
	var->value = value;

	if (scope < SCOPE_THREAD && thread->context > 0) {
		var->next = thread->context_stack[thread->context - 1].vars;
		thread->context_stack[thread->context - 1].vars = var;
	} else {
		var->next = thread->vars;
		thread->vars = var;
	}

	unlock_value (value);
	unlock_value (name);

	return value;
}

VALUE *
define_global_var (SYSTEM *system, VALUE *name, VALUE *value) {
	VAR *var;

	for (var = system->vars; var != NULL; var = var->next) {
		if (!strcasecmp (var->name->data.str.str, name->data.str.str)) {
			lock_value (value);
			unlock_value (var->value);
			var->value = value;
			unlock_value (value);
			return value;
		}
	}

	lock_value (name);
	lock_value (value);

	var = (VAR *)sx_malloc (system, sizeof (VAR));
	if (var == NULL) {
		unlock_value (value);
		unlock_value (name);
		return NULL;
	}

	var->name = name;
	var->value = value;
	var->next = system->vars;
	system->vars = var;

	unlock_value (value);
	unlock_value (name);

	return value;
}

VALUE *
do_lookup_var (THREAD *thread, char *name, int scope) {
	VAR *var = get_var (thread, name, scope);

	if (var) {
		return var->value;
	} else {
		return NULL;
	}
}

VALUE *
lookup_global_var (SYSTEM *system, char *name) {
	VAR *var;
	for (var = system->vars; var != NULL; var = var->next) {
		if (!strcasecmp (var->name->data.str.str, name)) {
			return var->value;
		}
	}
	return NULL;
}

VAR *
get_var (THREAD *thread, char *name, int scope) {
	VAR *var;

	/* local or def - not gloval or thread */
	if (scope < SCOPE_THREAD && thread->context > 0) {
		for (var = thread->context_stack[thread->context - 1].vars; var != NULL; var = var->next) {
			if (!strcasecmp (var->name->data.str.str, name)) {
				return var;
			}
		}
		if (scope == SCOPE_LOCAL) {
			return NULL;
		}
	}

	/* def, local, or thread - not global */
	if (scope < SCOPE_GLOBAL) {
		for (var = thread->vars; var != NULL; var = var->next) {
			if (!strcasecmp (var->name->data.str.str, name)) {
				return var;
			}
		}
		if (scope > SCOPE_DEF) {
			return NULL;
		}
	}

	/* must be def or global */
	for (var = thread->system->vars; var != NULL; var = var->next) {
		if (!strcasecmp (var->name->data.str.str, name)) {
			return var;
		}
	}

	return NULL;
}
