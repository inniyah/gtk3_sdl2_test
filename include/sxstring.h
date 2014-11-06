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

#ifndef SCRIPTIX_STRING_H
#define SCRIPTIX_STRING_H

#include <string>

namespace Scriptix {

typedef std::basic_string<char, std::char_traits<char>, gc_allocator<char> > BaseString;

class String : public Value {
	public:
	String (const char* src, size_t len);
	String (const char* src);
	String (const BaseString& src);

	virtual const TypeInfo* GetType () const;

	// Methods
	public:
	static Value* MethodLength (size_t argc, Value** argv);
	static Value* MethodUpper (size_t argc, Value** argv);
	static Value* MethodLower (size_t argc, Value** argv);
	static Value* MethodSplit (size_t argc, Value** argv);
	static Value* MethodSubstr (size_t argc, Value** argv);
	static Value* MethodTrim (size_t argc, Value** argv);
	static Value* MethodLtrim (size_t argc, Value** argv);
	static Value* MethodRtrim (size_t argc, Value** argv);
	static Value* MethodToInt (size_t argc, Value** argv);

	static Value* SMethodConcat (size_t argc, Value** argv);

	// Query data
	public:
	inline size_t GetLen (void) const { return data.length(); }
	inline const char* GetCStr (void) const { return data.c_str(); }
	inline const BaseString& GetStr (void) const { return data; }

	// Operations
	protected:
	virtual void Print () const;
	virtual bool Equal (const Value* other) const;
	virtual int Compare (const Value* other) const;
	virtual bool True () const;
	virtual Value* GetIndex (Value* index) const;
	virtual bool Has (const Value* value) const;

	private:
	BaseString data;
};

} // namespace Scriptix

#endif
