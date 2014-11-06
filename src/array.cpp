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

#include <string.h>

#include "scriptix.h"
#include "system.h"

#include <iostream>

using namespace std;
using namespace Scriptix;

Value*
Array::MethodLength (size_t argc, Value** argv)
{
	Array* self = (Array*)argv[0];
	return Number::Create(self->count);
}

Value*
Array::MethodAppend (size_t argc, Value** argv)
{
	Array* self = (Array*)argv[0];
	return self->Append (argv[1]);
}

Value*
Array::MethodRemove (size_t argc, Value** argv)
{
	Array* self = (Array*)argv[0];
	for (size_t i = 0; i < self->count; ++ i) {
		if (Value::Equal (argv[1], self->list[i])) {
			memmove (&self->list[i], &self->list[i + 1], (self->count - i - 1) * sizeof (Value* ));
			-- self->count;
			return Number::Create(1);
		}
	}

	return NULL;
}

Value*
Array::MethodIter (size_t argc, Value** argv)
{
	Array* self = (Array*)argv[0];
	return self->GetIter();
}

// Our methods
SX_BEGINMETHODS(Array)
	SX_DEFMETHOD(Array::MethodLength, "length", 0, 0)
	SX_DEFMETHOD(Array::MethodAppend, "append", 1, 0)
	SX_DEFMETHOD(Array::MethodRemove, "remove", 1, 0)
	SX_DEFMETHOD(Array::MethodIter, "iter", 0, 0)
SX_ENDMETHODS

// Define type parameters
namespace Scriptix {
	SX_TYPEIMPL(Array, "Array", Value, SX_TYPECREATE(Array))
}

Array::Array () : Value(), size(0), count(0), list(NULL) { }

Array::Array (size_t n_size, Value** n_list) : Value()
{
	list = NULL;
	size = n_size;
	count = 0;

	if (n_list != NULL) {
		list = (Value**)GC_MALLOC (size * sizeof(Value*));
		memcpy (list, n_list, size * sizeof (Value*));
		count = n_size;
	} else if (size != 0) {
		list = (Value**)GC_MALLOC (size * sizeof(Value*));
	}
};

const TypeInfo*
Array::GetType () const
{
	return GetSystem()->GetArrayType();
}

void
Array::Print () const
{
	cout << "[";
	size_t i;
	if (count > 0)
		Value::Print(list[0]);
	for (i = 1; i < count; ++i) {
		cout << ",";
		Value::Print(list[i]);
	}
	cout << "]";
}

bool
Array::True () const
{
	return count > 0;
}

Value*
Array::GetIndex (long index) const
{
	// no data items?
	if (count == 0)
		return NULL;

	// wrap negative index
	if (index < 0) {
		index += count;
		if (index < 0) {
			index = 0;
		}
	}

	// top index
	if ((size_t)index >= count)
		index = (long)count - 1;
	
	// return value
	return list[index];
}

Value*
Array::SetIndex (long index, Value* value)
{
	// no data items?
	if (count == 0)
		return NULL;

	// wrap negative index
	if (index < 0) {
		index += count;
		if (index < 0) {
			index = 0;
		}
	}

	// top index
	if ((size_t)index >= count)
		index = (long)count - 1;
	
	// return value
	return list[index] = value;
}

Value*
Array::Append (Value* value)
{
	Value** nlist;

	if (count == size) {
		nlist = (Value* *)GC_REALLOC (list, (size + GetSystem()->GetArrayChunk()) * sizeof (Value* ));
		if (nlist == NULL) {
			return NULL;
		}
		list = nlist;
		size += GetSystem()->GetArrayChunk();
	}

	list[count ++] = value;

	return value;
}

bool
Array::Has (Value* value) const
{
	size_t i;
	for (i = 0; i < count; ++ i)
		if (Value::Equal(value, list[i]))
			return true;
	return false;
}

Iterator*
Array::GetIter ()
{
	return new ArrayIterator(this);
}

bool
Array::ArrayIterator::Next(Value*& value)
{
	if (index >= array->GetCount()) {
		return false;
	} else {
		value = array->GetIndex(index++);
		return true;
	}
}
