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

/**
 * Scriptix script engine.
 * C++ based high-performance scripting engine for games.
 * @author AwesomePlay Produtions, Inc.
 * @pkgdoc Scriptix http://www.awemud.net/scriptix/
 */

#ifndef __SCRIPTIX_H__
#define __SCRIPTIX_H__

#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <inttypes.h>

#include "gc/gc_cpp.h"
#include "gc/new_gc_alloc.h"

/**
 * Scriptix namespace.
 * All Scriptix methods, types, classes, and functions exist
 * in this namespace.
 */
namespace Scriptix {

// various stack sizes
const int DEF_DATA_CHUNK = 50;
const int DEF_CONTEXT_CHUNK = 10;
const int DEF_BLOCK_CHUNK = 10;
const int DEF_ARRAY_CHUNK = 5;

// base options
const int DEF_RUN_LENGTH = 1000;

// max length of an identifier
const int MAX_NAME = 128;

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

// Error Codes
typedef enum {
	SXE_OK = 0,	// no error
	SXE_NOMEM,	// out of memory
	SXE_BADTYPE,	// invalid type for operation
	SXE_UNDEFINED,	// undefined/nonexistant
	SXE_NILCALL,	// method call on nil value
	SXE_BADOP,	// invalid operator - internal error
	SXE_BOUNDS,	// value out of bounds
	SXE_NOTREADY,	// not ready to handle request
	SXE_INVALID,	// generic invalid request
	SXE_DISABLED, 	// operation disabled
	SXE_BUSY,	// busy, cannot complete request
	SXE_INTERNAL,	// internal, unknown error
	SXE_BADARGS,	// bad set or arguments; count or type
	SXE_EXISTS,	// already exists (duplicate)
	SXE_DIVZERO,	// divide by zero
} sx_err_type;

// Byte-code ops
typedef enum {
	OP_PUSH = 0,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_NEGATE,
	OP_INVOKE,
	OP_GT,
	OP_LT,
	OP_GTE,
	OP_LTE = 10,
	OP_EQUAL,
	OP_NEQUAL,
	OP_NOT,
	OP_LOOKUP,
	OP_ASSIGN,
	OP_INDEX,
	OP_NEWARRAY,
	OP_TYPECAST,
	OP_STRINGCAST,
	OP_INTCAST = 20,
	OP_SETINDEX,
	OP_METHOD,
	OP_SETFILE,
	OP_SETLINE,
	OP_NEXTLINE,
	OP_JUMP,
	OP_POP,
	OP_TEST,
	OP_TJUMP,
	OP_FJUMP = 30,
	OP_STATIC_METHOD,
	OP_YIELD,
	OP_IN,
	OP_SET_MEMBER,
	OP_GET_MEMBER,
	OP_ITER,
	OP_NEW,
	OP_COPY = 38,
} sx_op_type;

// Thread flags
typedef enum {
	TFLAG_PREEMPT = (1 << 0), // pre-emptable threading
} sx_thread_flags;

// Call-stack flags
typedef enum {
	CFLAG_TTRUE = (1 << 0),
	CFLAG_BREAK = (1 << 1),
} sx_call_flags;

// Thread states
typedef enum {
	STATE_READY = 0,	// ready to run
	STATE_RUNNING,		// currentl running
	STATE_FINISHED,		// execution complete
	STATE_FAILED,		// runtime error
	STATE_RETURN,		// in return
} sx_state_type;

// System options
typedef enum {
	OPT_NONE = 0,
	OPT_DATACHUNK,
	OPT_BLOCKCHUNK,
	OPT_CONTEXTCHUNK,
	OPT_RUNLENGTH,
	OPT_ARRAYCHUNK,
	OPT_PATH,
} sx_option_type;

// Define opcodes
class OpCode {
	public:
	const char* name;
	unsigned char args;
};

extern OpCode OpCodeDefs[];

// Security level type
typedef uint16_t SecurityLevel;

// Basic secutity types
const SecurityLevel SEC_FILEIO = (1);		// allowed to do file i/o
const SecurityLevel SEC_NETWORKIO = (1 << 1);// allowed to do network i/o
const SecurityLevel SEC_FORK = (1 << 2);		// allowed to use fork()

// Reserved security types
const SecurityLevel SEC_RESERVED1 = (1 << 3);// first user sec type
const SecurityLevel SEC_RESERVED2 = (1 << 4);// first user sec type
const SecurityLevel SEC_RESERVED3 = (1 << 5);// first user sec type
const SecurityLevel SEC_RESERVED4 = (1 << 6);// first user sec type
const SecurityLevel SEC_RESERVED5 = (1 << 7);// first user sec type

// User available security types
const SecurityLevel SEC_USER1 = (1 << 8); 	// first user sec type
const SecurityLevel SEC_USER2 = (1 << 9); 	// second user sec type
const SecurityLevel SEC_USER3 = (1 << 10); 	// third user sec type
const SecurityLevel SEC_USER4 = (1 << 11); 	// fourth user sec type
const SecurityLevel SEC_USER5 = (1 << 12); 	// fifth user sec type
const SecurityLevel SEC_USER6 = (1 << 13); 	// sixth user sec type
const SecurityLevel SEC_USER7 = (1 << 14); 	// seventh user sec type
const SecurityLevel SEC_USER8 = (1 << 15); 	// eight user sec type

const SecurityLevel SEC_DEFAULTS = (SEC_FILEIO|SEC_NETWORKIO|SEC_FORK);

// how to mark a number
const intptr_t NUM_MARK = 0x01;

// core structures
class Value;
class Global;
//class Method;
class MethodDef;
class Call;
class System;
class Thread;
class Type;
class TypeDef;

// core types
class Number;
class String;
class Array;
class Assoc;
class Function;
class Iterator;
class TypeValue;

// Nil
class Value* const Nil = NULL;

// id types
typedef size_t NameID;
typedef size_t ThreadID;

typedef void (*sx_gc_hook)(System* system);
typedef void (*sx_error_hook)(const char *file, unsigned int line, const char *str);

typedef Value* (*sx_cmethod)(Thread* thread, Value* self, size_t argc, Value** argv);
typedef Value* (*sx_cfunc)(Thread* thread, size_t argc, Value** argv);
typedef Value* (*sx_construct)(System* system, const Type* type);

// errors
const char *StrError (sx_err_type err);

// version
const char *Version (void);

// easy convert
#define SX_TOVALUE(val) ((Scriptix::Value*)(val))
#define SX_TOFUNC(val) ((Scriptix::Function*)(val))
#define SX_TOSTRING(val) ((Scriptix::String*)(val))
#define SX_TOARRAY(val) ((Scriptix::Array*)(val))
#define SX_TOASSOC(val) ((Scriptix::Assoc*)(val))
#define SX_TONUM(val) ((intptr_t)val)
#define SX_TOTYPE(val) ((Scriptix::TypeValue*)(val))
#define SX_TOITER(val) ((Scriptix::Iterator*)(val))

/* Provide a base class for GC objects.  Very similar to the GC's normal
 * Collectable class, except it uses the no_order variant of the finalizer
 * registration; this allows us to have destructors even when we've cyclic
 * links of objects.  Destructors should never use pointers to GC'd data,
 * only free non-GC'd resources, like strings and file handles.
 */

class Collectable : virtual public ::gc
{
	public:
	inline Collectable (void);
	inline virtual ~Collectable (void);
	private:
	inline static void cleanup(void* obj, void* data);
};

Collectable::Collectable(void)
{
	GC_finalization_proc old_proc;
	void* old_data;
	void* base = GC_base((void*)this);

	if (base != NULL) {
		GC_register_finalizer_no_order(base, (GC_finalization_proc)cleanup,
			(void*)((char*)this - (char*)base), &old_proc, &old_data);
		if (old_proc != NULL) {
			GC_register_finalizer_no_order(base, old_proc, old_data, 0, 0);
		}
	}
}

Collectable::~Collectable(void)
{
	GC_register_finalizer_no_order(GC_base(this), 0, 0, 0, 0);
}

void
Collectable::cleanup(void* obj, void* displace)
{
	((Collectable*)((char*)obj + (ptrdiff_t)displace))->~Collectable();
}

// Name<->ID translation
NameID NameToID(const char *name);
const char *IDToName(NameID id);

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
	const sx_construct construct;	///< Create a new Value of our Type.
};

/**
 * Type information.
 * Contains actual information on a Scriptix type.
 */
class Type : public Collectable {
	private:
	NameID name;			///< Name of type.
	const Type* parent;		///< Parent type.
	typedef std::map<NameID,Function*,std::less<NameID>, gc_alloc > MethodList;
	MethodList methods;	///< List of methods.
	MethodList smethods;	///< List of static methods.
	sx_construct construct;	///< Make a new value of our Type.

	public:
	/**
	 * Craft a Type from a TypeDef
	 */
	Type (System* system, const TypeDef* base);

	/**
	 * Craft custom Type
	 */
	Type (System* system, NameID name, const Type* parent, sx_construct s_construct);

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
	Function* GetMethod (NameID id) const;
	/**
	 * Lookup a static method.
	 * Finds a static method with the given name.  Traverses ancestory.
	 * @param id ID of the method to find.
	 * @return A Method if exists, or NULL if not found.
	 */
	Function* GetStaticMethod (NameID id) const;
	/**
	 * Register a new method.
	 * Add a method to the method list.
	 * @param method to add.
	 * @return SXE_OK on success, or error code on failure.
	 */
	int AddMethod (Function* method);
	/**
	 * Register a new static method.
	 * Add a static method to the static method list.
	 * @param method to add.
	 * @return SXE_OK on success, or error code on failure.
	 */
	int AddStaticMethod (Function* method);
	/**
	 * Create a new value of our Type.
	 * Creates a new value, of our Type.
	 * @param system System the value will exist in.
	 * @return A value of our Type on success, NULL on failure.
	 */
	inline Value* Construct (System* system) const { return construct(system, this); }
};

/**
 * Base type for all values.
 * Every data type in Scriptix must derive from the Value class.  This
 * class also contains static methods for the manipulation of Value-
 * based instances.
 *
 * Numeric data is stored inside a Value pointer.  For this reason,
 * you should never treat a Value pointer as an actual pointer, but
 * instead as an opaque data type.  Always use the static wrappers
 * for Value methods versus calling the methods directly, unless you
 * are positive you have a valid pointer.
 */
class Value : public Collectable {
	// our type
	private:
	const Type* type; //< The value's type.
	
	// Stubs for data type
	protected:
	static MethodDef _MyMethods[];
	static MethodDef _MyStaticMethods[];

	public:
	/**
	 * Fetch the type definition for the class.
	 * @return The type definition
	 */
	static const TypeDef* GetTypeDef (void) { return NULL; }
	/**
	 * Fetch the type information for the value's class.
	 * @return The type information
	 */
	inline const Type* GetType (void) const { return type; }

	// Constructor/destructor
	public:
	/**
	 * Construct a new Value.
	 * This is the base constructor, which must be invoked by children
	 * constructuors.
	 * @param system A pointer to a System the Value is created in.
	 */
	Value (System* system, const Type* s_type) : gc(), type(s_type) {}
	/**
	 * Destroy a Value.
	 * This is the destructor, which should be over-ridden by children
	 * classes that allocate non-managed data or resources.
	 */
	virtual ~Value (void) {}

	// Operations
	protected:
	/**
	 * Print out a Value.
	 * Over-ride this to provide custom behaviour for printing an instance.
	 * @param system System that the instance exists in.
	 */
	virtual void Print (System* system);
	/**
	 * Check equality.
	 * Test whether two instances are equal to each other.  The more
	 * in-depth and accurate, the better.  For example, comparing a
	 * string with a number would be a good idea to implement here.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @see Compare
	 * @see True
	 * @param system System that the instance exists in.
	 * @param other The instance to compare against.
	 * @return Return true if equal, false otherwise.
	 */
	virtual bool Equal (System* system, Value* other);
	/**
	 * Compare relationship.
	 * Compare the relationship between two instance; which one
	 * is ordered before the other.  Using in less-than comparisons
	 * and friends.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @see Equal
	 * @see True
	 * @param system System that the instance exists in.
	 * @param other The instance to compare against.
	 * @return -1 when the current instance comes before the other
	 *   instance, 0 when the instances are equal (or no comparison can
	 *   be made), and 1 when the other instance comes before the
	 *   current instance.
	 */
	virtual int Compare (System* system, Value* other);
	/**
	 * Test truth.
	 * Test if the instance is a "true" instance or not.  Used in if and
	 * other boolean test.  For example, on an array type, return true
	 * if the array has more than 0 items, or false otherwise.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @see Equal
	 * @see Compare
	 * @param system System that the instance exists in.
	 */
	virtual bool True (System* system);
	/**
	 * Cast to a string.
	 * Attempt to convert the value to a string.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, a string must always
	 * be returned; an empty string is allowed.
	 * @param system System that the instance exists in.
	 * @return A string if conversion is possible, or NULL otherwise.
	 */
	virtual Value* ToString (System* system) { return NULL; }
	/**
	 * Cast to an int.
	 * Attempt to convert the value to an int.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, an int must always
	 * be returned; zero is allowed.
	 * @param system System that the instance exists in.
	 * @return An int if conversion is possible, or NULL otherwise.
	 */
	virtual Value* ToInt (System* system) { return NULL; }

	// Operate on values
	public:
	/**
	 * Print an instance.
	 * Calls the Print method for the given instance.
	 * @param system System that the instances exists in.
	 * @param self The instance to be printed.
	 */
	inline static void Print (System* system, Value* self);
	/**
	 * Check equality.
	 * Compare equality of two instances, using the Equal method of the
	 * self instance.
	 * @param system System that the instance exists in.
	 * @param self First instance to check, used as basis for comparison.
	 * @param other Second instance to check.
	 * @return True if the instances are equal, false otherwise.
	 */
	inline static bool Equal (System* system, Value* self, Value* other);
	/**
	 * Compare relationship.
	 * Compare the ordered relationship between two instances, using the
	 * Compare method of the self instance.
	 * @param system System that the instances exists in.
	 * @param self First instance to check, used as basis for comparison.
	 * @param other Second instance to check.
	 * @return -1 when the self instance comes before the other
	 *   instance, 0 when the instances are equal (or no comparison can
	 *   be made), and 1 when the other instance comes before the
	 *   self instance.
	 */
	inline static int Compare (System* system, Value* self, Value* other);
	/**
	 * Check truth.
	 * Determine if an instance is a true value or not, for boolean checks.
	 * Calls the Truth method on the given instance.
	 * @param system System that the instances exists in.
	 * @param self The instance to check.
	 * @return True if the instance is true, false otherwise.
	 */
	inline static bool True (System* system, Value* self);
	/**
	 * Cast to a string.
	 * Attempt to convert the value to a string.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, a string must always
	 * be returned; an empty string is allowed.
	 * @param system System that the instance exists in.
	 * @param self The instance to convert.
	 * @return A string if conversion is possible, or NULL otherwise.
	 */
	static Value* ToString (System* system, Value* self);
	/**
	 * Cast to an int.
	 * Attempt to convert the value to an int.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, an int must always
	 * be returned; zero is allowed.
	 * @param system System that the instance exists in.
	 * @param self The instance to convert.
	 * @return An int if conversion is possible, or NULL otherwise.
	 */
	inline static Value* ToInt (System* system, Value* self)
		{ return Value::IsA<Number>(system, self) ? self : DoToInt(system, self); }

	// Silly type-casting struct hacks
	private:
	template <typename TTYPE>
	struct _TypeCheck {
		inline static bool Check(System* system, Value* value);
	};

	// In depth int casting
	static Value* DoToInt (System* System, Value* self);

	// Special operations
	public:
	/**
	 * Determine the Type of an instance.
	 * Dynamically determines the type of a Value instance.  Handles both
	 * NULL pointers and the specially encoded numeric values, and return
	 * appropriate values.
	 * @param value The value whose type will be found.
	 * @return The type of the value, or NULL on a NULL value.
	 */
	inline static const Type* TypeOf (System* system, Value* value);
	/**
	 * Determine if an instance is of a given Type.
	 * Dynamically checks the type of an instance, and return true if the
	 * instance is of the given type, or the instance is derived from the 
	 * given type.
	 * @param value The value to type check.
	 * @param type The type used in the comparison.
	 * @return True if the value is of the given type, or derived from the
	 *   type, and false otherwise.
	 */
	inline static bool IsA (System* system, Value* value, const Type* type);
	/**
	 * Determine if an instance is of a given Type.
	 * Dynamically checks the type of an instance, and return true if the
	 * instance is of the given type, or the instance is derived from the 
	 * given type.
	 * @param value The value to type check.
	 * @return True if the value is of the given type, or derived from the
	 *   type, and false otherwise.
	 */
	template<typename TTYPE> inline static bool IsA(System* system, Value* value) { return _TypeCheck<TTYPE>::Check(system, value); }
	/**
	 * Cast an instance to a given type.
	 * Dynamically checks the type of an instance, and return a cast
	 * pointer if the instance is of the given type, or the instance is
	 * derived from the given type.
	 * @param value The value to type check.
	 * @return A cast pointer if the value is of the given type, or
	 *   derived from the type, and NULL otherwise.
	 */
	template<typename TTYPE> inline static TTYPE* Cast(System* system, Value* value) { return _TypeCheck<TTYPE>::Check(system, value) ? (TTYPE*)value : NULL; }

	// System has to access this for the GC
	friend class System;
};

/**
 * Iterator base type.
 * Iterators provide a language-based feature for iterating thru any
 * sort of list or collection.  Iterators can be used with the foreach()
 * language construct, or on their own uses normal method calls.
 */
class Iterator : public Value {
	SX_TYPEDEF // Implemented in iter.cc

	// operations
	public:
	/**
	 * Fetch next item in the collection.
	 * This is the main part of an iterator.  Each call to this method
	 * returns the next item in the collection, until the end of the
	 * collection is reached.
	 * @note Over-ride in your derived iterator to provide functionality.
	 * @param system System the value should be in.
	 * @param value A value if true is returned, undefined otherwise.
	 * @return false if there are no more items, true if there are.
	 */
	virtual bool Next (System* system, Value*& value) = 0;

	// Methods
	private:
	/**
	 * Method: Get next item.
	 * Get next item from collection.  Skips nil items due to implementation
	 *   details.
	 * @return Next item, or nil if there are no more.
	 */
	static Value* MethodNext (Thread* thread, Value* self, size_t argc, Value** argv);

	// Constructor
	public:
	inline Iterator (System* system);
};

/**
 * List base type.
 * This is the base type for list types (such as arrays).  It provides
 * functionality for setting, getting, appending, checking a list.
 */
class List : public Value {
	SX_TYPEDEF // Implemented in value.cc

	// operations
	public:
	/**
	 * Fetch an item at a given index.
	 * Given an index, return the item at that index.  Used to implement
	 * any kind of multi-value property, such as arrays or data members.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param index The index to look at.
	 * @return The value at the given index, or NULL if the index is
	 *   invalid.
	 */
	virtual Value* GetIndex (System* system, Value* index);
	/**
	 * Set an item at a given index.
	 * Set the value of an item at a given index.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param index The index value to use.
	 * @param set The value to set.
	 * @return The value of set if successful, or NULL on failure.
	 */
	virtual Value* SetIndex (System* system, Value* index, Value* set);
	/**
	 * Append an item.
	 * Used mainly in array types, it should append an item to the
	 * instance's internal list.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param value The value to append.
	 * @return The value appended on success, or NULL otherwise.
	 */
	virtual Value* Append (System* system, Value* value);
	/**
	 * Check if a list has a value or key.
	 * Use this to check if a certain value exists in a list, or if a
	 * particular key is set.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param value The value or key to look for.
	 * @return True if the value/key exists, or false otherwise.
	 */
	virtual bool Has (System* system, Value* value);
	/**
	 * Get an iterator.
	 * Create an iterator for the list.
	 * @param system System iterator is in.
	 * @return An iterator, or NULL on error.
	 */
	virtual Iterator* GetIter (System* system);

	public:
	/**
	 * Initialize list.
	 * @param system System that the instance will be created in.
	 * @return The initialized list instance.
	 */
	inline List (System* system, const Type* type) : Value(system, type) {}

	/**
	 * Fetch an item at a given index.
	 * Given an index, return the item at that index.  Used to implement
	 * any kind of multi-value property, such as arrays or data members.
	 * @param system System that the instance exists in.
	 * @param list List to operate on.
	 * @param index The index to look at.
	 * @return The value at the given index, or NULL if the index is
	 *   invalid.
	 */
	inline static Value* GetIndex (System* system, List* list, Value* index)
	{
		return list->GetIndex(system, index);
	}
	/**
	 * Set an item at a given index.
	 * Set the value of an item at a given index.
	 * @param system System that the instance exists in.
	 * @param list List to operate on.
	 * @param index The index value to use.
	 * @param set The value to set.
	 * @return The value of set if successful, or NULL on failure.
	 */
	inline static Value* SetIndex (System* system, List* list, Value* index, Value* set)
	{
		return list->SetIndex(system, index, set);
	}
	/**
	 * Append an item.
	 * Used mainly in array types, it should append an item to the
	 * instance's internal list.
	 * @param system System that the instance exists in.
	 * @param list List to operate on.
	 * @param value The value to append.
	 * @return The value appended on success, or NULL otherwise.
	 */
	inline static Value* Append (System* system, List* list, Value* value)
	{
		return list->Append(system, value);
	}
	/**
	 * Check if a list has a value or key.
	 * Use this to check if a certain value exists in a list, or if a
	 * particular key is set.
	 * @param system System that the instance exists in.
	 * @param list List to operate on.
	 * @param value The value or key to look for.
	 * @return True if the value/key exists, or false otherwise.
	 */
	inline static bool Has (System* system, List* list, Value* value)
	{
		return list->Has(system, value);
	}
	/**
	 * Get an iterator.
	 * Create an iterator for the list.
	 * @param system System iterator is in.
	 * @return An iterator, or NULL on error.
	 */
	inline static Iterator* GetIter (System* system, List* list)
	{
		return list->GetIter(system);
	}
};

/**
 * Struct value.
 * An structure is similar to a C structure.  Structs contain member values,
 * which can be read or modified.  Unlike C, Structs' member lists are
 * dynamic, like an associate array type.
 */
class Struct : public Value {
	SX_TYPEDEF

	// member data
	private:
	typedef std::map<NameID,Value*,std::less<NameID>, gc_alloc > datalist;
	datalist data;

	// Method implementations
	protected:
	/**
	 * Set an unset member.
	 * If an attempt is made to set a member value that does not
	 * exist in the member list, this method is called.
	 * @param system The system the structure exists in.
	 * @param id The ID of the member to be set.
	 * @param value The value to set the member to.
	 */
	virtual void SetUndefMember (System* system, NameID id, Value* value);
	/**
	 * Get an undefined member.
	 * If an attempt is made to lookup the value of an undefined
	 * member, this method is called to return a value.
	 * @param system The system the structure exists in.
	 * @param id The ID of the member to be retrieved.
	 */
	virtual Value* GetUndefMember (System* system, NameID id);

	// Constructor
	public:
	/**
	 * Initialize structure.
	 * @param system System that the structure will be created in.
	 * @return The initialized structure instance.
	 */
	inline Struct (System* system, const Type* type) : Value(system, type), data() {}
	inline Struct (System* system);

	/**
	 * Set member value.
	 * Will set the given member to the given value.
	 * @param System System structure exists in.
	 * @param id The ID of the member to be set.
	 * @param value The value to set the member to.
	 */
	void SetMember (System* system, NameID id, Value* value);

	/**
	 * Get member value.
	 * Get the value of the given member.
	 * @param System System structure exists in.
	 * @param id The ID of the member to be retrieved.
	 * @return The value of the member, or NULL on error.
	 */
	Value* GetMember (System* system, NameID id);
};

/**
 * Numeric value.
 * This is the class of a numeric value.  Note that there will *never* be an
 * instance of this class, as numerics are encoded into pointers.  However, we
 * still need the class for member functions and type specification.
 */
class Number : public Value {
	SX_TYPEDEF

	private:
	// Methods
	/**
	 * Method: Convert to a string.
	 * A method to convert a number to a String.
	 * @param thread Current thread.
	 * @param self Numeric value.
	 * @param argc Argument count, unused.
	 * @param argv Argument list, unused.
	 * @return A String.
	 */
	static Value* MethodTostr (Thread* thread, Value* self, size_t argc, Value** argv);

	public:
	/**
	 * Phony constructor.
	 * We need a constructor for this class to satisfy libsgc.
	 */
	Number (void);

	/**
	 * Phony destructor.
	 * We need a destructor for this class to satisfy libsgc.  Abstract
	 * declaration to guarantee we don't instantiate this class.
	 */
	~Number (void) = 0; // disallow creation of Number

	/**
	 * Create new numeric value.
	 * Given an intptr_t value, create an encoded pointer usable in the rest
	 * of the Scriptix system.
	 * @param i Numeric value.
	 * @return Encoded numeric value.
	 */
	inline static Value* Create (intptr_t i) { return ((Value* )((i << 1) | NUM_MARK)); }
	/**
	 * Decode numeric value.
	 * Given an encoded numeric value, return a normal intptr_t numeric value.
	 * @param num Encoded numeric value.
	 * @return Decoded intptr_t numeric value.
	 */
	inline static intptr_t ToInt (Value* num) { return (intptr_t)num >> 1; }
};

/**
 * String value.
 * Stores a string of text.
 * @note Cannot sub-class.
 */
class String : public Value {
	SX_TYPEDEF

	private:
	std::string data;

	// Methods
	private:
	static Value* MethodLength (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodToint (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodUpper (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodLower (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodSplit (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodSubstr (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodTrim (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodLtrim (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodRtrim (Thread* thread, Value* self, size_t argc, Value** argv);

	static Value* SMethodConcat (Thread* thread, size_t argc, Value** argv);

	public:
	String (System* system, const char* src, size_t len);
	String (System* system, const char* src);
	String (System* system, const std::string& src);

	// Query data
	public:
	/**
	 * Get length of string.
	 * @return Length of the string.
	 */
	inline size_t GetLen (void) const { return data.length(); }
	/**
	 * Get C string.
	 * Returns a pointer type to be used in C/C++ code.
	 * @return A pointer to an array of the ctypeacter type.
	 */
	inline const char* GetCStr (void) const { return data.c_str(); }
	/**
	 * Get C++ string.
	 * Returns a reference of the C++ string member.
	 * @return const reference of data.
	 */
	inline const std::string& GetStr (void) const { return data; }

	// Operations
	protected:
	virtual void Print (System* system);
	virtual bool Equal (System* system, Value* other);
	virtual int Compare (System* system, Value* other);
	virtual bool True (System* system);
	virtual Value* GetIndex (System* system, Value* index);
	virtual bool Has (System* system, Value* value);
};

/**
 * Store a list of values.
 * Your basic array type.
 * @note Cannot sub-class.
 */
class Array : public List {
	SX_TYPEDEF

	// Methods
	protected:
	static Value* MethodLength (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodAppend (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodRemove (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodIter (Thread* thread, Value* self, size_t argc, Value** argv);

	protected:
	size_t size;
	size_t count;
	Value** list;

	public:
	Array (System* system);
	Array (System* system, size_t n_size, Value** n_list);

	// Value Operations
	protected:
	virtual void Print (System* system);
	virtual bool True (System* system);

	// List Operations
	public:
	/**
	 * Fetch an item at a given index.
	 * Given an index, return the item at that index.  Used to implement
	 * any kind of multi-value property, such as arrays or data members.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param index The index to look at.
	 * @return The value at the given index, or NULL if the index is
	 *   invalid.
	 */
	virtual Value* GetIndex (System* system, Value* index);
	/**
	 * Set an item at a given index.
	 * Set the value of an item at a given index.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param index The index value to use.
	 * @param set The value to set.
	 * @return The value of set if successful, or NULL on failure.
	 */
	virtual Value* SetIndex (System* system, Value* index, Value* set);
	/**
	 * Append an item.
	 * Used mainly in array types, it should append an item to the
	 * instance's internal list.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param value The value to append.
	 * @return The value appended on success, or NULL otherwise.
	 */
	virtual Value* Append (System* system, Value* value);
	/**
	 * Check if a list has a value or key.
	 * Use this to check if a certain value exists in a list, or if a
	 * particular key is set.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param value The value or key to look for.
	 * @return True if the value/key exists, or false otherwise.
	 */
	virtual bool Has (System* system, Value* value);
	/**
	 * Get an iterator.
	 * Create an iterator for the list.
	 * @param system System iterator is in.
	 * @return An iterator, or NULL on error.
	 */
	virtual Iterator* GetIter (System* system);

	// Custom
	public:
	inline size_t GetCount (void) const { return count; }
	inline Value* GetIndex (size_t i) const { return list[i]; }
	// NOTE: the following should only be used on ranges 0 thru (count - 1)
	inline Value* SetIndex (size_t i, Value* value) { return list[i] = value; }

	// Iterators
	public:
	class ArrayIterator : public Scriptix::Iterator
	{
		// data
		private:
		Array* array;
		size_t index;

		// Next iterator
		public:
		virtual bool Next (System* system, Value*& value);

		// Constructor
		public:
		inline ArrayIterator (System* system, Array* s_arr) :
			Scriptix::Iterator(system), array(s_arr), index(0) {}
	};
};

/**
 * Associate array.
 * Maps key/value pairs.
 * @note Cannot sub-type.
 */
class Assoc : public List {
	SX_TYPEDEF

	private:
	// assoc array node
	struct _scriptix_assoc_node {
		String* name;
		Value* value;
	};

	protected:
	struct _scriptix_assoc_node* list;
	size_t count;
	size_t size;

	protected:
	// Methods
	static Value* MethodLength (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodGet (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodSet (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodAppend (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodRemove (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodIter (Thread* thread, Value* self, size_t argc, Value** argv);

	public:
	Assoc (System* system);
	Assoc (System* system, size_t n_size, Value** n_list); // evens are strings, odds are values

	// Value Operations
	protected:
	virtual void Print (System* system);
	virtual bool True (System* system);

	// List Operations
	public:
	virtual Value* GetIndex (System* system, Value* index);
	virtual Value* SetIndex (System* system, Value* index, Value* set);
	virtual Value* Append (System* system, Value* value);
	virtual bool Has (System* system, Value* value);

	// Custom
	public:
	inline size_t GetCount (void) const { return count; }
	inline Value* GetIndex (size_t i) const { return list[i].value; }
	inline Value* SetIndex (size_t i, Value* value) { return list[i].value = value; }
};

/**
 * Function.
 * The basis of Scriptix execution.
 * @note Cannot sub-class.
 */
class Function : public Value {
	SX_TYPEDEF

	public:
	Function (System* system);
	Function (System* system, NameID id, size_t argc, bool varg); // argc is minimum arg count
	Function (System* system, NameID id, size_t argc, bool varg, sx_cfunc func); // argc is minimum arg count
	Function (System* system, NameID id, size_t argc, bool varg, sx_cmethod method); // argc is minimum arg count

	NameID id; // name of function
	size_t argc; // number of arguments to function
	size_t varc; // number of variables in function
	intptr_t* nodes; // byte codes
	size_t count; // number of valid bytecode nodes
	size_t size; // size of nodes
	bool varg; // name of variable argument - FIXME: should be a flag or something
	sx_cfunc cfunc; // c function pointer (for cfuncs)
	sx_cmethod cmethod; // c method pointer (for cmethods)

	// Build byte-codes
	public:
	int AddValue (System* system, Value* value);
	inline int AddOpcode (System* system, sx_op_type code) { return AddOparg(system,code); } // same thing
	int AddOparg (System* system, long arg);
};

/**
 * Type wrapper.
 * Carry around a Scriptix type as a Scriptix value.
 * @note Cannot sub-class.
 */
class TypeValue : public Value
{
	SX_TYPEDEF

	// Data
	private:
	const Type* type;

	// Methods
	private:
	static Value* MethodName (Thread* thread, Value* self, size_t argc, Value** argv);

	// Operators
	protected:
	bool Equal (System* system, Value* other);

	public:
	inline TypeValue (System* system, const Type* our_type);

	inline const Type* GetTypePtr (void) const { return type; } // silly name from conflict
};

// OTHER CONSTRUCTS
class MethodDef {
	public:
	const char* name;
	size_t argc;
	bool varg;
	void* method;
};

class System : public Collectable {
	private:
	// global data
	typedef std::map<NameID,Value*,std::less<NameID>, gc_alloc > GlobalList;
	GlobalList globals;

	// public functions
	typedef std::map<NameID,Function*,std::less<NameID>, gc_alloc > FunctionList;
	FunctionList funcs;

	// tags feature
	typedef std::vector<NameID> TagList;
	TagList tags;

	// types
	typedef std::map<NameID,Type*,std::less<NameID>, gc_alloc > TypeList;
	TypeList types;

	// threads/scheduler
	Thread* threads;
	Thread* cur_thread;

	// options
	size_t data_chunk;
	size_t context_chunk;
	size_t block_chunk;
	size_t gc_thresh;
	size_t array_chunk;
	std::string script_path;

	// options
	size_t valid_threads;
	size_t run_length;

	// built-in types
	const Type* t_number;
	const Type* t_string;
	const Type* t_array;
	const Type* t_assoc;
	const Type* t_function;
	const Type* t_type;
	const Type* t_list;
	const Type* t_struct;
	const Type* t_iterator;

	// helper functions
	int InitStdlib (void);

	// manager threads
	void AddThread (Thread* thread);
	void EndThread (Thread* thread);

	public:
	// Constructor/Destructor
	System (void);
	virtual ~System (void) {}

	// Hooks
	sx_error_hook error_hook;

	// Add/check types
	Type* AddType (const TypeDef* type);
	const Type* GetType (NameID id) const;
	Type* GetType (NameID id);

	inline const Type* GetNumberType (void) const { return t_number; }
	inline const Type* GetStringType (void) const { return t_string; }
	inline const Type* GetStructType (void) const { return t_struct; }
	inline const Type* GetListType (void) const { return t_list; }
	inline const Type* GetIteratorType (void) const { return t_iterator; }
	inline const Type* GetArrayType (void) const { return t_array; }
	inline const Type* GetAssocType (void) const { return t_assoc; }
	inline const Type* GetFunctionType (void) const { return t_function; }
	inline const Type* GetTypeValueType (void) const { return t_type; }

	// Query information
	inline size_t GetValidThreads (void) const { return valid_threads; }
	inline size_t GetRunLength (void) const { return run_length; }
	inline size_t GetDataChunk (void) const { return data_chunk; }
	inline size_t GetContextChunk (void) const { return context_chunk; }
	inline size_t GetBlockChunk (void) const { return block_chunk; }
	inline size_t GetArrayChunk (void) const { return array_chunk; }

	// Set options
	int SetOption (sx_option_type op, long value);
	int SetOption (sx_option_type op, const std::string& value);

	// Functions
	int AddFunction (Function* function);
	Function* GetFunction (NameID id);

	// Globals
	int AddGlobal (NameID id, Value* value);
	Value* GetGlobal (NameID id) const;

	// Threads
	Thread* CreateThread (Function* func, size_t argc, Value* array[], SecurityLevel sl = SEC_DEFAULTS, int flags = 0);

	// Running threads
	int Run (void);
	int WaitOn (ThreadID id, Value** retval);
	int NestedRun (Thread* thread, Value** retval);

	// Function tags
	int AddFunctionTag (NameID tag);
	bool ValidFunctionTag (NameID tag);
	virtual void HandleFunctionTag (NameID tag, Function* func) {} // over-ride to handle

	// Load/compile scripts
	int LoadFile (const std::string& filepath);
	int LoadString (const std::string& buffer, const std::string& name, size_t lineno = 1);

	// FIXME: hacks
	friend Value::Value (System* system, const Type* type);
};

class Frame {
	private:
	Function* func;
	String* file;
	Value** items;
	size_t op_ptr;
	size_t top;
	size_t line;
	size_t argc;
	int flags;

	public:
	Frame(void) : func(NULL), file(NULL), items(NULL), op_ptr(0), top(0), line(1), argc(0), flags(0) {}

	// Thread works on us extensively
	friend class Thread;
};

/**
 * Thread.
 * A thread contains a current execution context.
 */
class Thread : public gc {
	public:
	// Contructor/destructor
	Thread (System* system, SecurityLevel sl, int flags);

	// Misc
	inline ThreadID GetID(void) const { return id; }

	// Get system
	inline System* GetSystem(void) const { return system; }

	// Raise an error condition
	int RaiseError (int err, const char *format, ...);
	int RaiseArgError (const char* func, const char* arg, const char* type);
	int RaiseSecurityError (const char* func);

	// exit thread
	int Exit (Value* retval);

	// Fetch stack item from end (args) - INLINE for speed
	inline Value* GetValue (size_t index) { return data_stack[data_stack.size() - index]; }
	// Same as GetValue(1):
	inline Value* GetValue (void) { return data_stack.back(); }

	// Fetch item from frame stack for op atrgs; "eats" arg
	inline intptr_t GetOpArg (void) { return GetFrame().func->nodes[GetFrame().op_ptr++]; }

	// Security level
	inline SecurityLevel get_security (void) const { return sec_flags; }
	inline bool has_access (SecurityLevel sl) const { return sec_flags & sl; }

	// Invoke a frameable
	Value* Invoke (Function* func, size_t argc, Value* array[]);

	private:
	// various stuffs
	System* system;
	Value* ret;
	ThreadID id;
	int state;
	SecurityLevel sec_flags;
	unsigned char flags;

	// function frame stack
	typedef std::vector<Frame, gc_alloc > FrameStack;
	FrameStack frames;

	// data stack
	typedef std::vector<Value*, gc_alloc > DataStack;
	DataStack data_stack;

	// list pointers
	Thread* prev;
	Thread* next;

	// Evaluate the thread - run it
	int Eval (void);
	int Run (void);

	// Evaluation helpers
	inline Value* InvokeCFunc (Function* cfunc, size_t argc);

	// Manipulate data stack - INLINE for speed
	inline int
	PushValue (Value* value) {
		data_stack.push_back(value);
		return SXE_OK;
	}
	inline void PopValue (size_t len) { data_stack.resize(data_stack.size() - len); }
	// Same as PopValue(1):
	inline void PopValue (void) { data_stack.pop_back(); }

	// Manipulate data stack
	int PushFrame (Function* func, size_t argc, Value* argv[], int flags);
	int PushFrame (Value* object, NameID method, size_t argc, Value* argv[], int flags);
	void PopFrame (void);
	inline int PushFrame (Function* func, size_t argc) { return PushFrame (func, argc, &data_stack[data_stack.size() - argc], 0); }
	inline Frame& GetFrame (void) { return frames.back(); }


	// System can control me
	friend class System;
};

// Utility functions

template <typename T1> inline int
CheckArgs (Thread* thread, Value** argv, const char* fname, const char* name1) {
	if (!Value::IsA<T1>(thread->GetSystem(), argv[0])) {
		thread->RaiseArgError(fname, name1, T1::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	return SXE_OK;
}
template <typename T1, typename T2> inline int
CheckArgs (Thread* thread, Value** argv, const char* fname, const char* name1, const char* name2) {
	if (!Value::IsA<T1>(thread->GetSystem(), argv[0])) {
		thread->RaiseArgError(fname, name1, T1::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	if (!Value::IsA<T2>(thread->GetSystem(), argv[1])) {
		thread->RaiseArgError(fname, name2, T2::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	return SXE_OK;
}
template <typename T1, typename T2, typename T3> inline int
CheckArgs (Thread* thread, Value** argv, const char* fname, const char* name1, const char* name2, const char* name3) {
	if (!Value::IsA<T1>(thread->GetSystem(), argv[0])) {
		thread->RaiseArgError(fname, name1, T1::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	if (!Value::IsA<T2>(thread->GetSystem(), argv[1])) {
		thread->RaiseArgError(fname, name2, T2::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	if (!Value::IsA<T3>(thread->GetSystem(), argv[2])) {
		thread->RaiseArgError(fname, name3, T3::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	return SXE_OK;
}

// INLINE METHODS
//  These have to be down here, in the header, thanks to stupid C++ and it's inline linking

// --- Type Checking/Casting ---
inline
const Type*
Value::TypeOf (System* system, Value* value)
{
	if (value == NULL)
		return NULL;

	if ((intptr_t)value & 0x01)
		return system->GetNumberType();

	return value->GetType();
}

inline
bool
Value::IsA (System* system, Value* value, const Type* type)
{
	const Type* my_type = Value::TypeOf (system, value);

	while (my_type != NULL) {
		if (my_type == type)
			return true;
		my_type = my_type->GetParent();
	}

	return false;
}

template <typename TTYPE>
inline const Type* _GetType(System* system);

template<> inline const Type* _GetType<Number>(System* system) { return system->GetNumberType(); }
template<> inline const Type* _GetType<String>(System* system) { return system->GetStringType(); }
template<> inline const Type* _GetType<List>(System* system) { return system->GetListType(); }
template<> inline const Type* _GetType<Iterator>(System* system) { return system->GetIteratorType(); }
template<> inline const Type* _GetType<Array>(System* system) { return system->GetArrayType(); }
template<> inline const Type* _GetType<Assoc>(System* system) { return system->GetAssocType(); }
template<> inline const Type* _GetType<Function>(System* system) { return system->GetFunctionType(); }
template<> inline const Type* _GetType<TypeValue>(System* system) { return system->GetTypeValueType(); }
template<> inline const Type* _GetType<Struct>(System* system) { return system->GetStructType(); }

template <typename TTYPE>
inline
bool
Value::_TypeCheck<TTYPE>::Check(System* system, Value* value)
{
	return Value::IsA(system, value, _GetType<TTYPE>(system));
}

template <>
inline
bool
Value::_TypeCheck<Number>::Check(System* system, Value* value)
{
	return ((intptr_t)value) & 0x01;
}

// --- Value --- 
inline
void
Value::Print (System* system, Value* self)
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
Value::Equal (System* system, Value* self, Value* other)
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
Value::Compare (System* system, Value* self, Value* other)
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
Value::True (System* system, Value* self)
{
	if (self == NULL)
		return false;
	else if (IsA<Number>(system, self))
		return Number::ToInt(self);
	else
		return self->True(system);
}

// ---- Various constructors ----
inline Iterator::Iterator(System* system) : Value(system, system->GetIteratorType()) {}
inline Struct::Struct(System* system) : Value(system, system->GetStructType()) {}
inline TypeValue::TypeValue(System* system, const Type* s_type) : Value(system, system->GetTypeValueType()), type(s_type) {}

// ---- Magic NEW operator constructor ----
template <typename CTYPE>
inline
Value*
_CreateNew (System* system, const Type* type)
{
	return new CTYPE(system, type);
}
inline
Value*
_CreateNewNull (System* system, const Type* type)
{
	return NULL;
}
template <typename CTYPE>
inline
Value*
_CreateNewFinal (System* system, const Type* type)
{
	return new CTYPE(system);
}

}

#endif
