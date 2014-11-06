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

	int parser_node_stack_size = 0;
	int parser_node_stack_top = 0;
	NODE **parser_node_stack = NULL;

	__INLINE__ NODE *parser_node_top (void);
	__INLINE__ void parser_node_pop (void);
	void parser_node_push (NODE *node);

	VALUE *name_list[20];
	int name_ptr = 0;
	VALUE *get_dup_name (VALUE *name);

	VALUE *append_to_array (VALUE *array, VALUE *value);
	NODE *append_to_expr (NODE *expr, NODE *node);

	int sxerror (char *);
	int sxlex (void);

	SYSTEM *parse_system = NULL;
	VALUE *parse_block = NULL;

	extern FILE *sxin;
	int sxparse (void);
%}

%union {
	VALUE *value;
	NODE *node;
}

%token<value> TNUM TSTR TNAME
%token TSEP TIF TTHEN TELSE TEND TWHILE TDO TAND TOR TGTE TLTE TNE
%token TRETURN TFUNC TBREAK TBLOCK TLOCAL TGLOBAL TEQUALS TRANGE
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
%nonassoc '!' CUNARY
%nonassoc CPARAN TLENGTH TTYPE TWHILE TUNTIL TDO TNEW
%left '.' '[' '(' TMETHOD

%type<node> node stmt cstmt array
%type<value> data block cblock args name scope

%%

program: block { parse_block = $1; }
	;

block:	{ parser_push (new_block (parse_system)); } stmts { $$ = parser_top (); parser_pop (); }
	;

stmts:	stmt { if ($1 != NULL) { add_stmt (parser_top (), $1); }}
	| stmts TSEP stmt { if ($3 != NULL) { add_stmt (parser_top (), $3); }}
	;

stmt:	{ $$ = NULL; }
	| node { $$ = $1; }
	;

cblock:	{ parser_push (new_block (parse_system)); } cstmts { $$ = parser_top (); parser_pop (); }
	;

cstmts:	cstmt { if ($1 != NULL) { add_stmt (parser_top (), $1); }}
	| cstmts TSEP cstmt { if ($3!= NULL) { add_stmt (parser_top (), $3); }}
	;

cstmt:	{ $$ = NULL; }
	| TFUNC name '(' args ')' block TEND { $$ = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, $2), new_node (parse_system, new_func (parse_system, $4, $6))); }
	| TFUNC name '(' ')' block TEND { $$ = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, $2), new_node (parse_system, new_func (parse_system, new_nil (), $5))); }
	| name '=' node { $$ = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, $1), $3); }
	;

array:	'{' { parser_node_push (new_expr (parse_system, OP_NEWARRAY, 0)); } array_list '}' { $$ = parser_node_top (); parser_node_pop (); }
	;

array_list:
	| node { append_to_expr (parser_node_top  (), $1); }
	| array_list ',' node { append_to_expr (parser_node_top (), $3); }
	;

args:	{ parser_push (new_array (parse_system, 0, NULL)); } arg_list { $$ = parser_top (); parser_pop (); }
	;

arg_list: name { append_to_array (parser_top (), $1); }
	| arg_list ',' name { append_to_array (parser_top (), $3); }
	;

node:	node '+' node { $$ = new_expr (parse_system, OP_ADD, 2, $1, $3); }
	| node '-' node { $$ = new_expr (parse_system, OP_SUBTRACT, 2, $1, $3); }
	| '(' node ')' %prec CPARAN { $$ = $2; }
	| node '*' node { $$ = new_expr (parse_system, OP_MULTIPLY, 2, $1, $3); }
	| node '/' node { $$ = new_expr (parse_system, OP_DIVIDE, 2, $1, $3); }
	| '-' node %prec CUNARY { $$ = new_expr (parse_system, OP_NEGATE, 1, $2); }

	| '!' node { $$ = new_expr (parse_system, OP_NOT, 1, $2); }
	| node TAND node { $$ = new_expr (parse_system, OP_AND, 2, $1, $3); }
	| node TOR node { $$ = new_expr (parse_system, OP_OR, 2, $1, $3); }

	| node '>' node { $$ = new_expr (parse_system, OP_GT, 2, $1, $3); }
	| node '<' node { $$ = new_expr (parse_system, OP_LT, 2, $1, $3); }
	| node TNE node { $$ = new_expr (parse_system, OP_NEQUAL, 2, $1, $3); }
	| node TGTE node { $$ = new_expr (parse_system, OP_GTE, 2, $1, $3); }
	| node TLTE node { $$ = new_expr (parse_system, OP_LTE, 2, $1, $3); }
	| node TEQUALS node { $$ = new_expr (parse_system, OP_EQUAL, 2, $1, $3); }

	| name '=' node { $$ = new_expr (parse_system, OP_ASSIGN, 3, new_node (parse_system, $1), $3, new_node (parse_system, new_num (SCOPE_DEF))); }
	| scope name '=' node { $$ = new_expr (parse_system, OP_ASSIGN, 3, new_node (parse_system, $2), $4, new_node (parse_system, $1)); }
	| node '[' node ']' '=' node %prec '=' { $$ = new_expr (parse_system, OP_SETINDEX, 3, $1, $3, $6); }
	| node '.' name '=' node %prec '=' { $$ = new_expr (parse_system, OP_SETMEMBER, 3, $1, new_node (parse_system, $3), $5); }

	| name TADDASSIGN node { $$ = new_expr (parse_system, OP_PREINCREMENT, 2, new_node (parse_system, $1), $3); }
	| name TSUBASSIGN node { $$ = new_expr (parse_system, OP_PREDECREMENT, 2, new_node (parse_system, $1), $3); }
	| name TINCREMENT { $$ = new_expr (parse_system, OP_POSTINCREMENT, 2, new_node (parse_system, $1), new_node (parse_system, new_num (1))); }
	| TINCREMENT name { $$ = new_expr (parse_system, OP_PREINCREMENT, 2, new_node (parse_system, $2), new_node (parse_system, new_num (1))); }
	| name TDECREMENT { $$ = new_expr (parse_system, OP_POSTDECREMENT, 2, new_node (parse_system, $1), new_node (parse_system, new_num (1))); }
	| TDECREMENT name { $$ = new_expr (parse_system, OP_PREDECREMENT, 2, new_node (parse_system, $2), new_node (parse_system, new_num (1))); }
	

	| TLENGTH '(' node ')' { $$ = new_expr (parse_system, OP_SIZEOF, 1, $3); }
	| TTYPE '(' node ')' { $$ = new_expr (parse_system, OP_TYPEOF, 1, $3); }
	| node TISA node { $$ = new_expr (parse_system, OP_ISA, 2, $1, $3); }

	| node '(' { parser_node_push (new_expr (parse_system, OP_CALL, 2, $1, NULL)); } array_list ')' { $$ = parser_node_top (); parser_node_pop (); }
	| TFUNC name '(' args ')' block TEND { $$ = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, $2), new_node (parse_system, new_func (parse_system, $4, $6))); }
	| TFUNC name '(' ')' block TEND { $$ = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, $2), new_node (parse_system, new_func (parse_system, new_nil (), $5))); }

	| node TMETHOD name '(' { parser_node_push (new_expr (parse_system, OP_CALL, 2, new_expr (parse_system, OP_MEMBER, 2, $1, new_node (parse_system, $3)), $1)); } array_list ')' { $$ = parser_node_top (); parser_node_pop (); }
	| node '.' name { $$ = new_expr (parse_system, OP_MEMBER, 2, $1, new_node (parse_system, $3)); }
	| TNEW node { $$ = new_expr (parse_system, OP_NEWINSTANCE, 1, $2); }
	| TCLASS name cblock TEND { $$ = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, $2), new_expr (parse_system, OP_NEWCLASS, 2, NULL, new_node (parse_system, $3))); }
	| TCLASS name ':' name cblock TEND { $$ = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, $2), new_expr (parse_system, OP_NEWCLASS, 2, new_expr (parse_system, OP_LOOKUP, 2, new_node (parse_system, $4), new_node (parse_system, new_num (SCOPE_DEF))), new_node (parse_system, $5))); }

	| node '[' node ']' { $$ = new_expr (parse_system, OP_INDEX, 2, $1, $3); }
	
	| TIF node TTHEN block TEND { $$ = new_expr (parse_system, OP_IF, 2, $2, new_node (parse_system, $4)); }
	| TIF node TTHEN block TELSE block TEND { $$ = new_expr (parse_system, OP_IF, 3, $2, new_node (parse_system, $4), new_node (parse_system, $6)); }
	| TWHILE node TDO block TEND { $$ = new_expr (parse_system, OP_WHILE, 2, $2, new_node (parse_system, $4)); }
	| TUNTIL node TDO block TEND { $$ = new_expr (parse_system, OP_WHILE, 2, new_expr (parse_system, OP_NOT, 1, $2), new_node (parse_system, $4)); }
	| TTRY block TRESCUE block TEND { $$ = new_expr (parse_system, OP_TRY, 2, new_node (parse_system, $2), new_node (parse_system, $4)); }
	| TDO block TEND { $$ = new_expr (parse_system, OP_EVAL, 1, new_node (parse_system, $2)); }
	| TFOR name TIN node TDO block TEND { $$ = new_expr (parse_system, OP_FOR, 3, new_node (parse_system, $2), $4, new_node (parse_system, $6)); }

	| name { $$ = new_expr (parse_system, OP_LOOKUP, 2, new_node (parse_system, $1), new_node (parse_system, new_num (SCOPE_DEF))); }
	| scope name { $$ = new_expr (parse_system, OP_LOOKUP, 2, new_node (parse_system, $2), new_node (parse_system, $1)); }

	| TRETURN node { $$ = new_expr (parse_system, OP_RETURN, 1, $2); }
	| TRETURN { $$ = new_expr (parse_system, OP_RETURN, 0);  }
	| TBREAK { $$ = new_expr (parse_system, OP_BREAK, 0); }
	| TBREAK node { $$ = new_expr (parse_system, OP_BREAK, 1, $2); }
	| TRAISE node { $$ = new_expr (parse_system, OP_RAISE, 1, $2); }

	| data { $$ = new_node (parse_system, $1);  }
	| array { $$ = $1; }
	;


data:	TNUM { $$ = $1;  }
	| TSTR { $$ = $1; }
	| TBLOCK block TEND { $$ = $2;  }
	| TFUNC '(' ')' block TEND { $$ = new_func (parse_system, new_nil (), $4); }
	| TFUNC '(' args ')' block TEND { $$ = new_func (parse_system, $3, $5); }
	| TNIL { $$ = new_nil (); }
	| TNUM TRANGE TNUM { $$ = new_range (parse_system, TO_INT($1), TO_INT($3), 1); }
	;

name:	TNAME { $$ = get_dup_name ($1); }
	;

scope:	TLOCAL { $$ = new_num (SCOPE_LOCAL); }
	| TGLOBAL { $$ = new_num (SCOPE_GLOBAL); }
	| TTHREAD { $$ = new_num (SCOPE_THREAD); }
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
			new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + STACK_CHUNK_SIZE) * sizeof (VALUE **));
		} else {
			new_stack = sx_malloc (parse_system, (parser_stack_size + STACK_CHUNK_SIZE) * sizeof (VALUE **));
		}
		if (new_stack == NULL) {
			/* FIXME: error */
			return;
		}
		sx_free (parser_stack);
		parser_stack = new_stack;
		parser_stack_size += STACK_CHUNK_SIZE;
	}

	parser_stack[parser_stack_top ++] = value;
}

void
parser_pop (void) {
	if (parser_stack_top > 0) {
		-- parser_stack_top;
	}
}

/* node stack */
NODE *
parser_node_top (void) {
	if (parser_node_stack_top > 0) {
		return parser_node_stack[parser_node_stack_top - 1];
	}

	return NULL;
}

void
parser_node_push (NODE *node) {
	NODE **new_stack;
	if (parser_node_stack_top >= parser_node_stack_size) {
		if (parser_node_stack != NULL) {
			new_stack = sx_dupmem (parse_system, parser_node_stack, (parser_node_stack_size + STACK_CHUNK_SIZE) * sizeof (NODE **));
		} else {
			new_stack = sx_malloc (parse_system, (parser_node_stack_size + STACK_CHUNK_SIZE) * sizeof (NODE **));
		}
		if (new_stack == NULL) {
			/* FIXME: error */
			return;
		}
		sx_free (parser_node_stack);
		parser_node_stack = new_stack;
		parser_node_stack_size += STACK_CHUNK_SIZE;
	}

	parser_node_stack[parser_node_stack_top ++] = node;
}

void
parser_node_pop (void) {
	if (parser_node_stack_top > 0) {
		-- parser_node_stack_top;
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

NODE *
append_to_expr (NODE *expr, NODE *node) {
	NODE **nnodes;

	if (expr->data.expr.count > 0) {
		nnodes = (NODE **)sx_malloc (parse_system, (expr->data.expr.count + 1) * sizeof (NODE *));
		if (nnodes == NULL) {
			return NULL;
		}
		memcpy (nnodes, expr->data.expr.nodes, expr->data.expr.count * sizeof (NODE *));
		sx_free (expr->data.expr.nodes);
		expr->data.expr.nodes = nnodes;
		expr->data.expr.nodes[expr->data.expr.count] = node;
		expr->data.expr.count += 1;
	} else {
		expr->data.expr.nodes = (NODE **)sx_malloc (parse_system, sizeof (NODE *));
		if (expr->data.expr.nodes == NULL) {
			return NULL;
		}
		expr->data.expr.nodes[0] = node;
		expr->data.expr.count = 1;
	}

	return expr;
}

VALUE *
get_dup_name (VALUE *name) {
	int i;
	for (i = 0; i < 20; ++ i) {
		if (name == name_list[i]) {
			return name;
		}
		if (are_equal (name, name_list[i])) {
			return name_list[i];
		}
	}
	name_list[name_ptr] = name;
	if (++ name_ptr >= 20) {
		name_ptr = 0;
	}
	return name;
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
	parse_block = NULL;

	flags = system->flags;
	system->flags |= SFLAG_GCOFF;
	ret = sxparse ();
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
