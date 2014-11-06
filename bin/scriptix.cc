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

#include <iostream>

#include "libsgc/libsgc.h"
#include "scriptix.h"

using namespace std;
using namespace Scriptix;

int
main (int argc, const char **argv) {
	// variables
	System* system;
	Invocable* func;
	Value** sargv;

	// initialize gc
	SGC::System::Initialize();

	// create a system context
	system = new System();
	if (system == NULL) { // check success
		cerr << "sx_create_system() failed." << endl;
		return 1;
	}

	// have we any command-line arguments?
	if (argc > 1) {
		// if first arg is -, read from stdin
		if (strcmp (argv[1], "-")) {
			// load the file name fiven
			if (system->LoadFile (argv[1]))
				return 1;
		} else {
			// read from stdin
			if (system->LoadFile(NULL))
				return 1;
		}
	} else {
		// no args - use stdin
		if (system->LoadFile(NULL))
			return 1;
	}

	// find the exported main function
	func = system->GetFunction(NameToID("main"));
	if (func == NULL) { // not found?
		cerr << "Fatal error: No main() function defined." << endl;
	} else {
		// have we more than one arg, to pass to our function?
		if (argc > 2) {
			// allocate array for values
			sargv = new (Value*)[argc - 2];
			// copy in values
			for (int i = 2; i < argc; ++i) {
				// crate String for each arguments
				sargv[i - 2] = String::Create(system, argv[i]);
			}
		} else {
			// no args, empty
			sargv = NULL;
		}

		// create new thread
		new Thread (system, func, 0, argc > 2 ? argc - 2 : 0, sargv);

		// delete our temporary array
		if (sargv)
			delete[] sargv;

		// run so long as we have open threads
		while (system->GetValidThreads())
			system->Run();
	}

	// free system context
	delete system;
	SGC::System::Shutdown();

	return 0;
}
