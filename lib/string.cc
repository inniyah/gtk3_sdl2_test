/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003, 2004, 2005  AwesomePlay Productions, Inc.
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

SX_BEGINMETHODS(String)
	SX_DEFMETHOD(String::MethodLength, "length", 0, 0)
	SX_DEFMETHOD(String::MethodToInt, "toInt", 0, 0)
	SX_DEFMETHOD(String::MethodUpper, "upper", 0, 0)
	SX_DEFMETHOD(String::MethodLower, "lower", 0, 0)
	SX_DEFMETHOD(String::MethodSubstr, "substr", 2, 0)
	SX_DEFMETHOD(String::MethodSplit, "split", 1, 0)
	SX_DEFMETHOD(String::MethodTrim, "trim", 0, 0)
	SX_DEFMETHOD(String::MethodLtrim, "ltrim", 0, 0)
	SX_DEFMETHOD(String::MethodRtrim, "rtrim", 0, 0)
SX_ENDMETHODS

namespace Scriptix {
	SX_TYPEIMPL(String, "String", Value, SX_TYPECREATENONE(String))
}

String::String (const char* src, size_t size) : Value(), data(src, size) {}
String::String (const char* src) : Value(), data(src) {}
String::String (const BaseString& src) : Value(), data(src) {}

const TypeInfo*
String::GetType () const {
	return GetSystem()->GetStringType();
}

void
String::Print () const
{
	std::cout << data;
}

bool
String::Equal (const Value* other) const
{
	if (!Value::IsA<String>(other))
		return false;

	return data == ((String*)other)->data;
}

int
String::Compare (const Value* other) const
{
	if (!Value::IsA<String>(other))
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
String::True () const
{
	return !data.empty();
}

bool
String::Has (const Value* value) const
{
	const char *c;

	if (!Value::IsA<String>(value))
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
String::GetIndex (Value* vindex) const
{
	long index;

	if (!Value::IsA<Number>(vindex))
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
	
	return new String (GetCStr() + index, 1);
}

Value*
String::MethodLength (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	return Number::Create (self->GetLen());
}

Value*
String::MethodToInt(size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	return Number::Create (atoi (self->GetCStr()));
}

Value*
String::MethodSplit (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	const char *c, *needle, *haystack;
	size_t nlen;

	if (!Value::IsA<String>(argv[1])) {
		GetSystem()->RaiseError(SXE_BADARGS, "Argument 1 to String::split() is not a string");
		return NULL;
	}

	haystack = self->GetCStr();
	needle = ((String*)argv[1])->GetCStr();
	nlen = strlen (needle);

	Array* array = new Array();
	if (array == NULL) {
		return NULL;
	}

	// no needle
	if (nlen == 0) {
		Array::Append (array, self);
		return array;
	}

	// find substr
	for (c = haystack; *c != '\0'; ++ c) {
		if (!strncasecmp (c, needle, strlen (needle))) {
			Array::Append (array, new String (haystack, c - haystack));
			haystack = c + nlen;
		}
	}

	// append last
	if (*haystack != '\0') {
		Array::Append (array, new String (haystack, strlen(haystack)));
	}

	return array;
}

Value*
String::MethodSubstr (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	int start, len;

	start = Number::ToInt(argv[1]);
	len = Number::ToInt(argv[2]);

	// valid starting location?
	if (start < 0 || (size_t)start >= self->GetLen()) {
		// FIXME: perhaps an error?
		return NULL;
	}

	// trim len
	if ((size_t)(start + len) > self->GetLen()) {
		len = self->GetLen() - start;
	}

	// return value
	return new String (self->GetCStr() + start, len);
}

Value*
String::MethodLower (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	String* ret = new String (self->GetStr());
	if (ret)
		for (size_t i = 0; i < ((String*)ret)->GetLen(); ++ i)
			((String*)ret)->data[i] = tolower (((String*)ret)->data[i]);
	return ret;
}

Value*
String::MethodUpper (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	String* ret = new String (self->GetStr());
	if (ret)
		for (size_t i = 0; i < ((String*)ret)->GetLen(); ++ i)
			((String*)ret)->data[i] = toupper (((String*)ret)->data[i]);
	return ret;
}

Value*
String::MethodTrim (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	size_t left = self->GetStr().find_first_not_of(" \t\n");
	if (left == BaseString::npos)
		return new String("");
	size_t right = self->GetStr().find_last_not_of(" \t\n");
	if (right == BaseString::npos)
		return new String("");
	return new String(self->GetStr().substr(left, right - left + 1));
}

Value*
String::MethodLtrim (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	size_t left = self->GetStr().find_first_not_of(" \t\n");
	if (left == BaseString::npos)
		return new String("");
	return new String(self->GetStr().substr(left, BaseString::npos));
}

Value*
String::MethodRtrim (size_t argc, Value** argv)
{
	String* self = (String*)argv[0];
	size_t right = self->GetStr().find_last_not_of(" \t\n");
	if (right == BaseString::npos)
		return new String("");
	return new String(self->GetStr().substr(0, right + 1));
}
