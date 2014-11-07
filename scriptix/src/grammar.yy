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
	#include <cstdlib>
	#include <cstdio>
	#include <cstring>
	#include <errno.h>
	#include <gc/gc.h>

	#include "scriptix.h"
	#include "system.h"
	#include "compiler.h"

	using namespace Scriptix;
	using namespace Scriptix::Compiler;

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int yyerror (const char *);
	extern int yylex (void);
	int yyparse (void);

	Scriptix::Compiler::Compiler* compiler = NULL;

	#define YYERROR_VERBOSE 1
	#define SXERROR_VERBOSE 1

	/* stupid BISON fix */
	#define __attribute__(x)

	#define malloc(size) GC_MALLOC(size)
	#define realloc(ptr,size) GC_REALLOC(ptr,size)
	#define free(ptr)
%}

%union {
	CompilerNode* node;
	Value* value;
	TypeInfo* type;
	NameID id;
	NameList* names;
	struct CompilerArgList args;
}

%token<value> NUMBER
%token<value> STRING
%token<id> IDENTIFIER
%token<type> TYPE
%token IF "if"
%token ELSE "else"
%token WHILE "while"
%token FOREVER "forever"
%token DO "do"
%token AND "&&"
%token OR "||"
%token TGTE ">="
%token TLTE "<="
%token TNE "!="
%token TFOREACH "foreach"
%token TADDASSIGN "+="
%token TSUBASSIGN "-="
%token TINCREMENT "++"
%token TDECREMENT "--"
%token TNEW "new"
%token TUNTIL "until"
%token TNIL "nil"
%token TIN "in"
%token TFOR "for"
%token TCONTINUE "continue"
%token TYIELD "yield"
%token TPUBLIC "public"
%token TMULASSIGN "*="
%token TDIVASSIGN "/="
%token TVAR "var"
%token TDEREFERENCE "."
%token TCONCAT "::"
%token TBREAK "break"
%token TRETURN "return"

%nonassoc TBREAK TRETURN 
%right '=' TADDASSIGN TSUBASSIGN TMULASSIGN TDIVASSIGN
%left AND OR
%left '>' '<' TGTE TLTE TIN
%left TNE TEQUALS
%left '+' '-' TCONCAT
%left '*' '/'
%nonassoc WHILE TUNTIL DO
%nonassoc '!' CUNARY
%nonassoc TINCREMENT TDECREMENT
%left TCAST
%left TDEREFERENCE ':' '[' TNEW
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
	| program new
	;

function: name '(' arg_names ')' '{' block '}' { compiler->AddFunc($1, ($3.args ? *$3.args : NameList()), $3.varg, $6, false); }
	| TPUBLIC name '(' arg_names ')' '{' block '}' { compiler->AddFunc($2, ($4.args ? *$4.args : NameList()), $4.varg, $7, true); }
	;

global: TVAR name '=' data ';' { compiler->SetGlobal($2, $4); }
	| TVAR name ';' { compiler->SetGlobal($2, NULL); }
	;

method: name '(' arg_names ')' '{' block '}' { compiler->AddMethod($1, ($3.args ? *$3.args : NameList()), $3.varg, $6); }
	| TNEW '(' arg_names ')' '{' block '}' { compiler->AddMethod(NameToID("new"), ($3.args ? *$3.args : NameList()), $3.varg, $6); }
	;

methods: method
	| methods method
	;

new: TNEW name { if (!compiler->AddType ($2, GetSystem()->GetScriptClassType())) YYERROR; } '{' methods '}'
	| TNEW name ':' type { if (!compiler->AddType ($2, $4)) YYERROR; } '{' methods '}'
	;

block: { $$ = NULL; }
	| stmts { $$ = $1; }
	;

stmts:	stmt { $$ = $1; }
	| stmts stmt { if ($1 != NULL) { $$ = $1; $$->Append($2); } else { $$ = $2; } }
	;

stmt:	node ';' { $$ = $1; }
	| TRETURN expr ';' { $$ = sxp_new_return (compiler, $2); }
	| TRETURN ';' { $$ = sxp_new_return (compiler, NULL); }
	| TBREAK ';' { $$ = sxp_new_break (compiler); }
	| TCONTINUE ';' { $$ = sxp_new_continue (compiler); }
	| TYIELD ';' { $$ = sxp_new_yield (compiler); }

	| IF '(' expr ')' stmt %prec IF { $$ = sxp_new_if (compiler, $3, $5, NULL); }
	| IF '(' expr ')' stmt ELSE stmt %prec ELSE { $$ = sxp_new_if (compiler, $3, $5, $7); }
	| WHILE '(' expr ')' stmt { $$ = sxp_new_loop (compiler, SXP_LOOP_WHILE, $3, $5); }
	| TUNTIL '(' expr ')' stmt { $$ = sxp_new_loop (compiler, SXP_LOOP_UNTIL, $3, $5); }
	| DO stmt WHILE '(' expr ')' ';' { $$ = sxp_new_loop (compiler, SXP_LOOP_DOWHILE, $5, $2); }
	| DO stmt TUNTIL '(' expr ')' ';' { $$ = sxp_new_loop (compiler, SXP_LOOP_DOUNTIL, $5, $2); }
	| DO stmt FOREVER ';' { $$ = sxp_new_loop (compiler, SXP_LOOP_FOREVER, NULL, $2); }
	
	| TFOR '(' node ';' expr ';' node ')' stmt { $$ = sxp_new_for (compiler, $3, $5, $7, $9); }
/*	| TFOREACH '(' name TIN expr ')' stmt { $$ = sxp_new_foreach (compiler, $3, $5, $7); } */
	| TFOREACH '(' TVAR name TIN expr ')' stmt { $$ = sxp_new_foreach (compiler, $4, $6, $8); }

	| '{' block '}' { $$ = $2; }

	| error { $$ = NULL; }
	;

node:	{ $$ = NULL; }
	| expr { $$ = sxp_new_statement (compiler, $1); }
	;

args:	expr { $$ = $1; }
	| args ',' expr { $$ = $1; $$->Append($3); }
	;

arg_names: { $$.args = NULL; $$.varg = 0; }
	| arg_names_list { $$.args = $1; $$.varg = 0; }
	| arg_names_list ',' '&' name { $$.args = $1; $$.varg = $4; }
	| '&' name { $$.args = NULL; $$.varg = $2; }
	;

arg_names_list: name { $$ = new (UseGC) NameList(); $$->push_back($1); }
	| arg_names_list ',' name { $$->push_back($3); }
	;

func_args: args { $$ = $1; }
	| { $$ = NULL; }
	;

lval: name { $$ = sxp_new_lookup(compiler, $1); }
	| expr '[' expr ']' { $$ = sxp_new_getindex(compiler, $1, $3); }
	| expr TDEREFERENCE name { $$ = sxp_new_get_member(compiler, $1, $3); }
	;

expr: expr '+' expr { $$ = sxp_new_math (compiler, OP_ADD, $1, $3); }
	| expr '-' expr { $$ = sxp_new_math (compiler, OP_SUBTRACT, $1, $3); }
	| expr '*' expr { $$ = sxp_new_math (compiler, OP_MULTIPLY, $1, $3); }
	| expr '/' expr { $$ = sxp_new_math (compiler, OP_DIVIDE, $1, $3); }
	| expr TCONCAT expr { $$ = sxp_new_concat (compiler, $1, $3); }
	| '(' expr ')' { $$ = $2; }

	| expr TIN expr { $$ = sxp_new_in (compiler, $1, $3); }

	| '-' expr %prec CUNARY {
			if ($2->type == SXP_DATA && Value::IsA<Number>($2->parts.value))
				$$ = sxp_new_data(compiler,Number::Create(-Number::ToInt($2->parts.value)));
			else
				$$ = sxp_new_negate (compiler, $2); 
		}

	| '!' expr { $$ = sxp_new_not (compiler, $2); }
	| expr AND expr { $$ = sxp_new_and (compiler, $1, $3); }
	| expr OR expr { $$ = sxp_new_or (compiler, $1, $3); }

	| expr '>' expr { $$ = sxp_new_math (compiler, OP_GT, $1, $3); }
	| expr '<' expr { $$ = sxp_new_math (compiler, OP_LT, $1, $3); }
	| expr TNE expr { $$ = sxp_new_math (compiler, OP_NEQUAL, $1, $3); }
	| expr TGTE expr { $$ = sxp_new_math (compiler, OP_GTE, $1, $3); }
	| expr TLTE expr { $$ = sxp_new_math (compiler, OP_LTE, $1, $3); }
	| expr TEQUALS expr { $$ = sxp_new_math (compiler, OP_EQUAL, $1, $3); }

	| TVAR name { $$ = sxp_new_declare (compiler, $2, NULL); }
	| TVAR name '=' expr { $$ = sxp_new_declare (compiler, $2, $4); }
	| name '=' expr { $$ = sxp_new_assign (compiler, $1, $3); }
	| expr '[' expr ']' '=' expr %prec '=' { $$ = sxp_new_setindex (compiler, $1, $3, $6); }
	| expr TDEREFERENCE name '=' expr { $$ = sxp_new_set_member(compiler, $1, $3, $5); }

	| lval TADDASSIGN expr { $$ = sxp_new_preop (compiler, $1, OP_ADD, $3); }
	| lval TSUBASSIGN expr { $$ = sxp_new_preop (compiler, $1, OP_SUBTRACT, $3); }
	| lval TMULASSIGN expr { $$ = sxp_new_preop (compiler, $1, OP_MULTIPLY, $3); }
	| lval TDIVASSIGN expr { $$ = sxp_new_preop (compiler, $1, OP_DIVIDE, $3); }
	| lval TINCREMENT { $$ = sxp_new_postop (compiler, $1, OP_ADD, sxp_new_data (compiler, Number::Create (1))); }
	| lval TDECREMENT { $$ = sxp_new_postop (compiler, $1, OP_SUBTRACT, sxp_new_data (compiler, Number::Create (1))); }

	// FIXME: problem lines: reduce/reduce errors, can't figure out why or out to fix
	| TINCREMENT lval { $$ = sxp_new_preop (compiler, $2, OP_ADD, sxp_new_data (compiler, Number::Create (1))); }
	| TDECREMENT lval { $$ = sxp_new_preop (compiler, $2, OP_SUBTRACT, sxp_new_data (compiler, Number::Create (1))); }
	
	| type '(' expr ')' %prec TCAST { $$ = sxp_new_cast (compiler, $1, $3); }

	| name '(' func_args ')' { $$ = sxp_new_invoke (compiler, sxp_new_lookup(compiler, $1), $3); }
	| '(' expr ')' '(' func_args ')' { $$ = sxp_new_invoke (compiler, $2, $5); }

	| TNEW type { $$ = sxp_new_new (compiler, $2, NULL, false); }
	| TNEW type '(' func_args ')' { $$ = sxp_new_new (compiler, $2, $4, true); }
	| expr TDEREFERENCE name '(' func_args ')' { $$ = sxp_new_method (compiler, $1, $3, $5); }

	| '[' args ']' { $$ = sxp_new_array (compiler, $2); }
	| '[' ']' { $$ = sxp_new_array (compiler, NULL); }

	| data { $$ = sxp_new_data (compiler, $1); }

	| lval { $$ = $1; }
	;

	
data:	NUMBER { $$ = $1;  }
	| STRING { $$ = $1; }
	| TNIL { $$ = NULL; }
	| type { $$ = new TypeValue($1); }
	;

name:	IDENTIFIER { $$ = $1; }
	;

type:	TYPE { $$ = $1; }
	;

%%

int
yyerror (const char *str) {
	compiler->Error(str);
	return 1;
}

extern "C"
int
yywrap (void) {
	return 1;
}

int
Scriptix::System::LoadFile(const BaseString& file, SecurityLevel access, CompilerHandler* handler) {
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

	compiler = new Scriptix::Compiler::Compiler();
	if (compiler == NULL) {
		if (!file.empty())
			fclose (yyin);
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	if (!file.empty())
		compiler->SetFile(file);
	compiler->SetAccess(access);
	compiler->SetHandler(handler);

	sxp_compiler_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!file.empty())
		fclose (yyin);

	if (!ret)
		ret = compiler->Compile();

	return ret;
}

int
Scriptix::System::LoadString(const BaseString& buf, const BaseString& name, size_t lineno, SecurityLevel access, CompilerHandler* handler) {
	int ret;

	if (buf.empty())
		return SXE_INVALID;

	compiler = new Scriptix::Compiler::Compiler();
	if (compiler == NULL) {
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	compiler->SetAccess(access);
	compiler->SetFile(name);
	compiler->SetLine(lineno);
	compiler->SetHandler(handler);

	yyin = NULL;
	sxp_compiler_inbuf = buf.c_str();

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!ret)
		ret = compiler->Compile();

	return ret;
}
