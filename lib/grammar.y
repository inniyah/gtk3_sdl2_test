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

	int sxerror (const char *);
	int sxlex (void);
	int sxparse (void);

	SXP_INFO *sxp_parser_info = NULL;
%}

%union {
	SXP_NODE *node;
	SX_VALUE value;
	sx_name_id id;
	struct _sxp_arg_list args;
}

%token<value> TNUM TSTR
%token<id> TNAME TTYPE
%token TIF TELSE TWHILE TDO TAND TOR TGTE TLTE TNE TFOREACH
%token TADDASSIGN TSUBASSIGN TINCREMENT TDECREMENT  TNEW
%token TUNTIL TNIL TRESCUE TIN TFOR TCONTINUE TYIELD

%nonassoc TBREAK TRETURN 
%right '=' TADDASSIGN TSUBASSIGN 
%left TAND TOR
%left '>' '<' TGTE TLTE TIN
%left TNE TEQUALS
%left '+' '-' TINCREMENT TDECREMENT
%left '*' '/'
%nonassoc TCAST
%nonassoc TLENGTH TWHILE TUNTIL TDO
%left TRANGE
%nonassoc '!' CUNARY
%left '.' TSTATMETHOD '[' '(' '^'

%nonassoc TIF
%nonassoc TELSE

%type<node> node args block stmts stmt control expr
%type<value> arg_names_list data
%type<id> name type
%type<args> arg_names

%%
program:
	| program function
	;

function: name '(' arg_names ')' '{' block '}' { sxp_new_func (sxp_parser_info, $1, (SX_ARRAY )$3.args, $3.varg, $6); }
	;

block: { $$ = NULL; }
	| stmts { $$ = $1; }
	;

stmts:	stmt { $$ = $1; }
	| stmts stmt { $$ = $1; sxp_append ($$, $2); } 
	;

stmt:	node ';' { $$ = $1; }
	| control ';' { $$ = $1; }
	| TIF '(' expr ')' stmt %prec TIF { $$ = sxp_new_if (sxp_parser_info, $3, $5, NULL); }
	| TIF '(' expr ')' stmt TELSE stmt %prec TELSE { $$ = sxp_new_if (sxp_parser_info, $3, $5, $7); }
	| TWHILE '(' expr ')' stmt { $$ = sxp_new_whil (sxp_parser_info, $3, $5, SXP_W_WD); }
	| TUNTIL '(' expr ')' stmt { $$ = sxp_new_whil (sxp_parser_info, $3, $5, SXP_W_UD); }
	| TDO stmt TWHILE '(' expr ')' ';' { $$ = sxp_new_whil (sxp_parser_info, $5, $2, SXP_W_DW); }
	| TDO stmt TUNTIL '(' expr ')' ';' { $$ = sxp_new_whil (sxp_parser_info, $5, $2, SXP_W_DU); }
	
	| TFOREACH '(' name TIN expr ')' stmt { $$ = sxp_new_for (sxp_parser_info, $3, $5, $7); }
	| TFOR '(' node ';' expr ';' node ')' stmt { $$ = sxp_new_cfor (sxp_parser_info, $3, $5, $7, $9); }

	| type name ';' {}
	| type name '=' expr ';' {}

	| '{' block '}' { $$ = $2; }
	;

node:	{ $$ = NULL; }
	| expr { $$ = sxp_new_stmt (sxp_parser_info, $1); }
	;

control: TRETURN expr { $$ = sxp_new_retr (sxp_parser_info, $2); }
	| TRETURN { $$ = sxp_new_retr (sxp_parser_info, NULL); }
	| TBREAK { $$ = sxp_new_brak (sxp_parser_info); }
	| TCONTINUE { $$ = sxp_new_cont (sxp_parser_info); }
	| TYIELD { $$ = sxp_new_yeld (sxp_parser_info); }
	;

args: { $$ = NULL; }
	| expr { $$ = $1; }
	| args ',' expr { $$ = $1; sxp_append ($$, $3); }
	;

arg_names: { $$.args = NULL; $$.varg = 0; }
	| arg_names_list { $$.args = $1; $$.varg = 0; }
	| arg_names_list ',' '&' name { $$.args = $1; $$.varg = $4; }
	| '&' name { $$.args = NULL; $$.varg = $2; }
	;

arg_names_list: name { $$ = sx_append (sxp_parser_info->system, sx_new_array (sxp_parser_info->system, 0, NULL), sx_new_num ($1)); }
	| arg_names_list ',' name { $$ = sx_append (sxp_parser_info->system, $1, sx_new_num ($3)); }
	;

expr:	expr '+' expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_ADD, $1, $3); }
	| expr '-' expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_SUBTRACT, $1, $3); }
	| expr '*' expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_MULTIPLY, $1, $3); }
	| expr '/' expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_DIVIDE, $1, $3); }
	| '(' expr ')' { $$ = $2; }

	| expr TIN expr { $$ = sxp_new_in (sxp_parser_info, $1, $3); }

	| '-' expr %prec CUNARY { $$ = sxp_new_nega (sxp_parser_info, $2); }

	| '!' expr { $$ = sxp_new_not (sxp_parser_info, $2); }
	| expr TAND expr { $$ = sxp_new_and (sxp_parser_info, $1, $3); }
	| expr TOR expr { $$ = sxp_new_or (sxp_parser_info, $1, $3); }

	| expr '>' expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_GT, $1, $3); }
	| expr '<' expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_LT, $1, $3); }
	| expr TNE expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_NEQUAL, $1, $3); }
	| expr TGTE expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_GTE, $1, $3); }
	| expr TLTE expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_LTE, $1, $3); }
	| expr TEQUALS expr { $$ = sxp_new_math (sxp_parser_info, SX_OP_EQUAL, $1, $3); }

	| name '=' expr { $$ = sxp_new_assi (sxp_parser_info, $1, $3); }
	| expr '[' expr ']' '=' expr %prec '=' { $$ = sxp_new_set (sxp_parser_info, $1, $3, $6); }
	| expr '.' name '=' expr %prec '=' { $$ = sxp_new_setm (sxp_parser_info, $1, $3, $5); }

	| name TADDASSIGN expr { $$ = sxp_new_pric (sxp_parser_info, $1, $3); }
	| name TSUBASSIGN expr { $$ = sxp_new_pric (sxp_parser_info, $1, sxp_new_nega (sxp_parser_info, $3)); }
	| name TINCREMENT { $$ = sxp_new_poic (sxp_parser_info, $1, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
	| TINCREMENT name { $$ = sxp_new_pric (sxp_parser_info, $2, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
	| name TDECREMENT { $$ = sxp_new_poic (sxp_parser_info, $1, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
	| TDECREMENT name { $$ = sxp_new_pric (sxp_parser_info, $2, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
	
	| '(' type ')' expr %prec TCAST { $$ = sxp_new_cast (sxp_parser_info, $4, $2); }
	| name '(' args ')' { $$ = sxp_new_call (sxp_parser_info, $1, $3); }

	| TNEW type { $$ = sxp_new_new (sxp_parser_info, $2); }
	| type '.' name '(' args ')' { $$ = sxp_new_smet (sxp_parser_info, $1, $3, $5); }
	| expr '.' name '(' args ')' { $$ = sxp_new_meth (sxp_parser_info, $1, $3, $5); }
	| expr '.' name { $$ = sxp_new_getm (sxp_parser_info, $1, $3); }

	| expr '[' expr ']' { $$ = sxp_new_indx (sxp_parser_info, $1, $3); }
	| '[' args ']' { $$ = sxp_new_arry (sxp_parser_info, $2); }

	| data { $$ = sxp_new_data (sxp_parser_info, $1); }

	| name { $$ = sxp_new_look (sxp_parser_info, $1); }
	;

	
data:	TNUM { $$ = $1;  }
	| TSTR { $$ = $1; }
	| TNIL { $$ = NULL; }
	;

name:	TNAME { $$ = $1; }
	;

type:	TTYPE { $$ = $1; }
	;

%%

int
sxerror (const char *str) {
	sxp_error (sxp_parser_info, str);
	return 1;
}

int
sxwrap (void) {
	return 1;
}

int
sxp_load_file (SX_MODULE module, const char *file) {
	int ret, flags;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return 1;
		}
	}

	sxp_parser_info = sxp_new_info (module);
	if (sxp_parser_info == NULL) {
		if (file != NULL)
			fclose (sxin);
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}
	if (file != NULL)
		sxp_parser_info->file = sx_new_str (module->system, file);

	sxp_parser_inbuf = NULL;
	flags = module->system->flags;
	module->system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	module->system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (module->system);

	return ret;
}

int
sxp_load_string (SX_MODULE module, const char *buf) {
	int ret, flags;

	if (buf == NULL) {
		return 1;
	}

	sxp_parser_info = sxp_new_info (module);
	if (sxp_parser_info == NULL) {
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}

	sxin = NULL;
	sxp_parser_inbuf = buf;
	flags = module->system->flags;
	module->system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	module->system->flags = flags;

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (module->system);

	return ret;
}
