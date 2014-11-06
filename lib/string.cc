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
	SX_DEFMETHOD(MethodToint, "to_num", 0, 0)
	SX_DEFMETHOD(MethodToint, "to_int", 0, 0)
	SX_DEFMETHOD(MethodUpper, "upper", 0, 0)
	SX_DEFMETHOD(MethodLower, "lower", 0, 0)
	SX_DEFMETHOD(MethodSubstr, "substr", 2, 0)
	SX_DEFMETHOD(MethodSplit, "split", 1, 0)
	SX_DEFMETHOD(MethodTrim, "trim", 0, 0)
	SX_DEFMETHOD(MethodLtrim, "ltrim", 0, 0)
	SX_DEFMETHOD(MethodRtrim, "rtrim", 0, 0)
SX_ENDMETHODS

SX_BEGINSMETHODS(String)
	SX_DEFMETHOD(SMethodConcat, "concat", 2, 0)
SX_ENDMETHODS

String::String (System* system, const char* src, size_t size) : Value(system, system->GetStringType()), data(src, size) {}
String::String (System* system, const char* src) : Value(system, system->GetStringType()), data(src) {}
String::String (System* system, const std::string& src) : Value(system, system->GetStringType()), data(src) {}

void
String::Print (System* system)
{
	std::cout << data;
}

bool
String::Equal (System* system, Value* other) {
	if (!Value::IsA<String>(system, other))
		return false;

	return data == ((String*)other)->data;
}

int
String::Compare (System* system, Value* other) {
	if (!Value::IsA<String>(system, other))
		return -1;

	if (GetLen() < ((String*)other)->GetLen()) {
		return -1;
	} else if (GetLen() > ((String*)other)->GetLen()) {
		return 1;
	} else if (GetLen() == 0) {
		return 0;
	}
	return memcmp (GetCStr(), ((String*)other)->GetCStr(), GetLen()*sizeof(char));
}

bool
String::True (System* system) {
	return !data.empty();
}

bool
String::Has (System* system, Value* value) {
	const char *c;

	if (!Value::IsA<String>(system, value))
		return false;

	// blank test - always in
	if (!((String*)value)->GetLen())
		return true;
	// longer - can't be in
	if (((String*)value)->GetLen() > GetLen())
		return false;

	// scan and check
	for (c = GetCStr(); *c != '\0'; ++ c) {
		if (!strncasecmp (c, ((String*)value)->GetCStr(), ((String*)value)->GetLen()))
			return true;
	}

	return false;
}

Value* 
String::GetIndex (System* system, Value* vindex) {
	long index;

	if (!Value::IsA<Number>(system, vindex))
		return NULL;
	
	index = Number::ToInt(vindex);

	if (data.empty()) {
		return NULL;
	}
	if (index < 0) {
		index += GetLen();
		if (index < 0) {
			index = 0;
		}
	}
	if ((size_t)index >= GetLen()) {
		index = GetLen() - 1;
	}
	
	return new String (system, GetCStr() + index, 1);
}

Value*
String::MethodLength (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return Number::Create (((String*)self)->GetLen());
}

Value*
String::MethodToint (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return Number::Create (atoi (((String*)self)->GetCStr()));
}

// methods
Value*
String::SMethodConcat (Thread* thread, Value* self, size_t argc, Value** argv)
{
	std::string ret;

	// do concat
	for (size_t i = 0; i < argc; ++ i)
		if (Value::IsA<String>(thread->GetSystem(), argv[i]))
			ret += ((String*)argv[i])->data;

	// allocate string
	String* strret = new String (thread->GetSystem(), ret);
	if (strret == NULL) {
		thread->RaiseError(SXE_NOMEM, "Out of memory");
		return NULL;
	}
	return strret;
}

Value*
String::MethodSplit (Thread* thread, Value* self, size_t argc, Value** argv)
{
	const char *c, *needle, *haystack;
	size_t nlen;

	if (!Value::IsA<String>(thread->GetSystem(), argv[0])) {
		thread->RaiseError(SXE_BADARGS, "Argument 1 to String::split() is not a string");
		return NULL;
	}

	haystack = ((String*)self)->GetCStr();
	needle = ((String*)argv[0])->GetCStr();
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
			List::Append (thread->GetSystem(), array, new String (thread->GetSystem(), haystack, c - haystack));
			haystack = c + nlen;
		}
	}

	// append last
	if (*haystack != '\0') {
		List::Append (thread->GetSystem(), array, new String (thread->GetSystem(), haystack, strlen(haystack)));
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
	if (start < 0 || (size_t)start >= ((String*)self)->GetLen()) {
		// FIXME: perhaps an error?
		return NULL;
	}

	// trim len
	if ((size_t)(start + len) > ((String*)self)->GetLen()) {
		len = ((String*)self)->GetLen() - start;
	}

	// return value
	return new String (thread->GetSystem(), ((String*)self)->GetCStr() + start, len);
}

Value*
String::MethodLower (Thread* thread, Value* self, size_t argc, Value** argv)
{
	String* ret = new String (thread->GetSystem(), ((String*)self)->GetStr());
	if (ret)
		for (size_t i = 0; i < ((String*)ret)->GetLen(); ++ i)
			((String*)ret)->data[i] = tolower (((String*)ret)->data[i]);
	return ret;
}

Value*
String::MethodUpper (Thread* thread, Value* self, size_t argc, Value** argv)
{
	String* ret = new String (thread->GetSystem(), ((String*)self)->GetStr());
	if (ret)
		for (size_t i = 0; i < ((String*)ret)->GetLen(); ++ i)
			((String*)ret)->data[i] = toupper (((String*)ret)->data[i]);
	return ret;
}

Value*
String::MethodTrim (Thread* thread, Value* self, size_t argc, Value** argv)
{
	size_t left = ((String*)self)->GetStr().find_first_not_of(" \t\n");
	if (left == std::string::npos)
		return new String(thread->GetSystem(), "");
	size_t right = ((String*)self)->GetStr().find_last_not_of(" \t\n");
	if (right == std::string::npos)
		return new String(thread->GetSystem(), "");
	return new String(thread->GetSystem(), ((String*)self)->GetStr().substr(left, right - left + 1));
}

Value*
String::MethodLtrim (Thread* thread, Value* self, size_t argc, Value** argv)
{
	size_t left = ((String*)self)->GetStr().find_first_not_of(" \t\n");
	if (left == std::string::npos)
		return new String(thread->GetSystem(), "");
	return new String(thread->GetSystem(), ((String*)self)->GetStr().substr(left, std::string::npos));
}

Value*
String::MethodRtrim (Thread* thread, Value* self, size_t argc, Value** argv)
{
	size_t right = ((String*)self)->GetStr().find_last_not_of(" \t\n");
	if (right == std::string::npos)
		return new String(thread->GetSystem(), "");
	return new String(thread->GetSystem(), ((String*)self)->GetStr().substr(0, right + 1));
}
