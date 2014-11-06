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

class Number;
class TypeInfo;
class TypeDef;

class Value : public GC::Collectable {
	public:
	// Constructor/destructor
	public:
	inline Value () : gc() {}
	virtual ~Value (void) {}

	// Operations
	protected:
	virtual void Print () const;
	virtual bool Equal (const Value* other) const;
	virtual int Compare (const Value* other) const;
	virtual bool True () const;
	virtual const TypeInfo* GetType (void) const = 0;

	// Operate on values
	public:
	static void Print (const Value* self);
	static bool Equal (const Value* self, const Value* other);
	static int Compare (const Value* self, const Value* other);
	static bool True (const Value* self);
	static Value* ToString (Value* self);
	static Value* ToInt (Value* self);

	// Silly type-casting struct hacks
	private:
	template <typename TTYPE>
	struct _TypeCheck {
		inline static bool Check(const Value* value);
	};

	// Special operations
	public:
	static const TypeInfo* TypeOf (const Value* value);
	static bool IsA (const Value* value, const TypeInfo* type);
	template<typename TTYPE> inline static bool IsA(const Value* value) { return _TypeCheck<TTYPE>::Check(value); }

	// class System has to access this for the GC
	friend class System;
};

// Nil
class Value* const Nil = NULL;

} // namespace Scriptix
