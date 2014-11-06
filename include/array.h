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

namespace Scriptix {

class Array : public Value {
	public:
	Array ();
	Array (size_t n_size, Value** n_list);

	virtual const TypeInfo* GetType () const;

	// Value Operations
	protected:
	virtual void Print () const;
	virtual bool True () const;

	// Array Operations
	public:
	virtual Value* GetIndex (long index) const;
	virtual Value* SetIndex (long index, Value* set);
	virtual Value* Append (Value* value);
	virtual bool Has (Value* value) const;
	virtual Iterator* GetIter ();

	// Methods
	public:
	static Value* MethodLength (size_t argc, Value** argv);
	static Value* MethodAppend (size_t argc, Value** argv);
	static Value* MethodRemove (size_t argc, Value** argv);
	static Value* MethodIter (size_t argc, Value** argv);

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
		virtual bool Next (Value*& value);

		// Constructor
		public:
		inline ArrayIterator (Array* s_arr) :
			Scriptix::Iterator(), array(s_arr), index(0) {}
	};

	public:
	inline static Value* GetIndex (const Array* array, long index)
	{
		return array->GetIndex(index);
	}
	inline static Value* SetIndex (Array* array, long index, Value* set)
	{
		return array->SetIndex(index, set);
	}
	inline static Value* Append (Array* array, Value* value)
	{
		return array->Append(value);
	}
	inline static bool Has (const Array* array, Value* value)
	{
		return array->Has(value);
	}
	inline static Iterator* GetIter (Array* array)
	{
		return array->GetIter();
	}

	protected:
	size_t size;
	size_t count;
	Value** list;
};

} // namespace Scriptix
