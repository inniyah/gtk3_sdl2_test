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
#include <stdio.h>
#include <string.h>

#include "scriptix.h"

int
main (int argc, char **argv) {
	THREAD *thread;
	SYSTEM *system;
	VALUE *value;
	int ret;

	system = sx_create_system (argc - 1, argv + 1);
	sx_init_stdlib (system);

	if (argc > 1 && strcmp (argv[1], "-")) {
		value = sx_load_file (system, argv[1]);
	} else {
		value = sx_load_file (system, NULL);
	}

	if (value == NULL) {
		sx_free_system (system);
		return 1;
	}
	
	thread = sx_create_thread (system, value);
	if (thread == NULL) {
		sx_free_system (system);
		return 1;
	}

	ret = sx_run_thread (thread);
	if (ret != SX_STATE_EXIT) {
		return 1;
	}
 
	ret = SX_ISNUM (thread->ret) ? SX_TOINT (thread->ret) : sx_is_true (thread->ret);

	sx_free_system (system);

	return ret;
}
