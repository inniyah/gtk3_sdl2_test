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
#include <set>

namespace Scriptix {
namespace GC {

typedef ::gc Collectable;

// GC traced version of std::map
template <typename K, typename T>
struct map : public std::map<const K, T, std::less<const K>, gc_allocator<std::pair<const K, T> > >, public Collectable { };

// GC traced version of std::set
template <typename K>
struct set : public std::set<K, std::less<K>, gc_allocator<K> >, public Collectable { };

// GC traced version of std::list
template <typename T>
struct list : public std::list<T, gc_allocator<T> >, public Collectable { };

// GC traced version of std::vector
template <typename T>
struct vector : public std::vector<T, gc_allocator<T> >, public Collectable { };

} // namespace GC
} // namespace Scriptix

#endif
