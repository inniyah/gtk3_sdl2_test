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

#ifndef SCRIPTIX_STRUCT_H
#define SCRIPTIX_STRUCT_H

#include <map>

namespace Scriptix {

class Struct : public Value {
	// member data
	protected:
	typedef GC::map<NameID, Value*> datalist;
	datalist data;

	// Method implementations
	protected:
	virtual void SetUndefMember (NameID id, Value* value);
	virtual Value* GetUndefMember (NameID id) const;

	// Constructor
	public:
	Struct ();

	virtual const TypeInfo* GetType () const;

	void SetMember (NameID id, Value* value);

	Value* GetMember (NameID id) const;
};

class ScriptClass : public Struct {
	public:
	inline ScriptClass (const TypeInfo* s_type) : Struct(), type(s_type) {}

	virtual const TypeInfo* GetType () const { return type; }

	private:
	const TypeInfo* type;
};

// Used for custom types
extern const TypeDef Struct_Type;
extern const TypeDef ScriptClass_Type;

} // namespace Scriptix

#endif
