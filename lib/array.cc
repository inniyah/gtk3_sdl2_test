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

#include <string.h>

#include "scriptix.h"
#include "system.h"

#include <iostream>

using namespace std;
using namespace Scriptix;

Value*
Array::MethodLength (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return Number::Create(((Array*)self)->count);
}

Value*
Array::MethodAppend (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return ((Array*)self)->Append (thread->GetSystem(), argv[0]);
}

Value*
Array::MethodRemove (Thread* thread, Value* self, size_t argc, Value** argv)
{
	for (size_t i = 0; i < ((Array*)self)->count; ++ i) {
		if (Value::Equal (thread->GetSystem(), argv[0], ((Array*)self)->list[i])) {
			memmove (&((Array*)self)->list[i], &((Array*)self)->list[i + 1], (((Array*)self)->count - i - 1) * sizeof (Value* ));
			-- ((Array*)self)->count;
			return Number::Create(1);
		}
	}

	return NULL;
}

Value*
Array::MethodIter (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return ((Array*)self)->GetIter(thread->GetSystem());
}

// Define type parameters
SX_TYPEIMPL(Array, "Array", List, SX_TYPECREATEFINAL(Array))

// Our methods
SX_BEGINMETHODS(Array)
	SX_DEFMETHOD(MethodLength, "length", 0, 0)
	SX_DEFMETHOD(MethodAppend, "append", 1, 0)
	SX_DEFMETHOD(MethodRemove, "remove", 1, 0)
	SX_DEFMETHOD(MethodIter, "iter", 0, 0)
SX_ENDMETHODS
SX_NOSMETHODS(Array)

Array::Array (System* system) : List(system, system->GetArrayType()), size(0), count(0), list(NULL) { }

Array::Array (System* system, size_t n_size, Value** n_list) : List(system, system->GetArrayType())
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

void
Array::Print (System* system)
{
	cout << "[";
	size_t i;
	if (count > 0)
		Value::Print(system, list[0]);
	for (i = 1; i < count; ++i) {
		cout << ",";
		Value::Print(system, list[i]);
	}
	cout << "]";
}

bool
Array::True (System* system)
{
	return count > 0;
}

Value*
Array::GetIndex (System* system, Value* vindex)
{
	long index;

	// no data items?
	if (count == 0)
		return NULL;

	// must be numeric index
	if (!Value::IsA<Number>(system, vindex))
		return NULL;
	index = Number::ToInt(vindex);

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
Array::SetIndex (System* system, Value* vindex, Value* value)
{
	long index;

	// no data items?
	if (count == 0)
		return NULL;

	// must be numeric index
	if (!Value::IsA<Number>(system, vindex))
		return NULL;
	index = Number::ToInt(vindex);

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
Array::Append (System* system, Value* value)
{
	Value** nlist;

	if (count == size) {
		nlist = (Value* *)GC_REALLOC (list, (size + system->GetArrayChunk()) * sizeof (Value* ));
		if (nlist == NULL) {
			return NULL;
		}
		list = nlist;
		size += system->GetArrayChunk();
	}

	list[count ++] = value;

	return value;
}

bool
Array::Has (System* system, Value* value)
{
	size_t i;
	for (i = 0; i < count; ++ i)
		if (Value::Equal(system, value, list[i]))
			return true;
	return false;
}

Iterator*
Array::GetIter (System* system)
{
	return new ArrayIterator(system, this);
}

bool
Array::ArrayIterator::Next(System* system, Value*& value)
{
	if (index >= array->GetCount()) {
		return false;
	} else {
		value = array->GetIndex(index++);
		return true;
	}
}
