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

#include <stdlib.h>

#include "scriptix.h"

SX_MODULE *
sx_new_module (SX_SYSTEM *system, sx_name_id id, SX_MODULE *parent) {
	SX_MODULE *mod = sx_malloc (system, sizeof (SX_MODULE));
	if (mod == NULL) {
		return NULL;
	}

	if (parent != NULL) {
		sx_ref_module (parent);
	} else {
		parent = system->core;
	}
	mod->parent = parent;

	mod->name = id;
	mod->funcs = NULL;
	mod->classes = NULL;
	mod->system = system;
	mod->refs = 1;
	mod->next = system->modules;
	mod->prev = NULL;
	system->modules = mod;

	return mod;
}

unsigned long
sx_ref_module (SX_MODULE *module) {
	return ++ module->refs;
}

unsigned long
sx_unref_module (SX_MODULE *module) {
	if ((-- module->refs) == 0) {
		sx_free_module (module);
		return 0;
	} else {
		return module->refs;
	}
}

void
sx_mark_module (SX_MODULE *module) {
	SX_FUNC *func;
	SX_CLASS *klass;

	for (func = module->funcs; func != NULL; func = func->next) {
		sx_mark_func (module->system, func);
	}

	for (klass = module->classes; klass != NULL; klass = klass->next) {
		sx_mark_class (module->system, klass);
	}
}

void
sx_free_module (SX_MODULE *module) {
	SX_FUNC *nfunc;
	SX_CLASS *nclass;

	if (module->prev != NULL) {
		module->prev->next = module->next;
	} else {
		module->system->modules = module->next;
	}
	if (module->next != NULL) {
		module->next->prev = module->prev;
	}

	if (module->parent != NULL) {
		sx_unref_module (module->parent);
	}

	while (module->funcs != NULL) {
		nfunc = module->funcs->next;
		sx_unref_func (module->funcs);
		module->funcs = nfunc;
	}

	while (module->classes != NULL) {
		nclass = module->classes->next;
		sx_unref_class (module->classes);
		module->classes = nclass;
	}
}

SX_CLASS *
sx_add_class (SX_MODULE *module, SX_CLASS *klass) {
	if (klass == NULL || module == NULL) {
		return NULL;
	}

	sx_ref_class (klass);
	klass->next = module->classes;
	module->classes = klass;

	return klass;
}

SX_CLASS *
sx_get_class (SX_MODULE *module, sx_name_id id) {
	SX_CLASS *klass;

	while (module != NULL) {
		for (klass = module->classes; klass != NULL; klass = klass->next) {
			if (klass->id == id) {
				return klass;
			}
		}
		module = module->parent;
	}

	return NULL;
}

SX_FUNC *
sx_add_func (SX_MODULE *module, SX_FUNC *func) {
	if (func == NULL || module == NULL) {
		return NULL;
	}

	sx_ref_func (func);
	func->next = module->funcs;
	module->funcs = func;

	return func;
}

SX_FUNC *
sx_get_func (SX_MODULE *module, sx_name_id name) {
	SX_FUNC *func;

	while (module != NULL) {
		for (func = module->funcs; func != NULL; func = func->next) {
			if (func->id == name)
				return func;
		}
		module = module->parent;
	}
		
	return NULL;
}
