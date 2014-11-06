/*
 * Scriptix - Lite-weight scripting longerface
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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "scriptix.h"

static
void
_sx_function_mark (SX_SYSTEM system, SX_FUNC func) {
	if (func->body != NULL) {
		sx_mark_value (system, (SX_VALUE )func->body);
	}
}

static
void
_sx_function_del (SX_SYSTEM system, SX_FUNC func) {
	if (func->arg_names) {
		sx_free (func->arg_names);
	}
}

SX_TYPE 
sx_init_function (SX_SYSTEM system) {
	SX_TYPE type;

	type = sx_new_type (system, "Function");
	if (type == NULL) {
		return NULL;
	}

	type->fmark = (sx_type_mark)_sx_function_mark;
	type->fdel = (sx_type_del)_sx_function_del;

	return type;
}

SX_FUNC
sx_new_func (SX_SYSTEM system, sx_name_id id, sx_name_id *args, sx_name_id varg, SX_BLOCK body) {
	SX_FUNC func;

	func = (SX_FUNC )sx_malloc (sizeof (struct scriptix_func));
	if (func == NULL) {
		return NULL;
	}
	if (args != NULL) {
		func->argc = sx_sizeof_namelist (args);
		func->arg_names = sx_dupmem (args, func->argc * sizeof (sx_name_id));
		if (func->arg_names == NULL) {
			sx_free (func);
			return NULL;
		}
	} else {
		func->arg_names = NULL;
		func->argc = 0;
	}

	func->id = id;
	func->var_arg_name = varg;
	func->body = body;
	func->cfunc = NULL;
	func->next = NULL;

	sx_clear_value (system, &func->header, system->cfunction);

	return func;
}

SX_FUNC
sx_new_cfunc (SX_SYSTEM system, sx_name_id id, unsigned long argc, int varg, sx_cfunc cfunc) {
	SX_FUNC func ;
	
	func = (SX_FUNC )sx_malloc (sizeof (struct scriptix_func));
	if (func == NULL) {
		return NULL;
	}

	func->cfunc = cfunc;
	func->body = NULL;
	func->arg_names = NULL;
	func->var_arg_name = varg;
	func->argc = argc;
	func->id = id;
	func->next = NULL;

	sx_clear_value (system, &func->header, system->cfunction);

	return func;
}

SX_FUNC 
sx_add_func (SX_SYSTEM system, SX_FUNC func) {
	if (func == NULL || system == NULL) {
		return NULL;
	}

	func->next = system->funcs;
	system->funcs = func;

	return func;
}

SX_FUNC 
sx_get_func (SX_SYSTEM system, sx_name_id name) {
	SX_FUNC func;

	for (func = system->funcs; func != NULL; func = func->next) {
		if (func->id == name)
			return func;
	}
		
	return NULL;
}

SX_FUNC
sx_define_cfunc (SX_SYSTEM system, const char* name, unsigned long argc, int varg, sx_cfunc func)
{
	SX_FUNC sfunc = (SX_FUNC)sx_new_cfunc (system, sx_name_to_id (name), argc, varg, func);
	if (sfunc == NULL)
		return NULL;

	return sx_add_func (system, sfunc);
}
