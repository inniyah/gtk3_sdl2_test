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
#include <list>
#include <iostream>

#include "libsgc/libsgc.h"

/**
 * Scriptix namespace.
 * All Scriptix methods, types, classes, and functions exist
 * in this namespace.
 */
namespace Scriptix {

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
	static Scriptix::Type _MyType; \
	static Scriptix::Method _MyMethods[]; \
	static Scriptix::Method _MyStaticMethods[]; \
	public: \
	static const Scriptix::Type* GetType (void) { return &_MyType; } \
	virtual const Scriptix::Type* GetMyType (void) const { return &_MyType; }
#define SX_TYPEIMPL(CPPNAME, SXNAME, CPPPARENT) \
	Scriptix::Type CPPNAME::_MyType = { \
		SXNAME , \
		CPPPARENT::GetType(), \
		CPPNAME::_MyMethods, \
		CPPNAME::_MyStaticMethods, \
	}; 
#define SX_NOMETHODS(CPPNAME) Scriptix::Method CPPNAME::_MyMethods[] = { { NULL, 0, 0, NULL } };
#define SX_NOSMETHODS(CPPNAME) Scriptix::Method CPPNAME::_MyStaticMethods[] = { { NULL, 0, 0, NULL } };
#define SX_BEGINMETHODS(CPPNAME) Scriptix::Method CPPNAME::_MyMethods[] = {
#define SX_ENDMETHODS { NULL, 0, 0, NULL } };
#define SX_BEGINSMETHODS(CPPNAME) Scriptix::Method CPPNAME::_MyStaticMethods[] = {
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
	SX_OP_PUSH = 0,
	SX_OP_ADD,
	SX_OP_SUBTRACT,
	SX_OP_MULTIPLY,
	SX_OP_DIVIDE,
	SX_OP_NEGATE,
	SX_OP_INVOKE,
	SX_OP_GT,
	SX_OP_LT,
	SX_OP_GTE,
	SX_OP_LTE = 10,
	SX_OP_EQUAL,
	SX_OP_NEQUAL,
	SX_OP_NOT,
	SX_OP_LOOKUP,
	SX_OP_ASSIGN,
	SX_OP_INDEX,
	SX_OP_PREINCREMENT,
	SX_OP_POSTINCREMENT,
	SX_OP_NEWARRAY,
	SX_OP_TYPECAST = 20,
	SX_OP_SETINDEX,
	SX_OP_METHOD,
	SX_OP_SETFILELINE,
	SX_OP_NEXTLINE,
	SX_OP_JUMP,
	SX_OP_POP,
	SX_OP_TEST,
	SX_OP_TJUMP,
	SX_OP_FJUMP,
	SX_OP_STATIC_METHOD = 30,
	SX_OP_YIELD,
	SX_OP_IN,
	SX_OP_SET_MEMBER,
	SX_OP_GET_MEMBER,
	SX_OP_ITER,
} sx_op_type;

// Thread flags
typedef enum {
	SX_TFLAG_PREEMPT = (1 << 0), // pre-emptable threading
} sx_thread_flags;

// Call-stack flags
typedef enum {
	SX_CFLAG_TTRUE = (1 << 0),
	SX_CFLAG_BREAK = (1 << 1),
} sx_call_flags;

// Thread states
typedef enum {
	SX_STATE_READY = 0,
	SX_STATE_RUNNING,
	SX_STATE_FINISHED,
	SX_STATE_FAILED,
	SX_STATE_RETURN,
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
class Call;
class System;
class Thread;
class Type;

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
typedef size_t sx_name_id;
typedef size_t sx_thread_id;

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
#define SX_TONUM(val) ((long)(val))
#define SX_TOTYPE(val) ((Scriptix::TypeValue*)(val))
#define SX_TOITER(val) ((Scriptix::Iterator*)(val))

// Name<->ID translation
sx_name_id NameToID(const char *name);
const char *IDToName(sx_name_id id);

/**
 * Type information.
 * Contains information on a Scriptix type.
 */
struct Type {
	const char* name;		///< Name of type.
	const Type* parent;		///< Parent type.
	const Method* methods;		///< Array of methods.
	const Method* smethods;		///< Array of static methods.

	/**
	 * Lookup a static method.
	 * Finds a static method with the given name.  Traverses ancestory.
	 * @param id ID of the method to find.
	 * @return A Method if exists, or NULL if not found.
	 */
	const Method* GetStaticMethod (sx_name_id id) const;
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
	// Stubs for data type
	protected:
	static Method _MyMethods[];
	static Method _MyStaticMethods[];

	public:
	/**
	 * Fetch the type information for the class.
	 * @return The type information
	 */
	static const Type* GetType (void) { return NULL; }
	/**
	 * Fetch the type information for the instance.
	 * @return The type information
	 */
	virtual const Type* GetMyType (void) const = 0;

	// Constructor/destructor
	public:
	/**
	 * Construct a new Value.
	 * This is the base constructor, which must be invoked by children
	 * constructuors.
	 * @param system A pointer to a System instance the Value is created in.
	 */
	Value (System* system) {}
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
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance exists in.
	 */
	virtual bool True (System* system);

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
	 * @param system System instance that the instances exists in.
	 * @param self The instance to be printed.
	 */
	inline static void Print (System* system, Value* self);
	/**
	 * Check equality.
	 * Compare equality of two instances, using the Equal method of the
	 * self instance.
	 * @param system System instance that the instance exists in.
	 * @param self First instance to check, used as basis for comparison.
	 * @param other Second instance to check.
	 * @return True if the instances are equal, false otherwise.
	 */
	inline static bool Equal (System* system, Value* self, Value* other);
	/**
	 * Compare relationship.
	 * Compare the ordered relationship between two instances, using the
	 * Compare method of the self instance.
	 * @param system System instance that the instances exists in.
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
	 * @param system System instance that the instances exists in.
	 * @param self The instance to check.
	 * @return True if the instance is true, false otherwise.
	 */
	inline static bool True (System* system, Value* self);

	// Silly type-casting struct hacks
	private:
	template <typename TTYPE>
	struct _TypeCheck {
		inline static bool Check(Value* value);
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
	inline static const Type* TypeOf (Value* value);
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
	inline static bool IsA (Value* value, const Type* type);
	/**
	 * Determine if an instance is of a given Type.
	 * Dynamically checks the type of an instance, and return true if the
	 * instance is of the given type, or the instance is derived from the 
	 * given type.
	 * @param value The value to type check.
	 * @return True if the value is of the given type, or derived from the
	 *   type, and false otherwise.
	 */
	template<typename TTYPE> inline static bool IsA(Value* value) { return _TypeCheck<TTYPE>::Check(value); }
	/**
	 * Cast an instance to a given type.
	 * Dynamically checks the type of an instance, and return a cast
	 * pointer if the instance is of the given type, or the instance is
	 * derived from the given type.
	 * @param value The value to type check.
	 * @return A cast pointer if the value is of the given type, or
	 *   derived from the type, and NULL otherwise.
	 */
	template<typename TTYPE> inline static TTYPE* Cast(Value* value) { return _TypeCheck<TTYPE>::Check(value) ? (TTYPE*)value : NULL; }

	/**
	 * Locate a method.
	 * Searches the instance's class ancestory for a method.
	 * @param value The instance to search.
	 * @param id The ID of the method to be found.
	 * @return The method if it exists, or NULL otherwise.
	 */
	static const Method* GetMethod (Value* value, sx_name_id id);

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
	Iterator (System* system) : Value(system) {}
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
	 * @param system System instance that the instance exists in.
	 * @param index The index to look at.
	 * @return The value at the given index, or NULL if the index is
	 *   invalid.
	 */
	virtual Value* GetIndex (System* system, Value* index);
	/**
	 * Set an item at a given index.
	 * Set the value of an item at a given index.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance exists in.
	 * @param value The value to append.
	 * @return The value appended on success, or NULL otherwise.
	 */
	virtual Value* Append (System* system, Value* value);
	/**
	 * Check if a list has a value or key.
	 * Use this to check if a certain value exists in a list, or if a
	 * particular key is set.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance will be created in.
	 * @return The initialized list instance.
	 */
	List (System* system) : Value(system) {}

	/**
	 * Fetch an item at a given index.
	 * Given an index, return the item at that index.  Used to implement
	 * any kind of multi-value property, such as arrays or data members.
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance exists in.
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
	 * @param system System instance that the instance exists in.
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
	struct Data {
		sx_name_id id;
		Value* value;
	};
	std::list<Data> data;

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
	virtual void SetUndefMember (System* system, sx_name_id id, Value* value);
	/**
	 * Get an undefined member.
	 * If an attempt is made to lookup the value of an undefined
	 * member, this method is called to return a value.
	 * @param system The system the structure exists in.
	 * @param id The ID of the member to be retrieved.
	 */
	virtual Value* GetUndefMember (System* system, sx_name_id id);

	// Garbage collection
	protected:
	void MarkChildren (void);

	// Constructor
	public:
	/**
	 * Initialize structure.
	 * @param system System instance that the structure will be created in.
	 * @return The initialized structure instance.
	 */
	Struct (System* system) : Value(system), data() {}

	/**
	 * Set member value.
	 * Will set the given member to the given value.
	 * @param System System structure exists in.
	 * @param id The ID of the member to be set.
	 * @param value The value to set the member to.
	 */
	void SetMember (System* system, sx_name_id id, Value* value);

	/**
	 * Get member value.
	 * Get the value of the given member.
	 * @param System System structure exists in.
	 * @param id The ID of the member to be retrieved.
	 * @return The value of the member, or NULL on error.
	 */
	Value* GetMember (System* system, sx_name_id id);
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
	Number (System* system) : Value (system) {}
	/**
	 * Phony destructor.
	 * We need a destructor for this class to satisfy libsgc.  Abstract
	 * declaration to guarantee we don't instantiate this class.
	 */
	~Number (void) = 0; // disallow creation of Number

	/**
	 * Create new numeric value.
	 * Given a long value, create an encoded pointer usable in the rest
	 * of the Scriptix system.
	 * @param i Numeric value.
	 * @return Encoded numeric value.
	 */
	static Value* Create (long i) { return ((Value* )((i << 1) | SX_NUM_MARK)); }
	/**
	 * Decode numeric value.
	 * Given an encoded numeric value, return a normal long numeric value.
	 * @param num Encoded numeric value.
	 * @return Decoded long numeric value.
	 */
	static long ToInt (Value* num) { return (long)num >> 1; }
};

/**
 * String value.
 * Stores a string of text.  This class is special in that its size is
 * variable; the data of the string is appended to the memory of the
 * class.
 *
 * Thanks to C++ memory management, this requires a few hacks.  An
 * important note is that the memory is allocated using new[], but will
 * eventually be deleted with delete.  (note lack of [])  This can cause
 * certain memory debuggers to complain.  It might also cause crashes
 * on weird architectures that have different memory pools for the variable
 * new/delete operators.
 */
struct String : public Value {
	SX_TYPEDEF

	private:
	typedef char ctype;	///< Type of each character in the string.
	size_t len;		///< Length of the string.
	ctype str[0];		///< Fake array, data of string.

	// Methods
	private:
	static Value* MethodLength (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodTonum (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodUpper (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodLower (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodSplit (Thread* thread, Value* self, size_t argc, Value** argv);
	static Value* MethodSubstr (Thread* thread, Value* self, size_t argc, Value** argv);

	static Value* SMethodConcat (Thread* thread, Value* self, size_t argc, Value** argv);

	private:
	String (System* system, const ctype* src, size_t len);
	// Our specialized new operator
	void* operator new (size_t size, size_t slen) { return new ctype[size + ((slen + 1) * sizeof(ctype))]; }

	/**
	 * Alloc space for a string.
	 * This is an internally used method to create an empty string of a
	 * given length.  This is needed in methods that must construct a
	 * string piece by piece: they need the space allocated, but don't
	 * have the character data actually ready.
	 * @param system The system the string is to be created in.
	 * @param length Length in ctypeacters of the new string.
	 * @return A new string instance, or NULL on error.
	 */
	static String* Alloc (System* system, size_t length)
	{
		return new(length) String(system, NULL, length);
	}

	// Convenience allocators
	public:
	/**
	 * Create a new string instance.
	 * This method must be used versus the new operator due to the memory
	 * allocation needs of the string class.  This method copies the
	 * input string.
	 * @param system The system the string is to be created in.
	 * @param src A C string that the new instance will contain.
	 * @return A new string instance, or NULL on error.
	 */
	static String* Create (System* system, const ctype* src)
	{
		size_t len = src ? strlen(src) : 0;
		return new(len) String(system, src, len);
	}
	/**
	 * Create a new string instance.
	 * This method must be used versus the new operator due to the memory
	 * allocation needs of the string class.  This method copies the
	 * input string.  If the input string is longer than the maximum
	 * specified, the resulting string instance will contain a truncated
	 * copy.
	 * @param system The system the string is to be created in.
	 * @param src A C string that the new instance will contain.
	 * @param max Maximum length in ctypeacters of the new string.
	 * @return A new string instance, or NULL on error.
	 */
	static String* Create (System* system, const ctype* src, size_t max)
	{
		size_t len = src ? strlen(src) : 0;
		if (len < max)
			return new(len) String(system, src, len);
		else
			return new(max) String(system, src, max);
	}

	// Query data
	public:
	/**
	 * Get length of string.
	 * @return Length of the string.
	 */
	size_t GetLen (void) const { return len; }
	/**
	 * Get C string.
	 * Returns a pointer type to be used in C/C++ code.
	 * @return A pointer to an array of the ctypeacter type.
	 */
	const ctype* GetStr (void) const { return str; }

	// Operations
	protected:
	virtual void Print (System* system);
	virtual bool Equal (System* system, Value* other);
	virtual int Compare (System* system, Value* other);
	virtual bool True (System* system);
	virtual Value* GetIndex (System* system, Value* index);
	virtual bool Has (System* system, Value* value);
};

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
	virtual Value* GetIndex (System* system, Value* index);
	virtual Value* SetIndex (System* system, Value* index, Value* set);
	virtual Value* Append (System* system, Value* value);
	virtual bool Has (System* system, Value* value);
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

class Function : public Value {
	SX_TYPEDEF

	public:
	Function (System* system);
	Function (System* system, sx_name_id id, size_t argc, bool varg); // argc is minimum arg count
	Function (System* system, sx_name_id id, size_t argc, bool varg, sx_cfunc func); // argc is minimum arg count
	~Function (void);

	sx_name_id id; // name of function
	size_t argc; // number of arguments to function
	size_t varc; // number of variables in function
	long* nodes; // byte codes
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

// "wrap" an Type - in type.cc
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
	TypeValue (System* system, const Type* s_type) : Value(system), type(s_type) {}

	const Type* GetTypePtr (void) const { return type; } // silly name from conflict
};

// OTHER CONSTRUCTS
struct Method {
	const char* name;
	size_t argc;
	bool varg;
	sx_cmethod method;
};

struct Global {
	sx_name_id id;
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
	// special struct for function tags
	struct Tag {
		char* name;
		Tag* next;
	};
	// pools - not used inside, useful outside
	struct Pool {
		size_t argc;
		Value** argv;
		Pool* next;
	};

	private:
	// global data
	std::vector<const Type*> types;
	std::vector<Global> globals;
	Function* funcs;

	// tags feature
	Tag* tags;

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
	int AddType (const Type* type);
	const Type* GetType (sx_name_id id) const;

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
	Function* GetFunction (sx_name_id id);

	// Globals
	int AddGlobal (sx_name_id id, Value* value);
	Value* GetGlobal (sx_name_id id) const;

	// Threads
	void AddThread (Thread* thread);
	void EndThread (Thread* thread);

	// Running threads
	int Run (void);
	int WaitOn (sx_thread_id id, int *retval);
	int NestedRun (Thread* thread, Value** retval);

	// Pools
	int PushPool (size_t argc, Value** argv);
	void PopPool (void);

	// Function tags
	int AddFunctionTag (const char *tag);
	bool ValidFunctionTag (const char* tag);
	virtual void HandleFunctionTag (const char* tag, Function* func) {} // over-ride to handle

	// Load/compile scripts
	int LoadFile (const char *file);
	int LoadString (const char *buffer);

	// FIXME: hacks
	friend Value::Value (System* system);
};

class Thread {
	private:
	// various stuffs
	System* system;
	Value* ret;
	int state;
	unsigned char flags;
	sx_thread_id id;

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
	sx_thread_id GetID(void) const { return id; }

	// Get system
	System* GetSystem(void) const { return system; }

	// Raise an error condition
	int RaiseError (int err, const char *format, ...);
	int RaiseArgError (const char* func, const char* arg, const char* type)
	{
		return RaiseError(SXE_BADARGS, "Argument '%s' to '%s' is not a '%s'", arg, func, type);
	}

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
const Type*
Value::TypeOf (Value* value)
{
	if (value == NULL)
		return NULL;

	if ((long)value & 0x01)
		return Number::GetType();

	return value->GetMyType();
}

bool
Value::IsA (Value* value, const Type* type)
{
	const Type* my_type = Value::TypeOf (value);

	while (my_type != NULL) {
		if (my_type == type)
			return true;
		my_type = my_type->parent;
	}

	return false;
}

template <typename TTYPE>
bool
Value::_TypeCheck<TTYPE>::Check(Value* value)
{
	return Value::IsA(value, TTYPE::GetType());
}

template <>
bool
Value::_TypeCheck<Number>::Check(Value* value)
{
	return ((long)value) & 0x01;
}

// --- Value --- 
void
Value::Mark (Value* self)
{
	if (self != NULL && !IsA<Number>(self))
		if (!self->IsMarked())
			self->SGC::Collectable::Mark();
}
void
Value::Print (System* system, Value* self)
{
	if (self != NULL && !IsA<Number>(self))
		self->Print(system);
	else if (IsA<Number>(self))
		std::cout << Number::ToInt(self);
	else
		std::cout << "(nil)";
}
bool
Value::Equal (System* system, Value* self, Value* other)
{
	if (self == other)
		return true;

	if (self != NULL && !IsA<Number>(self))
		return self->Equal(system, other);
	else
		return false;
}
int
Value::Compare (System* system, Value* self, Value* other)
{
	if (self == other)
		return 0;

	if (self != NULL && !IsA<Number>(self))
		return self->Compare(system, other);
	else if (IsA<Number>(self)) {
		if (Number::ToInt(self) < Number::ToInt(other))
			return -1;
		else
			return 1;
	} else
		return 1; // default
}
bool
Value::True (System* system, Value* self)
{
	if (self == NULL)
		return false;
	else if (IsA<Number>(self))
		return Number::ToInt(self);
	else
		return self->True(system);
}

// ---- Magic NEW operator constructor ----
template <class CTYPE>
Value*
_CreateNew (Thread* thread, Value*, size_t, Value**)
{
	return new CTYPE(thread->GetSystem());
}

}

#endif
