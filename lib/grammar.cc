/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
     TAG = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     DO = 266,
     AND = 267,
     OR = 268,
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
#define NUMBER 258
#define STRING 259
#define IDENTIFIER 260
#define TYPE 261
#define TAG 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define DO 266
#define AND 267
#define OR 268
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
#line 28 "grammar.yy"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <errno.h>

	#include "scriptix.h"
	#include "system.h"
	
	using namespace Scriptix;
	
	#include "parser.h"

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int yyerror (const char *);
	extern int yylex (void);
	int yyparse (void);

	SXP_INFO *sxp_parser_info = NULL;

	static SXP_NODE* _sxp_namelist_to_lookups (SXP_INFO* info, sx_name_id* list);

	#define YYERROR_VERBOSE 1
	#define SXERROR_VERBOSE 1

	/* stupid BISON fix */
	#define __attribute__(x)


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
#line 59 "grammar.yy"
typedef union YYSTYPE {
	SXP_NODE* node;
	Value* value;
	sx_name_id id;
	sx_name_id* name_list;
	struct _sxp_arg_list args;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 189 "grammar.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 201 "grammar.cc"

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
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

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
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   741

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  22
/* YYNRULES -- Number of rules. */
#define YYNRULES  94
/* YYNRULES -- Number of states. */
#define YYNSTATES  216

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,     2,     2,     2,    56,     2,
      47,    50,    38,    36,    54,    37,    45,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    53,
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
       0,     0,     3,     4,     7,    10,    13,    21,    30,    31,
      41,    46,    47,    49,    51,    54,    57,    60,    66,    74,
      80,    86,    94,   102,   112,   116,   117,   119,   122,   124,
     126,   128,   130,   132,   136,   140,   146,   147,   149,   154,
     157,   159,   163,   164,   166,   174,   184,   196,   200,   205,
     208,   212,   216,   220,   224,   228,   232,   236,   239,   242,
     246,   250,   254,   258,   262,   266,   270,   274,   278,   285,
     289,   293,   296,   299,   302,   305,   310,   315,   318,   321,
     326,   331,   337,   341,   346,   350,   354,   356,   358,   360,
     362,   364,   366,   368,   370
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      59,     0,    -1,    -1,    59,    60,    -1,    59,    62,    -1,
      59,     1,    -1,    77,    47,    70,    50,    51,    63,    52,
      -1,    29,    77,    47,    70,    50,    51,    63,    52,    -1,
      -1,    77,    61,    77,    47,    70,    50,    51,    63,    52,
      -1,    77,    32,    76,    53,    -1,    -1,    64,    -1,    65,
      -1,    64,    65,    -1,    66,    53,    -1,    67,    53,    -1,
       8,    47,    75,    50,    65,    -1,     8,    47,    75,    50,
      65,     9,    65,    -1,    10,    47,    75,    50,    65,    -1,
      22,    47,    75,    50,    65,    -1,    11,    65,    10,    47,
      75,    50,    53,    -1,    11,    65,    22,    47,    75,    50,
      53,    -1,    26,    47,    66,    53,    75,    53,    66,    50,
      65,    -1,    51,    63,    52,    -1,    -1,    75,    -1,    30,
      75,    -1,    30,    -1,    31,    -1,    27,    -1,    28,    -1,
      75,    -1,    68,    54,    75,    -1,     4,    55,    75,    -1,
      69,    54,     4,    55,    75,    -1,    -1,    71,    -1,    71,
      54,    56,    77,    -1,    56,    77,    -1,    77,    -1,    71,
      54,    77,    -1,    -1,    71,    -1,    11,    47,    72,    50,
      51,    63,    52,    -1,    11,    47,    72,    53,    72,    50,
      51,    63,    52,    -1,    11,    47,    72,    50,    55,    47,
      72,    50,    51,    63,    52,    -1,    47,    68,    50,    -1,
      47,    68,    50,    73,    -1,    47,    50,    -1,    47,    50,
      73,    -1,    75,    36,    75,    -1,    75,    37,    75,    -1,
      75,    38,    75,    -1,    75,    39,    75,    -1,    47,    75,
      50,    -1,    75,    25,    75,    -1,    37,    75,    -1,    43,
      75,    -1,    75,    12,    75,    -1,    75,    13,    75,    -1,
      75,    33,    75,    -1,    75,    34,    75,    -1,    75,    16,
      75,    -1,    75,    14,    75,    -1,    75,    15,    75,    -1,
      75,    35,    75,    -1,    77,    32,    75,    -1,    75,    46,
      75,    57,    32,    75,    -1,    77,    17,    75,    -1,    77,
      18,    75,    -1,    77,    19,    -1,    19,    77,    -1,    77,
      20,    -1,    20,    77,    -1,    47,    79,    50,    75,    -1,
      79,    47,    75,    50,    -1,    75,    74,    -1,    21,    79,
      -1,    79,    45,    77,    74,    -1,    75,    45,    77,    74,
      -1,    75,    55,    78,    32,    75,    -1,    75,    55,    78,
      -1,    75,    46,    75,    57,    -1,    46,    68,    57,    -1,
      46,    69,    57,    -1,    76,    -1,    77,    -1,     1,    -1,
       3,    -1,     4,    -1,    23,    -1,     5,    -1,    77,    -1,
       6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    97,    97,    98,    99,   100,   103,   104,   105,   105,
     114,   117,   118,   121,   122,   125,   126,   127,   128,   129,
     130,   131,   132,   134,   136,   139,   140,   143,   144,   145,
     146,   147,   150,   151,   154,   155,   158,   159,   160,   161,
     164,   165,   168,   169,   172,   173,   174,   177,   178,   179,
     180,   183,   184,   185,   186,   187,   189,   191,   193,   194,
     195,   197,   198,   199,   200,   201,   202,   204,   205,   207,
     208,   209,   210,   211,   212,   214,   215,   217,   219,   220,
     221,   222,   223,   225,   226,   227,   229,   231,   233,   237,
     238,   239,   242,   245,   247
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IDENTIFIER", "TYPE", 
  "TAG", "IF", "ELSE", "WHILE", "DO", "AND", "OR", "TGTE", "TLTE", "TNE", 
  "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", "TNEW", 
  "TUNTIL", "TNIL", "TRESCUE", "TIN", "TFOR", "TCONTINUE", "TYIELD", 
  "TPUBLIC", "TRETURN", "TBREAK", "'='", "'>'", "'<'", "TEQUALS", "'+'", 
  "'-'", "'*'", "'/'", "TCAST", "TLENGTH", "TRANGE", "'!'", "CUNARY", 
  "'.'", "'['", "'('", "'^'", "TSTATMETHOD", "')'", "'{'", "'}'", "';'", 
  "','", "':'", "'&'", "']'", "$accept", "program", "function", "@1", 
  "global", "block", "stmts", "stmt", "node", "control", "args", 
  "assoc_args", "arg_names", "arg_names_list", "anon_name_args", 
  "anon_call", "func_args", "expr", "data", "name", "namenode", "type", 0
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
      41,   123,   125,    59,    44,    58,    38,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    58,    59,    59,    59,    59,    60,    60,    61,    60,
      62,    63,    63,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    66,    66,    67,    67,    67,
      67,    67,    68,    68,    69,    69,    70,    70,    70,    70,
      71,    71,    72,    72,    73,    73,    73,    74,    74,    74,
      74,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    76,
      76,    76,    77,    78,    79
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     2,     2,     7,     8,     0,     9,
       4,     0,     1,     1,     2,     2,     2,     5,     7,     5,
       5,     7,     7,     9,     3,     0,     1,     2,     1,     1,
       1,     1,     1,     3,     3,     5,     0,     1,     4,     2,
       1,     3,     0,     1,     7,     9,    11,     3,     4,     2,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     6,     3,
       3,     2,     2,     2,     2,     4,     4,     2,     2,     4,
       4,     5,     3,     4,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,     5,    92,     0,     3,     4,     8,     0,
       0,    36,     0,    36,    89,    90,    91,     0,     0,     0,
      37,    40,     0,     0,    10,    39,     0,     0,    36,     0,
       0,     0,    41,     0,     0,    88,    94,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    31,     0,    29,     0,
       0,     0,     0,     0,     0,     0,    13,     0,     0,    26,
      86,    87,     0,    38,     0,     0,     0,     0,     0,    72,
      74,    78,     0,     0,    27,    57,    58,    90,     0,     0,
      32,     0,     0,     0,     6,    14,    15,    16,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    77,     0,     0,    71,    73,
       0,     0,     0,     0,     7,     0,     0,     0,     0,     0,
       0,     0,     0,    84,     0,    85,    55,     0,    24,    59,
      60,    64,    65,    63,    56,    61,    62,    66,    51,    52,
      53,    54,     0,     0,    49,     0,    93,    82,    69,    70,
      67,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    33,     0,    75,    80,    83,     0,    50,    47,     0,
      79,    76,     9,    17,    19,     0,     0,    20,     0,     0,
       0,    42,    48,    81,     0,     0,     0,     0,    35,    68,
      43,     0,    18,    21,    22,     0,     0,     0,    42,     0,
       0,     0,     0,    23,     0,    42,     0,    44,     0,     0,
       0,     0,     0,    45,     0,    46
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,     6,    12,     7,    54,    55,    56,    57,    58,
      78,    79,    19,    20,   191,   167,   105,    59,    60,    61,
     147,    62
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -125
static const short yypact[] =
{
    -125,    31,  -125,  -125,  -125,    19,  -125,  -125,   -13,   -22,
      12,     8,    19,     8,  -125,  -125,  -125,   -11,    19,    -7,
      13,  -125,    26,    37,  -125,  -125,    46,     9,     8,    69,
     138,    19,  -125,    76,   138,  -125,  -125,    82,    83,   248,
      19,    19,   127,    87,    90,  -125,  -125,    85,  -125,   360,
     360,   367,   360,   138,    88,   195,  -125,    92,    97,   646,
    -125,    52,    64,  -125,   100,   101,   360,   360,    11,  -125,
    -125,  -125,   360,   283,   646,    47,    47,    99,    25,    62,
     646,   414,    51,   103,  -125,  -125,  -125,  -125,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,    19,   360,   304,    19,  -125,   360,   360,  -125,  -125,
     360,    19,   360,   138,  -125,   442,   470,   105,   109,   498,
     110,   360,   360,  -125,   166,  -125,  -125,   360,  -125,   661,
     661,   674,   674,   686,   674,   674,   674,   686,   189,   189,
      47,    47,   124,   386,   161,    45,  -125,   141,   646,   646,
     646,   124,   526,   122,   248,   248,   360,   360,   248,   360,
     646,   646,   123,    47,  -125,   145,   135,  -125,   161,   360,
    -125,  -125,  -125,   174,  -125,   554,   582,  -125,   610,   360,
     360,    19,  -125,   646,   248,   133,   134,   312,   646,   646,
     139,    74,  -125,  -125,  -125,   142,    19,   -14,    19,   248,
     138,   147,   152,  -125,   136,    19,   156,  -125,   158,   138,
     159,   157,   138,  -125,   160,  -125
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -125,  -125,  -125,  -125,  -125,   -33,  -125,   -37,   -64,  -125,
     108,  -125,    48,  -124,   -91,    56,  -113,   -44,   203,    -1,
    -125,    33
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -29
static const short yytable[] =
{
       8,    65,    68,    74,     9,    75,    76,    80,    81,   120,
      21,    22,    21,     4,     4,    14,    15,    25,    85,    10,
      83,   117,   115,   116,     4,    13,    32,    21,   119,   164,
      63,     2,     3,   118,    11,    16,     4,   200,   170,    69,
      70,   201,    24,    26,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   190,   143,    80,
       5,    23,   148,   149,    18,    31,   150,    27,   152,   106,
     107,   108,   109,    28,   190,    71,    33,   160,   161,   122,
     153,   190,   123,   163,   110,    82,    35,    29,    14,    15,
       4,    36,   101,   102,   103,   168,   111,    30,   112,   122,
     142,   127,   104,   146,    40,    41,    42,   202,    16,   111,
     151,   112,   175,   176,   208,   178,   124,   173,   174,   125,
      34,   177,    49,   195,   197,   183,    64,   198,    50,    66,
      67,    51,    52,    36,    72,   188,   189,    73,   -28,    35,
      84,    14,    15,     4,    36,    86,    37,   192,    38,    39,
      87,   113,   156,   114,   121,   128,   157,    40,    41,    42,
      43,    16,   203,   159,    44,    45,    46,   204,    47,    48,
     162,   103,   166,   169,   172,    49,   211,   180,   179,   214,
      21,    50,   181,   184,    51,    52,   193,   194,   207,    53,
     -11,   -25,   199,   196,   205,    32,    35,    21,    14,    15,
       4,    36,   206,    37,    21,    38,    39,   209,   210,   213,
     212,   145,   215,    17,    40,    41,    42,    43,    16,     0,
       0,    44,    45,    46,   182,    47,    48,    99,   100,     0,
       0,     0,    49,     0,   101,   102,   103,     0,    50,     0,
       0,    51,    52,     0,   104,     0,    53,   -12,   -25,    35,
       0,    14,    15,     4,    36,     0,    37,     0,    38,    39,
       0,     0,     0,     0,     0,     0,     0,    40,    41,    42,
      43,    16,     0,     0,    44,    45,    46,     0,    47,    48,
       0,     0,     0,     0,    35,    49,    14,    15,     4,    36,
       0,    50,     0,     0,    51,    52,     0,     0,     0,    53,
       0,   -25,    40,    41,    42,    35,    16,    14,    15,     4,
      36,     0,     0,    35,     0,    14,    15,     4,    36,     0,
      49,     0,     0,    40,    41,    42,    50,    16,     0,    51,
      52,    40,    41,    42,     0,    16,   -25,     0,     0,     0,
       0,    49,     0,     0,     0,     0,     0,    50,     0,    49,
      51,    52,     0,     0,   144,    50,     0,     0,    51,    52,
       0,    35,   -25,    14,    15,     4,    36,     0,    35,     0,
      14,    77,     4,    36,     0,     0,     0,     0,     0,    40,
      41,    42,     0,    16,     0,     0,    40,    41,    42,     0,
      16,     0,     0,     0,     0,     0,     0,    49,    88,    89,
      90,    91,    92,    50,    49,     0,    51,    52,     0,     0,
      50,    93,     0,    51,    52,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,    88,    89,    90,    91,
      92,   101,   102,   103,     0,     0,     0,     0,     0,    93,
       0,   104,     0,   165,     0,     0,     0,    94,    95,    96,
      97,    98,    99,   100,    88,    89,    90,    91,    92,   101,
     102,   103,     0,     0,   126,     0,     0,    93,     0,   104,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,    88,    89,    90,    91,    92,   101,   102,   103,
       0,     0,   154,     0,     0,    93,     0,   104,     0,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,   100,
      88,    89,    90,    91,    92,   101,   102,   103,     0,     0,
     155,     0,     0,    93,     0,   104,     0,     0,     0,     0,
       0,    94,    95,    96,    97,    98,    99,   100,    88,    89,
      90,    91,    92,   101,   102,   103,     0,     0,   158,     0,
       0,    93,     0,   104,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,    88,    89,    90,    91,
      92,   101,   102,   103,     0,     0,   171,     0,     0,    93,
       0,   104,     0,     0,     0,     0,     0,    94,    95,    96,
      97,    98,    99,   100,    88,    89,    90,    91,    92,   101,
     102,   103,     0,     0,   185,     0,     0,    93,     0,   104,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,    88,    89,    90,    91,    92,   101,   102,   103,
       0,     0,   186,     0,     0,    93,     0,   104,     0,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,   100,
       0,     0,     0,     0,     0,   101,   102,   103,    88,    89,
      90,    91,    92,   187,     0,   104,     0,     0,     0,     0,
       0,    93,     0,     0,     0,    90,    91,    92,     0,    94,
      95,    96,    97,    98,    99,   100,    93,     0,     0,     0,
      92,   101,   102,   103,    94,    95,    96,    97,    98,    99,
     100,   104,     0,     0,     0,     0,   101,   102,   103,    96,
      97,    98,    99,   100,     0,     0,   104,     0,     0,   101,
     102,   103,    97,    98,    99,   100,     0,     0,     0,   104,
       0,   101,   102,   103,     0,     0,     0,     0,     0,     0,
       0,   104
};

static const short yycheck[] =
{
       1,    34,    39,    47,     5,    49,    50,    51,    52,    73,
      11,    12,    13,     5,     5,     3,     4,    18,    55,    32,
      53,    10,    66,    67,     5,    47,    27,    28,    72,   142,
      31,     0,     1,    22,    47,    23,     5,    51,   151,    40,
      41,    55,    53,    50,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   181,   102,   103,
      29,    13,   106,   107,    56,    56,   110,    54,   112,    17,
      18,    19,    20,    47,   198,    42,    28,   121,   122,    54,
     113,   205,    57,   127,    32,    52,     1,    50,     3,     4,
       5,     6,    45,    46,    47,    50,    45,    51,    47,    54,
     101,    50,    55,   104,    19,    20,    21,   198,    23,    45,
     111,    47,   156,   157,   205,   159,    54,   154,   155,    57,
      51,   158,    37,   187,    50,   169,    50,    53,    43,    47,
      47,    46,    47,     6,    47,   179,   180,    47,    53,     1,
      52,     3,     4,     5,     6,    53,     8,   184,    10,    11,
      53,    51,    47,    52,    55,    52,    47,    19,    20,    21,
      22,    23,   199,    53,    26,    27,    28,   200,    30,    31,
       4,    47,    11,    32,    52,    37,   209,    32,    55,   212,
     181,    43,    47,     9,    46,    47,    53,    53,    52,    51,
      52,    53,    50,    54,    47,   196,     1,   198,     3,     4,
       5,     6,    50,     8,   205,    10,    11,    51,    50,    52,
      51,   103,    52,    10,    19,    20,    21,    22,    23,    -1,
      -1,    26,    27,    28,   168,    30,    31,    38,    39,    -1,
      -1,    -1,    37,    -1,    45,    46,    47,    -1,    43,    -1,
      -1,    46,    47,    -1,    55,    -1,    51,    52,    53,     1,
      -1,     3,     4,     5,     6,    -1,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    -1,    -1,    26,    27,    28,    -1,    30,    31,
      -1,    -1,    -1,    -1,     1,    37,     3,     4,     5,     6,
      -1,    43,    -1,    -1,    46,    47,    -1,    -1,    -1,    51,
      -1,    53,    19,    20,    21,     1,    23,     3,     4,     5,
       6,    -1,    -1,     1,    -1,     3,     4,     5,     6,    -1,
      37,    -1,    -1,    19,    20,    21,    43,    23,    -1,    46,
      47,    19,    20,    21,    -1,    23,    53,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    -1,    -1,    43,    -1,    37,
      46,    47,    -1,    -1,    50,    43,    -1,    -1,    46,    47,
      -1,     1,    50,     3,     4,     5,     6,    -1,     1,    -1,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    -1,    23,    -1,    -1,    19,    20,    21,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    37,    12,    13,
      14,    15,    16,    43,    37,    -1,    46,    47,    -1,    -1,
      43,    25,    -1,    46,    47,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    12,    13,    14,    15,
      16,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    55,    -1,    57,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    12,    13,    14,    15,    16,    45,
      46,    47,    -1,    -1,    50,    -1,    -1,    25,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    12,    13,    14,    15,    16,    45,    46,    47,
      -1,    -1,    50,    -1,    -1,    25,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      12,    13,    14,    15,    16,    45,    46,    47,    -1,    -1,
      50,    -1,    -1,    25,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    12,    13,
      14,    15,    16,    45,    46,    47,    -1,    -1,    50,    -1,
      -1,    25,    -1,    55,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    12,    13,    14,    15,
      16,    45,    46,    47,    -1,    -1,    50,    -1,    -1,    25,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    12,    13,    14,    15,    16,    45,
      46,    47,    -1,    -1,    50,    -1,    -1,    25,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    12,    13,    14,    15,    16,    45,    46,    47,
      -1,    -1,    50,    -1,    -1,    25,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    12,    13,
      14,    15,    16,    53,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    14,    15,    16,    -1,    33,
      34,    35,    36,    37,    38,    39,    25,    -1,    -1,    -1,
      16,    45,    46,    47,    33,    34,    35,    36,    37,    38,
      39,    55,    -1,    -1,    -1,    -1,    45,    46,    47,    35,
      36,    37,    38,    39,    -1,    -1,    55,    -1,    -1,    45,
      46,    47,    36,    37,    38,    39,    -1,    -1,    -1,    55,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    59,     0,     1,     5,    29,    60,    62,    77,    77,
      32,    47,    61,    47,     3,     4,    23,    76,    56,    70,
      71,    77,    77,    70,    53,    77,    50,    54,    47,    50,
      51,    56,    77,    70,    51,     1,     6,     8,    10,    11,
      19,    20,    21,    22,    26,    27,    28,    30,    31,    37,
      43,    46,    47,    51,    63,    64,    65,    66,    67,    75,
      76,    77,    79,    77,    50,    63,    47,    47,    65,    77,
      77,    79,    47,    47,    75,    75,    75,     4,    68,    69,
      75,    75,    79,    63,    52,    65,    53,    53,    12,    13,
      14,    15,    16,    25,    33,    34,    35,    36,    37,    38,
      39,    45,    46,    47,    55,    74,    17,    18,    19,    20,
      32,    45,    47,    51,    52,    75,    75,    10,    22,    75,
      66,    55,    54,    57,    54,    57,    50,    50,    52,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    77,    75,    50,    68,    77,    78,    75,    75,
      75,    77,    75,    63,    50,    50,    47,    47,    50,    53,
      75,    75,     4,    75,    74,    57,    11,    73,    50,    32,
      74,    50,    52,    65,    65,    75,    75,    65,    75,    55,
      32,    47,    73,    75,     9,    50,    50,    53,    75,    75,
      71,    72,    65,    53,    53,    66,    54,    50,    53,    50,
      51,    55,    72,    65,    63,    47,    50,    52,    72,    51,
      50,    63,    51,    52,    63,    52
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

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
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

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
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
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
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
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
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
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

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
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

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



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

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
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
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
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

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
        case 6:
#line 103 "grammar.yy"
    { sxp_new_func (sxp_parser_info, yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 0); }
    break;

  case 7:
#line 104 "grammar.yy"
    { sxp_new_func (sxp_parser_info, yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 1); }
    break;

  case 8:
#line 105 "grammar.yy"
    { 
		if (!sxp_parser_info->system->ValidFunctionTag(IDToName (yyvsp[0].id))) {
			yyerror ("Unregistered tag");
			YYERROR;
		}
		yyval.id = yyvsp[0].id;
	}
    break;

  case 9:
#line 111 "grammar.yy"
    { sxp_new_func (sxp_parser_info, yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, IDToName(yyvsp[-7].id), 1); }
    break;

  case 10:
#line 114 "grammar.yy"
    { sxp_set_global (sxp_parser_info, yyvsp[-3].id, yyvsp[-1].value); }
    break;

  case 11:
#line 117 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 12:
#line 118 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 13:
#line 121 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 14:
#line 122 "grammar.yy"
    { yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 15:
#line 125 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 16:
#line 126 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 17:
#line 127 "grammar.yy"
    { yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;

  case 18:
#line 128 "grammar.yy"
    { yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 19:
#line 129 "grammar.yy"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_WD); }
    break;

  case 20:
#line 130 "grammar.yy"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_UD); }
    break;

  case 21:
#line 131 "grammar.yy"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DW); }
    break;

  case 22:
#line 132 "grammar.yy"
    { yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DU); }
    break;

  case 23:
#line 134 "grammar.yy"
    { yyval.node = sxp_new_cfor (sxp_parser_info, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 24:
#line 136 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 25:
#line 139 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 26:
#line 140 "grammar.yy"
    { yyval.node = sxp_new_stmt (sxp_parser_info, yyvsp[0].node); }
    break;

  case 27:
#line 143 "grammar.yy"
    { yyval.node = sxp_new_retr (sxp_parser_info, yyvsp[0].node); }
    break;

  case 28:
#line 144 "grammar.yy"
    { yyval.node = sxp_new_retr (sxp_parser_info, NULL); }
    break;

  case 29:
#line 145 "grammar.yy"
    { yyval.node = sxp_new_brak (sxp_parser_info); }
    break;

  case 30:
#line 146 "grammar.yy"
    { yyval.node = sxp_new_cont (sxp_parser_info); }
    break;

  case 31:
#line 147 "grammar.yy"
    { yyval.node = sxp_new_yeld (sxp_parser_info); }
    break;

  case 32:
#line 150 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 33:
#line 151 "grammar.yy"
    { yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 34:
#line 154 "grammar.yy"
    { yyval.node = sxp_new_data(sxp_parser_info,yyvsp[-2].value); sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 35:
#line 155 "grammar.yy"
    { yyval.node = yyvsp[-4].node; sxp_append (yyval.node, sxp_new_data(sxp_parser_info,yyvsp[-2].value)); sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 36:
#line 158 "grammar.yy"
    { yyval.args.args = NULL; yyval.args.varg = 0; }
    break;

  case 37:
#line 159 "grammar.yy"
    { yyval.args.args = yyvsp[0].name_list; yyval.args.varg = 0; }
    break;

  case 38:
#line 160 "grammar.yy"
    { yyval.args.args = yyvsp[-3].name_list; yyval.args.varg = yyvsp[0].id; }
    break;

  case 39:
#line 161 "grammar.yy"
    { yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;

  case 40:
#line 164 "grammar.yy"
    { yyval.name_list = sx_new_namelist (sxp_parser_info->system, 1, yyvsp[0].id); }
    break;

  case 41:
#line 165 "grammar.yy"
    { yyval.name_list = sx_namelist_append (sxp_parser_info->system, yyvsp[-2].name_list, yyvsp[0].id); }
    break;

  case 42:
#line 168 "grammar.yy"
    { yyval.name_list = NULL; }
    break;

  case 43:
#line 169 "grammar.yy"
    { yyval.name_list = yyvsp[0].name_list; }
    break;

  case 44:
#line 172 "grammar.yy"
    { yyval.node = sxp_new_afnc (sxp_parser_info, sxp_new_anon_func (sxp_parser_info, yyvsp[-4].name_list, 0, yyvsp[-1].node)); }
    break;

  case 45:
#line 173 "grammar.yy"
    { SXP_NODE* args = _sxp_namelist_to_lookups (sxp_parser_info, yyvsp[-4].name_list); yyval.node = sxp_new_clos (sxp_parser_info, sxp_new_anon_func (sxp_parser_info, sx_namelist_concat (sxp_parser_info->system, yyvsp[-6].name_list, yyvsp[-4].name_list), 0, yyvsp[-1].node), args); }
    break;

  case 46:
#line 174 "grammar.yy"
    { SXP_NODE* args = _sxp_namelist_to_lookups (sxp_parser_info, yyvsp[-4].name_list); yyval.node = sxp_new_clos (sxp_parser_info, sxp_new_anon_func (sxp_parser_info, sx_namelist_concat (sxp_parser_info->system, yyvsp[-8].name_list, yyvsp[-4].name_list), 0, yyvsp[-1].node), args); }
    break;

  case 47:
#line 177 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 48:
#line 178 "grammar.yy"
    { sxp_append (yyvsp[-2].node, yyvsp[0].node); yyval.node = yyvsp[-2].node; }
    break;

  case 49:
#line 179 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 50:
#line 180 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 51:
#line 183 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 52:
#line 184 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 53:
#line 185 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 54:
#line 186 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 55:
#line 187 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 56:
#line 189 "grammar.yy"
    { yyval.node = sxp_new_in (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 57:
#line 191 "grammar.yy"
    { yyval.node = sxp_new_nega (sxp_parser_info, yyvsp[0].node); }
    break;

  case 58:
#line 193 "grammar.yy"
    { yyval.node = sxp_new_not (sxp_parser_info, yyvsp[0].node); }
    break;

  case 59:
#line 194 "grammar.yy"
    { yyval.node = sxp_new_and (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 60:
#line 195 "grammar.yy"
    { yyval.node = sxp_new_or (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 61:
#line 197 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 62:
#line 198 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 63:
#line 199 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 64:
#line 200 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 65:
#line 201 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 66:
#line 202 "grammar.yy"
    { yyval.node = sxp_new_math (sxp_parser_info, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 67:
#line 204 "grammar.yy"
    { yyval.node = sxp_new_assi (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 68:
#line 205 "grammar.yy"
    { yyval.node = sxp_new_set (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;

  case 69:
#line 207 "grammar.yy"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 70:
#line 208 "grammar.yy"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, sxp_new_nega (sxp_parser_info, yyvsp[0].node)); }
    break;

  case 71:
#line 209 "grammar.yy"
    { yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, Number::Create (1))); }
    break;

  case 72:
#line 210 "grammar.yy"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, Number::Create (1))); }
    break;

  case 73:
#line 211 "grammar.yy"
    { yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, Number::Create (-1))); }
    break;

  case 74:
#line 212 "grammar.yy"
    { yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, Number::Create (-1))); }
    break;

  case 75:
#line 214 "grammar.yy"
    { yyval.node = sxp_new_cast (sxp_parser_info, yyvsp[0].node, yyvsp[-2].id); }
    break;

  case 76:
#line 215 "grammar.yy"
    { yyval.node = sxp_new_cast (sxp_parser_info, yyvsp[-1].node, yyvsp[-3].id); }
    break;

  case 77:
#line 217 "grammar.yy"
    { yyval.node = sxp_new_call (sxp_parser_info, yyvsp[-1].node, yyvsp[0].node); }
    break;

  case 78:
#line 219 "grammar.yy"
    { yyval.node = sxp_new_new (sxp_parser_info, yyvsp[0].id); }
    break;

  case 79:
#line 220 "grammar.yy"
    { yyval.node = sxp_new_smet (sxp_parser_info, yyvsp[-3].id, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 80:
#line 221 "grammar.yy"
    { yyval.node = sxp_new_meth (sxp_parser_info, yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 81:
#line 222 "grammar.yy"
    { yyval.node = sxp_new_node (sxp_parser_info, SXP_SET_MEMBER, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 82:
#line 223 "grammar.yy"
    { yyval.node = sxp_new_node (sxp_parser_info, SXP_GET_MEMBER, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 83:
#line 225 "grammar.yy"
    { yyval.node = sxp_new_indx (sxp_parser_info, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 84:
#line 226 "grammar.yy"
    { yyval.node = sxp_new_arry (sxp_parser_info, yyvsp[-1].node); }
    break;

  case 85:
#line 227 "grammar.yy"
    { yyval.node = sxp_new_assc (sxp_parser_info, yyvsp[-1].node); }
    break;

  case 86:
#line 229 "grammar.yy"
    { yyval.node = sxp_new_data (sxp_parser_info, yyvsp[0].value); }
    break;

  case 87:
#line 231 "grammar.yy"
    { yyval.node = sxp_new_look (sxp_parser_info, yyvsp[0].id); }
    break;

  case 88:
#line 233 "grammar.yy"
    { yyval.node = sxp_new_data (sxp_parser_info, NULL); }
    break;

  case 89:
#line 237 "grammar.yy"
    { yyval.value = yyvsp[0].value;  }
    break;

  case 90:
#line 238 "grammar.yy"
    { yyval.value = yyvsp[0].value; }
    break;

  case 91:
#line 239 "grammar.yy"
    { yyval.value = NULL; }
    break;

  case 92:
#line 242 "grammar.yy"
    { yyval.id = yyvsp[0].id; }
    break;

  case 93:
#line 245 "grammar.yy"
    { yyval.node = sxp_new_name (sxp_parser_info, yyvsp[0].id); }
    break;

  case 94:
#line 247 "grammar.yy"
    { yyval.id = yyvsp[0].id; }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1819 "grammar.cc"

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
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
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
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



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
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
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

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
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


#line 250 "grammar.yy"


int
yyerror (const char *str) {
	sxp_error (sxp_parser_info, str);
	return 1;
}

extern "C"
int
yywrap (void) {
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
Scriptix::System::LoadFile(const char *file) {
	int ret;

	if (file == NULL) {
		yyin = stdin;
	} else {
		yyin = fopen (file, "r");
		if (yyin == NULL) {
			std::cerr << "Could not open '" << file << "'" << std::endl;
			return 1;
		}
	}

	sxp_parser_info = sxp_new_info (this);
	if (sxp_parser_info == NULL) {
		if (file != NULL)
			fclose (yyin);
		std::cerr << "Failed to create compiler context" << std::endl;
		return 1;
	}
	if (file != NULL)
		sxp_parser_info->file = String::Create(this, file);

	sxp_parser_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = -1;

	if (file != NULL) {
		fclose (yyin);
	}

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	return ret;
}

int
Scriptix::System::LoadString(const char *buf) {
	int ret;

	if (buf == NULL) {
		return 1;
	}

	sxp_parser_info = sxp_new_info (this);
	if (sxp_parser_info == NULL) {
		std::cerr << "Failed to create compiler context" << std::endl;
		return 1;
	}

	yyin = NULL;
	sxp_parser_inbuf = buf;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = -1;

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	return ret;
}

