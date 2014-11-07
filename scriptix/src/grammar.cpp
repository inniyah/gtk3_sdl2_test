/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 28 "src/grammar.yy" /* yacc.c:339  */

	#include <cstdlib>
	#include <cstdio>
	#include <cstring>
	#include <errno.h>
	#include <gc/gc.h>

	#include "scriptix.h"
	#include "system.h"
	#include "compiler.h"

	using namespace Scriptix;
	using namespace Scriptix::Compiler;

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int yyerror (const char *);
	extern int yylex (void);
	int yyparse (void);

	Scriptix::Compiler::Compiler* compiler = NULL;

	#define YYERROR_VERBOSE 1
	#define SXERROR_VERBOSE 1

	/* stupid BISON fix */
	#define __attribute__(x)

	#define malloc(size) GC_MALLOC(size)
	#define realloc(ptr,size) GC_REALLOC(ptr,size)
	#define free(ptr)

#line 100 "src/grammar.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "grammar.h".  */
#ifndef YY_YY_SRC_GRAMMAR_H_INCLUDED
# define YY_YY_SRC_GRAMMAR_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    STRING = 259,
    IDENTIFIER = 260,
    TYPE = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOREVER = 265,
    DO = 266,
    AND = 267,
    OR = 268,
    TGTE = 269,
    TLTE = 270,
    TNE = 271,
    TFOREACH = 272,
    TADDASSIGN = 273,
    TSUBASSIGN = 274,
    TINCREMENT = 275,
    TDECREMENT = 276,
    TNEW = 277,
    TUNTIL = 278,
    TNIL = 279,
    TIN = 280,
    TFOR = 281,
    TCONTINUE = 282,
    TYIELD = 283,
    TPUBLIC = 284,
    TMULASSIGN = 285,
    TDIVASSIGN = 286,
    TVAR = 287,
    TDEREFERENCE = 288,
    TCONCAT = 289,
    TBREAK = 290,
    TRETURN = 291,
    TEQUALS = 292,
    CUNARY = 293,
    TCAST = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 62 "src/grammar.yy" /* yacc.c:355  */

	CompilerNode* node;
	Value* value;
	TypeInfo* type;
	NameID id;
	NameList* names;
	struct CompilerArgList args;

#line 189 "src/grammar.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_GRAMMAR_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 204 "src/grammar.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   876

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  232

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,     2,    56,     2,
      50,    51,    43,    41,    55,    42,     2,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    54,
      39,    37,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    57,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,    53,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    40,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   131,   131,   132,   133,   134,   135,   138,   139,   142,
     143,   146,   147,   150,   151,   154,   154,   155,   155,   158,
     159,   162,   163,   166,   167,   168,   169,   170,   171,   173,
     174,   175,   176,   177,   178,   179,   181,   183,   185,   187,
     190,   191,   194,   195,   198,   199,   200,   201,   204,   205,
     208,   209,   212,   213,   214,   217,   218,   219,   220,   221,
     222,   224,   226,   233,   234,   235,   237,   238,   239,   240,
     241,   242,   244,   245,   246,   247,   248,   250,   251,   252,
     253,   254,   255,   258,   259,   261,   263,   264,   266,   267,
     268,   270,   271,   273,   275,   279,   280,   281,   282,   285,
     288
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IDENTIFIER", "TYPE",
  "\"if\"", "\"else\"", "\"while\"", "\"forever\"", "\"do\"", "\"&&\"",
  "\"||\"", "\">=\"", "\"<=\"", "\"!=\"", "\"foreach\"", "\"+=\"",
  "\"-=\"", "\"++\"", "\"--\"", "\"new\"", "\"until\"", "\"nil\"",
  "\"in\"", "\"for\"", "\"continue\"", "\"yield\"", "\"public\"", "\"*=\"",
  "\"/=\"", "\"var\"", "\".\"", "\"::\"", "\"break\"", "\"return\"", "'='",
  "'>'", "'<'", "TEQUALS", "'+'", "'-'", "'*'", "'/'", "'!'", "CUNARY",
  "TCAST", "':'", "'['", "'('", "')'", "'{'", "'}'", "';'", "','", "'&'",
  "']'", "$accept", "program", "function", "global", "method", "methods",
  "new", "$@1", "$@2", "block", "stmts", "stmt", "node", "args",
  "arg_names", "arg_names_list", "func_args", "lval", "expr", "data",
  "name", "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    61,    62,    60,
     292,    43,    45,    42,    47,    33,   293,   294,    58,    91,
      40,    41,   123,   125,    59,    44,    38,    93
};
# endif

#define YYPACT_NINF -108

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-108)))

#define YYTABLE_NINF -41

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -108,   143,  -108,  -108,  -108,    16,    16,    16,  -108,  -108,
    -108,   -11,    -6,    -4,   -18,    -3,    44,     5,    -3,    25,
    -108,    16,    41,    29,  -108,  -108,  -108,    78,    48,  -108,
    -108,  -108,    47,  -108,  -108,    50,     4,    59,    68,  -108,
      32,    69,    70,  -108,   215,    16,  -108,    78,    -3,  -108,
    -108,    -3,   215,  -108,    74,    83,   323,    85,   358,   358,
      44,    87,    95,    77,    92,    16,    98,     2,   358,   358,
     158,   358,   215,   104,   269,  -108,   112,   441,   815,  -108,
      -7,   118,  -108,    33,   119,   122,   116,   358,   358,    81,
     144,   441,   815,   441,   127,   358,   358,  -108,  -108,   151,
    -108,  -108,   409,    61,    61,  -108,    40,   815,   495,   128,
    -108,  -108,  -108,   358,   358,  -108,  -108,   358,   358,   358,
     358,   358,   358,   358,   358,    16,   358,   358,   358,   358,
     358,   358,   358,   358,   358,   358,   358,   358,  -108,   135,
     137,  -108,   535,   575,   145,   147,   148,    16,   358,   615,
     152,   358,  -108,   358,  -108,   154,  -108,   815,   815,   815,
     815,   827,   827,    72,    72,   150,    72,    -2,   153,    72,
      72,   150,   153,   153,    61,    61,   371,   815,   155,   160,
     655,   215,   215,   323,   323,   358,  -108,   358,   180,   161,
     323,   358,   815,   815,   358,   358,   358,   172,  -108,  -108,
     164,   170,   205,  -108,   695,   735,   358,  -108,  -108,   452,
     163,   815,   174,   358,  -108,  -108,   323,   175,   176,   775,
     358,  -108,  -108,   815,  -108,  -108,  -108,   323,   177,  -108,
     323,  -108
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     5,    99,     0,     0,     0,     3,     4,
       6,     0,    15,     0,     0,    44,     0,     0,    44,     0,
      10,     0,     0,    45,    48,   100,    17,     0,     0,    95,
      96,    97,     0,    98,    47,     0,     0,     0,     0,    13,
       0,     0,     0,     9,     0,     0,    49,     0,    44,    16,
      14,    44,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,    94,    41,    93,
      52,    98,    46,     0,     0,     0,     0,     0,     0,     0,
       0,    83,     0,    84,    88,     0,    40,    27,    28,    72,
      26,    25,     0,    62,    63,    92,     0,    42,     0,     0,
       7,    22,    23,     0,     0,    81,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,    18,     0,
       0,     8,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,    24,     0,    91,    60,    38,    77,    78,    79,
      80,    64,    65,    69,    70,    68,    61,    54,    59,    66,
      67,    71,    55,    56,    57,    58,     0,    74,    50,     0,
       0,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,    73,    43,    51,     0,    51,    53,    86,    85,
       0,     0,    29,    31,     0,     0,     0,    89,    32,     0,
       0,    76,     0,     0,    12,    11,     0,     0,     0,     0,
      40,    87,    90,    75,    30,    33,    34,     0,     0,    37,
       0,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,  -108,  -108,   -13,   184,  -108,  -108,  -108,   -27,
    -108,   -56,   -95,   178,   108,  -108,  -107,   -48,   -55,   214,
     102,     1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     8,     9,    39,    40,    10,    17,    37,    73,
      74,    75,    76,   178,    22,    23,   179,    77,    78,    79,
      80,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      89,   150,     4,    92,    92,    29,    30,     4,    25,     4,
      91,    93,   102,   103,   104,   107,   108,    26,   111,    19,
      33,     4,    58,    59,    60,    86,    31,    50,    29,    30,
     135,    25,   142,   143,    65,   195,    20,     4,     4,    15,
     149,   189,    16,   136,    68,   109,    18,    69,   196,    31,
      25,    70,    71,    21,    38,    38,   101,    27,   157,   158,
      45,    94,   159,   160,   161,   162,   163,   164,   165,   166,
      50,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   107,   180,     4,    36,    49,   138,   210,   123,   212,
     144,   145,    35,   107,   125,   153,   192,   154,   193,    42,
      38,    43,    44,    11,   146,   125,   126,    12,    13,    14,
     134,    47,   129,   130,   131,   132,   133,    24,    48,    51,
      24,   134,    52,    34,    87,   228,    28,   202,   203,    41,
     204,    97,   205,    88,   208,    90,   209,    95,    46,   107,
     211,   107,    41,     2,     3,    96,    98,    82,     4,    41,
      24,   219,   100,    24,   200,   201,    84,   110,   223,    85,
     224,    29,    30,     4,    25,     5,   112,    99,   137,   141,
     139,   229,     6,   140,   231,     7,   147,   148,    58,    59,
      60,   156,    31,   125,   126,    41,   125,   181,   151,   182,
      65,   130,   131,   132,   133,   185,   132,   133,   187,   134,
      68,   186,   134,    69,   194,   206,   191,    70,    71,   213,
     153,   198,   207,   216,   221,   105,    53,   214,    29,    30,
       4,    25,    54,   215,    55,   222,    56,   167,   230,   225,
     226,    83,    57,    32,     0,    58,    59,    60,    61,    31,
       0,    62,    63,    64,     0,     0,     0,    65,   106,   188,
      66,    67,     0,     0,     0,     0,     0,    68,     0,     0,
      69,     0,     0,     0,    70,    71,     0,    72,   -19,   -40,
      53,     0,    29,    30,     4,    25,    54,     0,    55,     0,
      56,     0,     0,     0,     0,     0,    57,     0,     0,    58,
      59,    60,    61,    31,     0,    62,    63,    64,     0,     0,
       0,    65,     0,     0,    66,    67,     0,     0,     0,     0,
       0,    68,     0,     0,    69,     0,     0,     0,    70,    71,
       0,    72,   -20,   -40,    53,     0,    29,    30,     4,    25,
      54,     0,    55,     0,    56,     0,     0,     0,     0,     0,
      57,     0,     0,    58,    59,    60,    61,    31,     0,    62,
      63,    64,     0,     0,     0,    65,     0,     0,    66,    67,
       0,    29,    30,     4,    25,    68,     0,     0,    69,     0,
       0,     0,    70,    71,     0,    72,     0,   -40,    58,    59,
      60,     0,    31,   119,   120,   121,   122,   123,     0,     0,
      65,     0,     0,     0,     0,     0,   124,     0,     0,     0,
      68,     0,     0,    69,   125,   126,     0,    70,    71,   127,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
     134,   119,   120,   121,   122,   123,     0,     0,   197,     0,
       0,     0,     0,     0,   124,     0,     0,     0,     0,     0,
       0,     0,   125,   126,     0,     0,     0,   127,   128,   129,
     130,   131,   132,   133,     0,     0,     0,     0,   134,   113,
     114,   115,   116,   152,   119,   120,   121,   122,   123,     0,
       0,   117,   118,     0,     0,     0,     0,   124,     0,     0,
       0,     0,     0,     0,     0,   125,   126,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   133,     0,     0,     0,
       0,   134,     0,     0,     0,     0,   220,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   155,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   183,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   184,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   190,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   199,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   217,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   218,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   227,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   121,   122,   123,     0,     0,     0,     0,   125,   126,
       0,     0,   124,   127,   128,   129,   130,   131,   132,   133,
     125,   126,     0,     0,   134,   127,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,   134
};

static const yytype_int16 yycheck[] =
{
      56,    96,     5,    58,    59,     3,     4,     5,     6,     5,
      58,    59,    67,    68,    69,    70,    71,    16,    74,    37,
      19,     5,    20,    21,    22,    52,    24,    40,     3,     4,
      37,     6,    87,    88,    32,    37,    54,     5,     5,    50,
      95,   148,    48,    50,    42,    72,    50,    45,    50,    24,
       6,    49,    50,    56,    22,    22,    54,    52,   113,   114,
      56,    60,   117,   118,   119,   120,   121,   122,   123,   124,
      83,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,     5,    55,    53,    53,   194,    16,   196,
       9,    10,    51,   148,    33,    55,   151,    57,   153,    51,
      22,    54,    52,     1,    23,    33,    34,     5,     6,     7,
      49,    52,    40,    41,    42,    43,    44,    15,    50,    50,
      18,    49,    52,    21,    50,   220,    18,   183,   184,    27,
     185,    54,   187,    50,   190,    50,   191,    50,    36,   194,
     195,   196,    40,     0,     1,    50,    54,    45,     5,    47,
      48,   206,    54,    51,   181,   182,    48,    53,   213,    51,
     216,     3,     4,     5,     6,    22,    54,    65,    50,    53,
      51,   227,    29,    51,   230,    32,    32,    50,    20,    21,
      22,    53,    24,    33,    34,    83,    33,    52,    37,    52,
      32,    41,    42,    43,    44,    50,    43,    44,    50,    49,
      42,    54,    49,    45,    50,    25,    54,    49,    50,    37,
      55,    51,    51,     8,    51,    57,     1,    53,     3,     4,
       5,     6,     7,    53,     9,    51,    11,   125,    51,    54,
      54,    47,    17,    19,    -1,    20,    21,    22,    23,    24,
      -1,    26,    27,    28,    -1,    -1,    -1,    32,    70,   147,
      35,    36,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      45,    -1,    -1,    -1,    49,    50,    -1,    52,    53,    54,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    20,
      21,    22,    23,    24,    -1,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,
      -1,    42,    -1,    -1,    45,    -1,    -1,    -1,    49,    50,
      -1,    52,    53,    54,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    -1,    20,    21,    22,    23,    24,    -1,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,
      -1,     3,     4,     5,     6,    42,    -1,    -1,    45,    -1,
      -1,    -1,    49,    50,    -1,    52,    -1,    54,    20,    21,
      22,    -1,    24,    12,    13,    14,    15,    16,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      42,    -1,    -1,    45,    33,    34,    -1,    49,    50,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    12,    13,    14,    15,    16,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,    18,
      19,    20,    21,    54,    12,    13,    14,    15,    16,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    54,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    14,    15,    16,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    25,    38,    39,    40,    41,    42,    43,    44,
      33,    34,    -1,    -1,    49,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    59,     0,     1,     5,    22,    29,    32,    60,    61,
      64,    78,    78,    78,    78,    50,    48,    65,    50,    37,
      54,    56,    72,    73,    78,     6,    79,    52,    72,     3,
       4,    24,    77,    79,    78,    51,    55,    66,    22,    62,
      63,    78,    51,    54,    52,    56,    78,    52,    50,    53,
      62,    50,    52,     1,     7,     9,    11,    17,    20,    21,
      22,    23,    26,    27,    28,    32,    35,    36,    42,    45,
      49,    50,    52,    67,    68,    69,    70,    75,    76,    77,
      78,    79,    78,    63,    72,    72,    67,    50,    50,    69,
      50,    75,    76,    75,    79,    50,    50,    54,    54,    78,
      54,    54,    76,    76,    76,    57,    71,    76,    76,    67,
      53,    69,    54,    18,    19,    20,    21,    30,    31,    12,
      13,    14,    15,    16,    25,    33,    34,    38,    39,    40,
      41,    42,    43,    44,    49,    37,    50,    50,    53,    51,
      51,    53,    76,    76,     9,    10,    23,    32,    50,    76,
      70,    37,    54,    55,    57,    51,    53,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    78,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    71,    74,
      76,    52,    52,    51,    51,    50,    54,    50,    78,    74,
      51,    54,    76,    76,    50,    37,    50,    57,    51,    51,
      67,    67,    69,    69,    76,    76,    25,    51,    69,    76,
      74,    76,    74,    37,    53,    53,     8,    51,    51,    76,
      54,    51,    51,    76,    69,    54,    54,    51,    70,    69,
      51,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    59,    59,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    65,    64,    66,    64,    67,
      67,    68,    68,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    70,    71,    71,    72,    72,    72,    72,    73,    73,
      74,    74,    75,    75,    75,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    77,    77,    77,    77,    78,
      79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     7,     8,     5,
       3,     7,     7,     1,     2,     0,     6,     0,     8,     0,
       1,     1,     2,     2,     3,     2,     2,     2,     2,     5,
       7,     5,     5,     7,     7,     4,     9,     8,     3,     1,
       0,     1,     1,     3,     0,     1,     4,     2,     1,     3,
       1,     0,     1,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     4,     3,     6,     5,     3,     3,     3,
       3,     2,     2,     2,     2,     4,     4,     6,     2,     5,
       6,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:
#line 138 "src/grammar.yy" /* yacc.c:1646  */
    { compiler->AddFunc((yyvsp[-6].id), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node), false); }
#line 1565 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 139 "src/grammar.yy" /* yacc.c:1646  */
    { compiler->AddFunc((yyvsp[-6].id), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node), true); }
#line 1571 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 142 "src/grammar.yy" /* yacc.c:1646  */
    { compiler->SetGlobal((yyvsp[-3].id), (yyvsp[-1].value)); }
#line 1577 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 143 "src/grammar.yy" /* yacc.c:1646  */
    { compiler->SetGlobal((yyvsp[-1].id), NULL); }
#line 1583 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 146 "src/grammar.yy" /* yacc.c:1646  */
    { compiler->AddMethod((yyvsp[-6].id), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node)); }
#line 1589 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 147 "src/grammar.yy" /* yacc.c:1646  */
    { compiler->AddMethod(NameToID("new"), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node)); }
#line 1595 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 154 "src/grammar.yy" /* yacc.c:1646  */
    { if (!compiler->AddType ((yyvsp[0].id), GetSystem()->GetScriptClassType())) YYERROR; }
#line 1601 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 155 "src/grammar.yy" /* yacc.c:1646  */
    { if (!compiler->AddType ((yyvsp[-2].id), (yyvsp[0].type))) YYERROR; }
#line 1607 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 158 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1613 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 159 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1619 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 162 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1625 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 163 "src/grammar.yy" /* yacc.c:1646  */
    { if ((yyvsp[-1].node) != NULL) { (yyval.node) = (yyvsp[-1].node); (yyval.node)->Append((yyvsp[0].node)); } else { (yyval.node) = (yyvsp[0].node); } }
#line 1631 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 166 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1637 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 167 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_return (compiler, (yyvsp[-1].node)); }
#line 1643 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 168 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_return (compiler, NULL); }
#line 1649 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 169 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_break (compiler); }
#line 1655 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 170 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_continue (compiler); }
#line 1661 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 171 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_yield (compiler); }
#line 1667 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 173 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_if (compiler, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1673 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 174 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_if (compiler, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1679 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 175 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_WHILE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1685 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 176 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_UNTIL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1691 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 177 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_DOWHILE, (yyvsp[-2].node), (yyvsp[-5].node)); }
#line 1697 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 178 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_DOUNTIL, (yyvsp[-2].node), (yyvsp[-5].node)); }
#line 1703 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 179 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_FOREVER, NULL, (yyvsp[-2].node)); }
#line 1709 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 181 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_for (compiler, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1715 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 183 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_foreach (compiler, (yyvsp[-4].id), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1721 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 185 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1727 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 187 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1733 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 190 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1739 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 191 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_statement (compiler, (yyvsp[0].node)); }
#line 1745 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 194 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1751 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 195 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node); (yyval.node)->Append((yyvsp[0].node)); }
#line 1757 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 198 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.args).args = NULL; (yyval.args).varg = 0; }
#line 1763 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 199 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.args).args = (yyvsp[0].names); (yyval.args).varg = 0; }
#line 1769 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 200 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.args).args = (yyvsp[-3].names); (yyval.args).varg = (yyvsp[0].id); }
#line 1775 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 201 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.args).args = NULL; (yyval.args).varg = (yyvsp[0].id); }
#line 1781 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 204 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.names) = new (UseGC) NameList(); (yyval.names)->push_back((yyvsp[0].id)); }
#line 1787 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 205 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.names)->push_back((yyvsp[0].id)); }
#line 1793 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 208 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1799 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 209 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = NULL; }
#line 1805 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 212 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_lookup(compiler, (yyvsp[0].id)); }
#line 1811 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 213 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_getindex(compiler, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1817 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 214 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_get_member(compiler, (yyvsp[-2].node), (yyvsp[0].id)); }
#line 1823 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 217 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1829 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 218 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_SUBTRACT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1835 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 219 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_MULTIPLY, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1841 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 220 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_DIVIDE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1847 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 221 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_concat (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1853 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 222 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1859 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 224 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_in (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1865 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 226 "src/grammar.yy" /* yacc.c:1646  */
    {
			if ((yyvsp[0].node)->type == SXP_DATA && Value::IsA<Number>((yyvsp[0].node)->parts.value))
				(yyval.node) = sxp_new_data(compiler,Number::Create(-Number::ToInt((yyvsp[0].node)->parts.value)));
			else
				(yyval.node) = sxp_new_negate (compiler, (yyvsp[0].node)); 
		}
#line 1876 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 233 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_not (compiler, (yyvsp[0].node)); }
#line 1882 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 234 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_and (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1888 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 235 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_or (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1894 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 237 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1900 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 238 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1906 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 239 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_NEQUAL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1912 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 240 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_GTE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1918 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 241 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_LTE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1924 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 242 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_math (compiler, OP_EQUAL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1930 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 244 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_declare (compiler, (yyvsp[0].id), NULL); }
#line 1936 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 245 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_declare (compiler, (yyvsp[-2].id), (yyvsp[0].node)); }
#line 1942 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 246 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_assign (compiler, (yyvsp[-2].id), (yyvsp[0].node)); }
#line 1948 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 247 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_setindex (compiler, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node)); }
#line 1954 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 248 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_set_member(compiler, (yyvsp[-4].node), (yyvsp[-2].id), (yyvsp[0].node)); }
#line 1960 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 250 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_ADD, (yyvsp[0].node)); }
#line 1966 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 251 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_SUBTRACT, (yyvsp[0].node)); }
#line 1972 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 252 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_MULTIPLY, (yyvsp[0].node)); }
#line 1978 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 253 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_DIVIDE, (yyvsp[0].node)); }
#line 1984 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 254 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_postop (compiler, (yyvsp[-1].node), OP_ADD, sxp_new_data (compiler, Number::Create (1))); }
#line 1990 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 255 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_postop (compiler, (yyvsp[-1].node), OP_SUBTRACT, sxp_new_data (compiler, Number::Create (1))); }
#line 1996 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 258 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[0].node), OP_ADD, sxp_new_data (compiler, Number::Create (1))); }
#line 2002 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 259 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[0].node), OP_SUBTRACT, sxp_new_data (compiler, Number::Create (1))); }
#line 2008 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 261 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_cast (compiler, (yyvsp[-3].type), (yyvsp[-1].node)); }
#line 2014 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 263 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_invoke (compiler, sxp_new_lookup(compiler, (yyvsp[-3].id)), (yyvsp[-1].node)); }
#line 2020 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 264 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_invoke (compiler, (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2026 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 266 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_new (compiler, (yyvsp[0].type), NULL, false); }
#line 2032 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 267 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_new (compiler, (yyvsp[-3].type), (yyvsp[-1].node), true); }
#line 2038 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 268 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_method (compiler, (yyvsp[-5].node), (yyvsp[-3].id), (yyvsp[-1].node)); }
#line 2044 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 270 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_array (compiler, (yyvsp[-1].node)); }
#line 2050 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 271 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_array (compiler, NULL); }
#line 2056 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 273 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = sxp_new_data (compiler, (yyvsp[0].value)); }
#line 2062 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 275 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2068 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 279 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.value) = (yyvsp[0].value);  }
#line 2074 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 280 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.value) = (yyvsp[0].value); }
#line 2080 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 281 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.value) = NULL; }
#line 2086 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 282 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.value) = new TypeValue((yyvsp[0].type)); }
#line 2092 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 285 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.id) = (yyvsp[0].id); }
#line 2098 "src/grammar.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 288 "src/grammar.yy" /* yacc.c:1646  */
    { (yyval.type) = (yyvsp[0].type); }
#line 2104 "src/grammar.cpp" /* yacc.c:1646  */
    break;


#line 2108 "src/grammar.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 291 "src/grammar.yy" /* yacc.c:1906  */


int
yyerror (const char *str) {
	compiler->Error(str);
	return 1;
}

extern "C"
int
yywrap (void) {
	return 1;
}

int
Scriptix::System::LoadFile(const BaseString& file, SecurityLevel access, CompilerHandler* handler) {
	int ret;

	if (file.empty()) {
		yyin = stdin;
	} else {
		yyin = fopen (file.c_str(), "rt");
		if (yyin == NULL) {
			std::cerr << "Could not open '" << file << "'" << std::endl;
			return SXE_INVALID;
		}
	}

	compiler = new Scriptix::Compiler::Compiler();
	if (compiler == NULL) {
		if (!file.empty())
			fclose (yyin);
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	if (!file.empty())
		compiler->SetFile(file);
	compiler->SetAccess(access);
	compiler->SetHandler(handler);

	sxp_compiler_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!file.empty())
		fclose (yyin);

	if (!ret)
		ret = compiler->Compile();

	return ret;
}

int
Scriptix::System::LoadString(const BaseString& buf, const BaseString& name, size_t lineno, SecurityLevel access, CompilerHandler* handler) {
	int ret;

	if (buf.empty())
		return SXE_INVALID;

	compiler = new Scriptix::Compiler::Compiler();
	if (compiler == NULL) {
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	compiler->SetAccess(access);
	compiler->SetFile(name);
	compiler->SetLine(lineno);
	compiler->SetHandler(handler);

	yyin = NULL;
	sxp_compiler_inbuf = buf.c_str();

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!ret)
		ret = compiler->Compile();

	return ret;
}
