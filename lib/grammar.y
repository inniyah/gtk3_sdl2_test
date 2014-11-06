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
	VALUE **parser_stack = NULL;

	VALUE *parser_top (void);
	void parser_push (VALUE *value);
	void parser_pop (void);

	VALUE *append_to_array (VALUE *array, VALUE *value);
	NODE *append_to_expr (NODE *expr, NODE *node);

	int sxerror (char *);
	int sxlex (void);

	SYSTEM *parse_system = NULL;
	VALUE *parse_block = NULL;

	extern FILE *sxin;
	int sxparse (void);

	VALUE *temp_val;

	#define pushv(v) (sx_add_value (parse_system, parser_top (), (v)))
	#define pushn(o,c) (sx_add_stmt (parse_system, parser_top (), (o), (c)))
%}

%union {
	VALUE *value;
	char name[SX_MAX_NAME + 1];
	unsigned int count;
}

%token<value> TNUM TSTR
%token<name> TNAME
%token TSEP TIF TTHEN TELSE TEND TWHILE TDO TAND TOR TGTE TLTE TNE
%token TRETURN TFUNC TBREAK TBLOCK TLOCAL TGLOBAL TEQUALS TRANGE TSTEP
%token TADDASSIGN TSUBASSIGN TINCREMENT TDECREMENT TLENGTH TTHREAD
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
%left '.' '[' '(' TMETHOD

%type<count> array_list stmt_list cstmt_list

%%

program: stmts {}
	;

block:	{ parser_push (sx_new_block (parse_system)); } stmts { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

oblock:	{ parser_push (sx_new_block (parse_system)); } node { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

stmts:	
	| stmt_list {}
	| seps stmt_list {}
	| stmt_list seps {}
	| seps stmt_list seps {}
	;

stmt_list: node { $$ = 1; }
	| stmt_list seps { if ($1 > 0) { pushn (SX_OP_POP, 0); } $$ = $1 + 1; } node
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
	| cstmt_list seps { if ($1 > 0) { pushn (SX_OP_POP, 0); } $$ = $1 + 1; } cstmt 
	;

cstmt:	{ pushv (sx_new_num (SX_SCOPE_LOCAL)); } name '=' node { pushn (SX_OP_ASSIGN, 3); }
	| { pushv (sx_new_num (SX_SCOPE_LOCAL)); } TFUNC name '(' args ')' block TEND { pushn (SX_OP_NEWFUNC, 2); pushn (SX_OP_ASSIGN, 3); }
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

node:	node '+' node { pushn (SX_OP_ADD, 2); }
	| node '-' node { pushn (SX_OP_SUBTRACT, 2); }
	| node '*' node { pushn (SX_OP_MULTIPLY, 2); }
	| node '/' node { pushn (SX_OP_DIVIDE, 2); }
	| '(' node ')'
	| '-' node %prec CUNARY { pushn (SX_OP_NEGATE, 1); }

	| '!' node { pushn (SX_OP_NOT, 1); }
	| node TAND node { pushn (SX_OP_AND, 2); }
	| node TOR node { pushn (SX_OP_OR, 2); }

	| node '>' node { pushn (SX_OP_GT, 2); }
	| node '<' node { pushn (SX_OP_LT, 2); }
	| node TNE node { pushn (SX_OP_NEQUAL, 2); }
	| node TGTE node { pushn (SX_OP_GTE, 2); }
	| node TLTE node { pushn (SX_OP_LTE, 2); }
	| node TEQUALS node { pushn (SX_OP_EQUAL, 2); }

	| name '=' node { pushn (SX_OP_ASSIGN, 2); }
	| scope name '=' node { pushn (SX_OP_ASSIGN, 3); }
	| node '[' node ']' '=' node %prec '=' { pushn (SX_OP_SETINDEX, 3); }
	| node '.' name '=' node %prec '=' { pushn (SX_OP_SETMEMBER, 3); }

	| name TADDASSIGN node { pushn (SX_OP_PREINCREMENT, 2); }
	| name TSUBASSIGN node { pushn (SX_OP_PREDECREMENT, 2); }
	| name TINCREMENT { pushv (sx_new_num (1)); pushn (SX_OP_POSTINCREMENT, 2); }
	| TINCREMENT name { pushv (sx_new_num (1)); pushn (SX_OP_PREINCREMENT, 2); }
	| name TDECREMENT { pushv (sx_new_num (1)); pushn (SX_OP_POSTDECREMENT, 2); }
	| TDECREMENT name { pushv (sx_new_num (1)); pushn (SX_OP_PREDECREMENT, 2); }
	
	| TLENGTH '(' node ')' { pushn (SX_OP_SIZEOF, 1); }
	| TTYPE '(' node ')' { pushn (SX_OP_TYPEOF, 1); }
	| node TISA node { pushn (SX_OP_ISA, 2); }

	| node '(' array_list ')' { pushn (SX_OP_CALL, 1 + $3); }
	| TFUNC name '(' args ')' block TEND { pushn (SX_OP_NEWFUNC, 2); pushn (SX_OP_ASSIGN, 2); }
	| TFUNC '(' args ')' block TEND { pushn (SX_OP_NEWFUNC, 2); }

	| node TMETHOD name '(' array_list ')' { pushn (SX_OP_METHOD, 2 + $5); }
	| node '.' name { pushn (SX_OP_MEMBER, 2); }
	| TNEW node { pushn (SX_OP_NEWINSTANCE, 1); }
	| TCLASS name cblock TEND { pushn (SX_OP_NEWCLASS, 1); pushn (SX_OP_ASSIGN, 2); }
	| TCLASS name ':' name { pushn (SX_OP_LOOKUP, 1); } cblock TEND { pushn (SX_OP_NEWCLASS, 2); pushn (SX_OP_ASSIGN, 2); }

	| node '[' node ']' { pushn (SX_OP_INDEX, 2); }
	
	| TIF node TTHEN block TEND { pushv (sx_new_nil ()); pushn (SX_OP_IF, 3); }
	| TIF node TTHEN block TELSE block TEND { pushn (SX_OP_IF, 3); }
	| TWHILE oblock TDO block TEND { pushn (SX_OP_WHILE, 2); }
	| TTRY block TRESCUE errors block TEND { pushn (SX_OP_TRY, 3); }
	| TUNTIL oblock TDO block TEND { pushn (SX_OP_UNTIL, 2); }
	| TDO block TEND { pushn (SX_OP_EVAL, 1); }
	| TFOR name TIN node TDO block TEND { pushn (SX_OP_FOR, 3); }
	| TFOR name TIN node TSTEP TNUM { pushv ($6); } TDO block TEND { pushn (SX_OP_FOR, 4); }

	| name { pushn (SX_OP_LOOKUP, 1); }
	| scope name { pushn (SX_OP_LOOKUP, 2); }

	| TRETURN node { pushn (SX_OP_RETURN, 1); }
	| TRETURN { pushn (SX_OP_RETURN, 0); }
	| TBREAK { pushn (SX_OP_BREAK, 0); }
	| TBREAK node { pushn (SX_OP_BREAK, 1); }
	| TRAISE node { pushn (SX_OP_RAISE, 0); }

	| node TRANGE node { pushn (SX_OP_NEWRANGE, 2); }
	| '{' array_list '}' { pushn (SX_OP_NEWARRAY, $2); }
	| data
	;


data:	TNUM { pushv ($1);  }
	| TSTR { pushv ($1); }
	| TBLOCK block TEND
	| TNIL { pushv (sx_new_nil ()); }
	;

name:	TNAME { pushv (sx_new_num (sx_name_to_id ($1))); }
	;

scope:	TLOCAL { pushv (sx_new_num (SX_SCOPE_LOCAL)); }
	| TGLOBAL { pushv (sx_new_num (SX_SCOPE_GLOBAL)); }
	| TTHREAD { pushv (sx_new_num (SX_SCOPE_THREAD)); }
	;

%%

/* value stack */
VALUE *
parser_top (void) {
	if (parser_stack_top > 0) {
		return parser_stack[parser_stack_top - 1];
	}

	return NULL;
}

void
parser_push (VALUE *value) {
	VALUE **sx_new_stack;
	if (parser_stack_top >= parser_stack_size) {
		if (parser_stack != NULL) {
			sx_new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + COMP_STACK_SIZE) * sizeof (VALUE **));
		} else {
			sx_new_stack = sx_malloc (parse_system, (parser_stack_size + COMP_STACK_SIZE) * sizeof (VALUE **));
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


VALUE *
append_to_array (VALUE *array, VALUE *value) {
	VALUE **nlist;

	if (!SX_ISARRAY (array)) {
		return sx_new_nil ();
	}

	if (array->data.array.count > 0) {
		nlist = (VALUE **)sx_malloc (parse_system, (array->data.array.count + 1) * sizeof (VALUE *));
		if (nlist == NULL) {
			return sx_new_nil ();
		}
		memcpy (nlist, array->data.array.list, array->data.array.count * sizeof (VALUE *));
		sx_free (array->data.array.list);
		array->data.array.list = nlist;
		array->data.array.list[array->data.array.count] = value;
		array->data.array.count += 1;
	} else {
		array->data.array.list = (VALUE **)sx_malloc (parse_system, sizeof (VALUE *));
		if (array->data.array.list == NULL) {
			return sx_new_nil ();
		}
		array->data.array.list[0] = value;
		array->data.array.count = 1;
	}

	return array;
}

/* global vars */
unsigned int parse_lineno = 1;

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

VALUE *
sx_load_file (SYSTEM *system, char *file) {
	int ret, flags;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return NULL;
		}
	}

	parse_system = system;
	parse_block = sx_new_block (system);
	if (parse_block == NULL) {
		if (sxin != NULL) {
			fclose (sxin);
		}
		return NULL;
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
		return NULL;
	}

	sx_lock_value (parse_block);
	sx_run_gc (system);
	sx_unlock_value (parse_block);

	cleanup_parser ();

	return parse_block;
}
