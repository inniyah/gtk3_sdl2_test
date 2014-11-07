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

#include "scriptix.h"
#include "system.h"

#include <iostream>
#include <string.h>

using namespace Scriptix;

// Root typedef
namespace { const MethodDef Value_Methods[] = { { NULL, 0, 0, } }; }
const TypeDef Scriptix::Value_Type = { "Value", NULL, Value_Methods, NULL };

// STATIC FUNCTIONS

const TypeInfo*
Value::TypeOf (const Value* value)
{
	if (value == NULL)
		return NULL;

	if ((intptr_t)value & 0x01)
		return GetSystem()->GetNumberType();

	return value->GetType();
}

bool
Value::IsA (const Value* value, const TypeInfo* type)
{
	const TypeInfo* my_type = Value::TypeOf (value);

	while (my_type != NULL) {
		if (my_type == type)
			return true;
		my_type = my_type->GetParent();
	}

	return false;
}

void
Value::Print (const Value* self)
{
	if (self != NULL && !IsA<Number>(self))
		self->Print();
	else if (IsA<Number>(self))
		std::cout << Number::ToInt(self);
	else
		std::cout << "(nil)";
}

bool
Value::Equal (const Value* self, const Value* other)
{
	if (self == other)
		return true;

	if (self != NULL && !IsA<Number>(self))
		return self->Equal(other);
	else
		return false;
}

int
Value::Compare (const Value* self, const Value* other)
{
	if (self == other)
		return 0;

	// handle nil values somewhat gracefully
	if (self == NULL)
		return -1; // non-nil bigger than nil
	else if (other == NULL)
		return 1; // non-nil bigger than nil

	// do compare
	if (self != NULL && !IsA<Number>(self))
		return self->Compare(other);
	else if (IsA<Number>(self)) {
		if (Number::ToInt(self) < Number::ToInt(other))
			return -1;
		else
			return 1;
	} else
		return 1; // default
}

bool
Value::True (const Value* self)
{
	if (self == NULL)
		return false;
	else if (IsA<Number>(self))
		return Number::ToInt(self);
	else
		return self->True();
}


// DEFAULT IMPLEMENTATIONS
void
Value::Print () const
{
	std::cout << this;
}

bool
Value::Equal (const Value* other) const
{
	return this == other;
}

int
Value::Compare (const Value* other) const
{
	return !(this == other);
}

bool
Value::True () const
{
	return true;
}

// COMPLEX WRAPPERS
Value*
Value::ToString(Value* value)
{
	if (Value::IsA(value, GetSystem()->GetStringType()))
		return value;

	Value* ret;
	static NameID to_string_id = NameToID("toString");
	if (GetSystem()->Invoke(value, to_string_id, 0, NULL, &ret))
		return NULL;

	if (Value::IsA(ret, GetSystem()->GetStringType()))
		return ret;

	return NULL;
}

Value*
Value::ToInt(Value* value)
{
	if (Number::IsNumber(value))
		return value;

	Value* ret;
	static NameID to_int_id = NameToID("toInt");
	if (GetSystem()->Invoke(value, to_int_id, 0, NULL, &ret))
		return NULL;

	if (Number::IsNumber(ret))
		return ret;

	return NULL;
}
