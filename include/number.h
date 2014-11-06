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

#ifndef SCRIPTIX_NUMBER_H
#define SCRIPTIX_NUMBER_H

#include "scriptix/sysdep.h"

namespace Scriptix {

// how to mark a number
const intptr_t NUM_MARK = 0x01;

/**
 * Numeric value.
 * This is the class of a numeric value.  Note that there will *never* be an
 * instance of this class, as numerics are encoded into pointers.  However, we
 * still need the class for member functions and type specification.
 */
class Number : public Value {
	SX_TYPEDEF

	private:
	// Methods
	/**
	 * Method: Convert to a string.
	 * A method to convert a number to a String.
	 * @param thread Current thread.
	 * @param self Numeric value.
	 * @param argc Argument count, unused.
	 * @param argv Argument list, unused.
	 * @return A String.
	 */
	static Value* MethodTostr (Thread* thread, Value* self, size_t argc, Value** argv);

	public:
	/**
	 * Phony constructor.
	 * We need a constructor for this class to satisfy libsgc.
	 */
	Number (void);

	/**
	 * Phony destructor.
	 * We need a destructor for this class to satisfy libsgc.  Abstract
	 * declaration to guarantee we don't instantiate this class.
	 */
	~Number (void) = 0; // disallow creation of Number

	/**
	 * Create new numeric value.
	 * Given an intptr_t value, create an encoded pointer usable in the rest
	 * of the Scriptix system.
	 * @param i Numeric value.
	 * @return Encoded numeric value.
	 */
	inline static Value* Create (intptr_t i) { return ((Value* )((i << 1) | NUM_MARK)); }
	/**
	 * Decode numeric value.
	 * Given an encoded numeric value, return a normal intptr_t numeric value.
	 * @param num Encoded numeric value.
	 * @return Decoded intptr_t numeric value.
	 */
	inline static intptr_t ToInt (const Value* num) { return (intptr_t)num >> 1; }
};

} // namespace Scriptix

#endif
