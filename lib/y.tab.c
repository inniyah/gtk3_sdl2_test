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
# define	TSEP	260
# define	TIF	261
# define	TTHEN	262
# define	TELSE	263
# define	TEND	264
# define	TWHILE	265
# define	TDO	266
# define	TAND	267
# define	TOR	268
# define	TGTE	269
# define	TLTE	270
# define	TNE	271
# define	TRETURN	272
# define	TFUNC	273
# define	TBREAK	274
# define	TBLOCK	275
# define	TLOCAL	276
# define	TGLOBAL	277
# define	TEQUALS	278
# define	TRANGE	279
# define	TSTEP	280
# define	TADDASSIGN	281
# define	TSUBASSIGN	282
# define	TINCREMENT	283
# define	TDECREMENT	284
# define	TLENGTH	285
# define	TCLASS	286
# define	TNEW	287
# define	TUNTIL	288
# define	TNIL	289
# define	TRAISE	290
# define	TRESCUE	291
# define	TTRY	292
# define	TIN	293
# define	TFOR	294
# define	TMETHOD	295
# define	TISA	296
# define	CUNARY	297

#line 28 "grammar.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <errno.h>

	#include "scriptix.h"
	#include "system.h"

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int parser_stack_size = 0;
	int parser_stack_top = 0;
	SX_VALUE **parser_stack = NULL;

	SX_VALUE *parser_top (void);
	void parser_push (SX_VALUE *value);
	void parser_pop (void);

	SX_VALUE *append_to_array (SX_VALUE *array, SX_VALUE *value);

	__INLINE__ void parser_add_line (void);

	int sxerror (const char *);
	int sxlex (void);

	SX_SYSTEM *parse_system = NULL;
	SX_VALUE *parse_block = NULL;

	unsigned int parse_lineno = 1;
	extern FILE *sxin;
	int sxparse (void);

	SX_VALUE *temp_val;

	extern const char *sx_parser_inbuf;

	#define pushv(v) (sx_add_value (parse_system, parser_top (), (v)))
	#define pushn(o) (sx_add_stmt (parse_system, parser_top (), (o)))

#line 70 "grammar.y"
#ifndef YYSTYPE
typedef union {
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	unsigned int count;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		219
#define	YYFLAG		-32768
#define	YYNTBASE	62

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 297 ? yytranslate[x] : 94)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,     2,     2,     2,     2,     2,
      54,    56,    48,    46,    57,    47,    52,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,     2,
      44,    42,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    58,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      36,    37,    38,    39,    40,    41,    45,    51
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,     7,    10,    11,    13,    16,
      19,    23,    25,    26,    31,    33,    35,    37,    40,    42,
      44,    47,    48,    59,    60,    62,    66,    67,    68,    71,
      73,    77,    78,    81,    84,    89,    93,    97,   101,   105,
     109,   112,   115,   116,   121,   122,   127,   131,   135,   139,
     143,   147,   151,   155,   160,   167,   173,   177,   181,   184,
     187,   190,   193,   198,   202,   207,   213,   222,   230,   237,
     241,   244,   245,   252,   260,   265,   271,   279,   285,   293,
     294,   302,   308,   312,   313,   322,   323,   334,   337,   339,
     341,   344,   347,   351,   353,   357,   361,   363,   365,   369,
     371,   373,   376,   378,   380
};
static const short yyrhs[] =
{
      67,     0,     0,    64,    67,     0,     0,    66,    84,     0,
       0,    68,     0,    72,    68,     0,    68,    72,     0,    72,
      68,    72,     0,    70,     0,     0,    68,    72,    69,    70,
       0,    84,     0,     6,     0,    71,     0,    72,    71,     0,
      74,     0,    75,     0,    74,    75,     0,     0,    19,    92,
      54,    78,    56,    71,    63,    76,    10,    72,     0,     0,
      84,     0,    77,    57,    84,     0,     0,     0,    79,    80,
       0,     5,     0,    80,    57,     5,     0,     0,    82,    83,
       0,     5,     5,     0,    80,    57,     5,     5,     0,    84,
      46,    84,     0,    84,    47,    84,     0,    84,    48,    84,
       0,    84,    49,    84,     0,    54,    84,    56,     0,    47,
      84,     0,    50,    84,     0,     0,    84,    13,    85,    84,
       0,     0,    84,    14,    86,    84,     0,    84,    43,    84,
       0,    84,    44,    84,     0,    84,    17,    84,     0,    84,
      15,    84,     0,    84,    16,    84,     0,    84,    24,    84,
       0,    92,    42,    84,     0,    93,    92,    42,    84,     0,
      84,    53,    84,    58,    42,    84,     0,    84,    52,    92,
      42,    84,     0,    92,    27,    84,     0,    92,    28,    84,
       0,    92,    29,     0,    29,    92,     0,    92,    30,     0,
      30,    92,     0,    31,    54,    84,    56,     0,    84,    45,
      92,     0,    91,    54,    77,    56,     0,    84,    41,    54,
      77,    56,     0,    19,    92,    54,    78,    56,    71,    63,
      10,     0,    19,    54,    78,    56,    71,    63,    10,     0,
      84,    52,    92,    54,    77,    56,     0,    84,    52,    92,
       0,    33,    92,     0,     0,    32,    92,    72,    87,    73,
      10,     0,    32,    92,    59,    92,    72,    73,    10,     0,
      84,    53,    84,    58,     0,     7,    84,     8,    63,    10,
       0,     7,    84,     8,    63,     9,    63,    10,     0,    11,
      65,    12,    63,    10,     0,    38,    63,    37,    81,    71,
      63,    10,     0,     0,    38,    63,    37,    71,    88,    63,
      10,     0,    34,    65,    12,    63,    10,     0,    12,    63,
      10,     0,     0,    40,    92,    39,    84,    12,    89,    63,
      10,     0,     0,    40,    92,    39,    84,    26,     3,    90,
      12,    63,    10,     0,    18,    84,     0,    18,     0,    20,
       0,    20,    84,     0,    36,    92,     0,    36,    92,    84,
       0,    91,     0,    84,    25,    84,     0,    60,    77,    61,
       0,     3,     0,     4,     0,    21,    63,    10,     0,    35,
       0,    92,     0,    93,    92,     0,     5,     0,    22,     0,
      23,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   101,   104,   104,   107,   107,   110,   111,   112,   113,
     114,   117,   118,   118,   121,   124,   127,   128,   131,   134,
     135,   138,   138,   141,   142,   143,   146,   147,   147,   150,
     151,   154,   154,   157,   158,   161,   162,   163,   164,   165,
     166,   168,   169,   169,   170,   170,   172,   173,   174,   175,
     176,   177,   179,   180,   181,   182,   184,   185,   186,   187,
     188,   189,   191,   192,   194,   195,   196,   197,   199,   200,
     201,   202,   202,   203,   205,   207,   208,   209,   210,   211,
     211,   212,   213,   214,   214,   215,   215,   217,   218,   219,
     220,   221,   222,   224,   226,   227,   229,   230,   231,   232,
     235,   236,   239,   242,   243
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "TNUM", "TSTR", "TNAME", "TSEP", "TIF", 
  "TTHEN", "TELSE", "TEND", "TWHILE", "TDO", "TAND", "TOR", "TGTE", 
  "TLTE", "TNE", "TRETURN", "TFUNC", "TBREAK", "TBLOCK", "TLOCAL", 
  "TGLOBAL", "TEQUALS", "TRANGE", "TSTEP", "TADDASSIGN", "TSUBASSIGN", 
  "TINCREMENT", "TDECREMENT", "TLENGTH", "TCLASS", "TNEW", "TUNTIL", 
  "TNIL", "TRAISE", "TRESCUE", "TTRY", "TIN", "TFOR", "TMETHOD", "'='", 
  "'>'", "'<'", "TISA", "'+'", "'-'", "'*'", "'/'", "'!'", "CUNARY", 
  "'.'", "'['", "'('", "'^'", "')'", "','", "']'", "':'", "'{'", "'}'", 
  "program", "block", "@1", "oblock", "@2", "stmts", "stmt_list", "@3", 
  "stmt", "sep", "seps", "cblock", "cstmt_list", "cstmt", "@4", 
  "array_list", "args", "@5", "arg_list", "errors", "@6", "error_list", 
  "node", "@7", "@8", "@9", "@10", "@11", "@12", "lookup", "name", 
  "scope", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    62,    64,    63,    66,    65,    67,    67,    67,    67,
      67,    68,    69,    68,    70,    71,    72,    72,    73,    74,
      74,    76,    75,    77,    77,    77,    78,    79,    78,    80,
      80,    82,    81,    83,    83,    84,    84,    84,    84,    84,
      84,    84,    85,    84,    86,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    87,    84,    84,    84,    84,    84,    84,    84,    88,
      84,    84,    84,    89,    84,    90,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      91,    91,    92,    93,    93
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     0,     2,     0,     1,     2,     2,
       3,     1,     0,     4,     1,     1,     1,     2,     1,     1,
       2,     0,    10,     0,     1,     3,     0,     0,     2,     1,
       3,     0,     2,     2,     4,     3,     3,     3,     3,     3,
       2,     2,     0,     4,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     4,     6,     5,     3,     3,     2,     2,
       2,     2,     4,     3,     4,     5,     8,     7,     6,     3,
       2,     0,     6,     7,     4,     5,     7,     5,     7,     0,
       7,     5,     3,     0,     8,     0,    10,     2,     1,     1,
       2,     2,     3,     1,     3,     3,     1,     1,     3,     1,
       1,     2,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       6,    96,    97,   102,    15,     0,     4,     2,    88,     0,
      89,     2,   103,   104,     0,     0,     0,     0,     0,     4,
      99,     0,     2,     0,     0,     0,     0,    23,     1,     7,
      11,    16,     0,    14,    93,   100,     0,     0,     0,     0,
       0,     6,    87,    26,     0,    90,     0,    59,    61,     0,
       0,    70,     0,    91,     0,     0,    40,    41,     0,     0,
      24,    12,     8,    17,    42,    44,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,     0,     0,    58,    60,     0,   101,     2,     2,
       5,    82,     3,     0,     0,    26,    98,     0,     0,    71,
       2,    92,    31,     0,    39,     0,    95,     0,    12,     0,
       0,    49,    50,    48,    51,    94,    23,    46,    47,    63,
      35,    36,    37,    38,    69,     0,     0,    56,    57,    52,
       0,     0,     0,     0,    29,    28,     0,    62,     0,     0,
       0,    79,     0,     0,     0,    25,    13,    43,    45,     0,
       0,    23,    74,    64,    53,     2,    75,    77,     2,     0,
       0,     0,     0,     0,    18,    19,    81,     2,     2,    29,
       0,    32,    83,     0,    65,    55,     0,     0,     0,     0,
      30,     2,     0,     0,    72,    20,     0,     0,    33,     0,
       2,    85,    68,    54,    76,    67,     0,    73,    26,    80,
      78,    30,     0,     0,    66,     0,    34,    84,     2,     0,
       0,     2,    86,    21,     0,     0,    22,     0,     0,     0
};

static const short yydefgoto[] =
{
     217,    40,    41,    38,    39,    28,    29,   107,    30,    31,
      32,   163,   164,   165,   214,    59,    93,    94,   135,   142,
     143,   171,    33,   109,   110,   139,   167,   190,   203,    34,
      35,    36
};

static const short yypact[] =
{
     198,-32768,-32768,-32768,-32768,   250,-32768,-32768,   250,     0,
     250,-32768,-32768,-32768,    23,    23,   -21,    23,    23,-32768,
  -32768,    23,-32768,    23,   250,   250,   250,   250,-32768,    32,
  -32768,-32768,   198,   430,    -9,    19,    23,   298,    39,   250,
      33,   198,   430,    70,     8,   430,    69,-32768,-32768,   250,
      -3,-32768,    71,   250,    51,    56,   -27,   -27,   357,   -49,
     430,     7,    32,-32768,-32768,-32768,   250,   250,   250,   250,
     250,    42,   250,   250,    23,   250,   250,   250,   250,    23,
     250,   250,   250,   250,-32768,-32768,   250,    55,-32768,-32768,
     430,-32768,-32768,    43,    95,    70,-32768,   371,    23,    32,
  -32768,   430,    32,   250,-32768,   250,-32768,   250,    31,   250,
     250,   516,   516,    11,    11,   -27,   250,   516,   516,-32768,
     111,   111,    40,    40,   -24,   311,   -47,   430,   430,   430,
     250,    57,    91,    32,-32768,    46,    50,-32768,    32,    83,
      98,-32768,    32,   104,   416,   430,-32768,   470,   483,    30,
     250,   250,    77,-32768,   430,-32768,-32768,-32768,-32768,   119,
      32,    13,    23,   120,    83,-32768,-32768,-32768,-32768,   124,
      75,-32768,-32768,   130,-32768,   430,    34,   250,   127,   128,
  -32768,-32768,   129,    86,-32768,-32768,   131,   132,-32768,   138,
  -32768,-32768,-32768,   430,-32768,-32768,   135,-32768,    70,-32768,
  -32768,   141,   139,   146,-32768,    97,-32768,-32768,-32768,    32,
     152,-32768,-32768,-32768,   155,    32,    32,   151,   166,-32768
};

static const short yypgoto[] =
{
  -32768,   -11,-32768,   148,-32768,   133,   137,-32768,    64,   -26,
     -28,    12,-32768,    14,-32768,   -77,   -93,-32768,    29,-32768,
  -32768,-32768,    45,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
       6,-32768
};


#define	YYLAST		569


static const short yytable[] =
{
      46,    61,   136,     4,   126,     3,    63,    -9,   105,   153,
     105,    54,   106,     4,    71,    44,    -9,    -9,   150,     4,
      47,    48,    99,    50,    51,    79,    80,    53,     3,    55,
     151,   -10,   162,    49,   108,    63,    70,     4,     4,   149,
     -10,   -10,    87,    91,    -9,    81,    82,    83,    84,    85,
      37,    89,    71,    42,    43,    45,    98,    75,    76,    77,
      78,    86,    95,    79,    80,    70,   155,   156,   -10,    56,
      57,    58,    60,    63,   176,   -27,   141,   131,   132,    96,
     119,    71,    63,   100,    90,   124,   174,   105,   102,   140,
     192,   105,    79,    80,    97,   103,   116,   130,   101,   133,
     134,   157,   162,   159,   138,   205,   160,   158,   166,   169,
     161,   111,   112,   113,   114,   115,   168,   117,   118,   177,
     120,   121,   122,   123,   180,   125,    60,   127,   128,   188,
     184,   129,   189,   191,   181,    63,    70,   194,   195,   197,
     198,   199,   200,   201,   178,   204,   206,   179,   144,   207,
     145,   218,    71,   209,   147,   148,   186,   187,   208,    77,
      78,    60,   212,    79,    80,   215,   219,    52,   183,    62,
     196,   146,   170,   182,    92,   154,     0,     0,   185,   202,
       0,     0,     0,   211,     0,     0,     0,   216,     0,     0,
      63,     0,     0,     0,     0,   175,    60,   210,     0,     0,
     213,     1,     2,     3,     4,     5,     0,     0,     0,     6,
       7,     0,     0,     0,     0,     0,     8,     9,    10,    11,
      12,    13,   193,     0,     0,     0,     0,    14,    15,    16,
      17,    18,    19,    20,    21,     0,    22,     0,    23,     0,
       0,     0,     0,     0,     0,    24,     0,     0,    25,     0,
       0,     0,    26,     1,     2,     3,     0,     5,    27,     0,
       0,     6,     7,     0,     0,     0,     0,     0,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,    14,
      15,    16,    17,    18,    19,    20,    21,     0,    22,     0,
      23,     0,     0,     0,     0,     0,     0,    24,     0,     0,
      25,     0,     0,     0,    26,     0,    88,     0,     0,     0,
      27,    64,    65,    66,    67,    68,     0,     0,     0,     0,
       0,     0,    69,    70,    64,    65,    66,    67,    68,     0,
       0,     0,     0,     0,     0,    69,    70,     0,     0,    71,
       0,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    71,     0,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,     0,     0,     0,     0,   152,
      64,    65,    66,    67,    68,     0,     0,     0,     0,     0,
       0,    69,    70,     0,    64,    65,    66,    67,    68,     0,
       0,     0,     0,     0,     0,    69,    70,     0,    71,     0,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,     0,    71,   104,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,     0,     0,   137,   172,    64,
      65,    66,    67,    68,     0,     0,     0,     0,     0,     0,
      69,    70,   173,    64,    65,    66,    67,    68,     0,     0,
       0,     0,     0,     0,    69,    70,     0,    71,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
       0,    71,     0,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    65,    66,    67,    68,     0,     0,
       0,     0,     0,     0,    69,    70,     0,     0,    66,    67,
      68,     0,     0,     0,     0,     0,     0,    69,    70,     0,
       0,    71,     0,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    68,     0,    79,    80,     0,     0,     0,
      69,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,     0,     0,
       0,    74,    75,    76,    77,    78,     0,     0,    79,    80
};

static const short yycheck[] =
{
      11,    29,    95,     6,    81,     5,    32,     0,    57,    56,
      57,    22,    61,     6,    41,     9,     9,    10,    42,     6,
      14,    15,    50,    17,    18,    52,    53,    21,     5,    23,
      54,     0,    19,    54,    62,    61,    25,     6,     6,   116,
       9,    10,    36,    10,    37,    54,    27,    28,    29,    30,
       5,    12,    41,     8,    54,    10,    59,    46,    47,    48,
      49,    42,    54,    52,    53,    25,     9,    10,    37,    24,
      25,    26,    27,    99,   151,     5,   102,    88,    89,    10,
      74,    41,   108,    12,    39,    79,    56,    57,    37,   100,
      56,    57,    52,    53,    49,    39,    54,    42,    53,    56,
       5,    10,    19,    57,    98,   198,    56,   133,    10,     5,
     138,    66,    67,    68,    69,    70,   142,    72,    73,    42,
      75,    76,    77,    78,     5,    80,    81,    82,    83,     5,
      10,    86,    57,     3,   160,   161,    25,    10,    10,    10,
      54,    10,    10,     5,   155,    10,     5,   158,   103,    10,
     105,     0,    41,    56,   109,   110,   167,   168,    12,    48,
      49,   116,    10,    52,    53,    10,     0,    19,   162,    32,
     181,   107,   143,   161,    41,   130,    -1,    -1,   164,   190,
      -1,    -1,    -1,   209,    -1,    -1,    -1,   215,    -1,    -1,
     216,    -1,    -1,    -1,    -1,   150,   151,   208,    -1,    -1,
     211,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    18,    19,    20,    21,
      22,    23,   177,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    38,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    -1,
      -1,    -1,    54,     3,     4,     5,    -1,     7,    60,    -1,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    38,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      50,    -1,    -1,    -1,    54,    -1,     8,    -1,    -1,    -1,
      60,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,    41,
      -1,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      52,    53,    41,    -1,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,    -1,    -1,    -1,    -1,    58,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    -1,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    -1,    41,    -1,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    52,
      53,    -1,    41,    56,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,    -1,    -1,    56,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    25,    26,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    -1,    41,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    52,    53,
      -1,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    52,    53,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    -1,    -1,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    -1,
      -1,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    52,    53,    41,    -1,    43,    44,    45,    46,
      47,    48,    49,    17,    -1,    52,    53,    -1,    -1,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    -1,    -1,    52,    53
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

case 1:
#line 101 "grammar.y"
{}
    break;
case 2:
#line 104 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 3:
#line 104 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 4:
#line 107 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 5:
#line 107 "grammar.y"
{ pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 7:
#line 111 "grammar.y"
{}
    break;
case 8:
#line 112 "grammar.y"
{}
    break;
case 9:
#line 113 "grammar.y"
{}
    break;
case 10:
#line 114 "grammar.y"
{}
    break;
case 11:
#line 117 "grammar.y"
{ yyval.count = 1; }
    break;
case 12:
#line 118 "grammar.y"
{ yyval.count = yyvsp[-1].count + 1; }
    break;
case 14:
#line 121 "grammar.y"
{ pushn (SX_OP_STMT); }
    break;
case 15:
#line 124 "grammar.y"
{ pushn (SX_OP_NEXTLINE); }
    break;
case 18:
#line 131 "grammar.y"
{ pushv (sx_new_num (yyvsp[0].count)); pushn (SX_OP_NEWARRAY); }
    break;
case 19:
#line 134 "grammar.y"
{ yyval.count = 2; }
    break;
case 20:
#line 135 "grammar.y"
{ yyval.count = yyvsp[-1].count + 2; }
    break;
case 21:
#line 138 "grammar.y"
{ pushn (SX_OP_NEWFUNC); }
    break;
case 23:
#line 141 "grammar.y"
{ yyval.count = 0; }
    break;
case 24:
#line 142 "grammar.y"
{ yyval.count = 1; }
    break;
case 25:
#line 143 "grammar.y"
{ yyval.count = yyvsp[-2].count + 1; }
    break;
case 26:
#line 146 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 27:
#line 147 "grammar.y"
{ parser_push (sx_new_array (parse_system, 0, NULL)); }
    break;
case 28:
#line 147 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 29:
#line 150 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 30:
#line 151 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 31:
#line 154 "grammar.y"
{ parser_push (sx_new_array (parse_system, 0, NULL)); }
    break;
case 32:
#line 154 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 33:
#line 157 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[-1].name))); append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 34:
#line 158 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[-1].name))); append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 35:
#line 161 "grammar.y"
{ pushn (SX_OP_ADD); }
    break;
case 36:
#line 162 "grammar.y"
{ pushn (SX_OP_SUBTRACT); }
    break;
case 37:
#line 163 "grammar.y"
{ pushn (SX_OP_MULTIPLY); }
    break;
case 38:
#line 164 "grammar.y"
{ pushn (SX_OP_DIVIDE); }
    break;
case 40:
#line 166 "grammar.y"
{ pushn (SX_OP_NEGATE); }
    break;
case 41:
#line 168 "grammar.y"
{ pushn (SX_OP_NOT); }
    break;
case 42:
#line 169 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 43:
#line 169 "grammar.y"
{ pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); pushn (SX_OP_AND); }
    break;
case 44:
#line 170 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 45:
#line 170 "grammar.y"
{ pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); pushn (SX_OP_OR); }
    break;
case 46:
#line 172 "grammar.y"
{ pushn (SX_OP_GT); }
    break;
case 47:
#line 173 "grammar.y"
{ pushn (SX_OP_LT); }
    break;
case 48:
#line 174 "grammar.y"
{ pushn (SX_OP_NEQUAL); }
    break;
case 49:
#line 175 "grammar.y"
{ pushn (SX_OP_GTE); }
    break;
case 50:
#line 176 "grammar.y"
{ pushn (SX_OP_LTE); }
    break;
case 51:
#line 177 "grammar.y"
{ pushn (SX_OP_EQUAL); }
    break;
case 52:
#line 179 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
    break;
case 53:
#line 180 "grammar.y"
{ pushv (yyvsp[-3].value); pushn (SX_OP_ASSIGN); }
    break;
case 54:
#line 181 "grammar.y"
{ pushn (SX_OP_SETINDEX); }
    break;
case 55:
#line 182 "grammar.y"
{ pushn (SX_OP_SETMEMBER); }
    break;
case 56:
#line 184 "grammar.y"
{ pushn (SX_OP_PREINCREMENT); }
    break;
case 57:
#line 185 "grammar.y"
{ pushn (SX_OP_PREDECREMENT); }
    break;
case 58:
#line 186 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_POSTINCREMENT); }
    break;
case 59:
#line 187 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_PREINCREMENT); }
    break;
case 60:
#line 188 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_POSTDECREMENT); }
    break;
case 61:
#line 189 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_PREDECREMENT); }
    break;
case 62:
#line 191 "grammar.y"
{ pushn (SX_OP_SIZEOF); }
    break;
case 63:
#line 192 "grammar.y"
{ pushn (SX_OP_ISA); }
    break;
case 64:
#line 194 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_CALL); }
    break;
case 65:
#line 195 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_CALL); }
    break;
case 66:
#line 196 "grammar.y"
{ pushn (SX_OP_NEWFUNC); pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
    break;
case 67:
#line 197 "grammar.y"
{ pushn (SX_OP_NEWFUNC); }
    break;
case 68:
#line 199 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_METHOD); }
    break;
case 69:
#line 200 "grammar.y"
{ pushn (SX_OP_MEMBER); }
    break;
case 70:
#line 201 "grammar.y"
{ pushn (SX_OP_NEWINSTANCE); }
    break;
case 71:
#line 202 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 72:
#line 202 "grammar.y"
{ pushn (SX_OP_NEWCLASS); }
    break;
case 73:
#line 203 "grammar.y"
{ pushn (SX_OP_NEWCLASS); }
    break;
case 74:
#line 205 "grammar.y"
{ pushn (SX_OP_INDEX); }
    break;
case 75:
#line 207 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_IF); }
    break;
case 76:
#line 208 "grammar.y"
{ pushn (SX_OP_IF); }
    break;
case 77:
#line 209 "grammar.y"
{ pushn (SX_OP_WHILE); }
    break;
case 78:
#line 210 "grammar.y"
{ pushn (SX_OP_TRY); }
    break;
case 79:
#line 211 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 80:
#line 211 "grammar.y"
{ pushn (SX_OP_TRY); }
    break;
case 81:
#line 212 "grammar.y"
{ pushn (SX_OP_UNTIL); }
    break;
case 82:
#line 213 "grammar.y"
{ pushn (SX_OP_EVAL); }
    break;
case 83:
#line 214 "grammar.y"
{ pushv (sx_new_num (1)); }
    break;
case 84:
#line 214 "grammar.y"
{ pushn (SX_OP_FOR); }
    break;
case 85:
#line 215 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 86:
#line 215 "grammar.y"
{ pushn (SX_OP_FOR); }
    break;
case 87:
#line 217 "grammar.y"
{ pushn (SX_OP_RETURN); }
    break;
case 88:
#line 218 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_RETURN); }
    break;
case 89:
#line 219 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_BREAK); }
    break;
case 90:
#line 220 "grammar.y"
{ pushn (SX_OP_BREAK); }
    break;
case 91:
#line 221 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_RAISE); }
    break;
case 92:
#line 222 "grammar.y"
{ pushn (SX_OP_RAISE); }
    break;
case 93:
#line 224 "grammar.y"
{}
    break;
case 94:
#line 226 "grammar.y"
{ pushn (SX_OP_NEWRANGE); }
    break;
case 95:
#line 227 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_NEWARRAY); }
    break;
case 96:
#line 229 "grammar.y"
{ pushv (yyvsp[0].value);  }
    break;
case 97:
#line 230 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 99:
#line 232 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 100:
#line 235 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_LOOKUP); }
    break;
case 101:
#line 236 "grammar.y"
{ pushv (yyvsp[-1].value); pushn (SX_OP_LOOKUP); }
    break;
case 102:
#line 239 "grammar.y"
{ pushv (sx_new_num (sx_name_to_id (yyvsp[0].name))); }
    break;
case 103:
#line 242 "grammar.y"
{ yyval.value = (sx_new_num (SX_SCOPE_LOCAL)); }
    break;
case 104:
#line 243 "grammar.y"
{ yyval.value = (sx_new_num (SX_SCOPE_GLOBAL)); }
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
#line 246 "grammar.y"


void
parser_add_line (void) {
	++ parse_lineno;
}

/* value stack */
SX_VALUE *
parser_top (void) {
	if (parser_stack_top > 0) {
		return parser_stack[parser_stack_top - 1];
	}

	return NULL;
}

void
parser_push (SX_VALUE *value) {
	SX_VALUE **sx_new_stack;
	if (parser_stack_top >= parser_stack_size) {
		if (parser_stack != NULL) {
			sx_new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + COMP_STACK_SIZE) * sizeof (SX_VALUE **));
		} else {
			sx_new_stack = sx_malloc (parse_system, (parser_stack_size + COMP_STACK_SIZE) * sizeof (SX_VALUE **));
		}
		if (sx_new_stack == NULL) {
			return;
		}
		sx_free (parser_stack);
		parser_stack = sx_new_stack;
		parser_stack_size += COMP_STACK_SIZE;
	}

	parser_stack[parser_stack_top ++] = value;
}

void
parser_pop (void) {
	if (parser_stack_top > 0) {
		-- parser_stack_top;
	}
}


SX_VALUE *
append_to_array (SX_VALUE *array, SX_VALUE *value) {
	SX_VALUE **nlist;

	if (!SX_ISARRAY (parse_system, array)) {
		return sx_new_nil ();
	}

	if (SX_TOARRAY(array)->count > 0) {
		nlist = (SX_VALUE **)sx_malloc (parse_system, (SX_TOARRAY(array)->count + 1) * sizeof (SX_VALUE *));
		if (nlist == NULL) {
			return sx_new_nil ();
		}
		memcpy (nlist, SX_TOARRAY(array)->list, SX_TOARRAY(array)->count * sizeof (SX_VALUE *));
		sx_free (SX_TOARRAY(array)->list);
		SX_TOARRAY(array)->list = nlist;
		SX_TOARRAY(array)->list[SX_TOARRAY(array)->count] = value;
		SX_TOARRAY(array)->count += 1;
	} else {
		SX_TOARRAY(array)->list = (SX_VALUE **)sx_malloc (parse_system, sizeof (SX_VALUE *));
		if (SX_TOARRAY(array)->list == NULL) {
			return sx_new_nil ();
		}
		SX_TOARRAY(array)->list[0] = value;
		SX_TOARRAY(array)->count = 1;
	}

	return array;
}

int
sxerror (const char *str) {
	if (parse_system->error_hook != NULL) {
		char buffer[512];
		snprintf (buffer, 512, "Parse Error: line %d: %s", parse_lineno, str);
		parse_system->error_hook (buffer);
	} else {
		fprintf (stderr, "Scriptix Parse Error: line %d: %s\n", parse_lineno, str);
	}
	return 1;
}

int
sxwrap (void) {
	return 1;
}

void
cleanup_parser (void) {
	free (parser_stack);
	parser_stack = NULL;
	parser_stack_top = 0;
	parser_stack_size = 0;
}

SX_VALUE *
sx_load_file (SX_SYSTEM *system, const char *file) {
	int ret, flags;
	SX_VALUE *sfile;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return 0;
		}
	}

	parse_system = system;
	parse_block = sx_new_block (system);
	if (parse_block == NULL) {
		if (sxin != NULL) {
			fclose (sxin);
		}
		return 0;
	}

	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	parser_push (parse_block);
	sfile = sx_new_str (system, file ? file : "<stdin>");
	pushv (sfile);
	pushv (sx_new_num (1));
	pushn (SX_OP_SETFILELINE);
	ret = sxparse ();

	parser_pop ();
	system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	sx_lock_value (parse_block);

	cleanup_parser ();
	sx_run_gc (system);

	sx_unlock_value (parse_block);

	if (ret) {
		return 0;
	}

	return parse_block;
}

SX_VALUE *
sx_load_string (SX_SYSTEM *system, const char *str) {
	int ret, flags;

	if (str == NULL) {
		return 0;
	}

	parse_system = system;
	parse_block = sx_new_block (system);
	if (parse_block == NULL) {
		return 0;
	}

	sx_parser_inbuf = str;

	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;
	parser_push (parse_block);
	ret = sxparse ();
	parser_pop ();
	system->flags = flags;

	sx_parser_inbuf = NULL;

	sx_lock_value (parse_block);

	cleanup_parser ();
	sx_run_gc (system);

	sx_unlock_value (parse_block);

	if (ret) {
		return 0;
	}

	return parse_block;
}

sx_thread_id
sx_start_file (SX_SYSTEM *system, const char *file, SX_VALUE *argv) {
	int ret, flags;
	SX_VALUE *sfile;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return 0;
		}
	}

	parse_system = system;
	sx_lock_value (argv);
	parse_block = sx_new_block (system);
	sx_unlock_value (argv);
	if (parse_block == NULL) {
		if (sxin != NULL) {
			fclose (sxin);
		}
		return 0;
	}

	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;

	parser_push (parse_block);
	sfile = sx_new_str (system, file ? file : "<stdin>");
	pushv (sfile);
	pushv (sx_new_num (1));
	pushn (SX_OP_SETFILELINE);
	ret = sxparse ();

	parser_pop ();
	system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	sx_lock_value (parse_block);
	sx_lock_value (argv);

	cleanup_parser ();
	sx_run_gc (system);

	sx_unlock_value (parse_block);
	sx_unlock_value (argv);

	if (ret) {
		return 0;
	}

	return sx_create_thread (system, parse_block, argv);
}

sx_thread_id
sx_start_string (SX_SYSTEM *system, const char *str, SX_VALUE *argv) {
	int ret, flags;

	if (str == NULL) {
		return 0;
	}

	parse_system = system;
	sx_lock_value (argv);
	parse_block = sx_new_block (system);
	sx_unlock_value (argv);
	if (parse_block == NULL) {
		return 0;
	}

	sx_parser_inbuf = str;

	flags = system->flags;
	system->flags |= SX_SFLAG_GCOFF;
	parser_push (parse_block);
	ret = sxparse ();
	parser_pop ();
	system->flags = flags;

	sx_parser_inbuf = NULL;

	sx_lock_value (parse_block);
	sx_lock_value (argv);

	cleanup_parser ();
	sx_run_gc (system);

	sx_unlock_value (parse_block);
	sx_unlock_value (argv);

	if (ret) {
		return 0;
	}

	return sx_create_thread (system, parse_block, argv);
}

SX_VALUE *
sx_run_file (SX_SYSTEM *system, const char *file, SX_VALUE *argv) {
	sx_thread_id id;

	id = sx_start_file (system, file, argv);
	if (id) {
		return sx_run_until (system, id);
	} else {
		return NULL;
	}
}

SX_VALUE *
sx_run_string (SX_SYSTEM *system, const char *str, SX_VALUE *argv) {
	sx_thread_id id;

	id = sx_start_string (system, str, argv);
	if (id) {
		return sx_run_until (system, id);
	} else {
		return NULL;
	}
}
