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

#ifndef SCRIPTIX_VIMPL_H
#define SCRIPTIX_VIMPL_H

#include "sysdep.h"

#include <iostream>

namespace Scriptix {

template <typename TTYPE>
inline const TypeInfo* _GetType();

template<> inline const TypeInfo* _GetType<String>() { return GetSystem()->GetStringType(); }
template<> inline const TypeInfo* _GetType<Iterator>() { return GetSystem()->GetIteratorType(); }
template<> inline const TypeInfo* _GetType<Array>() { return GetSystem()->GetArrayType(); }
template<> inline const TypeInfo* _GetType<Function>() { return GetSystem()->GetFunctionType(); }
template<> inline const TypeInfo* _GetType<TypeValue>() { return GetSystem()->GetTypeValueType(); }
template<> inline const TypeInfo* _GetType<Struct>() { return GetSystem()->GetStructType(); }

template <typename TTYPE>
inline
bool
Value::_TypeCheck<TTYPE>::Check(const Value* value)
{
	return Value::IsA(value, _GetType<TTYPE>());
}

template <>
inline
bool
Value::_TypeCheck<Number>::Check(const Value* value)
{
	return ((intptr_t)value) & 0x01;
}

template <typename CTYPE>
inline
Value*
_CreateNewScript (const TypeInfo* type)
{
	return new CTYPE(type);
}

inline
Value*
_CreateNewNull (const TypeInfo* type)
{
	return NULL;
}

template <typename CTYPE>
inline
Value*
_CreateNew(const TypeInfo* type)
{
	return new CTYPE();
}

} // namespace Scriptix

#endif
