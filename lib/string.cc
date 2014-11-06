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

#include <iostream>
#include <ctype.h>

#include "scriptix.h"
#include "system.h"

using namespace Scriptix;

SX_TYPEIMPL(String, "String", Value)

SX_BEGINMETHODS(String)
	SX_DEFMETHOD(MethodLength, "length", 0, 0)
	SX_DEFMETHOD(MethodTonum, "to_num", 0, 0)
	SX_DEFMETHOD(MethodUpper, "upper", 0, 0)
	SX_DEFMETHOD(MethodLower, "lower", 0, 0)
	SX_DEFMETHOD(MethodSubstr, "substr", 2, 0)
	SX_DEFMETHOD(MethodSplit, "split", 1, 0)
SX_ENDMETHODS

SX_BEGINSMETHODS(String)
	SX_DEFMETHOD(SMethodConcat, "concat", 2, 0)
SX_ENDMETHODS

String::String (System* system, const ctype* src, size_t size) : Value(system)
{
	len = size;
	if (src) {
		memcpy (str, src, len);
		str[len] = '\0';
	} else
		str[0] = '\0';
}

void
String::Print (System* system)
{
	if (len)
		std::cout << str;
}

bool
String::Equal (System* system, Value* other) {
	if (!Value::IsA<String>(other))
		return false;

	if (len != ((String*)other)->len) {
		return false;
	}
	if (len == 0) {
		return true;
	}
	return !strcmp (str, ((String*)other)->str);
}

int
String::Compare (System* system, Value* other) {
	if (!Value::IsA<String>(other))
		return -1;

	if (len < ((String*)other)->len) {
		return -1;
	} else if (len > ((String*)other)->len) {
		return 1;
	} else if (len == 0) {
		return 0;
	}
	return memcmp (str, ((String*)other)->str, len*sizeof(ctype));
}

bool
String::True (System* system) {
	return len > 0;
}

bool
String::Has (System* system, Value* value) {
	const ctype *c;

	if (!Value::IsA<String>(value))
		return false;

	// blank test - always in
	if (!((String*)value)->len)
		return true;
	// longer - can't be in
	if (((String*)value)->len > len)
		return false;

	// scan and check
	for (c = str; *c != '\0'; ++ c) {
		if (!strncasecmp (c, ((String*)value)->str, ((String*)value)->len))
			return true;
	}

	return false;
}

Value* 
String::GetIndex (System* system, Value* vindex) {
	long index;

	if (!Value::IsA<Number>(vindex))
		return NULL;
	
	index = Number::ToInt(vindex);

	if (len == 0) {
		return NULL;
	}
	if (index < 0) {
		index += len;
		if (index < 0) {
			index = 0;
		}
	}
	if ((size_t)index >= len) {
		index = len - 1;
	}
	
	return String::Create (system, str + index, 1);
}

Value*
String::MethodLength (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return Number::Create (((String*)self)->len);
}

Value*
String::MethodTonum (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return Number::Create (atoi (((String*)self)->str));
}

// methods
Value*
String::SMethodConcat (Thread* thread, Value* self, size_t argc, Value** argv)
{
	size_t len = 0;
	String* ret;

	// calc length
	for (size_t i = 0; i < argc; ++ i) {
		if (Value::IsA<String>(argv[i])) {
			len += ((String*)argv[i])->len;
		}
	}

	// allocate string
	ret = String::Alloc(thread->GetSystem(), len);
	if (ret == NULL) {
		thread->RaiseError(SXE_NOMEM, "Out of memory");
		return NULL;
	}

	// copy into
	len = 0; // pointer to index
	for (size_t i = 0; i < argc; ++ i) {
		if (Value::IsA<String>(argv[i])) {
			memcpy (ret->str + len, ((String*)argv[i])->str, ((String*)argv[i])->len * sizeof (ctype));
			len += ((String*)argv[i])->len;
		}
	}

	// finish
	ret->str[((String*)ret)->len] = '\0';
	return ret;
}

Value*
String::MethodSplit (Thread* thread, Value* self, size_t argc, Value** argv)
{
	const ctype *c, *needle, *haystack;
	size_t nlen;

	if (!Value::IsA<String>(argv[0])) {
		thread->RaiseError(SXE_BADARGS, "Argument 1 to String::split() is not a string");
		return NULL;
	}

	haystack = ((String*)self)->str;
	needle = ((String*)argv[0])->str;
	nlen = strlen (needle);

	Array* array = new Array(thread->GetSystem());
	if (array == NULL) {
		return NULL;
	}

	// no needle
	if (nlen == 0) {
		List::Append (thread->GetSystem(), array, self);
		return array;
	}

	// find substr
	for (c = haystack; *c != '\0'; ++ c) {
		if (!strncasecmp (c, needle, strlen (needle))) {
			List::Append (thread->GetSystem(), array, String::Create (thread->GetSystem(), haystack, c - haystack));
			haystack = c + nlen;
		}
	}

	// append last
	if (*haystack != '\0') {
		List::Append (thread->GetSystem(), array, String::Create (thread->GetSystem(), haystack, strlen(haystack)));
	}

	return array;
}

Value*
String::MethodSubstr (Thread* thread, Value* self, size_t argc, Value** argv)
{
	int start, len;

	start = Number::ToInt(argv[0]);
	len = Number::ToInt(argv[1]);

	// valid starting location?
	if (start < 0 || (size_t)start >= ((String*)self)->len) {
		// FIXME: perhaps an error?
		return NULL;
	}

	// trim len
	if ((size_t)(start + len) > ((String*)self)->len) {
		len = ((String*)self)->len - start;
	}

	// return value
	return String::Create (thread->GetSystem(), ((String*)self)->str + start, len);
}

Value*
String::MethodLower (Thread* thread, Value* self, size_t argc, Value** argv)
{
	String* ret = String::Create(thread->GetSystem(), ((String*)self)->GetStr());
	if (ret)
		for (size_t i = 0; i < ((String*)ret)->GetLen(); ++ i)
			((String*)ret)->str[i] = tolower (((String*)ret)->str[i]);
	return ret;
}

Value*
String::MethodUpper (Thread* thread, Value* self, size_t argc, Value** argv)
{
	String* ret = String::Create(thread->GetSystem(), ((String*)self)->GetStr());
	if (ret)
		for (size_t i = 0; i < ((String*)ret)->GetLen(); ++ i)
			((String*)ret)->str[i] = toupper (((String*)ret)->str[i]);
	return ret;
}
