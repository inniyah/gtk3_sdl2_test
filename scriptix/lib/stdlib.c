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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "scriptix.h"

SX_DEFINE_CFUNC (sx_stdlib_print) {
	unsigned int i;
	for (i = 0; i < sx_argc; i ++) {
		sx_print_value (sx_thread->system, sx_argv[i]);
	}
}

SX_DEFINE_CFUNC (sx_stdlib_printl) {
	sx_stdlib_print (sx_thread, sx_self, sx_argc, sx_argv, NULL);
	sx_thread->system->print_hook ("\r\n");
}

SX_DEFINE_CFUNC (sx_stdlib_get_tid) {
	*sx_ret = sx_new_num ((long)sx_thread >> 2);
}

int
sx_init_stdlib (SX_SYSTEM system) {
	if (sx_define_cfunc (system, "print", 0, 1, sx_stdlib_print) == NULL)
		return SXE_INTERNAL;
	if (sx_define_cfunc (system, "printl", 0, 1, sx_stdlib_printl) == NULL)
		return SXE_INTERNAL;
	if (sx_define_cfunc (system, "get_tid", 0, 0, sx_stdlib_get_tid) == NULL)
		return SXE_INTERNAL;

	return SXE_OK;
}
