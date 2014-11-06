/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     STRING = 259,
     IDENTIFIER = 260,
     TYPE = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     DO = 265,
     AND = 266,
     OR = 267,
     TGTE = 268,
     TLTE = 269,
     TNE = 270,
     TFOREACH = 271,
     TADDASSIGN = 272,
     TSUBASSIGN = 273,
     TINCREMENT = 274,
     TDECREMENT = 275,
     TNEW = 276,
     TUNTIL = 277,
     TNIL = 278,
     TIN = 279,
     TFOR = 280,
     TCONTINUE = 281,
     TYIELD = 282,
     TPUBLIC = 283,
     TMULASSIGN = 284,
     TDIVASSIGN = 285,
     TVAR = 286,
     TDEREFERENCE = 287,
     TCONCAT = 288,
     TBREAK = 289,
     TRETURN = 290,
     TEQUALS = 291,
     CUNARY = 292,
     TCAST = 293
   };
#endif
#define NUMBER 258
#define STRING 259
#define IDENTIFIER 260
#define TYPE 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define DO 265
#define AND 266
#define OR 267
#define TGTE 268
#define TLTE 269
#define TNE 270
#define TFOREACH 271
#define TADDASSIGN 272
#define TSUBASSIGN 273
#define TINCREMENT 274
#define TDECREMENT 275
#define TNEW 276
#define TUNTIL 277
#define TNIL 278
#define TIN 279
#define TFOR 280
#define TCONTINUE 281
#define TYIELD 282
#define TPUBLIC 283
#define TMULASSIGN 284
#define TDIVASSIGN 285
#define TVAR 286
#define TDEREFERENCE 287
#define TCONCAT 288
#define TBREAK 289
#define TRETURN 290
#define TEQUALS 291
#define CUNARY 292
#define TCAST 293




/* Copy the first part of user declarations.  */
#line 28 "grammar.yy"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 62 "grammar.yy"
typedef union YYSTYPE {
	CompilerNode* node;
	Value* value;
	TypeInfo* type;
	NameID id;
	NameList* names;
	struct CompilerArgList args;
} YYSTYPE;
/* Line 190 of yacc.c.  */
#line 195 "grammar.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 213 of yacc.c.  */
#line 207 "grammar.cc"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   876

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  22
/* YYNRULES -- Number of rules. */
#define YYNRULES  100
/* YYNRULES -- Number of states. */
#define YYNSTATES  230

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,     2,     2,     2,    55,     2,
      49,    50,    42,    40,    54,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    53,
      38,    36,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    39,    45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    24,    33,
      39,    43,    51,    59,    61,    64,    65,    72,    73,    82,
      83,    85,    87,    90,    93,    97,   100,   103,   106,   109,
     115,   123,   129,   135,   143,   151,   154,   164,   173,   177,
     179,   180,   182,   184,   188,   189,   191,   196,   199,   201,
     205,   207,   208,   210,   215,   219,   223,   227,   231,   235,
     239,   243,   247,   250,   253,   257,   261,   265,   269,   273,
     277,   281,   285,   288,   293,   297,   304,   310,   314,   318,
     322,   326,   329,   332,   335,   338,   343,   348,   355,   358,
     364,   371,   375,   378,   380,   382,   384,   386,   388,   390,
     392
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      58,     0,    -1,    -1,    58,    59,    -1,    58,    60,    -1,
      58,     1,    -1,    58,    63,    -1,    77,    49,    71,    50,
      51,    66,    52,    -1,    28,    77,    49,    71,    50,    51,
      66,    52,    -1,    31,    77,    36,    76,    53,    -1,    31,
      77,    53,    -1,    77,    49,    71,    50,    51,    66,    52,
      -1,    21,    49,    71,    50,    51,    66,    52,    -1,    61,
      -1,    62,    61,    -1,    -1,    21,    77,    64,    51,    62,
      52,    -1,    -1,    21,    77,    47,    78,    65,    51,    62,
      52,    -1,    -1,    67,    -1,    68,    -1,    67,    68,    -1,
      69,    53,    -1,    35,    75,    53,    -1,    35,    53,    -1,
      34,    53,    -1,    26,    53,    -1,    27,    53,    -1,     7,
      49,    75,    50,    68,    -1,     7,    49,    75,    50,    68,
       8,    68,    -1,     9,    49,    75,    50,    68,    -1,    22,
      49,    75,    50,    68,    -1,    10,    68,     9,    49,    75,
      50,    53,    -1,    10,    68,    22,    49,    75,    50,    53,
      -1,    10,    68,    -1,    25,    49,    69,    53,    75,    53,
      69,    50,    68,    -1,    16,    49,    31,    77,    24,    75,
      50,    68,    -1,    51,    66,    52,    -1,     1,    -1,    -1,
      75,    -1,    75,    -1,    70,    54,    75,    -1,    -1,    72,
      -1,    72,    54,    55,    77,    -1,    55,    77,    -1,    77,
      -1,    72,    54,    77,    -1,    70,    -1,    -1,    77,    -1,
      75,    48,    75,    56,    -1,    75,    32,    77,    -1,    75,
      40,    75,    -1,    75,    41,    75,    -1,    75,    42,    75,
      -1,    75,    43,    75,    -1,    75,    33,    75,    -1,    49,
      75,    50,    -1,    75,    24,    75,    -1,    41,    75,    -1,
      44,    75,    -1,    75,    11,    75,    -1,    75,    12,    75,
      -1,    75,    37,    75,    -1,    75,    38,    75,    -1,    75,
      15,    75,    -1,    75,    13,    75,    -1,    75,    14,    75,
      -1,    75,    39,    75,    -1,    31,    77,    -1,    31,    77,
      36,    75,    -1,    77,    36,    75,    -1,    75,    48,    75,
      56,    36,    75,    -1,    75,    32,    77,    36,    75,    -1,
      74,    17,    75,    -1,    74,    18,    75,    -1,    74,    29,
      75,    -1,    74,    30,    75,    -1,    74,    19,    -1,    74,
      20,    -1,    19,    74,    -1,    20,    74,    -1,    78,    49,
      75,    50,    -1,    77,    49,    73,    50,    -1,    49,    75,
      50,    49,    73,    50,    -1,    21,    78,    -1,    21,    78,
      49,    73,    50,    -1,    75,    32,    77,    49,    73,    50,
      -1,    48,    70,    56,    -1,    48,    56,    -1,    76,    -1,
      74,    -1,     3,    -1,     4,    -1,    23,    -1,    78,    -1,
       5,    -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   130,   130,   131,   132,   133,   134,   137,   138,   141,
     142,   145,   146,   149,   150,   153,   153,   154,   154,   157,
     158,   161,   162,   165,   166,   167,   168,   169,   170,   172,
     173,   174,   175,   176,   177,   178,   180,   182,   184,   186,
     189,   190,   193,   194,   197,   198,   199,   200,   203,   204,
     207,   208,   211,   212,   213,   216,   217,   218,   219,   220,
     221,   223,   225,   232,   233,   234,   236,   237,   238,   239,
     240,   241,   243,   244,   245,   246,   247,   249,   250,   251,
     252,   253,   254,   257,   258,   260,   262,   263,   265,   266,
     267,   269,   270,   272,   274,   278,   279,   280,   281,   284,
     287
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IDENTIFIER", "TYPE",
  "\"if\"", "\"else\"", "\"while\"", "\"do\"", "\"&&\"", "\"||\"",
  "\">=\"", "\"<=\"", "\"!=\"", "\"foreach\"", "\"+=\"", "\"-=\"",
  "\"++\"", "\"--\"", "\"new\"", "\"until\"", "\"nil\"", "\"in\"",
  "\"for\"", "\"continue\"", "\"yield\"", "\"public\"", "\"*=\"", "\"/=\"",
  "\"var\"", "\".\"", "\"::\"", "\"break\"", "\"return\"", "'='", "'>'",
  "'<'", "TEQUALS", "'+'", "'-'", "'*'", "'/'", "'!'", "CUNARY", "TCAST",
  "':'", "'['", "'('", "')'", "'{'", "'}'", "';'", "','", "'&'", "']'",
  "$accept", "program", "function", "global", "method", "methods", "new",
  "@1", "@2", "block", "stmts", "stmt", "node", "args", "arg_names",
  "arg_names_list", "func_args", "lval", "expr", "data", "name", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,    61,    62,    60,   291,
      43,    45,    42,    47,    33,   292,   293,    58,    91,    40,
      41,   123,   125,    59,    44,    38,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    57,    58,    58,    58,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    64,    63,    65,    63,    66,
      66,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    72,    72,
      73,    73,    74,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    76,    76,    76,    76,    77,
      78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     7,     8,     5,
       3,     7,     7,     1,     2,     0,     6,     0,     8,     0,
       1,     1,     2,     2,     3,     2,     2,     2,     2,     5,
       7,     5,     5,     7,     7,     2,     9,     8,     3,     1,
       0,     1,     1,     3,     0,     1,     4,     2,     1,     3,
       1,     0,     1,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     4,     3,     6,     5,     3,     3,     3,
       3,     2,     2,     2,     2,     4,     4,     6,     2,     5,
       6,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,     5,    99,     0,     0,     0,     3,     4,
       6,     0,    15,     0,     0,    44,     0,     0,    44,     0,
      10,     0,     0,    45,    48,   100,    17,     0,     0,    95,
      96,    97,     0,    98,    47,     0,     0,     0,     0,    13,
       0,     0,     0,     9,     0,     0,    49,     0,    44,    16,
      14,    44,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,    94,    41,    93,
      52,    98,    46,     0,     0,     0,     0,     0,     0,    35,
       0,    83,     0,    84,    88,     0,    40,    27,    28,    72,
      26,    25,     0,    62,    63,    92,     0,    42,     0,     0,
       7,    22,    23,     0,     0,    81,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,    18,     0,
       0,     8,     0,     0,     0,     0,     0,    51,     0,     0,
       0,    24,     0,    91,    60,    38,    77,    78,    79,    80,
      64,    65,    69,    70,    68,    61,    54,    59,    66,    67,
      71,    55,    56,    57,    58,     0,    74,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,    43,    51,     0,    51,    53,    86,    85,     0,     0,
      29,    31,     0,     0,     0,    89,    32,     0,     0,    76,
       0,     0,    12,    11,     0,     0,     0,     0,    40,    87,
      90,    75,    30,    33,    34,     0,     0,    37,     0,    36
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,     8,     9,    39,    40,    10,    17,    37,    73,
      74,    75,    76,   177,    22,    23,   178,    77,    78,    79,
      80,    81
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -146
static const short int yypact[] =
{
    -146,   235,  -146,  -146,  -146,    12,    12,    12,  -146,  -146,
    -146,   -27,    -5,    38,   -25,     0,    45,    48,     0,   101,
    -146,    12,    39,    55,  -146,  -146,  -146,    16,    58,  -146,
    -146,  -146,    59,  -146,  -146,    63,     1,    64,    68,  -146,
      33,    69,    70,  -146,   161,    12,  -146,    16,     0,  -146,
    -146,     0,   161,  -146,    71,    76,   276,    79,   333,   333,
      45,    87,    92,    66,    80,    12,    91,   327,   333,   333,
       4,   333,   161,    93,   223,  -146,    97,   343,   816,  -146,
      54,   102,  -146,    36,   103,   104,   100,   333,   333,    84,
     124,   343,   816,   343,   108,   333,   333,  -146,  -146,   123,
    -146,  -146,   410,     2,     2,  -146,   -10,   816,   496,   109,
    -146,  -146,  -146,   333,   333,  -146,  -146,   333,   333,   333,
     333,   333,   333,   333,   333,    12,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,  -146,   112,
     125,  -146,   536,   576,   126,   130,    12,   333,   616,   121,
     333,  -146,   333,  -146,   136,  -146,   816,   816,   816,   816,
     828,   828,   158,   158,   175,   158,    62,   -12,   158,   158,
     175,   -12,   -12,     2,     2,   372,   816,   135,   143,   656,
     161,   161,   276,   276,   333,   333,   170,   153,   276,   333,
     816,   816,   333,   333,   333,   168,  -146,  -146,   159,   167,
     213,  -146,   696,   736,   333,  -146,  -146,   453,   172,   816,
     181,   333,  -146,  -146,   276,   184,   185,   776,   333,  -146,
    -146,   816,  -146,  -146,  -146,   276,   197,  -146,   276,  -146
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -146,  -146,  -146,  -146,     3,   178,  -146,  -146,  -146,   -33,
    -146,   -56,   -95,   164,    43,  -146,  -145,    25,   -55,   232,
      95,    10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -41
static const short int yytable[] =
{
      89,   149,   187,    92,    92,     4,     4,    29,    30,     4,
      25,    19,   102,   103,   104,   107,   108,     4,   111,    86,
     125,     4,    15,    58,    59,    60,    26,    31,    20,    33,
     132,   133,   142,   143,   125,    65,   134,    38,     4,   109,
     148,     4,    16,    50,   152,    68,   153,   208,    69,   210,
     134,    25,    70,    71,    38,    21,    45,    38,   156,   157,
     105,    28,   158,   159,   160,   161,   162,   163,   164,   165,
      94,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   107,   179,    91,    93,    49,    50,    18,   138,    35,
     135,    84,   107,   -41,    85,   190,    11,   191,   193,    27,
      12,    13,    14,   136,    29,    30,   -41,    25,    42,    36,
      24,   194,    43,    24,    44,    47,    34,    48,    51,    97,
      87,    52,    41,   226,    31,    88,   200,   201,    90,   202,
     203,    46,   206,    98,   207,    41,    95,   107,   209,   107,
      82,    96,    41,    24,   100,   110,    24,   198,   199,   217,
     112,   137,   141,   139,   140,   146,   221,   147,   222,   150,
      99,   155,    53,   180,    29,    30,     4,    25,    54,   227,
      55,    56,   229,   123,   189,   184,   181,    57,    41,   185,
      58,    59,    60,    61,    31,   192,    62,    63,    64,   152,
     125,   126,    65,   196,   204,    66,    67,   129,   130,   131,
     132,   133,    68,   205,   211,    69,   134,   125,   126,    70,
      71,   212,    72,   -19,   -40,   130,   131,   132,   133,   213,
     166,   214,   219,   134,    53,    83,    29,    30,     4,    25,
      54,   220,    55,    56,   106,     2,     3,   223,   224,    57,
       4,   186,    58,    59,    60,    61,    31,   228,    62,    63,
      64,    32,     0,     0,    65,     0,     5,    66,    67,     0,
       0,     0,     0,     6,    68,     0,     7,    69,     0,     0,
       0,    70,    71,     0,    72,   -20,   -40,    53,     0,    29,
      30,     4,    25,    54,     0,    55,    56,     0,     0,     0,
       0,     0,    57,     0,     0,    58,    59,    60,    61,    31,
       0,    62,    63,    64,     0,     0,     0,    65,     0,     0,
      66,    67,     0,     0,     0,     0,     0,    68,     0,     0,
      69,     0,     0,     0,    70,    71,     0,    72,     0,   -40,
      29,    30,     4,    25,     0,     0,    29,    30,     4,    25,
       0,     0,     0,     0,     0,     0,    58,    59,    60,     0,
      31,     0,    58,    59,    60,     0,    31,     0,    65,     0,
     113,   114,   115,   116,    65,     0,     0,     0,    68,     0,
       0,    69,   117,   118,    68,    70,    71,    69,     0,     0,
     101,    70,    71,   119,   120,   121,   122,   123,     0,     0,
       0,     0,     0,     0,     0,     0,   124,     0,     0,     0,
       0,     0,     0,     0,   125,   126,     0,     0,     0,   127,
     128,   129,   130,   131,   132,   133,     0,     0,     0,     0,
     134,   119,   120,   121,   122,   123,     0,     0,   195,     0,
       0,     0,     0,     0,   124,     0,     0,     0,     0,     0,
       0,     0,   125,   126,     0,     0,     0,   127,   128,   129,
     130,   131,   132,   133,     0,     0,     0,     0,   134,     0,
       0,     0,     0,   151,   119,   120,   121,   122,   123,     0,
       0,     0,     0,     0,     0,     0,     0,   124,     0,     0,
       0,     0,     0,     0,     0,   125,   126,     0,     0,     0,
     127,   128,   129,   130,   131,   132,   133,     0,     0,     0,
       0,   134,     0,     0,     0,     0,   218,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   154,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   182,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   183,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   188,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   197,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   215,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   216,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,     0,     0,     0,     0,     0,     0,     0,   125,   126,
       0,     0,     0,   127,   128,   129,   130,   131,   132,   133,
       0,     0,     0,     0,   134,     0,   225,   119,   120,   121,
     122,   123,     0,     0,     0,     0,     0,     0,     0,     0,
     124,   121,   122,   123,     0,     0,     0,     0,   125,   126,
       0,     0,   124,   127,   128,   129,   130,   131,   132,   133,
     125,   126,     0,     0,   134,   127,   128,   129,   130,   131,
     132,   133,     0,     0,     0,     0,   134
};

static const short int yycheck[] =
{
      56,    96,   147,    58,    59,     5,     5,     3,     4,     5,
       6,    36,    67,    68,    69,    70,    71,     5,    74,    52,
      32,     5,    49,    19,    20,    21,    16,    23,    53,    19,
      42,    43,    87,    88,    32,    31,    48,    21,     5,    72,
      95,     5,    47,    40,    54,    41,    56,   192,    44,   194,
      48,     6,    48,    49,    21,    55,    55,    21,   113,   114,
      56,    18,   117,   118,   119,   120,   121,   122,   123,   124,
      60,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,    58,    59,    52,    83,    49,    52,    50,
      36,    48,   147,     9,    51,   150,     1,   152,    36,    51,
       5,     6,     7,    49,     3,     4,    22,     6,    50,    54,
      15,    49,    53,    18,    51,    51,    21,    49,    49,    53,
      49,    51,    27,   218,    23,    49,   182,   183,    49,   184,
     185,    36,   188,    53,   189,    40,    49,   192,   193,   194,
      45,    49,    47,    48,    53,    52,    51,   180,   181,   204,
      53,    49,    52,    50,    50,    31,   211,    49,   214,    36,
      65,    52,     1,    51,     3,     4,     5,     6,     7,   225,
       9,    10,   228,    15,    53,    49,    51,    16,    83,    49,
      19,    20,    21,    22,    23,    49,    25,    26,    27,    54,
      32,    33,    31,    50,    24,    34,    35,    39,    40,    41,
      42,    43,    41,    50,    36,    44,    48,    32,    33,    48,
      49,    52,    51,    52,    53,    40,    41,    42,    43,    52,
     125,     8,    50,    48,     1,    47,     3,     4,     5,     6,
       7,    50,     9,    10,    70,     0,     1,    53,    53,    16,
       5,   146,    19,    20,    21,    22,    23,    50,    25,    26,
      27,    19,    -1,    -1,    31,    -1,    21,    34,    35,    -1,
      -1,    -1,    -1,    28,    41,    -1,    31,    44,    -1,    -1,
      -1,    48,    49,    -1,    51,    52,    53,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    19,    20,    21,    22,    23,
      -1,    25,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,
      34,    35,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      44,    -1,    -1,    -1,    48,    49,    -1,    51,    -1,    53,
       3,     4,     5,     6,    -1,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    -1,
      23,    -1,    19,    20,    21,    -1,    23,    -1,    31,    -1,
      17,    18,    19,    20,    31,    -1,    -1,    -1,    41,    -1,
      -1,    44,    29,    30,    41,    48,    49,    44,    -1,    -1,
      53,    48,    49,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    11,    12,    13,    14,    15,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    53,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    53,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      -1,    -1,    -1,    -1,    48,    -1,    50,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    13,    14,    15,    -1,    -1,    -1,    -1,    32,    33,
      -1,    -1,    24,    37,    38,    39,    40,    41,    42,    43,
      32,    33,    -1,    -1,    48,    37,    38,    39,    40,    41,
      42,    43,    -1,    -1,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    58,     0,     1,     5,    21,    28,    31,    59,    60,
      63,    77,    77,    77,    77,    49,    47,    64,    49,    36,
      53,    55,    71,    72,    77,     6,    78,    51,    71,     3,
       4,    23,    76,    78,    77,    50,    54,    65,    21,    61,
      62,    77,    50,    53,    51,    55,    77,    51,    49,    52,
      61,    49,    51,     1,     7,     9,    10,    16,    19,    20,
      21,    22,    25,    26,    27,    31,    34,    35,    41,    44,
      48,    49,    51,    66,    67,    68,    69,    74,    75,    76,
      77,    78,    77,    62,    71,    71,    66,    49,    49,    68,
      49,    74,    75,    74,    78,    49,    49,    53,    53,    77,
      53,    53,    75,    75,    75,    56,    70,    75,    75,    66,
      52,    68,    53,    17,    18,    19,    20,    29,    30,    11,
      12,    13,    14,    15,    24,    32,    33,    37,    38,    39,
      40,    41,    42,    43,    48,    36,    49,    49,    52,    50,
      50,    52,    75,    75,     9,    22,    31,    49,    75,    69,
      36,    53,    54,    56,    50,    52,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    77,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    70,    73,    75,
      51,    51,    50,    50,    49,    49,    77,    73,    50,    53,
      75,    75,    49,    36,    49,    56,    50,    50,    66,    66,
      68,    68,    75,    75,    24,    50,    68,    75,    73,    75,
      73,    36,    52,    52,     8,    50,    50,    75,    53,    50,
      50,    75,    68,    53,    53,    50,    69,    68,    50,    68
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
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
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  yyvsp[0] = yylval;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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
     `$$ = $1'.

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
#line 137 "grammar.yy"
    { compiler->AddFunc((yyvsp[-6].id), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node), false); }
    break;

  case 8:
#line 138 "grammar.yy"
    { compiler->AddFunc((yyvsp[-6].id), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node), true); }
    break;

  case 9:
#line 141 "grammar.yy"
    { compiler->SetGlobal((yyvsp[-3].id), (yyvsp[-1].value)); }
    break;

  case 10:
#line 142 "grammar.yy"
    { compiler->SetGlobal((yyvsp[-1].id), NULL); }
    break;

  case 11:
#line 145 "grammar.yy"
    { compiler->AddMethod((yyvsp[-6].id), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node)); }
    break;

  case 12:
#line 146 "grammar.yy"
    { compiler->AddMethod(NameToID("new"), ((yyvsp[-4].args).args ? *(yyvsp[-4].args).args : NameList()), (yyvsp[-4].args).varg, (yyvsp[-1].node)); }
    break;

  case 15:
#line 153 "grammar.yy"
    { if (!compiler->AddType ((yyvsp[0].id), GetSystem()->GetScriptClassType())) YYERROR; }
    break;

  case 17:
#line 154 "grammar.yy"
    { if (!compiler->AddType ((yyvsp[-2].id), (yyvsp[0].type))) YYERROR; }
    break;

  case 19:
#line 157 "grammar.yy"
    { (yyval.node) = NULL; }
    break;

  case 20:
#line 158 "grammar.yy"
    { (yyval.node) = (yyvsp[0].node); }
    break;

  case 21:
#line 161 "grammar.yy"
    { (yyval.node) = (yyvsp[0].node); }
    break;

  case 22:
#line 162 "grammar.yy"
    { if ((yyvsp[-1].node) != NULL) { (yyval.node) = (yyvsp[-1].node); (yyval.node)->Append((yyvsp[0].node)); } else { (yyval.node) = (yyvsp[0].node); } }
    break;

  case 23:
#line 165 "grammar.yy"
    { (yyval.node) = (yyvsp[-1].node); }
    break;

  case 24:
#line 166 "grammar.yy"
    { (yyval.node) = sxp_new_return (compiler, (yyvsp[-1].node)); }
    break;

  case 25:
#line 167 "grammar.yy"
    { (yyval.node) = sxp_new_return (compiler, NULL); }
    break;

  case 26:
#line 168 "grammar.yy"
    { (yyval.node) = sxp_new_break (compiler); }
    break;

  case 27:
#line 169 "grammar.yy"
    { (yyval.node) = sxp_new_continue (compiler); }
    break;

  case 28:
#line 170 "grammar.yy"
    { (yyval.node) = sxp_new_yield (compiler); }
    break;

  case 29:
#line 172 "grammar.yy"
    { (yyval.node) = sxp_new_if (compiler, (yyvsp[-2].node), (yyvsp[0].node), NULL); }
    break;

  case 30:
#line 173 "grammar.yy"
    { (yyval.node) = sxp_new_if (compiler, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 31:
#line 174 "grammar.yy"
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_WHILE, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 32:
#line 175 "grammar.yy"
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_UNTIL, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 33:
#line 176 "grammar.yy"
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_DOWHILE, (yyvsp[-2].node), (yyvsp[-5].node)); }
    break;

  case 34:
#line 177 "grammar.yy"
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_DOUNTIL, (yyvsp[-2].node), (yyvsp[-5].node)); }
    break;

  case 35:
#line 178 "grammar.yy"
    { (yyval.node) = sxp_new_loop (compiler, SXP_LOOP_FOREVER, NULL, (yyvsp[0].node)); }
    break;

  case 36:
#line 180 "grammar.yy"
    { (yyval.node) = sxp_new_for (compiler, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 37:
#line 182 "grammar.yy"
    { (yyval.node) = sxp_new_foreach (compiler, (yyvsp[-4].id), (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 38:
#line 184 "grammar.yy"
    { (yyval.node) = (yyvsp[-1].node); }
    break;

  case 39:
#line 186 "grammar.yy"
    { (yyval.node) = NULL; }
    break;

  case 40:
#line 189 "grammar.yy"
    { (yyval.node) = NULL; }
    break;

  case 41:
#line 190 "grammar.yy"
    { (yyval.node) = sxp_new_statement (compiler, (yyvsp[0].node)); }
    break;

  case 42:
#line 193 "grammar.yy"
    { (yyval.node) = (yyvsp[0].node); }
    break;

  case 43:
#line 194 "grammar.yy"
    { (yyval.node) = (yyvsp[-2].node); (yyval.node)->Append((yyvsp[0].node)); }
    break;

  case 44:
#line 197 "grammar.yy"
    { (yyval.args).args = NULL; (yyval.args).varg = 0; }
    break;

  case 45:
#line 198 "grammar.yy"
    { (yyval.args).args = (yyvsp[0].names); (yyval.args).varg = 0; }
    break;

  case 46:
#line 199 "grammar.yy"
    { (yyval.args).args = (yyvsp[-3].names); (yyval.args).varg = (yyvsp[0].id); }
    break;

  case 47:
#line 200 "grammar.yy"
    { (yyval.args).args = NULL; (yyval.args).varg = (yyvsp[0].id); }
    break;

  case 48:
#line 203 "grammar.yy"
    { (yyval.names) = new (UseGC) NameList(); (yyval.names)->push_back((yyvsp[0].id)); }
    break;

  case 49:
#line 204 "grammar.yy"
    { (yyval.names)->push_back((yyvsp[0].id)); }
    break;

  case 50:
#line 207 "grammar.yy"
    { (yyval.node) = (yyvsp[0].node); }
    break;

  case 51:
#line 208 "grammar.yy"
    { (yyval.node) = NULL; }
    break;

  case 52:
#line 211 "grammar.yy"
    { (yyval.node) = sxp_new_lookup(compiler, (yyvsp[0].id)); }
    break;

  case 53:
#line 212 "grammar.yy"
    { (yyval.node) = sxp_new_getindex(compiler, (yyvsp[-3].node), (yyvsp[-1].node)); }
    break;

  case 54:
#line 213 "grammar.yy"
    { (yyval.node) = sxp_new_get_member(compiler, (yyvsp[-2].node), (yyvsp[0].id)); }
    break;

  case 55:
#line 216 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 56:
#line 217 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_SUBTRACT, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 57:
#line 218 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_MULTIPLY, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 58:
#line 219 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_DIVIDE, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 59:
#line 220 "grammar.yy"
    { (yyval.node) = sxp_new_concat (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 60:
#line 221 "grammar.yy"
    { (yyval.node) = (yyvsp[-1].node); }
    break;

  case 61:
#line 223 "grammar.yy"
    { (yyval.node) = sxp_new_in (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 62:
#line 225 "grammar.yy"
    {
			if ((yyvsp[0].node)->type == SXP_DATA && Value::IsA<Number>((yyvsp[0].node)->parts.value))
				(yyval.node) = sxp_new_data(compiler,Number::Create(-Number::ToInt((yyvsp[0].node)->parts.value)));
			else
				(yyval.node) = sxp_new_negate (compiler, (yyvsp[0].node)); 
		}
    break;

  case 63:
#line 232 "grammar.yy"
    { (yyval.node) = sxp_new_not (compiler, (yyvsp[0].node)); }
    break;

  case 64:
#line 233 "grammar.yy"
    { (yyval.node) = sxp_new_and (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 65:
#line 234 "grammar.yy"
    { (yyval.node) = sxp_new_or (compiler, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 66:
#line 236 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 67:
#line 237 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 68:
#line 238 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_NEQUAL, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 69:
#line 239 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_GTE, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 70:
#line 240 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_LTE, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 71:
#line 241 "grammar.yy"
    { (yyval.node) = sxp_new_math (compiler, OP_EQUAL, (yyvsp[-2].node), (yyvsp[0].node)); }
    break;

  case 72:
#line 243 "grammar.yy"
    { (yyval.node) = sxp_new_declare (compiler, (yyvsp[0].id), NULL); }
    break;

  case 73:
#line 244 "grammar.yy"
    { (yyval.node) = sxp_new_declare (compiler, (yyvsp[-2].id), (yyvsp[0].node)); }
    break;

  case 74:
#line 245 "grammar.yy"
    { (yyval.node) = sxp_new_assign (compiler, (yyvsp[-2].id), (yyvsp[0].node)); }
    break;

  case 75:
#line 246 "grammar.yy"
    { (yyval.node) = sxp_new_setindex (compiler, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[0].node)); }
    break;

  case 76:
#line 247 "grammar.yy"
    { (yyval.node) = sxp_new_set_member(compiler, (yyvsp[-4].node), (yyvsp[-2].id), (yyvsp[0].node)); }
    break;

  case 77:
#line 249 "grammar.yy"
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_ADD, (yyvsp[0].node)); }
    break;

  case 78:
#line 250 "grammar.yy"
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_SUBTRACT, (yyvsp[0].node)); }
    break;

  case 79:
#line 251 "grammar.yy"
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_MULTIPLY, (yyvsp[0].node)); }
    break;

  case 80:
#line 252 "grammar.yy"
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[-2].node), OP_DIVIDE, (yyvsp[0].node)); }
    break;

  case 81:
#line 253 "grammar.yy"
    { (yyval.node) = sxp_new_postop (compiler, (yyvsp[-1].node), OP_ADD, sxp_new_data (compiler, Number::Create (1))); }
    break;

  case 82:
#line 254 "grammar.yy"
    { (yyval.node) = sxp_new_postop (compiler, (yyvsp[-1].node), OP_SUBTRACT, sxp_new_data (compiler, Number::Create (1))); }
    break;

  case 83:
#line 257 "grammar.yy"
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[0].node), OP_ADD, sxp_new_data (compiler, Number::Create (1))); }
    break;

  case 84:
#line 258 "grammar.yy"
    { (yyval.node) = sxp_new_preop (compiler, (yyvsp[0].node), OP_SUBTRACT, sxp_new_data (compiler, Number::Create (1))); }
    break;

  case 85:
#line 260 "grammar.yy"
    { (yyval.node) = sxp_new_cast (compiler, (yyvsp[-3].type), (yyvsp[-1].node)); }
    break;

  case 86:
#line 262 "grammar.yy"
    { (yyval.node) = sxp_new_invoke (compiler, sxp_new_lookup(compiler, (yyvsp[-3].id)), (yyvsp[-1].node)); }
    break;

  case 87:
#line 263 "grammar.yy"
    { (yyval.node) = sxp_new_invoke (compiler, (yyvsp[-4].node), (yyvsp[-1].node)); }
    break;

  case 88:
#line 265 "grammar.yy"
    { (yyval.node) = sxp_new_new (compiler, (yyvsp[0].type), NULL, false); }
    break;

  case 89:
#line 266 "grammar.yy"
    { (yyval.node) = sxp_new_new (compiler, (yyvsp[-3].type), (yyvsp[-1].node), true); }
    break;

  case 90:
#line 267 "grammar.yy"
    { (yyval.node) = sxp_new_method (compiler, (yyvsp[-5].node), (yyvsp[-3].id), (yyvsp[-1].node)); }
    break;

  case 91:
#line 269 "grammar.yy"
    { (yyval.node) = sxp_new_array (compiler, (yyvsp[-1].node)); }
    break;

  case 92:
#line 270 "grammar.yy"
    { (yyval.node) = sxp_new_array (compiler, NULL); }
    break;

  case 93:
#line 272 "grammar.yy"
    { (yyval.node) = sxp_new_data (compiler, (yyvsp[0].value)); }
    break;

  case 94:
#line 274 "grammar.yy"
    { (yyval.node) = (yyvsp[0].node); }
    break;

  case 95:
#line 278 "grammar.yy"
    { (yyval.value) = (yyvsp[0].value);  }
    break;

  case 96:
#line 279 "grammar.yy"
    { (yyval.value) = (yyvsp[0].value); }
    break;

  case 97:
#line 280 "grammar.yy"
    { (yyval.value) = NULL; }
    break;

  case 98:
#line 281 "grammar.yy"
    { (yyval.value) = new TypeValue((yyvsp[0].type)); }
    break;

  case 99:
#line 284 "grammar.yy"
    { (yyval.id) = (yyvsp[0].id); }
    break;

  case 100:
#line 287 "grammar.yy"
    { (yyval.type) = (yyvsp[0].type); }
    break;


    }

/* Line 1037 of yacc.c.  */
#line 1897 "grammar.cc"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
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
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 290 "grammar.yy"


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

