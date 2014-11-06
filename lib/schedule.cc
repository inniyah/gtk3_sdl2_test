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

#include <stdlib.h>

#include "scriptix.h"
#include "config.h"

using namespace Scriptix;

int
System::Run (void)
{
	Thread* next;

	if (cur_thread == NULL)
		cur_thread = threads;
	while (cur_thread != NULL) {
		cur_thread->Run();
		if (cur_thread) {
			if (cur_thread->state == STATE_FINISHED || cur_thread->state == STATE_FAILED) {
				next = cur_thread->next;
				EndThread(cur_thread);
				cur_thread = next;
			} else {
				cur_thread = cur_thread->next;
			}
		}
	}

	return SXE_OK;
}

int
System::WaitOn (ThreadID id, Value** retval) {
	Thread* next;

	if (retval != NULL)
		*retval = NULL;

	/* check existance of valid thread */
	if (id == 0) {
		return SXE_BOUNDS;
	}

	if (cur_thread == NULL)
		cur_thread = threads;
	while (cur_thread != NULL) { /* will break if we have no threads */
		cur_thread->Run();
		if (cur_thread) {
			if (cur_thread->state == STATE_FINISHED || cur_thread->state == STATE_FAILED) {
				/* our thread? */
				if (cur_thread->id == id) {
					/* return value */
					if (retval != NULL) {
						*retval = cur_thread->ret;
					}

					next = cur_thread->next;
					EndThread(cur_thread);
					cur_thread = next;

					return SXE_OK;
				}

				next = cur_thread->next;
				EndThread(cur_thread);
				cur_thread = next;
			} else {
				cur_thread = cur_thread->next;
			}
		}

		/* end of list? restart */
		if (cur_thread == NULL) {
			cur_thread = threads;
		}
	}

	return SXE_OK;
}

int
System::NestedRun (Thread* thread, Value** retval) {
	Thread* next;

	if (retval)
		*retval = NULL;

	/* not running? invalid... */
	if (thread->state != STATE_RUNNING)
		return SXE_NOTREADY;

	/* set ready state so it can run */
	thread->state = STATE_READY;

	if (cur_thread == NULL)
		cur_thread = threads;
	while (cur_thread != NULL) { /* will break if we have no threads */
		cur_thread->Run();
		if (cur_thread) {
			if (cur_thread->state == STATE_FINISHED || cur_thread->state == STATE_FAILED) {
				/* our thread? */
				if (cur_thread == thread) {
					/* return value */
					if (retval) {
						*retval = cur_thread->ret;
					}

					next = cur_thread->next;
					EndThread(cur_thread);
					cur_thread = next;

					return SXE_INTERNAL;
				}

				next = cur_thread->next;
				EndThread(cur_thread);
				cur_thread = next;
			} else if (cur_thread->state == STATE_RETURN) {
				/* our thread? */
				if (cur_thread == thread) {
					cur_thread->state = STATE_RUNNING;
					/* return value */
					if (retval) {
						*retval = cur_thread->ret;
					}

					cur_thread = cur_thread->next;

					return SXE_OK;
				}
			} else {
				cur_thread = cur_thread->next;
			}
		}

		/* end of list? restart */
		if (cur_thread == NULL) {
			cur_thread = threads;
		}
	}

	return SXE_OK;
}
