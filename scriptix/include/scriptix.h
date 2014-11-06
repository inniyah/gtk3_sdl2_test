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

#define SX_DEF_DATA_CHUNK 50
#define SX_DEF_CONTEXT_CHUNK 10
#define SX_DEF_BLOCK_CHUNK 10
#define SX_DEF_GC_THRESH 200
#define SX_DEF_RUN_LENGTH 1000

#ifndef __INLINE__
#ifdef __GNUC__
	#define __INLINE__ inline
#else
	#define __INLINE__
#endif /* __GNUC__ */
#endif /* __INLINE__ */

#define SX_MAX_NAME 128

/* Error Codes */
#define SXE_OK 0	/* no error */
#define SXE_NOMEM 1	/* out of memory */
#define SXE_BADTYPE 2	/* invalid type for operation */
#define SXE_UNDEFINED 3	/* undefined/nonexistant */
#define SXE_NILCALL 4	/* method call on nil value */
#define SXE_BADOP 5	/* invalid operator - internal error */
#define SXE_BOUNDS 6	/* value out of bounds */
#define SXE_NOTREADY 7	/* not ready to handle request */
#define SXE_INVALID 8	/* generic invalid request */
#define SXE_DISABLED 9 	/* operation disabled */
#define SXE_BUSY 10	/* busy, cannot complete request */
#define SXE_INTERNAL 11 /* internal, unknown error */
#define SXE_BADARGS 12	/* bad set or arguments; count or type */

typedef enum sx_op_type {
	SX_OP_NIL = 0,
	SX_OP_ADD,
	SX_OP_SUBTRACT,
	SX_OP_NEGATE,
	SX_OP_CALL,
	SX_OP_MULTIPLY,
	SX_OP_DIVIDE,
	SX_OP_GT,
	SX_OP_LT,
	SX_OP_GTE,
	SX_OP_LTE,
	SX_OP_EQUAL,
	SX_OP_NEQUAL,
	SX_OP_NOT,
	SX_OP_LOOKUP,
	SX_OP_ASSIGN,
	SX_OP_INDEX,
	SX_OP_PREINCREMENT,
	SX_OP_POSTINCREMENT,
	SX_OP_NEWARRAY,
	SX_OP_TYPECAST,
	SX_OP_SETINDEX,
	SX_OP_SIZEOF,
	SX_OP_METHOD,
	SX_OP_SETFILELINE,
	SX_OP_NEXTLINE,
	SX_OP_JUMP,
	SX_OP_POP,
	SX_OP_TEST,
	SX_OP_TJUMP,
	SX_OP_FJUMP,
	SX_OP_STATIC_METHOD,
	SX_OP_YIELD,
	SX_OP_IN,
	SX_OP_NEW,
	SX_OP_CLOSURE,
} sx_op_type;

	/* system flags */
#define SX_SFLAG_GCOFF (1 << 0)

	/* call flags */
#define SX_CFLAG_TTRUE (1 << 0)
#define SX_CFLAG_BREAK (1 << 1)

typedef enum sx_state_type {
	SX_STATE_READY = 0,
	SX_STATE_RUNNING,
	SX_STATE_FINISHED,
	SX_STATE_FAILED,
	SX_STATE_RETURN,
} sx_state_type;

typedef enum {
	SX_OPT_NONE = 0,
	SX_OPT_GCTHRESH,
	SX_OPT_DATACHUNK,
	SX_OPT_BLOCKCHUNK,
	SX_OPT_CONTEXTCHUNK,
	SX_OPT_RUNLENGTH,
} sx_option_type;

#define SX_NUM_MARK 0x01

typedef struct scriptix_value* SX_VALUE;
typedef struct scriptix_var* SX_VAR;
typedef struct scriptix_method* SX_METHOD;
typedef struct scriptix_call* SX_CALL;
typedef struct scriptix_system* SX_SYSTEM;
typedef struct scriptix_thread* SX_THREAD;
typedef struct scriptix_type* SX_TYPE;

typedef struct scriptix_string* SX_STRING;
typedef struct scriptix_array* SX_ARRAY;
typedef struct scriptix_func* SX_FUNC;
typedef struct scriptix_block* SX_BLOCK;
typedef struct scriptix_object* SX_OBJECT;
typedef struct scriptix_closure* SX_CLOSURE;

typedef unsigned long sx_name_id;
typedef unsigned long sx_thread_id;

typedef void (*sx_gc_hook)(SX_SYSTEM system);
typedef int (*sx_print_hook)(const char *str, ...);
typedef void (*sx_error_hook)(const char *file, unsigned int line, const char *str);

typedef void (*sxp_tag_func)(SX_SYSTEM system, const char *name, SX_FUNC func);

typedef void (*sx_type_mark)(SX_SYSTEM system, SX_VALUE obj);
typedef void (*sx_type_del)(SX_SYSTEM system, SX_VALUE obj);
typedef void (*sx_type_print)(SX_SYSTEM system, SX_VALUE value);
typedef SX_VALUE (*sx_type_to_num)(SX_SYSTEM system, SX_VALUE value);
typedef SX_STRING (*sx_type_to_str)(SX_SYSTEM system, SX_VALUE value);
typedef int (*sx_type_equal)(SX_SYSTEM system, SX_VALUE one, SX_VALUE two);
typedef int (*sx_type_compare)(SX_SYSTEM system, SX_VALUE one, SX_VALUE two);
typedef int (*sx_type_true)(SX_SYSTEM system, SX_VALUE value);
typedef SX_VALUE (*sx_type_get_index)(SX_SYSTEM system, SX_VALUE value, long index);
typedef SX_VALUE (*sx_type_set_index)(SX_SYSTEM system, SX_VALUE value, long index, SX_VALUE set);
typedef SX_VALUE (*sx_type_append)(SX_SYSTEM system, SX_VALUE value, SX_VALUE add);
typedef int (*sx_type_is_in)(SX_SYSTEM system, SX_VALUE value, SX_VALUE sub);
typedef SX_VALUE (*sx_type_new)(SX_SYSTEM system, SX_TYPE);

typedef void (*sx_cfunc)(SX_THREAD thread, SX_VALUE self, unsigned long args, SX_VALUE *argv, SX_VALUE *ret);
#define SX_DEFINE_CFUNC(name) void name (SX_THREAD sx_thread, SX_VALUE sx_self, unsigned long sx_argc, SX_VALUE *sx_argv, SX_VALUE *sx_ret)

#define sx_malloc(size) malloc(size)
#define sx_free(ptr) free(ptr);
extern __INLINE__ void *sx_dupmem (const void *mem, unsigned long size);

#define sx_new_nil() ((SX_VALUE )(NULL))
#define sx_new_num(i) ((SX_VALUE )(((i) << 1) | SX_NUM_MARK))
#define sx_toint(n) ((long)(n) >> 1)

extern void sx_clear_value (SX_SYSTEM system, SX_VALUE value, SX_TYPE type);
extern SX_STRING sx_new_str (SX_SYSTEM system, const char *str);
extern SX_STRING sx_new_str_len (SX_SYSTEM system, const char *str, unsigned long len);
extern SX_BLOCK sx_new_block (SX_SYSTEM system);
extern SX_ARRAY sx_new_array (SX_SYSTEM system, unsigned long argc, SX_VALUE *argv);
extern SX_ARRAY sx_new_stack_array (SX_THREAD thread, unsigned long argc, long top);

extern SX_BLOCK sx_add_to_block (SX_SYSTEM system, SX_BLOCK block, SX_VALUE value, sx_op_type op);
#define sx_add_value(s,b,v) (sx_add_to_block ((s), (b), (v), 0))
#define sx_add_stmt(s,b,o) (sx_add_to_block ((s), (b), NULL, (o)))

extern SX_VALUE sx_copy_value (SX_SYSTEM system, SX_VALUE value);
extern __INLINE__ void sx_mark_value (SX_SYSTEM system, SX_VALUE value);
extern int sx_is_true (SX_SYSTEM system, SX_VALUE value);
extern int sx_are_equal (SX_SYSTEM system, SX_VALUE one, SX_VALUE two);
extern int sx_compare (SX_SYSTEM system, SX_VALUE one, SX_VALUE two);
extern int sx_is_in (SX_SYSTEM system, SX_VALUE container, SX_VALUE value);
extern void sx_print_value (SX_SYSTEM system, SX_VALUE value);
extern SX_VALUE sx_get_index (SX_SYSTEM system, SX_VALUE cont, long index);
extern SX_VALUE sx_set_index (SX_SYSTEM system, SX_VALUE cont, long index, SX_VALUE value);
extern SX_VALUE sx_append (SX_SYSTEM system, SX_VALUE base, SX_VALUE value);
extern __INLINE__ SX_VALUE sx_to_num (SX_SYSTEM system, SX_VALUE value);
extern __INLINE__ SX_STRING sx_to_str (SX_SYSTEM system, SX_VALUE value);
extern void sx_free_value (SX_SYSTEM system, SX_VALUE value);

/* common names */
extern sx_name_id sx_parent_id;
extern sx_name_id sx_self_id;
extern sx_name_id sx_init_id;

/* errors */
extern const char *sx_str_error (int err);
extern int sx_raise_error (SX_THREAD thread, int err, const char *format, ...);
extern int sx_raise_sys_error (SX_THREAD thread, int err, const char *format, ...);

/* check types */
#define sx_type_of(s,v) ((v) == (NULL) ? NULL : ((long)(v) & SX_NUM_MARK) ? (s)->cint : (SX_TYPE)((long)(v)->type & ~0x01))
#define SX_ISNIL(s,v) ((v) == NULL)
#define SX_ISNUM(s,v) ((long)(v) & SX_NUM_MARK)
#define SX_ISOBJECT(s,v) ((sx_type_of ((s), (v))) == (s)->cobject)
#define SX_ISSTRING(s,v) ((sx_type_of ((s),(v))) == (s)->cstring)
#define SX_ISBLOCK(s,v) ((sx_type_of ((s),(v))) == (s)->cblock)
#define SX_ISARRAY(s,v) ((sx_type_of ((s),(v))) == (s)->carray)
#define SX_ISFUNC(s,v) ((sx_type_of ((s),(v))) == (s)->cfunction)
#define SX_ISCLOSURE(s,v) ((sx_type_of ((s),(v))) == (s)->cclosure)

/* special type checks for functions/closures */
#define SX_ISINVOCABLE(s,v) ((SX_ISFUNC((s),(v))) || (SX_ISCLOSURE((s),(v))))
#define SX_ISCFUNC(s,v) ( \
		SX_ISFUNC((s),(v)) ? \
		((SX_FUNC)(v))->cfunc != NULL : \
		( \
			SX_ISCLOSURE((s),(v)) ? \
			((SX_CLOSURE)(v))->func->cfunc != NULL : \
			0 \
		) \
	)

extern int sx_eval (SX_THREAD thread, unsigned long max);

/* variables */
extern SX_VALUE sx_define_var (SX_THREAD thread, sx_name_id id, SX_VALUE value);
extern SX_VALUE sx_define_global (SX_SYSTEM system, sx_name_id id, SX_VALUE value);
extern SX_VAR sx_get_var (SX_THREAD thread, sx_name_id id);
extern SX_VALUE sx_get_global (SX_SYSTEM system, sx_name_id id);
extern void sx_free_var (SX_VAR var);

/* system */
extern SX_SYSTEM sx_create_system (void);
extern int sx_set_option (SX_SYSTEM system, sx_option_type op, long value);
extern int sx_run_gc (SX_SYSTEM system);
extern int sx_run (SX_SYSTEM system);
extern int sx_nested_run (SX_THREAD thread, SX_VALUE* retval);
extern int sx_wait (SX_SYSTEM system, sx_thread_id id, int *retval);
extern int sx_runable (SX_SYSTEM system);
extern void sx_free_system (SX_SYSTEM system);

/* functions */
extern SX_FUNC sx_new_func (SX_SYSTEM system, sx_name_id id, sx_name_id* args, sx_name_id varg, SX_BLOCK body);
extern SX_FUNC sx_new_cfunc (SX_SYSTEM system, sx_name_id id, unsigned long argc, int varg_flag, sx_cfunc func);
extern SX_FUNC sx_add_func (SX_SYSTEM system, SX_FUNC func);
extern SX_FUNC sx_get_func (SX_SYSTEM system, sx_name_id id);
extern SX_FUNC sx_define_cfunc (SX_SYSTEM system, const char* name, unsigned long argc, int varg_flag, sx_cfunc func);

/* closures */
extern SX_CLOSURE sx_new_closure (SX_SYSTEM system, SX_FUNC func, unsigned long argc, SX_VALUE args[]);

/* init basic types */
extern SX_TYPE sx_init_string (SX_SYSTEM system);
extern SX_TYPE sx_init_int (SX_SYSTEM system);
extern SX_TYPE sx_init_block (SX_SYSTEM system);
extern SX_TYPE sx_init_array (SX_SYSTEM system);
extern SX_TYPE sx_init_object (SX_SYSTEM system);
extern SX_TYPE sx_init_function (SX_SYSTEM system);
extern SX_TYPE sx_init_closure (SX_SYSTEM system);

/* types */
extern SX_TYPE sx_new_type (SX_SYSTEM system, const char *name);
extern SX_TYPE sx_new_object_type (SX_SYSTEM system, const char *name, SX_TYPE parent);
extern SX_METHOD sx_add_method (SX_SYSTEM system, SX_TYPE type, const char *name, unsigned long argc, int varg_flag, sx_cfunc method);
extern SX_METHOD sx_get_method (SX_SYSTEM system, SX_TYPE type, sx_name_id id);
extern SX_METHOD sx_add_static_method (SX_SYSTEM system, SX_TYPE type, const char *name, unsigned long argc, int varg_flag, sx_cfunc method);
extern SX_METHOD sx_get_static_method (SX_SYSTEM system, SX_TYPE type, sx_name_id id);
extern __INLINE__ unsigned long sx_ref_type (SX_TYPE type);
extern __INLINE__ unsigned long sx_unref_type (SX_TYPE type);
extern SX_TYPE sx_type_is_a (SX_SYSTEM system, SX_TYPE base, SX_TYPE par);
extern SX_VALUE sx_value_is_a (SX_SYSTEM system, SX_VALUE base, SX_TYPE par);
extern SX_TYPE sx_get_type (SX_SYSTEM system, sx_name_id id);
extern SX_VALUE sx_type_create_new (SX_SYSTEM system, SX_TYPE type);

extern SX_OBJECT sx_new_object (SX_SYSTEM system, SX_TYPE par, void *data);
#define sx_object_data(obj) ((obj)->data)

/* returns the block of the script */
extern int sxp_add_tag (SX_SYSTEM system, const char *tag, sxp_tag_func func);
extern int sxp_load_file (SX_SYSTEM system, const char *file);
extern int sxp_load_string (SX_SYSTEM system, const char *buffer);

/* threads */
extern SX_THREAD sx_create_thread (SX_SYSTEM system, SX_VALUE call, unsigned long argc, SX_VALUE argv[]);
extern SX_THREAD sx_create_thread_v (SX_SYSTEM system, SX_VALUE call, unsigned long argc, ...);
extern int sx_run_thread (SX_THREAD thread, unsigned long max);
extern __INLINE__ void sx_mark_thread (SX_THREAD thread);
extern void sx_end_thread (SX_THREAD thread);
extern void sx_free_thread (SX_THREAD thread);
extern SX_THREAD sx_push_call (SX_THREAD thread, SX_VALUE call, unsigned long argc);
extern SX_THREAD sx_pop_call (SX_THREAD thread);
extern SX_VALUE sx_invoke (SX_THREAD thread, SX_VALUE call, unsigned long argc, SX_VALUE array[]); 
extern __INLINE__ SX_VALUE sx_invoke_v (SX_THREAD thread, SX_VALUE call, unsigned long argc, ...);
extern __INLINE__ SX_CALL sx_get_call (SX_THREAD thread);
extern SX_VALUE sx_push_value (SX_THREAD thread, SX_VALUE value);
extern __INLINE__ SX_VALUE sx_get_value (SX_THREAD thread, long index);
extern __INLINE__ void sx_pop_value (SX_THREAD thread, long start, unsigned long len);

/* names */
extern __INLINE__ sx_name_id sx_name_to_id (const char *name);
extern __INLINE__ const char *sx_name_id_to_name (sx_name_id id);
extern void sx_init_ids (void);

extern sx_name_id* sx_new_namelist (SX_SYSTEM system, unsigned long argc, ...);
extern sx_name_id* sx_new_namelist_from_array (SX_SYSTEM system, SX_ARRAY array);
extern sx_name_id* sx_namelist_append (SX_SYSTEM system, sx_name_id* list, sx_name_id id);
extern sx_name_id* sx_namelist_concat (SX_SYSTEM system, sx_name_id* list, sx_name_id* list2);
extern __INLINE__ unsigned long sx_sizeof_namelist (sx_name_id* list);
extern __INLINE__ void sx_free_namelist (sx_name_id* list);

/* standard library calls */
extern int sx_init_stdlib (SX_SYSTEM system);

struct scriptix_type {
	sx_name_id id;
	SX_TYPE parent;
	SX_METHOD methods;
	SX_METHOD static_methods;
	unsigned long refs;

	sx_type_del fdel;
	sx_type_mark fmark;
	sx_type_print fprint;
	sx_type_to_num ftonum;
	sx_type_to_str ftostr;
	sx_type_equal fequal;
	sx_type_compare fcompare;
	sx_type_true ftrue;
	sx_type_get_index fgetindex;
	sx_type_set_index fsetindex;
	sx_type_append fappend;
	sx_type_is_in fisin;
	sx_type_new fnew;

	SX_TYPE next;
};

struct scriptix_value {
	/* for the GC - mark 0x01 in the type pointer */
	SX_TYPE type;

	SX_VALUE next;
};

struct scriptix_object {
	struct scriptix_value header;

	void *data;
};

struct scriptix_string {
	struct scriptix_value header;
	unsigned long len;
	char str[0];
};

struct scriptix_array {
	struct scriptix_value header;
	SX_VALUE *list;
	unsigned long count;
	unsigned long size;
};

struct scriptix_func {
	struct scriptix_value header;
	sx_name_id id;
	unsigned long argc;
	sx_name_id* arg_names;
	sx_name_id var_arg_name;
	SX_BLOCK body;
	sx_cfunc cfunc;
	SX_FUNC next; /* for module list */
};

struct scriptix_closure {
	struct scriptix_value header;
	SX_ARRAY args;
	SX_FUNC func;
};

struct scriptix_method {
	sx_name_id id;
	unsigned long argc;
	int varg;
	sx_cfunc method;
	SX_METHOD next;
};

/* special struct for nodes */
struct _scriptix_node {
	int op;
	SX_VALUE value;
};

struct scriptix_block {
	struct scriptix_value header;
	struct _scriptix_node *nodes;
	unsigned long count;
	unsigned long size;
};

struct scriptix_var {
	unsigned long id;
	SX_TYPE type;
	SX_VALUE value;
	SX_VAR next;
};

struct scriptix_call {
	SX_FUNC func;
	SX_VALUE file;
	SX_VAR vars;
	unsigned long op_ptr;
	unsigned long top;
	unsigned long line;
	unsigned long argc;
	int flags;
};

/* special struct for function tags */
struct _scriptix_tag {
	char* tag;
	sxp_tag_func func;
	struct _scriptix_tag* next;
};

struct scriptix_system {
	/* global data */
	SX_THREAD threads;
	SX_FUNC funcs;
	SX_TYPE types;
	SX_VAR globals;

	/* tags feature */
	struct _scriptix_tag* tags;

	/* options */
	unsigned long data_chunk;
	unsigned long context_chunk;
	unsigned long block_chunk;
	unsigned long gc_thresh;

	/* for gc */
	SX_VALUE gc_list;

	SX_TYPE cstring;
	SX_TYPE cint;
	SX_TYPE cblock;
	SX_TYPE carray;
	SX_TYPE cobject;
	SX_TYPE cfunction;
	SX_TYPE cclosure;

	sx_gc_hook gc_hook;
	sx_print_hook print_hook;
	sx_error_hook error_hook;

	unsigned char flags;
	unsigned long gc_count;
	unsigned long cur_gc_thresh;
	unsigned long valid_threads;
	unsigned long run_length;
};

struct scriptix_thread {
	SX_SYSTEM system;
	SX_VALUE ret;
	int state;
	sx_thread_id id;

	SX_CALL call_stack;
	unsigned long call;
	unsigned long call_size;

	SX_VALUE *data_stack;
	unsigned long data;
	unsigned long data_size;

	SX_THREAD prev;
	SX_THREAD next;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
