/* A Bison parser, made from grammar.y
   by GNU bison 1.34.  */

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
# define	TADDASSIGN	280
# define	TSUBASSIGN	281
# define	TINCREMENT	282
# define	TDECREMENT	283
# define	TLENGTH	284
# define	TTHREAD	285
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
# define	TSTEP	296
# define	TTO	297
# define	TISA	298
# define	CUNARY	299
# define	CPARAN	300
# define	TTYPE	301

#line 28 "grammar.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	#include "scriptix.h"

	#define COMP_STACK_SIZE 50

	int parser_stack_size = 0;
	int parser_stack_top = 0;
	VALUE **parser_stack = NULL;

	VALUE *parser_top (void);
	void parser_push (VALUE *value);
	void parser_pop (void);

	VALUE *name_list[20];
	int name_ptr = 0;
	VALUE *get_dup_name (char *name);

	VALUE *append_to_array (VALUE *array, VALUE *value);
	NODE *append_to_expr (NODE *expr, NODE *node);

	int sxerror (char *);
	int sxlex (void);

	SYSTEM *parse_system = NULL;
	VALUE *parse_block = NULL;

	extern FILE *sxin;
	int sxparse (void);

	VALUE *temp_val;

	#define pushv(v) (add_value (parse_system, parser_top (), (v)))
	#define pushn(o,c) (add_stmt (parse_system, parser_top (), (o), (c)))

#line 67 "grammar.y"
#ifndef YYSTYPE
typedef union {
	VALUE *value;
	char name[MAX_NAME_LEN + 1];
	unsigned int count;
} yystype;
# define YYSTYPE yystype
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		199
#define	YYFLAG		-32768
#define	YYNTBASE	65

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 301 ? yytranslate[x] : 92)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,     2,     2,     2,     2,
      58,    59,    50,    48,    60,    49,    56,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,     2,
      46,    44,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,     2,    64,     2,     2,     2,     2,
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
      36,    37,    38,    39,    40,    41,    42,    43,    47,    53,
      54,    55
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,     7,    10,    11,    13,    16,
      19,    23,    25,    26,    31,    33,    36,    37,    40,    41,
      43,    46,    49,    53,    55,    56,    61,    62,    67,    68,
      77,    78,    80,    84,    85,    86,    89,    91,    95,    99,
     103,   107,   111,   115,   118,   121,   125,   129,   133,   137,
     141,   145,   149,   153,   157,   162,   169,   175,   179,   183,
     186,   189,   192,   195,   200,   205,   209,   214,   222,   229,
     236,   240,   243,   248,   249,   257,   262,   268,   276,   282,
     288,   296,   297,   308,   310,   313,   316,   318,   320,   323,
     326,   330,   334,   336,   338,   340,   344,   346,   348,   350,
     352
};
static const short yyrhs[] =
{
      70,     0,     0,    67,    70,     0,     0,    69,    86,     0,
       0,    71,     0,    73,    71,     0,    71,    73,     0,    73,
      71,    73,     0,    86,     0,     0,    71,    73,    72,    86,
       0,     6,     0,    73,     6,     0,     0,    75,    76,     0,
       0,    77,     0,    73,    77,     0,    77,    73,     0,    73,
      77,    73,     0,    79,     0,     0,    77,    73,    78,    79,
       0,     0,    80,    90,    44,    86,     0,     0,    81,    19,
      90,    58,    83,    59,    66,    10,     0,     0,    86,     0,
      82,    60,    86,     0,     0,     0,    84,    85,     0,     5,
       0,    85,    60,     5,     0,    86,    48,    86,     0,    86,
      49,    86,     0,    86,    50,    86,     0,    86,    51,    86,
       0,    58,    86,    59,     0,    49,    86,     0,    52,    86,
       0,    86,    13,    86,     0,    86,    14,    86,     0,    86,
      45,    86,     0,    86,    46,    86,     0,    86,    17,    86,
       0,    86,    15,    86,     0,    86,    16,    86,     0,    86,
      24,    86,     0,    90,    44,    86,     0,    91,    90,    44,
      86,     0,    86,    57,    86,    61,    44,    86,     0,    86,
      56,    90,    44,    86,     0,    90,    26,    86,     0,    90,
      27,    86,     0,    90,    28,     0,    28,    90,     0,    90,
      29,     0,    29,    90,     0,    30,    58,    86,    59,     0,
      55,    58,    86,    59,     0,    86,    47,    86,     0,    86,
      58,    82,    59,     0,    19,    90,    58,    83,    59,    66,
      10,     0,    19,    58,    83,    59,    66,    10,     0,    86,
      41,    90,    58,    82,    59,     0,    86,    56,    90,     0,
      33,    86,     0,    32,    90,    74,    10,     0,     0,    32,
      90,    62,    90,    87,    74,    10,     0,    86,    57,    86,
      61,     0,     7,    86,     8,    66,    10,     0,     7,    86,
       8,    66,     9,    66,    10,     0,    11,    68,    12,    66,
      10,     0,    38,    66,    37,    66,    10,     0,    40,    90,
      39,    86,    12,    66,    10,     0,     0,    40,    90,    39,
      86,    42,     3,    88,    12,    66,    10,     0,    90,     0,
      91,    90,     0,    18,    86,     0,    18,     0,    20,     0,
      20,    86,     0,    36,    86,     0,     3,    25,     3,     0,
      63,    82,    64,     0,    89,     0,     3,     0,     4,     0,
      21,    66,    10,     0,    35,     0,     5,     0,    22,     0,
      23,     0,    31,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    97,   100,   100,   103,   103,   106,   107,   108,   109,
     110,   113,   114,   114,   117,   118,   121,   121,   124,   125,
     126,   127,   128,   131,   132,   132,   135,   135,   136,   136,
     139,   140,   141,   144,   145,   145,   148,   149,   152,   153,
     154,   155,   156,   157,   159,   160,   161,   163,   164,   165,
     166,   167,   168,   170,   171,   172,   173,   175,   176,   177,
     178,   179,   180,   182,   183,   184,   186,   187,   188,   190,
     191,   192,   193,   194,   194,   196,   198,   199,   200,   201,
     206,   207,   207,   209,   210,   212,   213,   214,   215,   216,
     218,   219,   220,   224,   225,   226,   227,   230,   233,   234,
     235
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "TNUM", "TSTR", "TNAME", "TSEP", "TIF", 
  "TTHEN", "TELSE", "TEND", "TWHILE", "TDO", "TAND", "TOR", "TGTE", 
  "TLTE", "TNE", "TRETURN", "TFUNC", "TBREAK", "TBLOCK", "TLOCAL", 
  "TGLOBAL", "TEQUALS", "TRANGE", "TADDASSIGN", "TSUBASSIGN", 
  "TINCREMENT", "TDECREMENT", "TLENGTH", "TTHREAD", "TCLASS", "TNEW", 
  "TUNTIL", "TNIL", "TRAISE", "TRESCUE", "TTRY", "TIN", "TFOR", "TMETHOD", 
  "TSTEP", "TTO", "'='", "'>'", "'<'", "TISA", "'+'", "'-'", "'*'", "'/'", 
  "'!'", "CUNARY", "CPARAN", "TTYPE", "'.'", "'['", "'('", "')'", "','", 
  "']'", "':'", "'{'", "'}'", "program", "block", "@1", "oblock", "@2", 
  "stmts", "stmt_list", "@3", "seps", "cblock", "@4", "cstmts", 
  "cstmt_list", "@5", "cstmt", "@6", "@7", "array_list", "args", "@8", 
  "arg_list", "node", "@9", "@10", "data", "name", "scope", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    65,    67,    66,    69,    68,    70,    70,    70,    70,
      70,    71,    72,    71,    73,    73,    75,    74,    76,    76,
      76,    76,    76,    77,    78,    77,    80,    79,    81,    79,
      82,    82,    82,    83,    84,    83,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    87,    86,    86,    86,    86,    86,    86,
      86,    88,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    89,    89,    89,    89,    90,    91,    91,
      91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     0,     2,     0,     1,     2,     2,
       3,     1,     0,     4,     1,     2,     0,     2,     0,     1,
       2,     2,     3,     1,     0,     4,     0,     4,     0,     8,
       0,     1,     3,     0,     0,     2,     1,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     6,     5,     3,     3,     2,
       2,     2,     2,     4,     4,     3,     4,     7,     6,     6,
       3,     2,     4,     0,     7,     4,     5,     7,     5,     5,
       7,     0,    10,     1,     2,     2,     1,     1,     2,     2,
       3,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       6,    93,    94,    97,    14,     0,     4,    86,     0,    87,
       2,    98,    99,     0,     0,     0,   100,     0,     0,    96,
       0,     2,     0,     0,     0,     0,     0,    30,     1,     7,
       0,    11,    92,    83,     0,     0,     0,     0,     0,    85,
      33,     0,    88,     0,     6,    60,    62,     0,    16,    71,
      89,     0,     0,    43,    44,     0,     0,     0,    31,    12,
      15,     8,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,    59,    61,     0,    84,    90,     2,     2,     5,     0,
       0,    33,    95,     3,     0,     0,     0,    18,     2,     0,
       0,    42,     0,    91,     0,    12,    45,    46,    50,    51,
      49,    52,     0,    47,    48,    65,    38,    39,    40,    41,
      70,     0,     0,    57,    58,    53,     0,     0,     0,     2,
      36,    35,     0,    63,    73,    72,    26,    17,    19,    23,
       0,     0,     0,     0,    64,    32,    13,    30,     0,    75,
      66,    54,     2,    76,    78,     0,     0,     2,    16,    20,
      24,     0,     0,    79,     2,     0,     0,    56,     0,     0,
      68,    37,     0,     0,    24,    26,     0,     0,     0,    81,
      69,    55,    77,    67,    74,    25,    27,    33,    80,     0,
       0,     2,     2,     0,     0,    82,    29,     0,     0,     0
};

static const short yydefgoto[] =
{
     197,    43,    44,    37,    38,    28,    29,   104,    30,    96,
      97,   137,   138,   175,   139,   140,   141,    57,    89,    90,
     131,    31,   158,   189,    32,    33,    34
};

static const short yypact[] =
{
     169,     3,-32768,-32768,-32768,   290,-32768,   290,    -4,   290,
  -32768,-32768,-32768,     1,     1,   -27,-32768,     1,   290,-32768,
     290,-32768,     1,   290,   290,   -24,   290,   290,-32768,    37,
     233,   514,-32768,   -18,     1,    53,   319,    51,   290,   514,
      72,    35,   514,    86,   169,-32768,-32768,   290,    36,    -9,
     514,    63,    64,    -9,    -9,   290,   429,   -40,   514,   128,
  -32768,    37,   290,   290,   290,   290,   290,   290,     1,   290,
     290,   290,   290,   290,   290,   290,     1,   290,   290,   290,
     290,-32768,-32768,   290,    58,-32768,-32768,-32768,   514,    46,
      99,    72,-32768,-32768,   448,     1,    96,    11,-32768,   290,
     495,-32768,   290,-32768,   290,   130,    68,   532,   550,   550,
     -12,   -12,    50,   550,   550,   -12,   103,   103,    -9,    -9,
      66,   365,   -19,   514,   514,   514,   290,    43,   101,-32768,
  -32768,    60,    70,-32768,-32768,-32768,     6,-32768,    37,-32768,
       1,   104,   117,   383,-32768,   514,   514,   290,   290,    87,
  -32768,   514,-32768,-32768,-32768,   122,   141,-32768,-32768,    37,
      17,    91,     1,-32768,-32768,   144,    29,   514,   290,   138,
  -32768,-32768,   142,   145,    45,   132,   290,    98,   148,-32768,
  -32768,   514,-32768,-32768,-32768,-32768,   514,    72,-32768,   150,
     105,-32768,-32768,   156,   159,-32768,-32768,   170,   177,-32768
};

static const short yypgoto[] =
{
  -32768,    -7,-32768,-32768,-32768,   134,   149,-32768,   -26,    23,
  -32768,-32768,    47,-32768,     7,-32768,-32768,   -71,   -86,-32768,
  -32768,    -5,-32768,-32768,-32768,    73,-32768
};


#define	YYLAST		608


static const short yytable[] =
{
      36,     3,    39,    59,    42,   132,     3,   122,    79,    80,
      81,    82,    60,    49,    51,    50,   -26,     4,    53,    54,
     102,    56,    58,    60,   103,   -28,    83,   -21,    35,    68,
     -28,    47,    68,    88,    55,   105,    72,    73,    74,    75,
     150,   102,    94,     4,    76,    77,    78,    76,    77,    78,
     100,    60,   152,   153,    40,   -22,    85,   106,   107,   108,
     109,   110,   111,    87,   113,   114,   115,   116,   117,   118,
     119,   136,   121,    58,   123,   124,   166,   -34,   125,   127,
     128,    41,    63,    64,    65,    66,    45,    46,   180,   102,
      48,   142,    67,    91,   143,    52,    92,   145,    95,   146,
      98,   190,   126,    99,   130,   129,   135,    84,   147,    68,
     148,   154,   160,    69,    70,    71,    72,    73,    74,    75,
     156,   151,   155,   162,    76,    77,    78,   163,    -9,   157,
     -10,   168,   170,   174,    60,   176,    60,    -9,    -9,   -10,
     -10,   112,    58,   167,    68,   169,   171,   179,   182,   120,
     172,   -28,   183,    74,    75,   184,   187,   178,   188,    76,
      77,    78,   191,   181,   192,    -9,   195,   -10,   134,   196,
     198,   186,     1,     2,     3,     4,     5,   199,    93,    61,
       6,   173,   185,   159,   193,   194,     0,     7,     8,     9,
      10,    11,    12,     0,     0,     0,     0,    13,    14,    15,
      16,    17,    18,     0,    19,    20,     0,    21,     0,    22,
       0,     0,     0,   161,     0,     0,     0,     0,    23,     0,
       0,    24,     0,     0,    25,     0,     0,    26,     0,     0,
       0,     0,    27,     0,     0,   177,     1,     2,     3,    60,
       5,     0,     0,     0,     6,     0,     0,     0,     0,     0,
       0,     7,     8,     9,    10,    11,    12,     0,     0,     0,
       0,    13,    14,    15,    16,    17,    18,     0,    19,    20,
       0,    21,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,    23,     0,     0,    24,     0,     0,    25,     0,
       0,    26,     0,     1,     2,     3,    27,     5,     0,     0,
       0,     6,     0,     0,     0,     0,     0,     0,     7,     8,
       9,    10,    11,    12,     0,     0,     0,     0,    13,    14,
      15,    16,    17,    18,     0,    19,    20,    86,    21,     0,
      22,     0,    62,    63,    64,    65,    66,     0,     0,    23,
       0,     0,    24,    67,     0,    25,     0,     0,    26,     0,
       0,     0,     0,    27,     0,     0,     0,     0,     0,     0,
      68,     0,     0,     0,    69,    70,    71,    72,    73,    74,
      75,     0,     0,     0,     0,    76,    77,    78,    62,    63,
      64,    65,    66,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,   164,    62,    63,    64,    65,
      66,     0,     0,     0,     0,     0,    68,    67,     0,     0,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,    76,    77,    78,    68,   165,   149,     0,    69,    70,
      71,    72,    73,    74,    75,     0,     0,     0,     0,    76,
      77,    78,    62,    63,    64,    65,    66,     0,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
       0,    62,    63,    64,    65,    66,     0,     0,     0,     0,
      68,     0,    67,     0,    69,    70,    71,    72,    73,    74,
      75,     0,     0,     0,     0,    76,    77,    78,   101,    68,
       0,     0,     0,    69,    70,    71,    72,    73,    74,    75,
       0,     0,     0,     0,    76,    77,    78,   133,    62,    63,
      64,    65,    66,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,     0,     0,    62,    63,    64,
      65,    66,     0,     0,     0,     0,    68,     0,    67,     0,
      69,    70,    71,    72,    73,    74,    75,    64,    65,    66,
       0,    76,    77,    78,   144,    68,    67,     0,     0,    69,
      70,    71,    72,    73,    74,    75,     0,    66,     0,     0,
      76,    77,    78,    68,    67,     0,     0,    69,    70,    71,
      72,    73,    74,    75,     0,     0,     0,     0,    76,    77,
      78,    68,     0,     0,     0,     0,     0,    71,    72,    73,
      74,    75,     0,     0,     0,     0,    76,    77,    78
};

static const short yycheck[] =
{
       5,     5,     7,    29,     9,    91,     5,    78,    26,    27,
      28,    29,     6,    18,    21,    20,     5,     6,    23,    24,
      60,    26,    27,     6,    64,    19,    44,    10,    25,    41,
      19,    58,    41,    38,    58,    61,    48,    49,    50,    51,
      59,    60,    47,     6,    56,    57,    58,    56,    57,    58,
      55,     6,     9,    10,    58,    10,     3,    62,    63,    64,
      65,    66,    67,    12,    69,    70,    71,    72,    73,    74,
      75,    97,    77,    78,    79,    80,   147,     5,    83,    86,
      87,     8,    14,    15,    16,    17,    13,    14,    59,    60,
      17,    98,    24,    58,    99,    22,    10,   102,    62,   104,
      37,   187,    44,    39,     5,    59,    10,    34,    58,    41,
      44,    10,   138,    45,    46,    47,    48,    49,    50,    51,
      60,   126,   129,    19,    56,    57,    58,    10,     0,    59,
       0,    44,    10,   159,     6,    44,     6,     9,    10,     9,
      10,    68,   147,   148,    41,   152,     5,     3,    10,    76,
     157,    19,    10,    50,    51,    10,    58,   164,    10,    56,
      57,    58,    12,   168,    59,    37,    10,    37,    95,    10,
       0,   176,     3,     4,     5,     6,     7,     0,    44,    30,
      11,   158,   175,   136,   191,   192,    -1,    18,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    -1,    35,    36,    -1,    38,    -1,    40,
      -1,    -1,    -1,   140,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    52,    -1,    -1,    55,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    63,    -1,    -1,   162,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    19,    20,    21,    22,    23,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    -1,    35,    36,
      -1,    38,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    52,    -1,    -1,    55,    -1,
      -1,    58,    -1,     3,     4,     5,    63,     7,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    -1,    35,    36,     8,    38,    -1,
      40,    -1,    13,    14,    15,    16,    17,    -1,    -1,    49,
      -1,    -1,    52,    24,    -1,    55,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    41,    24,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    41,    42,    61,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      41,    -1,    24,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    41,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    41,    -1,    24,    -1,
      45,    46,    47,    48,    49,    50,    51,    15,    16,    17,
      -1,    56,    57,    58,    59,    41,    24,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    -1,    17,    -1,    -1,
      56,    57,    58,    41,    24,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    41,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    56,    57,    58
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

/* Relocate the TYPE STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Type, Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	yymemcpy ((char *) yyptr, (char *) (Stack),			\
		  yysize * (YYSIZE_T) sizeof (Type));			\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (Type) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


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

#if ! defined (yyoverflow) && ! defined (yymemcpy)
# if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#  define yymemcpy __builtin_memcpy
# else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
#  if defined (__STDC__) || defined (__cplusplus)
yymemcpy (char *yyto, const char *yyfrom, YYSIZE_T yycount)
#  else
yymemcpy (yyto, yyfrom, yycount)
     char *yyto;
     const char *yyfrom;
     YYSIZE_T yycount;
#  endif
{
  register const char *yyf = yyfrom;
  register char *yyt = yyto;
  register YYSIZE_T yyi = yycount;

  while (yyi-- != 0)
    *yyt++ = *yyf++;
}
# endif
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

#line 319 "/usr/share/bison/bison.simple"


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
	YYSTACK_RELOCATE (short, yyss);
	YYSTACK_RELOCATE (YYSTYPE, yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (YYLTYPE, yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
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
#line 97 "grammar.y"
{}
    break;
case 2:
#line 100 "grammar.y"
{ parser_push (new_block (parse_system)); }
    break;
case 3:
#line 100 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 4:
#line 103 "grammar.y"
{ parser_push (new_block (parse_system)); }
    break;
case 5:
#line 103 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 7:
#line 107 "grammar.y"
{}
    break;
case 8:
#line 108 "grammar.y"
{}
    break;
case 9:
#line 109 "grammar.y"
{}
    break;
case 10:
#line 110 "grammar.y"
{}
    break;
case 11:
#line 113 "grammar.y"
{ yyval.count = 1; }
    break;
case 12:
#line 114 "grammar.y"
{ if (yyvsp[-1].count > 0) { pushn (OP_POP, 0); } yyval.count = yyvsp[-1].count + 1; }
    break;
case 16:
#line 121 "grammar.y"
{ parser_push (new_block (parse_system)); }
    break;
case 17:
#line 121 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 19:
#line 125 "grammar.y"
{}
    break;
case 20:
#line 126 "grammar.y"
{}
    break;
case 21:
#line 127 "grammar.y"
{}
    break;
case 22:
#line 128 "grammar.y"
{}
    break;
case 23:
#line 131 "grammar.y"
{ yyval.count = 1; }
    break;
case 24:
#line 132 "grammar.y"
{ if (yyvsp[-1].count > 0) { pushn (OP_POP, 0); } yyval.count = yyvsp[-1].count + 1; }
    break;
case 26:
#line 135 "grammar.y"
{ pushv (new_num (SCOPE_LOCAL)); }
    break;
case 27:
#line 135 "grammar.y"
{ pushn (OP_ASSIGN, 3); }
    break;
case 28:
#line 136 "grammar.y"
{ pushv (new_num (SCOPE_LOCAL)); }
    break;
case 29:
#line 136 "grammar.y"
{ pushn (OP_NEWFUNC, 2); pushn (OP_ASSIGN, 3); }
    break;
case 30:
#line 139 "grammar.y"
{ yyval.count = 0; }
    break;
case 31:
#line 140 "grammar.y"
{ yyval.count = 1; }
    break;
case 32:
#line 141 "grammar.y"
{ yyval.count = yyvsp[-2].count + 1; }
    break;
case 33:
#line 144 "grammar.y"
{ pushv (new_nil ()); }
    break;
case 34:
#line 145 "grammar.y"
{ parser_push (new_array (parse_system, 0, NULL)); }
    break;
case 35:
#line 145 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 36:
#line 148 "grammar.y"
{ append_to_array (parser_top (), get_dup_name (yyvsp[0].name)); }
    break;
case 37:
#line 149 "grammar.y"
{ append_to_array (parser_top (), get_dup_name (yyvsp[0].name)); }
    break;
case 38:
#line 152 "grammar.y"
{ pushn (OP_ADD, 2); }
    break;
case 39:
#line 153 "grammar.y"
{ pushn (OP_SUBTRACT, 2); }
    break;
case 40:
#line 154 "grammar.y"
{ pushn (OP_MULTIPLY, 2); }
    break;
case 41:
#line 155 "grammar.y"
{ pushn (OP_DIVIDE, 2); }
    break;
case 43:
#line 157 "grammar.y"
{ pushn (OP_NEGATE, 1); }
    break;
case 44:
#line 159 "grammar.y"
{ pushn (OP_NOT, 1); }
    break;
case 45:
#line 160 "grammar.y"
{ pushn (OP_AND, 2); }
    break;
case 46:
#line 161 "grammar.y"
{ pushn (OP_OR, 2); }
    break;
case 47:
#line 163 "grammar.y"
{ pushn (OP_GT, 2); }
    break;
case 48:
#line 164 "grammar.y"
{ pushn (OP_LT, 2); }
    break;
case 49:
#line 165 "grammar.y"
{ pushn (OP_NEQUAL, 2); }
    break;
case 50:
#line 166 "grammar.y"
{ pushn (OP_GTE, 2); }
    break;
case 51:
#line 167 "grammar.y"
{ pushn (OP_LTE, 2); }
    break;
case 52:
#line 168 "grammar.y"
{ pushn (OP_EQUAL, 2); }
    break;
case 53:
#line 170 "grammar.y"
{ pushn (OP_ASSIGN, 2); }
    break;
case 54:
#line 171 "grammar.y"
{ pushn (OP_ASSIGN, 3); }
    break;
case 55:
#line 172 "grammar.y"
{ pushn (OP_SETINDEX, 3); }
    break;
case 56:
#line 173 "grammar.y"
{ pushn (OP_SETMEMBER, 3); }
    break;
case 57:
#line 175 "grammar.y"
{ pushn (OP_PREINCREMENT, 2); }
    break;
case 58:
#line 176 "grammar.y"
{ pushn (OP_PREDECREMENT, 2); }
    break;
case 59:
#line 177 "grammar.y"
{ pushn (OP_POSTINCREMENT, 1); }
    break;
case 60:
#line 178 "grammar.y"
{ pushn (OP_PREINCREMENT, 1); }
    break;
case 61:
#line 179 "grammar.y"
{ pushn (OP_POSTDECREMENT, 1); }
    break;
case 62:
#line 180 "grammar.y"
{ pushn (OP_PREDECREMENT, 1); }
    break;
case 63:
#line 182 "grammar.y"
{ pushn (OP_SIZEOF, 1); }
    break;
case 64:
#line 183 "grammar.y"
{ pushn (OP_TYPEOF, 1); }
    break;
case 65:
#line 184 "grammar.y"
{ pushn (OP_ISA, 2); }
    break;
case 66:
#line 186 "grammar.y"
{ pushn (OP_CALL, 1 + yyvsp[-1].count); }
    break;
case 67:
#line 187 "grammar.y"
{ pushn (OP_NEWFUNC, 2); pushn (OP_ASSIGN, 2); }
    break;
case 68:
#line 188 "grammar.y"
{ pushn (OP_NEWFUNC, 2); }
    break;
case 69:
#line 190 "grammar.y"
{ pushn (OP_METHOD, 2 + yyvsp[-1].count); }
    break;
case 70:
#line 191 "grammar.y"
{ pushn (OP_MEMBER, 2); }
    break;
case 71:
#line 192 "grammar.y"
{ pushn (OP_NEWINSTANCE, 1); }
    break;
case 72:
#line 193 "grammar.y"
{ pushn (OP_NEWCLASS, 1); pushn (OP_ASSIGN, 2); }
    break;
case 73:
#line 194 "grammar.y"
{ pushn (OP_LOOKUP, 1); }
    break;
case 74:
#line 194 "grammar.y"
{ pushn (OP_NEWCLASS, 2); pushn (OP_ASSIGN, 2); }
    break;
case 75:
#line 196 "grammar.y"
{ pushn (OP_INDEX, 2); }
    break;
case 76:
#line 198 "grammar.y"
{ pushv (new_nil ()); pushn (OP_IF, 3); }
    break;
case 77:
#line 199 "grammar.y"
{ pushn (OP_IF, 3); }
    break;
case 78:
#line 200 "grammar.y"
{ pushn (OP_WHILE, 2); }
    break;
case 79:
#line 201 "grammar.y"
{ pushn (OP_TRY, 2); }
    break;
case 80:
#line 206 "grammar.y"
{ pushn (OP_FOR, 3); }
    break;
case 81:
#line 207 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 82:
#line 207 "grammar.y"
{ pushn (OP_FOR, 4); }
    break;
case 83:
#line 209 "grammar.y"
{ pushn (OP_LOOKUP, 1); }
    break;
case 84:
#line 210 "grammar.y"
{ pushn (OP_LOOKUP, 2); }
    break;
case 85:
#line 212 "grammar.y"
{ pushn (OP_RETURN, 1); }
    break;
case 86:
#line 213 "grammar.y"
{ pushn (OP_RETURN, 0); }
    break;
case 87:
#line 214 "grammar.y"
{ pushn (OP_BREAK, 0); }
    break;
case 88:
#line 215 "grammar.y"
{ pushn (OP_BREAK, 1); }
    break;
case 89:
#line 216 "grammar.y"
{ pushn (OP_RAISE, 0); }
    break;
case 90:
#line 218 "grammar.y"
{ pushv (yyvsp[-2].value); pushv (yyvsp[0].value); pushn (OP_NEWRANGE, 2); }
    break;
case 91:
#line 219 "grammar.y"
{ pushn (OP_NEWARRAY, yyvsp[-1].count); }
    break;
case 93:
#line 224 "grammar.y"
{ pushv (yyvsp[0].value);  }
    break;
case 94:
#line 225 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 96:
#line 227 "grammar.y"
{ pushv (new_nil ()); }
    break;
case 97:
#line 230 "grammar.y"
{ pushv (get_dup_name (yyvsp[0].name)); }
    break;
case 98:
#line 233 "grammar.y"
{ pushv (new_num (SCOPE_LOCAL)); }
    break;
case 99:
#line 234 "grammar.y"
{ pushv (new_num (SCOPE_GLOBAL)); }
    break;
case 100:
#line 235 "grammar.y"
{ pushv (new_num (SCOPE_THREAD)); }
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
#line 238 "grammar.y"


/* value stack */
VALUE *
parser_top (void) {
	if (parser_stack_top > 0) {
		return parser_stack[parser_stack_top - 1];
	}

	return NULL;
}

void
parser_push (VALUE *value) {
	VALUE **new_stack;
	if (parser_stack_top >= parser_stack_size) {
		if (parser_stack != NULL) {
			new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + 20) * sizeof (VALUE **));
		} else {
			new_stack = sx_malloc (parse_system, (parser_stack_size + 20) * sizeof (VALUE **));
		}
		if (new_stack == NULL) {
			/* FIXME: error */
			return;
		}
		sx_free (parser_stack);
		parser_stack = new_stack;
		parser_stack_size += 20;
	}

	parser_stack[parser_stack_top ++] = value;
}

void
parser_pop (void) {
	if (parser_stack_top > 0) {
		-- parser_stack_top;
	}
}


VALUE *
append_to_array (VALUE *array, VALUE *value) {
	VALUE **nlist;

	if (!IS_ARRAY (array)) {
		return new_nil ();
	}

	if (array->data.array.count > 0) {
		nlist = (VALUE **)sx_malloc (parse_system, (array->data.array.count + 1) * sizeof (VALUE *));
		if (nlist == NULL) {
			return new_nil ();
		}
		memcpy (nlist, array->data.array.list, array->data.array.count * sizeof (VALUE *));
		sx_free (array->data.array.list);
		array->data.array.list = nlist;
		array->data.array.list[array->data.array.count] = value;
		array->data.array.count += 1;
	} else {
		array->data.array.list = (VALUE **)sx_malloc (parse_system, sizeof (VALUE *));
		if (array->data.array.list == NULL) {
			return new_nil ();
		}
		array->data.array.list[0] = value;
		array->data.array.count = 1;
	}

	return array;
}

VALUE *
get_dup_name (char *name) {
	int i;
	VALUE *ret;
	for (i = 0; i < 20 && name_list[i] != NULL; ++ i) {
		if (!strcasecmp (name, TO_STR (name_list[i]))) {
			return name_list[i];
		}
	}
	ret = new_str (parse_system, name);
	name_list[name_ptr] = ret;
	if (++ name_ptr >= 20) {
		name_ptr = 0;
	}
	return ret;
}

/* global vars */
unsigned int parse_lineno = 1;

int
sxerror (char *str) {
	fprintf (stderr, "ERROR: line %d: %s\n", parse_lineno, str);
	return 1;
}

int
sxwrap (void) {
	return 1;
}

void
cleanup_parser (void) {
	unsigned int i;

	for (i = 0; i < parser_stack_top; i ++) {
		free_value (parser_stack[i]);
	}
	free (parser_stack);
	parser_stack = NULL;
	parser_stack_top = 0;
	parser_stack_size = 0;
}

VALUE *
load_file (SYSTEM *system, char *file) {
	int ret, flags, i;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			/* FIXME: error message */
			return NULL;
		}
	}

	for (i = 0; i < 20; ++ i) {
		name_list[i] = NULL;
	}

	parse_system = system;
	parse_block = new_block (system);
	if (parse_block == NULL) {
		if (sxin != NULL) {
			fclose (sxin);
		}
		return NULL;
	}

	flags = system->flags;
	system->flags |= SFLAG_GCOFF;
	parser_push (parse_block);
	ret = sxparse ();
	parser_pop ();
	system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (ret) {
		cleanup_parser ();
		return NULL;
	}

	lock_value (parse_block);
	run_gc (system);
	unlock_value (parse_block);

	cleanup_parser ();

	return parse_block;
}
