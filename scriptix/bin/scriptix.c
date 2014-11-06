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
main (int argc, const char **argv) {
	SX_SYSTEM system;
	SX_FUNC func;
	SX_VALUE* sargv;
	int i;

	system = sx_create_system ();
	if (system == NULL) {
		fprintf (stderr, "sx_create_system() failed.\n");
		return 1;
	}
	if (sx_init_stdlib (system) != SXE_OK) {
		fprintf (stderr, "sx_init_stdlib() failed.\n");
		return 1;
	}

	if (argc > 1 && strcmp (argv[1], "-")) {
		if (sxp_load_file (system, argv[1]))
			return 1;
	} else {
		if (sxp_load_file (system, NULL))
			return 1;
	}

	func = sx_get_func (system, sx_name_to_id ("main"));
	if (func == NULL) {
		fprintf (stderr, "Fatal error: No main() function defined.\n");
	} else {
		sargv = (SX_VALUE*)malloc((argc - 2) * sizeof (SX_VALUE));
		for (i = 2; i < argc; ++i) {
			sargv[i - 2] = (SX_VALUE)sx_new_str (system, argv[i]);
		}

		sx_create_thread (system, (SX_VALUE)func, argc - 2, sargv);
		while (sx_runable (system))
			sx_run (system);
	}

	sx_free_system (system);

	return 0;
}
