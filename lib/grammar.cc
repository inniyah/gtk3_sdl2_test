/* A Bison parser, made by GNU Bison 1.875.  */

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
     TEXTEND = 273,
     TADDASSIGN = 274,
     TSUBASSIGN = 275,
     TINCREMENT = 276,
     TDECREMENT = 277,
     TNEW = 278,
     TSTATIC = 279,
     TUNTIL = 280,
     TNIL = 281,
     TRESCUE = 282,
     TIN = 283,
     TFOR = 284,
     TCONTINUE = 285,
     TYIELD = 286,
     TPUBLIC = 287,
     TMULASSIGN = 288,
     TDIVASSIGN = 289,
     TRETURN = 290,
     TBREAK = 291,
     TEQUALS = 292,
     TLENGTH = 293,
     CUNARY = 294,
     TCAST = 295
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
#define TEXTEND 273
#define TADDASSIGN 274
#define TSUBASSIGN 275
#define TINCREMENT 276
#define TDECREMENT 277
#define TNEW 278
#define TSTATIC 279
#define TUNTIL 280
#define TNIL 281
#define TRESCUE 282
#define TIN 283
#define TFOR 284
#define TCONTINUE 285
#define TYIELD 286
#define TPUBLIC 287
#define TMULASSIGN 288
#define TDIVASSIGN 289
#define TRETURN 290
#define TBREAK 291
#define TEQUALS 292
#define TLENGTH 293
#define CUNARY 294
#define TCAST 295




/* Copy the first part of user declarations.  */
#line 28 "grammar.yy"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <errno.h>
	#include <gc/gc.h>

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

	#define malloc GC_MALLOC_UNCOLLECTABLE
	#define free GC_FREE


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
#line 61 "grammar.yy"
typedef union YYSTYPE {
	ParserNode* node;
	Value* value;
	Type* type;
	NameID id;
	NameList* names;
	struct ParserArgList args;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 197 "grammar.cc"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 209 "grammar.cc"

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
#define YYLAST   1059

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  26
/* YYNRULES -- Number of rules. */
#define YYNRULES  108
/* YYNRULES -- Number of states. */
#define YYNSTATES  251

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,     2,     2,     2,    60,     2,
      54,    55,    44,    41,    59,    42,    50,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    58,
      39,    37,    38,     2,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    61,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,    57,     2,     2,     2,     2,
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
      35,    36,    40,    46,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    27,
      36,    37,    47,    52,    53,    60,    68,    77,    79,    82,
      83,    91,    92,   100,   101,   111,   112,   114,   116,   119,
     122,   126,   129,   132,   135,   138,   144,   152,   158,   164,
     172,   180,   183,   193,   201,   205,   207,   208,   210,   212,
     216,   217,   219,   224,   227,   229,   233,   237,   240,   242,
     247,   251,   254,   258,   262,   266,   270,   274,   278,   282,
     285,   288,   292,   296,   300,   304,   308,   312,   316,   320,
     324,   331,   337,   342,   346,   350,   354,   358,   361,   364,
     367,   370,   375,   380,   383,   388,   391,   395,   400,   404,
     409,   413,   416,   418,   420,   422,   424,   426,   428
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      63,     0,    -1,    -1,    63,    64,    -1,    63,    66,    -1,
      63,     1,    -1,    63,    67,    -1,    63,    72,    -1,    86,
      54,    80,    55,    56,    75,    57,    -1,    32,    86,    54,
      80,    55,    56,    75,    57,    -1,    -1,    86,    86,    65,
      54,    80,    55,    56,    75,    57,    -1,    86,    37,    85,
      58,    -1,    -1,    18,    87,    68,    56,    70,    57,    -1,
      86,    54,    80,    55,    56,    75,    57,    -1,    24,    86,
      54,    80,    55,    56,    75,    57,    -1,    69,    -1,    70,
      69,    -1,    -1,    23,    54,    80,    55,    56,    75,    57,
      -1,    -1,    23,    86,    73,    56,    71,    70,    57,    -1,
      -1,    23,    86,    51,    87,    74,    56,    71,    70,    57,
      -1,    -1,    76,    -1,    77,    -1,    76,    77,    -1,    78,
      58,    -1,    35,    84,    58,    -1,    35,    58,    -1,    36,
      58,    -1,    30,    58,    -1,    31,    58,    -1,     8,    54,
      84,    55,    77,    -1,     8,    54,    84,    55,    77,     9,
      77,    -1,    10,    54,    84,    55,    77,    -1,    25,    54,
      84,    55,    77,    -1,    11,    77,    10,    54,    84,    55,
      58,    -1,    11,    77,    25,    54,    84,    55,    58,    -1,
      11,    77,    -1,    29,    54,    78,    58,    84,    58,    78,
      55,    77,    -1,    17,    54,    86,    28,    84,    55,    77,
      -1,    56,    75,    57,    -1,     1,    -1,    -1,    84,    -1,
      84,    -1,    79,    59,    84,    -1,    -1,    81,    -1,    81,
      59,    60,    86,    -1,    60,    86,    -1,    86,    -1,    81,
      59,    86,    -1,    54,    79,    55,    -1,    54,    55,    -1,
      86,    -1,    84,    52,    84,    61,    -1,    84,    50,    86,
      -1,    50,    86,    -1,    84,    41,    84,    -1,    84,    42,
      84,    -1,    84,    44,    84,    -1,    84,    45,    84,    -1,
      84,    43,    84,    -1,    54,    84,    55,    -1,    84,    28,
      84,    -1,    42,    84,    -1,    47,    84,    -1,    84,    12,
      84,    -1,    84,    13,    84,    -1,    84,    38,    84,    -1,
      84,    39,    84,    -1,    84,    16,    84,    -1,    84,    14,
      84,    -1,    84,    15,    84,    -1,    84,    40,    84,    -1,
      86,    37,    84,    -1,    84,    52,    84,    61,    37,    84,
      -1,    84,    50,    86,    37,    84,    -1,    50,    86,    37,
      84,    -1,    84,    19,    84,    -1,    84,    20,    84,    -1,
      84,    33,    84,    -1,    84,    34,    84,    -1,    84,    21,
      -1,    21,    84,    -1,    84,    22,    -1,    22,    84,    -1,
      54,    87,    55,    84,    -1,    87,    54,    84,    55,    -1,
      86,    82,    -1,    54,    84,    55,    82,    -1,    23,    87,
      -1,    23,    87,    82,    -1,    84,    50,    86,    82,    -1,
      50,    86,    82,    -1,    87,    50,    86,    82,    -1,    52,
      79,    61,    -1,    52,    61,    -1,    85,    -1,    83,    -1,
       3,    -1,     4,    -1,    26,    -1,     5,    -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   103,   103,   104,   105,   106,   107,   108,   111,   112,
     113,   113,   123,   126,   126,   129,   130,   133,   134,   137,
     138,   141,   141,   142,   142,   145,   146,   149,   150,   153,
     154,   155,   156,   157,   158,   160,   161,   162,   163,   164,
     165,   166,   168,   169,   171,   173,   176,   177,   180,   181,
     184,   185,   186,   187,   190,   191,   194,   195,   198,   199,
     200,   201,   204,   205,   206,   207,   208,   209,   211,   213,
     220,   221,   222,   224,   225,   226,   227,   228,   229,   231,
     232,   233,   234,   236,   237,   238,   239,   240,   241,   242,
     243,   245,   246,   248,   249,   251,   252,   253,   254,   255,
     257,   258,   260,   262,   266,   267,   268,   271,   274
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IDENTIFIER", "TYPE", 
  "TAG", "IF", "ELSE", "WHILE", "DO", "AND", "OR", "TGTE", "TLTE", "TNE", 
  "TFOREACH", "TEXTEND", "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", 
  "TDECREMENT", "TNEW", "TSTATIC", "TUNTIL", "TNIL", "TRESCUE", "TIN", 
  "TFOR", "TCONTINUE", "TYIELD", "TPUBLIC", "TMULASSIGN", "TDIVASSIGN", 
  "TRETURN", "TBREAK", "'='", "'>'", "'<'", "TEQUALS", "'+'", "'-'", 
  "'@'", "'*'", "'/'", "TLENGTH", "'!'", "CUNARY", "TCAST", "'.'", "':'", 
  "'['", "'^'", "'('", "')'", "'{'", "'}'", "';'", "','", "'&'", "']'", 
  "$accept", "program", "function", "@1", "global", "extend", "@2", 
  "extend_method", "extend_methods", "construct_method", "new", "@3", 
  "@4", "block", "stmts", "stmt", "node", "args", "arg_names", 
  "arg_names_list", "func_args", "lval", "expr", "data", "name", "type", 0
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
     285,   286,   287,   288,   289,   290,   291,    61,    62,    60,
     292,    43,    45,    64,    42,    47,   293,    33,   294,   295,
      46,    58,    91,    94,    40,    41,   123,   125,    59,    44,
      38,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    62,    63,    63,    63,    63,    63,    63,    64,    64,
      65,    64,    66,    68,    67,    69,    69,    70,    70,    71,
      71,    73,    72,    74,    72,    75,    75,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    78,    78,    79,    79,
      80,    80,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    83,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    85,    85,    85,    86,    87
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     7,     8,
       0,     9,     4,     0,     6,     7,     8,     1,     2,     0,
       7,     0,     7,     0,     9,     0,     1,     1,     2,     2,
       3,     2,     2,     2,     2,     5,     7,     5,     5,     7,
       7,     2,     9,     7,     3,     1,     0,     1,     1,     3,
       0,     1,     4,     2,     1,     3,     3,     2,     1,     4,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       6,     5,     4,     3,     3,     3,     3,     2,     2,     2,
       2,     4,     4,     2,     4,     2,     3,     4,     3,     4,
       3,     2,     1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       2,     0,     1,     5,   107,     0,     0,     0,     3,     4,
       6,     7,     0,   108,    13,    21,     0,     0,    50,    10,
       0,     0,     0,    50,   104,   105,   106,     0,     0,     0,
      51,    54,     0,     0,    23,    19,     0,    12,    53,     0,
       0,    50,     0,    17,     0,     0,     0,     0,     0,     0,
       0,     0,    55,     0,     0,    14,    18,    50,    19,    50,
       0,     0,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,   103,    47,   102,    58,
       0,    52,     0,    50,     0,     0,     0,    22,     0,     0,
       0,    41,     0,    88,    90,    95,     0,    46,    33,    34,
      31,     0,    32,    69,    70,    61,   101,     0,    48,     0,
       0,     0,     8,    28,    29,     0,     0,     0,     0,     0,
       0,     0,    87,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     9,     0,     0,
       0,     0,     0,    96,     0,     0,    30,     0,    98,     0,
     100,    67,     0,    44,    71,    72,    76,    77,    75,    83,
      84,    68,    85,    86,    73,    74,    78,    62,    63,    66,
      64,    65,    60,     0,    79,    57,     0,     0,     0,     0,
       0,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,    82,    49,    94,    91,     0,    97,    59,    56,    99,
      92,    11,     0,     0,     0,    35,    37,     0,     0,     0,
      38,     0,    81,     0,     0,    15,    20,     0,     0,     0,
       0,    46,    80,    16,    36,    39,    40,    43,     0,     0,
      42
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     1,     8,    32,     9,    10,    20,    43,    44,    48,
      11,    22,    46,    82,    83,    84,    85,   117,    29,    30,
     149,    86,    87,    88,    89,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -107
static const short yypact[] =
{
    -107,   110,  -107,  -107,  -107,    18,    26,    26,  -107,  -107,
    -107,  -107,     1,  -107,  -107,   -17,    36,   126,    -3,  -107,
      16,    18,    43,    -3,  -107,  -107,  -107,    35,    26,    53,
      55,  -107,    66,    37,  -107,   108,    86,  -107,  -107,    81,
      -1,    -3,    26,  -107,    38,    95,   100,    97,    37,   105,
     264,    26,  -107,   107,   109,  -107,  -107,    -3,   108,    -3,
      39,   264,  -107,   112,   115,   380,   116,   455,   455,    18,
     120,   125,   122,   124,     6,   134,   455,   455,    26,   202,
     455,   264,   142,   322,  -107,   144,  -107,   975,  -107,   -24,
      51,  -107,   147,    -3,   145,    37,   154,  -107,   157,   455,
     455,    12,    26,   133,   133,   161,   455,   455,  -107,  -107,
    -107,   541,  -107,    -5,    -5,    -2,  -107,    77,   975,   623,
     103,   159,  -107,  -107,  -107,   455,   455,   455,   455,   455,
     455,   455,  -107,  -107,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,    26,   455,   455,   420,  -107,
      26,   455,   264,   156,   162,    49,   163,  -107,   667,   711,
     166,   167,   189,  -107,   755,   164,  -107,   455,  -107,   455,
    -107,   161,   455,  -107,  1007,  1007,    82,    82,   146,   975,
     975,    82,   975,   975,    82,    82,   146,   133,   133,   133,
      -5,    -5,    65,   498,   975,  -107,    62,   161,   799,   169,
     171,   264,  -107,   264,   380,   380,   455,   455,   455,   380,
     455,   975,   975,  -107,    -5,   455,  -107,   192,  -107,  -107,
    -107,  -107,   264,   173,   175,   224,  -107,   843,   887,   931,
    -107,   582,   975,   455,   177,  -107,  -107,   380,   178,   179,
     380,   455,   975,  -107,  -107,  -107,  -107,  -107,   180,   380,
    -107
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -107,  -107,  -107,  -107,  -107,  -107,  -107,   -39,     2,   181,
    -107,  -107,  -107,   -58,  -107,   -65,  -106,    90,    -8,  -107,
     -79,  -107,   -60,   223,   153,    20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const short yytable[] =
{
     101,   165,     4,    98,     4,    56,     4,   103,   104,    24,
      25,     4,    13,   147,   111,    36,   113,   114,   123,   118,
     119,    56,   -47,   121,    13,    14,   163,    67,    68,    69,
     148,     4,    26,    53,    21,   167,   168,   -47,    17,   158,
     159,    34,     4,     4,     4,   145,   164,   146,    76,    94,
      60,    96,   148,    77,     4,    18,    78,    28,    79,    51,
      80,    42,    42,    42,   110,   174,   175,   176,   177,   178,
     179,   180,    33,    42,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   153,   193,   194,   118,   105,
      23,   198,   213,    37,   199,    55,    97,   155,   129,    35,
     120,   150,   215,   132,   133,   151,   202,   211,    39,   212,
       2,     3,   214,   216,    40,     4,    56,   218,   219,   148,
      41,   169,   139,   140,   141,   142,   143,   144,     5,    24,
      25,    47,   145,     6,   146,   248,   169,    50,   170,   225,
     226,    49,     7,   223,   230,   224,   227,   228,   229,    57,
     231,    59,    26,   150,    12,   232,    58,   151,   172,    15,
      16,    61,    92,    93,   234,    19,    99,   132,   133,   100,
     102,    31,   244,   242,   106,   247,    31,   143,   144,   107,
     108,    38,   109,   145,   250,   146,    45,   140,   141,   142,
     143,   144,   112,    52,    31,    54,   145,    45,   146,   122,
     154,    45,   124,   152,    91,    24,    25,     4,    13,   156,
      31,   200,    31,    45,   157,   148,   173,   208,   201,   203,
     206,   207,   210,    67,    68,    69,   221,   222,    26,   233,
     235,   115,   236,   237,   243,   249,   245,   246,   196,    95,
      27,     0,     0,     0,    76,     0,    31,     0,    45,    77,
       0,     0,    78,     0,    79,   162,    80,     0,     0,     0,
       0,     0,     0,   116,     0,    62,     0,    24,    25,     4,
      13,     0,    63,     0,    64,    65,     0,     0,     0,     0,
       0,    66,     0,     0,     0,    67,    68,    69,     0,    70,
      26,     0,     0,    71,    72,    73,     0,     0,   192,    74,
      75,     0,     0,   197,     0,     0,    76,     0,    45,     0,
       0,    77,     0,     0,    78,     0,    79,     0,    80,     0,
      81,   -25,   -46,    62,     0,    24,    25,     4,    13,     0,
      63,     0,    64,    65,     0,     0,     0,     0,     0,    66,
       0,     0,     0,    67,    68,    69,     0,    70,    26,     0,
       0,    71,    72,    73,     0,     0,     0,    74,    75,     0,
       0,     0,     0,     0,    76,     0,     0,     0,     0,    77,
       0,     0,    78,     0,    79,     0,    80,     0,    81,   -26,
     -46,    62,     0,    24,    25,     4,    13,     0,    63,     0,
      64,    65,     0,     0,     0,     0,     0,    66,     0,     0,
       0,    67,    68,    69,     0,    70,    26,     0,     0,    71,
      72,    73,     0,     0,     0,    74,    75,     0,     0,     0,
       0,     0,    76,    24,    25,     4,    13,    77,     0,     0,
      78,     0,    79,     0,    80,     0,    81,     0,   -46,     0,
       0,    67,    68,    69,     0,     0,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,    25,
       4,    13,    76,     0,     0,     0,     0,    77,     0,     0,
      78,     0,    79,     0,    80,   195,    67,    68,    69,     0,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,     0,     0,
       0,     0,    77,     0,     0,    78,     0,    79,     0,    80,
     125,   126,   127,   128,   129,     0,     0,   130,   131,   132,
     133,     0,     0,     0,     0,     0,   134,     0,     0,     0,
       0,   135,   136,     0,     0,     0,   137,   138,   139,   140,
     141,   142,   143,   144,     0,     0,     0,     0,   145,     0,
     146,     0,     0,   125,   126,   127,   128,   129,     0,   217,
     130,   131,   132,   133,     0,     0,     0,     0,     0,   134,
       0,     0,     0,     0,   135,   136,     0,     0,     0,   137,
     138,   139,   140,   141,   142,   143,   144,     0,     0,     0,
       0,   145,     0,   146,   125,   126,   127,   128,   129,   166,
       0,   130,   131,   132,   133,     0,     0,     0,     0,     0,
     134,     0,     0,     0,     0,   135,   136,     0,     0,     0,
     137,   138,   139,   140,   141,   142,   143,   144,     0,     0,
       0,     0,   145,     0,   146,   125,   126,   127,   128,   129,
     241,     0,   130,   131,   132,   133,     0,     0,     0,     0,
       0,   134,     0,     0,     0,     0,   135,   136,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,     0,
       0,     0,     0,   145,     0,   146,     0,     0,   171,   125,
     126,   127,   128,   129,     0,     0,   130,   131,   132,   133,
       0,     0,     0,     0,     0,   134,     0,     0,     0,     0,
     135,   136,     0,     0,     0,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,     0,   145,     0,   146,
       0,     0,   204,   125,   126,   127,   128,   129,     0,     0,
     130,   131,   132,   133,     0,     0,     0,     0,     0,   134,
       0,     0,     0,     0,   135,   136,     0,     0,     0,   137,
     138,   139,   140,   141,   142,   143,   144,     0,     0,     0,
       0,   145,     0,   146,     0,     0,   205,   125,   126,   127,
     128,   129,     0,     0,   130,   131,   132,   133,     0,     0,
       0,     0,     0,   134,     0,     0,     0,     0,   135,   136,
       0,     0,     0,   137,   138,   139,   140,   141,   142,   143,
     144,     0,     0,     0,     0,   145,     0,   146,     0,     0,
     209,   125,   126,   127,   128,   129,     0,     0,   130,   131,
     132,   133,     0,     0,     0,     0,     0,   134,     0,     0,
       0,     0,   135,   136,     0,     0,     0,   137,   138,   139,
     140,   141,   142,   143,   144,     0,     0,     0,     0,   145,
       0,   146,     0,     0,   220,   125,   126,   127,   128,   129,
       0,     0,   130,   131,   132,   133,     0,     0,     0,     0,
       0,   134,     0,     0,     0,     0,   135,   136,     0,     0,
       0,   137,   138,   139,   140,   141,   142,   143,   144,     0,
       0,     0,     0,   145,     0,   146,     0,     0,   238,   125,
     126,   127,   128,   129,     0,     0,   130,   131,   132,   133,
       0,     0,     0,     0,     0,   134,     0,     0,     0,     0,
     135,   136,     0,     0,     0,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,     0,   145,     0,   146,
       0,     0,   239,   125,   126,   127,   128,   129,     0,     0,
     130,   131,   132,   133,     0,     0,     0,     0,     0,   134,
       0,     0,     0,     0,   135,   136,     0,     0,     0,   137,
     138,   139,   140,   141,   142,   143,   144,     0,     0,     0,
       0,   145,     0,   146,     0,     0,   240,   125,   126,   127,
     128,   129,     0,     0,   130,   131,   132,   133,     0,     0,
       0,     0,     0,   134,     0,     0,     0,     0,   135,   136,
       0,     0,     0,   137,   138,   139,   140,   141,   142,   143,
     144,   127,   128,   129,     0,   145,     0,   146,   132,   133,
       0,     0,     0,     0,     0,   134,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   137,   138,   139,   140,   141,
     142,   143,   144,     0,     0,     0,     0,   145,     0,   146
};

static const short yycheck[] =
{
      65,   107,     5,    61,     5,    44,     5,    67,    68,     3,
       4,     5,     6,    37,    74,    23,    76,    77,    83,    79,
      80,    60,    10,    81,     6,     5,   105,    21,    22,    23,
      54,     5,    26,    41,    51,    37,   115,    25,    37,    99,
     100,    21,     5,     5,     5,    50,   106,    52,    42,    57,
      48,    59,    54,    47,     5,    54,    50,    60,    52,    60,
      54,    24,    24,    24,    58,   125,   126,   127,   128,   129,
     130,   131,    56,    24,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,    93,   146,   147,   148,    69,
      54,   151,   171,    58,   152,    57,    57,    95,    16,    56,
      80,    50,    37,    21,    22,    54,    57,   167,    55,   169,
       0,     1,   172,   192,    59,     5,   155,    55,   197,    54,
      54,    59,    40,    41,    42,    43,    44,    45,    18,     3,
       4,    23,    50,    23,    52,   241,    59,    56,    61,   204,
     205,    55,    32,   201,   209,   203,   206,   207,   208,    54,
     210,    54,    26,    50,     1,   215,    56,    54,    55,     6,
       7,    56,    55,    54,   222,    12,    54,    21,    22,    54,
      54,    18,   237,   233,    54,   240,    23,    44,    45,    54,
      58,    28,    58,    50,   249,    52,    33,    41,    42,    43,
      44,    45,    58,    40,    41,    42,    50,    44,    52,    57,
      55,    48,    58,    56,    51,     3,     4,     5,     6,    55,
      57,    55,    59,    60,    57,    54,    57,    28,    56,    56,
      54,    54,    58,    21,    22,    23,    57,    56,    26,    37,
      57,    78,    57,     9,    57,    55,    58,    58,   148,    58,
      17,    -1,    -1,    -1,    42,    -1,    93,    -1,    95,    47,
      -1,    -1,    50,    -1,    52,   102,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,     1,    -1,     3,     4,     5,
       6,    -1,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    21,    22,    23,    -1,    25,
      26,    -1,    -1,    29,    30,    31,    -1,    -1,   145,    35,
      36,    -1,    -1,   150,    -1,    -1,    42,    -1,   155,    -1,
      -1,    47,    -1,    -1,    50,    -1,    52,    -1,    54,    -1,
      56,    57,    58,     1,    -1,     3,     4,     5,     6,    -1,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    21,    22,    23,    -1,    25,    26,    -1,
      -1,    29,    30,    31,    -1,    -1,    -1,    35,    36,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    50,    -1,    52,    -1,    54,    -1,    56,    57,
      58,     1,    -1,     3,     4,     5,     6,    -1,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      -1,    21,    22,    23,    -1,    25,    26,    -1,    -1,    29,
      30,    31,    -1,    -1,    -1,    35,    36,    -1,    -1,    -1,
      -1,    -1,    42,     3,     4,     5,     6,    47,    -1,    -1,
      50,    -1,    52,    -1,    54,    -1,    56,    -1,    58,    -1,
      -1,    21,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,    42,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      50,    -1,    52,    -1,    54,    55,    21,    22,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    50,    -1,    52,    -1,    54,
      12,    13,    14,    15,    16,    -1,    -1,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    -1,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    -1,    12,    13,    14,    15,    16,    -1,    61,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    -1,    52,    12,    13,    14,    15,    16,    58,
      -1,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    -1,
      -1,    -1,    50,    -1,    52,    12,    13,    14,    15,    16,
      58,    -1,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    50,    -1,    52,    -1,    -1,    55,    12,
      13,    14,    15,    16,    -1,    -1,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,    52,
      -1,    -1,    55,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    -1,    52,    -1,    -1,    55,    12,    13,    14,
      15,    16,    -1,    -1,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    50,    -1,    52,    -1,    -1,
      55,    12,    13,    14,    15,    16,    -1,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,
      -1,    52,    -1,    -1,    55,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    21,    22,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    50,    -1,    52,    -1,    -1,    55,    12,
      13,    14,    15,    16,    -1,    -1,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,    52,
      -1,    -1,    55,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    50,    -1,    52,    -1,    -1,    55,    12,    13,    14,
      15,    16,    -1,    -1,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    14,    15,    16,    -1,    50,    -1,    52,    21,    22,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    63,     0,     1,     5,    18,    23,    32,    64,    66,
      67,    72,    86,     6,    87,    86,    86,    37,    54,    86,
      68,    51,    73,    54,     3,     4,    26,    85,    60,    80,
      81,    86,    65,    56,    87,    56,    80,    58,    86,    55,
      59,    54,    24,    69,    70,    86,    74,    23,    71,    55,
      56,    60,    86,    80,    86,    57,    69,    54,    56,    54,
      70,    56,     1,     8,    10,    11,    17,    21,    22,    23,
      25,    29,    30,    31,    35,    36,    42,    47,    50,    52,
      54,    56,    75,    76,    77,    78,    83,    84,    85,    86,
      87,    86,    55,    54,    80,    71,    80,    57,    75,    54,
      54,    77,    54,    84,    84,    87,    54,    54,    58,    58,
      58,    84,    58,    84,    84,    86,    61,    79,    84,    84,
      87,    75,    57,    77,    58,    12,    13,    14,    15,    16,
      19,    20,    21,    22,    28,    33,    34,    38,    39,    40,
      41,    42,    43,    44,    45,    50,    52,    37,    54,    82,
      50,    54,    56,    80,    55,    70,    55,    57,    84,    84,
      10,    25,    86,    82,    84,    78,    58,    37,    82,    59,
      61,    55,    55,    57,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    86,    84,    84,    55,    79,    86,    84,    75,
      55,    56,    57,    56,    55,    55,    54,    54,    28,    55,
      58,    84,    84,    82,    84,    37,    82,    61,    55,    82,
      55,    57,    56,    75,    75,    77,    77,    84,    84,    84,
      77,    84,    84,    37,    75,    57,    57,     9,    55,    55,
      55,    58,    84,    57,    77,    58,    58,    77,    78,    55,
      77
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
        case 8:
#line 111 "grammar.yy"
    { parser->AddFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, 0, false); }
    break;

  case 9:
#line 112 "grammar.yy"
    { parser->AddFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, 0, true); }
    break;

  case 10:
#line 113 "grammar.yy"
    { 
		if (!parser->GetSystem()->ValidFunctionTag(yyvsp[-1].id)) {
			yyerror ("Error: Unrecognized function tag");
			YYERROR;
		}
		yyvsp[-1].id = yyvsp[-1].id;
		yyvsp[0].id = yyvsp[0].id;
	}
    break;

  case 11:
#line 120 "grammar.yy"
    { parser->AddFunc(yyvsp[-7].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, yyvsp[-8].id, false); }
    break;

  case 12:
#line 123 "grammar.yy"
    { parser->SetGlobal(yyvsp[-3].id, yyvsp[-1].value); }
    break;

  case 13:
#line 126 "grammar.yy"
    { if (!parser->AddExtend (yyvsp[0].type)) YYERROR; }
    break;

  case 15:
#line 129 "grammar.yy"
    { parser->AddExtendFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, false); }
    break;

  case 16:
#line 130 "grammar.yy"
    { parser->AddExtendFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, true); }
    break;

  case 20:
#line 138 "grammar.yy"
    { parser->AddExtendFunc(NameToID("new"), (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, false); }
    break;

  case 21:
#line 141 "grammar.yy"
    { if (!parser->AddType (yyvsp[0].id, parser->GetSystem()->GetStructType())) YYERROR; }
    break;

  case 23:
#line 142 "grammar.yy"
    { if (!parser->AddType (yyvsp[-2].id, yyvsp[0].type)) YYERROR; }
    break;

  case 25:
#line 145 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 26:
#line 146 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 27:
#line 149 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 28:
#line 150 "grammar.yy"
    { if (yyvsp[-1].node != NULL) { yyval.node = yyvsp[-1].node; yyval.node->Append(yyvsp[0].node); } else { yyval.node = yyvsp[0].node; } }
    break;

  case 29:
#line 153 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 30:
#line 154 "grammar.yy"
    { yyval.node = sxp_new_return (parser, yyvsp[-1].node); }
    break;

  case 31:
#line 155 "grammar.yy"
    { yyval.node = sxp_new_return (parser, NULL); }
    break;

  case 32:
#line 156 "grammar.yy"
    { yyval.node = sxp_new_break (parser); }
    break;

  case 33:
#line 157 "grammar.yy"
    { yyval.node = sxp_new_continue (parser); }
    break;

  case 34:
#line 158 "grammar.yy"
    { yyval.node = sxp_new_yield (parser); }
    break;

  case 35:
#line 160 "grammar.yy"
    { yyval.node = sxp_new_if (parser, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;

  case 36:
#line 161 "grammar.yy"
    { yyval.node = sxp_new_if (parser, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 37:
#line 162 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_WHILE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 38:
#line 163 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_UNTIL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 39:
#line 164 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_DOWHILE, yyvsp[-2].node, yyvsp[-5].node); }
    break;

  case 40:
#line 165 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_DOUNTIL, yyvsp[-2].node, yyvsp[-5].node); }
    break;

  case 41:
#line 166 "grammar.yy"
    { yyval.node = sxp_new_loop (parser, SXP_LOOP_FOREVER, NULL, yyvsp[0].node); }
    break;

  case 42:
#line 168 "grammar.yy"
    { yyval.node = sxp_new_for (parser, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 43:
#line 169 "grammar.yy"
    { yyval.node = sxp_new_foreach (parser, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 44:
#line 171 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 45:
#line 173 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 46:
#line 176 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 47:
#line 177 "grammar.yy"
    { yyval.node = sxp_new_statement (parser, yyvsp[0].node); }
    break;

  case 48:
#line 180 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 49:
#line 181 "grammar.yy"
    { yyval.node = yyvsp[-2].node; yyval.node->Append(yyvsp[0].node); }
    break;

  case 50:
#line 184 "grammar.yy"
    { yyval.args.args = NULL; yyval.args.varg = 0; }
    break;

  case 51:
#line 185 "grammar.yy"
    { yyval.args.args = yyvsp[0].names; yyval.args.varg = 0; }
    break;

  case 52:
#line 186 "grammar.yy"
    { yyval.args.args = yyvsp[-3].names; yyval.args.varg = yyvsp[0].id; }
    break;

  case 53:
#line 187 "grammar.yy"
    { yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;

  case 54:
#line 190 "grammar.yy"
    { yyval.names = new NameList(); yyval.names->push_back(yyvsp[0].id); }
    break;

  case 55:
#line 191 "grammar.yy"
    { yyval.names->push_back(yyvsp[0].id); }
    break;

  case 56:
#line 194 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 57:
#line 195 "grammar.yy"
    { yyval.node = NULL; }
    break;

  case 58:
#line 198 "grammar.yy"
    { yyval.node = sxp_new_lookup(parser, yyvsp[0].id); }
    break;

  case 59:
#line 199 "grammar.yy"
    { yyval.node = sxp_new_getindex(parser, yyvsp[-3].node, yyvsp[-1].node); }
    break;

  case 60:
#line 200 "grammar.yy"
    { yyval.node = sxp_new_get_member(parser, yyvsp[-2].node, yyvsp[0].id); }
    break;

  case 61:
#line 201 "grammar.yy"
    { yyval.node = sxp_new_get_member(parser, sxp_new_lookup(parser, NameToID("self")), yyvsp[0].id); }
    break;

  case 62:
#line 204 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 63:
#line 205 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 64:
#line 206 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 65:
#line 207 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 66:
#line 208 "grammar.yy"
    { yyerror("Warning: use of '@' concatenation operator is deprecrated; please use '+'"); yyval.node = sxp_new_math (parser, OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 67:
#line 209 "grammar.yy"
    { yyval.node = yyvsp[-1].node; }
    break;

  case 68:
#line 211 "grammar.yy"
    { yyval.node = sxp_new_in (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 69:
#line 213 "grammar.yy"
    {
			if (yyvsp[0].node->type == SXP_DATA && Value::IsA<Number>(parser->system, yyvsp[0].node->parts.value))
				yyval.node = sxp_new_data(parser,Number::Create(-Number::ToInt(yyvsp[0].node->parts.value)));
			else
				yyval.node = sxp_new_negate (parser, yyvsp[0].node); 
		}
    break;

  case 70:
#line 220 "grammar.yy"
    { yyval.node = sxp_new_not (parser, yyvsp[0].node); }
    break;

  case 71:
#line 221 "grammar.yy"
    { yyval.node = sxp_new_and (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 72:
#line 222 "grammar.yy"
    { yyval.node = sxp_new_or (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 73:
#line 224 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 74:
#line 225 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 75:
#line 226 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 76:
#line 227 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 77:
#line 228 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 78:
#line 229 "grammar.yy"
    { yyval.node = sxp_new_math (parser, OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 79:
#line 231 "grammar.yy"
    { yyval.node = sxp_new_assign (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 80:
#line 232 "grammar.yy"
    { yyval.node = sxp_new_setindex (parser, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;

  case 81:
#line 233 "grammar.yy"
    { yyval.node = sxp_new_set_member(parser, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 82:
#line 234 "grammar.yy"
    { yyval.node = sxp_new_set_member(parser, sxp_new_lookup(parser, NameToID("self")), yyvsp[-2].id, yyvsp[0].node); }
    break;

  case 83:
#line 236 "grammar.yy"
    { yyval.node = sxp_new_preop (parser, yyvsp[-2].node, OP_ADD, yyvsp[0].node); }
    break;

  case 84:
#line 237 "grammar.yy"
    { yyval.node = sxp_new_preop (parser, yyvsp[-2].node, OP_SUBTRACT, yyvsp[0].node); }
    break;

  case 85:
#line 238 "grammar.yy"
    { yyval.node = sxp_new_preop (parser, yyvsp[-2].node, OP_MULTIPLY, yyvsp[0].node); }
    break;

  case 86:
#line 239 "grammar.yy"
    { yyval.node = sxp_new_preop (parser, yyvsp[-2].node, OP_DIVIDE, yyvsp[0].node); }
    break;

  case 87:
#line 240 "grammar.yy"
    { yyval.node = sxp_new_postop (parser, yyvsp[-1].node, OP_ADD, sxp_new_data (parser, Number::Create (1))); }
    break;

  case 88:
#line 241 "grammar.yy"
    { yyval.node = sxp_new_preop (parser, yyvsp[0].node, OP_ADD, sxp_new_data (parser, Number::Create (1))); }
    break;

  case 89:
#line 242 "grammar.yy"
    { yyval.node = sxp_new_postop (parser, yyvsp[-1].node, OP_SUBTRACT, sxp_new_data (parser, Number::Create (1))); }
    break;

  case 90:
#line 243 "grammar.yy"
    { yyval.node = sxp_new_preop (parser, yyvsp[0].node, OP_SUBTRACT, sxp_new_data (parser, Number::Create (1))); }
    break;

  case 91:
#line 245 "grammar.yy"
    { yyerror("Warning: use of '(type)expr' casting is deprecrated; please use 'type(expr)'"); yyval.node = sxp_new_cast (parser, yyvsp[-2].type, yyvsp[0].node); }
    break;

  case 92:
#line 246 "grammar.yy"
    { yyval.node = sxp_new_cast (parser, yyvsp[-3].type, yyvsp[-1].node); }
    break;

  case 93:
#line 248 "grammar.yy"
    { yyval.node = sxp_new_invoke (parser, sxp_new_lookup(parser, yyvsp[-1].id), yyvsp[0].node); }
    break;

  case 94:
#line 249 "grammar.yy"
    { yyval.node = sxp_new_invoke (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;

  case 95:
#line 251 "grammar.yy"
    { yyval.node = sxp_new_new (parser, yyvsp[0].type, NULL, false); }
    break;

  case 96:
#line 252 "grammar.yy"
    { yyval.node = sxp_new_new (parser, yyvsp[-1].type, yyvsp[0].node, true); }
    break;

  case 97:
#line 253 "grammar.yy"
    { yyval.node = sxp_new_method (parser, yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 98:
#line 254 "grammar.yy"
    { yyval.node = sxp_new_method (parser, sxp_new_lookup(parser, NameToID("self")), yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 99:
#line 255 "grammar.yy"
    { yyval.node = sxp_new_smethod (parser, yyvsp[-3].type, yyvsp[-1].id, yyvsp[0].node); }
    break;

  case 100:
#line 257 "grammar.yy"
    { yyval.node = sxp_new_array (parser, yyvsp[-1].node); }
    break;

  case 101:
#line 258 "grammar.yy"
    { yyval.node = sxp_new_array (parser, NULL); }
    break;

  case 102:
#line 260 "grammar.yy"
    { yyval.node = sxp_new_data (parser, yyvsp[0].value); }
    break;

  case 103:
#line 262 "grammar.yy"
    { yyval.node = yyvsp[0].node; }
    break;

  case 104:
#line 266 "grammar.yy"
    { yyval.value = yyvsp[0].value;  }
    break;

  case 105:
#line 267 "grammar.yy"
    { yyval.value = yyvsp[0].value; }
    break;

  case 106:
#line 268 "grammar.yy"
    { yyval.value = NULL; }
    break;

  case 107:
#line 271 "grammar.yy"
    { yyval.id = yyvsp[0].id; }
    break;

  case 108:
#line 274 "grammar.yy"
    { yyval.type = yyvsp[0].type; }
    break;


    }

/* Line 999 of yacc.c.  */
#line 1948 "grammar.cc"

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


#line 277 "grammar.yy"


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
Scriptix::System::LoadFile(const std::string& file, SecurityLevel access) {
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

	parser = new ParserState(this);
	if (parser == NULL) {
		if (!file.empty())
			fclose (yyin);
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	if (!file.empty())
		parser->SetFile(file);
	parser->SetAccess(access);

	sxp_parser_inbuf = NULL;

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!file.empty())
		fclose (yyin);

	if (!ret)
		ret = parser->Compile();

	return ret;
}

int
Scriptix::System::LoadString(const std::string& buf, const std::string& name, size_t lineno, SecurityLevel access) {
	int ret;

	if (buf.empty())
		return SXE_INVALID;

	parser = new ParserState(this);
	if (parser == NULL) {
		std::cerr << "Failed to create Compiler context" << std::endl;
		return SXE_INTERNAL;
	}
	parser->SetAccess(access);
	parser->SetFile(name);
	parser->SetLine(lineno);

	yyin = NULL;
	sxp_parser_inbuf = buf.c_str();

	ret = yyparse ();
	if (yynerrs > 0)
		ret = SXE_INVALID;

	if (!ret)
		ret = parser->Compile();

	return ret;
}

