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
	Array (const System* system);
	Array (const System* system, size_t n_size, Value** n_list);

	// Value Operations
	protected:
	virtual void Print (System* system) const;
	virtual bool True (const System* system) const;

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
		virtual bool Next (const System* system, Value*& value);

		// Constructor
		public:
		inline ArrayIterator (const System* system, Array* s_arr) :
			Scriptix::Iterator(system), array(s_arr), index(0) {}
	};
};

} // namespace Scriptix
