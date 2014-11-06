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

#ifndef SCRIPTIX_TYPE_H
#define SCRIPTIX_TYPE_H

namespace Scriptix {

// type def for callbacks
typedef class Value* (*sx_cmethod)(class Thread* thread, class Value* self, size_t argc, class Value** argv);
typedef class Value* (*sx_cfunc)(class Thread* thread, size_t argc, class Value** argv);
typedef class Value* (*sx_construct)(const class System* system, const class Type* type);

/**
 * Method definition.
 * Contains template information on a Scriptix type method.
 */
class MethodDef {
	public:
	const char* name;
	size_t argc;
	bool varg;
	void* method;
};

/**
 * Type definition.
 * Contains template information on a Scriptix type.
 */
class TypeDef {
	public:
	const char* name;		///< Name of type.
	const TypeDef* parent;		///< Parent type.
	const MethodDef* methods;	///< Array of methods.
	const MethodDef* smethods;	///< Array of static methods.
	const sx_construct construct;	///< Create a new class Value of our Type.
};

/**
 * Type information.
 * Contains actual information on a Scriptix type.
 */
class Type : public GC::Collectable {
	private:
	NameID name;			///< Name of type.
	const Type* parent;		///< Parent type.
	typedef GC::map<NameID, class Function*> MethodList;
	MethodList methods;	///< List of methods.
	MethodList smethods;	///< List of static methods.
	sx_construct construct;	///< Make a new value of our Type.

	public:
	/**
	 * Craft a Type from a TypeDef
	 */
	Type (class System* system, const TypeDef* base);

	/**
	 * Craft custom Type
	 */
	Type (class System* system, NameID name, const Type* parent, sx_construct s_construct);

	/**
	 * Return name.
	 * Return the name of the type.
	 * @return The type's name.
	 */
	NameID GetName (void) const { return name; }
	/**
	 * Return parent.
	 * Return the parent type of the type.
	 * @return The parent type, or NULL if there is no parent.
	 */
	const Type* GetParent (void) const { return parent; }
	/**
	 * Locate a method.
	 * Searches the instance's class ancestory for a method.
	 * @param id The ID of the method to be found.
	 * @return The method if it exists, or NULL otherwise.
	 */
	class Function* GetMethod (NameID id) const;
	/**
	 * Lookup a static method.
	 * Finds a static method with the given name.  Traverses ancestory.
	 * @param id ID of the method to find.
	 * @return A Method if exists, or NULL if not found.
	 */
	class Function* GetStaticMethod (NameID id) const;
	/**
	 * Register a new method.
	 * Add a method to the method list.
	 * @param method to add.
	 * @return SXE_OK on success, or error code on failure.
	 */
	int AddMethod (class Function* method);
	/**
	 * Register a new static method.
	 * Add a static method to the static method list.
	 * @param method to add.
	 * @return SXE_OK on success, or error code on failure.
	 */
	int AddStaticMethod (class Function* method);
	/**
	 * Create a new value of our Type.
	 * Creates a new value, of our Type.
	 * @param system System the value will exist in.
	 * @return A value of our Type on success, NULL on failure.
	 */
	inline class Value* Construct (class System* system) const { return construct(system, this); }
};

// Creating new types
#define SX_TYPEDEF \
	protected: \
	static Scriptix::TypeDef _MyType; \
	static Scriptix::MethodDef _MyMethods[]; \
	static Scriptix::MethodDef _MyStaticMethods[]; \
	public: \
	static const Scriptix::TypeDef* GetTypeDef (void) { return &_MyType; }
#define SX_TYPECREATE(CPPNAME) \
	Scriptix::_CreateNew<CPPNAME>
#define SX_TYPECREATEFINAL(CPPNAME) \
	Scriptix::_CreateNewFinal<CPPNAME>
#define SX_TYPECREATENONE(CPPNAME) \
	Scriptix::_CreateNewNull
#define SX_TYPEIMPL(CPPNAME, SXNAME, CPPPARENT, CREATE) \
	Scriptix::TypeDef CPPNAME::_MyType = { \
		SXNAME , \
		CPPPARENT::GetTypeDef(), \
		CPPNAME::_MyMethods, \
		CPPNAME::_MyStaticMethods, \
		CREATE \
	}; 
#define SX_NOMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyMethods[] = { { NULL, 0, 0, NULL } };
#define SX_NOSMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyStaticMethods[] = { { NULL, 0, 0, NULL } };
#define SX_BEGINMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyMethods[] = {
#define SX_ENDMETHODS { NULL, 0, 0, NULL } };
#define SX_BEGINSMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyStaticMethods[] = {
#define SX_ENDSMETHODS { NULL, 0, 0, NULL } };
#define SX_DEFMETHOD(CPPNAME, SXNAME, ARGC, VARARG) { SXNAME, ARGC, VARARG, (void*)CPPNAME }, 

} // namespace Scriptix

#endif
