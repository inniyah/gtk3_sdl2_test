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

#ifndef SCRIPTIX_H
#define SCFIPTIX_H

#ifdef __cplusplus__
extern "C" {
#endif

#define SX_DATA_CHUNK 50
#define SX_CONTEXT_CHUNK 10
#define SX_BLOCK_CHUNK 10
#define SX_GC_THRESH 200

#ifndef __INLINE__
#ifdef __GNUC__
	#define __INLINE__ inline
#else
	#define __INLINE__
#endif /* __GNUC__ */
#endif /* __INLINE__ */

#define SX_MAX_NAME 128

#define SX_VALUE_NIL 0
#define SX_VALUE_NUM 1
#define SX_VALUE_STRING 2
#define SX_VALUE_BLOCK 3
#define SX_VALUE_FUNC 4
#define SX_VALUE_ARRAY 5
#define SX_VALUE_CLASS 6
#define SX_VALUE_RANGE 7

#define SX_OP_NIL 0
#define SX_OP_ADD 1
#define SX_OP_SUBTRACT 2
#define SX_OP_NEGATE 3
#define SX_OP_CALL 4
#define SX_OP_MULTIPLY 5
#define SX_OP_DIVIDE 6
#define SX_OP_GT 7
#define SX_OP_LT 8
#define SX_OP_GTE 9
#define SX_OP_LTE 10
#define SX_OP_EQUAL 11
#define SX_OP_NEQUAL 12
#define SX_OP_NOT 13
#define SX_OP_LOOKUP 14
#define SX_OP_ASSIGN 15
#define SX_OP_INDEX 16
#define SX_OP_PREINCREMENT 17
#define SX_OP_POSTINCREMENT 18
#define SX_OP_PREDECREMENT 19
#define SX_OP_POSTDECREMENT 20
#define SX_OP_NEWARRAY 21
#define SX_OP_SETINDEX 22
#define SX_OP_SIZEOF 23
#define SX_OP_NEWCLASS 24
#define SX_OP_SETMEMBER 25
#define SX_OP_MEMBER 26
#define SX_OP_NEWINSTANCE 27
#define SX_OP_ISA 28
#define SX_OP_TYPEOF 29
#define SX_OP_EVAL 30
#define SX_OP_NEWFUNC 31
#define SX_OP_METHOD 32
#define SX_OP_NEWRANGE 33

#define SX_OP_FOR 100
#define SX_OP_IF 101
#define SX_OP_WHILE 102
#define SX_OP_BREAK 103
#define SX_OP_RETURN 104
#define SX_OP_RAISE 105
#define SX_OP_OR 106
#define SX_OP_AND 107
#define SX_OP_TRY 108
#define SX_OP_STMT 109
#define SX_OP_UNTIL 110
#define SX_OP_DOWHILE 111
#define SX_OP_DOUNTIL 112
#define SX_OP_JUMP 113

	/* value flags */
#define SX_VFLAG_MARK 0x01
#define SX_VFLAG_CONST 0x02

	/* system flags */
#define SX_SFLAG_GCOFF 0x01

	/* call flags */
#define SX_CFLAG_VARS 0x01
#define SX_CFLAG_HARD 0x03 /* force to include VARS */

	/* variable flags */
#define SX_RFLAG_CONST 0x01

#define SX_STATE_READY 0
#define SX_STATE_RUN 1
#define SX_STATE_BREAK 2
#define SX_STATE_RETURN 3
#define SX_STATE_EXIT 4
#define SX_STATE_ERROR 5
#define SX_STATE_SWITCH 6

#define SX_SCOPE_DEF 0
#define SX_SCOPE_LOCAL 1
#define SX_SCOPE_CLASS 2
#define SX_SCOPE_GLOBAL 3

#define SX_NUM_MARK 0x01

typedef struct scriptix_value SX_VALUE;
typedef struct scriptix_var SX_VAR;
typedef struct scriptix_call SX_CALL;
typedef struct scriptix_system SX_SYSTEM;
typedef struct scriptix_thread SX_THREAD;
typedef struct scriptix_script SX_SCRIPT;

typedef unsigned int sx_id;
typedef unsigned int sx_script_id;
typedef void (*sx_gc_hook)(SX_SYSTEM *system);

extern __INLINE__ void *sx_malloc (SX_SYSTEM *system, unsigned long size);
extern __INLINE__ void *sx_dupmem (SX_SYSTEM *system, void *mem, unsigned long size);
#define sx_free free

#define sx_new_nil() ((SX_VALUE *)(NULL))
#define sx_new_num(i) ((SX_VALUE *)(((i) << 1) | SX_NUM_MARK))
#define SX_TOINT(n) ((long)(n) >> 1)
#define SX_TOSTR(s) ((s)->data.str.str)
extern SX_VALUE *sx_new_str (SX_SYSTEM *system, char *str);
extern SX_VALUE *sx_new_str_len (SX_SYSTEM *system, char *str, unsigned int len);
extern SX_VALUE *sx_new_block (SX_SYSTEM *system);
extern SX_VALUE *sx_add_to_block (SX_SYSTEM *system, SX_VALUE *block, SX_VALUE *balue, int op);
#define sx_add_value(s,b,v) (sx_add_to_block ((s), (b), (v), 0))
#define sx_add_stmt(s,b,o) (sx_add_to_block ((s), (b), NULL, (o)))
extern SX_VALUE *sx_new_func (SX_SYSTEM *system, SX_VALUE *args, SX_VALUE *body);
extern SX_VALUE *sx_new_cfunc (SX_SYSTEM *system, SX_VALUE *(*func)(SX_THREAD *, SX_VALUE *, unsigned int, unsigned int));
extern SX_VALUE *sx_new_array (SX_SYSTEM *system, unsigned int argc, SX_VALUE **argv);
extern SX_VALUE *sx_new_stack_array (SX_THREAD *thread, unsigned int argc, unsigned int top);
extern SX_VALUE *sx_new_range (SX_SYSTEM *system, int start, int end);
extern SX_VALUE *sx_copy_value (SX_SYSTEM *system, SX_VALUE *value);
extern __INLINE__ void sx_mark_value (SX_SYSTEM *system, SX_VALUE *value);
extern int sx_is_true (SX_VALUE *value);
extern int sx_are_equal (SX_VALUE *one, SX_VALUE *two);
extern int sx_compare (SX_VALUE *one, SX_VALUE *two);
extern void sx_print_value (SX_VALUE *value);
extern __INLINE__ void sx_lock_value (SX_VALUE *value);
extern __INLINE__ void sx_unlock_value (SX_VALUE *value);
extern SX_VALUE *sx_get_index (SX_SYSTEM *system, SX_VALUE *cont, int index);
extern SX_VALUE *sx_get_section (SX_SYSTEM *system, SX_VALUE *cont, int start, int end);
extern void sx_free_value (SX_VALUE *value);

extern SX_VALUE *sx_new_class (SX_SYSTEM *system, SX_VALUE *parent);
extern SX_VALUE *sx_new_user_class (SX_SYSTEM *system, SX_VALUE *parent, void *data, void (*free_data)(void *data), void (*ref_data)(SX_SYSTEM *system, void *data));
extern int sx_class_is_a (SX_VALUE *klass, SX_VALUE *par);
extern SX_VAR *sx_set_member (SX_SYSTEM *system, SX_VALUE *klass, sx_id id, SX_VALUE *value);
extern SX_VALUE *sx_get_member (SX_VALUE *klass, sx_id id);
extern SX_VAR *sx_find_member (SX_VALUE *klass, sx_id id);

extern sx_id sx_parent_id;
extern sx_id sx_self_id;
extern sx_id sx_init_id;
extern sx_id sx_error_id;
extern sx_id sx_etype_id;
extern sx_id sx_estack_id;
extern sx_id sx_ename_id;

#define sx_type_of(v) ((v) == (NULL) ? SX_VALUE_NIL : ((long)(v) & SX_NUM_MARK) ? SX_VALUE_NUM : (v)->type)
#define SX_ISNIL(v) ((v) == NULL)
#define SX_ISNUM(v) ((long)(v) & SX_NUM_MARK)
#define SX_ISSTRING(v) ((sx_type_of ((v))) == SX_VALUE_STRING)
#define SX_ISBLOCK(v) ((sx_type_of ((v))) == SX_VALUE_BLOCK)
#define SX_ISFUNC(v) ((sx_type_of ((v))) == SX_VALUE_FUNC)
#define SX_ISARRAY(v) ((sx_type_of ((v))) == SX_VALUE_ARRAY)
#define SX_ISCLASS(v) ((sx_type_of ((v))) == SX_VALUE_CLASS)
#define SX_ISRANGE(v) ((sx_type_of ((v))) == SX_VALUE_RANGE)

extern int sx_eval (SX_THREAD *thread, unsigned int max);

extern SX_VALUE *sx_define_cfunc (SX_SYSTEM *system, char *name, SX_VALUE *(*func)(SX_THREAD *, SX_VALUE *, unsigned int, unsigned int));

extern SX_VALUE *sx_define_var (SX_THREAD *thread, unsigned int id, SX_VALUE *value, int scope);
extern SX_VALUE *sx_define_system_var (SX_SYSTEM *system, unsigned int id, SX_VALUE *value);
extern SX_VAR *sx_get_var (SX_THREAD *thread, unsigned int id, int scope);
extern SX_VAR *sx_get_system_var (SX_SYSTEM *system, unsigned int id);
#define sx_free_var(v) sx_free ((v))

extern SX_SYSTEM *sx_create_system (int argc, char **argv);
extern __INLINE__ void sx_add_gc_value (SX_SYSTEM *system, SX_VALUE *value);
extern void sx_run_gc (SX_SYSTEM *system);
extern void sx_run (SX_SYSTEM *system, unsigned int max);
extern void sx_free_system (SX_SYSTEM *system);
extern sx_script_id sx_add_script (SX_SYSTEM *system, SX_SCRIPT *script);

extern sx_script_id sx_load_file (SX_SYSTEM *system, char *file);

extern SX_THREAD *sx_start_thread (SX_SYSTEM *system, sx_script_id);
extern SX_THREAD *sx_create_thread (SX_SYSTEM *system, SX_VALUE *main);
extern int sx_run_thread (SX_THREAD *thread, unsigned int max);
extern __INLINE__ void sx_mark_thread (SX_THREAD *thread);
extern void sx_end_thread (SX_THREAD *thread);
extern void sx_free_thread (SX_THREAD *thread);
extern SX_THREAD *sx_push_call (SX_THREAD *thread, SX_VALUE *block, SX_VALUE *klass, unsigned char flags);
extern SX_THREAD *sx_pop_call (SX_THREAD *thread);
extern SX_VALUE *sx_push_value (SX_THREAD *thread, SX_VALUE *value);
extern __INLINE__ SX_VALUE *sx_get_value (SX_THREAD *thread, int);
extern __INLINE__ void sx_pop_value (SX_THREAD *thread, int start, unsigned int len);

extern unsigned int sx_name_to_id (const char *name);
extern const char *sx_id_to_name (unsigned int id);
extern void sx_init_ids (void);

/* standard library calls */
extern void sx_init_stdlib (SX_SYSTEM *system);

/* special struct for nodes */
struct _scriptix_node {
	int op;
	SX_VALUE *value;
};

struct scriptix_value {
	unsigned char type;
	unsigned char flags;
	unsigned int locks;
	SX_VALUE *gc_next;
	union {
		struct {
			unsigned int len;
			char str[0];
		} str;
		struct {
			SX_VALUE *args;
			SX_VALUE *body;
			SX_VALUE *(*cfunc)(SX_THREAD *, SX_VALUE *, unsigned int, unsigned int);
		} func;
		struct {
			SX_VALUE **list;
			unsigned int count;
			unsigned int size;
		} array;
		struct {
			SX_VALUE *parent;
			SX_VAR *members;
			void *data;
			void (*free_data)(void *data);
			void (*ref_data)(SX_SYSTEM *system, void *data);
		} klass;
		struct {
			int start;
			int end;
		} range;
		struct {
			struct _scriptix_node *nodes;
			unsigned int count;
			unsigned int size;
		} block;
	} data;
};

struct scriptix_var {
	unsigned char flags;
	unsigned int id;
	SX_VALUE *value;
	SX_VAR *next;
};

struct scriptix_call {
	SX_VALUE *block;
	SX_VALUE *stmt;
	SX_VAR *vars;
	SX_VALUE *klass;
	unsigned int op_ptr;
	unsigned int top;
	int state;
	unsigned char flags;
};

struct scriptix_script {
	sx_script_id id;
	char *name;
	char *path;
	SX_VALUE *block;
	SX_SCRIPT *next;
};

struct scriptix_system {
	SX_THREAD *threads;
	SX_SCRIPT *scripts;
	SX_VAR *vars;
	SX_VALUE *gc_values;
	sx_gc_hook gc_hook;
	unsigned char flags;
	unsigned int gc_count;
	unsigned int gc_thresh;
	unsigned int valid_threads;
};

struct scriptix_thread {
	SX_SYSTEM *system;
	SX_VALUE *main;
	SX_VALUE *ret;
	int state;

	SX_CALL *call_stack;
	unsigned int call;
	unsigned int call_size;
	SX_VALUE *cur_class; /* set by call stack */

	SX_VALUE **data_stack;
	unsigned int data;
	unsigned int data_size;

	SX_THREAD *next;
};

#ifdef __cplusplus__
} /* extern "C" */
#endif

#endif
