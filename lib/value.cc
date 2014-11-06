/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003  AwesomePlay Productions, Inc.
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

#include "scriptix.h"
#include "system.h"

#include <iostream>
#include <string.h>

using namespace Scriptix;

// Methods
MethodDef Value::_MyStaticMethods[] = { { NULL, 0, 0, NULL } };
MethodDef Value::_MyMethods[] = { { NULL, 0, 0, NULL } };

// DEFAULT IMPLEMENTATIONS
void
Value::Print (System* system) const
{
	std::cout << this;
}

bool
Value::Equal (const System* system, const Value* other) const
{
	return this == other;
}

int
Value::Compare (const System* system, const Value* other) const
{
	return !(this == other);
}

bool
Value::True (const System* system) const
{
	return true;
}

// COMPLEX WRAPPERS
Value*
Value::ToString(const System* system, const Value* self)
{
	if (self == NULL) {
		return NULL;
	} else if (IsA<String>(system, self)) {
		// safe to un-const-ify because strings are immutable anyway
		return const_cast<Value*>(self);
	} else if (IsA<Number>(system, self)) {
		char buf[20];
		snprintf (buf, 20, "%d", Number::ToInt (self));
		return new String(system, buf);
	} else {
		return self->ToString(system);
	}
}

Value*
Value::DoToInt(const System* system, const Value* self)
{
	if (self == NULL) {
		return NULL;
	} else if (IsA<String>(system, self)) {
		return Number::Create(atoi(((String*)self)->GetCStr()));
	} else {
		return self->ToInt(system);
	}
}
