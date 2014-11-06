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
# define	TTYPE	297
# define	CUNARY	298

#line 28 "grammar.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <errno.h>

	#include "scriptix.h"

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

	int sxerror (char *);
	int sxlex (void);

	SX_SYSTEM *parse_system = NULL;
	SX_VALUE *parse_block = NULL;

	unsigned int parse_lineno = 1;
	extern FILE *sxin;
	int sxparse (void);

	SX_VALUE *temp_val;

	extern char *sx_parser_inbuf;

	#define pushv(v) (sx_add_value (parse_system, parser_top (), (v)))
	#define pushn(o) (sx_add_stmt (parse_system, parser_top (), (o)))

#line 69 "grammar.y"
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



#define	YYFINAL		225
#define	YYFLAG		-32768
#define	YYNTBASE	63

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 96)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,     2,     2,     2,     2,     2,
      55,    57,    48,    46,    58,    47,    53,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,     2,
      44,    42,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    59,    56,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,     2,    62,     2,     2,     2,     2,
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
      36,    37,    38,    39,    40,    41,    45,    50,    52
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,     7,    10,    11,    13,    16,
      19,    23,    25,    26,    31,    33,    35,    38,    39,    42,
      43,    45,    48,    51,    55,    57,    58,    63,    67,    76,
      77,    79,    83,    84,    85,    88,    90,    94,    95,    98,
     101,   106,   110,   114,   118,   122,   126,   129,   132,   133,
     138,   139,   144,   148,   152,   156,   160,   164,   168,   172,
     177,   184,   190,   194,   198,   201,   204,   207,   210,   215,
     220,   224,   229,   235,   244,   252,   259,   263,   266,   267,
     274,   275,   284,   289,   295,   303,   309,   316,   322,   326,
     327,   336,   337,   348,   351,   353,   355,   358,   361,   363,
     367,   371,   373,   375,   379,   381,   383,   386,   388,   390
};
static const short yyrhs[] =
{
      68,     0,     0,    65,    68,     0,     0,    67,    86,     0,
       0,    69,     0,    72,    69,     0,    69,    72,     0,    72,
      69,    72,     0,    71,     0,     0,    69,    72,    70,    71,
       0,    86,     0,     6,     0,    72,     6,     0,     0,    74,
      75,     0,     0,    76,     0,    72,    76,     0,    76,    72,
       0,    72,    76,    72,     0,    78,     0,     0,    76,    72,
      77,    78,     0,    94,    42,    86,     0,    19,    94,    55,
      80,    57,     6,    64,    10,     0,     0,    86,     0,    79,
      58,    86,     0,     0,     0,    81,    82,     0,     5,     0,
      82,    58,     5,     0,     0,    84,    85,     0,     5,     5,
       0,    82,    58,     5,     5,     0,    86,    46,    86,     0,
      86,    47,    86,     0,    86,    48,    86,     0,    86,    49,
      86,     0,    55,    86,    57,     0,    47,    86,     0,    51,
      86,     0,     0,    86,    13,    87,    86,     0,     0,    86,
      14,    88,    86,     0,    86,    43,    86,     0,    86,    44,
      86,     0,    86,    17,    86,     0,    86,    15,    86,     0,
      86,    16,    86,     0,    86,    24,    86,     0,    94,    42,
      86,     0,    95,    94,    42,    86,     0,    86,    54,    86,
      59,    42,    86,     0,    86,    53,    94,    42,    86,     0,
      94,    27,    86,     0,    94,    28,    86,     0,    94,    29,
       0,    29,    94,     0,    94,    30,     0,    30,    94,     0,
      31,    55,    86,    57,     0,    50,    55,    86,    57,     0,
      86,    45,    86,     0,    93,    55,    79,    57,     0,    86,
      41,    55,    79,    57,     0,    19,    94,    55,    80,    57,
       6,    64,    10,     0,    19,    55,    80,    57,     6,    64,
      10,     0,    86,    53,    94,    55,    79,    57,     0,    86,
      53,    94,     0,    33,    86,     0,     0,    32,    94,     6,
      89,    73,    10,     0,     0,    32,    94,    60,    94,     6,
      90,    73,    10,     0,    86,    54,    86,    59,     0,     7,
      86,     8,    64,    10,     0,     7,    86,     8,    64,     9,
      64,    10,     0,    11,    66,    12,    64,    10,     0,    38,
      64,    37,    83,    64,    10,     0,    34,    66,    12,    64,
      10,     0,    12,    64,    10,     0,     0,    40,    94,    39,
      86,    12,    91,    64,    10,     0,     0,    40,    94,    39,
      86,    26,     3,    92,    12,    64,    10,     0,    18,    86,
       0,    18,     0,    20,     0,    20,    86,     0,    36,    86,
       0,    93,     0,    86,    25,    86,     0,    61,    79,    62,
       0,     3,     0,     4,     0,    21,    64,    10,     0,    35,
       0,    94,     0,    95,    94,     0,     5,     0,    22,     0,
      23,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   100,   103,   103,   106,   106,   109,   110,   111,   112,
     113,   116,   117,   117,   120,   123,   124,   127,   127,   130,
     131,   132,   133,   134,   137,   138,   138,   141,   142,   145,
     146,   147,   150,   151,   151,   154,   155,   158,   158,   161,
     162,   165,   166,   167,   168,   169,   170,   172,   173,   173,
     174,   174,   176,   177,   178,   179,   180,   181,   183,   184,
     185,   186,   188,   189,   190,   191,   192,   193,   195,   196,
     197,   199,   200,   201,   202,   204,   205,   206,   207,   207,
     208,   208,   210,   212,   213,   214,   215,   216,   217,   218,
     218,   219,   219,   221,   222,   223,   224,   225,   227,   229,
     230,   232,   233,   234,   235,   238,   239,   242,   245,   246
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
  "'>'", "'<'", "TISA", "'+'", "'-'", "'*'", "'/'", "TTYPE", "'!'", 
  "CUNARY", "'.'", "'['", "'('", "'^'", "')'", "','", "']'", "':'", "'{'", 
  "'}'", "program", "block", "@1", "oblock", "@2", "stmts", "stmt_list", 
  "@3", "stmt", "seps", "cblock", "@4", "cstmts", "cstmt_list", "@5", 
  "cstmt", "array_list", "args", "@6", "arg_list", "errors", "@7", 
  "error_list", "node", "@8", "@9", "@10", "@11", "@12", "@13", "lookup", 
  "name", "scope", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    63,    65,    64,    67,    66,    68,    68,    68,    68,
      68,    69,    70,    69,    71,    72,    72,    74,    73,    75,
      75,    75,    75,    75,    76,    77,    76,    78,    78,    79,
      79,    79,    80,    81,    80,    82,    82,    84,    83,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    87,    86,
      88,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    89,    86,
      90,    86,    86,    86,    86,    86,    86,    86,    86,    91,
      86,    92,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    93,    93,    94,    95,    95
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     0,     2,     0,     1,     2,     2,
       3,     1,     0,     4,     1,     1,     2,     0,     2,     0,
       1,     2,     2,     3,     1,     0,     4,     3,     8,     0,
       1,     3,     0,     0,     2,     1,     3,     0,     2,     2,
       4,     3,     3,     3,     3,     3,     2,     2,     0,     4,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     4,
       6,     5,     3,     3,     2,     2,     2,     2,     4,     4,
       3,     4,     5,     8,     7,     6,     3,     2,     0,     6,
       0,     8,     4,     5,     7,     5,     6,     5,     3,     0,
       8,     0,    10,     2,     1,     1,     2,     2,     1,     3,
       3,     1,     1,     3,     1,     1,     2,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       6,   101,   102,   107,    15,     0,     4,     2,    94,     0,
      95,     2,   108,   109,     0,     0,     0,     0,     0,     4,
     104,     0,     2,     0,     0,     0,     0,     0,    29,     1,
       7,    11,     0,    14,    98,   105,     0,     0,     0,     0,
       0,     6,    93,    32,     0,    96,     0,    65,    67,     0,
       0,    77,     0,    97,     0,     0,    46,     0,    47,     0,
       0,    30,    12,    16,     8,    48,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    64,    66,     0,   106,     2,
       2,     5,    88,     3,     0,     0,    32,   103,     0,    78,
       0,     2,    37,     0,     0,    45,     0,   100,     0,    12,
       0,     0,    55,    56,    54,    57,    99,    29,    52,    53,
      70,    41,    42,    43,    44,    76,     0,     0,    62,    63,
      58,     0,     0,     0,     0,    35,    34,     0,    68,    17,
       0,     0,     2,     0,     0,    69,    31,    13,    49,    51,
       0,     0,    29,    82,    71,    59,     2,    83,    85,     2,
       0,     0,     0,    19,    80,    87,     0,    35,     0,    38,
      89,     0,    72,    61,     0,     0,     0,     0,    36,     2,
      79,     0,     0,    18,    20,    24,     0,    17,    86,    39,
       0,     2,    91,    75,    60,    84,    74,     0,     0,    21,
      25,     0,     0,    36,     0,     0,    73,    32,    25,     0,
      27,    81,    40,    90,     2,     0,    26,     0,     0,    92,
       2,     0,    28,     0,     0,     0
};

static const short yydefgoto[] =
{
     223,    40,    41,    38,    39,    29,    30,   108,    31,    32,
     162,   163,   183,   184,   209,   185,    60,    94,    95,   136,
     142,   143,   169,    33,   110,   111,   139,   187,   191,   205,
      34,    35,    36
};

static const short yypact[] =
{
     201,-32768,-32768,-32768,-32768,   307,-32768,-32768,   307,     3,
     307,-32768,-32768,-32768,     9,     9,   -32,     9,   307,-32768,
  -32768,   307,-32768,     9,   307,   -24,   307,   307,   307,-32768,
      28,-32768,   254,   517,     5,    -3,     9,   336,    32,   307,
      42,   201,   517,    72,    30,   517,    89,-32768,-32768,   307,
      -1,    66,   109,   517,    85,    84,    33,   307,    33,   397,
     -45,   517,    10,-32768,    28,-32768,-32768,   307,   307,   307,
     307,   307,    69,   307,   307,   307,   307,   307,   307,   307,
       9,   307,   307,   307,   307,-32768,-32768,   307,    83,-32768,
  -32768,   517,-32768,-32768,    70,   121,    72,-32768,   412,-32768,
       9,-32768,-32768,   307,   457,-32768,   307,-32768,   307,    12,
     307,   307,    16,    16,    93,    93,    33,   307,    16,    16,
      93,   437,   437,    66,    66,    38,   350,    25,   517,   517,
     517,   307,    79,   118,   123,-32768,    74,    86,-32768,-32768,
     130,   139,-32768,   146,   503,-32768,   517,-32768,   145,   552,
      55,   307,   307,   108,-32768,   517,-32768,-32768,-32768,-32768,
     147,   148,   143,    24,-32768,-32768,   153,   152,   106,-32768,
  -32768,   162,-32768,   517,    59,   307,   156,   157,-32768,-32768,
  -32768,     9,    62,-32768,    28,-32768,   133,-32768,-32768,-32768,
     167,-32768,-32768,-32768,   517,-32768,-32768,   166,   122,    28,
      40,   307,   171,   177,   173,   172,-32768,    72,    65,    37,
     517,-32768,-32768,-32768,-32768,   128,-32768,   185,   181,-32768,
  -32768,   186,-32768,   197,   200,-32768
};

static const short yypgoto[] =
{
  -32768,   -11,-32768,   191,-32768,   170,   182,-32768,   107,   -28,
      29,-32768,-32768,    35,-32768,    17,   -79,   -92,-32768,    75,
  -32768,-32768,-32768,    27,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    -8,-32768
};


#define	YYLAST		606


static const short yytable[] =
{
      46,    44,    62,   127,   137,    99,    47,    48,     3,    50,
      -9,    54,   -10,   106,     3,    55,    63,   107,    63,    -9,
      -9,   -10,   -10,    49,    83,    84,    85,    86,    88,     3,
       4,    57,    37,    69,     4,    42,   109,    45,   150,    87,
      70,    71,     3,   181,    90,    51,    63,    -9,    53,   -10,
     -22,    56,    92,    58,    59,    61,   181,    72,    43,   100,
      82,    75,    76,    77,    78,    79,    91,     3,    63,    80,
      81,    63,   125,   174,    72,   -23,    98,   -33,   132,   133,
     151,   181,   154,   106,   104,    96,    80,    81,   156,   157,
     141,    71,   140,   152,   112,   113,   114,   115,   116,    97,
     118,   119,   120,   121,   122,   123,   124,    72,   126,    61,
     128,   129,   172,   106,   130,   215,   193,   106,    71,    80,
      81,   101,   102,   103,   117,   131,   135,   134,   158,   159,
     144,   166,   160,   146,    72,   182,   164,   148,   149,    76,
      77,    78,    79,   161,    61,   176,    80,    81,   177,   165,
     175,   167,   178,   180,   179,   186,   200,   189,   155,    66,
      67,    68,    69,   188,   190,   192,   195,   196,   197,    70,
      71,   208,   203,   198,   186,   201,   206,   207,   173,    61,
     204,   211,   212,   213,   214,   218,    72,   220,    73,    74,
      75,    76,    77,    78,    79,   219,   222,   224,    80,    81,
     225,   186,   194,   217,     1,     2,     3,     4,     5,   221,
      52,    93,     6,     7,    64,   147,   202,   199,   168,     8,
       9,    10,    11,    12,    13,     0,   216,     0,   210,     0,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
       0,    23,     0,     0,     0,     0,     0,     0,    24,     0,
       0,    25,    26,     0,     0,     0,    27,     1,     2,     3,
      63,     5,    28,     0,     0,     6,     7,     0,     0,     0,
       0,     0,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,    14,    15,    16,    17,    18,    19,    20,
      21,     0,    22,     0,    23,     0,     0,     0,     0,     0,
       0,    24,     0,     0,    25,    26,     0,     0,     0,    27,
       1,     2,     3,     0,     5,    28,     0,     0,     6,     7,
       0,     0,     0,     0,     0,     8,     9,    10,    11,    12,
      13,     0,     0,     0,     0,     0,    14,    15,    16,    17,
      18,    19,    20,    21,    89,    22,     0,    23,     0,    65,
      66,    67,    68,    69,    24,     0,     0,    25,    26,     0,
      70,    71,    27,    65,    66,    67,    68,    69,    28,     0,
       0,     0,     0,     0,    70,    71,     0,    72,     0,    73,
      74,    75,    76,    77,    78,    79,     0,     0,     0,    80,
      81,    72,     0,    73,    74,    75,    76,    77,    78,    79,
       0,     0,     0,    80,    81,     0,     0,     0,     0,   153,
      65,    66,    67,    68,    69,     0,     0,     0,     0,     0,
       0,    70,    71,     0,     0,    65,    66,    67,    68,    69,
       0,     0,     0,     0,     0,     0,    70,    71,    72,     0,
      73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
      80,    81,     0,    72,   105,    73,    74,    75,    76,    77,
      78,    79,    71,     0,     0,    80,    81,     0,     0,   138,
      65,    66,    67,    68,    69,     0,     0,     0,    72,     0,
       0,    70,    71,     0,     0,    78,    79,     0,     0,     0,
      80,    81,     0,     0,     0,     0,     0,     0,    72,     0,
      73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
      80,    81,     0,     0,   145,   170,    65,    66,    67,    68,
      69,     0,     0,     0,     0,     0,     0,    70,    71,   171,
      65,    66,    67,    68,    69,     0,     0,     0,     0,     0,
       0,    70,    71,     0,    72,     0,    73,    74,    75,    76,
      77,    78,    79,     0,     0,     0,    80,    81,    72,     0,
      73,    74,    75,    76,    77,    78,    79,    67,    68,    69,
      80,    81,     0,     0,     0,     0,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    72,     0,    73,    74,    75,    76,    77,
      78,    79,     0,     0,     0,    80,    81
};

static const short yycheck[] =
{
      11,     9,    30,    82,    96,     6,    14,    15,     5,    17,
       0,    22,     0,    58,     5,    23,     6,    62,     6,     9,
      10,     9,    10,    55,    27,    28,    29,    30,    36,     5,
       6,    55,     5,    17,     6,     8,    64,    10,   117,    42,
      24,    25,     5,    19,    12,    18,     6,    37,    21,    37,
      10,    24,    10,    26,    27,    28,    19,    41,    55,    60,
      55,    45,    46,    47,    48,    49,    39,     5,     6,    53,
      54,     6,    80,   152,    41,    10,    49,     5,    89,    90,
      42,    19,    57,    58,    57,    55,    53,    54,     9,    10,
     101,    25,   100,    55,    67,    68,    69,    70,    71,    10,
      73,    74,    75,    76,    77,    78,    79,    41,    81,    82,
      83,    84,    57,    58,    87,   207,    57,    58,    25,    53,
      54,    12,    37,    39,    55,    42,     5,    57,    10,     6,
     103,   142,    58,   106,    41,   163,     6,   110,   111,    46,
      47,    48,    49,    57,   117,   156,    53,    54,   159,    10,
      42,     5,     5,    10,     6,   163,   184,     5,   131,    14,
      15,    16,    17,    10,    58,     3,    10,    10,   179,    24,
      25,   199,     5,   181,   182,    42,    10,    55,   151,   152,
     191,    10,     5,    10,    12,    57,    41,     6,    43,    44,
      45,    46,    47,    48,    49,    10,    10,     0,    53,    54,
       0,   209,   175,   214,     3,     4,     5,     6,     7,   220,
      19,    41,    11,    12,    32,   108,   187,   182,   143,    18,
      19,    20,    21,    22,    23,    -1,   209,    -1,   201,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    -1,    38,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    50,    51,    -1,    -1,    -1,    55,     3,     4,     5,
       6,     7,    61,    -1,    -1,    11,    12,    -1,    -1,    -1,
      -1,    -1,    18,    19,    20,    21,    22,    23,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    38,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    50,    51,    -1,    -1,    -1,    55,
       3,     4,     5,    -1,     7,    61,    -1,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    18,    19,    20,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,     8,    38,    -1,    40,    -1,    13,
      14,    15,    16,    17,    47,    -1,    -1,    50,    51,    -1,
      24,    25,    55,    13,    14,    15,    16,    17,    61,    -1,
      -1,    -1,    -1,    -1,    24,    25,    -1,    41,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    53,
      54,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    59,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    -1,    -1,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    41,    -1,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      53,    54,    -1,    41,    57,    43,    44,    45,    46,    47,
      48,    49,    25,    -1,    -1,    53,    54,    -1,    -1,    57,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    41,    -1,
      -1,    24,    25,    -1,    -1,    48,    49,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      53,    54,    -1,    -1,    57,    12,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    25,    -1,    41,    -1,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    53,    54,    41,    -1,
      43,    44,    45,    46,    47,    48,    49,    15,    16,    17,
      53,    54,    -1,    -1,    -1,    -1,    24,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    -1,    53,    54
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
#line 100 "grammar.y"
{}
    break;
case 2:
#line 103 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 3:
#line 103 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 4:
#line 106 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 5:
#line 106 "grammar.y"
{ pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 7:
#line 110 "grammar.y"
{}
    break;
case 8:
#line 111 "grammar.y"
{}
    break;
case 9:
#line 112 "grammar.y"
{}
    break;
case 10:
#line 113 "grammar.y"
{}
    break;
case 11:
#line 116 "grammar.y"
{ yyval.count = 1; }
    break;
case 12:
#line 117 "grammar.y"
{ yyval.count = yyvsp[-1].count + 1; }
    break;
case 14:
#line 120 "grammar.y"
{ pushn (SX_OP_STMT); }
    break;
case 17:
#line 127 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 18:
#line 127 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 20:
#line 131 "grammar.y"
{}
    break;
case 21:
#line 132 "grammar.y"
{}
    break;
case 22:
#line 133 "grammar.y"
{}
    break;
case 23:
#line 134 "grammar.y"
{}
    break;
case 24:
#line 137 "grammar.y"
{ yyval.count = 1; }
    break;
case 25:
#line 138 "grammar.y"
{ yyval.count = yyvsp[-1].count + 1; }
    break;
case 27:
#line 141 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_CLASS)); pushn (SX_OP_ASSIGN); pushn (SX_OP_STMT); }
    break;
case 28:
#line 142 "grammar.y"
{ pushn (SX_OP_NEWFUNC); pushv (sx_new_num (SX_SCOPE_CLASS)); pushn (SX_OP_ASSIGN); pushn (SX_OP_STMT); }
    break;
case 29:
#line 145 "grammar.y"
{ yyval.count = 0; }
    break;
case 30:
#line 146 "grammar.y"
{ yyval.count = 1; }
    break;
case 31:
#line 147 "grammar.y"
{ yyval.count = yyvsp[-2].count + 1; }
    break;
case 32:
#line 150 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 33:
#line 151 "grammar.y"
{ parser_push (sx_new_array (parse_system, 0, NULL)); }
    break;
case 34:
#line 151 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 35:
#line 154 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 36:
#line 155 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 37:
#line 158 "grammar.y"
{ parser_push (sx_new_array (parse_system, 0, NULL)); }
    break;
case 38:
#line 158 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 39:
#line 161 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[-1].name))); append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 40:
#line 162 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[-1].name))); append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 41:
#line 165 "grammar.y"
{ pushn (SX_OP_ADD); }
    break;
case 42:
#line 166 "grammar.y"
{ pushn (SX_OP_SUBTRACT); }
    break;
case 43:
#line 167 "grammar.y"
{ pushn (SX_OP_MULTIPLY); }
    break;
case 44:
#line 168 "grammar.y"
{ pushn (SX_OP_DIVIDE); }
    break;
case 46:
#line 170 "grammar.y"
{ pushn (SX_OP_NEGATE); }
    break;
case 47:
#line 172 "grammar.y"
{ pushn (SX_OP_NOT); }
    break;
case 48:
#line 173 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 49:
#line 173 "grammar.y"
{ pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); pushn (SX_OP_AND); }
    break;
case 50:
#line 174 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 51:
#line 174 "grammar.y"
{ pushn (SX_OP_STMT); temp_val = parser_top (); parser_pop (); pushv (temp_val); pushn (SX_OP_OR); }
    break;
case 52:
#line 176 "grammar.y"
{ pushn (SX_OP_GT); }
    break;
case 53:
#line 177 "grammar.y"
{ pushn (SX_OP_LT); }
    break;
case 54:
#line 178 "grammar.y"
{ pushn (SX_OP_NEQUAL); }
    break;
case 55:
#line 179 "grammar.y"
{ pushn (SX_OP_GTE); }
    break;
case 56:
#line 180 "grammar.y"
{ pushn (SX_OP_LTE); }
    break;
case 57:
#line 181 "grammar.y"
{ pushn (SX_OP_EQUAL); }
    break;
case 58:
#line 183 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
    break;
case 59:
#line 184 "grammar.y"
{ pushv (yyvsp[-3].value); pushn (SX_OP_ASSIGN); }
    break;
case 60:
#line 185 "grammar.y"
{ pushn (SX_OP_SETINDEX); }
    break;
case 61:
#line 186 "grammar.y"
{ pushn (SX_OP_SETMEMBER); }
    break;
case 62:
#line 188 "grammar.y"
{ pushn (SX_OP_PREINCREMENT); }
    break;
case 63:
#line 189 "grammar.y"
{ pushn (SX_OP_PREDECREMENT); }
    break;
case 64:
#line 190 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_POSTINCREMENT); }
    break;
case 65:
#line 191 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_PREINCREMENT); }
    break;
case 66:
#line 192 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_POSTDECREMENT); }
    break;
case 67:
#line 193 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_PREDECREMENT); }
    break;
case 68:
#line 195 "grammar.y"
{ pushn (SX_OP_SIZEOF); }
    break;
case 69:
#line 196 "grammar.y"
{ pushn (SX_OP_TYPEOF); }
    break;
case 70:
#line 197 "grammar.y"
{ pushn (SX_OP_ISA); }
    break;
case 71:
#line 199 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_CALL); }
    break;
case 72:
#line 200 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_CALL); }
    break;
case 73:
#line 201 "grammar.y"
{ pushn (SX_OP_NEWFUNC); pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
    break;
case 74:
#line 202 "grammar.y"
{ pushn (SX_OP_NEWFUNC); }
    break;
case 75:
#line 204 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_METHOD); }
    break;
case 76:
#line 205 "grammar.y"
{ pushn (SX_OP_MEMBER); }
    break;
case 77:
#line 206 "grammar.y"
{ pushn (SX_OP_NEWINSTANCE); }
    break;
case 78:
#line 207 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 79:
#line 207 "grammar.y"
{ pushn (SX_OP_NEWCLASS); pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
    break;
case 80:
#line 208 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_LOOKUP); }
    break;
case 81:
#line 208 "grammar.y"
{ pushn (SX_OP_NEWCLASS); pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_ASSIGN); }
    break;
case 82:
#line 210 "grammar.y"
{ pushn (SX_OP_INDEX); }
    break;
case 83:
#line 212 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_IF); }
    break;
case 84:
#line 213 "grammar.y"
{ pushn (SX_OP_IF); }
    break;
case 85:
#line 214 "grammar.y"
{ pushn (SX_OP_WHILE); }
    break;
case 86:
#line 215 "grammar.y"
{ pushn (SX_OP_TRY); }
    break;
case 87:
#line 216 "grammar.y"
{ pushn (SX_OP_UNTIL); }
    break;
case 88:
#line 217 "grammar.y"
{ pushn (SX_OP_EVAL); }
    break;
case 89:
#line 218 "grammar.y"
{ pushv (sx_new_num (1)); }
    break;
case 90:
#line 218 "grammar.y"
{ pushn (SX_OP_FOR); }
    break;
case 91:
#line 219 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 92:
#line 219 "grammar.y"
{ pushn (SX_OP_FOR); }
    break;
case 93:
#line 221 "grammar.y"
{ pushn (SX_OP_RETURN); }
    break;
case 94:
#line 222 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_RETURN); }
    break;
case 95:
#line 223 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_BREAK); }
    break;
case 96:
#line 224 "grammar.y"
{ pushn (SX_OP_BREAK); }
    break;
case 97:
#line 225 "grammar.y"
{ pushn (SX_OP_RAISE); }
    break;
case 98:
#line 227 "grammar.y"
{}
    break;
case 99:
#line 229 "grammar.y"
{ pushn (SX_OP_NEWRANGE); }
    break;
case 100:
#line 230 "grammar.y"
{ pushv (sx_new_num (yyvsp[-1].count)); pushn (SX_OP_NEWARRAY); }
    break;
case 101:
#line 232 "grammar.y"
{ pushv (yyvsp[0].value);  }
    break;
case 102:
#line 233 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 104:
#line 235 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 105:
#line 238 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_DEF)); pushn (SX_OP_LOOKUP); }
    break;
case 106:
#line 239 "grammar.y"
{ pushv (yyvsp[-1].value); pushn (SX_OP_LOOKUP); }
    break;
case 107:
#line 242 "grammar.y"
{ pushv (sx_new_num (sx_name_to_id (yyvsp[0].name))); }
    break;
case 108:
#line 245 "grammar.y"
{ yyval.value = (sx_new_num (SX_SCOPE_LOCAL)); }
    break;
case 109:
#line 246 "grammar.y"
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
#line 249 "grammar.y"


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
			/* FIXME: error */
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

	if (!SX_ISARRAY (array)) {
		return sx_new_nil ();
	}

	if (array->data.array.count > 0) {
		nlist = (SX_VALUE **)sx_malloc (parse_system, (array->data.array.count + 1) * sizeof (SX_VALUE *));
		if (nlist == NULL) {
			return sx_new_nil ();
		}
		memcpy (nlist, array->data.array.list, array->data.array.count * sizeof (SX_VALUE *));
		sx_free (array->data.array.list);
		array->data.array.list = nlist;
		array->data.array.list[array->data.array.count] = value;
		array->data.array.count += 1;
	} else {
		array->data.array.list = (SX_VALUE **)sx_malloc (parse_system, sizeof (SX_VALUE *));
		if (array->data.array.list == NULL) {
			return sx_new_nil ();
		}
		array->data.array.list[0] = value;
		array->data.array.count = 1;
	}

	return array;
}

int
sxerror (char *str) {
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

sx_script_id
sx_load_file (SX_SYSTEM *system, char *file) {
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

	return sx_new_script (system, NULL, file, parse_block);
}

sx_script_id
sx_load_string (SX_SYSTEM *system, char *str) {
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

	return sx_new_script (system, NULL, NULL, parse_block);
}

sx_thread_id
sx_run_file (SX_SYSTEM *system, char *file, SX_VALUE *argv) {
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
sx_run_string (SX_SYSTEM *system, char *str, SX_VALUE *argv) {
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
