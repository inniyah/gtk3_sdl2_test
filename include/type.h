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

#ifndef SCRIPTIX_TYPE_H
#define SCRIPTIX_TYPE_H

namespace Scriptix {

// type def for callbacks
typedef class Value* (*sx_cfunc)(size_t argc, class Value** argv);
typedef class Value* (*sx_construct)(const class TypeInfo* type);

class MethodDef {
	public:
	const char* name;
	size_t argc;
	bool varg;
	void* method;
};

class TypeDef {
	public:
	const char* name;		///< Name of type.
	const TypeDef* parent;		///< Parent type.
	const MethodDef* methods;	///< Array of methods.
	const sx_construct construct;	///< Create a new class Value of our TypeInfo.
};

class TypeInfo : public GC::Collectable {
	public:
	TypeInfo (const TypeDef* base, const TypeInfo* parent);

	TypeInfo (NameID name, const TypeInfo* parent, sx_construct s_construct);

	NameID GetName (void) const { return name; }
	const TypeInfo* GetParent (void) const { return parent; }
	class Function* GetMethod (NameID id) const;
	int AddMethod (NameID id, class Function* method);
	class Value* Construct () const { return construct(this); }

	private:
	NameID name;			///< Name of type.
	const TypeInfo* parent;		///< Parent type.
	typedef GC::map<NameID, class Function*> MethodList;
	MethodList methods;	///< List of methods.
	sx_construct construct;	///< Make a new value of our TypeInfo.
};

class TypeValue : public Value
{
	// Methods
	public:
	static Value* MethodName (size_t argc, Value** argv);
	static Value* MethodAddMethod (size_t argc, Value** argv);

	// Operators
	protected:
	bool Equal (Value* other);

	public:
	TypeValue (TypeInfo* our_type);

	virtual const TypeInfo* GetType () const;

	inline TypeInfo* GetTypePtr (void) const { return type; } // silly name from conflict

	// Data
	private:
	TypeInfo* type;
};

// Root typedef
extern const TypeDef Value_Type;

// Creating new types
#define SX_TYPECREATE(CPPNAME) \
	Scriptix::_CreateNew<CPPNAME>
#define SX_TYPECREATESCRIPT(CPPNAME) \
	Scriptix::_CreateNewScript<CPPNAME>
#define SX_TYPECREATENONE(CPPNAME) \
	Scriptix::_CreateNewNull
#define SX_TYPEIMPL(CPPNAME, SXNAME, CPPPARENT, CREATE) \
	extern const Scriptix::TypeDef CPPNAME ## _Type; \
	const Scriptix::TypeDef CPPNAME ## _Type = { \
		SXNAME , \
		&CPPPARENT ## _Type, \
		CPPNAME ## _Methods, \
		CREATE \
	}; 
#define SX_NOMETHODS(CPPNAME) namespace { Scriptix::MethodDef CPPNAME ## _Methods[] = { { NULL, 0, 0, NULL } }; }
#define SX_BEGINMETHODS(CPPNAME) namespace { Scriptix::MethodDef CPPNAME ## _Methods[] = {
#define SX_ENDMETHODS { NULL, 0, 0, NULL } }; }
#define SX_DEFMETHOD(CPPNAME, SXNAME, ARGC, VARARG) { SXNAME, ARGC, VARARG, (void*)CPPNAME }, 

} // namespace Scriptix

#endif
