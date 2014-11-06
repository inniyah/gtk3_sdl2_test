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

#include "scriptix.h"
#include "config.h"

struct _scriptix_name_id {
	char *name;
	unsigned int id;
	struct _scriptix_name_id *next;
};

struct _scriptix_name_id *_scriptix_name_id_list = NULL;
unsigned int _scriptix_free_name_id = 1;

/* globals */
sx_id sx_parent_id = 0;
sx_id sx_self_id = 0;
sx_id sx_init_id = 0;
sx_id sx_error_id = 0;
sx_id sx_etype_id = 0;
sx_id sx_estack_id = 0;
sx_id sx_ename_id = 0;

unsigned int
sx_name_to_id (const char *name) {
	struct _scriptix_name_id *ni;

	for (ni = _scriptix_name_id_list; ni != NULL; ni = ni->next) {
		if (!strcasecmp (name, ni->name)) {
			return ni->id;
		}
	}

	ni = sx_malloc (NULL, sizeof (struct _scriptix_name_id)); /* FIXME: need system */
	if (ni == NULL) {
		return 0;
	}
	ni->name = strdup (name);
	if (ni->name == NULL) {
		sx_free (ni);
		return 0;
	}
	
	ni->id = _scriptix_free_name_id;
	ni->next = _scriptix_name_id_list;
	_scriptix_name_id_list = ni;

	return _scriptix_free_name_id ++;
}

const char *
sx_id_to_name (unsigned int id) {
	struct _scriptix_name_id *ni;

	if (!id) {
		return NULL;
	}

	for (ni = _scriptix_name_id_list; ni != NULL; ni = ni->next) {
		if (id == ni->id) {
			return ni->name;
		}
	}

	return NULL;
}

void
sx_init_ids (void) {
	/* check if we're initialized already */
	if (sx_parent_id != 0) {
		return;
	}

	sx_parent_id = sx_name_to_id ("parent");
	sx_self_id = sx_name_to_id ("self");
	sx_init_id = sx_name_to_id ("init");
	sx_error_id = sx_name_to_id ("error");
	sx_etype_id = sx_name_to_id ("TypeError");
	sx_estack_id = sx_name_to_id ("StackError");
	sx_ename_id = sx_name_to_id ("NameError");
}
