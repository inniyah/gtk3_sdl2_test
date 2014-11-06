/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003, 2004  AwesomePlay Productions, Inc.
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

#ifndef SCRIPTIX_VIMPL_H
#define SCRIPTIX_VIMPL_H

#include "scriptix/sysdep.h"

#include <iostream>

namespace Scriptix {

template <typename TTYPE>
inline const Type* _GetType(const System* system);

template<> inline const Type* _GetType<String>(const System* system) { return system->GetStringType(); }
template<> inline const Type* _GetType<List>(const System* system) { return system->GetListType(); }
template<> inline const Type* _GetType<Iterator>(const System* system) { return system->GetIteratorType(); }
template<> inline const Type* _GetType<Array>(const System* system) { return system->GetArrayType(); }
template<> inline const Type* _GetType<Assoc>(const System* system) { return system->GetAssocType(); }
template<> inline const Type* _GetType<Function>(const System* system) { return system->GetFunctionType(); }
template<> inline const Type* _GetType<TypeValue>(const System* system) { return system->GetTypeValueType(); }
template<> inline const Type* _GetType<Struct>(const System* system) { return system->GetStructType(); }

template <typename TTYPE>
inline
bool
Value::_TypeCheck<TTYPE>::Check(const System* system, const Value* value)
{
	return Value::IsA(system, value, _GetType<TTYPE>(system));
}

template <>
inline
bool
Value::_TypeCheck<Number>::Check(const System* system, const Value* value)
{
	return ((intptr_t)value) & 0x01;
}

const Type*
Value::TypeOf (const System* system, const Value* value)
{
	if (value == NULL)
		return NULL;

	if ((intptr_t)value & 0x01)
		return system->GetNumberType();

	return value->GetType();
}

inline
bool
Value::IsA (const System* system, const Value* value, const Type* type)
{
	const Type* my_type = Value::TypeOf (system, value);

	while (my_type != NULL) {
		if (my_type == type)
			return true;
		my_type = my_type->GetParent();
	}

	return false;
}

inline
void
Value::Print (System* system, const Value* self)
{
	if (self != NULL && !IsA<Number>(system, self))
		self->Print(system);
	else if (IsA<Number>(system, self))
		std::cout << Number::ToInt(self);
	else
		std::cout << "(nil)";
}

inline
bool
Value::Equal (const System* system, const Value* self, const Value* other)
{
	if (self == other)
		return true;

	if (self != NULL && !IsA<Number>(system, self))
		return self->Equal(system, other);
	else
		return false;
}

inline
int
Value::Compare (const System* system, const Value* self, const Value* other)
{
	if (self == other)
		return 0;

	// handle nil values somewhat gracefully
	if (self == NULL)
		return -1; // non-nil bigger than nil
	else if (other == NULL)
		return 1; // non-nil bigger than nil

	// do compare
	if (self != NULL && !IsA<Number>(system, self))
		return self->Compare(system, other);
	else if (IsA<Number>(system, self)) {
		if (Number::ToInt(self) < Number::ToInt(other))
			return -1;
		else
			return 1;
	} else
		return 1; // default
}

inline
bool
Value::True (const System* system, const Value* self)
{
	if (self == NULL)
		return false;
	else if (IsA<Number>(system, self))
		return Number::ToInt(self);
	else
		return self->True(system);
}

template <typename CTYPE>
inline
Value*
_CreateNew (const System* system, const Type* type)
{
	return new CTYPE(system, type);
}

inline
Value*
_CreateNewNull (const System* system, const Type* type)
{
	return NULL;
}

template <typename CTYPE>
inline
Value*
_CreateNewFinal (const System* system, const Type* type)
{
	return new CTYPE(system);
}

} // namespace Scriptix

#endif
