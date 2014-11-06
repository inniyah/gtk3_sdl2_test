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

namespace Scriptix {

class Number;

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
class Value : public GC::Collectable {
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
	 * @param system A pointer to a class System the Value is created in.
	 */
	Value (const class System* system, const Type* s_type) : gc(), type(s_type) {}
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
	 * @param system class System that the instance exists in.
	 */
	virtual void Print (class System* system) const;
	/**
	 * Check equality.
	 * Test whether two instances are equal to each other.  The more
	 * in-depth and accurate, the better.  For example, comparing a
	 * string with a number would be a good idea to implement here.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @see Compare
	 * @see True
	 * @param system class System that the instance exists in.
	 * @param other The instance to compare against.
	 * @return Return true if equal, false otherwise.
	 */
	virtual bool Equal (const class System* system, const Value* other) const;
	/**
	 * Compare relationship.
	 * Compare the relationship between two instance; which one
	 * is ordered before the other.  Using in less-than comparisons
	 * and friends.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @see Equal
	 * @see True
	 * @param system class System that the instance exists in.
	 * @param other The instance to compare against.
	 * @return -1 when the current instance comes before the other
	 *   instance, 0 when the instances are equal (or no comparison can
	 *   be made), and 1 when the other instance comes before the
	 *   current instance.
	 */
	virtual int Compare (const class System* system, const Value* other) const;
	/**
	 * Test truth.
	 * Test if the instance is a "true" instance or not.  Used in if and
	 * other boolean test.  For example, on an array type, return true
	 * if the array has more than 0 items, or false otherwise.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @see Equal
	 * @see Compare
	 * @param system class System that the instance exists in.
	 */
	virtual bool True (const class System* system) const;
	/**
	 * Cast to a string.
	 * Attempt to convert the value to a string.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, a string must always
	 * be returned; an empty string is allowed.
	 * @param system class System that the instance exists in.
	 * @return A string if conversion is possible, or NULL otherwise.
	 */
	virtual Value* ToString (const class System* system) const { return NULL; }
	/**
	 * Cast to an int.
	 * Attempt to convert the value to an int.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, an int must always
	 * be returned; zero is allowed.
	 * @param system class System that the instance exists in.
	 * @return An int if conversion is possible, or NULL otherwise.
	 */
	virtual Value* ToInt (const class System* system) const { return NULL; }

	// Operate on values
	public:
	/**
	 * Print an instance.
	 * Calls the Print method for the given instance.
	 * @param system class System that the instances exists in.
	 * @param self The instance to be printed.
	 */
	inline static void Print (class System* system, const Value* self);
	/**
	 * Check equality.
	 * Compare equality of two instances, using the Equal method of the
	 * self instance.
	 * @param system class System that the instance exists in.
	 * @param self First instance to check, used as basis for comparison.
	 * @param other Second instance to check.
	 * @return True if the instances are equal, false otherwise.
	 */
	inline static bool Equal (const class System* system, const Value* self, const Value* other);
	/**
	 * Compare relationship.
	 * Compare the ordered relationship between two instances, using the
	 * Compare method of the self instance.
	 * @param system class System that the instances exists in.
	 * @param self First instance to check, used as basis for comparison.
	 * @param other Second instance to check.
	 * @return -1 when the self instance comes before the other
	 *   instance, 0 when the instances are equal (or no comparison can
	 *   be made), and 1 when the other instance comes before the
	 *   self instance.
	 */
	inline static int Compare (const class System* system, const Value* self, const Value* other);
	/**
	 * Check truth.
	 * Determine if an instance is a true value or not, for boolean checks.
	 * Calls the Truth method on the given instance.
	 * @param system class System that the instances exists in.
	 * @param self The instance to check.
	 * @return True if the instance is true, false otherwise.
	 */
	inline static bool True (const class System* system, const Value* self);
	/**
	 * Cast to a string.
	 * Attempt to convert the value to a string.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, a string must always
	 * be returned; an empty string is allowed.
	 * @param system class System that the instance exists in.
	 * @param self The instance to convert.
	 * @return A string if conversion is possible, or NULL otherwise.
	 */
	static Value* ToString (const class System* system, const Value* self);
	/**
	 * Cast to an int.
	 * Attempt to convert the value to an int.  Return NULL if this
	 * isn't allowed.  If conversion is allowed, an int must always
	 * be returned; zero is allowed.
	 * @param system class System that the instance exists in.
	 * @param self The instance to convert.
	 * @return An int if conversion is possible, or NULL otherwise.
	 */
	inline static Value* ToInt (const class System* system, const Value* self)
		{ return Value::IsA<Number>(system, self) ? const_cast<Value*>(self) : DoToInt(system, self); }
		// safe to un-const-ify since Number isn't really a class...

	// Silly type-casting struct hacks
	private:
	template <typename TTYPE>
	struct _TypeCheck {
		inline static bool Check(const class System* system, const Value* value);
	};

	// In depth int casting
	static Value* DoToInt (const class System* system, const Value* self);

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
	inline static const Type* TypeOf (const class System* system, const Value* value);
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
	inline static bool IsA (const class System* system, const Value* value, const Type* type);
	/**
	 * Determine if an instance is of a given Type.
	 * Dynamically checks the type of an instance, and return true if the
	 * instance is of the given type, or the instance is derived from the 
	 * given type.
	 * @param value The value to type check.
	 * @return True if the value is of the given type, or derived from the
	 *   type, and false otherwise.
	 */
	template<typename TTYPE> inline static bool IsA(const class System* system, const Value* value) { return _TypeCheck<TTYPE>::Check(system, value); }
	/**
	 * Cast an instance to a given type.
	 * Dynamically checks the type of an instance, and return a cast
	 * pointer if the instance is of the given type, or the instance is
	 * derived from the given type.
	 * @param value The value to type check.
	 * @return A cast pointer if the value is of the given type, or
	 *   derived from the type, and NULL otherwise.
	 */
	template<typename TTYPE> inline static TTYPE* Cast(const class System* system, const Value* value) { return _TypeCheck<TTYPE>::Check(system, value) ? (TTYPE*)value : NULL; }

	// class System has to access this for the GC
	friend class System;
};

// Nil
class Value* const Nil = NULL;

} // namespace Scriptix
