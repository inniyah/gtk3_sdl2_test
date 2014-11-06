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
	#include <stdio.h>
	#include <string.h>
	#include <errno.h>

	#include "scriptix.h"
	#include "system.h"
	#include "parser.h"

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	__INLINE__ void parser_add_line (void);

	int sxerror (const char *);
	int sxlex (void);

	SXP_INFO *parse_info = NULL;

	extern FILE *sxin;
	int sxparse (void);

	extern const char *sx_parser_inbuf;
%}

%union {
	SXP_NODE *node;
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	sx_name_id id;
}

%token<value> TNUM TSTR
%token<name> TNAME
%token TIF TELSE TWHILE TDO TAND TOR TGTE TLTE TNE TSTATMETHOD
%token TRETURN TBREAK TLOCAL TGLOBAL TEQUALS TCONTINUE
%token TADDASSIGN TSUBASSIGN TINCREMENT TDECREMENT TSTATIC
%token TCLASS TNEW TUNTIL TNIL TRAISE TRESCUE TTRY TIN TFOR

%nonassoc TBREAK TRETURN TRAISE
%right '=' TADDASSIGN TSUBASSIGN 
%left TAND
%left TOR
%left '>' '<' TGTE TLTE
%left TNE TEQUALS TISA
%left '+' '-' TINCREMENT TDECREMENT
%left '*' '/'
%nonassoc TLENGTH TWHILE TUNTIL TDO TNEW
%left TRANGE
%nonassoc '!' CUNARY
%left '.' TSTATMETHOD '[' '(' '^'

%nonassoc TIF
%nonassoc TELSE

%type<node> node args block stmts stmt control expr
%type<value> arg_names errors
%type<id> name

%%
program:
	| program class
	| program function
	;

class:	TCLASS name { sxp_new_class (parse_info, $2, 0); } '{' cblock '}'
	| TCLASS name ':' name { sxp_new_class (parse_info, $2, $4); } '{' cblock '}'
	;

cblock:	cstmt 
	| cblock cstmt
	;

cstmt:	name '(' arg_names ')' '{' block '}' { sxp_add_method (parse_info->classes, $1, (SX_ARRAY *)$3, $6); }
	| TSTATIC name '(' arg_names ')' '{' block '}' { sxp_add_static_method (parse_info->classes, $2, (SX_ARRAY *)$4, $7); }
	;

function: name '(' arg_names ')' '{' block '}' { sxp_new_func (parse_info, $1, (SX_ARRAY *)$3, $6); }
	;

block: { $$ = NULL; }
	| stmts { $$ = $1; }
	;

stmts:	stmt { $$ = $1; }
	| stmts stmt { $$ = $1; sxp_append ($$, $2); } 
	;

stmt:	node ';' { $$ = $1; }
	| control ';' { $$ = $1; }
	| TIF '(' expr ')' stmt %prec TIF { $$ = sxp_new_if (parse_info, $3, $5, NULL); }
	| TIF '(' expr ')' stmt TELSE stmt %prec TELSE { $$ = sxp_new_if (parse_info, $3, $5, $7); }
	| TWHILE '(' expr ')' stmt { $$ = sxp_new_whil (parse_info, $3, $5, SXP_W_WD); }
	| TUNTIL '(' expr ')' stmt { $$ = sxp_new_whil (parse_info, $3, $5, SXP_W_UD); }
	| TDO stmt TWHILE '(' expr ')' ';' { $$ = sxp_new_whil (parse_info, $5, $2, SXP_W_DW); }
	| TDO stmt TUNTIL '(' expr ')' ';' { $$ = sxp_new_whil (parse_info, $5, $2, SXP_W_DU); }
	
	| TTRY '{' block '}' TRESCUE '(' errors ')' '{' block '}' { $$ = sxp_new_try (parse_info, $7, $3, $10); }

	| TFOR name TIN expr TDO stmt { $$ = sxp_new_for (parse_info, $2, $4, $6); }
	| TFOR '(' node ';' expr ';' node ')' stmt { $$ = sxp_new_cfor (parse_info, $3, $5, $7, $9); }

	| '{' block '}' { $$ = $2; }
	;

node:	{ $$ = NULL; }
	| expr { $$ = sxp_new_stmt (parse_info, $1); }
	;

control: TRETURN expr { $$ = sxp_new_retr (parse_info, $2); }
	| TRETURN { $$ = sxp_new_retr (parse_info, NULL); }
	| TBREAK { $$ = sxp_new_brak (parse_info); }
	| TCONTINUE { $$ = sxp_new_cont (parse_info); }
	| TRAISE name { $$ = sxp_new_rais (parse_info, $2, NULL); }
	| TRAISE name expr { $$ = sxp_new_rais (parse_info, $2, $3); }
	;

args: { $$ = NULL; }
	| expr { $$ = $1; }
	| args ',' expr { $$ = $1; sxp_append ($$, $3); }
	;

arg_names: { $$ = NULL; }
	| name { $$ = sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num ($1)); }
	| arg_names ',' name { $$ = sx_append (parse_info->system, $1, sx_new_num ($3)); }
	;

errors: { $$ = NULL; }
	| name name { $$ = sx_append (parse_info->system, sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num ($1)), sx_new_num ($2)); }
	| errors ',' name name { $$ = sx_append (parse_info->system, sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num ($3)), sx_new_num ($4)); }
	;

expr:	expr '+' expr { $$ = sxp_new_math (parse_info, SX_OP_ADD, $1, $3); }
	| expr '-' expr { $$ = sxp_new_math (parse_info, SX_OP_SUBTRACT, $1, $3); }
	| expr '*' expr { $$ = sxp_new_math (parse_info, SX_OP_MULTIPLY, $1, $3); }
	| expr '/' expr { $$ = sxp_new_math (parse_info, SX_OP_DIVIDE, $1, $3); }
	| '(' expr ')' { $$ = $2; }

	| '-' expr %prec CUNARY { $$ = sxp_new_nega (parse_info, $2); }

	| '!' expr { $$ = sxp_new_not (parse_info, $2); }
	| expr TAND expr { $$ = sxp_new_and (parse_info, $1, $3); }
	| expr TOR expr { $$ = sxp_new_or (parse_info, $1, $3); }

	| expr '>' expr { $$ = sxp_new_math (parse_info, SX_OP_GT, $1, $3); }
	| expr '<' expr { $$ = sxp_new_math (parse_info, SX_OP_LT, $1, $3); }
	| expr TNE expr { $$ = sxp_new_math (parse_info, SX_OP_NEQUAL, $1, $3); }
	| expr TGTE expr { $$ = sxp_new_math (parse_info, SX_OP_GTE, $1, $3); }
	| expr TLTE expr { $$ = sxp_new_math (parse_info, SX_OP_LTE, $1, $3); }
	| expr TEQUALS expr { $$ = sxp_new_math (parse_info, SX_OP_EQUAL, $1, $3); }

	| name '=' expr { $$ = sxp_new_assi (parse_info, $1, SX_SCOPE_DEF, $3); }
	| TLOCAL name '=' expr { $$ = sxp_new_assi (parse_info, $2, SX_SCOPE_LOCAL, $4); }
	| TGLOBAL name '=' expr { $$ = sxp_new_assi (parse_info, $2, SX_SCOPE_GLOBAL, $4); }
	| expr '[' expr ']' '=' expr %prec '=' { $$ = sxp_new_set (parse_info, $1, $3, $6); }
	| expr '.' name '=' expr %prec '=' { $$ = sxp_new_setm (parse_info, $1, $3, $5); }

	| name TADDASSIGN expr { $$ = sxp_new_pric (parse_info, $1, $3); }
	| name TSUBASSIGN expr { $$ = sxp_new_pric (parse_info, $1, sxp_new_nega (parse_info, $3)); }
	| name TINCREMENT { $$ = sxp_new_poic (parse_info, $1, sxp_new_data (parse_info, sx_new_num (1))); }
	| TINCREMENT name { $$ = sxp_new_pric (parse_info, $2, sxp_new_data (parse_info, sx_new_num (1))); }
	| name TDECREMENT { $$ = sxp_new_poic (parse_info, $1, sxp_new_data (parse_info, sx_new_num (-1))); }
	| TDECREMENT name { $$ = sxp_new_pric (parse_info, $2, sxp_new_data (parse_info, sx_new_num (-1))); }
	
	| expr TISA name { $$ = sxp_new_isa (parse_info, $1, $3); }
	| name '(' args ')' { $$ = sxp_new_call (parse_info, $1, $3); }

	| name TSTATMETHOD name '(' args ')' { $$ = sxp_new_smet (parse_info, $1, $3, $5); }
	| expr '.' name '(' args ')' { $$ = sxp_new_meth (parse_info, $1, $3, $5); }
	| expr '.' name { $$ = sxp_new_memb (parse_info, $1, $3); }
	| TNEW name '(' args ')' { $$ = sxp_new_newc (parse_info, $2, $4); }

	| expr '[' expr ']' { $$ = sxp_new_indx (parse_info, $1, $3); }
	| '[' args ']' { $$ = sxp_new_arry (parse_info, $2); }
	
	| TNUM { $$ = sxp_new_data (parse_info, $1);  }
	| TSTR { $$ = sxp_new_data (parse_info, $1); }
	| TNIL { $$ = sxp_new_data (parse_info, NULL); }

	| name { $$ = sxp_new_name (parse_info, $1, SX_SCOPE_DEF); }
	| TLOCAL name { $$ = sxp_new_name (parse_info, $2, SX_SCOPE_LOCAL); }
	| TGLOBAL name { $$ = sxp_new_name (parse_info, $2, SX_SCOPE_GLOBAL); }
	;

name:	TNAME { $$ = sx_name_to_id ($1); }
	;

%%

void
parser_add_line (void) {
	++ parse_info->line;
}

int
sxerror (const char *str) {
	if (parse_info->system->error_hook != NULL) {
		char buffer[512];
		snprintf (buffer, 512, "File %s, line %d: %s", parse_info->file ? SX_TOSTRING (parse_info->file)->str : "<input>", parse_info->line, str);
		parse_info->system->error_hook (buffer);
	} else {
		fprintf (stderr, "Scriptix Error: File %s, line %d: %s\n", parse_info->file ? SX_TOSTRING (parse_info->file)->str : "<input>", parse_info->line, str);
	}
	return 1;
}

int
sxwrap (void) {
	return 1;
}

int
sx_load_file (SX_SYSTEM *system, const char *file) {
	int ret, flags;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return 0;
		}
	}

	parse_info = sxp_new_info (system);
	if (parse_info == NULL) {
		if (file != NULL)
			fclose (sxin);
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}
	if (file != NULL)
		parse_info->file = sx_new_str (system, file);

	sx_parser_inbuf = NULL;
	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (!ret) {
		ret = sxp_compile (parse_info);
	}

	sxp_del_info (parse_info);

	sx_run_gc (system);

	return ret;
}

int
sx_load_string (SX_SYSTEM *system, const char *buf) {
	int ret, flags;

	if (buf == NULL) {
		return 1;
	}

	parse_info = sxp_new_info (system);
	if (parse_info == NULL) {
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}

	sxin = NULL;
	sx_parser_inbuf = buf;
	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	system->flags = flags;

	if (!ret) {
		ret = sxp_compile (parse_info);
	}

	sxp_del_info (parse_info);

	sx_run_gc (system);

	return ret;
}
