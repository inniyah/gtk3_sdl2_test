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

	#include "scriptix.h"

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int parser_stack_size = 0;
	int parser_stack_top = 0;
	SX_VALUE **parser_stack = NULL;

	SX_VALUE *parser_top (void);
	void parser_push (SX_VALUE *value);
	void parser_pop (void);

	SX_VALUE *append_to_array (SX_VALUE *array, SX_VALUE *value);

	__INLINE__ void parser_add_line (void);

	int sxerror (char *);
	int sxlex (void);

	SX_SYSTEM *parse_system = NULL;
	SX_VALUE *parse_block = NULL;

	unsigned int parse_lineno = 1;
	extern FILE *sxin;
	int sxparse (void);

	SX_VALUE *temp_val;

	#define pushv(v) (sx_add_value (parse_system, parser_top (), (v)))
	#define pushn(o) (sx_add_stmt (parse_system, parser_top (), (o)))
%}

%union {
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	unsigned int count;
}

%token<value> TNUM TSTR
%token<name> TNAME
%token TSEP TIF TTHEN TELSE TEND TWHILE TDO TAND TOR TGTE TLTE TNE
%token TRETURN TFUNC TBREAK TBLOCK TLOCAL TGLOBAL TEQUALS TRANGE TSTEP
%token TADDASSIGN TSUBASSIGN TINCREMENT TDECREMENT TLENGTH
%token TCLASS TNEW TUNTIL TNIL TRAISE TRESCUE TTRY TIN TFOR TMETHOD

%nonassoc TBREAK TRETURN TRAISE
%right '=' TADDASSIGN TSUBASSIGN 
%left TAND
%left TOR
%left '>' '<' TGTE TLTE
%left TNE TEQUALS TISA
%left '+' '-' TINCREMENT TDECREMENT
%left '*' '/'
%nonassoc TLENGTH TTYPE TWHILE TUNTIL TDO TNEW
%left TRANGE
%nonassoc '!' CUNARY
%left '.' '[' '(' TMETHOD '^'

%type<count> array_list stmt_list cstmt_list
%type<value> scope

%%

program: stmts {}
	;

block:	{ parser_push (sx_new_block (parse_system)); } stmts { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

oblock:	{ parser_push (sx_new_block (parse_system)); } node { pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

stmts:	
	| stmt_list {}
	| seps stmt_list {}
	| stmt_list seps {}
	| seps stmt_list seps {}
	;

stmt_list: stmt { $$ = 1; }
	| stmt_list seps { $$ = $1 + 1; } stmt
	;

stmt:	node { pushn (SX_OP_STMT); }
	;

seps:	TSEP
	| seps TSEP
	;

cblock:	{ parser_push (sx_new_block (parse_system)); } cstmts { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

cstmts:	
	| cstmt_list {}
	| seps cstmt_list {}
	| cstmt_list seps {}
	| seps cstmt_list seps {}
	;

cstmt_list: cstmt { $$ = 1; }
	| cstmt_list seps { $$ = $1 + 1; } cstmt 
	;

cstmt:	name '=' node { pushv (sx_new_num (SX_SCOPE_CLASS)); pushn (SX_OP_ASSIGN); pushn (SX_OP_STMT); }
	| TFUNC name '(' args ')' TSEP block TEND { pushn (SX_OP_NEWFUNC); pushv (sx_new_num (SX_SCOPE_CLASS)); pushn (SX_OP_ASSIGN); pushn (SX_OP_STMT); }
	;

array_list: { $$ = 0; }
	| node { $$ = 1; }
	| array_list ',' node { $$ = $1 + 1; }
	;

args: { pushv (sx_new_nil ()); }
	| { parser_push (sx_new_array (parse_system, 0, NULL)); } arg_list { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

arg_list: TNAME { append_to_array (parser_top (), sx_new_num(sx_name_to_id ($1))); }
	| arg_list ',' TNAME { append_to_array (parser_top (), sx_new_num(sx_name_to_id ($3))); }
	;

errors: { parser_push (sx_new_array (parse_system, 0, NULL)); } error_list { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

error_list: TNAME TNAME { append_to_array (parser_top (), sx_new_num(sx_name_to_id ($1))); append_to_array (parser_top (), sx_new_num(sx_name_to_id ($2))); }
	| arg_list ',' TNAME TNAME { append_to_array (parser_top (), sx_new_num(sx_name_to_id ($3))); append_to_array (parser_top (), sx_new_num(sx_name_to_id ($4))); }
	;

node:	node '+' node { pushn (SX_OP_ADD); }
	| node '-' node { pushn (SX_OP_SUBTRACT); }
	| node '*' node { pushn (SX_OP_MULTIPLY); }
	| node '/' node { pushn (SX_OP_DIVIDE); }
	| '(' node ')'
	| '-' node %prec CUNARY { pushn (SX_OP_NEGATE); }

	| '!' node { pushn (SX_OP_NOT); }
	| node TAND { parser_push (sx_new_block (parse_system)); } node { pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); pushn (SX_OP_AND); }
	| node TOR { parser_push (sx_new_block (parse_system)); } node { pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); pushn (SX_OP_OR); }

	| node '>' node { pushn (SX_OP_GT); }
	| node '<' node { pushn (SX_OP_LT); }
	| node TNE node { pushn (SX_OP_NEQUAL); }
	| node TGTE node { pushn (SX_OP_GTE); }
	| node TLTE node { pushn (SX_OP_LTE); }
	| node TEQUALS node { pushn (SX_OP_EQUAL); }

	| name '=' node { pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
	| scope name '=' node { pushv ($1); pushn (SX_OP_ASSIGN); }
	| node '[' node ']' '=' node %prec '=' { pushn (SX_OP_SETINDEX); }
	| node '.' name '=' node %prec '=' { pushn (SX_OP_SETMEMBER); }

	| name TADDASSIGN node { pushn (SX_OP_PREINCREMENT); }
	| name TSUBASSIGN node { pushn (SX_OP_PREDECREMENT); }
	| name TINCREMENT { pushv (sx_new_num (1)); pushn (SX_OP_POSTINCREMENT); }
	| TINCREMENT name { pushv (sx_new_num (1)); pushn (SX_OP_PREINCREMENT); }
	| name TDECREMENT { pushv (sx_new_num (1)); pushn (SX_OP_POSTDECREMENT); }
	| TDECREMENT name { pushv (sx_new_num (1)); pushn (SX_OP_PREDECREMENT); }
	
	| TLENGTH '(' node ')' { pushn (SX_OP_SIZEOF); }
	| TTYPE '(' node ')' { pushn (SX_OP_TYPEOF); }
	| node TISA node { pushn (SX_OP_ISA); }

	| lookup '(' array_list ')' { pushv (sx_new_num ($3)); pushn (SX_OP_CALL); }
	| node TMETHOD '(' array_list ')' { pushv (sx_new_num ($4)); pushn (SX_OP_CALL); }
	| TFUNC name '(' args ')' TSEP block TEND { pushn (SX_OP_NEWFUNC); pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
	| TFUNC '(' args ')' TSEP block TEND { pushn (SX_OP_NEWFUNC); }

	| node '.' name '(' array_list ')' { pushv (sx_new_num ($5)); pushn (SX_OP_METHOD); }
	| node '.' name { pushn (SX_OP_MEMBER); }
	| TNEW node { pushn (SX_OP_NEWINSTANCE); }
	| TCLASS name TSEP { pushv (sx_new_nil ()); } cblock TEND { pushn (SX_OP_NEWCLASS); pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
	| TCLASS name ':' name TSEP { pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_LOOKUP); } cblock TEND { pushn (SX_OP_NEWCLASS); pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }

	| node '[' node ']' { pushn (SX_OP_INDEX); }
	
	| TIF node TTHEN block TEND { pushv (sx_new_nil ()); pushn (SX_OP_IF); }
	| TIF node TTHEN block TELSE block TEND { pushn (SX_OP_IF); }
	| TWHILE oblock TDO block TEND { pushn (SX_OP_WHILE); }
	| TTRY block TRESCUE errors block TEND { pushn (SX_OP_TRY); }
	| TUNTIL oblock TDO block TEND { pushn (SX_OP_UNTIL); }
	| TDO block TEND { pushn (SX_OP_EVAL); }
	| TFOR name TIN node TDO { pushv (sx_new_num (1)); } block TEND { pushn (SX_OP_FOR); }
	| TFOR name TIN node TSTEP TNUM { pushv ($6); } TDO block TEND { pushn (SX_OP_FOR); }

	| TRETURN node { pushn (SX_OP_RETURN); }
	| TRETURN { pushv (sx_new_nil ()); pushn (SX_OP_RETURN); }
	| TBREAK { pushv (sx_new_nil ()); pushn (SX_OP_BREAK); }
	| TBREAK node { pushn (SX_OP_BREAK); }
	| TRAISE node { pushn (SX_OP_RAISE); }

	| lookup {}

	| node TRANGE node { pushn (SX_OP_NEWRANGE); }
	| '{' array_list '}' { pushv (sx_new_num ($2)); pushn (SX_OP_NEWARRAY); }

	| TNUM { pushv ($1);  }
	| TSTR { pushv ($1); }
	| TBLOCK block TEND
	| TNIL { pushv (sx_new_nil ()); }
	;

lookup:	name { pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_LOOKUP); }
	| scope name { pushv ($1); pushn (SX_OP_LOOKUP); }
	;

name:	TNAME { pushv (sx_new_num (sx_name_to_id ($1))); }
	;

scope:	TLOCAL { $$ = (sx_new_num (SX_SCOPE_LOCAL)); }
	| TGLOBAL { $$ = (sx_new_num (SX_SCOPE_GLOBAL)); }
	;

%%

void
parser_add_line (void) {
	++ parse_lineno;
}

/* value stack */
SX_VALUE *
parser_top (void) {
	if (parser_stack_top > 0) {
		return parser_stack[parser_stack_top - 1];
	}

	return NULL;
}

void
parser_push (SX_VALUE *value) {
	SX_VALUE **sx_new_stack;
	if (parser_stack_top >= parser_stack_size) {
		if (parser_stack != NULL) {
			sx_new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + COMP_STACK_SIZE) * sizeof (SX_VALUE **));
		} else {
			sx_new_stack = sx_malloc (parse_system, (parser_stack_size + COMP_STACK_SIZE) * sizeof (SX_VALUE **));
		}
		if (sx_new_stack == NULL) {
			/* FIXME: error */
			return;
		}
		sx_free (parser_stack);
		parser_stack = sx_new_stack;
		parser_stack_size += COMP_STACK_SIZE;
	}

	parser_stack[parser_stack_top ++] = value;
}

void
parser_pop (void) {
	if (parser_stack_top > 0) {
		-- parser_stack_top;
	}
}


SX_VALUE *
append_to_array (SX_VALUE *array, SX_VALUE *value) {
	SX_VALUE **nlist;

	if (!SX_ISARRAY (array)) {
		return sx_new_nil ();
	}

	if (array->data.array.count > 0) {
		nlist = (SX_VALUE **)sx_malloc (parse_system, (array->data.array.count + 1) * sizeof (SX_VALUE *));
		if (nlist == NULL) {
			return sx_new_nil ();
		}
		memcpy (nlist, array->data.array.list, array->data.array.count * sizeof (SX_VALUE *));
		sx_free (array->data.array.list);
		array->data.array.list = nlist;
		array->data.array.list[array->data.array.count] = value;
		array->data.array.count += 1;
	} else {
		array->data.array.list = (SX_VALUE **)sx_malloc (parse_system, sizeof (SX_VALUE *));
		if (array->data.array.list == NULL) {
			return sx_new_nil ();
		}
		array->data.array.list[0] = value;
		array->data.array.count = 1;
	}

	return array;
}

int
sxerror (char *str) {
	fprintf (stderr, "ERROR: line %d: %s\n", parse_lineno, str);
	return 1;
}

int
sxwrap (void) {
	return 1;
}

void
cleanup_parser (void) {
	free (parser_stack);
	parser_stack = NULL;
	parser_stack_top = 0;
	parser_stack_size = 0;
}

sx_script_id
sx_load_file (SX_SYSTEM *system, char *file) {
	int ret, flags;
	SX_SCRIPT *script;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return 0;
		}
	}

	parse_system = system;
	parse_block = sx_new_block (system);
	if (parse_block == NULL) {
		if (sxin != NULL) {
			fclose (sxin);
		}
		return 0;
	}

	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;
	parser_push (parse_block);
	ret = sxparse ();
	parser_pop ();
	system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (ret) {
		cleanup_parser ();
		return 0;
	}

	sx_lock_value (parse_block);
	sx_run_gc (system);

	cleanup_parser ();

	script = sx_malloc (system, sizeof (SX_SCRIPT));
	sx_unlock_value (parse_block);
	if (script == NULL) {
		return 0;
	}

	script->block = parse_block;
	script->name = NULL;
	script->path = NULL;
	script->id = 0;
	script->next = NULL;
	sx_add_script (system, script);

	return script->id;
}
