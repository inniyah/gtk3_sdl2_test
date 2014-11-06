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
	#include <ctype.h>

	#include "scriptix.h"
	#include "y.tab.h"

	#define LEX_NAME(name,value) if (!strcmp (yytext, name)) { return value; } else 

	extern SYSTEM *parse_system;
	extern unsigned int parse_lineno;

	__INLINE__ void sxll_to_lower (char *buf);
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
'[^\']*' { yytext[strlen (yytext) - 1] = '\0'; sxlval.value = sx_new_str (parse_system, yytext + 1); return TSTR; }
"[^\"]*" { yytext[strlen (yytext) - 1] = '\0'; sxlval.value = sx_new_str (parse_system, yytext + 1); return TSTR; }
[a-zA-Z_][a-zA-Z0-9_]* { 
		sxll_to_lower (yytext);
		LEX_NAME("if", TIF)
		LEX_NAME("then", TTHEN)
		LEX_NAME("else", TELSE)
		LEX_NAME("end", TEND)
		LEX_NAME("while", TWHILE)
		LEX_NAME("do", TDO)
		LEX_NAME("or", TOR)
		LEX_NAME("and", TAND)
		LEX_NAME("return", TRETURN)
		LEX_NAME("break", TBREAK)
		LEX_NAME("function", TFUNC)
		LEX_NAME("local", TLOCAL)
		LEX_NAME("global", TGLOBAL)
		LEX_NAME("length", TLENGTH)
		LEX_NAME("thread", TTHREAD)
		LEX_NAME("class", TCLASS)
		LEX_NAME("new", TNEW)
		LEX_NAME("type", TTYPE)
		LEX_NAME("isa", TISA)
		LEX_NAME("nil", TNIL)
		LEX_NAME("raise", TRAISE)
		LEX_NAME("rescue", TRESCUE)
		LEX_NAME("try", TTRY)
		LEX_NAME("in", TIN)
		LEX_NAME("for", TFOR)
		LEX_NAME("step", TSTEP)
		{
			strncpy (sxlval.name, yytext, SX_MAX_NAME);
			sxlval.name[SX_MAX_NAME] = 0;
			return TNAME;
		}
	}
[0-9]+ { sxlval.value = sx_new_num (atoi (yytext)); return TNUM; }
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
void
sxll_to_lower (char *buf) {
	while (*buf != '\0') {
		*buf = tolower (*buf);
		++ buf;
	}
}
