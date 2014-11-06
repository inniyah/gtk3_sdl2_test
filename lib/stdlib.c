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
sx_stdlib_print (THREAD *thread, VALUE *self, unsigned int argc, unsigned int top) {
	unsigned int i;
	for (i = 0; i < argc; i ++) {
		sx_print_value (sx_get_value (thread, top + i));
	}
	printf ("\n");
	return sx_new_nil ();
}

VALUE *
sx_stdlib_concat (THREAD *thread, VALUE *self, unsigned int argc, unsigned int top) {
	VALUE *ret, *one, *two;

	if (argc != 2) {
		return sx_new_nil ();
	}

	one = sx_get_value (thread, top);
	two = sx_get_value (thread, top + 1);

	if (sx_type_of (one) != sx_type_of (two)) {
		return sx_new_nil ();
	}

	if (SX_ISSTRING (one)) {
		ret = sx_new_str_len (thread->system, NULL, one->data.str.len + one->data.str.len);
		if (ret == NULL) {
			return sx_new_nil ();
		}
		if (one->data.str.len > 0) {
			strcpy (SX_TOSTR (ret), SX_TOSTR (one));
		}
		if (two->data.str.len > 0) {
			strcpy (SX_TOSTR (ret) + one->data.str.len, SX_TOSTR (two));
		}
		return ret;
	} else if (SX_ISARRAY (two)) {
		/* FIXME */
	}

	return sx_new_nil ();
}

void
sx_init_stdlib (SYSTEM *system) {
	sx_define_cfunc (system, "print", sx_stdlib_print);
	sx_define_cfunc (system, "concat", sx_stdlib_concat);
}
