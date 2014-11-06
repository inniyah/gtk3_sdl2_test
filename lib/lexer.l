/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, AwesomePlay Productions, Inc.
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

%{
	#include <stdlib.h>
	#include <string.h>

	#include "scriptix.h"
	#include "y.tab.h"

	extern SYSTEM *parse_system;
	extern unsigned int parse_lineno;
%}

%s bcomment
%s lcomment

%%

<bcomment>[^*\n]+ { /* IGNORE */ }
<bcomment>[\n] { parse_lineno ++; }
<bcomment>"*"+[^*/\n]	{ /* IGNORE */ }
<bcomment>"*/" { BEGIN INITIAL; }

<lcomment>[^\n]+ { /* IGNORE */ }
<lcomment>[\n] { parse_lineno ++; BEGIN INITIAL; }

[ \t]+ { /* IGNORE */ }
"/*"  { BEGIN bcomment; }
# { BEGIN lcomment; }
[\n] { parse_lineno ++; return TSEP; }
; { return TSEP; } 
'[^\']*' { yytext[strlen (yytext) - 1] = '\0'; sxlval.value = new_str (parse_system, yytext + 1); return TSTR; }
"[^\"]*" { yytext[strlen (yytext) - 1] = '\0'; sxlval.value = new_str (parse_system, yytext + 1); return TSTR; }
[a-zA-Z_][a-zA-Z0-9_]* { 
		if (!strcasecmp (yytext, "if")) {
			return TIF;
		} else if (!strcasecmp (yytext, "then")) {
			return TTHEN;
		} else if (!strcasecmp (yytext, "else")) {
			return TELSE;
		} else if (!strcasecmp (yytext, "end")) {
			return TEND;
		} else if (!strcasecmp (yytext, "while")) {
			return TWHILE;
		} else if (!strcasecmp (yytext, "do")) {
			return TDO;
		} else if (!strcasecmp (yytext, "or")) {
			return TOR;
		} else if (!strcasecmp (yytext, "and")) {
			return TAND;
		} else if (!strcasecmp (yytext, "return")) {
			return TRETURN;
		} else if (!strcasecmp (yytext, "break")) {
			return TBREAK;
		} else if (!strcasecmp (yytext, "function")) {
			return TFUNC;
		} else if (!strcasecmp (yytext, "local")) {
			return TLOCAL;
		} else if (!strcasecmp (yytext, "global")) {
			return TGLOBAL;
		} else if (!strcasecmp (yytext, "length")) {
			return TLENGTH;
		} else if (!strcasecmp (yytext, "thread")) {
			return TTHREAD;
		} else if (!strcasecmp (yytext, "class")) {
			return TCLASS;
		} else if (!strcasecmp (yytext, "new")) {
			return TNEW;
		} else if (!strcasecmp (yytext, "type")) {
			return TTYPE;
		} else if (!strcasecmp (yytext, "isa")) {
			return TISA;
		} else if (!strcasecmp (yytext, "nil")) {
			return TNIL;
		} else if (!strcasecmp (yytext, "raise")) {
			return TRAISE;
		} else if (!strcasecmp (yytext, "rescue")) {
			return TRESCUE;
		} else if (!strcasecmp (yytext, "try")) {
			return TTRY;
		} else if (!strcasecmp (yytext, "in")) {
			return TIN;
		} else if (!strcasecmp (yytext, "for")) {
			return TFOR;
		} else {
			sxlval.value = new_str (parse_system, yytext);
			return TNAME;
		}
	}
[0-9]+ { sxlval.value = new_num (atoi (yytext)); return TNUM; }
[>]= { return TGTE; }
[<]= { return TLTE; }
== { return TEQUALS; }
"+=" { return TADDASSIGN; }
-= { return TSUBASSIGN; }
"++" { return TINCREMENT; }
"--" { return TDECREMENT; }
"->" { return TMETHOD; }
!= { return TNE; }
".." { return TRANGE; }
. { return yytext[0]; }
<<EOF>> { return 0; }

%%
