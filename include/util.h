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

#ifndef SCRIPTIX_UTIL_H
#define SCRIPTIX_UTIL_H

namespace Scriptix {

// Utility functions

template <typename T1> inline int
CheckArgs (Thread* thread, Value** argv, const char* fname, const char* name1) {
	if (!Value::IsA<T1>(thread->GetSystem(), argv[0])) {
		thread->RaiseArgError(fname, name1, T1::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	return SXE_OK;
}
template <typename T1, typename T2> inline int
CheckArgs (Thread* thread, Value** argv, const char* fname, const char* name1, const char* name2) {
	if (!Value::IsA<T1>(thread->GetSystem(), argv[0])) {
		thread->RaiseArgError(fname, name1, T1::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	if (!Value::IsA<T2>(thread->GetSystem(), argv[1])) {
		thread->RaiseArgError(fname, name2, T2::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	return SXE_OK;
}
template <typename T1, typename T2, typename T3> inline int
CheckArgs (Thread* thread, Value** argv, const char* fname, const char* name1, const char* name2, const char* name3) {
	if (!Value::IsA<T1>(thread->GetSystem(), argv[0])) {
		thread->RaiseArgError(fname, name1, T1::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	if (!Value::IsA<T2>(thread->GetSystem(), argv[1])) {
		thread->RaiseArgError(fname, name2, T2::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	if (!Value::IsA<T3>(thread->GetSystem(), argv[2])) {
		thread->RaiseArgError(fname, name3, T3::GetTypeDef()->name);
		return SXE_BADTYPE;
	}
	return SXE_OK;
}

} // namespace Scriptix

#endif
