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

#include "scriptix.h"

using namespace Scriptix;

int
System::AddType (const Type* type)
{
	// have we the type already?
	for (std::vector<const Type*>::iterator i = types.begin(); i != types.end(); ++i)
		if (!strcmp (type->name, (*i)->name))
			return SXE_EXISTS;
		
	// add type
	types.push_back(type);
	
	return SXE_OK;
}

const Type* 
System::GetType (sx_name_id id) const
{
	const char* name = IDToName (id);

	// no name?  nope
	if (name == NULL)
		return NULL;

	// search
	for (std::vector<const Type*>::const_iterator i = types.begin(); i != types.end(); ++i)
		if (!strcmp (name, (*i)->name))
			return (*i);

	// no have
	return NULL;
}

const Method*
Type::GetStaticMethod (sx_name_id id) const
{
	const char* name = IDToName(id);
	if (name == NULL)
		return NULL;

	const Type* type = this;
	const Method* method = NULL;
	while (type != NULL) {
		method = type->smethods;
		while (method->name != NULL) {
			if (!strcmp (method->name, name))
				return method;
			++ method;
		}
		type = type->parent;
	}

	return NULL;
}

const Method*
Value::GetMethod (Value* value, sx_name_id id)
{
	const char* name = IDToName(id);
	if (name == NULL)
		return NULL;

	const Type* type = Value::TypeOf(value);
	if (type == NULL)
		return NULL;

	const Method* method = NULL;
	while (type != NULL) {
		method = type->methods;
		while (method->name != NULL) {
			if (!strcmp (method->name, name))
				return method;
			++ method;
		}
		method = type->smethods;
		while (method->name != NULL) {
			if (!strcmp (method->name, name))
				return method;
			++ method;
		}
		type = type->parent;
	}

	return NULL;
}

SX_TYPEIMPL(TypeValue, "Type", Value)

SX_BEGINMETHODS(TypeValue)
	SX_DEFMETHOD(MethodName, "name", 0, 0)
SX_ENDMETHODS

SX_NOSMETHODS(TypeValue)
	
Value*
TypeValue::MethodName (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return String::Create (thread->GetSystem(), ((TypeValue*)self)->type->name);
}

bool
TypeValue::Equal (System* system, Value* other)
{
	if (Value::TypeOf (other) != TypeValue::GetType())
		return false;

	return ((TypeValue*)other)->type == type;
}
