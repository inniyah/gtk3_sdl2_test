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

#ifndef SCRIPTIX_COLLECTABLE_H
#define SCRIPTIX_COLLECTABLE_H

#include <gc/gc_cpp.h>

/* fix for this file being broken... */
#ifndef AWESOMEPLAY_GC_ALLOCATOR_H
#define AWESOMEPLAY_GC_ALLOCATOR_H
#include <gc/gc_allocator.h>
#endif

#include <vector>
#include <list>
#include <map>

namespace Scriptix {
namespace GC {

/* Provide a base class for GC objects.  Very similar to the GC's normal
 * Collectable class, except it uses the no_order variant of the finalizer
 * registration; this allows us to have destructors even when we've cyclic
 * links of objects.  Destructors should never use pointers to GC'd data,
 * only free non-GC'd resources, like strings and file handles.
 */

class Collectable : virtual public ::gc
{
	public:
	Collectable (void);
	inline virtual ~Collectable (void) {}
	private:
	static void cleanup(void* obj, void* data);
};

// GC traced version of std::map
template <typename K, typename T>
struct map : public std::map<K, T, std::less<K>, traceable_allocator<std::pair<K, T> > > { };

// GC traced version of std::list
template <typename T>
struct list : public std::list<T, traceable_allocator<T> > { };

// GC traced version of std::vector
template <typename T>
struct vector : public std::vector<T, traceable_allocator<T> > { };

} // namespace GC
} // namespace Scriptix

#endif
