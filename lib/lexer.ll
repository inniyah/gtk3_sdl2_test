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
	using namespace Scriptix;
	#include "parser.h"
	#include "grammar.hh"

	#define SX_LEX_STR_MAX 1024

	#define LEX_NAME(name,value) if (!strcmp (yytext, name)) { return value; } else 

	static char sx_lex_str[SX_LEX_STR_MAX + 1];
	static unsigned int sx_lex_str_i;
	static void sx_lex_str_escape (char esc);
	static void sx_lex_str_push (char c);

	#define YY_INPUT(b,r,m) sxp_parser_input((b),&(r),(m))

	const char *sxp_parser_inbuf = NULL;
	static void sxp_parser_input (char *buf, int *result, int max);
%}

%x BCOMMENT
%x LCOMMENT
%x SSTRING
%x DSTRING

%%

<BCOMMENT>[^*\n]+ { /* IGNORE */ }
<BCOMMENT>[\n] { parser->LineIncr(); }
<BCOMMENT>"*"+[^*/\n]	{ /* IGNORE */ }
<BCOMMENT>"*/" { BEGIN INITIAL; }

<LCOMMENT>[^\n]+ { /* IGNORE */ }
<LCOMMENT>[\n] { parser->LineIncr(); BEGIN INITIAL; }

<SSTRING,DSTRING>\\. { sx_lex_str_escape (yytext[1]); }
<SSTRING>[^'\n] { sx_lex_str_push (yytext[0]); }
<DSTRING>[^"\n] { sx_lex_str_push (yytext[0]); }
<SSTRING,DSTRING>[\n] { parser->LineIncr(); sx_lex_str_push ('\n'); }
<DSTRING>\" { BEGIN INITIAL; sx_lex_str[sx_lex_str_i] = 0; yylval.value = new String(parser->GetSystem(), sx_lex_str); return STRING; } 
<SSTRING>' { BEGIN INITIAL; sx_lex_str[sx_lex_str_i] = 0; yylval.value = new String(parser->GetSystem(), sx_lex_str); return STRING; } 

[ \t]+ { /* IGNORE */ }
"/*"  { BEGIN BCOMMENT; }
"//"  { BEGIN LCOMMENT; }
# { BEGIN LCOMMENT; }
[\n] { parser->LineIncr(); }
[a-zA-Z_][a-zA-Z0-9_]* { 
		LEX_NAME("if", IF)
		LEX_NAME("else", ELSE)
		LEX_NAME("while", WHILE)
		LEX_NAME("do", DO)
		LEX_NAME("until", TUNTIL)
		LEX_NAME("return", TRETURN)
		LEX_NAME("break", TBREAK)
		LEX_NAME("nil", TNIL)
		LEX_NAME("in", TIN)
		LEX_NAME("for", TFOR)
		LEX_NAME("foreach", TFOREACH)
		LEX_NAME("continue", TCONTINUE)
		LEX_NAME("yield", TYIELD)
		LEX_NAME("new", TNEW)
		LEX_NAME("public", TPUBLIC)
		LEX_NAME("extend", TEXTEND)
		{
			yylval.id = NameToID (yytext);
			if (parser->GetSystem()->GetType(yylval.id) != NULL) {
				return TYPE;
			} else {
				return IDENTIFIER;
			}
		}
	}
[0-9]+ { yylval.value = Number::Create (atoi (yytext)); return NUMBER; }
[>]= { return TGTE; }
[<]= { return TLTE; }
== { return TEQUALS; }
"+=" { return TADDASSIGN; }
-= { return TSUBASSIGN; }
"++" { return TINCREMENT; }
"--" { return TDECREMENT; }
"||" { return OR; }
"&&" { return AND; }
!= { return TNE; }
' { sx_lex_str_i = 0; BEGIN SSTRING; }
\" { sx_lex_str_i = 0; BEGIN DSTRING; }
. { return yytext[0]; }
<<EOF>> { return 0; }

%%
static
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
	} else if (esc == '0') {
		sx_lex_str_push (0);
	} else {
		sx_lex_str_push (esc);
	}
}

static
void
sx_lex_str_push (char c) {
	sx_lex_str[sx_lex_str_i] = c;
	if (sx_lex_str_i < SX_LEX_STR_MAX) 
		++ sx_lex_str_i;
}
	
static
void
sxp_parser_input (char *buf, int *result, int max_size) {
	if (sxp_parser_inbuf != NULL) {
		int len = strlen (sxp_parser_inbuf);
		if (max_size > len) {
			max_size = len;
		}

		memcpy (buf, sxp_parser_inbuf, max_size);
		sxp_parser_inbuf += max_size;

		*result = max_size;
	} else {
		errno = 0;
		while ((*result = fread (buf, 1, max_size, yyin)) == 0 && ferror (yyin)) {
			if (errno != EINTR) {
				break;
			}
			errno = 0;
			clearerr (yyin);
		}
	}
}
