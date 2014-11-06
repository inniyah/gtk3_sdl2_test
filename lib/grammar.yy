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
	#include <gc/gc.h>

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

	#define malloc GC_MALLOC_UNCOLLECTABLE
	#define free GC_FREE
%}

%union {
	ParserNode* node;
	Value* value;
	Type* type;
	NameID id;
	NameList* names;
	struct ParserArgList args;
}

%token<value> NUMBER STRING
%token<id> IDENTIFIER
%token<type> TYPE
%token<tag> TAG
%token IF ELSE WHILE DO AND OR TGTE TLTE TNE TFOREACH TEXTEND
%token TADDASSIGN TSUBASSIGN TINCREMENT TDECREMENT TNEW TSTATIC
%token TUNTIL TNIL TRESCUE TIN TFOR TCONTINUE TYIELD TPUBLIC
%token TMULASSIGN TDIVASSIGN

%nonassoc TBREAK TRETURN 
%right '=' TADDASSIGN TSUBASSIGN TMULASSIGN TDIVASSIGN
%left AND OR
%left '>' '<' TGTE TLTE TIN
%left TNE TEQUALS
%left '+' '-' TINCREMENT TDECREMENT '@'
%left '*' '/'
%nonassoc TLENGTH WHILE TUNTIL DO
%nonassoc '!' CUNARY
%left TCAST
%left '.' ':' '[' '^' TNEW
%left '('

%nonassoc IF
%nonassoc ELSE

%type<node> node args block stmts stmt expr func_args lval
%type<names> arg_names_list
%type<value> data
%type<id> name
%type<type> type
%type<args> arg_names

%%
program:
	| program function
	| program global
	| program error
	| program extend
	| program new
	;

function: name '(' arg_names ')' '{' block '}' { parser->AddFunc($1, ($3.args ? *$3.args : NameList()), $3.varg, $6, 0, false); }
	| TPUBLIC name '(' arg_names ')' '{' block '}' { parser->AddFunc($2, ($4.args ? *$4.args : NameList()), $4.varg, $7, 0, true); }
	| name name { 
		if (!parser->GetSystem()->ValidFunctionTag($1)) {
			yyerror ("Error: Unrecognized function tag");
			YYERROR;
		}
		$<id>1 = $1;
		$<id>2 = $2;
	} '(' arg_names ')' '{' block '}' { parser->AddFunc($<id>2, ($5.args ? *$5.args : NameList()), $5.varg, $8, $<id>1, false); }
	;

global: name '=' data ';' { parser->SetGlobal($1, $3); }
	;

extend: TEXTEND type { if (!parser->AddExtend ($2)) YYERROR; } '{' extend_methods '}'
	;

extend_method: name '(' arg_names ')' '{' block '}' { parser->AddExtendFunc($1, ($3.args ? *$3.args : NameList()), $3.varg, $6, false); }
	| TSTATIC name '(' arg_names ')' '{' block '}' { parser->AddExtendFunc($2, ($4.args ? *$4.args : NameList()), $4.varg, $7, true); }
	;

extend_methods: extend_method
	| extend_methods extend_method
	;

construct_method:
	| TNEW '(' arg_names ')' '{' block '}' { parser->AddExtendFunc(NameToID("new"), ($3.args ? *$3.args : NameList()), $3.varg, $6, false); }
	;

new: TNEW name { if (!parser->AddType ($2, parser->GetSystem()->GetStructType())) YYERROR; } '{' construct_method extend_methods '}'
	| TNEW name ':' type { if (!parser->AddType ($2, $4)) YYERROR; } '{' construct_method extend_methods '}'
	;

block: { $$ = NULL; }
	| stmts { $$ = $1; }
	;

stmts:	stmt { $$ = $1; }
	| stmts stmt { if ($1 != NULL) { $$ = $1; $$->Append($2); } else { $$ = $2; } }
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

	| error { $$ = NULL; }
	;

node:	{ $$ = NULL; }
	| expr { $$ = sxp_new_statement (parser, $1); }
	;

args:	expr { $$ = $1; }
	| args ',' expr { $$ = $1; $$->Append($3); }
	;

arg_names: { $$.args = NULL; $$.varg = 0; }
	| arg_names_list { $$.args = $1; $$.varg = 0; }
	| arg_names_list ',' '&' name { $$.args = $1; $$.varg = $4; }
	| '&' name { $$.args = NULL; $$.varg = $2; }
	;

arg_names_list: name { $$ = new NameList(); $$->push_back($1); }
	| arg_names_list ',' name { $$->push_back($3); }
	;

func_args: '(' args ')' { $$ = $2; }
	| '(' ')' { $$ = NULL; }
	;

lval: name { $$ = sxp_new_lookup(parser, $1); }
	| expr '[' expr ']' { $$ = sxp_new_getindex(parser, $1, $3); }
	| expr '.' name { $$ = sxp_new_get_member(parser, $1, $3); }
	| '.' name { $$ = sxp_new_get_member(parser, sxp_new_lookup(parser, NameToID("self")), $2); }
	;

expr: expr '+' expr { $$ = sxp_new_math (parser, OP_ADD, $1, $3); }
	| expr '-' expr { $$ = sxp_new_math (parser, OP_SUBTRACT, $1, $3); }
	| expr '*' expr { $$ = sxp_new_math (parser, OP_MULTIPLY, $1, $3); }
	| expr '/' expr { $$ = sxp_new_math (parser, OP_DIVIDE, $1, $3); }
	| expr '@' expr { yyerror("Warning: use of '@' concatenation operator is deprecrated; please use '+'"); $$ = sxp_new_math (parser, OP_ADD, $1, $3); }
	| '(' expr ')' { $$ = $2; }

	| expr TIN expr { $$ = sxp_new_in (parser, $1, $3); }

	| '-' expr %prec CUNARY {
			if ($2->type == SXP_DATA && Value::IsA<Number>(parser->system, $2->parts.value))
				$$ = sxp_new_data(parser,Number::Create(-Number::ToInt($2->parts.value)));
			else
				$$ = sxp_new_negate (parser, $2); 
		}

	| '!' expr { $$ = sxp_new_not (parser, $2); }
	| expr AND expr { $$ = sxp_new_and (parser, $1, $3); }
	| expr OR expr { $$ = sxp_new_or (parser, $1, $3); }

	| expr '>' expr { $$ = sxp_new_math (parser, OP_GT, $1, $3); }
	| expr '<' expr { $$ = sxp_new_math (parser, OP_LT, $1, $3); }
	| expr TNE expr { $$ = sxp_new_math (parser, OP_NEQUAL, $1, $3); }
	| expr TGTE expr { $$ = sxp_new_math (parser, OP_GTE, $1, $3); }
	| expr TLTE expr { $$ = sxp_new_math (parser, OP_LTE, $1, $3); }
	| expr TEQUALS expr { $$ = sxp_new_math (parser, OP_EQUAL, $1, $3); }

	| name '=' expr { $$ = sxp_new_assign (parser, $1, $3); }
	| expr '[' expr ']' '=' expr %prec '=' { $$ = sxp_new_setindex (parser, $1, $3, $6); }
	| expr '.' name '=' expr { $$ = sxp_new_set_member(parser, $1, $3, $5); }
	| '.' name '=' expr { $$ = sxp_new_set_member(parser, sxp_new_lookup(parser, NameToID("self")), $2, $4); }

	| expr TADDASSIGN expr { $$ = sxp_new_preop (parser, $1, OP_ADD, $3); }
	| expr TSUBASSIGN expr { $$ = sxp_new_preop (parser, $1, OP_SUBTRACT, $3); }
	| expr TMULASSIGN expr { $$ = sxp_new_preop (parser, $1, OP_MULTIPLY, $3); }
	| expr TDIVASSIGN expr { $$ = sxp_new_preop (parser, $1, OP_DIVIDE, $3); }
	| expr TINCREMENT { $$ = sxp_new_postop (parser, $1, OP_ADD, sxp_new_data (parser, Number::Create (1))); }
	| TINCREMENT expr { $$ = sxp_new_preop (parser, $2, OP_ADD, sxp_new_data (parser, Number::Create (1))); }
	| expr TDECREMENT { $$ = sxp_new_postop (parser, $1, OP_SUBTRACT, sxp_new_data (parser, Number::Create (1))); }
	| TDECREMENT expr { $$ = sxp_new_preop (parser, $2, OP_SUBTRACT, sxp_new_data (parser, Number::Create (1))); }
	
	| '(' type ')' expr %prec TCAST { yyerror("Warning: use of '(type)expr' casting is deprecrated; please use 'type(expr)'"); $$ = sxp_new_cast (parser, $2, $4); }
	| type '(' expr ')' %prec TCAST { $$ = sxp_new_cast (parser, $1, $3); }

	| name func_args { $$ = sxp_new_invoke (parser, sxp_new_lookup(parser, $1), $2); }
	| '(' expr ')' func_args { $$ = sxp_new_invoke (parser, $2, $4); }

	| TNEW type { $$ = sxp_new_new (parser, $2, NULL, false); }
	| TNEW type func_args { $$ = sxp_new_new (parser, $2, $3, true); }
	| expr '.' name func_args { $$ = sxp_new_method (parser, $1, $3, $4); }
	| '.' name func_args { $$ = sxp_new_method (parser, sxp_new_lookup(parser, NameToID("self")), $2, $3); }
	| type '.' name func_args { $$ = sxp_new_smethod (parser, $1, $3, $4); }

	| '[' args ']' { $$ = sxp_new_array (parser, $2); }
	| '[' ']' { $$ = sxp_new_array (parser, NULL); }

	| data { $$ = sxp_new_data (parser, $1); }

	| lval { $$ = $1; }
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
Scriptix::System::LoadFile(const std::string& file, SecurityLevel access) {
	int ret;

	if (file.empty()) {
		yyin = stdin;
	} else {
		yyin = fopen (file.c_str(), "rt");
		if (yyin == NULL) {
			std::cerr << "Could not open '" << file << "'" << std::endl;
			return SXE_INVALID;
		}
	}

	parser = new ParserState(this);
	if (parser == NULL) {
		if (!file.empty())
			fclose (yyin);
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	if (!file.empty())
		parser->SetFile(file);
	parser->SetAccess(access);

	sxp_parser_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!file.empty())
		fclose (yyin);

	if (!ret)
		ret = parser->Compile();

	return ret;
}

int
Scriptix::System::LoadString(const std::string& buf, const std::string& name, size_t lineno, SecurityLevel access) {
	int ret;

	if (buf.empty())
		return SXE_INVALID;

	parser = new ParserState(this);
	if (parser == NULL) {
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	parser->SetAccess(access);
	parser->SetFile(name);
	parser->SetLine(lineno);

	yyin = NULL;
	sxp_parser_inbuf = buf.c_str();

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!ret)
		ret = parser->Compile();

	return ret;
}
