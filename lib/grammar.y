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

	#define COMP_STACK_SIZE 50

	int parser_stack_size = 0;
	int parser_stack_top = 0;
	VALUE **parser_stack = NULL;

	VALUE *parser_top (void);
	void parser_push (VALUE *value);
	void parser_pop (void);

	VALUE *name_list[20];
	int name_ptr = 0;
	VALUE *get_dup_name (char *name);

	VALUE *append_to_array (VALUE *array, VALUE *value);
	NODE *append_to_expr (NODE *expr, NODE *node);

	int sxerror (char *);
	int sxlex (void);

	SYSTEM *parse_system = NULL;
	VALUE *parse_block = NULL;

	extern FILE *sxin;
	int sxparse (void);

	VALUE *temp_val;

	#define pushv(v) (add_value (parse_system, parser_top (), (v)))
	#define pushn(o,c) (add_stmt (parse_system, parser_top (), (o), (c)))
%}

%union {
	VALUE *value;
	char name[MAX_NAME_LEN + 1];
	unsigned int count;
}

%token<value> TNUM TSTR
%token<name> TNAME
%token TSEP TIF TTHEN TELSE TEND TWHILE TDO TAND TOR TGTE TLTE TNE
%token TRETURN TFUNC TBREAK TBLOCK TLOCAL TGLOBAL TEQUALS TRANGE
%token TADDASSIGN TSUBASSIGN TINCREMENT TDECREMENT TLENGTH TTHREAD
%token TCLASS TNEW TUNTIL TNIL TRAISE TRESCUE TTRY TIN TFOR TMETHOD
%token TSTEP TTO

%nonassoc TBREAK TRETURN TRAISE
%right '=' TADDASSIGN TSUBASSIGN 
%left TAND
%left TOR
%left '>' '<' TGTE TLTE
%left TNE TEQUALS TISA
%left '+' '-' TINCREMENT TDECREMENT
%left '*' '/'
%nonassoc '!' CUNARY
%nonassoc CPARAN TLENGTH TTYPE TWHILE TUNTIL TDO TNEW
%left '.' '[' '(' TMETHOD

%type<count> array_list stmt_list cstmt_list

%%

program: stmts {}
	;

block:	{ parser_push (new_block (parse_system)); } stmts { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

oblock:	{ parser_push (new_block (parse_system)); } node { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

stmts:	
	| stmt_list {}
	| seps stmt_list {}
	| stmt_list seps {}
	| seps stmt_list seps {}
	;

stmt_list: node { $$ = 1; }
	| stmt_list seps { if ($1 > 0) { pushn (OP_POP, 0); } $$ = $1 + 1; } node
	;

seps:	TSEP
	| seps TSEP
	;

cblock:	{ parser_push (new_block (parse_system)); } cstmts { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

cstmts:	
	| cstmt_list {}
	| seps cstmt_list {}
	| cstmt_list seps {}
	| seps cstmt_list seps {}
	;

cstmt_list: cstmt { $$ = 1; }
	| cstmt_list seps { if ($1 > 0) { pushn (OP_POP, 0); } $$ = $1 + 1; } cstmt 
	;

cstmt:	{ pushv (new_num (SCOPE_LOCAL)); } name '=' node { pushn (OP_ASSIGN, 3); }
	| { pushv (new_num (SCOPE_LOCAL)); } TFUNC name '(' args ')' block TEND { pushn (OP_NEWFUNC, 2); pushn (OP_ASSIGN, 3); }
	;

array_list: { $$ = 0; }
	| node { $$ = 1; }
	| array_list ',' node { $$ = $1 + 1; }
	;

args: { pushv (new_nil ()); }
	| { parser_push (new_array (parse_system, 0, NULL)); } arg_list { temp_val = parser_top (); parser_pop (); pushv (temp_val); }
	;

arg_list: TNAME { append_to_array (parser_top (), get_dup_name ($1)); }
	| arg_list ',' TNAME { append_to_array (parser_top (), get_dup_name ($3)); }
	;

node:	node '+' node { pushn (OP_ADD, 2); }
	| node '-' node { pushn (OP_SUBTRACT, 2); }
	| node '*' node { pushn (OP_MULTIPLY, 2); }
	| node '/' node { pushn (OP_DIVIDE, 2); }
	| '(' node ')' %prec CPARAN
	| '-' node %prec CUNARY { pushn (OP_NEGATE, 1); }

	| '!' node { pushn (OP_NOT, 1); }
	| node TAND node { pushn (OP_AND, 2); }
	| node TOR node { pushn (OP_OR, 2); }

	| node '>' node { pushn (OP_GT, 2); }
	| node '<' node { pushn (OP_LT, 2); }
	| node TNE node { pushn (OP_NEQUAL, 2); }
	| node TGTE node { pushn (OP_GTE, 2); }
	| node TLTE node { pushn (OP_LTE, 2); }
	| node TEQUALS node { pushn (OP_EQUAL, 2); }

	| name '=' node { pushn (OP_ASSIGN, 2); }
	| scope name '=' node { pushn (OP_ASSIGN, 3); }
	| node '[' node ']' '=' node %prec '=' { pushn (OP_SETINDEX, 3); }
	| node '.' name '=' node %prec '=' { pushn (OP_SETMEMBER, 3); }

	| name TADDASSIGN node { pushn (OP_PREINCREMENT, 2); }
	| name TSUBASSIGN node { pushn (OP_PREDECREMENT, 2); }
	| name TINCREMENT { pushn (OP_POSTINCREMENT, 1); }
	| TINCREMENT name { pushn (OP_PREINCREMENT, 1); }
	| name TDECREMENT { pushn (OP_POSTDECREMENT, 1); }
	| TDECREMENT name { pushn (OP_PREDECREMENT, 1); }
	
	| TLENGTH '(' node ')' { pushn (OP_SIZEOF, 1); }
	| TTYPE '(' node ')' { pushn (OP_TYPEOF, 1); }
	| node TISA node { pushn (OP_ISA, 2); }

	| node '(' array_list ')' { pushn (OP_CALL, 1 + $3); }
	| TFUNC name '(' args ')' block TEND { pushn (OP_NEWFUNC, 2); pushn (OP_ASSIGN, 2); }
	| TFUNC '(' args ')' block TEND { pushn (OP_NEWFUNC, 2); }

	| node TMETHOD name '(' array_list ')' { pushn (OP_METHOD, 2 + $5); }
	| node '.' name { pushn (OP_MEMBER, 2); }
	| TNEW node { pushn (OP_NEWINSTANCE, 1); }
	| TCLASS name cblock TEND { pushn (OP_NEWCLASS, 1); pushn (OP_ASSIGN, 2); }
	| TCLASS name ':' name { pushn (OP_LOOKUP, 1); } cblock TEND { pushn (OP_NEWCLASS, 2); pushn (OP_ASSIGN, 2); }

	| node '[' node ']' { pushn (OP_INDEX, 2); }
	
	| TIF node TTHEN block TEND { pushv (new_nil ()); pushn (OP_IF, 3); }
	| TIF node TTHEN block TELSE block TEND { pushn (OP_IF, 3); }
	| TWHILE oblock TDO block TEND { pushn (OP_WHILE, 2); }
	| TTRY block TRESCUE block TEND { pushn (OP_TRY, 2); }
	/*
	| TUNTIL node TDO block TEND { $$ = new_expr (parse_system, OP_WHILE, 2, new_expr (parse_system, OP_NOT, 1, $2), new_node (parse_system, $4)); }
	| TDO block TEND { $$ = new_expr (parse_system, OP_EVAL, 1, new_node (parse_system, $2)); }
	*/
	| TFOR name TIN node TDO block TEND { pushn (OP_FOR, 3); }
	| TFOR name TIN node TSTEP TNUM { pushv ($6); } TDO block TEND { pushn (OP_FOR, 4); }

	| name { pushn (OP_LOOKUP, 1); }
	| scope name { pushn (OP_LOOKUP, 2); }

	| TRETURN node { pushn (OP_RETURN, 1); }
	| TRETURN { pushn (OP_RETURN, 0); }
	| TBREAK { pushn (OP_BREAK, 0); }
	| TBREAK node { pushn (OP_BREAK, 1); }
	| TRAISE node { pushn (OP_RAISE, 0); }

	| TNUM TRANGE TNUM { pushv ($1); pushv ($3); pushn (OP_NEWRANGE, 2); }
	| '{' array_list '}' { pushn (OP_NEWARRAY, $2); }
	| data
	;


data:	TNUM { pushv ($1);  }
	| TSTR { pushv ($1); }
	| TBLOCK block TEND
	| TNIL { pushv (new_nil ()); }
	;

name:	TNAME { pushv (get_dup_name ($1)); }
	;

scope:	TLOCAL { pushv (new_num (SCOPE_LOCAL)); }
	| TGLOBAL { pushv (new_num (SCOPE_GLOBAL)); }
	| TTHREAD { pushv (new_num (SCOPE_THREAD)); }
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
	VALUE **new_stack;
	if (parser_stack_top >= parser_stack_size) {
		if (parser_stack != NULL) {
			new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + 20) * sizeof (VALUE **));
		} else {
			new_stack = sx_malloc (parse_system, (parser_stack_size + 20) * sizeof (VALUE **));
		}
		if (new_stack == NULL) {
			/* FIXME: error */
			return;
		}
		sx_free (parser_stack);
		parser_stack = new_stack;
		parser_stack_size += 20;
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

	if (!IS_ARRAY (array)) {
		return new_nil ();
	}

	if (array->data.array.count > 0) {
		nlist = (VALUE **)sx_malloc (parse_system, (array->data.array.count + 1) * sizeof (VALUE *));
		if (nlist == NULL) {
			return new_nil ();
		}
		memcpy (nlist, array->data.array.list, array->data.array.count * sizeof (VALUE *));
		sx_free (array->data.array.list);
		array->data.array.list = nlist;
		array->data.array.list[array->data.array.count] = value;
		array->data.array.count += 1;
	} else {
		array->data.array.list = (VALUE **)sx_malloc (parse_system, sizeof (VALUE *));
		if (array->data.array.list == NULL) {
			return new_nil ();
		}
		array->data.array.list[0] = value;
		array->data.array.count = 1;
	}

	return array;
}

VALUE *
get_dup_name (char *name) {
	int i;
	VALUE *ret;
	for (i = 0; i < 20 && name_list[i] != NULL; ++ i) {
		if (!strcasecmp (name, TO_STR (name_list[i]))) {
			return name_list[i];
		}
	}
	ret = new_str (parse_system, name);
	name_list[name_ptr] = ret;
	if (++ name_ptr >= 20) {
		name_ptr = 0;
	}
	return ret;
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
	unsigned int i;

	for (i = 0; i < parser_stack_top; i ++) {
		free_value (parser_stack[i]);
	}
	free (parser_stack);
	parser_stack = NULL;
	parser_stack_top = 0;
	parser_stack_size = 0;
}

VALUE *
load_file (SYSTEM *system, char *file) {
	int ret, flags, i;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			/* FIXME: error message */
			return NULL;
		}
	}

	for (i = 0; i < 20; ++ i) {
		name_list[i] = NULL;
	}

	parse_system = system;
	parse_block = new_block (system);
	if (parse_block == NULL) {
		if (sxin != NULL) {
			fclose (sxin);
		}
		return NULL;
	}

	flags = system->flags;
	system->flags |= SFLAG_GCOFF;
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

	lock_value (parse_block);
	run_gc (system);
	unlock_value (parse_block);

	cleanup_parser ();

	return parse_block;
}
