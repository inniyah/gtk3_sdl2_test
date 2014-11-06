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
	virtual bool Next (const System* system, Value*& value) = 0;

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
	Iterator (const System* system);
};

} // namespace Scriptix
