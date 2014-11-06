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
	virtual Value* GetIndex (const System* system, const Value* index) const;
	/**
	 * Set an item at a given index.
	 * Set the value of an item at a given index.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param index The index value to use.
	 * @param set The value to set.
	 * @return The value of set if successful, or NULL on failure.
	 */
	virtual Value* SetIndex (const System* system, const Value* index, Value* set);
	/**
	 * Append an item.
	 * Used mainly in array types, it should append an item to the
	 * instance's internal list.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param value The value to append.
	 * @return The value appended on success, or NULL otherwise.
	 */
	virtual Value* Append (const System* system, Value* value);
	/**
	 * Check if a list has a value or key.
	 * Use this to check if a certain value exists in a list, or if a
	 * particular key is set.
	 * @note Over-ride in your derived class to customize behaviour.
	 * @param system System that the instance exists in.
	 * @param value The value or key to look for.
	 * @return True if the value/key exists, or false otherwise.
	 */
	virtual bool Has (const System* system, const Value* value) const;
	/**
	 * Get an iterator.
	 * Create an iterator for the list.
	 * @param system System iterator is in.
	 * @return An iterator, or NULL on error.
	 */
	virtual Iterator* GetIter (const System* system);

	public:
	/**
	 * Initialize list.
	 * @param system System that the instance will be created in.
	 * @return The initialized list instance.
	 */
	inline List (const System* system, const Type* type) : Value(system, type) {}

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
	inline static Value* GetIndex (const System* system, const List* list, const Value* index)
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
	inline static Value* SetIndex (const System* system, List* list, const Value* index, Value* set)
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
	inline static Value* Append (const System* system, List* list, Value* value)
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
	inline static bool Has (const System* system, const List* list, const Value* value)
	{
		return list->Has(system, value);
	}
	/**
	 * Get an iterator.
	 * Create an iterator for the list.
	 * @param system System iterator is in.
	 * @return An iterator, or NULL on error.
	 */
	inline static Iterator* GetIter (const System* system, List* list)
	{
		return list->GetIter(system);
	}
};

} // namespace Scriptix
