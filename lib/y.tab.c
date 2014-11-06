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
# define	TADDASSIGN	276
# define	TSUBASSIGN	277
# define	TINCREMENT	278
# define	TDECREMENT	279
# define	TSTATIC	280
# define	TCLASS	281
# define	TNEW	282
# define	TUNTIL	283
# define	TNIL	284
# define	TRAISE	285
# define	TRESCUE	286
# define	TTRY	287
# define	TIN	288
# define	TFOR	289
# define	TISA	290
# define	TLENGTH	291
# define	TRANGE	292
# define	CUNARY	293

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

	extern FILE *sxin;
	int sxparse (void);

	extern const char *sx_parser_inbuf;

#line 54 "grammar.y"
#ifndef YYSTYPE
typedef union {
	SXP_NODE *node;
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	sx_name_id id;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		210
#define	YYFLAG		-32768
#define	YYNTBASE	59

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 293 ? yytranslate[x] : 76)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    46,     2,     2,     2,     2,     2,     2,
      50,    55,    42,    40,    57,    41,    48,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,    56,
      38,    36,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    58,    51,     2,     2,     2,     2,     2,
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
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      39,    44,    45,    47
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     7,     8,    15,    16,    25,    27,
      30,    38,    47,    55,    56,    58,    60,    63,    66,    69,
      75,    83,    89,    95,   103,   111,   123,   130,   140,   144,
     145,   147,   150,   152,   154,   156,   159,   163,   164,   166,
     170,   171,   173,   177,   178,   181,   186,   190,   194,   198,
     202,   206,   209,   212,   216,   220,   224,   228,   232,   236,
     240,   244,   248,   253,   258,   265,   271,   275,   279,   282,
     285,   288,   291,   295,   300,   307,   314,   318,   324,   329,
     333,   335,   337,   339,   341,   344,   347
};
static const short yyrhs[] =
{
      -1,    59,    60,     0,    59,    65,     0,     0,    27,    75,
      61,    52,    63,    53,     0,     0,    27,    75,    54,    75,
      62,    52,    63,    53,     0,    64,     0,    63,    64,     0,
      75,    50,    72,    55,    52,    66,    53,     0,    26,    75,
      50,    72,    55,    52,    66,    53,     0,    75,    50,    72,
      55,    52,    66,    53,     0,     0,    67,     0,    68,     0,
      67,    68,     0,    69,    56,     0,    70,    56,     0,     6,
      50,    74,    55,    68,     0,     6,    50,    74,    55,    68,
       7,    68,     0,     8,    50,    74,    55,    68,     0,    29,
      50,    74,    55,    68,     0,     9,    68,     8,    50,    74,
      55,    56,     0,     9,    68,    29,    50,    74,    55,    56,
       0,    33,    52,    66,    53,    32,    50,    73,    55,    52,
      66,    53,     0,    35,    75,    34,    74,     9,    68,     0,
      35,    50,    69,    56,    74,    56,    69,    55,    68,     0,
      52,    66,    53,     0,     0,    74,     0,    16,    74,     0,
      16,     0,    17,     0,    21,     0,    31,    75,     0,    31,
      75,    74,     0,     0,    74,     0,    71,    57,    74,     0,
       0,    75,     0,    72,    57,    75,     0,     0,    75,    75,
       0,    73,    57,    75,    75,     0,    74,    40,    74,     0,
      74,    41,    74,     0,    74,    42,    74,     0,    74,    43,
      74,     0,    50,    74,    55,     0,    41,    74,     0,    46,
      74,     0,    74,    10,    74,     0,    74,    11,    74,     0,
      74,    37,    74,     0,    74,    38,    74,     0,    74,    14,
      74,     0,    74,    12,    74,     0,    74,    13,    74,     0,
      74,    20,    74,     0,    75,    36,    74,     0,    18,    75,
      36,    74,     0,    19,    75,    36,    74,     0,    74,    49,
      74,    58,    36,    74,     0,    74,    48,    75,    36,    74,
       0,    75,    22,    74,     0,    75,    23,    74,     0,    75,
      24,     0,    24,    75,     0,    75,    25,     0,    25,    75,
       0,    74,    39,    75,     0,    75,    50,    71,    55,     0,
      75,    15,    75,    50,    71,    55,     0,    74,    48,    75,
      50,    71,    55,     0,    74,    48,    75,     0,    28,    75,
      50,    71,    55,     0,    74,    49,    74,    58,     0,    49,
      71,    58,     0,     3,     0,     4,     0,    30,     0,    75,
       0,    18,    75,     0,    19,    75,     0,     5,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    89,    90,    91,    94,    94,    95,    95,    98,    99,
     102,   103,   106,   109,   110,   113,   114,   117,   118,   119,
     120,   121,   122,   123,   124,   126,   128,   129,   131,   134,
     135,   138,   139,   140,   141,   142,   143,   146,   147,   148,
     151,   152,   153,   156,   157,   158,   161,   162,   163,   164,
     165,   167,   169,   170,   171,   173,   174,   175,   176,   177,
     178,   180,   181,   182,   183,   184,   186,   187,   188,   189,
     190,   191,   193,   194,   196,   197,   198,   199,   201,   202,
     204,   205,   206,   208,   209,   210,   213
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "TNUM", "TSTR", "TNAME", "TIF", "TELSE", 
  "TWHILE", "TDO", "TAND", "TOR", "TGTE", "TLTE", "TNE", "TSTATMETHOD", 
  "TRETURN", "TBREAK", "TLOCAL", "TGLOBAL", "TEQUALS", "TCONTINUE", 
  "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", "TSTATIC", 
  "TCLASS", "TNEW", "TUNTIL", "TNIL", "TRAISE", "TRESCUE", "TTRY", "TIN", 
  "TFOR", "'='", "'>'", "'<'", "TISA", "'+'", "'-'", "'*'", "'/'", 
  "TLENGTH", "TRANGE", "'!'", "CUNARY", "'.'", "'['", "'('", "'^'", "'{'", 
  "'}'", "':'", "')'", "';'", "','", "']'", "program", "class", "@1", 
  "@2", "cblock", "cstmt", "function", "block", "stmts", "stmt", "node", 
  "control", "args", "arg_names", "errors", "expr", "name", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    59,    59,    59,    61,    60,    62,    60,    63,    63,
      64,    64,    65,    66,    66,    67,    67,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    69,
      69,    70,    70,    70,    70,    70,    70,    71,    71,    71,
      72,    72,    72,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     2,     0,     6,     0,     8,     1,     2,
       7,     8,     7,     0,     1,     1,     2,     2,     2,     5,
       7,     5,     5,     7,     7,    11,     6,     9,     3,     0,
       1,     2,     1,     1,     1,     2,     3,     0,     1,     3,
       0,     1,     3,     0,     2,     4,     3,     3,     3,     3,
       3,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     6,     5,     3,     3,     2,     2,
       2,     2,     3,     4,     6,     6,     3,     5,     4,     3,
       1,     1,     1,     1,     2,     2,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,    86,     0,     2,     3,     0,     4,    40,     0,
       0,     0,    41,     6,     0,     0,     0,     0,     0,     0,
       8,     0,    13,    42,     0,     0,     5,     9,    40,    80,
      81,     0,     0,    29,    32,    33,     0,     0,    34,     0,
       0,     0,     0,    82,     0,     0,     0,     0,     0,    37,
       0,    13,     0,    14,    15,     0,     0,    30,    83,     0,
      40,     0,     0,     0,     0,    31,    84,    85,    69,    71,
       0,     0,    35,    13,    29,     0,    51,    52,     0,    38,
       0,     0,    12,    16,    17,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    68,    70,     0,    37,     7,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,    36,
       0,     0,     0,     0,    79,    50,    28,    53,    54,    58,
      59,    57,    60,    55,    56,    72,    46,    47,    48,    49,
      76,     0,     0,    66,    67,    61,     0,     0,    13,    29,
      29,     0,     0,    62,    63,     0,    29,     0,     0,     0,
      39,     0,    37,    78,    37,    73,    13,     0,    19,    21,
       0,     0,    77,    22,     0,     0,    29,    65,     0,     0,
       0,     0,    10,    29,     0,     0,    43,    29,    26,    75,
      64,    74,    11,    20,    23,    24,     0,     0,     0,     0,
       0,    44,    29,    13,     0,    27,     0,    45,    25,     0,
       0
};

static const short yydefgoto[] =
{
       1,     4,    10,    17,    19,    20,     5,    52,    53,    54,
      55,    56,    78,    11,   196,    57,    58
};

static const short yypact[] =
{
  -32768,    14,-32768,    27,-32768,-32768,   -13,   -10,    27,    27,
      -3,   -33,-32768,-32768,    20,    10,    27,    24,    27,     4,
  -32768,    18,   255,-32768,    20,    25,-32768,-32768,    27,-32768,
  -32768,    34,    37,    61,   118,-32768,    27,    27,-32768,    27,
      27,    27,    38,-32768,    27,    47,     0,   118,   118,   118,
     118,   255,    55,   255,-32768,    53,    59,   615,   363,     7,
      27,    16,   118,   118,    23,   615,    84,    94,-32768,-32768,
      81,   118,   118,   255,   118,    98,   -20,   -20,    -2,   615,
     355,    80,-32768,-32768,-32768,-32768,   118,   118,   118,   118,
     118,   118,   118,   118,    27,   118,   118,   118,   118,    27,
     118,    27,   118,   118,-32768,-32768,   118,   118,-32768,    17,
      93,   395,   435,    97,    99,   118,   118,   118,   475,   615,
     102,    96,   118,   118,-32768,-32768,-32768,   198,   647,   181,
     181,    86,    86,   181,   181,-32768,     5,     5,   -20,   -20,
     -16,   302,   100,   615,   615,   615,    26,   105,   255,    61,
      61,   118,   118,   615,   615,    40,    61,   126,   118,   602,
     615,   118,   118,   124,   118,-32768,   255,   108,   158,-32768,
     515,   555,-32768,-32768,   116,   315,    61,   615,    48,   118,
      49,   119,-32768,    61,   113,   115,    27,   118,-32768,-32768,
     615,-32768,-32768,-32768,-32768,-32768,    57,    27,   120,   121,
      27,-32768,    61,   255,    27,-32768,   123,-32768,-32768,   174,
  -32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,   166,    -8,-32768,   -47,-32768,   -32,
     -71,-32768,  -101,   -18,-32768,    91,    -1
};


#define	YYLAST		696


static const short yytable[] =
{
       6,    64,     7,   121,    81,     2,   146,    12,    13,     2,
      61,    27,     2,    21,   209,    23,   155,    25,    21,     2,
     161,    83,    15,    21,    16,     2,   120,    12,    99,   100,
      18,   113,     2,    18,   162,    66,    67,     8,    68,    69,
      70,     3,   109,    72,     9,    75,    18,    97,    98,    14,
      74,    27,   114,    99,   100,   123,   124,    26,    21,    12,
     108,   178,    22,   180,    29,    30,     2,    31,    28,    32,
      33,   110,   147,    16,    16,    60,    24,    34,    35,    36,
      37,   165,    38,   123,    62,    39,    40,    63,    71,    41,
      42,    43,    44,   135,    45,   172,    46,   123,   140,    73,
     142,   167,    47,   189,   191,   123,   123,    48,    82,    84,
      49,    50,   199,    51,   200,    85,   198,   168,   169,   181,
     115,    29,    30,     2,   173,    65,    95,    96,    97,    98,
     116,   117,   122,   126,    99,   100,    36,    37,    76,    77,
      79,    80,    39,    40,   188,   148,    41,   151,    43,   152,
     164,   193,   158,   111,   112,   157,   206,   166,   174,    47,
     179,   182,   118,   119,    48,   183,   186,    49,    50,   194,
     205,   195,   192,   203,   210,   202,   208,   127,   128,   129,
     130,   131,   132,   133,   134,   197,   136,   137,   138,   139,
      59,   141,     0,   143,   144,    90,   201,   145,    79,   204,
       0,    91,     0,   207,     0,     0,   153,   154,    79,    87,
      88,    89,    90,   159,   160,     0,     0,     0,    91,     0,
      94,    95,    96,    97,    98,     0,     0,     0,     0,    99,
     100,     0,     0,     0,     0,    92,    93,    94,    95,    96,
      97,    98,   170,   171,     0,     0,    99,   100,     0,   175,
       0,     0,   177,    79,     0,    79,     0,     0,    29,    30,
       2,    31,     0,    32,    33,     0,     0,     0,     0,     0,
     190,    34,    35,    36,    37,     0,    38,     0,     0,    39,
      40,     0,     0,    41,    42,    43,    44,     0,    45,     0,
      46,     0,     0,     0,     0,     0,    47,     0,     0,     0,
       0,    48,     0,     0,    49,    50,     0,    51,     0,     0,
       0,   -29,    86,    87,    88,    89,    90,     0,     0,     0,
       0,     0,    91,     0,     0,    86,    87,    88,    89,    90,
       0,     0,     0,     0,     0,    91,     0,     0,     0,    92,
      93,    94,    95,    96,    97,    98,     0,     0,     0,     0,
      99,   100,    92,    93,    94,    95,    96,    97,    98,     0,
     163,     0,     0,    99,   100,    86,    87,    88,    89,    90,
       0,   187,     0,     0,     0,    91,     0,     0,   101,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,   106,
       0,     0,     0,    99,   100,    86,    87,    88,    89,    90,
     125,     0,     0,   107,     0,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,    99,   100,    86,    87,    88,    89,    90,
     149,     0,     0,     0,     0,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,    99,   100,    86,    87,    88,    89,    90,
     150,     0,     0,     0,     0,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,    99,   100,    86,    87,    88,    89,    90,
     156,     0,     0,     0,     0,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,    99,   100,    86,    87,    88,    89,    90,
     184,     0,     0,     0,     0,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,    99,   100,     0,     0,     0,     0,     0,
     185,   176,    86,    87,    88,    89,    90,     0,     0,     0,
       0,     0,    91,     0,     0,    86,    87,    88,    89,    90,
       0,     0,     0,     0,     0,    91,     0,     0,     0,    92,
      93,    94,    95,    96,    97,    98,     0,     0,     0,     0,
      99,   100,    92,    93,    94,    95,    96,    97,    98,    88,
      89,    90,     0,    99,   100,     0,     0,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,    99,   100
};

static const short yycheck[] =
{
       1,    33,     3,    74,    51,     5,   107,     8,     9,     5,
      28,    19,     5,    14,     0,    16,   117,    18,    19,     5,
      36,    53,    55,    24,    57,     5,    73,    28,    48,    49,
      26,     8,     5,    26,    50,    36,    37,    50,    39,    40,
      41,    27,    60,    44,    54,    46,    26,    42,    43,    52,
      50,    59,    29,    48,    49,    57,    58,    53,    59,    60,
      53,   162,    52,   164,     3,     4,     5,     6,    50,     8,
       9,    55,    55,    57,    57,    50,    52,    16,    17,    18,
      19,    55,    21,    57,    50,    24,    25,    50,    50,    28,
      29,    30,    31,    94,    33,    55,    35,    57,    99,    52,
     101,   148,    41,    55,    55,    57,    57,    46,    53,    56,
      49,    50,    55,    52,    57,    56,   187,   149,   150,   166,
      36,     3,     4,     5,   156,    34,    40,    41,    42,    43,
      36,    50,    34,    53,    48,    49,    18,    19,    47,    48,
      49,    50,    24,    25,   176,    52,    28,    50,    30,    50,
      50,   183,    56,    62,    63,    53,   203,    52,    32,    41,
      36,    53,    71,    72,    46,     7,    50,    49,    50,    56,
     202,    56,    53,    52,     0,    55,    53,    86,    87,    88,
      89,    90,    91,    92,    93,   186,    95,    96,    97,    98,
      24,   100,    -1,   102,   103,    14,   197,   106,   107,   200,
      -1,    20,    -1,   204,    -1,    -1,   115,   116,   117,    11,
      12,    13,    14,   122,   123,    -1,    -1,    -1,    20,    -1,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    48,
      49,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,    43,   151,   152,    -1,    -1,    48,    49,    -1,   158,
      -1,    -1,   161,   162,    -1,   164,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,
     179,    16,    17,    18,    19,    -1,    21,    -1,    -1,    24,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    33,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    -1,    52,    -1,    -1,
      -1,    56,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    37,    38,    39,    40,    41,    42,    43,    -1,
      58,    -1,    -1,    48,    49,    10,    11,    12,    13,    14,
      -1,    56,    -1,    -1,    -1,    20,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    36,
      -1,    -1,    -1,    48,    49,    10,    11,    12,    13,    14,
      55,    -1,    -1,    50,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    48,    49,    10,    11,    12,    13,    14,
      55,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    48,    49,    10,    11,    12,    13,    14,
      55,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    48,    49,    10,    11,    12,    13,    14,
      55,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    48,    49,    10,    11,    12,    13,    14,
      55,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,    -1,
      55,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    37,    38,    39,    40,    41,    42,    43,    12,
      13,    14,    -1,    48,    49,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49
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
#line 94 "grammar.y"
{ sxp_new_class (parse_info, yyvsp[0].id, 0); }
    break;
case 6:
#line 95 "grammar.y"
{ sxp_new_class (parse_info, yyvsp[-2].id, yyvsp[0].id); }
    break;
case 10:
#line 102 "grammar.y"
{ sxp_add_method (parse_info->classes, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].value, yyvsp[-1].node); }
    break;
case 11:
#line 103 "grammar.y"
{ sxp_add_static_method (parse_info->classes, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].value, yyvsp[-1].node); }
    break;
case 12:
#line 106 "grammar.y"
{ sxp_new_func (parse_info, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].value, yyvsp[-1].node); }
    break;
case 13:
#line 109 "grammar.y"
{ yyval.node = NULL; }
    break;
case 14:
#line 110 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 15:
#line 113 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 16:
#line 114 "grammar.y"
{ yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;
case 17:
#line 117 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 18:
#line 118 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 19:
#line 119 "grammar.y"
{ yyval.node = sxp_new_if (parse_info, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;
case 20:
#line 120 "grammar.y"
{ yyval.node = sxp_new_if (parse_info, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 21:
#line 121 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_WD); }
    break;
case 22:
#line 122 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_UD); }
    break;
case 23:
#line 123 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DW); }
    break;
case 24:
#line 124 "grammar.y"
{ yyval.node = sxp_new_whil (parse_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DU); }
    break;
case 25:
#line 126 "grammar.y"
{ yyval.node = sxp_new_try (parse_info, yyvsp[-4].value, yyvsp[-8].node, yyvsp[-1].node); }
    break;
case 26:
#line 128 "grammar.y"
{ yyval.node = sxp_new_for (parse_info, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 27:
#line 129 "grammar.y"
{ yyval.node = sxp_new_cfor (parse_info, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 28:
#line 131 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 29:
#line 134 "grammar.y"
{ yyval.node = NULL; }
    break;
case 30:
#line 135 "grammar.y"
{ yyval.node = sxp_new_stmt (parse_info, yyvsp[0].node); }
    break;
case 31:
#line 138 "grammar.y"
{ yyval.node = sxp_new_retr (parse_info, yyvsp[0].node); }
    break;
case 32:
#line 139 "grammar.y"
{ yyval.node = sxp_new_retr (parse_info, NULL); }
    break;
case 33:
#line 140 "grammar.y"
{ yyval.node = sxp_new_brak (parse_info); }
    break;
case 34:
#line 141 "grammar.y"
{ yyval.node = sxp_new_cont (parse_info); }
    break;
case 35:
#line 142 "grammar.y"
{ yyval.node = sxp_new_rais (parse_info, yyvsp[0].id, NULL); }
    break;
case 36:
#line 143 "grammar.y"
{ yyval.node = sxp_new_rais (parse_info, yyvsp[-1].id, yyvsp[0].node); }
    break;
case 37:
#line 146 "grammar.y"
{ yyval.node = NULL; }
    break;
case 38:
#line 147 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 39:
#line 148 "grammar.y"
{ yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;
case 40:
#line 151 "grammar.y"
{ yyval.value = NULL; }
    break;
case 41:
#line 152 "grammar.y"
{ yyval.value = sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num (yyvsp[0].id)); }
    break;
case 42:
#line 153 "grammar.y"
{ yyval.value = sx_append (parse_info->system, yyvsp[-2].value, sx_new_num (yyvsp[0].id)); }
    break;
case 43:
#line 156 "grammar.y"
{ yyval.value = NULL; }
    break;
case 44:
#line 157 "grammar.y"
{ yyval.value = sx_append (parse_info->system, sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num (yyvsp[-1].id)), sx_new_num (yyvsp[0].id)); }
    break;
case 45:
#line 158 "grammar.y"
{ yyval.value = sx_append (parse_info->system, sx_append (parse_info->system, sx_new_array (parse_info->system, 0, NULL), sx_new_num (yyvsp[-1].id)), sx_new_num (yyvsp[0].id)); }
    break;
case 46:
#line 161 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 47:
#line 162 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 48:
#line 163 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 49:
#line 164 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 50:
#line 165 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 51:
#line 167 "grammar.y"
{ yyval.node = sxp_new_nega (parse_info, yyvsp[0].node); }
    break;
case 52:
#line 169 "grammar.y"
{ yyval.node = sxp_new_not (parse_info, yyvsp[0].node); }
    break;
case 53:
#line 170 "grammar.y"
{ yyval.node = sxp_new_and (parse_info, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 54:
#line 171 "grammar.y"
{ yyval.node = sxp_new_or (parse_info, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 55:
#line 173 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 56:
#line 174 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 57:
#line 175 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 58:
#line 176 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 59:
#line 177 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 60:
#line 178 "grammar.y"
{ yyval.node = sxp_new_math (parse_info, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 61:
#line 180 "grammar.y"
{ yyval.node = sxp_new_assi (parse_info, yyvsp[-2].id, SX_SCOPE_DEF, yyvsp[0].node); }
    break;
case 62:
#line 181 "grammar.y"
{ yyval.node = sxp_new_assi (parse_info, yyvsp[-2].id, SX_SCOPE_LOCAL, yyvsp[0].node); }
    break;
case 63:
#line 182 "grammar.y"
{ yyval.node = sxp_new_assi (parse_info, yyvsp[-2].id, SX_SCOPE_GLOBAL, yyvsp[0].node); }
    break;
case 64:
#line 183 "grammar.y"
{ yyval.node = sxp_new_set (parse_info, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;
case 65:
#line 184 "grammar.y"
{ yyval.node = sxp_new_setm (parse_info, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 66:
#line 186 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 67:
#line 187 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[-2].id, sxp_new_nega (parse_info, yyvsp[0].node)); }
    break;
case 68:
#line 188 "grammar.y"
{ yyval.node = sxp_new_poic (parse_info, yyvsp[-1].id, sxp_new_data (parse_info, sx_new_num (1))); }
    break;
case 69:
#line 189 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[0].id, sxp_new_data (parse_info, sx_new_num (1))); }
    break;
case 70:
#line 190 "grammar.y"
{ yyval.node = sxp_new_poic (parse_info, yyvsp[-1].id, sxp_new_data (parse_info, sx_new_num (-1))); }
    break;
case 71:
#line 191 "grammar.y"
{ yyval.node = sxp_new_pric (parse_info, yyvsp[0].id, sxp_new_data (parse_info, sx_new_num (-1))); }
    break;
case 72:
#line 193 "grammar.y"
{ yyval.node = sxp_new_isa (parse_info, yyvsp[-2].node, yyvsp[0].id); }
    break;
case 73:
#line 194 "grammar.y"
{ yyval.node = sxp_new_call (parse_info, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 74:
#line 196 "grammar.y"
{ yyval.node = sxp_new_smet (parse_info, yyvsp[-5].id, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 75:
#line 197 "grammar.y"
{ yyval.node = sxp_new_meth (parse_info, yyvsp[-5].node, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 76:
#line 198 "grammar.y"
{ yyval.node = sxp_new_memb (parse_info, yyvsp[-2].node, yyvsp[0].id); }
    break;
case 77:
#line 199 "grammar.y"
{ yyval.node = sxp_new_newc (parse_info, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 78:
#line 201 "grammar.y"
{ yyval.node = sxp_new_indx (parse_info, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 79:
#line 202 "grammar.y"
{ yyval.node = sxp_new_arry (parse_info, yyvsp[-1].node); }
    break;
case 80:
#line 204 "grammar.y"
{ yyval.node = sxp_new_data (parse_info, yyvsp[0].value);  }
    break;
case 81:
#line 205 "grammar.y"
{ yyval.node = sxp_new_data (parse_info, yyvsp[0].value); }
    break;
case 82:
#line 206 "grammar.y"
{ yyval.node = sxp_new_data (parse_info, NULL); }
    break;
case 83:
#line 208 "grammar.y"
{ yyval.node = sxp_new_name (parse_info, yyvsp[0].id, SX_SCOPE_DEF); }
    break;
case 84:
#line 209 "grammar.y"
{ yyval.node = sxp_new_name (parse_info, yyvsp[0].id, SX_SCOPE_LOCAL); }
    break;
case 85:
#line 210 "grammar.y"
{ yyval.node = sxp_new_name (parse_info, yyvsp[0].id, SX_SCOPE_GLOBAL); }
    break;
case 86:
#line 213 "grammar.y"
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
#line 216 "grammar.y"


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
sx_load_file (SX_SYSTEM *system, const char *file) {
	int ret, flags;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return 0;
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
sx_load_string (SX_SYSTEM *system, const char *buf) {
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
