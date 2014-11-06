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
     TFOREACH = 272,
     TADDASSIGN = 273,
     TSUBASSIGN = 274,
     TINCREMENT = 275,
     TDECREMENT = 276,
     TNEW = 277,
     TUNTIL = 278,
     TNIL = 279,
     TRESCUE = 280,
     TIN = 281,
     TFOR = 282,
     TCONTINUE = 283,
     TYIELD = 284,
     TPUBLIC = 285,
     TRETURN = 286,
     TBREAK = 287,
     TEQUALS = 288,
     TCAST = 289,
     TLENGTH = 290,
     TRANGE = 291,
     CUNARY = 292,
     TSTATMETHOD = 293
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
#define TFOREACH 272
#define TADDASSIGN 273
#define TSUBASSIGN 274
#define TINCREMENT 275
#define TDECREMENT 276
#define TNEW 277
#define TUNTIL 278
#define TNIL 279
#define TRESCUE 280
#define TIN 281
#define TFOR 282
#define TCONTINUE 283
#define TYIELD 284
#define TPUBLIC 285
#define TRETURN 286
#define TBREAK 287
#define TEQUALS 288
#define TCAST 289
#define TLENGTH 290
#define TRANGE 291
#define CUNARY 292
#define TSTATMETHOD 293




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

	Scriptix::ParserState* parser = NULL;

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
#line 57 "grammar.yy"
typedef union YYSTYPE {
	ParserNode* node;
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
#define YYLAST   798

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  17
/* YYNRULES -- Number of rules. */
#define YYNRULES  84
/* YYNRULES -- Number of states. */
#define YYNSTATES  192

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
       2,     2,     2,    44,     2,     2,     2,     2,    56,     2,
      48,    51,    39,    37,    55,    38,    46,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    54,
      35,    33,    34,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    57,    49,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    36,    41,
      42,    43,    45,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    21,    30,    31,
      41,    46,    47,    49,    51,    54,    57,    61,    64,    67,
      70,    73,    79,    87,    93,    99,   107,   115,   118,   128,
     136,   140,   141,   143,   145,   149,   150,   152,   157,   160,
     162,   166,   170,   173,   177,   181,   185,   189,   193,   197,
     200,   203,   207,   211,   215,   219,   223,   227,   231,   235,
     239,   246,   250,   254,   257,   260,   263,   266,   271,   276,
     279,   282,   287,   292,   298,   302,   307,   311,   313,   315,
     317,   319,   321,   323,   325
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      60,     0,    -1,    -1,    60,    61,    -1,    60,    63,    -1,
      60,     1,    -1,    74,    48,    69,    51,    52,    64,    53,
      -1,    30,    74,    48,    69,    51,    52,    64,    53,    -1,
      -1,    74,    62,    74,    48,    69,    51,    52,    64,    53,
      -1,    74,    33,    73,    54,    -1,    -1,    65,    -1,    66,
      -1,    65,    66,    -1,    67,    54,    -1,    31,    72,    54,
      -1,    31,    54,    -1,    32,    54,    -1,    28,    54,    -1,
      29,    54,    -1,     8,    48,    72,    51,    66,    -1,     8,
      48,    72,    51,    66,     9,    66,    -1,    10,    48,    72,
      51,    66,    -1,    23,    48,    72,    51,    66,    -1,    11,
      66,    10,    48,    72,    51,    54,    -1,    11,    66,    23,
      48,    72,    51,    54,    -1,    11,    66,    -1,    27,    48,
      67,    54,    72,    54,    67,    51,    66,    -1,    17,    48,
      74,    26,    72,    51,    66,    -1,    52,    64,    53,    -1,
      -1,    72,    -1,    72,    -1,    68,    55,    72,    -1,    -1,
      70,    -1,    70,    55,    56,    74,    -1,    56,    74,    -1,
      74,    -1,    70,    55,    74,    -1,    48,    68,    51,    -1,
      48,    51,    -1,    72,    37,    72,    -1,    72,    38,    72,
      -1,    72,    39,    72,    -1,    72,    40,    72,    -1,    48,
      72,    51,    -1,    72,    26,    72,    -1,    38,    72,    -1,
      44,    72,    -1,    72,    12,    72,    -1,    72,    13,    72,
      -1,    72,    34,    72,    -1,    72,    35,    72,    -1,    72,
      16,    72,    -1,    72,    14,    72,    -1,    72,    15,    72,
      -1,    72,    36,    72,    -1,    74,    33,    72,    -1,    72,
      47,    72,    57,    33,    72,    -1,    74,    18,    72,    -1,
      74,    19,    72,    -1,    74,    20,    -1,    20,    74,    -1,
      74,    21,    -1,    21,    74,    -1,    48,    75,    51,    72,
      -1,    75,    48,    72,    51,    -1,    72,    71,    -1,    22,
      75,    -1,    72,    46,    74,    71,    -1,    75,    46,    74,
      71,    -1,    72,    58,    74,    33,    72,    -1,    72,    58,
      74,    -1,    72,    47,    72,    57,    -1,    47,    68,    57,
      -1,    73,    -1,    74,    -1,     1,    -1,     3,    -1,     4,
      -1,    24,    -1,     5,    -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned char yyrline[] =
{
       0,    95,    95,    96,    97,    98,   101,   102,   103,   103,
     112,   115,   116,   119,   120,   123,   124,   125,   126,   127,
     128,   130,   131,   132,   133,   134,   135,   136,   138,   139,
     141,   144,   145,   148,   149,   152,   153,   154,   155,   158,
     159,   162,   163,   166,   167,   168,   169,   170,   172,   174,
     181,   182,   183,   185,   186,   187,   188,   189,   190,   192,
     193,   195,   196,   197,   198,   199,   200,   202,   203,   205,
     207,   208,   209,   210,   211,   213,   214,   216,   218,   220,
     224,   225,   226,   229,   232
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IDENTIFIER", "TYPE", 
  "TAG", "IF", "ELSE", "WHILE", "DO", "AND", "OR", "TGTE", "TLTE", "TNE", 
  "TFOREACH", "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", 
  "TNEW", "TUNTIL", "TNIL", "TRESCUE", "TIN", "TFOR", "TCONTINUE", 
  "TYIELD", "TPUBLIC", "TRETURN", "TBREAK", "'='", "'>'", "'<'", 
  "TEQUALS", "'+'", "'-'", "'*'", "'/'", "TCAST", "TLENGTH", "TRANGE", 
  "'!'", "CUNARY", "'.'", "'['", "'('", "'^'", "TSTATMETHOD", "')'", 
  "'{'", "'}'", "';'", "','", "'&'", "']'", "':'", "$accept", "program", 
  "function", "@1", "global", "block", "stmts", "stmt", "node", "args", 
  "arg_names", "arg_names_list", "func_args", "expr", "data", "name", 
  "type", 0
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
     285,   286,   287,    61,    62,    60,   288,    43,    45,    42,
      47,   289,   290,   291,    33,   292,    46,    91,    40,    94,
     293,    41,   123,   125,    59,    44,    38,    93,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    59,    60,    60,    60,    60,    61,    61,    62,    61,
      63,    64,    64,    65,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    68,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      73,    73,    73,    74,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     2,     2,     7,     8,     0,     9,
       4,     0,     1,     1,     2,     2,     3,     2,     2,     2,
       2,     5,     7,     5,     5,     7,     7,     2,     9,     7,
       3,     0,     1,     1,     3,     0,     1,     4,     2,     1,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       6,     3,     3,     2,     2,     2,     2,     4,     4,     2,
       2,     4,     4,     5,     3,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,     5,    83,     0,     3,     4,     8,     0,
       0,    35,     0,    35,    80,    81,    82,     0,     0,     0,
      36,    39,     0,     0,    10,    38,     0,     0,    35,     0,
       0,     0,    40,     0,     0,    79,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,     0,    32,
      77,    78,     0,    37,     0,     0,     0,     0,    27,     0,
      64,    66,    70,     0,     0,    19,    20,    17,     0,    18,
      49,    50,     0,    33,     0,     0,     0,     6,    14,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,     0,
      63,    65,     0,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     0,     0,    16,     0,    76,    47,     0,    30,
      51,    52,    56,    57,    55,    48,    53,    54,    58,    43,
      44,    45,    46,     0,     0,    42,     0,    74,    61,    62,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    67,    71,    75,    41,     0,    72,    68,     9,
      21,    23,     0,     0,     0,    24,     0,     0,    73,     0,
       0,     0,     0,     0,    60,    22,    25,    26,    29,     0,
       0,    28
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     6,    12,     7,    55,    56,    57,    58,    82,
      19,    20,   107,    59,    60,    61,    62
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const short yypact[] =
{
    -119,    10,  -119,  -119,  -119,     2,  -119,  -119,   -21,   -10,
      32,     4,     2,     4,  -119,  -119,  -119,   -38,     2,   -12,
      25,  -119,    36,    43,  -119,  -119,    44,     8,     4,    46,
     152,     2,  -119,    50,   152,  -119,  -119,    47,    49,   260,
      60,     2,     2,   106,    66,    70,    72,    74,   296,    75,
     390,   390,   390,   390,   152,    71,   206,  -119,    77,   724,
    -119,    54,    20,  -119,    80,    81,   390,   390,    11,     2,
    -119,  -119,  -119,   390,   325,  -119,  -119,  -119,   405,  -119,
      45,    45,    33,   724,   434,    31,    82,  -119,  -119,  -119,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   390,   390,     2,   390,   101,     2,  -119,   390,   390,
    -119,  -119,   390,     2,   390,   152,  -119,   463,   492,    85,
      88,   111,   521,    84,  -119,   390,  -119,  -119,   390,  -119,
     740,   740,   209,   209,   155,   209,   209,   209,   155,   -16,
     -16,    45,    45,    93,   550,  -119,   -14,   109,   724,   724,
     724,    93,   579,    91,   260,   260,   390,   390,   390,   260,
     390,   724,    45,  -119,   113,  -119,   390,  -119,  -119,  -119,
     138,  -119,   608,   637,   666,  -119,   695,   390,   724,   260,
      96,   100,   260,   354,   724,  -119,  -119,  -119,  -119,   108,
     260,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -119,  -119,  -119,  -119,  -119,   -32,  -119,   -39,   -66,    61,
       1,  -119,  -118,   -47,   157,    58,   -25
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -32
static const short yytable[] =
{
      68,    78,    65,    80,    81,    83,    84,     4,   123,     4,
       2,     3,    10,     4,    23,     4,    24,    88,    72,   117,
     118,   -32,    86,   101,   102,   163,   122,    11,    85,    33,
     103,   104,   105,   167,   -32,    14,    15,   165,    13,    26,
       5,   125,   106,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,    16,   144,    83,     8,
      18,   148,   149,     9,    31,   150,   113,   152,   114,    21,
      22,    21,   108,   109,   110,   111,    25,   113,   161,   114,
      27,   162,   128,   153,    28,    32,    21,   112,   125,    63,
     126,   103,   104,   105,    29,    66,    30,    67,    34,    70,
      71,    64,    35,   106,    14,    15,     4,    36,    69,   172,
     173,   174,    36,   176,    73,   170,   171,   189,    74,   178,
     175,    41,    42,    43,    87,    16,    75,   121,    76,    79,
     184,    89,   115,   156,   116,   129,   157,   158,   160,    50,
     185,   105,   166,   188,   169,    51,   177,   179,    52,    53,
     186,   191,   145,    35,   187,    14,    15,     4,    36,   190,
      37,   143,    38,    39,   147,     0,   146,    17,     0,    40,
       0,   151,    41,    42,    43,    44,    16,     0,     0,    45,
      46,    47,     0,    48,    49,     0,     0,     0,     0,     0,
      50,     0,    99,   100,   101,   102,    51,     0,     0,    52,
      53,   103,   104,   105,    54,   -11,   -31,    35,     0,    14,
      15,     4,    36,   106,    37,     0,    38,    39,     0,     0,
       0,     0,     0,    40,     0,    94,    41,    42,    43,    44,
      16,     0,     0,    45,    46,    47,     0,    48,    49,     0,
       0,     0,     0,     0,    50,    98,    99,   100,   101,   102,
      51,     0,     0,    52,    53,   103,   104,   105,    54,   -12,
     -31,    35,     0,    14,    15,     4,    36,   106,    37,     0,
      38,    39,     0,     0,     0,     0,     0,    40,     0,     0,
      41,    42,    43,    44,    16,     0,     0,    45,    46,    47,
       0,    48,    49,     0,     0,     0,     0,    35,    50,    14,
      15,     4,    36,     0,    51,     0,     0,    52,    53,     0,
       0,     0,    54,     0,   -31,     0,    41,    42,    43,     0,
      16,     0,     0,     0,     0,     0,    35,     0,    14,    15,
       4,    36,     0,     0,    50,     0,     0,     0,     0,     0,
      51,     0,     0,    52,    53,    41,    42,    43,     0,    16,
      77,     0,     0,     0,     0,    35,     0,    14,    15,     4,
      36,     0,     0,    50,     0,     0,     0,     0,     0,    51,
       0,     0,    52,    53,    41,    42,    43,     0,    16,   -31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    50,    14,    15,     4,    36,     0,    51,     0,
       0,    52,    53,     0,     0,   -31,     0,     0,     0,     0,
      41,    42,    43,     0,    16,     0,     0,    90,    91,    92,
      93,    94,     0,     0,     0,     0,     0,     0,    50,     0,
       0,    95,     0,     0,    51,     0,     0,    52,    53,    96,
      97,    98,    99,   100,   101,   102,    90,    91,    92,    93,
      94,   103,   104,   105,     0,     0,     0,     0,     0,   124,
      95,     0,     0,   106,     0,     0,     0,     0,    96,    97,
      98,    99,   100,   101,   102,    90,    91,    92,    93,    94,
     103,   104,   105,     0,     0,   127,     0,     0,     0,    95,
       0,     0,   106,     0,     0,     0,     0,    96,    97,    98,
      99,   100,   101,   102,    90,    91,    92,    93,    94,   103,
     104,   105,     0,     0,   154,     0,     0,     0,    95,     0,
       0,   106,     0,     0,     0,     0,    96,    97,    98,    99,
     100,   101,   102,    90,    91,    92,    93,    94,   103,   104,
     105,     0,     0,   155,     0,     0,     0,    95,     0,     0,
     106,     0,     0,     0,     0,    96,    97,    98,    99,   100,
     101,   102,    90,    91,    92,    93,    94,   103,   104,   105,
       0,     0,   159,     0,     0,     0,    95,     0,     0,   106,
       0,     0,     0,     0,    96,    97,    98,    99,   100,   101,
     102,    90,    91,    92,    93,    94,   103,   104,   105,     0,
       0,     0,     0,     0,     0,    95,     0,   164,   106,     0,
       0,     0,     0,    96,    97,    98,    99,   100,   101,   102,
      90,    91,    92,    93,    94,   103,   104,   105,     0,     0,
     168,     0,     0,     0,    95,     0,     0,   106,     0,     0,
       0,     0,    96,    97,    98,    99,   100,   101,   102,    90,
      91,    92,    93,    94,   103,   104,   105,     0,     0,   180,
       0,     0,     0,    95,     0,     0,   106,     0,     0,     0,
       0,    96,    97,    98,    99,   100,   101,   102,    90,    91,
      92,    93,    94,   103,   104,   105,     0,     0,   181,     0,
       0,     0,    95,     0,     0,   106,     0,     0,     0,     0,
      96,    97,    98,    99,   100,   101,   102,    90,    91,    92,
      93,    94,   103,   104,   105,     0,     0,   182,     0,     0,
       0,    95,     0,     0,   106,     0,     0,     0,     0,    96,
      97,    98,    99,   100,   101,   102,    90,    91,    92,    93,
      94,   103,   104,   105,     0,     0,     0,     0,     0,   183,
      95,     0,     0,   106,    92,    93,    94,     0,    96,    97,
      98,    99,   100,   101,   102,     0,    95,     0,     0,     0,
     103,   104,   105,     0,    96,    97,    98,    99,   100,   101,
     102,     0,   106,     0,     0,     0,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   106
};

static const short yycheck[] =
{
      39,    48,    34,    50,    51,    52,    53,     5,    74,     5,
       0,     1,    33,     5,    13,     5,    54,    56,    43,    66,
      67,    10,    54,    39,    40,   143,    73,    48,    53,    28,
      46,    47,    48,   151,    23,     3,     4,    51,    48,    51,
      30,    55,    58,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    24,   104,   105,     1,
      56,   108,   109,     5,    56,   112,    46,   114,    48,    11,
      12,    13,    18,    19,    20,    21,    18,    46,   125,    48,
      55,   128,    51,   115,    48,    27,    28,    33,    55,    31,
      57,    46,    47,    48,    51,    48,    52,    48,    52,    41,
      42,    51,     1,    58,     3,     4,     5,     6,    48,   156,
     157,   158,     6,   160,    48,   154,   155,   183,    48,   166,
     159,    20,    21,    22,    53,    24,    54,    69,    54,    54,
     177,    54,    52,    48,    53,    53,    48,    26,    54,    38,
     179,    48,    33,   182,    53,    44,    33,     9,    47,    48,
      54,   190,    51,     1,    54,     3,     4,     5,     6,    51,
       8,   103,    10,    11,   106,    -1,   105,    10,    -1,    17,
      -1,   113,    20,    21,    22,    23,    24,    -1,    -1,    27,
      28,    29,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    37,    38,    39,    40,    44,    -1,    -1,    47,
      48,    46,    47,    48,    52,    53,    54,     1,    -1,     3,
       4,     5,     6,    58,     8,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    16,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,    29,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    38,    36,    37,    38,    39,    40,
      44,    -1,    -1,    47,    48,    46,    47,    48,    52,    53,
      54,     1,    -1,     3,     4,     5,     6,    58,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      20,    21,    22,    23,    24,    -1,    -1,    27,    28,    29,
      -1,    31,    32,    -1,    -1,    -1,    -1,     1,    38,     3,
       4,     5,     6,    -1,    44,    -1,    -1,    47,    48,    -1,
      -1,    -1,    52,    -1,    54,    -1,    20,    21,    22,    -1,
      24,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,
       5,     6,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    47,    48,    20,    21,    22,    -1,    24,
      54,    -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,
       6,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    47,    48,    20,    21,    22,    -1,    24,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    38,     3,     4,     5,     6,    -1,    44,    -1,
      -1,    47,    48,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      20,    21,    22,    -1,    24,    -1,    -1,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    26,    -1,    -1,    44,    -1,    -1,    47,    48,    34,
      35,    36,    37,    38,    39,    40,    12,    13,    14,    15,
      16,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      26,    -1,    -1,    58,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    12,    13,    14,    15,    16,
      46,    47,    48,    -1,    -1,    51,    -1,    -1,    -1,    26,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    12,    13,    14,    15,    16,    46,
      47,    48,    -1,    -1,    51,    -1,    -1,    -1,    26,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    12,    13,    14,    15,    16,    46,    47,
      48,    -1,    -1,    51,    -1,    -1,    -1,    26,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    12,    13,    14,    15,    16,    46,    47,    48,
      -1,    -1,    51,    -1,    -1,    -1,    26,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    12,    13,    14,    15,    16,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    57,    58,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      12,    13,    14,    15,    16,    46,    47,    48,    -1,    -1,
      51,    -1,    -1,    -1,    26,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    39,    40,    12,
      13,    14,    15,    16,    46,    47,    48,    -1,    -1,    51,
      -1,    -1,    -1,    26,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    12,    13,
      14,    15,    16,    46,    47,    48,    -1,    -1,    51,    -1,
      -1,    -1,    26,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    12,    13,    14,
      15,    16,    46,    47,    48,    -1,    -1,    51,    -1,    -1,
      -1,    26,    -1,    -1,    58,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    12,    13,    14,    15,
      16,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      26,    -1,    -1,    58,    14,    15,    16,    -1,    34,    35,
      36,    37,    38,    39,    40,    -1,    26,    -1,    -1,    -1,
      46,    47,    48,    -1,    34,    35,    36,    37,    38,    39,
      40,    -1,    58,    -1,    -1,    -1,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    60,     0,     1,     5,    30,    61,    63,    74,    74,
      33,    48,    62,    48,     3,     4,    24,    73,    56,    69,
      70,    74,    74,    69,    54,    74,    51,    55,    48,    51,
      52,    56,    74,    69,    52,     1,     6,     8,    10,    11,
      17,    20,    21,    22,    23,    27,    28,    29,    31,    32,
      38,    44,    47,    48,    52,    64,    65,    66,    67,    72,
      73,    74,    75,    74,    51,    64,    48,    48,    66,    48,
      74,    74,    75,    48,    48,    54,    54,    54,    72,    54,
      72,    72,    68,    72,    72,    75,    64,    53,    66,    54,
      12,    13,    14,    15,    16,    26,    34,    35,    36,    37,
      38,    39,    40,    46,    47,    48,    58,    71,    18,    19,
      20,    21,    33,    46,    48,    52,    53,    72,    72,    10,
      23,    74,    72,    67,    54,    55,    57,    51,    51,    53,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    74,    72,    51,    68,    74,    72,    72,
      72,    74,    72,    64,    51,    51,    48,    48,    26,    51,
      54,    72,    72,    71,    57,    51,    33,    71,    51,    53,
      66,    66,    72,    72,    72,    66,    72,    33,    72,     9,
      51,    51,    51,    54,    72,    66,    54,    54,    66,    67,
      51,    66
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
#line 101 "grammar.yy"
    { parser->AddFunc(yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 0); }
    break;

  case 7:
#line 102 "grammar.yy"
    { parser->AddFunc(yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 1); }
    break;

  case 8:
#line 103 "grammar.yy"
    { 
		if (!parser->GetSystem()->ValidFunctionTag(IDToName (yyvsp[0].id))) {
			yyerror ("Unregistered tag");
			YYERROR;
		}
		yyval.id = yyvsp[0].id;
	}
    break;

  case 9:
#line 109 "grammar.yy"
    { parser->AddFunc(yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, IDToName(yyvsp[-7].id), 1); }
    break;

  case 10:
#line 112 "grammar.yy"
    { parser->SetGlobal(yyvsp[-3].id, yyvsp[-1].value); }
    break;

  case 11:
#line 115 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 12:
#line 116 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 13:
#line 119 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 14:
#line 120 "grammar.yy"
    { yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 15:
#line 123 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 16:
#line 124 "grammar.yy"
    { yyval.node = sxp_new_return (parser, yyvsp[-1].node); }
    break;

  case 17:
#line 125 "grammar.yy"
    { yyval.node = sxp_new_return (parser, NULL); }
    break;

  case 18:
#line 126 "grammar.yy"
    { yyval.node = sxp_new_break (parser); }
    break;

  case 19:
#line 127 "grammar.yy"
    { yyval.node = sxp_new_continue (parser); }
    break;

  case 20:
#line 128 "grammar.yy"
    { yyval.node = sxp_new_yield (parser); }
    break;

  case 21:
#line 130 "grammar.yy"
    { yyval.node = sxp_new_if (parser, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;

  case 22:
#line 131 "grammar.yy"
    { yyval.node = sxp_new_if (parser, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 23:
#line 132 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_WHILE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 24:
#line 133 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_UNTIL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 25:
#line 134 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_DOWHILE, yyvsp[-2].node, yyvsp[-5].node); }
    break;

  case 26:
#line 135 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_DOUNTIL, yyvsp[-2].node, yyvsp[-5].node); }
    break;

  case 27:
#line 136 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_FOREVER, NULL, yyvsp[0].node); }
    break;

  case 28:
#line 138 "grammar.yy"
    { yyval.node = sxp_new_for (parser, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 29:
#line 139 "grammar.yy"
    { yyval.node = sxp_new_foreach (parser, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 30:
#line 141 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 31:
#line 144 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 32:
#line 145 "grammar.yy"
    { yyval.node = sxp_new_statement (parser, yyvsp[0].node); }
    break;

  case 33:
#line 148 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 34:
#line 149 "grammar.yy"
    { yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;

  case 35:
#line 152 "grammar.yy"
    { yyval.args.args = NULL; yyval.args.varg = 0; }
    break;

  case 36:
#line 153 "grammar.yy"
    { yyval.args.args = yyvsp[0].name_list; yyval.args.varg = 0; }
    break;

  case 37:
#line 154 "grammar.yy"
    { yyval.args.args = yyvsp[-3].name_list; yyval.args.varg = yyvsp[0].id; }
    break;

  case 38:
#line 155 "grammar.yy"
    { yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;

  case 39:
#line 158 "grammar.yy"
    { yyval.name_list = sx_new_namelist (parser->GetSystem(), 1, yyvsp[0].id); }
    break;

  case 40:
#line 159 "grammar.yy"
    { yyval.name_list = sx_namelist_append (parser->GetSystem(), yyvsp[-2].name_list, yyvsp[0].id); }
    break;

  case 41:
#line 162 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 42:
#line 163 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 43:
#line 166 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 44:
#line 167 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 45:
#line 168 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 46:
#line 169 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 47:
#line 170 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 48:
#line 172 "grammar.yy"
    { yyval.node = sxp_new_in (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 49:
#line 174 "grammar.yy"
    {
			if (yyvsp[0].node->type == SXP_DATA && Value::IsA<Number>(yyvsp[0].node->parts.value))
				yyval.node = sxp_new_data(parser,Number::Create(-Number::ToInt(yyvsp[0].node->parts.value)));
			else
				yyval.node = sxp_new_negate (parser, yyvsp[0].node); 
		}
    break;

  case 50:
#line 181 "grammar.yy"
    { yyval.node = sxp_new_not (parser, yyvsp[0].node); }
    break;

  case 51:
#line 182 "grammar.yy"
    { yyval.node = sxp_new_and (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 52:
#line 183 "grammar.yy"
    { yyval.node = sxp_new_or (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 53:
#line 185 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 54:
#line 186 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 55:
#line 187 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 56:
#line 188 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 57:
#line 189 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 58:
#line 190 "grammar.yy"
    { yyval.node = sxp_new_math (parser, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 59:
#line 192 "grammar.yy"
    { yyval.node = sxp_new_assign (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 60:
#line 193 "grammar.yy"
    { yyval.node = sxp_new_setindex (parser, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;

  case 61:
#line 195 "grammar.yy"
    { yyval.node = sxp_new_preinc (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 62:
#line 196 "grammar.yy"
    { yyval.node = sxp_new_preinc (parser, yyvsp[-2].id, sxp_new_negate (parser, yyvsp[0].node)); }
    break;

  case 63:
#line 197 "grammar.yy"
    { yyval.node = sxp_new_postinc (parser, yyvsp[-1].id, sxp_new_data (parser, Number::Create (1))); }
    break;

  case 64:
#line 198 "grammar.yy"
    { yyval.node = sxp_new_preinc (parser, yyvsp[0].id, sxp_new_data (parser, Number::Create (1))); }
    break;

  case 65:
#line 199 "grammar.yy"
    { yyval.node = sxp_new_postinc (parser, yyvsp[-1].id, sxp_new_data (parser, Number::Create (-1))); }
    break;

  case 66:
#line 200 "grammar.yy"
    { yyval.node = sxp_new_preinc (parser, yyvsp[0].id, sxp_new_data (parser, Number::Create (-1))); }
    break;

  case 67:
#line 202 "grammar.yy"
    { yyval.node = sxp_new_cast (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 68:
#line 203 "grammar.yy"
    { yyval.node = sxp_new_cast (parser, yyvsp[-3].id, yyvsp[-1].node); }
    break;

  case 69:
#line 205 "grammar.yy"
    { yyval.node = sxp_new_invoke (parser, yyvsp[-1].node, yyvsp[0].node); }
    break;

  case 70:
#line 207 "grammar.yy"
    { yyval.node = sxp_new_new (parser, yyvsp[0].id); }
    break;

  case 71:
#line 208 "grammar.yy"
    { yyval.node = sxp_new_method (parser, yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 72:
#line 209 "grammar.yy"
    { yyval.node = sxp_new_smethod (parser, yyvsp[-3].id, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 73:
#line 210 "grammar.yy"
    { yyval.node = sxp_new_set_member(parser, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 74:
#line 211 "grammar.yy"
    { yyval.node = sxp_new_get_member (parser, yyvsp[-2].node, yyvsp[0].id); }
    break;

  case 75:
#line 213 "grammar.yy"
    { yyval.node = sxp_new_getindex (parser, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 76:
#line 214 "grammar.yy"
    { yyval.node = sxp_new_array (parser, yyvsp[-1].node); }
    break;

  case 77:
#line 216 "grammar.yy"
    { yyval.node = sxp_new_data (parser, yyvsp[0].value); }
    break;

  case 78:
#line 218 "grammar.yy"
    { yyval.node = sxp_new_lookup (parser, yyvsp[0].id); }
    break;

  case 79:
#line 220 "grammar.yy"
    { yyval.node = sxp_new_data (parser, NULL); }
    break;

  case 80:
#line 224 "grammar.yy"
    { yyval.value = yyvsp[0].value;  }
    break;

  case 81:
#line 225 "grammar.yy"
    { yyval.value = yyvsp[0].value; }
    break;

  case 82:
#line 226 "grammar.yy"
    { yyval.value = NULL; }
    break;

  case 83:
#line 229 "grammar.yy"
    { yyval.id = yyvsp[0].id; }
    break;

  case 84:
#line 232 "grammar.yy"
    { yyval.id = yyvsp[0].id; }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1767 "grammar.cc"

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


#line 235 "grammar.yy"


int
yyerror (const char *str) {
	parser->Error(str);
	return 1;
}

extern "C"
int
yywrap (void) {
	return 1;
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

	parser = new ParserState(this);
	if (parser == NULL) {
		if (file != NULL)
			fclose (yyin);
		std::cerr << "Failed to create Compiler context" << std::endl;
		return 1;
	}
	if (file != NULL)
		parser->SetFile(file);

	sxp_parser_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = -1;

	if (file != NULL) {
		fclose (yyin);
	}

	if (!ret) {
		ret = parser->Compile();
	}

	delete parser;

	return ret;
}

int
Scriptix::System::LoadFile(FILE* file, const char* name) {
	int ret;

	yyin = file;

	parser = new ParserState(this);
	if (parser == NULL) {
		std::cerr << "Failed to create Compiler context" << std::endl;
		return 1;
	}
	if (file != NULL)
		parser->SetFile(name);

	sxp_parser_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = -1;

	if (!ret) {
		ret = parser->Compile();
	}

	delete parser;

	return ret;
}

int
Scriptix::System::LoadString(const char *buf) {
	int ret;

	if (buf == NULL) {
		return 1;
	}

	parser = new ParserState(this);
	if (parser == NULL) {
		std::cerr << "Failed to create Compiler context" << std::endl;
		return 1;
	}

	yyin = NULL;
	sxp_parser_inbuf = buf;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = -1;

	if (!ret) {
		ret = parser->Compile();
	}

	delete parser;

	return ret;
}

