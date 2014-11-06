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

#ifndef SCRIPTIX_STRING_H
#define SCRIPTIX_STRING_H

#include <string>

namespace Scriptix {

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
	String (const System* system, const char* src, size_t len);
	String (const System* system, const char* src);
	String (const System* system, const std::string& src);

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
	virtual void Print (System* system) const;
	virtual bool Equal (const System* system, const Value* other) const;
	virtual int Compare (const System* system, const Value* other) const;
	virtual bool True (const System* system) const;
	virtual Value* GetIndex (const System* system, const Value* index) const;
	virtual bool Has (const System* system, const Value* value) const;
};

} // namespace Scriptix

#endif
