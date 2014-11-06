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
stdlib_print (THREAD *thread, VALUE *self, unsigned int argc, unsigned int top) {
	unsigned int i;
	for (i = 0; i < argc; i ++) {
		print_value (get_value (thread, top + i));
	}
	printf ("\n");
	return new_nil ();
}

VALUE *
stdlib_class_print (THREAD *thread, VALUE *self, unsigned int argc, unsigned int top) {
	VAR *var;
	printf ("<<CLASS:");
	for (var = self->data.klass.members; var != NULL; var = var->next) {
		printf ("\n  %s->", var->name->data.str.str);
		print_value (var->value);
	}
	printf ("\n>>\n");
	return new_nil ();
}

void
init_stdlib (SYSTEM *system) {
	VALUE *class;

	define_cfunc (system, "print", stdlib_print);

	/*
	class = new_class (system, NULL);
	lock_value (class);
	define_global_var (system, "testing", class);
	class = lookup_global_var (system, "testing");
	set_member (system, class, "print", new_cfunc (system, stdlib_class_print));
	unlock_value (class);
	*/
}
