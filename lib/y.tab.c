/* A Bison parser, made from grammar.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse sxparse
#define yylex sxlex
#define yyerror sxerror
#define yylval sxlval
#define yychar sxchar
#define yydebug sxdebug
#define yynerrs sxnerrs
# define	TNUM	257
# define	TSTR	258
# define	TNAME	259
# define	TIF	260
# define	TELSE	261
# define	TWHILE	262
# define	TDO	263
# define	TAND	264
# define	TOR	265
# define	TGTE	266
# define	TLTE	267
# define	TNE	268
# define	TSTATMETHOD	269
# define	TRETURN	270
# define	TBREAK	271
# define	TLOCAL	272
# define	TGLOBAL	273
# define	TEQUALS	274
# define	TCONTINUE	275
# define	TSUPER	276
# define	TADDASSIGN	277
# define	TSUBASSIGN	278
# define	TINCREMENT	279
# define	TDECREMENT	280
# define	TSTATIC	281
# define	TCLASS	282
# define	TNEW	283
# define	TUNTIL	284
# define	TNIL	285
# define	TRAISE	286
# define	TRESCUE	287
# define	TTRY	288
# define	TIN	289
# define	TFOR	290
# define	TISA	291
# define	TLENGTH	292
# define	TRANGE	293
# define	CUNARY	294

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

	__INLINE__ void parser_add_line (void);

	int sxerror (const char *);
	int sxlex (void);

	SXP_INFO *parse_info = NULL;

#line 49 "grammar.y"
#ifndef YYSTYPE
typedef union {
	SXP_NODE *node;
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	sx_name_id id;
	struct _sxp_arg_list args;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		221
#define	YYFLAG		-32768
#define	YYNTBASE	61

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 294 ? yytranslate[x] : 80)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,     2,     2,     2,    59,     2,
      51,    56,    43,    41,    58,    42,    49,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,    57,
      39,    37,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    60,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
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
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    40,    45,    46,    48
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     7,     8,    15,    16,    25,    27,
      30,    38,    47,    50,    58,    59,    61,    63,    66,    69,
      72,    78,    86,    92,    98,   106,   114,   126,   133,   143,
     147,   148,   150,   153,   155,   157,   159,   162,   166,   167,
     169,   173,   174,   176,   181,   184,   186,   190,   191,   194,
     199,   203,   207,   211,   215,   219,   222,   225,   229,   233,
     237,   241,   245,   249,   253,   257,   261,   266,   271,   278,
     284,   288,   292,   295,   298,   301,   304,   308,   313,   318,
     325,   332,   336,   342,   347,   351,   353,   355,   358,   361,
     363,   365,   367
};
static const short yyrhs[] =
{
      -1,    61,    62,     0,    61,    67,     0,     0,    28,    79,
      63,    53,    65,    54,     0,     0,    28,    79,    55,    79,
      64,    53,    65,    54,     0,    66,     0,    65,    66,     0,
      79,    51,    74,    56,    53,    68,    54,     0,    27,    79,
      51,    74,    56,    53,    68,    54,     0,    79,    57,     0,
      79,    51,    74,    56,    53,    68,    54,     0,     0,    69,
       0,    70,     0,    69,    70,     0,    71,    57,     0,    72,
      57,     0,     6,    51,    77,    56,    70,     0,     6,    51,
      77,    56,    70,     7,    70,     0,     8,    51,    77,    56,
      70,     0,    30,    51,    77,    56,    70,     0,     9,    70,
       8,    51,    77,    56,    57,     0,     9,    70,    30,    51,
      77,    56,    57,     0,    34,    53,    68,    54,    33,    51,
      76,    56,    53,    68,    54,     0,    36,    79,    35,    77,
       9,    70,     0,    36,    51,    71,    57,    77,    57,    71,
      56,    70,     0,    53,    68,    54,     0,     0,    77,     0,
      16,    77,     0,    16,     0,    17,     0,    21,     0,    32,
      79,     0,    32,    79,    77,     0,     0,    77,     0,    73,
      58,    77,     0,     0,    75,     0,    75,    58,    59,    79,
       0,    59,    79,     0,    79,     0,    75,    58,    79,     0,
       0,    79,    79,     0,    76,    58,    79,    79,     0,    77,
      41,    77,     0,    77,    42,    77,     0,    77,    43,    77,
       0,    77,    44,    77,     0,    51,    77,    56,     0,    42,
      77,     0,    47,    77,     0,    77,    10,    77,     0,    77,
      11,    77,     0,    77,    38,    77,     0,    77,    39,    77,
       0,    77,    14,    77,     0,    77,    12,    77,     0,    77,
      13,    77,     0,    77,    20,    77,     0,    79,    37,    77,
       0,    18,    79,    37,    77,     0,    19,    79,    37,    77,
       0,    77,    50,    77,    60,    37,    77,     0,    77,    49,
      79,    37,    77,     0,    79,    23,    77,     0,    79,    24,
      77,     0,    79,    25,     0,    25,    79,     0,    79,    26,
       0,    26,    79,     0,    77,    40,    79,     0,    79,    51,
      73,    56,     0,    22,    51,    73,    56,     0,    79,    15,
      79,    51,    73,    56,     0,    77,    49,    79,    51,    73,
      56,     0,    77,    49,    79,     0,    29,    79,    51,    73,
      56,     0,    77,    50,    77,    60,     0,    50,    73,    60,
       0,    78,     0,    79,     0,    18,    79,     0,    19,    79,
       0,     3,     0,     4,     0,    31,     0,     5,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    86,    87,    88,    91,    91,    92,    92,    95,    96,
      99,   100,   101,   109,   112,   113,   116,   117,   120,   121,
     122,   123,   124,   125,   126,   127,   129,   131,   132,   134,
     137,   138,   141,   142,   143,   144,   145,   146,   149,   150,
     151,   154,   155,   156,   157,   160,   161,   164,   165,   166,
     169,   170,   171,   172,   173,   175,   177,   178,   179,   181,
     182,   183,   184,   185,   186,   188,   189,   190,   191,   192,
     194,   195,   196,   197,   198,   199,   201,   202,   203,   205,
     206,   207,   208,   210,   211,   213,   215,   216,   217,   221,
     222,   223,   226
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "TNUM", "TSTR", "TNAME", "TIF", "TELSE", 
  "TWHILE", "TDO", "TAND", "TOR", "TGTE", "TLTE", "TNE", "TSTATMETHOD", 
  "TRETURN", "TBREAK", "TLOCAL", "TGLOBAL", "TEQUALS", "TCONTINUE", 
  "TSUPER", "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", 
  "TSTATIC", "TCLASS", "TNEW", "TUNTIL", "TNIL", "TRAISE", "TRESCUE", 
  "TTRY", "TIN", "TFOR", "'='", "'>'", "'<'", "TISA", "'+'", "'-'", "'*'", 
  "'/'", "TLENGTH", "TRANGE", "'!'", "CUNARY", "'.'", "'['", "'('", "'^'", 
  "'{'", "'}'", "':'", "')'", "';'", "','", "'&'", "']'", "program", 
  "class", "@1", "@2", "cblock", "cstmt", "function", "block", "stmts", 
  "stmt", "node", "control", "args", "arg_names", "arg_names_list", 
  "errors", "expr", "data", "name", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    61,    61,    61,    63,    62,    64,    62,    65,    65,
      66,    66,    66,    67,    68,    68,    69,    69,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      71,    71,    72,    72,    72,    72,    72,    72,    73,    73,
      73,    74,    74,    74,    74,    75,    75,    76,    76,    76,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      78,    78,    79
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     2,     0,     6,     0,     8,     1,     2,
       7,     8,     2,     7,     0,     1,     1,     2,     2,     2,
       5,     7,     5,     5,     7,     7,    11,     6,     9,     3,
       0,     1,     2,     1,     1,     1,     2,     3,     0,     1,
       3,     0,     1,     4,     2,     1,     3,     0,     2,     4,
       3,     3,     3,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     4,     6,     5,
       3,     3,     2,     2,     2,     2,     3,     4,     4,     6,
       6,     3,     5,     4,     3,     1,     1,     2,     2,     1,
       1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,    92,     0,     2,     3,     0,     4,    41,     0,
       0,     0,     0,    42,    45,     6,     0,    44,     0,     0,
       0,     0,     0,     8,     0,    14,     0,    46,     0,     0,
       5,     9,    41,    12,    89,    90,     0,     0,    30,    33,
      34,     0,     0,    35,     0,     0,     0,     0,     0,    91,
       0,     0,     0,     0,     0,    38,     0,    14,     0,    15,
      16,     0,     0,    31,    85,    86,    43,     0,    41,     0,
       0,     0,     0,    32,    87,    88,    38,    73,    75,     0,
       0,    36,    14,    30,     0,    55,    56,     0,    39,     0,
       0,    13,    17,    18,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    72,    74,     0,    38,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    38,     0,    37,
       0,     0,     0,     0,    84,    54,    29,    57,    58,    62,
      63,    61,    64,    59,    60,    76,    50,    51,    52,    53,
      81,     0,     0,    70,    71,    65,     0,     0,    14,    30,
      30,     0,     0,    66,    67,    78,     0,    30,     0,     0,
       0,    40,     0,    38,    83,    38,    77,    14,     0,    20,
      22,     0,     0,    82,    23,     0,     0,    30,    69,     0,
       0,     0,     0,    10,    30,     0,     0,    47,    30,    27,
      80,    68,    79,    11,    21,    24,    25,     0,     0,     0,
       0,     0,    48,    30,    14,     0,    28,     0,    49,    26,
       0,     0
};

static const short yydefgoto[] =
{
       1,     4,    10,    20,    22,    23,     5,    58,    59,    60,
      61,    62,    87,    12,    13,   207,    63,    64,    65
};

static const short yypact[] =
{
  -32768,    14,-32768,    53,-32768,-32768,   -27,   -22,     0,    53,
      18,    53,    16,    30,-32768,-32768,    21,-32768,    47,     1,
      51,    53,     7,-32768,   -34,   215,    53,-32768,    21,    52,
  -32768,-32768,     0,-32768,-32768,-32768,    62,    64,   270,   357,
  -32768,    53,    53,-32768,    66,    53,    53,    53,    68,-32768,
      53,    75,     4,   357,   357,   357,   357,   215,    79,   215,
  -32768,    77,    86,   646,-32768,    13,-32768,     8,     0,    92,
     357,   357,    24,   646,   116,   117,   357,-32768,-32768,   107,
     357,   357,   215,   357,   124,    19,    19,     5,   646,   380,
     106,-32768,-32768,-32768,-32768,   357,   357,   357,   357,   357,
     357,   357,   357,    53,   357,   357,   357,   357,    53,   357,
      53,   357,   357,-32768,-32768,   357,   357,-32768,   110,   109,
     421,   462,   112,   118,   357,   357,    22,   357,   503,   646,
     114,   113,   357,   357,-32768,-32768,-32768,   680,   693,    33,
      33,    48,    48,    33,    33,-32768,    82,    82,    19,    19,
       6,   314,   120,   646,   646,   646,    28,   121,   215,   270,
     270,   357,   357,   646,   646,-32768,    29,   270,   142,   357,
     633,   646,   357,   357,   140,   357,-32768,   215,   125,   171,
  -32768,   544,   585,-32768,-32768,   129,   328,   270,   646,    43,
     357,    50,   127,-32768,   270,   126,   128,    53,   357,-32768,
  -32768,   646,-32768,-32768,-32768,-32768,-32768,    56,    53,   130,
     131,    53,-32768,   270,   215,    53,-32768,   133,-32768,-32768,
     182,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,   160,   -11,-32768,   -53,-32768,   -37,
     -80,-32768,   -46,   -16,-32768,-32768,    40,-32768,    -1
};


#define	YYLAST		743


static const short yytable[] =
{
       6,    72,     7,   131,    90,     2,     2,    14,    15,     2,
      17,    31,     2,     2,   220,    24,    69,    32,    27,     2,
      29,    24,    92,    33,     8,    66,     2,    24,   110,   130,
     126,    14,   122,     9,    21,    21,   111,   112,   113,   114,
      74,    75,     3,   172,    77,    78,    79,    99,    21,    81,
     115,    84,   118,   100,   123,    83,    31,   173,     2,    11,
      26,    30,   117,   133,   116,   134,    24,    14,   108,   109,
     156,    16,    18,   103,   104,   105,   106,   107,   165,    73,
     133,   166,   108,   109,   176,   183,   133,   133,    19,   104,
     105,   106,   107,    85,    86,    88,    89,   108,   109,   200,
      25,   133,   145,    68,    28,   178,   202,   150,   133,   152,
     120,   121,   210,    70,   211,    71,    88,    76,   209,    80,
     128,   129,   179,   180,   192,   106,   107,   189,    82,   191,
     184,   108,   109,    91,    93,   137,   138,   139,   140,   141,
     142,   143,   144,    94,   146,   147,   148,   149,   119,   151,
     199,   153,   154,   124,   125,   155,    88,   204,   127,   132,
     136,   217,   158,   161,   163,   164,   157,    88,   168,   162,
     169,   175,   170,   171,   177,   185,   216,   190,   194,   193,
     197,   203,   221,   205,   214,   206,   213,   219,    67,     0,
       0,     0,     0,     0,     0,     0,   208,     0,     0,     0,
       0,   181,   182,     0,     0,     0,     0,   212,     0,   186,
     215,     0,   188,    88,   218,    88,     0,     0,    34,    35,
       2,    36,     0,    37,    38,     0,     0,     0,     0,     0,
     201,    39,    40,    41,    42,     0,    43,    44,     0,     0,
      45,    46,     0,     0,    47,    48,    49,    50,     0,    51,
       0,    52,     0,     0,     0,     0,     0,    53,     0,     0,
       0,     0,    54,     0,     0,    55,    56,     0,    57,     0,
       0,     0,   -30,    34,    35,     2,    36,     0,    37,    38,
       0,     0,     0,     0,     0,     0,    39,    40,    41,    42,
       0,    43,    44,     0,     0,    45,    46,     0,     0,    47,
      48,    49,    50,     0,    51,     0,    52,     0,     0,     0,
       0,     0,    53,     0,     0,     0,     0,    54,     0,     0,
      55,    56,     0,    57,    95,    96,    97,    98,    99,     0,
       0,     0,     0,     0,   100,     0,     0,     0,    95,    96,
      97,    98,    99,     0,     0,     0,     0,     0,   100,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,     0,
      34,    35,     2,   108,   109,     0,   101,   102,   103,   104,
     105,   106,   107,     0,   174,    41,    42,   108,   109,    44,
       0,     0,    45,    46,     0,   198,    47,     0,    49,     0,
      95,    96,    97,    98,    99,     0,     0,     0,     0,    53,
     100,     0,     0,     0,    54,     0,     0,    55,    56,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,   107,     0,     0,     0,     0,   108,
     109,    95,    96,    97,    98,    99,   135,     0,     0,     0,
       0,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   107,     0,     0,     0,     0,
     108,   109,    95,    96,    97,    98,    99,   159,     0,     0,
       0,     0,   100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,   107,     0,     0,     0,
       0,   108,   109,    95,    96,    97,    98,    99,   160,     0,
       0,     0,     0,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,     0,     0,
       0,     0,   108,   109,    95,    96,    97,    98,    99,   167,
       0,     0,     0,     0,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,   108,   109,    95,    96,    97,    98,    99,
     195,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,   102,   103,   104,   105,   106,   107,
       0,     0,     0,     0,   108,   109,     0,     0,     0,     0,
       0,   196,   187,    95,    96,    97,    98,    99,     0,     0,
       0,     0,     0,   100,     0,     0,    95,    96,    97,    98,
      99,     0,     0,     0,     0,     0,   100,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,   107,     0,     0,
       0,     0,   108,   109,   101,   102,   103,   104,   105,   106,
     107,    96,    97,    98,    99,   108,   109,     0,     0,     0,
     100,     0,     0,     0,     0,    97,    98,    99,     0,     0,
       0,     0,     0,   100,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,   107,     0,     0,     0,     0,   108,
     109,   101,   102,   103,   104,   105,   106,   107,     0,     0,
       0,     0,   108,   109
};

static const short yycheck[] =
{
       1,    38,     3,    83,    57,     5,     5,     8,     9,     5,
      11,    22,     5,     5,     0,    16,    32,    51,    19,     5,
      21,    22,    59,    57,    51,    26,     5,    28,    15,    82,
      76,    32,     8,    55,    27,    27,    23,    24,    25,    26,
      41,    42,    28,    37,    45,    46,    47,    14,    27,    50,
      37,    52,    68,    20,    30,    51,    67,    51,     5,    59,
      59,    54,    54,    58,    51,    60,    67,    68,    49,    50,
     116,    53,    56,    40,    41,    42,    43,    44,    56,    39,
      58,   127,    49,    50,    56,    56,    58,    58,    58,    41,
      42,    43,    44,    53,    54,    55,    56,    49,    50,    56,
      53,    58,   103,    51,    53,   158,    56,   108,    58,   110,
      70,    71,    56,    51,    58,    51,    76,    51,   198,    51,
      80,    81,   159,   160,   177,    43,    44,   173,    53,   175,
     167,    49,    50,    54,    57,    95,    96,    97,    98,    99,
     100,   101,   102,    57,   104,   105,   106,   107,    56,   109,
     187,   111,   112,    37,    37,   115,   116,   194,    51,    35,
      54,   214,    53,    51,   124,   125,    56,   127,    54,    51,
      57,    51,   132,   133,    53,    33,   213,    37,     7,    54,
      51,    54,     0,    57,    53,    57,    56,    54,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,    -1,
      -1,   161,   162,    -1,    -1,    -1,    -1,   208,    -1,   169,
     211,    -1,   172,   173,   215,   175,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
     190,    16,    17,    18,    19,    -1,    21,    22,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    31,    32,    -1,    34,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    50,    51,    -1,    53,    -1,
      -1,    -1,    57,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,    19,
      -1,    21,    22,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    31,    32,    -1,    34,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      50,    51,    -1,    53,    10,    11,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    10,    11,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
       3,     4,     5,    49,    50,    -1,    38,    39,    40,    41,
      42,    43,    44,    -1,    60,    18,    19,    49,    50,    22,
      -1,    -1,    25,    26,    -1,    57,    29,    -1,    31,    -1,
      10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,    42,
      20,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    10,    11,    12,    13,    14,    56,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      49,    50,    10,    11,    12,    13,    14,    56,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    50,    10,    11,    12,    13,    14,    56,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    10,    11,    12,    13,    14,    56,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    49,    50,    10,    11,    12,    13,    14,
      56,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    56,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    38,    39,    40,    41,    42,    43,
      44,    11,    12,    13,    14,    49,    50,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
      50,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50
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

case 4:
#line 91 "grammar.y"
{ sxp_new_class (parse_info, yyvsp[0].id, 0); }
    break;
case 6:
#line 92 "grammar.y"
{ sxp_new_class (parse_info, yyvsp[-2].id, yyvsp[0].id); }
    break;
case 10:
#line 99 "grammar.y"
{ sxp_add_method (parse_info->classes, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
    break;
case 11:
#line 100 "grammar.y"
{ sxp_add_static_method (parse_info->classes, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
    break;
case 12:
#line 101 "grammar.y"
{ 
		if (parse_info->classes->members == NULL) {
			parse_info->classes->members = (SX_ARRAY *)sx_new_array (parse_info->system, 0, NULL);
		}
		sx_append (parse_info->system, (SX_VALUE *)parse_info->classes->members, sx_new_num (yyvsp[-1].id));
	}
    break;
case 13:
#line 109 "grammar.y"
{ sxp_new_func (parse_info, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
    break;
case 14:
#line 112 "grammar.y"
{ yyval.node = NULL; }
    break;
case 15:
#line 113 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 16:
#line 116 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 17:
#line 117 "grammar.y"
{ yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;
case 18:
#line 120 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 19:
#line 121 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 20:
#line 122 "grammar.y"
{ yyval.node = sxp_new_if (parse_info, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;
case 21:
#line 123 "grammar.y"
{ yyval.node = sxp_new_if (parse_info, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 22:
#line 124 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_WD); }
    break;
case 23:
#line 125 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_UD); }
    break;
case 24:
#line 126 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DW); }
    break;
case 25:
#line 127 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DU); }
    break;
case 26:
#line 129 "grammar.y"
{ yyval.node = sxp_new_try (parse_info, yyvsp[-4].value, yyvsp[-8].node, yyvsp[-1].node); }
    break;
case 27:
#line 131 "grammar.y"
{ yyval.node = sxp_new_for (parse_info, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 28:
#line 132 "grammar.y"
{ yyval.node = sxp_new_cfor (parse_info, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 29:
#line 134 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 30:
#line 137 "grammar.y"
{ yyval.node = NULL; }
    break;
case 31:
#line 138 "grammar.y"
{ yyval.node = sxp_new_stmt (parse_info, yyvsp[0].node); }
    break;
case 32:
#line 141 "grammar.y"
{ yyval.node = sxp_new_retr (parse_info, yyvsp[0].node); }
    break;
case 33:
#line 142 "grammar.y"
{ yyval.node = sxp_new_retr (parse_info, NULL); }
    break;
case 34:
#line 143 "grammar.y"
{ yyval.node = sxp_new_brak (parse_info); }
    break;
case 35:
#line 144 "grammar.y"
{ yyval.node = sxp_new_cont (parse_info); }
    break;
case 36:
#line 145 "grammar.y"
{ yyval.node = sxp_new_rais (parse_info, yyvsp[0].id, NULL); }
    break;
case 37:
#line 146 "grammar.y"
{ yyval.node = sxp_new_rais (parse_info, yyvsp[-1].id, yyvsp[0].node); }
    break;
case 38:
#line 149 "grammar.y"
{ yyval.node = NULL; }
    break;
case 39:
#line 150 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 40:
#line 151 "grammar.y"
{ yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;
case 41:
#line 154 "grammar.y"
{ yyval.args.args = NULL; yyval.args.varg = 0; }
    break;
case 42:
#line 155 "grammar.y"
{ yyval.args.args = yyvsp[0].value; yyval.args.varg = 0; }
    break;
case 43:
#line 156 "grammar.y"
{ yyval.args.args = yyvsp[-3].value; yyval.args.varg = yyvsp[0].id; }
    break;
case 44:
#line 157 "grammar.y"
{ yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;
case 45:
#line 160 "grammar.y"
{ yyval.value = sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num (yyvsp[0].id)); }
    break;
case 46:
#line 161 "grammar.y"
{ yyval.value = sx_append (parse_info->system, yyvsp[-2].value, sx_new_num (yyvsp[0].id)); }
    break;
case 47:
#line 164 "grammar.y"
{ yyval.value = NULL; }
    break;
case 48:
#line 165 "grammar.y"
{ yyval.value = sx_append (parse_info->system, sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num (yyvsp[-1].id)), sx_new_num (yyvsp[0].id)); }
    break;
case 49:
#line 166 "grammar.y"
{ yyval.value = sx_append (parse_info->system, sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num (yyvsp[-1].id)), sx_new_num (yyvsp[0].id)); }
    break;
case 50:
#line 169 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 51:
#line 170 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 52:
#line 171 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 53:
#line 172 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 54:
#line 173 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 55:
#line 175 "grammar.y"
{ yyval.node = sxp_new_nega (parse_info, yyvsp[0].node); }
    break;
case 56:
#line 177 "grammar.y"
{ yyval.node = sxp_new_not (parse_info, yyvsp[0].node); }
    break;
case 57:
#line 178 "grammar.y"
{ yyval.node = sxp_new_and (parse_info, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 58:
#line 179 "grammar.y"
{ yyval.node = sxp_new_or (parse_info, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 59:
#line 181 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 60:
#line 182 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 61:
#line 183 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 62:
#line 184 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 63:
#line 185 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 64:
#line 186 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 65:
#line 188 "grammar.y"
{ yyval.node = sxp_new_assi (parse_info, yyvsp[-2].id, SX_SCOPE_DEF, yyvsp[0].node); }
    break;
case 66:
#line 189 "grammar.y"
{ yyval.node = sxp_new_assi (parse_info, yyvsp[-2].id, SX_SCOPE_LOCAL, yyvsp[0].node); }
    break;
case 67:
#line 190 "grammar.y"
{ yyval.node = sxp_new_assi (parse_info, yyvsp[-2].id, SX_SCOPE_GLOBAL, yyvsp[0].node); }
    break;
case 68:
#line 191 "grammar.y"
{ yyval.node = sxp_new_set (parse_info, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;
case 69:
#line 192 "grammar.y"
{ yyval.node = sxp_new_setm (parse_info, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 70:
#line 194 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 71:
#line 195 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[-2].id, sxp_new_nega (parse_info, yyvsp[0].node)); }
    break;
case 72:
#line 196 "grammar.y"
{ yyval.node = sxp_new_poic (parse_info, yyvsp[-1].id, sxp_new_data (parse_info, sx_new_num (1))); }
    break;
case 73:
#line 197 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[0].id, sxp_new_data (parse_info, sx_new_num (1))); }
    break;
case 74:
#line 198 "grammar.y"
{ yyval.node = sxp_new_poic (parse_info, yyvsp[-1].id, sxp_new_data (parse_info, sx_new_num (-1))); }
    break;
case 75:
#line 199 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[0].id, sxp_new_data (parse_info, sx_new_num (-1))); }
    break;
case 76:
#line 201 "grammar.y"
{ yyval.node = sxp_new_isa (parse_info, yyvsp[-2].node, yyvsp[0].id); }
    break;
case 77:
#line 202 "grammar.y"
{ yyval.node = sxp_new_call (parse_info, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 78:
#line 203 "grammar.y"
{ yyval.node = sxp_new_supr (parse_info, yyvsp[-1].node); }
    break;
case 79:
#line 205 "grammar.y"
{ yyval.node = sxp_new_smet (parse_info, yyvsp[-5].id, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 80:
#line 206 "grammar.y"
{ yyval.node = sxp_new_meth (parse_info, yyvsp[-5].node, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 81:
#line 207 "grammar.y"
{ yyval.node = sxp_new_memb (parse_info, yyvsp[-2].node, yyvsp[0].id); }
    break;
case 82:
#line 208 "grammar.y"
{ yyval.node = sxp_new_newc (parse_info, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 83:
#line 210 "grammar.y"
{ yyval.node = sxp_new_indx (parse_info, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 84:
#line 211 "grammar.y"
{ yyval.node = sxp_new_arry (parse_info, yyvsp[-1].node); }
    break;
case 85:
#line 213 "grammar.y"
{ yyval.node = sxp_new_data (parse_info, yyvsp[0].value); }
    break;
case 86:
#line 215 "grammar.y"
{ yyval.node = sxp_new_name (parse_info, yyvsp[0].id, SX_SCOPE_DEF); }
    break;
case 87:
#line 216 "grammar.y"
{ yyval.node = sxp_new_name (parse_info, yyvsp[0].id, SX_SCOPE_LOCAL); }
    break;
case 88:
#line 217 "grammar.y"
{ yyval.node = sxp_new_name (parse_info, yyvsp[0].id, SX_SCOPE_GLOBAL); }
    break;
case 89:
#line 221 "grammar.y"
{ yyval.value = yyvsp[0].value;  }
    break;
case 90:
#line 222 "grammar.y"
{ yyval.value = yyvsp[0].value; }
    break;
case 91:
#line 223 "grammar.y"
{ yyval.value = NULL; }
    break;
case 92:
#line 226 "grammar.y"
{ yyval.id = sx_name_to_id (yyvsp[0].name); }
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
#line 229 "grammar.y"


void
parser_add_line (void) {
	++ parse_info->line;
}

int
sxerror (const char *str) {
	if (parse_info->system->error_hook != NULL) {
		char buffer[512];
		snprintf (buffer, 512, "File %s, line %d: %s", parse_info->file ? SX_TOSTRING (parse_info->file)->str : "<input>", parse_info->line, str);
		parse_info->system->error_hook (buffer);
	} else {
		fprintf (stderr, "Scriptix Error: File %s, line %d: %s\n", parse_info->file ? SX_TOSTRING (parse_info->file)->str : "<input>", parse_info->line, str);
	}
	return 1;
}

int
sxwrap (void) {
	return 1;
}

int
sxp_load_file (SX_SYSTEM *system, const char *file) {
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

	parse_info = sxp_new_info (system);
	if (parse_info == NULL) {
		if (file != NULL)
			fclose (sxin);
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}
	if (file != NULL)
		parse_info->file = sx_new_str (system, file);

	sx_parser_inbuf = NULL;
	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (!ret) {
		ret = sxp_compile (parse_info);
	}

	sxp_del_info (parse_info);

	sx_run_gc (system);

	return ret;
}

int
sxp_load_string (SX_SYSTEM *system, const char *buf) {
	int ret, flags;

	if (buf == NULL) {
		return 1;
	}

	parse_info = sxp_new_info (system);
	if (parse_info == NULL) {
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}

	sxin = NULL;
	sx_parser_inbuf = buf;
	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	system->flags = flags;

	if (!ret) {
		ret = sxp_compile (parse_info);
	}

	sxp_del_info (parse_info);

	sx_run_gc (system);

	return ret;
}
