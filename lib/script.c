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
#include "config.h"

sx_script_id
sx_new_script (SX_SYSTEM *system, char *name, char *path, SX_VALUE *block) {
	SX_SCRIPT *script;
	static unsigned int _free_id = 0; /* ID tag for scripts */

	sx_lock_value (block);
	script = sx_malloc (system, sizeof (SX_SCRIPT));
	sx_unlock_value (block);

	if (script == NULL) {
		return 0;
	}

	script->name = sx_strdup (system, name);
	script->path = sx_strdup (system, path);

	script->block = block;

	script->next = system->scripts;
	system->scripts = script;

	script->id =  ++_free_id;
	return script->id;
}

void
sx_free_script (SX_SCRIPT *script) {
	if (script->name) {
		sx_free (script->name);
	}
	if (script->path) {
		sx_free (script->path);
	}

	sx_free (script);
}

sx_thread_id
sx_start_script (SX_SYSTEM *system, sx_script_id id, SX_VALUE *argv) {
	SX_SCRIPT *script;

	for (script = system->scripts; script != NULL; script = script->next) {
		if (script->id == id) {
			return sx_create_thread (system, script->block, argv);
		}
	}

	return 0;
}
