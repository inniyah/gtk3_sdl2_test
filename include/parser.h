/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003  AwesomePlay Productions, Inc.
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

#ifndef __SXPARSER_H__
#define __SXPARSER_H__

enum {
	SXP_NOOP = 0,
	SXP_MATH,
	SXP_DATA,
	SXP_NEGA,
	SXP_NOT,
	SXP_AND,
	SXP_OR,
	SXP_CALL,
	SXP_LOOK,
	SXP_ASSI,
	SXP_STMT,
	SXP_IF,
	SXP_WHIL,
	SXP_SET,
	SXP_INDX,
	SXP_ARRY,
	SXP_ASSC,
	SXP_PRIC,
	SXP_POIC,
	SXP_RETR,
	SXP_BRAK,
	SXP_METH,
	SXP_DEFC,
	SXP_CAST,
	SXP_CFOR,
	SXP_CONT,
	SXP_SMET,
	SXP_SUPR,
	SXP_YELD,
	SXP_IN,
	SXP_NEW,
	SXP_AFNC,
	SXP_CLOS,
	SXP_SET_MEMBER,
	SXP_GET_MEMBER,
	SXP_NAME_DATA,
};

#define SXP_W_WD 1
#define SXP_W_DW 2
#define SXP_W_DU 3
#define SXP_W_UD 4
#define SXP_W_PE 5

typedef struct scriptix_parse_node SXP_NODE;
typedef struct scriptix_parse_info SXP_INFO;
typedef struct scriptix_parse_function SXP_FUNC;
typedef struct scriptix_parse_jump SXP_JUMP;
typedef struct scriptix_parse_block SXP_BLOCK;

struct scriptix_parse_block {
	SXP_JUMP *breaks;
	SXP_JUMP *continues;
	SXP_BLOCK *next;
};

struct scriptix_parse_jump {
	unsigned long loc;
	SXP_JUMP *next;
};

struct scriptix_parse_function {
	sx_name_id name;
	sx_name_id varg;
	sx_name_id* vars;
	SXP_NODE* body;
	Function* func;
	char *tag;
	char pub;
	SXP_FUNC *next;
};

struct scriptix_parse_info {
	System* system;
	SXP_NODE* nodes;
	SXP_FUNC *funcs;
	SXP_JUMP *returns;
	String* last_file;
	unsigned int last_line;
	String* file;
	unsigned int line;
	SXP_BLOCK *blocks;
	Array* globals;
	sx_name_id* gnames;
};

struct scriptix_parse_node {
	int type;
	SXP_INFO* info;
	SXP_NODE* next;
	SXP_NODE* inext;
	String* file;
	unsigned int line;
	union {
		struct {
			SXP_NODE* nodea; // nodes
			SXP_NODE* nodeb;
			SXP_NODE* nodec;
			SXP_NODE* noded;
		} nodes;
		struct {
			int op;
			SXP_NODE* left;
			SXP_NODE* right;
		} math;
		struct {
			SXP_NODE* left;
			SXP_NODE* right;
		} logic;
		struct {
			SXP_NODE* expr;
			SXP_NODE* args;
		} call;
		struct {
			sx_name_id name;
			SXP_NODE* node;
		} assi;
		struct {
			SXP_NODE* test;
			SXP_NODE* th;
			SXP_NODE* el;
		} ifd;
		struct {
			SXP_NODE* test;
			SXP_NODE* block;
			int type;
		} whil;
		struct {
			SXP_NODE* index;
			SXP_NODE* array;
			SXP_NODE* node;
		} set;
		struct {
			SXP_NODE* index;
			SXP_NODE* array;
		} indx;
		struct {
			sx_name_id name;
			SXP_NODE* amount;
		} inc;
		struct {
			SXP_NODE* base;
			sx_name_id name;
			SXP_NODE* node;
		} meth;
		struct {
			SXP_NODE* node;
			sx_name_id name;
		} cast;
		struct {
			SXP_NODE* start;
			SXP_NODE* test;
			SXP_NODE* inc;
			SXP_NODE* body;
		} cfor;
		struct {
			sx_name_id type;
			sx_name_id func;
			SXP_NODE* args;
		} smet;
		struct {
			SXP_FUNC* func;
			SXP_NODE* args;
		} clos;
		sx_name_id name;
		Value* data;
		SXP_NODE* node;
		SXP_FUNC *func;
	} data;
};

struct _sxp_arg_list {
	sx_name_id *args;
	sx_name_id varg;
};

// error function
void sxp_error (SXP_INFO* info, const char *msg);

// create/destroy parser context
SXP_INFO* sxp_new_info (System* system);
void sxp_del_info (SXP_INFO* info);

// create/destroy functions
SXP_FUNC *sxp_new_func (SXP_INFO* info, sx_name_id name, sx_name_id* args, sx_name_id varg, SXP_NODE* body, const char *tag, char pub);
SXP_FUNC *sxp_new_anon_func (SXP_INFO* info, sx_name_id* args, sx_name_id varg, SXP_NODE* body);
void sxp_del_func (SXP_FUNC *func);

// get the index for a variable name (ret -1 on error)
long sxp_add_var (SXP_INFO* info, SXP_FUNC* func, sx_name_id id);
long sxp_get_var (SXP_INFO* info, SXP_FUNC* func, sx_name_id id);

// breaks/continues/returns (control)
SXP_JUMP *sxp_new_break (SXP_INFO* info, unsigned long loc);
SXP_JUMP *sxp_new_continue (SXP_INFO* info, unsigned long loc);
SXP_JUMP *sxp_new_return (SXP_INFO* info, unsigned long loc);
void sxp_do_returns (SXP_INFO* info, Function* func, unsigned long loc);

// block areas
SXP_BLOCK *sxp_push_block (SXP_INFO* info);
void sxp_pop_block (SXP_INFO* info, Function* func, unsigned long breakl, unsigned long contl);

// define global
void sxp_set_global (SXP_INFO* info, sx_name_id id, Value* value);
long sxp_get_global (SXP_INFO* info, sx_name_id id);

// crapola for parse tree creation - FIXME: *really* shouldn't need this much code...
extern SXP_NODE* sxp_new_math (SXP_INFO* info, int op, SXP_NODE* left, SXP_NODE* right);
extern SXP_NODE* sxp_new_data (SXP_INFO* info, Value* value);
extern SXP_NODE* sxp_new_nega (SXP_INFO* info, SXP_NODE* node);
extern SXP_NODE* sxp_new_nodet (SXP_INFO* info, SXP_NODE* node, int type);
#define sxp_new_not(i,n) sxp_new_nodet((i), (n),SXP_NOT)
extern SXP_NODE* sxp_new_logic (SXP_INFO* info, SXP_NODE* left, SXP_NODE* right, int type);
#define sxp_new_and(i,l,r) sxp_new_logic((i), (l),(r),SXP_AND)
#define sxp_new_or(i,l,r) sxp_new_logic((i), (l),(r),SXP_OR)
extern SXP_NODE* sxp_new_call (SXP_INFO* info, SXP_NODE* expr, SXP_NODE* args);
extern SXP_NODE* sxp_new_assi (SXP_INFO* info, sx_name_id name, SXP_NODE* node);
extern SXP_NODE* sxp_new_stmt (SXP_INFO* info, SXP_NODE* node);
extern SXP_NODE* sxp_new_if (SXP_INFO* info, SXP_NODE* test, SXP_NODE* th, SXP_NODE* el);
extern SXP_NODE* sxp_new_whil (SXP_INFO* info, SXP_NODE* test, SXP_NODE* block, int type);
extern SXP_NODE* sxp_new_set (SXP_INFO* info, SXP_NODE* array, SXP_NODE* index, SXP_NODE* value);
extern SXP_NODE* sxp_new_indx (SXP_INFO* info, SXP_NODE* array, SXP_NODE* index);
#define sxp_new_arry(i,n) sxp_new_nodet((i), (n),SXP_ARRY)
#define sxp_new_assc(i,n) sxp_new_nodet((i), (n),SXP_ASSC)
#define sxp_new_blok(i,n) sxp_new_nodet((i), (n),SXP_BLOK)
extern SXP_NODE* sxp_new_inc (SXP_INFO* info, sx_name_id name, SXP_NODE* amount, int type);
#define sxp_new_pric(i,n,a) sxp_new_inc((i), (n),(a),SXP_PRIC)
#define sxp_new_poic(i,n,a) sxp_new_inc((i), (n),(a),SXP_POIC)
extern SXP_NODE* sxp_new_retr (SXP_INFO* info, SXP_NODE* node);
extern SXP_NODE* sxp_new_brak (SXP_INFO* info);
extern SXP_NODE* sxp_new_meth (SXP_INFO* info, SXP_NODE* base, sx_name_id name, SXP_NODE* node);
extern SXP_NODE* sxp_new_smet (SXP_INFO* info, sx_name_id type, sx_name_id func, SXP_NODE* args);
extern SXP_NODE* sxp_new_cast (SXP_INFO* info, SXP_NODE* node, sx_name_id name);
extern SXP_NODE* sxp_new_for (SXP_INFO* info, sx_name_id name, SXP_NODE* node, SXP_NODE* body);
extern SXP_NODE* sxp_new_cfor (SXP_INFO* info, SXP_NODE* start, SXP_NODE* test, SXP_NODE* inc, SXP_NODE* body);
extern SXP_NODE* sxp_new_cont (SXP_INFO* info);
extern SXP_NODE* sxp_new_supr (SXP_INFO* info, SXP_NODE* args);
extern SXP_NODE* sxp_new_yeld (SXP_INFO* info);
#define sxp_new_in(i,v,b) sxp_new_logic((i), (v), (b), SXP_IN)
extern SXP_NODE* sxp_new_name_t (SXP_INFO* info, sx_name_id name, int type);
#define sxp_new_new(i,n) sxp_new_name_t ((i), (n), SXP_NEW)
#define sxp_new_look(i,n) sxp_new_name_t ((i), (n), SXP_LOOK)
extern SXP_NODE* sxp_new_afnc (SXP_INFO* info, SXP_FUNC* func);
extern SXP_NODE* sxp_new_clos (SXP_INFO* info, SXP_FUNC* func, SXP_NODE* args);

// create a new node
extern SXP_NODE* sxp_new_node (SXP_INFO* info, int op, SXP_NODE* nodea = NULL, SXP_NODE* nodeb = NULL, SXP_NODE* nodec = NULL, SXP_NODE* noded = NULL);
extern SXP_NODE* sxp_new_name (SXP_INFO* info, sx_name_id name);

// append a node to another node chain
extern SXP_NODE* sxp_append (SXP_NODE* base, SXP_NODE* add);

// compilation helpers
extern int sxp_compile (SXP_INFO* info); // byte-code generator
extern SXP_NODE* sxp_transform (SXP_NODE* node); // optimizer

// globals for during compilation
extern SXP_INFO* sxp_parser_info;
extern FILE *yyin;
extern const char *sxp_parser_inbuf;

// namelists
namespace Scriptix {
sx_name_id* sx_new_namelist (System* system, size_t argc, ...);
sx_name_id* sx_namelist_append (System* system, sx_name_id* list, sx_name_id id);
sx_name_id* sx_namelist_concat (System* system, sx_name_id* list, sx_name_id* list2);
size_t sx_sizeof_namelist (sx_name_id* list);
void sx_free_namelist (sx_name_id* list);
}

#endif
