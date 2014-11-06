/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003  AwesomePlay Productions, Inc.
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
#include "config.h"

using namespace Scriptix;

#include "parser.h"

struct _scriptix_name_id {
	char *name;
	struct _scriptix_name_id *next;
};

static struct _scriptix_name_id *_names = NULL;
static struct _scriptix_name_id *_last = NULL;

sx_name_id
Scriptix::NameToID(const char *name) {
	struct _scriptix_name_id *ni;
	sx_name_id id;

	if (name == NULL)
		return 0;

	id = 1;
	ni = _names;
	while (ni != NULL) {
		if (!strcmp (name, ni->name)) {
			return id;
		}
		++ id;
		ni = ni->next;
	}

	ni = (struct _scriptix_name_id*)malloc (sizeof (struct _scriptix_name_id));
	if (ni == NULL) {
		return 0;
	}
	ni->name = strdup (name);
	if (ni->name == NULL) {
		free (ni);
		return 0;
	}

	ni->next = NULL;
	if (_last != NULL) {
		_last->next = ni;
		_last = ni;
	} else {
		_last = _names = ni;
	}

	return id;
}

const char *
Scriptix::IDToName (sx_name_id id) {
	struct _scriptix_name_id *ni;

	if (!id) {
		return NULL;
	}

	ni = _names;
	while (ni != NULL) {
		if (--id == 0) {
			return ni->name;
		}
		ni = ni->next;
	}

	return NULL;
}

sx_name_id *
Scriptix::sx_new_namelist (System* system, size_t argc, ...) {
	sx_name_id *list;
	va_list va;
	size_t i;

	if (argc == 0) {
		return NULL;
	}

	list = (sx_name_id*)malloc ((argc + 1) * sizeof (sx_name_id));
	if (list == NULL) {
		return NULL;
	}

	va_start (va, argc);
	for (i = 0; i < argc; ++ i) {
		list[i] = va_arg (va, sx_name_id);
	}
	va_end (va);

	list[i] = 0;

	return list;
}

sx_name_id*
Scriptix::sx_namelist_append (System* system, sx_name_id* list, sx_name_id id)
{
	sx_name_id* newlist;
	size_t c = sx_sizeof_namelist (list);

	newlist = (sx_name_id*)malloc ((c + 2) * sizeof (sx_name_id));
	if (newlist == NULL) {
		return NULL;
	}

	memcpy (newlist, list, c * sizeof (sx_name_id));
	free (list);

	newlist[c] = id;
	newlist[c + 1] = 0;

	return newlist;
}

sx_name_id*
Scriptix::sx_namelist_concat (System* system, sx_name_id* list, sx_name_id* list2)
{
	sx_name_id* newlist;
	size_t c1 = sx_sizeof_namelist (list);
	size_t c2 = sx_sizeof_namelist (list2);
	size_t i;

	newlist = (sx_name_id*)malloc ((c1 + c2 + 1) * sizeof (sx_name_id));
	if (newlist == NULL) {
		return NULL;
	}

	for (i = 0; i < c1; ++i)
		newlist[i] = list[i];
	for (; i < c1 + c2; ++i)
		newlist[i] = list2[i - c1];
	free (list);
	free (list2);

	newlist[c1 + c2] = 0;

	return newlist;
}

size_t
Scriptix::sx_sizeof_namelist (sx_name_id *list) {
	size_t argc;

	if (!list)
		return 0;

	for (argc = 0; list[argc] != 0; ++ argc)
		;

	return argc;

}

void
Scriptix::sx_free_namelist (sx_name_id *list) {
	if (list != NULL) {
		free (list);
	}
}
