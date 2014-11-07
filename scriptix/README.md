Scriptix Embedded Scripting Engine
Copyright (C) 2014, Miriam Ruiz <miriam@debian.org>
Copyright (C) 2002,2003  AwesomePlay Productions, Inc.
Sean Middleditch <elanthis@awesomeplay.com>
Basic Scriptix Information
------------------------------------------------------


1. Introduction
   ============
   Scriptix is a scripting system coded in C++, designed solely for embedding
   in other C++ applications.  Scriptix doesn't pretend to be a stand-alone
   language.

   The language is based loosely on C++, Java, and C#.  Scriptix is a
   dynamically typed language.  (Meaning you don't declare
   variable/argument/return types.)  Scriptix is heavily OO based, however.

   Scriptix is intended to be fast, tho it isn't as fast as it could be.  (The
   older C version was much faster, due to better optimizations in the system.)


2. Features
   ========
   Scriptix is an object-oriented language.  Classes/types can only be defined
   from with the embedding application using the C++ API.

   Scriptix provides several core types, including Numbers (31-bit signed
   integers only, currently), Strings, Arrays, Structs, and Functions.

   New functions may be defined in scripts, and may be defined public.  Public
   functions are accessible to any other source file that is loaded afterwards,
   while non-public functions are only accessible to the source file they were
   declared in.

   All basic operations are supported, including math, string concatenation,
   array indexing, and so forth.

   Scriptix is threadable; it uses it's own (simplistic) threading interface to
   allow multiple scripts to be running at the same time.  Threads can be
   either cooperatively or pre-emptively threaded.  Cooperative threads must
   give up control explicitly, while pre-emptive threads have control taken
   away after a set number of instructions have been executed.

3. Install
   =======

   You will need the GC from http://www.hpl.hp.com/personal/Hans_Boehm/gc/ in
   order to build Scriptix.

   In order to compile, you will need a fairly recent version of GCC.
   Versions 3.1 and higher are officially supported.

   You will also need fairly recent flex and bison tools to muck with the
   grammar, and docbook-utils in order to build the documentation.


4. Bugs
   ====
   A bug tracking system is available at http://bugs.awemud.net for logging
   bugs and feature requests for Scriptix.

   If you happen to be experiencing a crash, it is important that you provide
   several pieces of information.  First, we need a backtrace; a log of what
   was going on inside Scriptix when the crash occured.  Second, we need a
   sample script that reproduces the crash.

   Before making a backtrace, you must make sure Scriptix is compiled with
   debugging on, and optimization turned off.  You can do this using the
   -g and -O0 compile flags to GCC.  To enable these flags, set the CXXFLAGS
   environment variable accordingly:
     export CXXFLAGS="-O0 -g"

   To generate a backtrace, you must run Scriptix in a debugger, such as GDB.
   Doing this can be slightly tricky.  I recommend using the following
   command:
     LD_LIBRARY_PATH=lib/.libs gdb bin/.libs/scriptix

   The run Scriptix, using the 'r' command in GDB.  Append an command line
   options (such as the filename of your script) to this command.  I.e.,
     r test/fact.sx 5000

   When the crash occurs, use the 'bt' command to generate a backtrace.  Copy
   and paste all of the GDB output to your bug report.


5. Documentation
   =============
   Yes, we're seriously lacking it.
   

6. Legal
   =====
   Scriptix comes with no warranty.  If something bad happens to you because of
   your use of Scriptix, we (the authors, distributors, builders, and testers)
   are not responsible for your misfortune and/or mistakes.  See the disclaimer
   section below.

   Scriptix is licensed under the BSD license.  See the COPYING file for more
   details.  As a summary, the BSD license gives you rights to do whatever you
   want with the code.  Note: you can NOT change the license of our code, or
   modify copyrights.  Our code is our code, and it is released under the BSD
   license - end of story.  You can, however, add new code or modify existing
   code.  Any code you write is yours, and licensed under whichever license you
   choose - end of story.  The BSD license grants you the right to distribute
   binaries; the license does NOT guarantee receivers of the binaries rights to
   the source code, original or modified.  The BSD license is ideal if you wish
   to release a modified codebase in a commercial setting.

   We do appreciate being given credit if you distribute binaries, but it is
   not legally required.


7. Disclaimer
   ==========
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
   DAMAGE.
