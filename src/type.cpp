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

using namespace Scriptix;

TypeInfo::TypeInfo (const TypeDef* base, const TypeInfo* s_parent) : parent(s_parent)
{
	name = NameToID(base->name);

	if (base->construct == NULL && parent)
		construct = parent->construct;
	else
		construct = base->construct;

	for (size_t i = 0; base->methods[i].name != NULL; ++i) {
		Function* method = new Function(
			NameToID(base->methods[i].name),
			base->methods[i].argc + 1,
			base->methods[i].varg,
			(sx_cfunc)base->methods[i].method);
		methods[method->id] = method;
	}
}

TypeInfo::TypeInfo (NameID s_name, const TypeInfo* s_parent, sx_construct s_construct)
{
	name = s_name;
	parent = s_parent;

	if (s_construct == NULL && parent)
		construct = parent->construct;
	else
		construct = s_construct;
}

TypeInfo*
System::AddType (const TypeDef* typed)
{
	// generate name
	NameID tname = NameToID(typed->name);

	// have we the type already?
	TypeInfo* type;
	if ((type = GetType(tname)) != NULL)
		return type;

	// get parent
	TypeInfo* parent = NULL;
	if (typed->parent)
		parent= GetType(NameToID(typed->parent->name));

	// copy type
	type = new TypeInfo(typed, parent);
	if (type == NULL) {
		return NULL;
	}
		
	// add type
	types[tname] = type;
	
	return type;
}

const TypeInfo* 
System::GetType (NameID id) const
{
	// search
	TypeList::const_iterator i = types.find(id);
	if (i != types.end())
		return i->second;

	// no have
	return NULL;
}

TypeInfo* 
System::GetType (NameID id)
{
	// search
	TypeList::iterator i = types.find(id);
	if (i != types.end())
		return i->second;

	// no have
	return NULL;
}

Function*
TypeInfo::GetMethod (NameID id) const
{
	const TypeInfo* type = this;
	while (type != NULL) {
		// search
		MethodList::const_iterator i = type->methods.find(id);
		if (i != type->methods.end())
			return i->second;
		type = type->parent;
	}

	return NULL;
}

int
TypeInfo::AddMethod (NameID id, Function* method)
{
	if (method == NULL)
		return SXE_INVALID;
	
	methods[id] = method;

	return SXE_OK;
}

TypeValue::TypeValue(TypeInfo* s_type) : Value(), type(s_type) {}

const TypeInfo*
TypeValue::GetType () const
{
	return GetSystem()->GetTypeValueType();
}

SX_BEGINMETHODS(TypeValue)
	SX_DEFMETHOD(TypeValue::MethodName, "name", 0, 0)
	SX_DEFMETHOD(TypeValue::MethodAddMethod, "addMethod", 2, 0)
SX_ENDMETHODS

namespace Scriptix {
	SX_TYPEIMPL(TypeValue, "TypeInfo", Value, SX_TYPECREATENONE(TypeValue))
}
	
Value*
TypeValue::MethodName (size_t argc, Value** argv)
{
	TypeValue* self = (TypeValue*)argv[0];
	return new String (IDToName(self->type->GetName()));
}

Value*
TypeValue::MethodAddMethod (size_t argc, Value** argv)
{
	TypeValue* self = (TypeValue*)argv[0];
	TypeInfo* type = self->GetTypePtr();

	if (!Value::IsA<String>(argv[1])) {
		GetSystem()->RaiseError(SXE_BADARGS, "Argument 1 to Type::add_method() is not a string");
		return NULL;
	}
	if (!Value::IsA<Function>(argv[2])) {
		GetSystem()->RaiseError(SXE_BADARGS, "Argument 2 to Type::add_method() is not a function");
		return NULL;
	}

	NameID id = NameToID(((String*)argv[1])->GetCStr());

	Function* func = type->GetMethod(id);
	if (func != NULL) {
		GetSystem()->RaiseError(SXE_EXISTS, "Method named %s already exists on type %s", IDToName(id), IDToName(type->GetName()));
	}

	type->AddMethod(id, (Function*)argv[2]);

	return argv[2];
}

bool
TypeValue::Equal (Value* other)
{
	if (Value::TypeOf (other) != TypeValue::GetType())
		return false;

	return ((TypeValue*)other)->type == type;
}
