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
#define SX_VALUE_CFUNC 5
#define SX_VALUE_ARRAY 6
#define SX_VALUE_CLASS 7
#define SX_VALUE_RANGE 8

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
#define SX_OP_POP 109
#define SX_OP_UNTIL 110
#define SX_OP_DOWHILE 111
#define SX_OP_DOUNTIL 112

#define SX_VFLAG_MARK 0x01
#define SX_VFLAG_CONST 0x02

#define SX_SFLAG_GCOFF 0x01

#define SX_CFLAG_HARD 0x01

#define SX_STATE_READY 0
#define SX_STATE_RUN 1
#define SX_STATE_BREAK 2
#define SX_STATE_RETURN 3
#define SX_STATE_EXIT 4
#define SX_STATE_ERROR 5

#define SX_SCOPE_DEF 0
#define SX_SCOPE_LOCAL 1
#define SX_SCOPE_THREAD 2
#define SX_SCOPE_GLOBAL 3

#define SX_NUM_MARK 0x01

typedef struct scriptix_value VALUE;
typedef struct scriptix_node NODE;
typedef struct scriptix_var VAR;
typedef struct scriptix_context CONTEXT;
typedef struct scriptix_system SYSTEM;
typedef struct scriptix_thread THREAD;

extern __INLINE__ void *sx_malloc (SYSTEM *system, unsigned long size);
extern __INLINE__ void *sx_dupmem (SYSTEM *system, void *mem, unsigned long size);
#define sx_free free

#define sx_new_nil() ((VALUE *)(NULL))
#define sx_new_num(i) ((VALUE *)(((i) << 1) | SX_NUM_MARK))
#define SX_TOINT(n) ((long)(n) >> 1)
#define SX_TOSTR(s) ((s)->data.str.str)
extern VALUE *sx_new_str (SYSTEM *system, char *str);
extern VALUE *sx_new_str_len (SYSTEM *system, char *str, unsigned int len);
extern VALUE *sx_new_block (SYSTEM *system);
extern VALUE *sx_add_to_block (SYSTEM *system, VALUE *block, VALUE *balue, int op, unsigned int count);
#define sx_add_value(s,b,v) (sx_add_to_block ((s), (b), (v), 0, 0))
#define sx_add_stmt(s,b,o,c) (sx_add_to_block ((s), (b), NULL, (o), (c)))
extern VALUE *sx_new_func (SYSTEM *system, VALUE *args, VALUE *body);
extern VALUE *sx_new_cfunc (SYSTEM *system, VALUE *(*func)(THREAD *, VALUE *, unsigned int, unsigned int));
extern VALUE *sx_new_array (SYSTEM *system, unsigned int argc, VALUE **argv);
extern VALUE *sx_new_stack_array (THREAD *thread, unsigned int argc, unsigned int top);
extern VALUE *sx_new_class (SYSTEM *system, VALUE *parent);
extern VALUE *sx_new_user_class (SYSTEM *system, VALUE *parent, void *data, void (*free_data)(void *data), void (*ref_data)(SYSTEM *system, void *data));
extern VALUE *sx_new_range (SYSTEM *system, int start, int end);
extern VALUE *sx_copy_value (SYSTEM *system, VALUE *value);
extern __INLINE__ void sx_mark_value (SYSTEM *system, VALUE *value);
extern int sx_is_true (VALUE *value);
extern int sx_are_equal (VALUE *one, VALUE *two);
extern int sx_compare (VALUE *one, VALUE *two);
extern void sx_print_value (VALUE *value);
extern __INLINE__ void sx_lock_value (VALUE *value);
extern __INLINE__ void sx_unlock_value (VALUE *value);
extern int sx_class_is_a (VALUE *klass, VALUE *par);
extern VAR *sx_set_member (SYSTEM *system, VALUE *klass, unsigned int id, VALUE *value);
extern VALUE *sx_get_member (VALUE *klass, unsigned int id);
extern VAR *sx_find_member (VALUE *klass, unsigned int id);
extern VALUE *sx_get_index (SYSTEM *system, VALUE *cont, int index);
extern VALUE *sx_get_section (SYSTEM *system, VALUE *cont, int start, int end);
extern void sx_free_value (VALUE *value);

#define sx_type_of(v) ((v) == (NULL) ? SX_VALUE_NIL : ((long)(v) & SX_NUM_MARK) ? SX_VALUE_NUM : (v)->type)
#define SX_ISNIL(v) ((v) == NULL)
#define SX_ISNUM(v) ((long)(v) & SX_NUM_MARK)
#define SX_ISSTRING(v) ((sx_type_of ((v))) == SX_VALUE_STRING)
#define SX_ISBLOCK(v) ((sx_type_of ((v))) == SX_VALUE_BLOCK)
#define SX_ISFUNC(v) ((sx_type_of ((v))) == SX_VALUE_FUNC)
#define SX_ISCFUNC(v) ((sx_type_of ((v))) == SX_VALUE_CFUNC)
#define SX_ISARRAY(v) ((sx_type_of ((v))) == SX_VALUE_ARRAY)
#define SX_ISCLASS(v) ((sx_type_of ((v))) == SX_VALUE_CLASS)
#define SX_ISRANGE(v) ((sx_type_of ((v))) == SX_VALUE_RANGE)

extern int sx_eval (THREAD *thread, VALUE *value);

extern VALUE *sx_define_cfunc (SYSTEM *system, char *name, VALUE *(*func)(THREAD *, VALUE *, unsigned int, unsigned int));

extern VALUE *sx_define_var (THREAD *thread, unsigned int id, VALUE *value, int scope);
extern VALUE *sx_define_system_var (SYSTEM *system, unsigned int id, VALUE *value);
extern VAR *sx_get_var (THREAD *thread, unsigned int id, int scope);
extern VAR *sx_get_system_var (SYSTEM *system, unsigned int id);
#define sx_free_var(v) sx_free ((v))

extern SYSTEM *sx_create_system (int argc, char **argv);
extern __INLINE__ void sx_add_gc_value (SYSTEM *system, VALUE *value);
extern void sx_run_gc (SYSTEM *system);
extern void sx_free_system (SYSTEM *system);

extern THREAD *sx_create_thread (SYSTEM *system, VALUE *main);
extern VALUE *sx_load_file (SYSTEM *system, char *file);
extern int sx_run_thread (THREAD *thread);
extern __INLINE__ void sx_mark_thread (THREAD *thread);
extern void sx_end_thread (THREAD *thread);
extern void sx_free_thread (THREAD *thread);
extern THREAD *sx_push_context (THREAD *thread, VALUE *block, unsigned char flags);
extern THREAD *sx_pop_context (THREAD *thread);
extern VALUE *sx_push_value (THREAD *thread, VALUE *value);
extern __INLINE__ VALUE *sx_get_value (THREAD *thread, int);
extern __INLINE__ void sx_pop_value (THREAD *thread, int start, unsigned int len);

extern unsigned int sx_name_to_id (const char *name);
extern const char *sx_id_to_name (unsigned int id);

/* standard library calls */
extern void sx_init_stdlib (SYSTEM *system);

/* special struct for nodes */
struct _scriptix_node {
	int op;
	int count;
	VALUE *value;
};

struct scriptix_value {
	char type;
	unsigned char flags;
	unsigned char locks;
	VALUE *gc_next;
	union {
		struct {
			unsigned int len;
			char str[0];
		} str;
		struct {
			VALUE *args;
			VALUE *body;
		} func;
		struct {
			VALUE **list;
			unsigned int count;
			unsigned int size;
		} array;
		struct {
			VALUE *parent;
			VAR *members;
			void *data;
			void (*free_data)(void *data);
			void (*ref_data)(SYSTEM *system, void *data);
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
		VALUE *(*cfunc)(THREAD *, VALUE *, unsigned int, unsigned int);
	} data;
};

struct scriptix_var {
	unsigned int id;
	VALUE *value;
	VAR *next;
};

struct scriptix_context {
	VAR *vars;
	VALUE *klass;
	unsigned char flags;
};

struct scriptix_system {
	THREAD *threads;
	VAR *vars;
	VALUE *gc_values;
	unsigned char flags;
	unsigned int gc_count;
	unsigned int gc_thresh;
};

struct scriptix_thread {
	SYSTEM *system;
	VALUE *main;
	VALUE *ret;
	int state;

	CONTEXT *context_stack;
	unsigned int context;
	unsigned int context_size;

	VALUE **data_stack;
	unsigned int data;
	unsigned int data_size;

	THREAD *next;
};

#ifdef __cplusplus__
} /* extern "C" */
#endif

#endif
