/*
 * Scriptix - Lite-weight scripting interface
 * Copyright (c) 2002, 2003, 2004  AwesomePlay Productions, Inc.
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

#include <string>
#include <list>
#include <vector>

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
	SXP_PREOP,
	SXP_POSTOP,
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
	SXP_STRINGCAST,
	SXP_INTCAST,
	SXP_COPY,
};

enum {
	SXP_LOOP_WHILE,
	SXP_LOOP_DOWHILE,
	SXP_LOOP_UNTIL,
	SXP_LOOP_DOUNTIL,
	SXP_LOOP_FOREVER,
};

namespace Scriptix {

typedef GC::vector<NameID> NameList;

struct ParserBlock : public GC::Collectable {
	Function* func;
	unsigned long start;
	std::vector<unsigned long> breaks;
	std::vector<unsigned long> continues;
};

struct ParserFunction : public GC::Collectable {
	NameID name;
	NameID varg;
	NameList vars;
	struct ParserNode* body;
	Function* func;
	NameID tag;
	bool pub;
	bool staticm; // for extend methods only
};

struct ParserExtend : public GC::Collectable {
	Type* type;
	typedef GC::vector<ParserFunction*> MethodList;
	MethodList methods;
};

class ParserState : public GC::Collectable
{
	public: // FIXME
	System* system;
	ParserNode* nodes;
	typedef GC::list<ParserFunction*> FunctionList;
	FunctionList funcs;
	typedef GC::vector<ParserExtend*> ExtendList;
	ExtendList extends;
	typedef GC::vector<Type*> TypeList;
	TypeList types;
	typedef std::vector<unsigned long> ReturnList;
	ReturnList returns;
	String* last_file;
	size_t last_line;
	String* file;
	size_t line;
	typedef GC::list<ParserBlock*> BlockList;
	BlockList blocks;
	Array* globals;
	NameList gnames;
	SecurityLevel access;

	// compiler helopers
	bool CompileNode (ParserFunction* func, ParserNode* node);
	// block areas
	bool PushBlock (Function* func);
	void PopBlock (void);
	bool AddBreak (void);
	bool AddBreakOnFalse (void);
	bool AddBreakOnTrue (void);
	bool AddContinue (void);
	long BlockStart (void) { return blocks.front()->start; }

	public:
	ParserState (System* s_system);
	~ParserState (void);

	// basics
	inline System* GetSystem(void) const { return system; }

	// building trees/input
	inline void SetFile(const std::string& path) { file = new String(system, path); line = 1; }
	inline void SetLine(size_t lineno) { line = lineno; }
	inline void LineIncr(void) { ++line; }
	inline String* GetFile(void) const { return file; }
	inline size_t GetLine(void) const { return line; }
	inline void SetAccess(SecurityLevel s_access) { access = s_access; }

	// compile
	int Compile(void);

	// error function
	void Error(const std::string& msg);

	// get the index for a variable name (ret -1 on error)
	long AddVar(ParserFunction* func, NameID id);
	long GetVar(ParserFunction* func, NameID id);

	// define global
	void SetGlobal(NameID id, Value* value);
	long GetGlobal(NameID id);

	// add functions
	ParserFunction* AddFunc(NameID name, const NameList& args, NameID varg, ParserNode* body, NameID tag, bool pub);

	// type extends
	ParserExtend* AddExtend(Type* type);
	ParserFunction* AddExtendFunc(NameID name, const NameList& args, NameID varg, ParserNode* body, bool staticm);

	// new types
	Type* AddType(NameID name, const Type* parent);
	ParserFunction* AddTypeFunc(NameID name, const NameList& args, NameID varg, ParserNode* body);
	Type* GetType(NameID name);
};

struct ParserNode : public GC::Collectable {
	int type;
	Scriptix::ParserState* info;
	ParserNode* next;
	ParserNode* inext;
	String* file;
	unsigned int line;
	struct {
		ParserNode* nodes[4];
		NameID name;
		Type* type;
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
		NameID name,
		Type* type,
		Value* value,
		int op);
	// append a new node to the list
	ParserNode* Append(ParserNode* node);
};

// Node types
#define sxp_new_set_member(info,base,name,value) (new ParserNode((info), SXP_SETMEMBER, (base), (value), NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_get_member(info,base,name) (new ParserNode((info), SXP_GETMEMBER, (base), NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_continue(info) (new ParserNode((info), SXP_CONTINUE, NULL, NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_break(info) (new ParserNode((info), SXP_BREAK, NULL, NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_yield(info) (new ParserNode((info), SXP_YIELD, NULL, NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_return(info,value) (new ParserNode((info), SXP_RETURN, (value), NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_lookup(info,name) (new ParserNode((info), SXP_LOOKUP, NULL, NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_new(info,type,args,call) (new ParserNode((info), SXP_NEW, (args), NULL, NULL, NULL, 0, (type), NULL, (call)))
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
#define sxp_new_smethod(info,type,name,args) (new ParserNode((info), SXP_SMETHOD, (args), NULL, NULL, NULL, (name), (type), NULL, 0))
#define sxp_new_and(info,left,right) (new ParserNode((info), SXP_AND, (left), (right), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_or(info,left,right) (new ParserNode((info), SXP_OR, (left), (right), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_in(info,node,list) (new ParserNode((info), SXP_IN, (node), (list), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_invoke(info,node,args) (new ParserNode((info), SXP_INVOKE, (node), (args), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_setindex(info,list,index,value) (new ParserNode((info), SXP_SETINDEX, (list), (index), (value), NULL, 0, 0, NULL, 0))
#define sxp_new_getindex(info,list,index) (new ParserNode((info), SXP_GETINDEX, (list), (index), NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_assign(info,name,value) (new ParserNode((info), SXP_ASSIGN, (value), NULL, NULL, NULL, (name), 0, NULL, 0))
#define sxp_new_cast(info,type,node) (new ParserNode((info), SXP_CAST, (node), NULL, NULL, NULL, 0, (type), NULL, 0))
#define sxp_new_preop(info,expr,op,value) (new ParserNode((info), SXP_PREOP, (expr), (value), NULL, NULL, 0, 0, NULL, (op)))
#define sxp_new_postop(info,expr,op,value) (new ParserNode((info), SXP_POSTOP, (expr), (value), NULL, NULL, 0, 0, NULL, (op)))
#define sxp_new_negate(info,node) (new ParserNode((info), SXP_NEGATE, (node), NULL, NULL, NULL, 0, 0, NULL, 0))
#define sxp_new_copy(info,loc) (new ParserNode((info), SXP_COPY, NULL, NULL, NULL, NULL, 0, 0, NULL, (loc)))

// compilation helpers
extern ParserNode* sxp_transform (ParserNode* node); // optimizer

}

// globals for during compilation - yay stupid yacc/lex
struct ParserArgList {
	NameList* args;
	NameID varg;
};

extern Scriptix::ParserState* parser;
extern FILE* yyin;
extern const char* sxp_parser_inbuf;

#endif
