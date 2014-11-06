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
	#include <errno.h>

	#include "scriptix.h"
	#include "y.tab.h"

	#define SX_LEX_STR_MAX 1024

	#define LEX_NAME(name,value) if (!strcmp (yytext, name)) { return value; } else 

	char sx_lex_str[SX_LEX_STR_MAX + 1];
	unsigned int sx_lex_str_i;
	__INLINE__ void sx_lex_str_escape (char esc);
	__INLINE__ void sx_lex_str_push (char c);

	extern SX_SYSTEM *parse_system;
	extern __INLINE__ void parser_add_line (void);

	__INLINE__ void sxll_to_lower (char *buf);

	#define YY_INPUT(b,r,m) sx_parser_input((b),&(r),(m))

	char *sx_parser_inbuf = NULL;
	void sx_parser_input (char *buf, int *result, int max);
%}

%x BCOMMENT
%x LCOMMENT
%x SSTRING
%x DSTRING

%%

<BCOMMENT>[^*\n]+ { /* IGNORE */ }
<BCOMMENT>[\n] { parser_add_line (); }
<BCOMMENT>"*"+[^*/\n]	{ /* IGNORE */ }
<BCOMMENT>"*/" { BEGIN INITIAL; }

<LCOMMENT>[^\n]+ { /* IGNORE */ }
<LCOMMENT>[\n] { parser_add_line (); BEGIN INITIAL; }

<SSTRING,DSTRING>\\. { sx_lex_str_escape (yytext[1]); }
<SSTRING>[^'\n] { sx_lex_str_push (yytext[0]); }
<DSTRING>[^"\n] { sx_lex_str_push (yytext[0]); }
<SSTRING,DSTRING>[\n] { parser_add_line (); sx_lex_str_push ('\n'); }
<DSTRING>\" { BEGIN INITIAL; sx_lex_str[sx_lex_str_i] = 0; sxlval.value = sx_new_str (parse_system, sx_lex_str); return TSTR; } 
<SSTRING>' { BEGIN INITIAL; sx_lex_str[sx_lex_str_i] = 0; sxlval.value = sx_new_str (parse_system, sx_lex_str); return TSTR; } 

[ \t]+ { /* IGNORE */ }
"/*"  { BEGIN BCOMMENT; }
# { BEGIN LCOMMENT; }
[\n] { parser_add_line (); return TSEP; }
; { return TSEP; } 
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
		LEX_NAME("class", TCLASS)
		LEX_NAME("new", TNEW)
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
' { sx_lex_str_i = 0; BEGIN SSTRING; }
\" { sx_lex_str_i = 0; BEGIN DSTRING; }
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

void
sx_lex_str_escape (char esc) {
	if (esc == 'n') {
		sx_lex_str_push ('\n');
	} else if (esc == 'r') {
		sx_lex_str_push ('\r');
	} else if (esc == 't') {
		sx_lex_str_push ('\t');
	} else if (esc == 'b') {
		sx_lex_str_push ('\b');
	} else {
		sx_lex_str_push (esc);
	}
}


void
sx_lex_str_push (char c) {
	sx_lex_str[sx_lex_str_i] = c;
	if (sx_lex_str_i < SX_LEX_STR_MAX) 
		++ sx_lex_str_i;
}
	
void
sx_parser_input (char *buf, int *result, int max_size) {
	if (sx_parser_inbuf != NULL) {
		int len = strlen (sx_parser_inbuf);
		if (max_size > len) {
			max_size = len;
		}

		memcpy (buf, sx_parser_inbuf, max_size);
		sx_parser_inbuf += max_size;

		*result = max_size;
	} else {
		errno = 0;
		while ((*result = fread (buf, 1, max_size, sxin)) == 0 && ferror (sxin)) {
			if (errno != EINTR) {
				break;
			}
			errno = 0;
			clearerr (sxin);
		}
	}
}
