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

#include "libsgc/libsgc.h"

/**
 * Scriptix namespace.
 * All Scriptix methods, types, classes, and functions exist
 * in this namespace.
 */
namespace Scriptix {

// type to use for numeric data
#if SIZEOF_LONG==SIZEOF_VOIDP
typedef long int_t;
#else // LONG
#if SIZEOF_LONG_LONG==SIZEOF_VOIDP
typedef long long int_t;
#else // LONG LONG
#if SIZEOF_INT==SIZEOF_VOIDP
typedef int int_t;
#else // INT
#error "None of long, long long, or int match the sizeof void*"
#endif // INT
#endif // LONG LONG
#endif // LONG

// various stack sizes
#define SX_DEF_DATA_CHUNK 50
#define SX_DEF_CONTEXT_CHUNK 10
#define SX_DEF_BLOCK_CHUNK 10
#define SX_DEF_ARRAY_CHUNK 5

// base options
#define SX_DEF_RUN_LENGTH 1000

// max length of an identifier
#define SX_MAX_NAME 128

// Creating new types
#define SX_TYPEDEF \
	protected: \
	static Scriptix::TypeDef _MyType; \
	static Scriptix::MethodDef _MyMethods[]; \
	static Scriptix::MethodDef _MyStaticMethods[]; \
	public: \
	static const Scriptix::TypeDef* GetTypeDef (void) { return &_MyType; }
#define SX_TYPEIMPL(CPPNAME, SXNAME, CPPPARENT) \
	Scriptix::TypeDef CPPNAME::_MyType = { \
		SXNAME , \
		CPPPARENT::GetTypeDef(), \
		CPPNAME::_MyMethods, \
		CPPNAME::_MyStaticMethods, \
	}; 
#define SX_NOMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyMethods[] = { { NULL, 0, 0, NULL } };
#define SX_NOSMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyStaticMethods[] = { { NULL, 0, 0, NULL } };
#define SX_BEGINMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyMethods[] = {
#define SX_ENDMETHODS { NULL, 0, 0, NULL } };
#define SX_BEGINSMETHODS(CPPNAME) Scriptix::MethodDef CPPNAME::_MyStaticMethods[] = {
#define SX_ENDSMETHODS { NULL, 0, 0, NULL } };
#define SX_DEFMETHOD(CPPNAME, SXNAME, ARGC, VARARG) { SXNAME, ARGC, VARARG, CPPNAME }, 

// Declare in SMETHODS - default NEW operator
#define SX_DEFNEW(CPPNAME) { "new", 0, 0, _CreateNew<CPPNAME> },

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
	OP_PREINCREMENT,
	OP_POSTINCREMENT,
	OP_NEWARRAY,
	OP_TYPECAST = 20,
	OP_STRINGCAST,
	OP_INTCAST,
	OP_SETINDEX,
	OP_METHOD,
	OP_SETFILELINE,
	OP_NEXTLINE,
	OP_JUMP,
	OP_POP,
	OP_TEST,
	OP_TJUMP = 30,
	OP_FJUMP,
	OP_STATIC_METHOD,
	OP_YIELD,
	OP_IN,
	OP_SET_MEMBER,
	OP_GET_MEMBER,
	OP_ITER,
	OP_CONCAT = 38,
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
	STATE_READY = 0,
	STATE_RUNNING,
	STATE_FINISHED,
	STATE_FAILED,
	STATE_RETURN,
} sx_state_type;

// System options
typedef enum {
	SX_OPT_NONE = 0,
	SX_OPT_DATACHUNK,
	SX_OPT_BLOCKCHUNK,
	SX_OPT_CONTEXTCHUNK,
	SX_OPT_RUNLENGTH,
	SX_OPT_ARRAYCHUNK,
	SX_OPT_PATH,
} sx_option_type;

// Define opcodes
struct OpCode {
	const char* name;
	unsigned char args;
};

extern OpCode OpCodeDefs[];

#define SX_NUM_MARK 0x01

// core structures
class Value;
class Global;
class Method;
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
#define SX_NIL (NULL)

// id types
typedef size_t NameID;
typedef size_t ThreadID;

typedef void (*sx_gc_hook)(System* system);
typedef void (*sx_error_hook)(const char *file, unsigned int line, const char *str);

typedef Value* (*sx_cmethod)(Thread* thread, Value* self, size_t argc, Value** argv);
typedef Value* (*sx_cfunc)(Thread* thread, size_t argc, Value** argv);

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
#define SX_TONUM(val) ((int_t)val)
#define SX_TOTYPE(val) ((Scriptix::TypeValue*)(val))
#define SX_TOITER(val) ((Scriptix::Iterator*)(val))

// Name<->ID translation
NameID NameToID(const char *name);
const char *IDToName(NameID id);

/**
 * Type definition.
 * Contains template information on a Scriptix type.
 */
struct TypeDef {
	const char* name;		///< Name of type.
	const TypeDef* parent;		///< Parent type.
	const MethodDef* methods;	///< Array of methods.
	const MethodDef* smethods;	///< Array of static methods.
};

/**
 * Type information.
 * Contains actual information on a Scriptix type.
 */
class Type {
	private:
	NameID name;			///< Name of type.
	const Type* parent;		///< Parent type.
	std::map<NameID,Method*> methods;	///< List of methods.
	std::map<NameID,Method*> smethods;	///< List of static methods.

	public:
	/**
	 * Craft a Type from a TypeDef
	 */
	Type (System* system, const TypeDef* base);

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
	const Method* GetMethod (NameID id) const;
	/**
	 * Lookup a static method.
	 * Finds a static method with the given name.  Traverses ancestory.
	 * @param id ID of the method to find.
	 * @return A Method if exists, or NULL if not found.
	 */
	const Method* GetStaticMethod (NameID id) const;
	/**
	 * Register a new method.
	 * Add a method to the method list.
	 * @param method to add.
	 * @return SXE_OK on success, or error code on failure.
	 */
	int AddMethod (Method* method);
	/**
	 * Register a new static method.
	 * Add a static method to the static method list.
	 * @param method to add.
	 * @return SXE_OK on success, or error code on failure.
	 */
	int AddStaticMethod (Method* method);
	/**
	 * Mark any methods.
	 * Called by the System for marking the Scriptix methods for the GC.
	 */
	void MarkMethods (void);
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
class Value : public SGC::Collectable {
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
	Value (System* system, const Type* s_type) : type(s_type) {}
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
	 * Mark an instance in the GC.
	 * Call this on an instance when it needs to be marked for the GC.
	 * @param self Value to mark.
	 */
	inline static void Mark (Value* self);
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
	static Value* ToInt (System* system, Value* self);

	// Silly type-casting struct hacks
	private:
	template <typename TTYPE>
	struct _TypeCheck {
		inline static bool Check(System* system, Value* value);
	};

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
	List (System* system, const Type* type) : Value(system, type) {}

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
	static Value* GetIndex (System* system, List* list, Value* index)
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
	static Value* SetIndex (System* system, List* list, Value* index, Value* set)
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
	static Value* Append (System* system, List* list, Value* value)
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
	static bool Has (System* system, List* list, Value* value)
	{
		return list->Has(system, value);
	}
	/**
	 * Get an iterator.
	 * Create an iterator for the list.
	 * @param system System iterator is in.
	 * @return An iterator, or NULL on error.
	 */
	static Iterator* GetIter (System* system, List* list)
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
	typedef std::map<NameID,Value*> datalist;
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

	// Garbage collection
	protected:
	void MarkChildren (void);

	// Constructor
	public:
	/**
	 * Initialize structure.
	 * @param system System that the structure will be created in.
	 * @return The initialized structure instance.
	 */
	Struct (System* system, const Type* type) : Value(system, type), data() {}
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
	 * Given an int_t value, create an encoded pointer usable in the rest
	 * of the Scriptix system.
	 * @param i Numeric value.
	 * @return Encoded numeric value.
	 */
	static Value* Create (int_t i) { return ((Value* )((i << 1) | SX_NUM_MARK)); }
	/**
	 * Decode numeric value.
	 * Given an encoded numeric value, return a normal int_t numeric value.
	 * @param num Encoded numeric value.
	 * @return Decoded int_t numeric value.
	 */
	static int_t ToInt (Value* num) { return (int_t)num >> 1; }
};

/**
 * String value.
 * Stores a string of text.
 * @note Cannot sub-class.
 */
struct String : public Value {
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

	static Value* SMethodConcat (Thread* thread, Value* self, size_t argc, Value** argv);

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
	size_t GetLen (void) const { return data.length(); }
	/**
	 * Get C string.
	 * Returns a pointer type to be used in C/C++ code.
	 * @return A pointer to an array of the ctypeacter type.
	 */
	const char* GetCStr (void) const { return data.c_str(); }
	/**
	 * Get C++ string.
	 * Returns a reference of the C++ string member.
	 * @return const reference of data.
	 */
	const std::string& GetStr (void) const { return data; }

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
	~Array (void);

	// Value Operations
	protected:
	virtual void MarkChildren (void);
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
	size_t GetCount (void) const { return count; }
	Value* GetIndex (size_t i) const { return list[i]; }
	// NOTE: the following should only be used on ranges 0 thru (count - 1)
	Value* SetIndex (size_t i, Value* value) { return list[i] = value; }

	// Iterators
	public:
	class ArrayIterator : public Scriptix::Iterator
	{
		// data
		private:
		Array* array;
		size_t index;

		// mark
		protected:
		virtual void MarkChildren (void);

		// Next iterator
		public:
		virtual bool Next (System* system, Value*& value);

		// Constructor
		public:
		ArrayIterator (System* system, Array* s_arr) :
			Scriptix::Iterator(system), array(s_arr), index(0) {}
	};
};

/**
 * Associate array.
 * Maps key/value pairs.
 * @note Cannot sub-type.
 */
struct Assoc : public List {
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
	~Assoc (void);

	// Value Operations
	protected:
	virtual void MarkChildren (void);
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
	size_t GetCount (void) const { return count; }
	Value* GetIndex (size_t i) const { return list[i].value; }
	Value* SetIndex (size_t i, Value* value) { return list[i].value = value; }
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
	~Function (void);

	NameID id; // name of function
	size_t argc; // number of arguments to function
	size_t varc; // number of variables in function
	int_t* nodes; // byte codes
	size_t count; // number of valid bytecode nodes
	size_t size; // size of nods
	bool varg; // name of variable argument - FIXME: should be a flag or something
	sx_cfunc cfunc; // c function pointer (for cfuncs)
	Function* fnext; // for module list

	// Operations
	protected:
	virtual void MarkChildren (void);

	// Build byte-codes
	public:
	int AddValue (System* system, Value* value);
	int AddOpcode (System* system, sx_op_type code) { return AddOparg(system,code); } // same thing
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

	const Type* GetTypePtr (void) const { return type; } // silly name from conflict
};

// OTHER CONSTRUCTS
struct MethodDef {
	const char* name;
	size_t argc;
	bool varg;
	sx_cmethod method;
};
struct Method {
	NameID name;
	size_t argc;
	bool varg;
	sx_cmethod method;
	Function *sxmethod;
};

struct Global {
	NameID id;
	Value* value;
};

class Call {
	private:
	Function* func;
	String* file;
	Value** items;
	size_t op_ptr;
	size_t top;
	size_t line;
	size_t argc;
	int flags;

	// Thread works on us extensively
	friend class Thread;
};

class System : public SGC::Root {
	// pools - not used inside, useful outside
	struct Pool {
		size_t argc;
		Value** argv;
		Pool* next;
	};

	private:
	// global data
	std::vector<Global> globals;
	Function* funcs;

	// tags feature
	std::vector<NameID> tags;

	// threads/scheduler
	Thread* threads;
	Thread* cur_thread;

	// pools
	Pool* pools;

	// options
	size_t data_chunk;
	size_t context_chunk;
	size_t block_chunk;
	size_t gc_thresh;
	size_t array_chunk;
	char* script_path;

	// options
	size_t valid_threads;
	size_t run_length;

	// types
	std::map<NameID,Type*> types;
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

	// root marker
	protected:
	void Mark (void);

	public:
	// Constructor/Destructor
	System (void);
	~System (void);

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
	size_t GetValidThreads (void) const { return valid_threads; }
	size_t GetRunLength (void) const { return run_length; }
	size_t GetDataChunk (void) const { return data_chunk; }
	size_t GetContextChunk (void) const { return context_chunk; }
	size_t GetBlockChunk (void) const { return block_chunk; }
	size_t GetArrayChunk (void) const { return array_chunk; }

	// Set options
	int SetOption (sx_option_type op, long value);
	int SetOption (sx_option_type op, const char* value);

	// Functions
	int AddFunction (Function* function);
	Function* GetFunction (NameID id);

	// Globals
	int AddGlobal (NameID id, Value* value);
	Value* GetGlobal (NameID id) const;

	// Threads
	void AddThread (Thread* thread);
	void EndThread (Thread* thread);

	// Running threads
	int Run (void);
	int WaitOn (ThreadID id, Value** retval);
	int NestedRun (Thread* thread, Value** retval);

	// Pools
	int PushPool (size_t argc, Value** argv);
	void PopPool (void);

	// Function tags
	int AddFunctionTag (NameID tag);
	bool ValidFunctionTag (NameID tag);
	virtual void HandleFunctionTag (NameID tag, Function* func) {} // over-ride to handle

	// Load/compile scripts
	int LoadFile (const char *file);
	int LoadFile (FILE* file, const char* name);
	int LoadString (const char *buffer);

	// FIXME: hacks
	friend Value::Value (System* system, const Type* type);
};

class Thread {
	private:
	// various stuffs
	System* system;
	Value* ret;
	int state;
	unsigned char flags;
	ThreadID id;

	// function call stack
	Call* call_stack;
	size_t call;
	size_t call_size;

	// data stack
	Value* *data_stack;
	size_t data;
	size_t data_size;

	// list pointers
	Thread* prev;
	Thread* next;

	// Evaluate the thread - run it
	int Eval (void);
	int Run (void);

	// Evaluation helpers
	inline Value* InvokeCFunc (Function* cfunc, size_t argc);
	inline Value* InvokeMethod (Value* self, const Method* method, size_t argc);

	// Manipulate data stack - INLINE for speed
	int
	Thread::PushValue (Value* value) {
		if (data == data_size) {
			Value** sx_new_stack = (Value**)realloc (data_stack, (data_size + system->GetDataChunk()) * sizeof (Value* ));
			if (sx_new_stack == NULL)
				return SXE_NOMEM;
			data_stack = sx_new_stack;
			data_size += system->GetDataChunk();
		}

		data_stack[data ++] = value;

		return SXE_OK;
	}
	void Thread::PopValue (size_t len) { data -= len; }

	// Manipulate data stack
	int PushCall (Function* called, size_t argc, Value* argv[], unsigned char flags);
	int PushCall (Function* called, size_t argc) { return PushCall (called, argc, &data_stack[data - argc], 0); }
	void PopCall (void);
	Call* GetCall (void) { return &call_stack[call - 1]; }

	// GC mark
	void Mark (void);

	public:
	// Contructor/destructor
	Thread (System* system, Function* called, unsigned char flags, size_t argc, Value* argv[]);
	Thread (System* system, Function* called, unsigned char flags, size_t argc, ...);
	~Thread (void);

	// Misc
	ThreadID GetID(void) const { return id; }

	// Get system
	System* GetSystem(void) const { return system; }

	// Raise an error condition
	int RaiseError (int err, const char *format, ...);
	int RaiseArgError (const char* func, const char* arg, const char* type)
	{
		return RaiseError(SXE_BADARGS, "Argument '%s' to '%s' is not a '%s'", arg, func, type);
	}

	// exit thread
	int Exit (Value* retval);

	// Fetch stack item from end (args) - INLINE for speed
	Value* Thread::GetValue (size_t index) { return data_stack[data - index]; }

	// Invoke a callable
	Value* Invoke (Function* called, size_t argc, Value* array[]);
	Value* Invoke (Function* called, size_t argc, ...);

	// System can control me
	friend class System;
};

// INLINE METHODS
//  These have to be down here, in the header, thanks to stupid C++ and it's inline linking

// --- Type Checking/Casting ---
inline
const Type*
Value::TypeOf (System* system, Value* value)
{
	if (value == NULL)
		return NULL;

	if ((int_t)value & 0x01)
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
	return ((int_t)value) & 0x01;
}

// --- Value --- 
inline
void
Value::Mark (Value* self)
{
	if (self != NULL && !((int_t)self & 0x01))
		if (!self->IsMarked())
			self->SGC::Collectable::Mark();
}
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
_CreateNew (Thread* thread, Value*, size_t, Value**)
{
	return new CTYPE(thread->GetSystem());
}

}

#endif
