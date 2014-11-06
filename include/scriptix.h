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

#ifndef __SCRIPTIX_H__
#define __SCRIPTIX_H__

#ifdef __cplusplus
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
#define SX_OP_NEWARRAY 19
#define SX_OP_SETINDEX 20
#define SX_OP_SIZEOF 21
#define SX_OP_SETMEMBER 22
#define SX_OP_MEMBER 23
#define SX_OP_NEWINSTANCE 24
#define SX_OP_ISA 25
#define SX_OP_METHOD 26
#define SX_OP_SETFILELINE 27
#define SX_OP_NEXTLINE 28
#define SX_OP_FOR 29 
#define SX_OP_RAISE 30 
#define SX_OP_TRY 31 
#define SX_OP_JUMP 32 
#define SX_OP_POP 33
#define SX_OP_TEST 34 
#define SX_OP_TJUMP 35 
#define SX_OP_FJUMP 36
#define SX_OP_STATIC_METHOD 37

	/* value flags */
#define SX_VFLAG_MARK 0x01
#define SX_VFLAG_CONST 0x02

	/* system flags */
#define SX_SFLAG_GCOFF 0x01

	/* variable flags */
#define SX_RFLAG_CONST 0x01

#define SX_STATE_RUN 0
#define SX_STATE_EXIT 1
#define SX_STATE_ERROR 2
#define SX_STATE_SWITCH 3

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
typedef struct scriptix_class SX_CLASS;

typedef struct scriptix_string SX_STRING;
typedef struct scriptix_array SX_ARRAY;
typedef struct scriptix_func SX_FUNC;
typedef struct scriptix_block SX_BLOCK;
typedef struct scriptix_error SX_ERROR;

typedef unsigned int sx_name_id;
typedef unsigned int sx_script_id;
typedef unsigned int sx_thread_id;

typedef void (*sx_gc_hook)(SX_SYSTEM *system);
typedef int (*sx_print_hook)(const char *str, ...);
typedef void (*sx_error_hook)(const char *str);

typedef void (*sx_class_mark)(SX_SYSTEM *system, SX_VALUE *value);
typedef void (*sx_class_del)(SX_SYSTEM *system, SX_VALUE *value);
typedef SX_VALUE *(*sx_class_new)(SX_SYSTEM *system, SX_CLASS *klass);
typedef void (*sx_class_print)(SX_SYSTEM *system, SX_VALUE *value);
typedef SX_VALUE *(*sx_class_to_num)(SX_SYSTEM *system, SX_VALUE *value);
typedef SX_VALUE *(*sx_class_to_str)(SX_SYSTEM *system, SX_VALUE *value);
typedef int (*sx_class_equal)(SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two);
typedef int (*sx_class_compare)(SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two);
typedef int (*sx_class_true)(SX_SYSTEM *system, SX_VALUE *value);
typedef SX_VALUE *(*sx_class_get_index)(SX_SYSTEM *system, SX_VALUE *value, int index);
typedef SX_VALUE *(*sx_class_set_index)(SX_SYSTEM *system, SX_VALUE *value, int index, SX_VALUE *set);
typedef SX_VALUE *(*sx_class_append)(SX_SYSTEM *system, SX_VALUE *value, SX_VALUE *add);

typedef void (*sx_cfunc)(SX_THREAD *thread, SX_VALUE *klass, SX_VALUE *data, unsigned int args);
#define SX_DEFINE_CFUNC(name) void name (SX_THREAD *sx_thread, SX_VALUE *sx_self, SX_VALUE *sx_data, unsigned int sx_argc)
#define sx_return(t,v) (sx_push_value ((t), (v)))

extern __INLINE__ void *sx_malloc (SX_SYSTEM *system, unsigned long size);
extern __INLINE__ void *sx_dupmem (SX_SYSTEM *system, const void *mem, unsigned long size);
extern char *sx_strdup (SX_SYSTEM *system, const char *str);
#define sx_free free

#define sx_new_nil() ((SX_VALUE *)(NULL))
#define sx_new_num(i) ((SX_VALUE *)(((i) << 1) | SX_NUM_MARK))
#define SX_TOINT(n) ((long)(n) >> 1)
#define SX_TOSTRING(s) ((SX_STRING *)(s))
#define SX_TOARRAY(s) ((SX_ARRAY *)(s))
#define SX_TOBLOCK(s) ((SX_BLOCK *)(s))
#define SX_TOERROR(s) ((SX_ERROR *)(s))

extern void sx_clear_value (SX_SYSTEM *system, SX_VALUE *value, SX_CLASS *klass);
extern SX_VALUE *sx_new_str (SX_SYSTEM *system, const char *str);
extern SX_VALUE *sx_new_str_len (SX_SYSTEM *system, const char *str, unsigned int len);
extern SX_VALUE *sx_new_block (SX_SYSTEM *system);
extern SX_VALUE *sx_new_array (SX_SYSTEM *system, unsigned int argc, SX_VALUE **argv);
extern SX_VALUE *sx_new_stack_array (SX_THREAD *thread, unsigned long argc, long top);
extern SX_VALUE *sx_new_error (SX_THREAD *thread, sx_name_id id, SX_VALUE *data);

extern SX_VALUE *sx_add_to_block (SX_SYSTEM *system, SX_VALUE *block, SX_VALUE *value, int op);
#define sx_add_value(s,b,v) (sx_add_to_block ((s), (b), (v), 0))
#define sx_add_stmt(s,b,o) (sx_add_to_block ((s), (b), NULL, (o)))

extern SX_VALUE *sx_copy_value (SX_SYSTEM *system, SX_VALUE *value);
extern __INLINE__ void sx_mark_value (SX_SYSTEM *system, SX_VALUE *value);
extern int sx_is_true (SX_SYSTEM *system, SX_VALUE *value);
extern int sx_are_equal (SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two);
extern int sx_compare (SX_SYSTEM *system, SX_VALUE *one, SX_VALUE *two);
extern void sx_print_value (SX_SYSTEM *system, SX_VALUE *value);
extern __INLINE__ void sx_lock_value (SX_VALUE *value);
extern __INLINE__ void sx_unlock_value (SX_VALUE *value);
extern SX_VALUE *sx_get_index (SX_SYSTEM *system, SX_VALUE *cont, int index);
extern SX_VALUE *sx_set_index (SX_SYSTEM *system, SX_VALUE *cont, int index, SX_VALUE *value);
extern SX_VALUE *sx_append (SX_SYSTEM *system, SX_VALUE *base, SX_VALUE *value);
extern __INLINE__ SX_VALUE *sx_to_num (SX_SYSTEM *system, SX_VALUE *value);
extern __INLINE__ SX_VALUE *sx_to_str (SX_SYSTEM *system, SX_VALUE *value);
extern void sx_free_value (SX_SYSTEM *system, SX_VALUE *value);

/* common names */
extern sx_name_id sx_parent_id;
extern sx_name_id sx_self_id;
extern sx_name_id sx_init_id;
extern sx_name_id sx_error_id;

/* errors */
extern sx_name_id sx_TypeError;
extern sx_name_id sx_StackError;
extern sx_name_id sx_NameError;
extern sx_name_id sx_ArgumentError;
extern sx_name_id sx_MemError;
extern int sx_raise_error (SX_THREAD *thread, sx_name_id error, const char *format, ...);

#define sx_class_of(s,v) ((v) == (NULL) ? NULL : ((long)(v) & SX_NUM_MARK) ? (s)->cfixnum : (v)->klass)
#define SX_ISNIL(s,v) ((v) == NULL)
#define SX_ISNUM(s,v) ((long)(v) & SX_NUM_MARK)
#define SX_ISSTRING(s,v) ((sx_top_class_of ((s),(v))) == (s)->cstring)
#define SX_ISBLOCK(s,v) ((sx_top_class_of ((s),(v))) == (s)->cblock)
#define SX_ISARRAY(s,v) ((sx_top_class_of ((s),(v))) == (s)->carray)
#define SX_ISEXCEPTION(s,v) ((sx_top_class_of ((s),(v))) == (s)->cerror)

extern int sx_eval (SX_THREAD *thread, unsigned int max);

extern SX_VALUE *sx_define_var (SX_THREAD *thread, unsigned int id, SX_VALUE *value, int scope);
extern SX_VALUE *sx_define_system_var (SX_SYSTEM *system, unsigned int id, SX_VALUE *value);
extern SX_VAR *sx_get_var (SX_THREAD *thread, unsigned int id, int scope);
extern SX_VAR *sx_get_system_var (SX_SYSTEM *system, unsigned int id);
#define sx_free_var(v) sx_free ((v))

extern SX_SYSTEM *sx_create_system (void);
extern __INLINE__ void sx_add_gc_value (SX_SYSTEM *system, SX_VALUE *value);
extern void sx_run_gc (SX_SYSTEM *system);
extern void sx_run (SX_SYSTEM *system, unsigned int max);
extern SX_VALUE *sx_run_until (SX_SYSTEM *system, sx_thread_id id);
#define sx_runable(s) ((s)->valid_threads)
extern void sx_free_system (SX_SYSTEM *system);

extern SX_FUNC *sx_new_func (SX_SYSTEM *system, sx_name_id id, SX_ARRAY *args, SX_BLOCK *body);
extern SX_FUNC *sx_new_cfunc (SX_SYSTEM *system, sx_name_id id, sx_cfunc func, SX_VALUE *data);
extern SX_FUNC *sx_get_func (SX_SYSTEM *system, sx_name_id id);
extern void sx_mark_func (SX_SYSTEM *system, SX_FUNC *func);
extern void sx_free_func (SX_FUNC *func);

extern SX_CLASS *sx_init_number (SX_SYSTEM *system);
extern SX_CLASS *sx_init_string (SX_SYSTEM *system);
extern SX_CLASS *sx_init_fixnum (SX_SYSTEM *system);
extern SX_CLASS *sx_init_error (SX_SYSTEM *system);
extern SX_CLASS *sx_init_block (SX_SYSTEM *system);
extern SX_CLASS *sx_init_array (SX_SYSTEM *system);

extern SX_CLASS *sx_new_class (SX_SYSTEM *system, sx_name_id id, SX_CLASS *par);
extern SX_CLASS *sx_new_core_class (SX_SYSTEM *system, sx_name_id id);
extern void sx_mark_class (SX_SYSTEM *system, SX_CLASS *klass);
extern void sx_free_class (SX_CLASS *klass);
extern SX_CLASS *sx_get_class (SX_SYSTEM *system, sx_name_id id);
extern __INLINE__ SX_CLASS *sx_top_class_of (SX_SYSTEM *system, SX_VALUE *value);
extern SX_VALUE *sx_new_object (SX_SYSTEM *system, SX_CLASS *par);
extern SX_FUNC *sx_add_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id, SX_ARRAY *args, SX_BLOCK *body);
extern SX_FUNC *sx_add_cmethod (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id, sx_cfunc func, SX_VALUE *data);
extern SX_FUNC *sx_get_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id);
extern SX_FUNC *sx_add_static_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id, SX_ARRAY *args, SX_BLOCK *body);
extern SX_FUNC *sx_add_static_cmethod (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id, sx_cfunc func, SX_VALUE *data);
extern SX_FUNC *sx_get_static_method (SX_SYSTEM *system, SX_CLASS *klass, sx_name_id id);
extern int sx_value_is_a (SX_SYSTEM *system, SX_VALUE *value, SX_CLASS *par);
extern int sx_class_is_a (SX_SYSTEM *system, SX_CLASS *klass, SX_CLASS *par);
extern SX_VAR *sx_set_member (SX_SYSTEM *system, SX_VALUE *klass, sx_name_id id, SX_VALUE *value);
extern SX_VALUE *sx_get_member (SX_SYSTEM *system, SX_VALUE *klass, sx_name_id id);
extern SX_VAR *sx_find_member (SX_SYSTEM *system, SX_VALUE *klass, sx_name_id id);

/* returns the block of the script */
extern int sx_load_file (SX_SYSTEM *system, const char *file);
extern int sx_load_string (SX_SYSTEM *system, const char *buffer);

extern SX_THREAD *sx_create_thread (SX_SYSTEM *system, SX_FUNC *func, SX_ARRAY *argv);
extern SX_THREAD *sx_create_thread_v (SX_SYSTEM *system, SX_FUNC *func, unsigned int argc, ...);
extern int sx_run_thread (SX_THREAD *thread, unsigned int max);
extern __INLINE__ void sx_mark_thread (SX_THREAD *thread);
extern void sx_end_thread (SX_THREAD *thread);
extern void sx_free_thread (SX_THREAD *thread);
extern SX_THREAD *sx_push_call (SX_THREAD *thread, SX_FUNC *func, SX_VALUE *klass, unsigned long argc);
extern SX_THREAD *sx_pop_call (SX_THREAD *thread);
extern SX_VALUE *sx_push_value (SX_THREAD *thread, SX_VALUE *value);
extern __INLINE__ SX_VALUE *sx_get_value (SX_THREAD *thread, int);
extern __INLINE__ void sx_pop_value (SX_THREAD *thread, int start, unsigned int len);

extern unsigned int sx_name_to_id (const char *name);
extern const char *sx_name_id_to_name (unsigned int id);
extern void sx_init_ids (void);

/* standard library calls */
extern void sx_init_stdlib (SX_SYSTEM *system);

/* special struct for nodes */
struct _scriptix_node {
	int op;
	SX_VALUE *value;
};

/* special struct for core/non-scriptable classes */
struct _scriptix_core {
	sx_class_print fprint;
	sx_class_new fnew;
	sx_class_del fdel;
	sx_class_mark fmark;
	sx_class_to_num ftonum;
	sx_class_to_str ftostr;
	sx_class_equal fequal;
	sx_class_compare fcompare;
	sx_class_true ftrue;
	sx_class_get_index fgetindex;
	sx_class_set_index fsetindex;
	sx_class_append fappend;
};

struct scriptix_class {
	sx_name_id id;
	SX_CLASS *par;
	SX_FUNC *methods;
	SX_FUNC *static_methods;

	struct _scriptix_core *core;

	SX_CLASS *next;
};

struct scriptix_value {
	SX_CLASS *klass;
	unsigned char flags;
	unsigned int locks;
	SX_VAR *members;
	SX_VALUE *gc_next;
};

struct scriptix_string {
	struct scriptix_value header;
	unsigned int len;
	char str[0];
};

struct scriptix_array {
	struct scriptix_value header;
	SX_VALUE **list;
	unsigned int count;
	unsigned int size;
};

struct scriptix_func {
	sx_name_id id;
	SX_ARRAY *args;
	SX_BLOCK *body;
	SX_VALUE *data;
	sx_cfunc cfunc;
	SX_FUNC *next;
};

struct scriptix_block {
	struct scriptix_value header;
	struct _scriptix_node *nodes;
	unsigned int count;
	unsigned int size;
};

struct scriptix_error {
	struct scriptix_value header;
	unsigned int line;
	SX_VALUE *file;
	SX_VALUE *data;
};

struct scriptix_var {
	unsigned char flags;
	unsigned int id;
	SX_VALUE *value;
	SX_VAR *next;
};

struct scriptix_call {
	SX_FUNC *func;
	SX_VALUE *klass;
	SX_VALUE *file;
	SX_VAR *vars;
	unsigned long op_ptr;
	unsigned long top;
	unsigned long line;
	unsigned long argc;
	int state;
	int test;
};

struct scriptix_system {
	SX_THREAD *threads;
	SX_CLASS *classes;
	SX_VAR *vars;
	SX_FUNC *funcs;
	SX_VALUE *gc_values;

	SX_CLASS *cstring;
	SX_CLASS *cfixnum;
	SX_CLASS *cerror;
	SX_CLASS *cblock;
	SX_CLASS *carray;
	SX_CLASS *cfunction;

	sx_gc_hook gc_hook;
	sx_print_hook print_hook;
	sx_error_hook error_hook;

	unsigned char flags;
	unsigned int gc_count;
	unsigned int gc_thresh;
	unsigned int valid_threads;
};

struct scriptix_thread {
	SX_SYSTEM *system;
	SX_VALUE *ret;
	int state;
	sx_thread_id id;
	unsigned int line;
	SX_VALUE *file;

	SX_CALL *call_stack;
	unsigned int call;
	unsigned int call_size;

	SX_VALUE **data_stack;
	unsigned int data;
	unsigned int data_size;

	SX_THREAD *next;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
