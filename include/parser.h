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

enum {
	SXP_NOOP = 0,
	SXP_MATH,
	SXP_DATA,
	SXP_NEGA,
	SXP_NOT,
	SXP_AND,
	SXP_OR,
	SXP_CALL,
	SXP_NAME,
	SXP_ASSI,
	SXP_STMT,
	SXP_IF,
	SXP_WHIL,
	SXP_SET,
	SXP_INDX,
	SXP_ARRY,
	SXP_PRIC,
	SXP_POIC,
	SXP_RETR,
	SXP_BRAK,
	SXP_METH,
	SXP_MEMB,
	SXP_DEFC,
	SXP_CAST,
	SXP_FOR,
	SXP_CFOR,
	SXP_CONT,
	SXP_SMET,
	SXP_SUPR,
	SXP_YELD,
	SXP_IN,
};

#define SXP_W_WD 1
#define SXP_W_DW 2
#define SXP_W_DU 3
#define SXP_W_UD 4

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
	SX_ARRAY args;
	sx_name_id varg;
	SXP_NODE *body;
	SXP_FUNC *next;
};

struct scriptix_parse_info {
	SX_SYSTEM system;
	SX_MODULE module;
	SXP_NODE *nodes;
	SXP_FUNC *funcs;
	SXP_JUMP *returns;
	SX_VALUE last_file;
	unsigned int last_line;
	SX_VALUE file;
	unsigned int line;
	SXP_BLOCK *blocks;
};

struct scriptix_parse_node {
	int type;
	SXP_INFO *info;
	SXP_NODE *next;
	SXP_NODE *inext;
	SX_VALUE file;
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
		} name;
		struct {
			sx_name_id name;
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
		} meth;
		struct {
			SXP_NODE *node;
			sx_name_id name;
		} cast;
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
			sx_name_id type;
			sx_name_id func;
			SXP_NODE *args;
		} smet;
		SX_VALUE data;
		SXP_NODE *node;
	} data;
};

struct _sxp_arg_list {
	SX_VALUE args;
	sx_name_id varg;
};

void sxp_error (SXP_INFO *info, const char *msg);

SXP_INFO *sxp_new_info (SX_MODULE module);
void sxp_del_info (SXP_INFO *info);

SXP_FUNC *sxp_new_func (SXP_INFO *info, sx_name_id name, SX_ARRAY args, sx_name_id varg, SXP_NODE *body);
void sxp_del_func (SXP_FUNC *func);

SXP_JUMP *sxp_new_break (SXP_INFO *info, unsigned long loc);
SXP_JUMP *sxp_new_continue (SXP_INFO *info, unsigned long loc);
SXP_JUMP *sxp_new_return (SXP_INFO *info, unsigned long loc);
void sxp_do_returns (SXP_INFO *info, SX_BLOCK block, unsigned long loc);

SXP_BLOCK *sxp_push_block (SXP_INFO *info);
void sxp_pop_block (SXP_INFO *info, SX_BLOCK block, unsigned long breakl, unsigned long contl);

extern SXP_NODE *sxp_new_math (SXP_INFO *info, int op, SXP_NODE *left, SXP_NODE *right);
extern SXP_NODE *sxp_new_data (SXP_INFO *info, SX_VALUE value);
extern SXP_NODE *sxp_new_nega (SXP_INFO *info, SXP_NODE *node);
extern SXP_NODE *sxp_new_nodet (SXP_INFO *info, SXP_NODE *node, int type);
#define sxp_new_not(i,n) sxp_new_nodet((i), (n),SXP_NOT)
extern SXP_NODE *sxp_new_logic (SXP_INFO *info, SXP_NODE *left, SXP_NODE *right, int type);
#define sxp_new_and(i,l,r) sxp_new_logic((i), (l),(r),SXP_AND)
#define sxp_new_or(i,l,r) sxp_new_logic((i), (l),(r),SXP_OR)
extern SXP_NODE *sxp_new_call (SXP_INFO *info, sx_name_id name, SXP_NODE *args);
extern SXP_NODE *sxp_new_name (SXP_INFO *info, sx_name_id name);
extern SXP_NODE *sxp_new_assi (SXP_INFO *info, sx_name_id name, SXP_NODE *node);
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
extern SXP_NODE *sxp_new_meth (SXP_INFO *info, SXP_NODE *base, sx_name_id name, SXP_NODE *node);
extern SXP_NODE *sxp_new_smet (SXP_INFO *info, sx_name_id type, sx_name_id func, SXP_NODE *args);
extern SXP_NODE *sxp_new_cast (SXP_INFO *info, SXP_NODE *node, sx_name_id name);
extern SXP_NODE *sxp_new_for (SXP_INFO *info, sx_name_id name, SXP_NODE *node, SXP_NODE *body);
extern SXP_NODE *sxp_new_cfor (SXP_INFO *info, SXP_NODE *start, SXP_NODE *test, SXP_NODE *inc, SXP_NODE *body);
extern SXP_NODE *sxp_new_cont (SXP_INFO *info);
extern SXP_NODE *sxp_new_supr (SXP_INFO *info, SXP_NODE *args);
extern SXP_NODE *sxp_new_yeld (SXP_INFO *info);
#define sxp_new_in(i,v,b) sxp_new_logic((i), (v), (b), SXP_IN)

extern SXP_NODE *sxp_append (SXP_NODE *base, SXP_NODE *add);

/* compilation helpers */
extern int sxp_compile (SXP_INFO *info);

/* globals for during compilation */
extern SXP_INFO *sxp_parser_info;
extern FILE *sxin;
extern const char *sxp_parser_inbuf;

#endif
