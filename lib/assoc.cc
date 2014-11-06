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

#include "scriptix.h"
#include "system.h"

using namespace Scriptix;

Value*
Assoc::MethodLength (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return Number::Create(((Assoc*)self)->count);
}

Value*
Assoc::MethodGet (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return ((Assoc*)self)->GetIndex (thread->GetSystem(), argv[0]);
}

Value*
Assoc::MethodSet (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return ((Assoc*)self)->SetIndex (thread->GetSystem(), argv[0], argv[1]);
}

Value*
Assoc::MethodAppend (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return ((Assoc*)self)->Append (thread->GetSystem(), argv[0]);
}

Value*
Assoc::MethodRemove (Thread* thread, Value* self, size_t argc, Value** argv)
{
	for (size_t i = 0; i < ((Assoc*)self)->count; ++ i) {
		if (Value::Equal (thread->GetSystem(), argv[0], ((Assoc*)self)->list[i].name)) {
			memmove (&((Assoc*)self)->list[i], &((Assoc*)self)->list[i + 1], (((Assoc*)self)->count - i - 1) * sizeof (_scriptix_assoc_node));
			-- ((Assoc*)self)->count;
			return Number::Create(1);
		}
	}

	return NULL;
}

Value*
Assoc::MethodIter (Thread* thread, Value* self, size_t argc, Value** argv)
{
	// FIXME
	return NULL;
}

// Define type parameters
SX_TYPEIMPL(Assoc, "Assoc", List, SX_TYPECREATEFINAL(Assoc))

// Our methods
SX_BEGINMETHODS(Assoc)
	SX_DEFMETHOD(MethodLength, "length", 0, 0)
	SX_DEFMETHOD(MethodGet, "get", 1, 0)
	SX_DEFMETHOD(MethodSet, "set", 2, 0)
	SX_DEFMETHOD(MethodAppend, "append", 1, 0)
	SX_DEFMETHOD(MethodRemove, "remove", 1, 0)
	SX_DEFMETHOD(MethodIter, "iter", 0, 0)
SX_ENDMETHODS
SX_NOSMETHODS(Assoc)

Assoc::Assoc (System* system) : List(system, system->GetAssocType())
{
	list = NULL;
	size = 0;
	count = 0;
}

Assoc::Assoc (System* system, size_t n_size, Value** n_list) : List(system, system->GetAssocType())
{
	list = NULL;
	size = n_size;
	count = 0;

	if (size > 0) {
		list = (_scriptix_assoc_node*)GC_MALLOC(size * sizeof (_scriptix_assoc_node));
		for (size_t i = 0; i < size * 2; i += 2) {
			SetIndex(system, n_list[i], n_list[i + 1]);
		}
		count = size;
	}
};

void
Assoc::Print (System* system)
{
	size_t i;
	if (count > 0) {
		std::cout << "[";
		if (list[0].name) {
			std::cout << list[0].name->GetStr() << ":";
		}
		Value::Print (system, list[0].value);
		for (i = 1; i < count; i ++) {
			std::cout << ",";
			if (list[i].name)
				std::cout << list[0].name->GetStr() << ":";
			Value::Print (system, list[i].value);
		}
		std::cout << "]";
	} else {
		std::cout << "[]";
	}
}

bool
Assoc::True (System* system) {
	return count > 0;
}

Value* 
Assoc::GetIndex (System* system, Value* vindex) {
	if (Value::IsA<Number>(system, vindex)) {
		long index = Number::ToInt(vindex);

		if (count == 0) {
			return NULL;
		}
		if (index < 0) {
			index += count;
			if (index < 0) {
				index = 0;
			}
		}
		if ((size_t)index >= count) {
			index = count - 1;
		}
	
		return list[index].value;
	} else if (Value::IsA<String>(system, vindex)) {
		size_t i = 0;
		while (i < count) {
			if (Value::Equal (system, vindex, list[i].name)) {
				return list[i].value;
			}
			++i;
		}
	}

	return NULL;
}

Value* 
Assoc::SetIndex (System* system, Value* vindex, Value* value) {
	if (Value::IsA<Number>(system, vindex)) {
		long index = Number::ToInt(vindex);

		if (count == 0) {
			return NULL;
		}
		if (index < 0) {
			index += count;
			if (index < 0) {
				index = 0;
			}
		}
		if ((size_t)index >= count) {
			index = count - 1;
		}
		
		return list[index].value = value;
	} else if (Value::IsA<String>(system, vindex)) {
		size_t i = 0;
		while (i < count) {
			if (Value::Equal (system, vindex, list[i].name)) {
				return list[i].value = value;
			}
			++i;
		}

		if (count == size) {
			_scriptix_assoc_node* nlist = (_scriptix_assoc_node*)GC_REALLOC (list, (count + system->GetArrayChunk()) * sizeof (_scriptix_assoc_node));
			if (nlist == NULL) {
				return NULL;
			}
			list = nlist;
			size += system->GetArrayChunk();
		}

		list[count].name = (String*)vindex;
		list[count].value = value;
		++ count;

		return value;
	}

	return NULL;
}

Value* 
Assoc::Append (System* system, Value* add) {
	if (count == size) {
		_scriptix_assoc_node* nlist = (_scriptix_assoc_node*)GC_REALLOC (list, (count + system->GetArrayChunk()) * sizeof (_scriptix_assoc_node));
		if (nlist == NULL) {
			return NULL;
		}
		list = nlist;
		size += system->GetArrayChunk();
	}

	list[count].name = NULL;
	list[count].value = add;
	++ count;

	return add;
}

bool
Assoc::Has (System* system, Value* value) {
	size_t i;
	for (i = 0; i < count; ++ i) {
		if (Value::Equal (system, list[i].value, value)) {
			return true;
		}
	}
	return false;
}
