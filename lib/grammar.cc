/* A Bison parser, made from grammar.yy
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	NUMBER	257
# define	STRING	258
# define	IDENTIFIER	259
# define	TYPE	260
# define	TAG	261
# define	IF	262
# define	ELSE	263
# define	WHILE	264
# define	DO	265
# define	AND	266
# define	OR	267
# define	TGTE	268
# define	TLTE	269
# define	TNE	270
# define	TFOREACH	271
# define	TADDASSIGN	272
# define	TSUBASSIGN	273
# define	TINCREMENT	274
# define	TDECREMENT	275
# define	TNEW	276
# define	TUNTIL	277
# define	TNIL	278
# define	TRESCUE	279
# define	TIN	280
# define	TFOR	281
# define	TCONTINUE	282
# define	TYIELD	283
# define	TPUBLIC	284
# define	TBREAK	285
# define	TRETURN	286
# define	TEQUALS	287
# define	TCAST	288
# define	TLENGTH	289
# define	TRANGE	290
# define	CUNARY	291
# define	TSTATMETHOD	292

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

#line 57 "grammar.yy"
#ifndef YYSTYPE
typedef union {
	ParserNode* node;
	Value* value;
	sx_name_id id;
	sx_name_id* name_list;
	struct _sxp_arg_list args;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		194
#define	YYFLAG		-32768
#define	YYNTBASE	60

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 292 ? yytranslate[x] : 76)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,     2,     2,     2,    56,     2,
      49,    51,    39,    37,    55,    38,    46,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    54,
      35,    33,    34,     2,    57,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    58,    50,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    36,    41,    42,
      43,    45,    47
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     7,    10,    18,    27,    28,    38,
      43,    44,    46,    48,    51,    54,    58,    61,    64,    67,
      70,    76,    84,    90,    96,   104,   112,   115,   125,   133,
     137,   138,   140,   142,   146,   147,   149,   154,   157,   159,
     163,   167,   170,   174,   178,   182,   186,   190,   194,   198,
     201,   204,   208,   212,   216,   220,   224,   228,   232,   236,
     240,   247,   251,   255,   258,   261,   264,   267,   272,   277,
     280,   283,   288,   293,   299,   303,   308,   312,   314,   316,
     318,   320,   322,   324,   326
};
static const short yyrhs[] =
{
      -1,    60,    61,     0,    60,    63,     0,    60,     1,     0,
      74,    49,    69,    51,    52,    64,    53,     0,    30,    74,
      49,    69,    51,    52,    64,    53,     0,     0,    74,    62,
      74,    49,    69,    51,    52,    64,    53,     0,    74,    33,
      73,    54,     0,     0,    65,     0,    66,     0,    65,    66,
       0,    67,    54,     0,    32,    72,    54,     0,    32,    54,
       0,    31,    54,     0,    28,    54,     0,    29,    54,     0,
       8,    49,    72,    51,    66,     0,     8,    49,    72,    51,
      66,     9,    66,     0,    10,    49,    72,    51,    66,     0,
      23,    49,    72,    51,    66,     0,    11,    66,    10,    49,
      72,    51,    54,     0,    11,    66,    23,    49,    72,    51,
      54,     0,    11,    66,     0,    27,    49,    67,    54,    72,
      54,    67,    51,    66,     0,    17,    49,    74,    26,    72,
      51,    66,     0,    52,    64,    53,     0,     0,    72,     0,
      72,     0,    68,    55,    72,     0,     0,    70,     0,    70,
      55,    56,    74,     0,    56,    74,     0,    74,     0,    70,
      55,    74,     0,    49,    68,    51,     0,    49,    51,     0,
      72,    37,    72,     0,    72,    38,    72,     0,    72,    39,
      72,     0,    72,    40,    72,     0,    72,    57,    72,     0,
      49,    72,    51,     0,    72,    26,    72,     0,    38,    72,
       0,    44,    72,     0,    72,    12,    72,     0,    72,    13,
      72,     0,    72,    34,    72,     0,    72,    35,    72,     0,
      72,    16,    72,     0,    72,    14,    72,     0,    72,    15,
      72,     0,    72,    36,    72,     0,    74,    33,    72,     0,
      72,    48,    72,    58,    33,    72,     0,    74,    18,    72,
       0,    74,    19,    72,     0,    74,    20,     0,    20,    74,
       0,    74,    21,     0,    21,    74,     0,    49,    75,    51,
      72,     0,    75,    49,    72,    51,     0,    72,    71,     0,
      22,    75,     0,    72,    46,    74,    71,     0,    75,    46,
      74,    71,     0,    72,    59,    74,    33,    72,     0,    72,
      59,    74,     0,    72,    48,    72,    58,     0,    48,    68,
      58,     0,    73,     0,    74,     0,     1,     0,     3,     0,
       4,     0,    24,     0,     5,     0,     6,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    95,    96,    97,    98,   101,   102,   103,   103,   112,
     115,   116,   119,   120,   123,   124,   125,   126,   127,   128,
     130,   131,   132,   133,   134,   135,   136,   138,   139,   141,
     144,   145,   148,   149,   152,   153,   154,   155,   158,   159,
     162,   163,   166,   167,   168,   169,   170,   171,   173,   175,
     182,   183,   184,   186,   187,   188,   189,   190,   191,   193,
     194,   196,   197,   198,   199,   200,   201,   203,   204,   206,
     208,   209,   210,   211,   212,   214,   215,   217,   219,   221,
     225,   226,   227,   230,   233
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "NUMBER", "STRING", "IDENTIFIER", "TYPE", 
  "TAG", "IF", "ELSE", "WHILE", "DO", "AND", "OR", "TGTE", "TLTE", "TNE", 
  "TFOREACH", "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", 
  "TNEW", "TUNTIL", "TNIL", "TRESCUE", "TIN", "TFOR", "TCONTINUE", 
  "TYIELD", "TPUBLIC", "TBREAK", "TRETURN", "'='", "'>'", "'<'", 
  "TEQUALS", "'+'", "'-'", "'*'", "'/'", "TCAST", "TLENGTH", "TRANGE", 
  "'!'", "CUNARY", "'.'", "TSTATMETHOD", "'['", "'('", "'^'", "')'", 
  "'{'", "'}'", "';'", "','", "'&'", "'@'", "']'", "':'", "program", 
  "function", "@1", "global", "block", "stmts", "stmt", "node", "args", 
  "arg_names", "arg_names_list", "func_args", "expr", "data", "name", 
  "type", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    60,    60,    60,    60,    61,    61,    62,    61,    63,
      64,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      67,    67,    68,    68,    69,    69,    69,    69,    70,    70,
      71,    71,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      73,    73,    73,    74,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     2,     2,     7,     8,     0,     9,     4,
       0,     1,     1,     2,     2,     3,     2,     2,     2,     2,
       5,     7,     5,     5,     7,     7,     2,     9,     7,     3,
       0,     1,     1,     3,     0,     1,     4,     2,     1,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       6,     3,     3,     2,     2,     2,     2,     4,     4,     2,
       2,     4,     4,     5,     3,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     4,    83,     0,     2,     3,     7,     0,     0,
      34,     0,    34,    80,    81,    82,     0,     0,     0,    35,
      38,     0,     0,     9,    37,     0,     0,    34,     0,     0,
       0,    39,     0,     0,    79,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,     0,    31,    77,
      78,     0,    36,     0,     0,     0,     0,    26,     0,    64,
      66,    70,     0,     0,    18,    19,    17,    16,     0,    49,
      50,     0,    32,     0,     0,     0,     5,    13,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    69,     0,     0,
      63,    65,     0,     0,     0,     0,     6,     0,     0,     0,
       0,     0,     0,     0,    15,     0,    76,    47,     0,    29,
      51,    52,    56,    57,    55,    48,    53,    54,    58,    42,
      43,    44,    45,     0,     0,    41,     0,    46,    74,    61,
      62,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,    67,    71,    75,    40,     0,    72,    68,
       8,    20,    22,     0,     0,     0,    23,     0,     0,    73,
       0,     0,     0,     0,     0,    60,    21,    24,    25,    28,
       0,     0,    27,     0,     0
};

static const short yydefgoto[] =
{
       1,     5,    11,     6,    54,    55,    56,    57,    81,    18,
      19,   107,    58,    59,    60,    61
};

static const short yypact[] =
{
  -32768,     9,-32768,-32768,    11,-32768,-32768,   -26,   -18,    17,
       8,    11,     8,-32768,-32768,-32768,   -25,    11,   -15,     4,
  -32768,    -9,    22,-32768,-32768,     3,    10,     8,    16,   146,
      11,-32768,    29,   146,-32768,-32768,    26,    34,   254,    35,
      11,    11,    81,    41,    42,    43,    44,    47,   290,   424,
     424,   424,   424,   146,    50,   200,-32768,    62,   759,-32768,
      88,    28,-32768,    73,    82,   424,   424,     1,    11,-32768,
  -32768,-32768,   424,   321,-32768,-32768,-32768,-32768,   440,    80,
      80,    24,   759,   469,   -16,    83,-32768,-32768,-32768,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   424,
     424,   424,    11,   424,   352,   424,    11,-32768,   424,   424,
  -32768,-32768,   424,    11,   424,   146,-32768,   498,   527,    85,
      89,   114,   556,    90,-32768,   424,-32768,-32768,   424,-32768,
     786,   786,    56,    56,   790,    56,    56,    56,   790,    84,
      84,    80,    80,    97,   585,-32768,   -17,   759,   115,   759,
     759,   759,    97,   614,   102,   254,   254,   424,   424,   424,
     254,   424,   759,    80,-32768,   125,-32768,   424,-32768,-32768,
  -32768,   150,-32768,   643,   672,   701,-32768,   730,   424,   759,
     254,   106,   108,   254,   388,   759,-32768,-32768,-32768,-32768,
     113,   254,-32768,   171,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,   -27,-32768,   -38,   -65,    72,     0,
  -32768,  -115,   -47,   170,    59,   -20
};


#define	YYLAST		849


static const short yytable[] =
{
      67,    78,    79,    80,    82,    83,    64,     9,   123,   193,
       2,-32768,    22,     3,     3,     3,     3,    87,   117,   118,
      13,    14,    71,    10,-32768,   122,    85,    32,   164,    23,
     113,    12,    84,   114,   166,   128,    25,   168,   125,     4,
      27,    15,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,    29,   144,    82,   147,    26,
       7,   149,   150,     8,    17,   151,    30,   153,    33,    20,
      21,    20,    93,    28,   113,    65,    24,   114,   162,   125,
      63,   163,   126,    66,    68,    31,    20,    35,   154,    62,
      72,    73,    97,    98,    99,   100,   101,    74,    75,    69,
      70,    76,   102,    86,   103,   104,   108,   109,   110,   111,
     173,   174,   175,   105,   177,   106,    88,   171,   172,   190,
     179,   112,   176,   100,   101,   115,   102,   121,   103,   104,
     102,   185,   103,   104,   157,   116,   129,   105,   158,   106,
     159,   105,   186,   106,   161,   189,   104,    34,   167,    13,
      14,     3,    35,   192,    36,   170,    37,    38,   178,   180,
     187,   143,   188,    39,   191,   148,    40,    41,    42,    43,
      15,   194,   152,    44,    45,    46,   146,    47,    48,    16,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
      50,     0,     0,     0,    51,    52,     0,     0,    53,   -10,
     -30,    34,     0,    13,    14,     3,    35,     0,    36,     0,
      37,    38,     0,     0,     0,     0,     0,    39,     0,     0,
      40,    41,    42,    43,    15,     0,     0,    44,    45,    46,
       0,    47,    48,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,     0,    50,     0,     0,     0,    51,    52,
       0,     0,    53,   -11,   -30,    34,     0,    13,    14,     3,
      35,     0,    36,     0,    37,    38,     0,     0,     0,     0,
       0,    39,     0,     0,    40,    41,    42,    43,    15,     0,
       0,    44,    45,    46,     0,    47,    48,     0,     0,     0,
       0,    34,    49,    13,    14,     3,    35,     0,    50,     0,
       0,     0,    51,    52,     0,     0,    53,     0,   -30,     0,
      40,    41,    42,     0,    15,     0,     0,     0,     0,     0,
       0,     0,    34,     0,    13,    14,     3,    35,    49,     0,
       0,     0,     0,     0,    50,     0,     0,     0,    51,    52,
       0,    40,    41,    42,    77,    15,     0,     0,     0,     0,
       0,     0,     0,    34,     0,    13,    14,     3,    35,    49,
       0,     0,     0,     0,     0,    50,     0,     0,     0,    51,
      52,     0,    40,    41,    42,   -30,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      49,    13,    14,     3,    35,     0,    50,     0,     0,     0,
      51,    52,     0,   145,     0,     0,     0,     0,    40,    41,
      42,     0,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    49,    13,    14,     3,
      35,     0,    50,     0,     0,     0,    51,    52,     0,   -30,
       0,     0,     0,     0,    40,    41,    42,     0,    15,     0,
       0,     0,    89,    90,    91,    92,    93,     0,     0,     0,
       0,     0,    49,     0,     0,     0,    94,     0,    50,     0,
       0,     0,    51,    52,    95,    96,    97,    98,    99,   100,
     101,    89,    90,    91,    92,    93,   102,     0,   103,   104,
       0,     0,     0,     0,   124,    94,     0,   105,     0,   106,
       0,     0,     0,    95,    96,    97,    98,    99,   100,   101,
      89,    90,    91,    92,    93,   102,     0,   103,   104,     0,
     127,     0,     0,     0,    94,     0,   105,     0,   106,     0,
       0,     0,    95,    96,    97,    98,    99,   100,   101,    89,
      90,    91,    92,    93,   102,     0,   103,   104,     0,   155,
       0,     0,     0,    94,     0,   105,     0,   106,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,    89,    90,
      91,    92,    93,   102,     0,   103,   104,     0,   156,     0,
       0,     0,    94,     0,   105,     0,   106,     0,     0,     0,
      95,    96,    97,    98,    99,   100,   101,    89,    90,    91,
      92,    93,   102,     0,   103,   104,     0,   160,     0,     0,
       0,    94,     0,   105,     0,   106,     0,     0,     0,    95,
      96,    97,    98,    99,   100,   101,    89,    90,    91,    92,
      93,   102,     0,   103,   104,     0,     0,     0,     0,     0,
      94,     0,   105,   165,   106,     0,     0,     0,    95,    96,
      97,    98,    99,   100,   101,    89,    90,    91,    92,    93,
     102,     0,   103,   104,     0,   169,     0,     0,     0,    94,
       0,   105,     0,   106,     0,     0,     0,    95,    96,    97,
      98,    99,   100,   101,    89,    90,    91,    92,    93,   102,
       0,   103,   104,     0,   181,     0,     0,     0,    94,     0,
     105,     0,   106,     0,     0,     0,    95,    96,    97,    98,
      99,   100,   101,    89,    90,    91,    92,    93,   102,     0,
     103,   104,     0,   182,     0,     0,     0,    94,     0,   105,
       0,   106,     0,     0,     0,    95,    96,    97,    98,    99,
     100,   101,    89,    90,    91,    92,    93,   102,     0,   103,
     104,     0,   183,     0,     0,     0,    94,     0,   105,     0,
     106,     0,     0,     0,    95,    96,    97,    98,    99,   100,
     101,    89,    90,    91,    92,    93,   102,     0,   103,   104,
       0,     0,     0,     0,   184,    94,     0,   105,     0,   106,
       0,     0,     0,    95,    96,    97,    98,    99,   100,   101,
      91,    92,    93,     0,     0,   102,     0,   103,   104,     0,
       0,     0,    94,     0,     0,     0,   105,     0,   106,     0,
      95,    96,    97,    98,    99,   100,   101,    98,    99,   100,
     101,     0,   102,     0,   103,   104,   102,     0,   103,   104,
       0,     0,     0,   105,     0,   106,     0,   105,     0,   106
};

static const short yycheck[] =
{
      38,    48,    49,    50,    51,    52,    33,    33,    73,     0,
       1,    10,    12,     5,     5,     5,     5,    55,    65,    66,
       3,     4,    42,    49,    23,    72,    53,    27,   143,    54,
      46,    49,    52,    49,    51,    51,    51,   152,    55,    30,
      49,    24,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,    52,   103,   104,   105,    55,
       1,   108,   109,     4,    56,   112,    56,   114,    52,    10,
      11,    12,    16,    51,    46,    49,    17,    49,   125,    55,
      51,   128,    58,    49,    49,    26,    27,     6,   115,    30,
      49,    49,    36,    37,    38,    39,    40,    54,    54,    40,
      41,    54,    46,    53,    48,    49,    18,    19,    20,    21,
     157,   158,   159,    57,   161,    59,    54,   155,   156,   184,
     167,    33,   160,    39,    40,    52,    46,    68,    48,    49,
      46,   178,    48,    49,    49,    53,    53,    57,    49,    59,
      26,    57,   180,    59,    54,   183,    49,     1,    33,     3,
       4,     5,     6,   191,     8,    53,    10,    11,    33,     9,
      54,   102,    54,    17,    51,   106,    20,    21,    22,    23,
      24,     0,   113,    27,    28,    29,   104,    31,    32,     9,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    48,    49,    -1,    -1,    52,    53,
      54,     1,    -1,     3,     4,     5,     6,    -1,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      20,    21,    22,    23,    24,    -1,    -1,    27,    28,    29,
      -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,    49,
      -1,    -1,    52,    53,    54,     1,    -1,     3,     4,     5,
       6,    -1,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    20,    21,    22,    23,    24,    -1,
      -1,    27,    28,    29,    -1,    31,    32,    -1,    -1,    -1,
      -1,     1,    38,     3,     4,     5,     6,    -1,    44,    -1,
      -1,    -1,    48,    49,    -1,    -1,    52,    -1,    54,    -1,
      20,    21,    22,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,     4,     5,     6,    38,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,    49,
      -1,    20,    21,    22,    54,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,    38,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,
      49,    -1,    20,    21,    22,    54,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      38,     3,     4,     5,     6,    -1,    44,    -1,    -1,    -1,
      48,    49,    -1,    51,    -1,    -1,    -1,    -1,    20,    21,
      22,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    38,     3,     4,     5,
       6,    -1,    44,    -1,    -1,    -1,    48,    49,    -1,    51,
      -1,    -1,    -1,    -1,    20,    21,    22,    -1,    24,    -1,
      -1,    -1,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    26,    -1,    44,    -1,
      -1,    -1,    48,    49,    34,    35,    36,    37,    38,    39,
      40,    12,    13,    14,    15,    16,    46,    -1,    48,    49,
      -1,    -1,    -1,    -1,    54,    26,    -1,    57,    -1,    59,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      12,    13,    14,    15,    16,    46,    -1,    48,    49,    -1,
      51,    -1,    -1,    -1,    26,    -1,    57,    -1,    59,    -1,
      -1,    -1,    34,    35,    36,    37,    38,    39,    40,    12,
      13,    14,    15,    16,    46,    -1,    48,    49,    -1,    51,
      -1,    -1,    -1,    26,    -1,    57,    -1,    59,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    12,    13,
      14,    15,    16,    46,    -1,    48,    49,    -1,    51,    -1,
      -1,    -1,    26,    -1,    57,    -1,    59,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    12,    13,    14,
      15,    16,    46,    -1,    48,    49,    -1,    51,    -1,    -1,
      -1,    26,    -1,    57,    -1,    59,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    12,    13,    14,    15,
      16,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    57,    58,    59,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    12,    13,    14,    15,    16,
      46,    -1,    48,    49,    -1,    51,    -1,    -1,    -1,    26,
      -1,    57,    -1,    59,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    12,    13,    14,    15,    16,    46,
      -1,    48,    49,    -1,    51,    -1,    -1,    -1,    26,    -1,
      57,    -1,    59,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    12,    13,    14,    15,    16,    46,    -1,
      48,    49,    -1,    51,    -1,    -1,    -1,    26,    -1,    57,
      -1,    59,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    12,    13,    14,    15,    16,    46,    -1,    48,
      49,    -1,    51,    -1,    -1,    -1,    26,    -1,    57,    -1,
      59,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      40,    12,    13,    14,    15,    16,    46,    -1,    48,    49,
      -1,    -1,    -1,    -1,    54,    26,    -1,    57,    -1,    59,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      14,    15,    16,    -1,    -1,    46,    -1,    48,    49,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    57,    -1,    59,    -1,
      34,    35,    36,    37,    38,    39,    40,    37,    38,    39,
      40,    -1,    46,    -1,    48,    49,    46,    -1,    48,    49,
      -1,    -1,    -1,    57,    -1,    59,    -1,    57,    -1,    59
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

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
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

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
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


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
#define YYABORT 	goto yyabortlab
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
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
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

#ifdef YYERROR_VERBOSE

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
#endif

#line 315 "/usr/share/bison/bison.simple"


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

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

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

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
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
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
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
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
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
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

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
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
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
      if (yyn == YYFLAG)
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
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 5:
#line 101 "grammar.yy"
{ parser->AddFunc(yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 0); }
    break;
case 6:
#line 102 "grammar.yy"
{ parser->AddFunc(yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, NULL, 1); }
    break;
case 7:
#line 103 "grammar.yy"
{ 
		if (!parser->GetSystem()->ValidFunctionTag(IDToName (yyvsp[0].id))) {
			yyerror ("Unregistered tag");
			YYERROR;
		}
		yyval.id = yyvsp[0].id;
	}
    break;
case 8:
#line 109 "grammar.yy"
{ parser->AddFunc(yyvsp[-6].id, yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node, IDToName(yyvsp[-7].id), 1); }
    break;
case 9:
#line 112 "grammar.yy"
{ parser->SetGlobal(yyvsp[-3].id, yyvsp[-1].value); }
    break;
case 10:
#line 115 "grammar.yy"
{ yyval.node = NULL; }
    break;
case 11:
#line 116 "grammar.yy"
{ yyval.node = yyvsp[0].node; }
    break;
case 12:
#line 119 "grammar.yy"
{ yyval.node = yyvsp[0].node; }
    break;
case 13:
#line 120 "grammar.yy"
{ yyval.node = yyvsp[-1].node; yyval.node->Append(yyvsp[0].node); }
    break;
case 14:
#line 123 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 15:
#line 124 "grammar.yy"
{ yyval.node = sxp_new_return (parser, yyvsp[-1].node); }
    break;
case 16:
#line 125 "grammar.yy"
{ yyval.node = sxp_new_return (parser, NULL); }
    break;
case 17:
#line 126 "grammar.yy"
{ yyval.node = sxp_new_break (parser); }
    break;
case 18:
#line 127 "grammar.yy"
{ yyval.node = sxp_new_continue (parser); }
    break;
case 19:
#line 128 "grammar.yy"
{ yyval.node = sxp_new_yield (parser); }
    break;
case 20:
#line 130 "grammar.yy"
{ yyval.node = sxp_new_if (parser, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;
case 21:
#line 131 "grammar.yy"
{ yyval.node = sxp_new_if (parser, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 22:
#line 132 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_WHILE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 23:
#line 133 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_UNTIL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 24:
#line 134 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_DOWHILE, yyvsp[-2].node, yyvsp[-5].node); }
    break;
case 25:
#line 135 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_DOUNTIL, yyvsp[-2].node, yyvsp[-5].node); }
    break;
case 26:
#line 136 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_FOREVER, NULL, yyvsp[0].node); }
    break;
case 27:
#line 138 "grammar.yy"
{ yyval.node = sxp_new_for (parser, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 28:
#line 139 "grammar.yy"
{ yyval.node = sxp_new_foreach (parser, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 29:
#line 141 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 30:
#line 144 "grammar.yy"
{ yyval.node = NULL; }
    break;
case 31:
#line 145 "grammar.yy"
{ yyval.node = sxp_new_statement (parser, yyvsp[0].node); }
    break;
case 32:
#line 148 "grammar.yy"
{ yyval.node = yyvsp[0].node; }
    break;
case 33:
#line 149 "grammar.yy"
{ yyval.node = yyvsp[-2].node; yyval.node->Append(yyvsp[0].node); }
    break;
case 34:
#line 152 "grammar.yy"
{ yyval.args.args = NULL; yyval.args.varg = 0; }
    break;
case 35:
#line 153 "grammar.yy"
{ yyval.args.args = yyvsp[0].name_list; yyval.args.varg = 0; }
    break;
case 36:
#line 154 "grammar.yy"
{ yyval.args.args = yyvsp[-3].name_list; yyval.args.varg = yyvsp[0].id; }
    break;
case 37:
#line 155 "grammar.yy"
{ yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;
case 38:
#line 158 "grammar.yy"
{ yyval.name_list = sx_new_namelist (parser->GetSystem(), 1, yyvsp[0].id); }
    break;
case 39:
#line 159 "grammar.yy"
{ yyval.name_list = sx_namelist_append (parser->GetSystem(), yyvsp[-2].name_list, yyvsp[0].id); }
    break;
case 40:
#line 162 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 41:
#line 163 "grammar.yy"
{ yyval.node = NULL; }
    break;
case 42:
#line 166 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 43:
#line 167 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 44:
#line 168 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 45:
#line 169 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 46:
#line 170 "grammar.yy"
{ yyval.node = sxp_new_concat (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 47:
#line 171 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 48:
#line 173 "grammar.yy"
{ yyval.node = sxp_new_in (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 49:
#line 175 "grammar.yy"
{
			if (yyvsp[0].node->type == SXP_DATA && Value::IsA<Number>(yyvsp[0].node->parts.value))
				yyval.node = sxp_new_data(parser,Number::Create(-Number::ToInt(yyvsp[0].node->parts.value)));
			else
				yyval.node = sxp_new_negate (parser, yyvsp[0].node); 
		}
    break;
case 50:
#line 182 "grammar.yy"
{ yyval.node = sxp_new_not (parser, yyvsp[0].node); }
    break;
case 51:
#line 183 "grammar.yy"
{ yyval.node = sxp_new_and (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 52:
#line 184 "grammar.yy"
{ yyval.node = sxp_new_or (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 53:
#line 186 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 54:
#line 187 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 55:
#line 188 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 56:
#line 189 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 57:
#line 190 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 58:
#line 191 "grammar.yy"
{ yyval.node = sxp_new_math (parser, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 59:
#line 193 "grammar.yy"
{ yyval.node = sxp_new_assign (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 60:
#line 194 "grammar.yy"
{ yyval.node = sxp_new_setindex (parser, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;
case 61:
#line 196 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 62:
#line 197 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[-2].id, sxp_new_negate (parser, yyvsp[0].node)); }
    break;
case 63:
#line 198 "grammar.yy"
{ yyval.node = sxp_new_postinc (parser, yyvsp[-1].id, sxp_new_data (parser, Number::Create (1))); }
    break;
case 64:
#line 199 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[0].id, sxp_new_data (parser, Number::Create (1))); }
    break;
case 65:
#line 200 "grammar.yy"
{ yyval.node = sxp_new_postinc (parser, yyvsp[-1].id, sxp_new_data (parser, Number::Create (-1))); }
    break;
case 66:
#line 201 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[0].id, sxp_new_data (parser, Number::Create (-1))); }
    break;
case 67:
#line 203 "grammar.yy"
{ yyval.node = sxp_new_cast (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 68:
#line 204 "grammar.yy"
{ yyval.node = sxp_new_cast (parser, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 69:
#line 206 "grammar.yy"
{ yyval.node = sxp_new_invoke (parser, yyvsp[-1].node, yyvsp[0].node); }
    break;
case 70:
#line 208 "grammar.yy"
{ yyval.node = sxp_new_new (parser, yyvsp[0].id); }
    break;
case 71:
#line 209 "grammar.yy"
{ yyval.node = sxp_new_method (parser, yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node); }
    break;
case 72:
#line 210 "grammar.yy"
{ yyval.node = sxp_new_smethod (parser, yyvsp[-3].id, yyvsp[-1].id, yyvsp[0].node); }
    break;
case 73:
#line 211 "grammar.yy"
{ yyval.node = sxp_new_set_member(parser, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 74:
#line 212 "grammar.yy"
{ yyval.node = sxp_new_get_member (parser, yyvsp[-2].node, yyvsp[0].id); }
    break;
case 75:
#line 214 "grammar.yy"
{ yyval.node = sxp_new_getindex (parser, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 76:
#line 215 "grammar.yy"
{ yyval.node = sxp_new_array (parser, yyvsp[-1].node); }
    break;
case 77:
#line 217 "grammar.yy"
{ yyval.node = sxp_new_data (parser, yyvsp[0].value); }
    break;
case 78:
#line 219 "grammar.yy"
{ yyval.node = sxp_new_lookup (parser, yyvsp[0].id); }
    break;
case 79:
#line 221 "grammar.yy"
{ yyval.node = sxp_new_data (parser, NULL); }
    break;
case 80:
#line 225 "grammar.yy"
{ yyval.value = yyvsp[0].value;  }
    break;
case 81:
#line 226 "grammar.yy"
{ yyval.value = yyvsp[0].value; }
    break;
case 82:
#line 227 "grammar.yy"
{ yyval.value = NULL; }
    break;
case 83:
#line 230 "grammar.yy"
{ yyval.id = yyvsp[0].id; }
    break;
case 84:
#line 233 "grammar.yy"
{ yyval.id = yyvsp[0].id; }
    break;
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

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
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
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
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

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

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 236 "grammar.yy"


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
