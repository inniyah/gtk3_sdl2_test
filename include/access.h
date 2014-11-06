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

#ifndef SCRIPTIX_ACCESS_H
#define SCRIPTIX_ACCESS_H

#include "scriptix/sysdep.h"

namespace Scriptix {

// Security level type
typedef uint16_t SecurityLevel;

// Basic secutity types
const SecurityLevel SEC_FILEIO = (1);		// allowed to do file i/o
const SecurityLevel SEC_NETWORKIO = (1 << 1);// allowed to do network i/o
const SecurityLevel SEC_FORK = (1 << 2);		// allowed to use fork()

// Reserved security types
const SecurityLevel SEC_RESERVED1 = (1 << 3);// first user sec type
const SecurityLevel SEC_RESERVED2 = (1 << 4);// first user sec type
const SecurityLevel SEC_RESERVED3 = (1 << 5);// first user sec type
const SecurityLevel SEC_RESERVED4 = (1 << 6);// first user sec type
const SecurityLevel SEC_RESERVED5 = (1 << 7);// first user sec type

// User available security types
const SecurityLevel SEC_USER1 = (1 << 8); 	// first user sec type
const SecurityLevel SEC_USER2 = (1 << 9); 	// second user sec type
const SecurityLevel SEC_USER3 = (1 << 10); 	// third user sec type
const SecurityLevel SEC_USER4 = (1 << 11); 	// fourth user sec type
const SecurityLevel SEC_USER5 = (1 << 12); 	// fifth user sec type
const SecurityLevel SEC_USER6 = (1 << 13); 	// sixth user sec type
const SecurityLevel SEC_USER7 = (1 << 14); 	// seventh user sec type
const SecurityLevel SEC_USER8 = (1 << 15); 	// eight user sec type

const SecurityLevel SEC_DEFAULTS = (SEC_FILEIO|SEC_NETWORKIO|SEC_FORK);

} // namespace Scriptix

#endif
