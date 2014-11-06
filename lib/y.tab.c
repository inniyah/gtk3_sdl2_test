/* A Bison parser, made from grammar.y, by GNU bison 1.50.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# if defined (__STDC__) || defined (__cplusplus)
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TNUM = 258,
     TSTR = 259,
     TNAME = 260,
     TTYPE = 261,
     TIF = 262,
     TELSE = 263,
     TWHILE = 264,
     TDO = 265,
     TAND = 266,
     TOR = 267,
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
     TRESCUE = 279,
     TIN = 280,
     TFOR = 281,
     TCONTINUE = 282,
     TYIELD = 283,
     TRETURN = 284,
     TBREAK = 285,
     TEQUALS = 286,
     TCAST = 287,
     TLENGTH = 288,
     TRANGE = 289,
     CUNARY = 290,
     TSTATMETHOD = 291
   };
# endif
  /* POSIX requires `int' for tokens in interfaces.  */
# define YYTOKENTYPE int
#endif /* !YYTOKENTYPE */
#define TNUM 258
#define TSTR 259
#define TNAME 260
#define TTYPE 261
#define TIF 262
#define TELSE 263
#define TWHILE 264
#define TDO 265
#define TAND 266
#define TOR 267
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
#define TRESCUE 279
#define TIN 280
#define TFOR 281
#define TCONTINUE 282
#define TYIELD 283
#define TRETURN 284
#define TBREAK 285
#define TEQUALS 286
#define TCAST 287
#define TLENGTH 288
#define TRANGE 289
#define CUNARY 290
#define TSTATMETHOD 291




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
#line 48 "grammar.y"
typedef union {
	SXP_NODE *node;
	SX_VALUE value;
	sx_name_id id;
	struct _sxp_arg_list args;
} yystype;
/* Line 193 of /usr/share/bison/yacc.c.  */
#line 184 "y.tab.c"
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
#line 205 "y.tab.c"

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

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
#define YYLAST   591

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  15
/* YYNRULES -- Number of rules. */
#define YYNRULES  77
/* YYNRULES -- Number of states. */
#define YYNSTATES  170

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(X) \
  ((unsigned)(X) <= YYMAXUTOK ? yytranslate[X] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,     2,     2,     2,    54,     2,
      46,    49,    37,    35,    53,    36,    44,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    52,
      33,    31,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    55,    47,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    34,    39,    40,    41,
      43,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     7,    15,    16,    18,    20,    23,
      26,    29,    35,    43,    49,    55,    63,    71,    79,    89,
      93,    99,   103,   104,   106,   109,   111,   113,   115,   117,
     118,   120,   124,   125,   127,   132,   135,   137,   141,   145,
     149,   153,   157,   161,   165,   168,   171,   175,   179,   183,
     187,   191,   195,   199,   203,   207,   214,   220,   224,   228,
     231,   234,   237,   240,   245,   250,   253,   260,   267,   271,
     276,   280,   282,   284,   286,   288,   290,   292
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const signed char yyrhs[] =
{
      57,     0,    -1,    -1,    57,    58,    -1,    69,    46,    65,
      49,    50,    59,    51,    -1,    -1,    60,    -1,    61,    -1,
      60,    61,    -1,    62,    52,    -1,    63,    52,    -1,     7,
      46,    67,    49,    61,    -1,     7,    46,    67,    49,    61,
       8,    61,    -1,     9,    46,    67,    49,    61,    -1,    22,
      46,    67,    49,    61,    -1,    10,    61,     9,    46,    67,
      49,    52,    -1,    10,    61,    22,    46,    67,    49,    52,
      -1,    16,    46,    69,    25,    67,    49,    61,    -1,    26,
      46,    62,    52,    67,    52,    62,    49,    61,    -1,    70,
      69,    52,    -1,    70,    69,    31,    67,    52,    -1,    50,
      59,    51,    -1,    -1,    67,    -1,    29,    67,    -1,    29,
      -1,    30,    -1,    27,    -1,    28,    -1,    -1,    67,    -1,
      64,    53,    67,    -1,    -1,    66,    -1,    66,    53,    54,
      69,    -1,    54,    69,    -1,    69,    -1,    66,    53,    69,
      -1,    67,    35,    67,    -1,    67,    36,    67,    -1,    67,
      37,    67,    -1,    67,    38,    67,    -1,    46,    67,    49,
      -1,    67,    25,    67,    -1,    36,    67,    -1,    42,    67,
      -1,    67,    11,    67,    -1,    67,    12,    67,    -1,    67,
      32,    67,    -1,    67,    33,    67,    -1,    67,    15,    67,
      -1,    67,    13,    67,    -1,    67,    14,    67,    -1,    67,
      34,    67,    -1,    69,    31,    67,    -1,    67,    45,    67,
      55,    31,    67,    -1,    67,    44,    69,    31,    67,    -1,
      69,    17,    67,    -1,    69,    18,    67,    -1,    69,    19,
      -1,    19,    69,    -1,    69,    20,    -1,    20,    69,    -1,
      46,    70,    49,    67,    -1,    69,    46,    64,    49,    -1,
      21,    70,    -1,    70,    44,    69,    46,    64,    49,    -1,
      67,    44,    69,    46,    64,    49,    -1,    67,    44,    69,
      -1,    67,    45,    67,    55,    -1,    45,    64,    55,    -1,
      68,    -1,    69,    -1,     3,    -1,     4,    -1,    23,    -1,
       5,    -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    83,    83,    84,    87,    90,    91,    94,    95,    98,
      99,   100,   101,   102,   103,   104,   105,   107,   108,   110,
     111,   113,   116,   117,   120,   121,   122,   123,   124,   127,
     128,   129,   132,   133,   134,   135,   138,   139,   142,   143,
     144,   145,   146,   148,   150,   152,   153,   154,   156,   157,
     158,   159,   160,   161,   163,   164,   165,   167,   168,   169,
     170,   171,   172,   174,   175,   177,   178,   179,   180,   182,
     183,   185,   187,   191,   192,   193,   196,   199
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TNUM", "TSTR", "TNAME", "TTYPE", "TIF", 
  "TELSE", "TWHILE", "TDO", "TAND", "TOR", "TGTE", "TLTE", "TNE", 
  "TFOREACH", "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", 
  "TNEW", "TUNTIL", "TNIL", "TRESCUE", "TIN", "TFOR", "TCONTINUE", 
  "TYIELD", "TRETURN", "TBREAK", "'='", "'>'", "'<'", "TEQUALS", "'+'", 
  "'-'", "'*'", "'/'", "TCAST", "TLENGTH", "TRANGE", "'!'", "CUNARY", 
  "'.'", "'['", "'('", "'^'", "TSTATMETHOD", "')'", "'{'", "'}'", "';'", 
  "','", "'&'", "']'", "$accept", "program", "function", "block", "stmts", 
  "stmt", "node", "control", "args", "arg_names", "arg_names_list", 
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
     285,    61,    62,    60,   286,    43,    45,    42,    47,   287,
     288,   289,    33,   290,    46,    91,    40,    94,   291,    41,
     123,   125,    59,    44,    38,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    56,    57,    57,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    63,    63,    63,    63,    63,    64,
      64,    64,    65,    65,    65,    65,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    68,    69,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     7,     0,     1,     1,     2,     2,
       2,     5,     7,     5,     5,     7,     7,     7,     9,     3,
       5,     3,     0,     1,     2,     1,     1,     1,     1,     0,
       1,     3,     0,     1,     4,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     6,     5,     3,     3,     2,
       2,     2,     2,     4,     4,     2,     6,     6,     3,     4,
       3,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,    76,     3,     0,    32,     0,     0,    33,
      36,    35,     0,     0,     5,     0,    37,    73,    74,    77,
       0,     0,    22,     0,     0,     0,     0,     0,    75,     0,
      27,    28,    25,    26,     0,     0,    29,     0,     5,     0,
       6,     7,     0,     0,    23,    71,    72,     0,    34,     0,
       0,     0,     0,    60,    62,    65,     0,    22,    24,     0,
      44,    45,     0,    30,     0,     0,     0,     4,     8,     9,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    61,
       0,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    42,     0,    21,    46,    47,    51,    52,
      50,    43,    48,    49,    53,    38,    39,    40,    41,    68,
       0,    57,    58,    54,     0,     0,     0,    19,    22,    22,
       0,     0,     0,    22,     0,    31,    63,     0,    29,    69,
      64,    29,     0,    11,    13,     0,     0,     0,    14,     0,
      56,     0,     0,     0,    20,    22,     0,     0,    22,    22,
      67,    55,    66,    12,    15,    16,    17,     0,    22,    18
};

/* YYDEFGOTO[NTERM-NUM]. */
static const signed char yydefgoto[] =
{
      -1,     1,     4,    39,    40,    41,    42,    43,    62,     8,
       9,    44,    45,    46,    59
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -86
static const short yypact[] =
{
     -86,    41,   -86,   -86,   -86,   -43,     6,     9,   -29,   -28,
     -86,   -86,   -19,     8,   152,     9,   -86,   -86,   -86,   -86,
     -17,    -4,   202,    -3,     9,     9,    46,    11,   -86,    22,
     -86,   -86,   265,   -86,   265,   265,   265,   265,   152,    31,
     152,   -86,    34,    38,   532,   -86,    20,     0,   -86,   265,
     265,    36,     9,   -86,   -86,   -86,   265,   265,   532,     5,
      61,    61,    43,   532,   336,    15,    52,   -86,   -86,   -86,
     -86,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,     9,   265,   265,   265,   -86,   -86,
     265,   265,     9,   -16,   364,   392,    51,    65,    88,   420,
      66,   265,   -86,   -86,   265,   -86,   546,   546,   155,   155,
      56,   155,   155,   155,    56,    72,    72,    61,    61,   -24,
     228,   532,   532,   532,   -32,    74,   265,   -86,   202,   202,
     265,   265,   265,   202,   265,   532,    61,   265,   265,    90,
     -86,   265,   280,   114,   -86,   448,   476,   504,   -86,   308,
     532,    12,   265,    14,   -86,   202,    71,    73,   202,   265,
     -86,   532,   -86,   -86,   -86,   -86,   -86,    77,   202,   -86
};

/* YYPGOTO[NTERM-NUM].  */
static const signed char yypgoto[] =
{
     -86,   -86,   -86,    89,   -86,   -21,   -55,   -86,   -85,   -86,
     -86,    -2,   -86,     3,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.  */
#define YYTABLE_NINF -1
static const short yytable[] =
{
      47,    51,   100,     6,     5,     3,   124,   137,    47,    10,
      11,     3,    55,     3,     3,   126,    16,   140,    48,    68,
      12,   101,   138,    65,    47,    13,    47,    53,    54,    49,
      58,    14,    60,    61,    63,    64,   127,    86,    87,    88,
      89,     2,    50,    52,    92,    96,     3,    94,    95,    92,
      93,    90,    19,   151,    99,    98,   153,    56,    97,    92,
       7,   160,    15,   162,   104,   101,    91,   101,    57,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,    67,   120,   121,   122,    69,   119,   123,    63,
      70,    80,    81,    82,    83,   125,   101,   130,   102,   135,
      84,    85,   136,   105,   167,    84,    85,   143,   144,    82,
      83,   131,   148,   132,    47,    47,    84,    85,   134,    47,
     141,   152,   155,   164,   142,   165,   168,    66,   145,   146,
     147,     0,   149,     0,   163,   150,    63,   166,     0,    63,
       0,    47,     0,     0,    47,     0,     0,   169,     0,     0,
     161,     0,     0,     0,    47,    17,    18,     3,    19,    20,
       0,    21,    22,     0,     0,     0,     0,     0,    23,     0,
      75,    24,    25,    26,    27,    28,     0,     0,    29,    30,
      31,    32,    33,     0,     0,     0,     0,     0,    34,    79,
      80,    81,    82,    83,    35,     0,     0,    36,    37,    84,
      85,     0,    38,     0,   -22,    17,    18,     3,    19,    20,
       0,    21,    22,     0,     0,     0,     0,     0,    23,     0,
       0,    24,    25,    26,    27,    28,     0,     0,    29,    30,
      31,    32,    33,     0,     0,     0,     0,     0,    34,    71,
      72,    73,    74,    75,    35,     0,     0,    36,    37,     0,
       0,     0,    38,    76,     0,     0,     0,     0,     0,     0,
      77,    78,    79,    80,    81,    82,    83,     0,    17,    18,
       3,    19,    84,    85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   139,    24,    25,    26,     0,    28,     0,
       0,    71,    72,    73,    74,    75,     0,     0,     0,     0,
       0,    34,     0,     0,     0,    76,     0,    35,     0,     0,
      36,    37,    77,    78,    79,    80,    81,    82,    83,    71,
      72,    73,    74,    75,    84,    85,     0,     0,     0,     0,
       0,     0,   154,    76,     0,     0,     0,     0,     0,     0,
      77,    78,    79,    80,    81,    82,    83,    71,    72,    73,
      74,    75,    84,    85,     0,     0,     0,     0,     0,     0,
     159,    76,     0,     0,     0,     0,     0,     0,    77,    78,
      79,    80,    81,    82,    83,    71,    72,    73,    74,    75,
      84,    85,     0,     0,     0,   103,     0,     0,     0,    76,
       0,     0,     0,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,    71,    72,    73,    74,    75,    84,    85,
       0,     0,     0,   128,     0,     0,     0,    76,     0,     0,
       0,     0,     0,     0,    77,    78,    79,    80,    81,    82,
      83,    71,    72,    73,    74,    75,    84,    85,     0,     0,
       0,   129,     0,     0,     0,    76,     0,     0,     0,     0,
       0,     0,    77,    78,    79,    80,    81,    82,    83,    71,
      72,    73,    74,    75,    84,    85,     0,     0,     0,   133,
       0,     0,     0,    76,     0,     0,     0,     0,     0,     0,
      77,    78,    79,    80,    81,    82,    83,    71,    72,    73,
      74,    75,    84,    85,     0,     0,     0,   156,     0,     0,
       0,    76,     0,     0,     0,     0,     0,     0,    77,    78,
      79,    80,    81,    82,    83,    71,    72,    73,    74,    75,
      84,    85,     0,     0,     0,   157,     0,     0,     0,    76,
       0,     0,     0,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,    71,    72,    73,    74,    75,    84,    85,
       0,     0,     0,   158,     0,     0,     0,    76,     0,    73,
      74,    75,     0,     0,    77,    78,    79,    80,    81,    82,
      83,    76,     0,     0,     0,     0,    84,    85,    77,    78,
      79,    80,    81,    82,    83,     0,     0,     0,     0,     0,
      84,    85
};

static const short yycheck[] =
{
      14,    22,    57,    46,     1,     5,    91,    31,    22,     6,
       7,     5,    26,     5,     5,    31,    13,    49,    15,    40,
      49,    53,    46,    37,    38,    53,    40,    24,    25,    46,
      32,    50,    34,    35,    36,    37,    52,    17,    18,    19,
      20,     0,    46,    46,    44,     9,     5,    49,    50,    44,
      47,    31,     6,   138,    56,    52,   141,    46,    22,    44,
      54,    49,    54,    49,    49,    53,    46,    53,    46,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    51,    85,    86,    87,    52,    84,    90,    91,
      52,    35,    36,    37,    38,    92,    53,    46,    55,   101,
      44,    45,   104,    51,   159,    44,    45,   128,   129,    37,
      38,    46,   133,    25,   128,   129,    44,    45,    52,   133,
      46,    31,     8,    52,   126,    52,    49,    38,   130,   131,
     132,    -1,   134,    -1,   155,   137,   138,   158,    -1,   141,
      -1,   155,    -1,    -1,   158,    -1,    -1,   168,    -1,    -1,
     152,    -1,    -1,    -1,   168,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      15,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    34,
      35,    36,    37,    38,    42,    -1,    -1,    45,    46,    44,
      45,    -1,    50,    -1,    52,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    19,    20,    21,    22,    23,    -1,    -1,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    11,
      12,    13,    14,    15,    42,    -1,    -1,    45,    46,    -1,
      -1,    -1,    50,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    -1,     3,     4,
       5,     6,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    19,    20,    21,    -1,    23,    -1,
      -1,    11,    12,    13,    14,    15,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    25,    -1,    42,    -1,    -1,
      45,    46,    32,    33,    34,    35,    36,    37,    38,    11,
      12,    13,    14,    15,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    11,    12,    13,
      14,    15,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    11,    12,    13,    14,    15,
      44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    11,    12,    13,    14,    15,    44,    45,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    11,    12,    13,    14,    15,    44,    45,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    11,
      12,    13,    14,    15,    44,    45,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    11,    12,    13,
      14,    15,    44,    45,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    11,    12,    13,    14,    15,
      44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      36,    37,    38,    11,    12,    13,    14,    15,    44,    45,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    25,    -1,    13,
      14,    15,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    25,    -1,    -1,    -1,    -1,    44,    45,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    57,     0,     5,    58,    69,    46,    54,    65,    66,
      69,    69,    49,    53,    50,    54,    69,     3,     4,     6,
       7,     9,    10,    16,    19,    20,    21,    22,    23,    26,
      27,    28,    29,    30,    36,    42,    45,    46,    50,    59,
      60,    61,    62,    63,    67,    68,    69,    70,    69,    46,
      46,    61,    46,    69,    69,    70,    46,    46,    67,    70,
      67,    67,    64,    67,    67,    70,    59,    51,    61,    52,
      52,    11,    12,    13,    14,    15,    25,    32,    33,    34,
      35,    36,    37,    38,    44,    45,    17,    18,    19,    20,
      31,    46,    44,    69,    67,    67,     9,    22,    69,    67,
      62,    53,    55,    49,    49,    51,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    69,
      67,    67,    67,    67,    64,    69,    31,    52,    49,    49,
      46,    46,    25,    49,    52,    67,    67,    31,    46,    55,
      49,    46,    67,    61,    61,    67,    67,    67,    61,    67,
      67,    64,    31,    64,    52,     8,    49,    49,    49,    52,
      49,    67,    49,    61,    52,    52,    61,    62,    49,    61
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


/*----------------------------------------------------------.
| yyreport_parse_error -- report a parse error in YYSTATE.  |
`----------------------------------------------------------*/

static void
#if defined (__STDC__) || defined (__cplusplus)
yyreport_parse_error (int yystate, int yychar, YYSTYPE yyvalue)
#else
yyreport_parse_error (yystate, yychar, yyvalue)
    int yystate;
    int yychar;
    YYSTYPE yyvalue;
#endif
{
#if YYERROR_VERBOSE
  int yyn = yypact[yystate];

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

  /* Pacify ``unused variable'' warnings.  */
  (void) yystate;
  (void) yychar;
  (void) yyvalue;
  
}


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

  yyn += yychar1;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

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
#line 87 "grammar.y"
    { sxp_new_func (sxp_parser_info, yyvsp[-6].id, (SX_ARRAY )yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
    break;

  case 5:
#line 90 "grammar.y"
    { yyval.node = NULL; }
    break;

  case 6:
#line 91 "grammar.y"
    { yyval.node = yyvsp[0].node; }
    break;

  case 7:
#line 94 "grammar.y"
    { yyval.node = yyvsp[0].node; }
    break;

  case 8:
#line 95 "grammar.y"
    { yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 9:
#line 98 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 10:
#line 99 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 11:
#line 100 "grammar.y"
    { yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;

  case 12:
#line 101 "grammar.y"
    { yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 13:
#line 102 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_WD); }
    break;

  case 14:
#line 103 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_UD); }
    break;

  case 15:
#line 104 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DW); }
    break;

  case 16:
#line 105 "grammar.y"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DU); }
    break;

  case 17:
#line 107 "grammar.y"
    { yyval.node = sxp_new_for (sxp_parser_info, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 18:
#line 108 "grammar.y"
    { yyval.node = sxp_new_cfor (sxp_parser_info, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 19:
#line 110 "grammar.y"
    {}
    break;

  case 20:
#line 111 "grammar.y"
    {}
    break;

  case 21:
#line 113 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 22:
#line 116 "grammar.y"
    { yyval.node = NULL; }
    break;

  case 23:
#line 117 "grammar.y"
    { yyval.node = sxp_new_stmt (sxp_parser_info, yyvsp[0].node); }
    break;

  case 24:
#line 120 "grammar.y"
    { yyval.node = sxp_new_retr (sxp_parser_info, yyvsp[0].node); }
    break;

  case 25:
#line 121 "grammar.y"
    { yyval.node = sxp_new_retr (sxp_parser_info, NULL); }
    break;

  case 26:
#line 122 "grammar.y"
    { yyval.node = sxp_new_brak (sxp_parser_info); }
    break;

  case 27:
#line 123 "grammar.y"
    { yyval.node = sxp_new_cont (sxp_parser_info); }
    break;

  case 28:
#line 124 "grammar.y"
    { yyval.node = sxp_new_yeld (sxp_parser_info); }
    break;

  case 29:
#line 127 "grammar.y"
    { yyval.node = NULL; }
    break;

  case 30:
#line 128 "grammar.y"
    { yyval.node = yyvsp[0].node; }
    break;

  case 31:
#line 129 "grammar.y"
    { yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 32:
#line 132 "grammar.y"
    { yyval.args.args = NULL; yyval.args.varg = 0; }
    break;

  case 33:
#line 133 "grammar.y"
    { yyval.args.args = yyvsp[0].value; yyval.args.varg = 0; }
    break;

  case 34:
#line 134 "grammar.y"
    { yyval.args.args = yyvsp[-3].value; yyval.args.varg = yyvsp[0].id; }
    break;

  case 35:
#line 135 "grammar.y"
    { yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;

  case 36:
#line 138 "grammar.y"
    { yyval.value = sx_append (sxp_parser_info->system, sx_new_array (sxp_parser_info->system, 0, NULL), sx_new_num (yyvsp[0].id)); }
    break;

  case 37:
#line 139 "grammar.y"
    { yyval.value = sx_append (sxp_parser_info->system, yyvsp[-2].value, sx_new_num (yyvsp[0].id)); }
    break;

  case 38:
#line 142 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 39:
#line 143 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 40:
#line 144 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 41:
#line 145 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 42:
#line 146 "grammar.y"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 43:
#line 148 "grammar.y"
    { yyval.node = sxp_new_in (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 44:
#line 150 "grammar.y"
    { yyval.node = sxp_new_nega (sxp_parser_info, yyvsp[0].node); }
    break;

  case 45:
#line 152 "grammar.y"
    { yyval.node = sxp_new_not (sxp_parser_info, yyvsp[0].node); }
    break;

  case 46:
#line 153 "grammar.y"
    { yyval.node = sxp_new_and (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 47:
#line 154 "grammar.y"
    { yyval.node = sxp_new_or (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 48:
#line 156 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 49:
#line 157 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 50:
#line 158 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 51:
#line 159 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 52:
#line 160 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 53:
#line 161 "grammar.y"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 54:
#line 163 "grammar.y"
    { yyval.node = sxp_new_assi (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 55:
#line 164 "grammar.y"
    { yyval.node = sxp_new_set (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;

  case 56:
#line 165 "grammar.y"
    { yyval.node = sxp_new_setm (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 57:
#line 167 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 58:
#line 168 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, sxp_new_nega (sxp_parser_info, yyvsp[0].node)); }
    break;

  case 59:
#line 169 "grammar.y"
    { yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
    break;

  case 60:
#line 170 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
    break;

  case 61:
#line 171 "grammar.y"
    { yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
    break;

  case 62:
#line 172 "grammar.y"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
    break;

  case 63:
#line 174 "grammar.y"
    { yyval.node = sxp_new_cast (sxp_parser_info, yyvsp[0].node, yyvsp[-2].id); }
    break;

  case 64:
#line 175 "grammar.y"
    { yyval.node = sxp_new_call (sxp_parser_info, yyvsp[-3].id, yyvsp[-1].node); }
    break;

  case 65:
#line 177 "grammar.y"
    { yyval.node = sxp_new_new (sxp_parser_info, yyvsp[0].id); }
    break;

  case 66:
#line 178 "grammar.y"
    { yyval.node = sxp_new_smet (sxp_parser_info, yyvsp[-5].id, yyvsp[-3].id, yyvsp[-1].node); }
    break;

  case 67:
#line 179 "grammar.y"
    { yyval.node = sxp_new_meth (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].id, yyvsp[-1].node); }
    break;

  case 68:
#line 180 "grammar.y"
    { yyval.node = sxp_new_getm (sxp_parser_info, yyvsp[-2].node, yyvsp[0].id); }
    break;

  case 69:
#line 182 "grammar.y"
    { yyval.node = sxp_new_indx (sxp_parser_info, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 70:
#line 183 "grammar.y"
    { yyval.node = sxp_new_arry (sxp_parser_info, yyvsp[-1].node); }
    break;

  case 71:
#line 185 "grammar.y"
    { yyval.node = sxp_new_data (sxp_parser_info, yyvsp[0].value); }
    break;

  case 72:
#line 187 "grammar.y"
    { yyval.node = sxp_new_look (sxp_parser_info, yyvsp[0].id); }
    break;

  case 73:
#line 191 "grammar.y"
    { yyval.value = yyvsp[0].value;  }
    break;

  case 74:
#line 192 "grammar.y"
    { yyval.value = yyvsp[0].value; }
    break;

  case 75:
#line 193 "grammar.y"
    { yyval.value = NULL; }
    break;

  case 76:
#line 196 "grammar.y"
    { yyval.id = yyvsp[0].id; }
    break;

  case 77:
#line 199 "grammar.y"
    { yyval.id = yyvsp[0].id; }
    break;


    }

/* Line 1086 of /usr/share/bison/yacc.c.  */
#line 1690 "y.tab.c"

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
      yyreport_parse_error (yystate, yychar, yylval);
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


#line 202 "grammar.y"


int
sxerror (const char *str) {
	sxp_error (sxp_parser_info, str);
	return 1;
}

int
sxwrap (void) {
	return 1;
}

int
sxp_load_file (SX_MODULE module, const char *file) {
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

	sxp_parser_info = sxp_new_info (module);
	if (sxp_parser_info == NULL) {
		if (file != NULL)
			fclose (sxin);
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}
	if (file != NULL)
		sxp_parser_info->file = sx_new_str (module->system, file);

	sxp_parser_inbuf = NULL;
	flags = module->system->flags;
	module->system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	module->system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (module->system);

	return ret;
}

int
sxp_load_string (SX_MODULE module, const char *buf) {
	int ret, flags;

	if (buf == NULL) {
		return 1;
	}

	sxp_parser_info = sxp_new_info (module);
	if (sxp_parser_info == NULL) {
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}

	sxin = NULL;
	sxp_parser_inbuf = buf;
	flags = module->system->flags;
	module->system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	module->system->flags = flags;

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (module->system);

	return ret;
}

