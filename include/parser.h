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

#ifndef __SXPARSER_H__
#define __SXPARSER_H__

#define SXP_MATH 1
#define SXP_DATA 2
#define SXP_NEGA 3
#define SXP_NOT  4
#define SXP_AND  5
#define SXP_OR   6
#define SXP_CALL 7
#define SXP_NAME 8
#define SXP_ASSI 9
#define SXP_STMT 10
#define SXP_IF   11
#define SXP_WHIL 12
#define SXP_SET  13
#define SXP_INDX 14
#define SXP_ARRY 15
#define SXP_SETM 16
#define SXP_GETM 17
#define SXP_PRIC 18
#define SXP_POIC 19
#define SXP_RETR 20
#define SXP_BRAK 21
#define SXP_METH 22
#define SXP_MEMB 23
#define SXP_NEWC 24
#define SXP_DEFC 25
#define SXP_ISA  26
#define SXP_RAIS 27
#define SXP_TRY  28
#define SXP_FOR  29
#define SXP_CFOR 30
#define SXP_CONT 31
#define SXP_SMET 32

#define SXP_W_WD 1
#define SXP_W_DW 2
#define SXP_W_DU 3
#define SXP_W_UD 4

typedef struct scriptix_parse_node SXP_NODE;
typedef struct scriptix_parse_info SXP_INFO;
typedef struct scriptix_parse_class SXP_CLASS;
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
	SX_ARRAY *args;
	SXP_NODE *body;
	SXP_FUNC *next;
};

struct scriptix_parse_class {
	SXP_INFO *info;
	sx_name_id name;
	sx_name_id parent;
	SXP_FUNC *methods;
	SXP_FUNC *static_methods;
	SXP_CLASS *next;
};

struct scriptix_parse_info {
	SX_SYSTEM *system;
	SXP_NODE *nodes;
	SXP_CLASS *classes;
	SXP_FUNC *funcs;
	SXP_JUMP *returns;
	SX_VALUE *last_file;
	unsigned int last_line;
	SX_VALUE *file;
	unsigned int line;
	SXP_BLOCK *blocks;
};

struct scriptix_parse_node {
	int type;
	SXP_INFO *info;
	SXP_NODE *next;
	SXP_NODE *inext;
	SX_VALUE *file;
	unsigned int line;
	union {
		struct {
			int op;
			SXP_NODE *left;
			SXP_NODE *right;
		} math;
		struct {
			SXP_NODE *left;
			SXP_NODE *right;
		} logic;
		struct {
			sx_name_id name;
			SXP_NODE *args;
		} call;
		struct {
			sx_name_id name;
			int scope;
		} name;
		struct {
			sx_name_id name;
			int scope;
			SXP_NODE *node;
		} assi;
		struct {
			SXP_NODE *test;
			SXP_NODE *th;
			SXP_NODE *el;
		} ifd;
		struct {
			SXP_NODE *test;
			SXP_NODE *block;
			int type;
		} whil;
		struct {
			SXP_NODE *index;
			SXP_NODE *array;
			SXP_NODE *node;
		} set;
		struct {
			SXP_NODE *index;
			SXP_NODE *array;
		} indx;
		struct {
			SXP_NODE *base;
			sx_name_id name;
			SXP_NODE *node;
		} setm;
		struct {
			SXP_NODE *base;
			sx_name_id name;
		} getm;
		struct {
			sx_name_id name;
			SXP_NODE *amount;
		} inc;
		struct {
			SXP_NODE *base;
			sx_name_id name;
			SXP_NODE *node;
		} klass;
		struct {
			SXP_NODE *node;
			sx_name_id name;
		} isa;
		struct {
			sx_name_id name;
			SXP_NODE *node;
		} rais;
		struct {
			SX_VALUE *names;
			SXP_NODE *body;
			SXP_NODE *rescue;
		} tryd;
		struct {
			sx_name_id name;
			SXP_NODE *node;
			SXP_NODE *body;
		} ford;
		struct {
			SXP_NODE *start;
			SXP_NODE *test;
			SXP_NODE *inc;
			SXP_NODE *body;
		} cfor;
		struct {
			sx_name_id klass;
			sx_name_id func;
			SXP_NODE *args;
		} smet;
		SX_VALUE *data;
		SXP_NODE *node;
	} data;
};

void sxp_error (SXP_INFO *info, const char *msg);

SXP_INFO *sxp_new_info (SX_SYSTEM *system);
void sxp_del_info (SXP_INFO *info);

SXP_CLASS *sxp_new_class (SXP_INFO *info, sx_name_id name, sx_name_id parent);
void sxp_add_method (SXP_CLASS *klass, sx_name_id name, SX_ARRAY *args, SXP_NODE *body);
void sxp_add_static_method (SXP_CLASS *klass, sx_name_id name, SX_ARRAY *args, SXP_NODE *body);
void sxp_del_class (SXP_CLASS *klass);

SXP_FUNC *sxp_new_func (SXP_INFO *info, sx_name_id name, SX_ARRAY *args, SXP_NODE *body);
void sxp_del_func (SXP_FUNC *func);

SXP_JUMP *sxp_new_break (SXP_INFO *info, unsigned long loc);
SXP_JUMP *sxp_new_continue (SXP_INFO *info, unsigned long loc);
SXP_JUMP *sxp_new_return (SXP_INFO *info, unsigned long loc);
void sxp_do_returns (SXP_INFO *info, SX_BLOCK *block, unsigned long loc);

SXP_BLOCK *sxp_push_block (SXP_INFO *info);
void sxp_pop_block (SXP_INFO *info, SX_BLOCK *block, unsigned long breakl, unsigned long contl);

extern SXP_NODE *sxp_new_math (SXP_INFO *info, int op, SXP_NODE *left, SXP_NODE *right);
extern SXP_NODE *sxp_new_data (SXP_INFO *info, SX_VALUE *value);
extern SXP_NODE *sxp_new_nodet (SXP_INFO *info, SXP_NODE *node, int type);
#define sxp_new_nega(i,n) sxp_new_nodet((i), (n),SXP_NEGA)
#define sxp_new_not(i,n) sxp_new_nodet((i), (n),SXP_NOT)
extern SXP_NODE *sxp_new_logic (SXP_INFO *info, SXP_NODE *left, SXP_NODE *right, int type);
#define sxp_new_and(i,l,r) sxp_new_logic((i), (l),(r),SXP_AND)
#define sxp_new_or(i,l,r) sxp_new_logic((i), (l),(r),SXP_OR)
extern SXP_NODE *sxp_new_call (SXP_INFO *info, sx_name_id name, SXP_NODE *args);
extern SXP_NODE *sxp_new_name (SXP_INFO *info, sx_name_id name, int scope);
extern SXP_NODE *sxp_new_assi (SXP_INFO *info, sx_name_id name, int scope, SXP_NODE *node);
extern SXP_NODE *sxp_new_stmt (SXP_INFO *info, SXP_NODE *node);
extern SXP_NODE *sxp_new_if (SXP_INFO *info, SXP_NODE *test, SXP_NODE *th, SXP_NODE *el);
extern SXP_NODE *sxp_new_whil (SXP_INFO *info, SXP_NODE *test, SXP_NODE *block, int type);
extern SXP_NODE *sxp_new_set (SXP_INFO *info, SXP_NODE *array, SXP_NODE *index, SXP_NODE *value);
extern SXP_NODE *sxp_new_indx (SXP_INFO *info, SXP_NODE *array, SXP_NODE *index);
#define sxp_new_arry(i,n) sxp_new_nodet((i), (n),SXP_ARRY)
#define sxp_new_blok(i,n) sxp_new_nodet((i), (n),SXP_BLOK)
extern SXP_NODE *sxp_new_setm (SXP_INFO *info, SXP_NODE *base, sx_name_id name, SXP_NODE *value);
extern SXP_NODE *sxp_new_getm (SXP_INFO *info, SXP_NODE *base, sx_name_id name);
extern SXP_NODE *sxp_new_inc (SXP_INFO *info, sx_name_id name, SXP_NODE *amount, int type);
#define sxp_new_pric(i,n,a) sxp_new_inc((i), (n),(a),SXP_PRIC)
#define sxp_new_poic(i,n,a) sxp_new_inc((i), (n),(a),SXP_POIC)
extern SXP_NODE *sxp_new_retr (SXP_INFO *info, SXP_NODE *node);
extern SXP_NODE *sxp_new_brak (SXP_INFO *info);
extern SXP_NODE *sxp_new_klass (SXP_INFO *info, SXP_NODE *base, sx_name_id name, SXP_NODE *node, int type);
#define sxp_new_meth(i,b,n,a) sxp_new_klass ((i), (b), (n), (a), SXP_METH)
#define sxp_new_memb(i,b,n) sxp_new_klass ((i), (b), (n), NULL, SXP_MEMB)
#define sxp_new_newc(i,n,a) sxp_new_klass ((i), NULL, (n), (a), SXP_NEWC)
extern SXP_NODE *sxp_new_smet (SXP_INFO *info, sx_name_id klass, sx_name_id func, SXP_NODE *args);
extern SXP_NODE *sxp_new_isa (SXP_INFO *info, SXP_NODE *node, sx_name_id name);
extern SXP_NODE *sxp_new_rais (SXP_INFO *info, sx_name_id name, SXP_NODE *node);
extern SXP_NODE *sxp_new_try (SXP_INFO *info, SX_VALUE *names, SXP_NODE *body, SXP_NODE *rescue);
extern SXP_NODE *sxp_new_for (SXP_INFO *info, sx_name_id name, SXP_NODE *node, SXP_NODE *body);
extern SXP_NODE *sxp_new_cfor (SXP_INFO *info, SXP_NODE *start, SXP_NODE *test, SXP_NODE *inc, SXP_NODE *body);
extern SXP_NODE *sxp_new_cont (SXP_INFO *info);

extern SXP_NODE *sxp_append (SXP_NODE *base, SXP_NODE *add);

extern int sxp_compile (SXP_INFO *info);

#endif
