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

	var = do_get_var (thread, name, scope);
	if (var != NULL) {
		lock_value (value);
		unlock_value (var->value);
		var->value = value;
		unlock_value (value);
		return value;
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

	if (scope == SCOPE_THREAD) {
		var->next = thread->context_stack[0].vars;
		thread->context_stack[0].vars = var;
	} else {
		var->next = thread->context_stack[thread->context - 1].vars;
		thread->context_stack[thread->context - 1].vars = var;
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

VAR *
do_get_var (THREAD *thread, VALUE *name, int scope) {
	VAR *var;
	int c = 0;

	/* local search only */
	if (scope == SCOPE_LOCAL) {
		for (var = thread->context_stack[thread->context - 1].vars; var != NULL; var = var->next) {
			if (are_equal (var->name, name)) {
				return var;
			}
		}
		return NULL;
	}

	/* thread search only */
	if (scope == SCOPE_THREAD) {
		for (var = thread->context_stack[0].vars; var != NULL; var = var->next) {
			if (are_equal (var->name, name)) {
				return var;
			}
		}
		return NULL;
	}

	/* default - search thru contexts until top/hard context break */
	if (scope == SCOPE_DEF) {
		for (c = thread->context - 1; c >= 0; -- c) {
			for (var = thread->context_stack[c].vars; var != NULL; var = var->next) {
				if (are_equal (var->name, name)) {
					return var;
				}
			}
			if ((thread->context_stack[c].flags & CFLAG_HARD) != 0 && c != 0) {
				c = 1; /* next loop, c will == 0, thus scan thread scope */
			}
		}
	}

	/* only get here on global or def search */
	return get_global_var (thread->system, name);
}

VAR *
get_global_var (SYSTEM *system, VALUE *name) {
	VAR *var;
	for (var = system->vars; var != NULL; var = var->next) {
		if (are_equal (var->name, name)) {
			return var;
		}
	}
	return NULL;
}
