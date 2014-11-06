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
	Assoc (const System* system);
	Assoc (const System* system, size_t n_size, Value** n_list); // evens are strings, odds are values

	// Value Operations
	protected:
	virtual void Print (System* system) const;
	virtual bool True (const System* system) const;

	// List Operations
	public:
	virtual Value* GetIndex (const System* system, const Value* index) const;
	virtual Value* SetIndex (const System* system, const Value* index, Value* set);
	virtual Value* Append (const System* system, Value* value);
	virtual bool Has (const System* system, const Value* value) const;

	// Custom
	public:
	inline size_t GetCount (void) const { return count; }
	inline Value* GetIndex (size_t i) const { return list[i].value; }
	inline Value* SetIndex (size_t i, Value* value) { return list[i].value = value; }
};

} // namespace Scriptix
