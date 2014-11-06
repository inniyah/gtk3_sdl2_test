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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR ORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
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
	
	using namespace Scriptix;
	
	#include "parser.h"

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int yyerror (const char *);
	extern int yylex (void);
	int yyparse (void);

	Scriptix::ParserState* parser = NULL;

	#define YYERROR_VERBOSE 1
	#define SXERROR_VERBOSE 1

	/* stupid BISON fix */
	#define __attribute__(x)
%}

%union {
	ParserNode* node;
	Value* value;
	sx_name_id id;
	sx_name_id* name_list;
	struct _sxp_arg_list args;
}

%token<value> NUMBER STRING
%token<id> IDENTIFIER TYPE
%token<tag> TAG
%token IF ELSE WHILE DO AND OR TGTE TLTE TNE TFOREACH
%token TADDASSIGN TSUBASSIGN TINCREMENT TDECREMENT  TNEW
%token TUNTIL TNIL TRESCUE TIN TFOR TCONTINUE TYIELD TPUBLIC

%nonassoc TBREAK TRETURN 
%right '=' TADDASSIGN TSUBASSIGN 
%left AND OR
%left '>' '<' TGTE TLTE TIN
%left TNE TEQUALS
%left '+' '-' TINCREMENT TDECREMENT
%left '*' '/'
%nonassoc TCAST
%nonassoc TLENGTH WHILE TUNTIL DO
%left TRANGE
%nonassoc '!' CUNARY
%left '.' TSTATMETHOD '[' '(' '^'

%nonassoc IF
%nonassoc ELSE

%type<node> node args block stmts stmt expr func_args
%type<name_list> arg_names_list
%type<value> data
%type<id> name type
%type<args> arg_names

%%
program:
	| program function
	| program global
	| program error
	;

function: name '(' arg_names ')' '{' block '}' { parser->AddFunc($1, $3.args, $3.varg, $6, NULL, 0); }
	| TPUBLIC name '(' arg_names ')' '{' block '}' { parser->AddFunc($2, $4.args, $4.varg, $7, NULL, 1); }
	| name { 
		if (!parser->GetSystem()->ValidFunctionTag(IDToName ($1))) {
			yyerror ("Unregistered tag");
			YYERROR;
		}
		$<id>$ = $1;
	} name '(' arg_names ')' '{' block '}' { parser->AddFunc($3, $5.args, $5.varg, $8, IDToName($<id>2), 1); }
	;

global: name '=' data ';' { parser->SetGlobal($1, $3); }
	;

block: { $$ = NULL; }
	| stmts { $$ = $1; }
	;

stmts:	stmt { $$ = $1; }
	| stmts stmt { $$ = $1; sxp_append ($$, $2); }
	;

stmt:	node ';' { $$ = $1; }
	| TRETURN expr ';' { $$ = sxp_new_return (parser, $2); }
	| TRETURN ';' { $$ = sxp_new_return (parser, NULL); }
	| TBREAK ';' { $$ = sxp_new_break (parser); }
	| TCONTINUE ';' { $$ = sxp_new_continue (parser); }
	| TYIELD ';' { $$ = sxp_new_yield (parser); }

	| IF '(' expr ')' stmt %prec IF { $$ = sxp_new_if (parser, $3, $5, NULL); }
	| IF '(' expr ')' stmt ELSE stmt %prec ELSE { $$ = sxp_new_if (parser, $3, $5, $7); }
	| WHILE '(' expr ')' stmt { $$ = sxp_new_loop (parser, SXP_LOOP_WHILE, $3, $5); }
	| TUNTIL '(' expr ')' stmt { $$ = sxp_new_loop (parser, SXP_LOOP_UNTIL, $3, $5); }
	| DO stmt WHILE '(' expr ')' ';' { $$ = sxp_new_loop (parser, SXP_LOOP_DOWHILE, $5, $2); }
	| DO stmt TUNTIL '(' expr ')' ';' { $$ = sxp_new_loop (parser, SXP_LOOP_DOUNTIL, $5, $2); }
	| DO stmt { $$ = sxp_new_loop (parser, SXP_LOOP_FOREVER, NULL, $2); }
	
	| TFOR '(' node ';' expr ';' node ')' stmt { $$ = sxp_new_for (parser, $3, $5, $7, $9); }
	| TFOREACH '(' name TIN expr ')' stmt { $$ = sxp_new_foreach (parser, $3, $5, $7); }

	| '{' block '}' { $$ = $2; }
	;

node:	{ $$ = NULL; }
	| expr { $$ = sxp_new_statement (parser, $1); }
	;

args:	expr { $$ = $1; }
	| args ',' expr { $$ = $1; sxp_append ($$, $3); }
	;

arg_names: { $$.args = NULL; $$.varg = 0; }
	| arg_names_list { $$.args = $1; $$.varg = 0; }
	| arg_names_list ',' '&' name { $$.args = $1; $$.varg = $4; }
	| '&' name { $$.args = NULL; $$.varg = $2; }
	;

arg_names_list: name { $$ = sx_new_namelist (parser->GetSystem(), 1, $1); }
	| arg_names_list ',' name { $$ = sx_namelist_append (parser->GetSystem(), $1, $3); }
	;

func_args: '(' args ')' { $$ = $2; }
	| '(' ')' { $$ = NULL; }
	;

expr: expr '+' expr { $$ = sxp_new_math (parser, SX_OP_ADD, $1, $3); }
	| expr '-' expr { $$ = sxp_new_math (parser, SX_OP_SUBTRACT, $1, $3); }
	| expr '*' expr { $$ = sxp_new_math (parser, SX_OP_MULTIPLY, $1, $3); }
	| expr '/' expr { $$ = sxp_new_math (parser, SX_OP_DIVIDE, $1, $3); }
	| '(' expr ')' { $$ = $2; }

	| expr TIN expr { $$ = sxp_new_in (parser, $1, $3); }

	| '-' expr %prec CUNARY {
			if ($2->type == SXP_DATA && Value::IsA<Number>($2->parts.value))
				$$ = sxp_new_data(parser,Number::Create(-Number::ToInt($2->parts.value)));
			else
				$$ = sxp_new_negate (parser, $2); 
		}

	| '!' expr { $$ = sxp_new_not (parser, $2); }
	| expr AND expr { $$ = sxp_new_and (parser, $1, $3); }
	| expr OR expr { $$ = sxp_new_or (parser, $1, $3); }

	| expr '>' expr { $$ = sxp_new_math (parser, SX_OP_GT, $1, $3); }
	| expr '<' expr { $$ = sxp_new_math (parser, SX_OP_LT, $1, $3); }
	| expr TNE expr { $$ = sxp_new_math (parser, SX_OP_NEQUAL, $1, $3); }
	| expr TGTE expr { $$ = sxp_new_math (parser, SX_OP_GTE, $1, $3); }
	| expr TLTE expr { $$ = sxp_new_math (parser, SX_OP_LTE, $1, $3); }
	| expr TEQUALS expr { $$ = sxp_new_math (parser, SX_OP_EQUAL, $1, $3); }

	| name '=' expr { $$ = sxp_new_assign (parser, $1, $3); }
	| expr '[' expr ']' '=' expr %prec '=' { $$ = sxp_new_setindex (parser, $1, $3, $6); }

	| name TADDASSIGN expr { $$ = sxp_new_preinc (parser, $1, $3); }
	| name TSUBASSIGN expr { $$ = sxp_new_preinc (parser, $1, sxp_new_negate (parser, $3)); }
	| name TINCREMENT { $$ = sxp_new_postinc (parser, $1, sxp_new_data (parser, Number::Create (1))); }
	| TINCREMENT name { $$ = sxp_new_preinc (parser, $2, sxp_new_data (parser, Number::Create (1))); }
	| name TDECREMENT { $$ = sxp_new_postinc (parser, $1, sxp_new_data (parser, Number::Create (-1))); }
	| TDECREMENT name { $$ = sxp_new_preinc (parser, $2, sxp_new_data (parser, Number::Create (-1))); }
	
	| '(' type ')' expr %prec TCAST { $$ = sxp_new_cast (parser, $2, $4); }
	| type '(' expr ')' %prec TCAST { $$ = sxp_new_cast (parser, $1, $3); }

	| expr func_args { $$ = sxp_new_invoke (parser, $1, $2); }

	| TNEW type { $$ = sxp_new_new (parser, $2); }
	| expr '.' name func_args { $$ = sxp_new_method (parser, $1, $3, $4); }
	| type '.' name func_args { $$ = sxp_new_smethod (parser, $1, $3, $4); }
	| expr ':' name '=' expr { $$ = sxp_new_set_member(parser, $1, $3, $5); }
	| expr ':' name { $$ = sxp_new_get_member (parser, $1, $3); }

	| expr '[' expr ']' { $$ = sxp_new_getindex (parser, $1, $3); }
	| '[' args ']' { $$ = sxp_new_array (parser, $2); }

	| data { $$ = sxp_new_data (parser, $1); }

	| name { $$ = sxp_new_lookup (parser, $1); }

	| error { $$ = sxp_new_data (parser, NULL); }
	;

	
data:	NUMBER { $$ = $1;  }
	| STRING { $$ = $1; }
	| TNIL { $$ = NULL; }
	;

name:	IDENTIFIER { $$ = $1; }
	;

type:	TYPE { $$ = $1; }
	;

%%

int
yyerror (const char *str) {
	parser->Error(str);
	return 1;
}

extern "C"
int
yywrap (void) {
	return 1;
}

int
Scriptix::System::LoadFile(const char *file) {
	int ret;

	if (file == NULL) {
		yyin = stdin;
	} else {
		yyin = fopen (file, "r");
		if (yyin == NULL) {
			std::cerr << "Could not open '" << file << "'" << std::endl;
			return 1;
		}
	}

	parser = new ParserState(this);
	if (parser == NULL) {
		if (file != NULL)
			fclose (yyin);
		std::cerr << "Failed to create Compiler context" << std::endl;
		return 1;
	}
	if (file != NULL)
		parser->SetFile(file);

	sxp_parser_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = -1;

	if (file != NULL) {
		fclose (yyin);
	}

	if (!ret) {
		ret = parser->Compile();
	}

	delete parser;

	return ret;
}

int
Scriptix::System::LoadString(const char *buf) {
	int ret;

	if (buf == NULL) {
		return 1;
	}

	parser = new ParserState(this);
	if (parser == NULL) {
		std::cerr << "Failed to create Compiler context" << std::endl;
		return 1;
	}

	yyin = NULL;
	sxp_parser_inbuf = buf;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = -1;

	if (!ret) {
		ret = parser->Compile();
	}

	delete parser;

	return ret;
}
