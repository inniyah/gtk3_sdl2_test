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

#include <list>

enum {
	SXP_NOOP = 0,
	SXP_MATH,
	SXP_DATA,
	SXP_NEGATE,
	SXP_NOT,
	SXP_AND,
	SXP_OR,
	SXP_INVOKE,
	SXP_LOOKUP,
	SXP_ASSIGN,
	SXP_STATEMENT,
	SXP_IF,
	SXP_LOOP,
	SXP_SETINDEX,
	SXP_GETINDEX,
	SXP_ARRAY,
	SXP_PREINC,
	SXP_POSTINC,
	SXP_RETURN,
	SXP_BREAK,
	SXP_METHOD,
	SXP_CAST,
	SXP_FOR,
	SXP_CONTINUE,
	SXP_SMETHOD,
	SXP_YIELD,
	SXP_IN,
	SXP_NEW,
	SXP_SETMEMBER,
	SXP_GETMEMBER,
	SXP_FOREACH,
	SXP_CONCAT,
};

enum {
	SXP_LOOP_WHILE,
	SXP_LOOP_DOWHILE,
	SXP_LOOP_UNTIL,
	SXP_LOOP_DOUNTIL,
	SXP_LOOP_FOREVER,
};

struct ParserBlock {
	Function* func;
	unsigned long start;
	std::list<unsigned long> breaks;
	std::list<unsigned long> continues;
	ParserBlock* next;
};

struct ParserFunction {
	sx_name_id name;
	sx_name_id varg;
	sx_name_id* vars;
	struct ParserNode* body;
	Function* func;
	char* tag;
	char pub;
	ParserFunction* next;
};

namespace Scriptix {
class ParserState
{
	public: // FIXME
	System* system;
	ParserNode* nodes;
	ParserFunction* funcs;
	std::list<unsigned long> returns;
	String* last_file;
	size_t last_line;
	String* file;
	size_t line;
	ParserBlock* blocks;
	Array* globals;
	sx_name_id* gnames;

	// compiler helopers
	bool CompileNode (ParserFunction* func, ParserNode* node);
	// block areas
	bool PushBlock (Function* func);
	void PopBlock (void);
	bool AddBreak (void);
	bool AddBreakOnFalse (void);
	bool AddBreakOnTrue (void);
	bool AddContinue (void);
	long BlockStart (void) { return blocks->start; }

	public:
	ParserState (System* s_system);
	~ParserState (void);

	// basics
	System* GetSystem(void) const { return system; }

	// building trees/input
	void SetFile(const char* path) { file = new String(system, path); line = 1; }
	void LineIncr(void) { ++line; }
	String* GetFile(void) const { return file; }
	size_t GetLine(void) const { return line; }

	// compile
	int Compile(void);

	// error function
	void Error(const char* msg);

	// get the index for a variable name (ret -1 on error)
	long AddVar(ParserFunction* func, sx_name_id id);
	long GetVar(ParserFunction* func, sx_name_id id);

	// define global
	void SetGlobal(sx_name_id id, Value* value);
	long GetGlobal(sx_name_id id);

	// add functions
	ParserFunction* AddFunc(sx_name_id name, sx_name_id* args, sx_name_id varg, ParserNode* body, const char* tag, char pub);
	void DelFunc(ParserFunction* func);
};
}

struct ParserNode {
	int type;
	Scriptix::ParserState* info;
	ParserNode* next;
	ParserNode* inext;
	String* file;
	unsigned int line;
	struct {
		ParserNode* nodes[4];
		sx_name_id names[2];
		Value* value;
		int op;
	} parts;

	// create new node
	ParserNode(Scriptix::ParserState* info,
		int type,
		ParserNode* node1,
		ParserNode* node2,
		ParserNode* node3,
		ParserNode* node4,
		sx_name_id name1,
		sx_name_id name2,
		Value* value,
		int op);
	// append a new node to the list
	ParserNode* Append(ParserNode* node);
};

struct _sxp_arg_list {
	sx_name_id* args;
	sx_name_id varg;
};

// Node types
#define sxp_new_set_member(info,base,name,value) (new ParserNode((info), SXP_SETMEMBER, (base), (value), NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_get_member(info,base,name) (new ParserNode((info), SXP_GETMEMBER, (base), NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_continue(info) (new ParserNode((info), SXP_CONTINUE, NULL, NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_break(info) (new ParserNode((info), SXP_BREAK, NULL, NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_yield(info) (new ParserNode((info), SXP_YIELD, NULL, NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_return(info,value) (new ParserNode((info), SXP_RETURN, (value), NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_lookup(info,name) (new ParserNode((info), SXP_LOOKUP, NULL, NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_new(info,name) (new ParserNode((info), SXP_NEW, NULL, NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_math(info,op,left,right) (new ParserNode((info), SXP_MATH, (left), (right), NULL, NULL, 0, 0, NULL, (op)))
#define sxp_new_data(info,data) (new ParserNode((info), SXP_DATA, NULL, NULL, NULL, NULL, 0, 0, (data), 0))
#define sxp_new_loop(info,type,test,body) (new ParserNode((info), SXP_LOOP, (test), (body), NULL, NULL, 0, 0, NULL, (type)))
#define sxp_new_if(info,test,then,els) (new ParserNode((info), SXP_IF, (test), (then), (els), NULL, 0, 0, NULL, 0))
#define sxp_new_for(info,start,test,inc,body) (new ParserNode((info), SXP_FOR, (start), (test), (inc), (body), 0, 0, NULL, 0))
#define sxp_new_foreach(info,name,list,body) (new ParserNode((info), SXP_FOREACH, (list), (body), NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_statement(info,node) (new ParserNode((info), SXP_STATEMENT, (node), NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_not(info,node) (new ParserNode((info), SXP_NOT, (node), NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_array(info,node) (new ParserNode((info), SXP_ARRAY, (node), NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_method(info,obj,name,args) (new ParserNode((info), SXP_METHOD, (obj), (args), NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_smethod(info,type,name,args) (new ParserNode((info), SXP_SMETHOD, (args), NULL, NULL, NULL, (type), (name), NULL, 0))
#define sxp_new_and(info,left,right) (new ParserNode((info), SXP_AND, (left), (right), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_or(info,left,right) (new ParserNode((info), SXP_OR, (left), (right), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_in(info,node,list) (new ParserNode((info), SXP_IN, (node), (list), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_invoke(info,node,args) (new ParserNode((info), SXP_INVOKE, (node), (args), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_setindex(info,list,index,value) (new ParserNode((info), SXP_SETINDEX, (list), (index), (value), NULL, 0, 0, NULL, 0))
#define sxp_new_getindex(info,list,index) (new ParserNode((info), SXP_GETINDEX, (list), (index), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_assign(info,name,value) (new ParserNode((info), SXP_ASSIGN, (value), NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_cast(info,type,node) (new ParserNode((info), SXP_CAST, (node), NULL, NULL, NULL, (type), 0, NULL, 0))
#define sxp_new_preinc(info,name,amount) (new ParserNode((info), SXP_PREINC, (amount), NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_postinc(info,name,amount) (new ParserNode((info), SXP_POSTINC, (amount), NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_negate(info,node) (new ParserNode((info), SXP_NEGATE, (node), NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_concat(info,left,right) (new ParserNode((info), SXP_CONCAT, (left), (right), NULL, NULL, 0, 0, NULL, 0))

// compilation helpers
extern ParserNode* sxp_transform (ParserNode* node); // optimizer

// globals for during compilation - yay stupid yacc/lex
extern Scriptix::ParserState* parser;
extern FILE* yyin;
extern const char* sxp_parser_inbuf;

// namelists
namespace Scriptix {
	sx_name_id* sx_new_namelist (System* system, size_t argc, ...);
	sx_name_id* sx_namelist_append (System* system, sx_name_id* list, sx_name_id id);
	sx_name_id* sx_namelist_concat (System* system, sx_name_id* list, sx_name_id* list2);
	size_t sx_sizeof_namelist (sx_name_id* list);
	void sx_free_namelist (sx_name_id* list);
}

#endif
