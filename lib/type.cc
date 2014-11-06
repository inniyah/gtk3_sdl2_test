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

Type::Type (System* system, const TypeDef* base)
{
	name = NameToID(base->name);

	if (base->parent) {
		NameID pname = NameToID(base->parent->name);
		parent = system->GetType(pname);
	} else {
		parent = NULL;
	}

	for (size_t i = 0; base->methods[i].name != NULL; ++i) {
		Method* method = new Method();
		method->name = NameToID(base->methods[i].name);
		method->argc = base->methods[i].argc;
		method->varg = base->methods[i].varg;
		method->method = base->methods[i].method;
		method->sxmethod = NULL;
		methods[method->name] = method;
	}
	for (size_t i = 0; base->smethods[i].name != NULL; ++i) {
		Method* method = new Method();
		method->name = NameToID(base->smethods[i].name);
		method->argc = base->smethods[i].argc;
		method->varg = base->smethods[i].varg;
		method->method = base->smethods[i].method;
		method->sxmethod = NULL;
		smethods[method->name] = method;
	}
}

Type*
System::AddType (const TypeDef* typed)
{
	// generate name
	NameID tname = NameToID(typed->name);

	// have we the type already?
	Type* type;
	if ((type = GetType(tname)) != NULL)
		return type;

	// copy type
	type = new Type(this, typed);
	if (type == NULL) {
		return NULL;
	}
		
	// add type
	types[tname] = type;
	
	return type;
}

const Type* 
System::GetType (NameID id) const
{
	// search
	std::map<NameID,Type*>::const_iterator i = types.find(id);
	if (i != types.end())
		return i->second;

	// no have
	return NULL;
}

Type* 
System::GetType (NameID id)
{
	// search
	std::map<NameID,Type*>::iterator i = types.find(id);
	if (i != types.end())
		return i->second;

	// no have
	return NULL;
}

const Method*
Type::GetStaticMethod (NameID id) const
{
	const Type* type = this;
	while (type != NULL) {
		// search
		std::map<NameID,Method*>::const_iterator i = type->smethods.find(id);
		if (i != type->smethods.end())
			return i->second;
		type = type->parent;
	}

	return NULL;
}

const Method*
Type::GetMethod (NameID id) const
{
	const Type* type = this;
	while (type != NULL) {
		// search
		std::map<NameID,Method*>::const_iterator i = type->methods.find(id);
		if (i != type->methods.end())
			return i->second;
		type = type->parent;
	}

	return NULL;
}

int
Type::AddMethod (Method* method)
{
	if (method == NULL)
		return SXE_INVALID;
	
	methods[method->name] = method;
	if (method->sxmethod)
		Value::Mark(method->sxmethod);

	return SXE_OK;
}

void
Type::MarkMethods (void)
{
	for (std::map<NameID,Method*>::iterator i = methods.begin(); i != methods.end(); ++i)
		if (i->second->sxmethod)
			Value::Mark(i->second->sxmethod);
	for (std::map<NameID,Method*>::iterator i = smethods.begin(); i != smethods.end(); ++i)
		if (i->second->sxmethod)
			Value::Mark(i->second->sxmethod);
}

SX_TYPEIMPL(TypeValue, "Type", Value)

SX_BEGINMETHODS(TypeValue)
	SX_DEFMETHOD(MethodName, "name", 0, 0)
SX_ENDMETHODS

SX_NOSMETHODS(TypeValue)
	
Value*
TypeValue::MethodName (Thread* thread, Value* self, size_t argc, Value** argv)
{
	return new String (thread->GetSystem(), IDToName(((TypeValue*)self)->type->GetName()));
}

bool
TypeValue::Equal (System* system, Value* other)
{
	if (Value::TypeOf (system, other) != TypeValue::GetType())
		return false;

	return ((TypeValue*)other)->type == type;
}
