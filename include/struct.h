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

#ifndef SCRIPTIX_STRUCT_H
#define SCRIPTIX_STRUCT_H

#include <map>

namespace Scriptix {

/**
 * Struct value.
 * An structure is similar to a C structure.  Structs contain member values,
 * which can be read or modified.  Unlike C, Structs' member lists are
 * dynamic, like an associate array type.
 */
class Struct : public Value {
	SX_TYPEDEF

	// member data
	private:
	typedef GC::map<NameID, Value*> datalist;
	datalist data;

	// Method implementations
	protected:
	/**
	 * Set an unset member.
	 * If an attempt is made to set a member value that does not
	 * exist in the member list, this method is called.
	 * @param system The system the structure exists in.
	 * @param id The ID of the member to be set.
	 * @param value The value to set the member to.
	 */
	virtual void SetUndefMember (const System* system, NameID id, Value* value);
	/**
	 * Get an undefined member.
	 * If an attempt is made to lookup the value of an undefined
	 * member, this method is called to return a value.
	 * @param system The system the structure exists in.
	 * @param id The ID of the member to be retrieved.
	 */
	virtual Value* GetUndefMember (const System* system, NameID id) const;

	// Constructor
	public:
	/**
	 * Initialize structure.
	 * @param system System that the structure will be created in.
	 * @return The initialized structure instance.
	 */
	Struct (const System* system, const Type* type);
	Struct (const System* system);

	/**
	 * Set member value.
	 * Will set the given member to the given value.
	 * @param System System structure exists in.
	 * @param id The ID of the member to be set.
	 * @param value The value to set the member to.
	 */
	void SetMember (const System* system, NameID id, Value* value);

	/**
	 * Get member value.
	 * Get the value of the given member.
	 * @param System System structure exists in.
	 * @param id The ID of the member to be retrieved.
	 * @return The value of the member, or NULL on error.
	 */
	Value* GetMember (const System* system, NameID id) const;
};

} // namespace Scriptix

#endif
