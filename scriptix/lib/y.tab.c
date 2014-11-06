/* A Bison parser, made from grammar.y, by GNU bison 1.75.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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
#define YYBISON	1

/* Pure parsers.  */
#define YYPURE	0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse sxparse
#define yylex   sxlex
#define yyerror sxerror
#define yylval  sxlval
#define yychar  sxchar
#define yydebug sxdebug
#define yynerrs sxnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TNUM = 258,
     TSTR = 259,
     TNAME = 260,
     TTYPE = 261,
     TFUNCTAG = 262,
     TIF = 263,
     TELSE = 264,
     TWHILE = 265,
     TDO = 266,
     TAND = 267,
     TOR = 268,
     TGTE = 269,
     TLTE = 270,
     TNE = 271,
     TADDASSIGN = 272,
     TSUBASSIGN = 273,
     TINCREMENT = 274,
     TDECREMENT = 275,
     TNEW = 276,
     TUNTIL = 277,
     TNIL = 278,
     TRESCUE = 279,
     TIN = 280,
     TFOR = 281,
     TCONTINUE = 282,
     TYIELD = 283,
     TPUBLIC = 284,
     TRETURN = 285,
     TBREAK = 286,
     TEQUALS = 287,
     TCAST = 288,
     TLENGTH = 289,
     TRANGE = 290,
     CUNARY = 291,
     TSTATMETHOD = 292
   };
#endif
#define TNUM 258
#define TSTR 259
#define TNAME 260
#define TTYPE 261
#define TFUNCTAG 262
#define TIF 263
#define TELSE 264
#define TWHILE 265
#define TDO 266
#define TAND 267
#define TOR 268
#define TGTE 269
#define TLTE 270
#define TNE 271
#define TADDASSIGN 272
#define TSUBASSIGN 273
#define TINCREMENT 274
#define TDECREMENT 275
#define TNEW 276
#define TUNTIL 277
#define TNIL 278
#define TRESCUE 279
#define TIN 280
#define TFOR 281
#define TCONTINUE 282
#define TYIELD 283
#define TPUBLIC 284
#define TRETURN 285
#define TBREAK 286
#define TEQUALS 287
#define TCAST 288
#define TLENGTH 289
#define TRANGE 290
#define CUNARY 291
#define TSTATMETHOD 292




/* Copy the first part of user declarations.  */
#line 28 "grammar.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <errno.h>

	#include "scriptix.h"
	#include "system.h"
	#include "parser.h"

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int sxerror (const char *);
	int sxlex (void);
	int sxparse (void);

	SXP_INFO *sxp_parser_info = NULL;

	static SXP_NODE* _sxp_namelist_to_lookups (SXP_INFO* info, sx_name_id* list);


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

#ifndef YYSTYPE
#line 50 "grammar.y"
typedef union {
	SXP_NODE* node;
	SX_VALUE value;
	sx_name_id id;
	sx_name_id* name_list;
	struct _sxp_arg_list args;
	struct _scriptix_tag* tag;
} yystype;
/* Line 193 of /usr/share/bison/yacc.c.  */
#line 187 "y.tab.c"
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif

#ifndef YYLTYPE
typedef struct yyltype
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;
# define YYLTYPE yyltype
# define YYLTYPE_IS_TRIVIAL 1
#endif

/* Copy the second part of user declarations.  */


/* Line 213 of /usr/share/bison/yacc.c.  */
#line 208 "y.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
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
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];	\
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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
#define YYLAST   583

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  18
/* YYNRULES -- Number of rules. */
#define YYNRULES  87
/* YYNRULES -- Number of states. */
#define YYNSTATES  196

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(X) \
  ((unsigned)(X) <= YYMAXUTOK ? yytranslate[X] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,     2,     2,     2,    55,     2,
      47,    50,    38,    36,    54,    37,    45,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    53,
      34,    32,    33,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    57,    48,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    35,    40,    41,
      42,    44,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     7,    15,    24,    33,    34,    36,
      38,    41,    44,    47,    53,    61,    67,    73,    81,    89,
      99,   103,   104,   106,   109,   111,   113,   115,   117,   119,
     123,   124,   126,   131,   134,   136,   140,   141,   143,   151,
     163,   168,   172,   177,   180,   184,   188,   192,   196,   200,
     204,   208,   211,   214,   218,   222,   226,   230,   234,   238,
     242,   246,   250,   257,   263,   267,   271,   274,   277,   280,
     283,   288,   293,   296,   301,   304,   309,   314,   318,   322,
     327,   331,   333,   335,   337,   339,   341,   343
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      59,     0,    -1,    -1,    59,    60,    -1,    74,    47,    67,
      50,    51,    61,    52,    -1,    29,    74,    47,    67,    50,
      51,    61,    52,    -1,     7,    74,    47,    67,    50,    51,
      61,    52,    -1,    -1,    62,    -1,    63,    -1,    62,    63,
      -1,    64,    53,    -1,    65,    53,    -1,     8,    47,    72,
      50,    63,    -1,     8,    47,    72,    50,    63,     9,    63,
      -1,    10,    47,    72,    50,    63,    -1,    22,    47,    72,
      50,    63,    -1,    11,    63,    10,    47,    72,    50,    53,
      -1,    11,    63,    22,    47,    72,    50,    53,    -1,    26,
      47,    64,    53,    72,    53,    64,    50,    63,    -1,    51,
      61,    52,    -1,    -1,    72,    -1,    30,    72,    -1,    30,
      -1,    31,    -1,    27,    -1,    28,    -1,    72,    -1,    66,
      54,    72,    -1,    -1,    68,    -1,    68,    54,    55,    74,
      -1,    55,    74,    -1,    74,    -1,    68,    54,    74,    -1,
      -1,    68,    -1,    11,    47,    67,    50,    51,    61,    52,
      -1,    11,    47,    67,    50,    56,    47,    69,    50,    51,
      61,    52,    -1,    11,    51,    61,    52,    -1,    47,    66,
      50,    -1,    47,    66,    50,    70,    -1,    47,    50,    -1,
      47,    50,    70,    -1,    72,    36,    72,    -1,    72,    37,
      72,    -1,    72,    38,    72,    -1,    72,    39,    72,    -1,
      47,    72,    50,    -1,    72,    25,    72,    -1,    37,    72,
      -1,    43,    72,    -1,    72,    12,    72,    -1,    72,    13,
      72,    -1,    72,    33,    72,    -1,    72,    34,    72,    -1,
      72,    16,    72,    -1,    72,    14,    72,    -1,    72,    15,
      72,    -1,    72,    35,    72,    -1,    74,    32,    72,    -1,
      72,    46,    72,    57,    32,    72,    -1,    72,    45,    74,
      32,    72,    -1,    74,    17,    72,    -1,    74,    18,    72,
      -1,    74,    19,    -1,    19,    74,    -1,    74,    20,    -1,
      20,    74,    -1,    47,    75,    50,    72,    -1,    75,    47,
      72,    50,    -1,    74,    71,    -1,    47,    72,    50,    71,
      -1,    21,    75,    -1,    75,    45,    74,    71,    -1,    72,
      45,    74,    71,    -1,    75,    45,    74,    -1,    72,    45,
      74,    -1,    72,    46,    72,    57,    -1,    46,    66,    57,
      -1,    73,    -1,    74,    -1,     3,    -1,     4,    -1,    23,
      -1,     5,    -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    89,    89,    90,    93,    94,    95,    98,    99,   102,
     103,   106,   107,   108,   109,   110,   111,   112,   113,   115,
     117,   120,   121,   124,   125,   126,   127,   128,   131,   132,
     135,   136,   137,   138,   141,   142,   145,   146,   149,   150,
     151,   154,   155,   156,   157,   160,   161,   162,   163,   164,
     166,   168,   170,   171,   172,   174,   175,   176,   177,   178,
     179,   181,   182,   183,   185,   186,   187,   188,   189,   190,
     192,   193,   195,   196,   198,   199,   200,   201,   202,   204,
     205,   207,   209,   213,   214,   215,   218,   221
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TNUM", "TSTR", "TNAME", "TTYPE", 
  "TFUNCTAG", "TIF", "TELSE", "TWHILE", "TDO", "TAND", "TOR", "TGTE", 
  "TLTE", "TNE", "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", 
  "TNEW", "TUNTIL", "TNIL", "TRESCUE", "TIN", "TFOR", "TCONTINUE", 
  "TYIELD", "TPUBLIC", "TRETURN", "TBREAK", "'='", "'>'", "'<'", 
  "TEQUALS", "'+'", "'-'", "'*'", "'/'", "TCAST", "TLENGTH", "TRANGE", 
  "'!'", "CUNARY", "'.'", "'['", "'('", "'^'", "TSTATMETHOD", "')'", 
  "'{'", "'}'", "';'", "','", "'&'", "':'", "']'", "$accept", "program", 
  "function", "block", "stmts", "stmt", "node", "control", "args", 
  "arg_names", "arg_names_list", "iter_args", "iter_call", "func_args", 
  "expr", "data", "name", "type", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    61,    62,    60,   287,    43,    45,    42,    47,
     288,   289,   290,    33,   291,    46,    91,    40,    94,   292,
      41,   123,   125,    59,    44,    38,    58,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      62,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    65,    65,    65,    65,    65,    66,    66,
      67,    67,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    71,    71,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    73,    73,    73,    74,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     7,     8,     8,     0,     1,     1,
       2,     2,     2,     5,     7,     5,     5,     7,     7,     9,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     3,
       0,     1,     4,     2,     1,     3,     0,     1,     7,    11,
       4,     3,     4,     2,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     6,     5,     3,     3,     2,     2,     2,     2,
       4,     4,     2,     4,     2,     4,     4,     3,     3,     4,
       3,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,    86,     0,     0,     3,     0,     0,     0,
      30,    30,    30,     0,     0,    31,    34,     0,     0,    33,
       0,     0,     0,     0,     7,     0,    35,     7,     7,    83,
      84,    87,     0,     0,    21,     0,     0,     0,     0,    85,
       0,    26,    27,    24,    25,     0,     0,     0,     0,     7,
       0,     8,     9,     0,     0,    22,    81,    82,     0,    32,
       0,     0,     0,     0,     0,    67,    69,    74,     0,    21,
      23,    51,    52,     0,    28,     0,     0,     0,     4,    10,
      11,    12,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    66,
      68,     0,     0,    72,     0,     0,     6,     5,     0,     0,
       0,     0,     0,     0,     0,    80,    49,     0,    20,    53,
      54,    58,    59,    57,    50,    55,    56,    60,    45,    46,
      47,    48,    78,     0,    64,    65,    61,    43,     0,    77,
       0,    21,    21,     0,     0,    21,     0,    29,    73,    70,
       0,    76,    79,     0,    44,    41,    75,    71,    13,    15,
       0,     0,    16,     0,    63,     0,    30,     7,    42,    21,
       0,     0,    21,    62,     0,     0,    14,    17,    18,     0,
       0,    40,    21,     7,     0,    19,     0,    36,    38,    37,
       0,     0,     0,     7,     0,    39
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,     6,    50,    51,    52,    53,    54,    73,    14,
      15,   190,   154,   103,    55,    56,    57,    58
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -100
static const short yypact[] =
{
    -100,    21,  -100,  -100,    11,    11,  -100,   -22,   -15,    20,
       3,     3,     3,    11,   -32,    24,  -100,     7,    18,  -100,
      31,    10,    34,    42,    33,    11,  -100,    33,    33,  -100,
    -100,  -100,    28,    57,   192,    11,    11,   106,    66,  -100,
      69,  -100,  -100,   276,  -100,   276,   276,   276,   276,    33,
      65,    33,  -100,    70,    72,   522,  -100,   119,    36,  -100,
      67,    74,   276,   276,     9,  -100,  -100,  -100,   276,   276,
     522,     2,     2,    12,   522,   326,    45,    75,  -100,  -100,
    -100,  -100,   276,   276,   276,   276,   276,   276,   276,   276,
     276,   276,   276,   276,   276,    11,   276,   276,   276,  -100,
    -100,   276,    68,  -100,    11,   276,  -100,  -100,   354,   382,
      81,    82,   410,    78,   276,  -100,    93,   276,  -100,   537,
     537,    61,    61,   107,    61,    61,    61,   107,    63,    63,
       2,     2,   -18,   232,   522,   522,   522,   111,    -8,    93,
     438,   192,   192,   276,   276,   192,   276,   522,  -100,     2,
     276,  -100,   110,    -2,  -100,   111,  -100,  -100,   138,  -100,
     466,   494,  -100,   291,   522,   276,     3,    33,  -100,   192,
     101,   103,   276,   522,   108,   112,  -100,  -100,  -100,   109,
     -29,  -100,   192,    33,   115,  -100,   116,    11,  -100,   128,
     113,    11,   136,    33,   139,  -100
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -100,  -100,  -100,   -26,  -100,   -21,   -62,  -100,    91,    -6,
      19,  -100,    39,   -99,    87,  -100,    -1,    14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, parse error.  */
#define YYTABLE_NINF -22
static const short yytable[] =
{
       7,    60,    61,     8,     9,    17,    18,   113,     3,    16,
      16,    16,    19,    64,   150,     3,     3,   148,    20,   110,
      26,     2,   183,    77,    59,    10,     3,   184,     4,   102,
      79,   111,    11,   151,    65,    66,    29,    30,     3,    31,
     156,    32,   155,    33,    34,   166,   114,    95,    96,   167,
       5,    67,    35,    36,    37,    38,    39,    22,    13,    40,
      41,    42,    76,    43,    44,    25,   114,    12,    23,   115,
      45,    29,    30,     3,    31,    62,    46,    86,    21,    47,
      48,   104,    24,   105,    49,    27,   -21,    35,    36,    37,
     104,    39,   105,    28,   132,   117,    90,    91,    92,    93,
      94,    93,    94,   139,    63,    45,    95,    96,    95,    96,
     179,    46,    31,    68,    47,    48,    69,    78,   137,   106,
     158,   159,   153,    80,   162,    81,   107,   118,   143,   144,
      70,   146,    71,    72,    74,    75,    97,    98,    99,   100,
     102,   175,   165,    91,    92,    93,    94,   169,   176,   108,
     109,   101,    95,    96,   177,   112,   178,   186,   180,   182,
     174,   185,   187,   192,   181,    16,   102,   194,   188,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   191,   133,   134,   135,    16,   193,   136,    74,
      26,   195,   140,   138,   168,    29,    30,     3,    31,     0,
      32,   147,    33,    34,   149,     0,   189,     0,     0,     0,
       0,    35,    36,    37,    38,    39,     0,     0,    40,    41,
      42,     0,    43,    44,     0,     0,     0,     0,     0,    45,
     160,   161,     0,   163,     0,    46,     0,   164,    47,    48,
       0,     0,     0,    49,    82,    83,    84,    85,    86,     0,
       0,     0,   173,     0,     0,     0,     0,    87,     0,     0,
       0,     0,     0,     0,     0,    88,    89,    90,    91,    92,
      93,    94,     0,     0,     0,     0,     0,    95,    96,    29,
      30,     3,    31,     0,     0,     0,     0,     0,     0,   152,
       0,     0,     0,     0,     0,    35,    36,    37,     0,    39,
       0,     0,     0,    82,    83,    84,    85,    86,     0,     0,
       0,     0,     0,    45,     0,     0,    87,     0,     0,    46,
       0,     0,    47,    48,    88,    89,    90,    91,    92,    93,
      94,     0,     0,     0,     0,     0,    95,    96,    82,    83,
      84,    85,    86,     0,   172,     0,     0,     0,     0,     0,
       0,    87,     0,     0,     0,     0,     0,     0,     0,    88,
      89,    90,    91,    92,    93,    94,    82,    83,    84,    85,
      86,    95,    96,     0,     0,     0,   116,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,    88,    89,    90,
      91,    92,    93,    94,    82,    83,    84,    85,    86,    95,
      96,     0,     0,     0,   141,     0,     0,    87,     0,     0,
       0,     0,     0,     0,     0,    88,    89,    90,    91,    92,
      93,    94,    82,    83,    84,    85,    86,    95,    96,     0,
       0,     0,   142,     0,     0,    87,     0,     0,     0,     0,
       0,     0,     0,    88,    89,    90,    91,    92,    93,    94,
      82,    83,    84,    85,    86,    95,    96,     0,     0,     0,
     145,     0,     0,    87,     0,     0,     0,     0,     0,     0,
       0,    88,    89,    90,    91,    92,    93,    94,    82,    83,
      84,    85,    86,    95,    96,     0,     0,     0,   157,     0,
       0,    87,     0,     0,     0,     0,     0,     0,     0,    88,
      89,    90,    91,    92,    93,    94,    82,    83,    84,    85,
      86,    95,    96,     0,     0,     0,   170,     0,     0,    87,
       0,     0,     0,     0,     0,     0,     0,    88,    89,    90,
      91,    92,    93,    94,    82,    83,    84,    85,    86,    95,
      96,     0,     0,     0,   171,     0,     0,    87,     0,     0,
       0,    84,    85,    86,     0,    88,    89,    90,    91,    92,
      93,    94,    87,     0,     0,     0,     0,    95,    96,     0,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,     0,    95,    96
};

static const short yycheck[] =
{
       1,    27,    28,     4,     5,    11,    12,    69,     5,    10,
      11,    12,    13,    34,    32,     5,     5,   116,    50,    10,
      21,     0,    51,    49,    25,    47,     5,    56,     7,    47,
      51,    22,    47,   132,    35,    36,     3,     4,     5,     6,
     139,     8,    50,    10,    11,    47,    54,    45,    46,    51,
      29,    37,    19,    20,    21,    22,    23,    50,    55,    26,
      27,    28,    48,    30,    31,    55,    54,    47,    50,    57,
      37,     3,     4,     5,     6,    47,    43,    16,    54,    46,
      47,    45,    51,    47,    51,    51,    53,    19,    20,    21,
      45,    23,    47,    51,    95,    50,    35,    36,    37,    38,
      39,    38,    39,   104,    47,    37,    45,    46,    45,    46,
     172,    43,     6,    47,    46,    47,    47,    52,    50,    52,
     141,   142,    11,    53,   145,    53,    52,    52,    47,    47,
      43,    53,    45,    46,    47,    48,    17,    18,    19,    20,
      47,   167,    32,    36,    37,    38,    39,     9,   169,    62,
      63,    32,    45,    46,    53,    68,    53,   183,    50,    50,
     166,   182,    47,    50,    52,   166,    47,   193,    52,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    54,    96,    97,    98,   187,    51,   101,   102,
     191,    52,   105,   102,   155,     3,     4,     5,     6,    -1,
       8,   114,    10,    11,   117,    -1,   187,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      28,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    37,
     143,   144,    -1,   146,    -1,    43,    -1,   150,    46,    47,
      -1,    -1,    -1,    51,    12,    13,    14,    15,    16,    -1,
      -1,    -1,   165,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    19,    20,    21,    -1,    23,
      -1,    -1,    -1,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    -1,    25,    -1,    -1,    43,
      -1,    -1,    46,    47,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    12,    13,
      14,    15,    16,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    12,    13,    14,    15,
      16,    45,    46,    -1,    -1,    -1,    50,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    12,    13,    14,    15,    16,    45,
      46,    -1,    -1,    -1,    50,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    12,    13,    14,    15,    16,    45,    46,    -1,
      -1,    -1,    50,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      12,    13,    14,    15,    16,    45,    46,    -1,    -1,    -1,
      50,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    12,    13,
      14,    15,    16,    45,    46,    -1,    -1,    -1,    50,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    12,    13,    14,    15,
      16,    45,    46,    -1,    -1,    -1,    50,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    12,    13,    14,    15,    16,    45,
      46,    -1,    -1,    -1,    50,    -1,    -1,    25,    -1,    -1,
      -1,    14,    15,    16,    -1,    33,    34,    35,    36,    37,
      38,    39,    25,    -1,    -1,    -1,    -1,    45,    46,    -1,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    59,     0,     5,     7,    29,    60,    74,    74,    74,
      47,    47,    47,    55,    67,    68,    74,    67,    67,    74,
      50,    54,    50,    50,    51,    55,    74,    51,    51,     3,
       4,     6,     8,    10,    11,    19,    20,    21,    22,    23,
      26,    27,    28,    30,    31,    37,    43,    46,    47,    51,
      61,    62,    63,    64,    65,    72,    73,    74,    75,    74,
      61,    61,    47,    47,    63,    74,    74,    75,    47,    47,
      72,    72,    72,    66,    72,    72,    75,    61,    52,    63,
      53,    53,    12,    13,    14,    15,    16,    25,    33,    34,
      35,    36,    37,    38,    39,    45,    46,    17,    18,    19,
      20,    32,    47,    71,    45,    47,    52,    52,    72,    72,
      10,    22,    72,    64,    54,    57,    50,    50,    52,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    74,    72,    72,    72,    72,    50,    66,    74,
      72,    50,    50,    47,    47,    50,    53,    72,    71,    72,
      32,    71,    57,    11,    70,    50,    71,    50,    63,    63,
      72,    72,    63,    72,    72,    32,    47,    51,    70,     9,
      50,    50,    53,    72,    67,    61,    63,    53,    53,    64,
      50,    52,    50,    51,    56,    63,    61,    47,    52,    68,
      69,    54,    50,    51,    61,    52
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
#define YYEMPTY		-2
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

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
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)           \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#define YYLEX	yylex ()

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
# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
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

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

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
/*-----------------------------.
| Print this symbol on YYOUT.  |
`-----------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yysymprint (FILE* yyout, int yytype, YYSTYPE yyvalue)
#else
yysymprint (yyout, yytype, yyvalue)
    FILE* yyout;
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyout, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyout, yytoknum[yytype], yyvalue);
# endif
    }
  else
    YYFPRINTF (yyout, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyout, ")");
}
#endif /* YYDEBUG. */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yydestruct (int yytype, YYSTYPE yyvalue)
#else
yydestruct (yytype, yyvalue)
    int yytype;
    YYSTYPE yyvalue;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvalue;

  switch (yytype)
    {
      default:
        break;
    }
}



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of parse errors so far.  */
int yynerrs;


int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

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

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


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
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
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

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with.  */

  if (yychar <= 0)		/* This means end of input.  */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more.  */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

      /* We have to keep this `#if YYDEBUG', since we use variables
	 which are defined only if `YYDEBUG' is set.  */
      YYDPRINTF ((stderr, "Next token is "));
      YYDSYMPRINT ((stderr, yychar1, yylval));
      YYDPRINTF ((stderr, "\n"));
    }

  /* If the proper action on seeing token YYCHAR1 is to reduce or to
     detect an error, take that action.  */
  yyn += yychar1;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yychar1)
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

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



#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn - 1, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] >= 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif
  switch (yyn)
    {
        case 4:
#line 93 "grammar.y"
    { sxp_new_func (sxp_parser_info, yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 0); }
    break;

  case 5:
#line 94 "grammar.y"
    { sxp_new_func (sxp_parser_info, yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 1); }
    break;

  case 6:
#line 95 "grammar.y"
    { sxp_new_func (sxp_parser_info, yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, yyvsp[-7].tag->tag, 1); }
    break;

  case 7:
#line 98 "grammar.y"
    { yyval.node = NULL; }
    break;

  case 8:
#line 99 "grammar.y"
    { yyval.node = yyvsp[0].node; }
    break;

  case 9:
#line 102 "grammar.y"
    { yyval.node = yyvsp[0].node; }
    break;

  case 10:
#line 103 "grammar.y"
    { yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 11:
#line 106 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 12:
#line 107 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 13:
#line 108 "grammar.y"
    { yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;

  case 14:
#line 109 "grammar.y"
    { yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 15:
#line 110 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_WD); }
    break;

  case 16:
#line 111 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_UD); }
    break;

  case 17:
#line 112 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DW); }
    break;

  case 18:
#line 113 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DU); }
    break;

  case 19:
#line 115 "grammar.y"
    { yyval.node = sxp_new_cfor (sxp_parser_info, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 20:
#line 117 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 21:
#line 120 "grammar.y"
    { yyval.node = NULL; }
    break;

  case 22:
#line 121 "grammar.y"
    { yyval.node = sxp_new_stmt (sxp_parser_info, yyvsp[0].node); }
    break;

  case 23:
#line 124 "grammar.y"
    { yyval.node = sxp_new_retr (sxp_parser_info, yyvsp[0].node); }
    break;

  case 24:
#line 125 "grammar.y"
    { yyval.node = sxp_new_retr (sxp_parser_info, NULL); }
    break;

  case 25:
#line 126 "grammar.y"
    { yyval.node = sxp_new_brak (sxp_parser_info); }
    break;

  case 26:
#line 127 "grammar.y"
    { yyval.node = sxp_new_cont (sxp_parser_info); }
    break;

  case 27:
#line 128 "grammar.y"
    { yyval.node = sxp_new_yeld (sxp_parser_info); }
    break;

  case 28:
#line 131 "grammar.y"
    { yyval.node = yyvsp[0].node; }
    break;

  case 29:
#line 132 "grammar.y"
    { yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 30:
#line 135 "grammar.y"
    { yyval.args.args = NULL; yyval.args.varg = 0; }
    break;

  case 31:
#line 136 "grammar.y"
    { yyval.args.args = yyvsp[0].name_list; yyval.args.varg = 0; }
    break;

  case 32:
#line 137 "grammar.y"
    { yyval.args.args = yyvsp[-3].name_list; yyval.args.varg = yyvsp[0].id; }
    break;

  case 33:
#line 138 "grammar.y"
    { yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;

  case 34:
#line 141 "grammar.y"
    { yyval.name_list = sx_new_namelist (sxp_parser_info->system, 1, yyvsp[0].id); }
    break;

  case 35:
#line 142 "grammar.y"
    { yyval.name_list = sx_namelist_append (sxp_parser_info->system, yyvsp[-2].name_list, yyvsp[0].id); }
    break;

  case 36:
#line 145 "grammar.y"
    { yyval.name_list = NULL; }
    break;

  case 37:
#line 146 "grammar.y"
    { yyval.name_list = yyvsp[0].name_list; }
    break;

  case 38:
#line 149 "grammar.y"
    { yyval.node = sxp_new_afnc (sxp_parser_info, sxp_new_anon_func (sxp_parser_info, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node)); }
    break;

  case 39:
#line 150 "grammar.y"
    { SXP_NODE* args = _sxp_namelist_to_lookups (sxp_parser_info, yyvsp[-4].name_list); yyval.node = sxp_new_clos (sxp_parser_info, sxp_new_anon_func (sxp_parser_info, sx_namelist_concat (sxp_parser_info->system, yyvsp[-8].args.args, yyvsp[-4].name_list), yyvsp[-8].args.varg, yyvsp[-1].node), args); }
    break;

  case 40:
#line 151 "grammar.y"
    { yyval.node = sxp_new_afnc (sxp_parser_info, sxp_new_anon_func (sxp_parser_info, NULL, 0, yyvsp[-1].node)); }
    break;

  case 41:
#line 154 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 42:
#line 155 "grammar.y"
    { sxp_append (yyvsp[-2].node, yyvsp[0].node); yyval.node = yyvsp[-2].node; }
    break;

  case 43:
#line 156 "grammar.y"
    { yyval.node = NULL; }
    break;

  case 44:
#line 157 "grammar.y"
    { yyval.node = yyvsp[0].node; }
    break;

  case 45:
#line 160 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 46:
#line 161 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 47:
#line 162 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 48:
#line 163 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 49:
#line 164 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 50:
#line 166 "grammar.y"
    { yyval.node = sxp_new_in (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 51:
#line 168 "grammar.y"
    { yyval.node = sxp_new_nega (sxp_parser_info, yyvsp[0].node); }
    break;

  case 52:
#line 170 "grammar.y"
    { yyval.node = sxp_new_not (sxp_parser_info, yyvsp[0].node); }
    break;

  case 53:
#line 171 "grammar.y"
    { yyval.node = sxp_new_and (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 54:
#line 172 "grammar.y"
    { yyval.node = sxp_new_or (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 55:
#line 174 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 56:
#line 175 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 57:
#line 176 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 58:
#line 177 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 59:
#line 178 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 60:
#line 179 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 61:
#line 181 "grammar.y"
    { yyval.node = sxp_new_assi (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 62:
#line 182 "grammar.y"
    { yyval.node = sxp_new_set (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;

  case 63:
#line 183 "grammar.y"
    { yyval.node = sxp_new_setm (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 64:
#line 185 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 65:
#line 186 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, sxp_new_nega (sxp_parser_info, yyvsp[0].node)); }
    break;

  case 66:
#line 187 "grammar.y"
    { yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
    break;

  case 67:
#line 188 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
    break;

  case 68:
#line 189 "grammar.y"
    { yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
    break;

  case 69:
#line 190 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
    break;

  case 70:
#line 192 "grammar.y"
    { yyval.node = sxp_new_cast (sxp_parser_info, yyvsp[0].node, yyvsp[-2].id); }
    break;

  case 71:
#line 193 "grammar.y"
    { yyval.node = sxp_new_cast (sxp_parser_info, yyvsp[-1].node, yyvsp[-3].id); }
    break;

  case 72:
#line 195 "grammar.y"
    { yyval.node = sxp_new_call (sxp_parser_info, sxp_new_look (sxp_parser_info, yyvsp[-1].id), yyvsp[0].node); }
    break;

  case 73:
#line 196 "grammar.y"
    { yyval.node = sxp_new_call (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 74:
#line 198 "grammar.y"
    { yyval.node = sxp_new_new (sxp_parser_info, yyvsp[0].id); }
    break;

  case 75:
#line 199 "grammar.y"
    { yyval.node = sxp_new_smet (sxp_parser_info, yyvsp[-3].id, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 76:
#line 200 "grammar.y"
    { yyval.node = sxp_new_meth (sxp_parser_info, yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 77:
#line 201 "grammar.y"
    { yyval.node = sxp_new_smet (sxp_parser_info, yyvsp[-2].id, yyvsp[0].id, NULL); }
    break;

  case 78:
#line 202 "grammar.y"
    { yyval.node = sxp_new_meth (sxp_parser_info, yyvsp[-2].node, yyvsp[0].id, NULL); }
    break;

  case 79:
#line 204 "grammar.y"
    { yyval.node = sxp_new_indx (sxp_parser_info, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 80:
#line 205 "grammar.y"
    { yyval.node = sxp_new_arry (sxp_parser_info, yyvsp[-1].node); }
    break;

  case 81:
#line 207 "grammar.y"
    { yyval.node = sxp_new_data (sxp_parser_info, yyvsp[0].value); }
    break;

  case 82:
#line 209 "grammar.y"
    { yyval.node = sxp_new_look (sxp_parser_info, yyvsp[0].id); }
    break;

  case 83:
#line 213 "grammar.y"
    { yyval.value = yyvsp[0].value;  }
    break;

  case 84:
#line 214 "grammar.y"
    { yyval.value = yyvsp[0].value; }
    break;

  case 85:
#line 215 "grammar.y"
    { yyval.value = NULL; }
    break;

  case 86:
#line 218 "grammar.y"
    { yyval.id = yyvsp[0].id; }
    break;

  case 87:
#line 221 "grammar.y"
    { yyval.id = yyvsp[0].id; }
    break;


    }

/* Line 1016 of /usr/share/bison/yacc.c.  */
#line 1687 "y.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

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
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyssp > yyss)
	    {
	      YYDPRINTF ((stderr, "Error: popping "));
	      YYDSYMPRINT ((stderr,
			    yystos[*yyssp],
			    *yyvsp));
	      YYDPRINTF ((stderr, "\n"));
	      yydestruct (yystos[*yyssp], *yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yydestruct (yychar1, yylval);
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

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

      YYDPRINTF ((stderr, "Error: popping "));
      YYDSYMPRINT ((stderr,
		    yystos[*yyssp], *yyvsp));
      YYDPRINTF ((stderr, "\n"));

      yydestruct (yystos[yystate], *yyvsp);
      yyvsp--;
      yystate = *--yyssp;


#if YYDEBUG
      if (yydebug)
	{
	  short *yyssp1 = yyss - 1;
	  YYFPRINTF (stderr, "Error: state stack now");
	  while (yyssp1 != yyssp)
	    YYFPRINTF (stderr, " %d", *++yyssp1);
	  YYFPRINTF (stderr, "\n");
	}
#endif
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


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


#line 224 "grammar.y"


int
sxerror (const char *str) {
	sxp_error (sxp_parser_info, str);
	return 1;
}

int
sxwrap (void) {
	return 1;
}

SXP_NODE*
_sxp_namelist_to_lookups (SXP_INFO* info, sx_name_id* list)
{
	unsigned long count = sx_sizeof_namelist(list);
	unsigned long i;
	SXP_NODE* ret = NULL;

	for (i = 0; i < count; ++i) {
		if (ret == NULL) {
			ret = sxp_new_look (info, list[i]);
		} else {
			ret = sxp_append (ret, sxp_new_look (info, list[i]));
		}
	}

	return ret;
}

int
sxp_load_file (SX_SYSTEM system, const char *file) {
	int ret, flags;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return 1;
		}
	}

	sxp_parser_info = sxp_new_info (system);
	if (sxp_parser_info == NULL) {
		if (file != NULL)
			fclose (sxin);
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}
	if (file != NULL)
		sxp_parser_info->file = sx_new_str (system, file);

	sxp_parser_inbuf = NULL;
	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (system);

	return ret;
}

int
sxp_load_string (SX_SYSTEM system, const char *buf) {
	int ret, flags;

	if (buf == NULL) {
		return 1;
	}

	sxp_parser_info = sxp_new_info (system);
	if (sxp_parser_info == NULL) {
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}

	sxin = NULL;
	sxp_parser_inbuf = buf;
	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	system->flags = flags;

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (system);

	return ret;
}

