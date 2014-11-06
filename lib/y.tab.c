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
# define	TTHREAD	286
# define	TCLASS	287
# define	TNEW	288
# define	TUNTIL	289
# define	TNIL	290
# define	TRAISE	291
# define	TRESCUE	292
# define	TTRY	293
# define	TIN	294
# define	TFOR	295
# define	TMETHOD	296
# define	TISA	297
# define	TTYPE	298
# define	CUNARY	299

#line 28 "grammar.y"

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	#include "scriptix.h"

	#define COMP_STACK_SIZE 20
	#define NAME_LIST_SIZE 20

	int parser_stack_size = 0;
	int parser_stack_top = 0;
	VALUE **parser_stack = NULL;

	VALUE *parser_top (void);
	void parser_push (VALUE *value);
	void parser_pop (void);

	VALUE *append_to_array (VALUE *array, VALUE *value);
	NODE *append_to_expr (NODE *expr, NODE *node);

	int sxerror (char *);
	int sxlex (void);

	SYSTEM *parse_system = NULL;
	VALUE *parse_block = NULL;

	extern FILE *sxin;
	int sxparse (void);

	VALUE *temp_val;

	#define pushv(v) (sx_add_value (parse_system, parser_top (), (v)))
	#define pushn(o,c) (sx_add_stmt (parse_system, parser_top (), (o), (c)))

#line 64 "grammar.y"
#ifndef YYSTYPE
typedef union {
	VALUE *value;
	char name[SX_MAX_NAME + 1];
	unsigned int count;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		216
#define	YYFLAG		-32768
#define	YYNTBASE	63

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 299 ? yytranslate[x] : 93)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,     2,     2,     2,     2,     2,     2,
      56,    57,    49,    47,    58,    48,    54,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,     2,
      45,    43,    44,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    59,     2,     2,     2,     2,     2,     2,
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
      36,    37,    38,    39,    40,    41,    42,    46,    51,    53
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,     7,    10,    11,    13,    16,
      19,    23,    25,    26,    31,    33,    36,    37,    40,    41,
      43,    46,    49,    53,    55,    56,    61,    62,    67,    68,
      77,    78,    80,    84,    85,    86,    89,    91,    95,    96,
      99,   102,   107,   111,   115,   119,   123,   127,   130,   133,
     137,   141,   145,   149,   153,   157,   161,   165,   169,   174,
     181,   187,   191,   195,   198,   201,   204,   207,   212,   217,
     221,   226,   234,   241,   248,   252,   255,   260,   261,   269,
     274,   280,   288,   294,   301,   307,   311,   319,   320,   331,
     333,   336,   339,   341,   343,   346,   349,   353,   357,   359,
     361,   363,   367,   369,   371,   373,   375
};
static const short yyrhs[] =
{
      68,     0,     0,    65,    68,     0,     0,    67,    87,     0,
       0,    69,     0,    71,    69,     0,    69,    71,     0,    71,
      69,    71,     0,    87,     0,     0,    69,    71,    70,    87,
       0,     6,     0,    71,     6,     0,     0,    73,    74,     0,
       0,    75,     0,    71,    75,     0,    75,    71,     0,    71,
      75,    71,     0,    77,     0,     0,    75,    71,    76,    77,
       0,     0,    78,    91,    43,    87,     0,     0,    79,    19,
      91,    56,    81,    57,    64,    10,     0,     0,    87,     0,
      80,    58,    87,     0,     0,     0,    82,    83,     0,     5,
       0,    83,    58,     5,     0,     0,    85,    86,     0,     5,
       5,     0,    83,    58,     5,     5,     0,    87,    47,    87,
       0,    87,    48,    87,     0,    87,    49,    87,     0,    87,
      50,    87,     0,    56,    87,    57,     0,    48,    87,     0,
      52,    87,     0,    87,    13,    87,     0,    87,    14,    87,
       0,    87,    44,    87,     0,    87,    45,    87,     0,    87,
      17,    87,     0,    87,    15,    87,     0,    87,    16,    87,
       0,    87,    24,    87,     0,    91,    43,    87,     0,    92,
      91,    43,    87,     0,    87,    55,    87,    59,    43,    87,
       0,    87,    54,    91,    43,    87,     0,    91,    27,    87,
       0,    91,    28,    87,     0,    91,    29,     0,    29,    91,
       0,    91,    30,     0,    30,    91,     0,    31,    56,    87,
      57,     0,    51,    56,    87,    57,     0,    87,    46,    87,
       0,    87,    56,    80,    57,     0,    19,    91,    56,    81,
      57,    64,    10,     0,    19,    56,    81,    57,    64,    10,
       0,    87,    42,    91,    56,    80,    57,     0,    87,    54,
      91,     0,    34,    87,     0,    33,    91,    72,    10,     0,
       0,    33,    91,    60,    91,    88,    72,    10,     0,    87,
      55,    87,    59,     0,     7,    87,     8,    64,    10,     0,
       7,    87,     8,    64,     9,    64,    10,     0,    11,    66,
      12,    64,    10,     0,    39,    64,    38,    84,    64,    10,
       0,    35,    66,    12,    64,    10,     0,    12,    64,    10,
       0,    41,    91,    40,    87,    12,    64,    10,     0,     0,
      41,    91,    40,    87,    26,     3,    89,    12,    64,    10,
       0,    91,     0,    92,    91,     0,    18,    87,     0,    18,
       0,    20,     0,    20,    87,     0,    37,    87,     0,    87,
      25,    87,     0,    61,    80,    62,     0,    90,     0,     3,
       0,     4,     0,    21,    64,    10,     0,    36,     0,     5,
       0,    22,     0,    23,     0,    32,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    94,    97,    97,   100,   100,   103,   104,   105,   106,
     107,   110,   111,   111,   114,   115,   118,   118,   121,   122,
     123,   124,   125,   128,   129,   129,   132,   132,   133,   133,
     136,   137,   138,   141,   142,   142,   145,   146,   149,   149,
     152,   153,   156,   157,   158,   159,   160,   161,   163,   164,
     165,   167,   168,   169,   170,   171,   172,   174,   175,   176,
     177,   179,   180,   181,   182,   183,   184,   186,   187,   188,
     190,   191,   192,   194,   195,   196,   197,   198,   198,   200,
     202,   203,   204,   205,   206,   207,   208,   209,   209,   211,
     212,   214,   215,   216,   217,   218,   220,   221,   222,   226,
     227,   228,   229,   232,   235,   236,   237
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
  "TINCREMENT", "TDECREMENT", "TLENGTH", "TTHREAD", "TCLASS", "TNEW", 
  "TUNTIL", "TNIL", "TRAISE", "TRESCUE", "TTRY", "TIN", "TFOR", "TMETHOD", 
  "'='", "'>'", "'<'", "TISA", "'+'", "'-'", "'*'", "'/'", "TTYPE", "'!'", 
  "CUNARY", "'.'", "'['", "'('", "')'", "','", "']'", "':'", "'{'", "'}'", 
  "program", "block", "@1", "oblock", "@2", "stmts", "stmt_list", "@3", 
  "seps", "cblock", "@4", "cstmts", "cstmt_list", "@5", "cstmt", "@6", 
  "@7", "array_list", "args", "@8", "arg_list", "errors", "@9", 
  "error_list", "node", "@10", "@11", "data", "name", "scope", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    63,    65,    64,    67,    66,    68,    68,    68,    68,
      68,    69,    70,    69,    71,    71,    73,    72,    74,    74,
      74,    74,    74,    75,    76,    75,    78,    77,    79,    77,
      80,    80,    80,    81,    82,    81,    83,    83,    85,    84,
      86,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    89,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    90,
      90,    90,    90,    91,    92,    92,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     0,     2,     0,     1,     2,     2,
       3,     1,     0,     4,     1,     2,     0,     2,     0,     1,
       2,     2,     3,     1,     0,     4,     0,     4,     0,     8,
       0,     1,     3,     0,     0,     2,     1,     3,     0,     2,
       2,     4,     3,     3,     3,     3,     3,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     6,
       5,     3,     3,     2,     2,     2,     2,     4,     4,     3,
       4,     7,     6,     6,     3,     2,     4,     0,     7,     4,
       5,     7,     5,     6,     5,     3,     7,     0,    10,     1,
       2,     2,     1,     1,     2,     2,     3,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       6,    99,   100,   103,    14,     0,     4,     2,    92,     0,
      93,     2,   104,   105,     0,     0,     0,   106,     0,     0,
       4,   102,     0,     2,     0,     0,     0,     0,     0,    30,
       1,     7,     0,    11,    98,    89,     0,     0,     0,     0,
       0,     6,    91,    33,     0,    94,     0,    64,    66,     0,
      16,    75,     0,    95,     0,     0,    47,     0,    48,     0,
       0,    31,    12,    15,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,    63,    65,     0,    90,     2,
       2,     5,    85,     3,     0,     0,    33,   101,     0,     0,
       0,    18,     2,    38,     0,     0,    46,     0,    97,     0,
      12,    49,    50,    54,    55,    53,    56,    96,     0,    51,
      52,    69,    42,    43,    44,    45,    74,     0,     0,    61,
      62,    57,     0,     0,     0,     2,    36,    35,     0,    67,
      77,    76,    26,    17,    19,    23,     0,     0,     0,     2,
       0,     0,    68,    32,    13,    30,     0,    79,    70,    58,
       2,    80,    82,     0,     0,     2,    16,    20,    24,     0,
       0,    84,     0,    36,     0,    39,     2,     0,     0,    60,
       0,     0,    72,    37,     0,     0,    24,    26,     0,     0,
      83,    40,     0,     0,    87,    73,    59,    81,    71,    78,
      25,    27,    33,    37,    86,     0,     0,    41,     2,     2,
       0,     0,    88,    29,     0,     0,     0
};

static const short yydefgoto[] =
{
     214,    40,    41,    38,    39,    30,    31,   109,    32,   100,
     101,   143,   144,   187,   145,   146,   147,    60,    94,    95,
     137,   149,   150,   175,    33,   166,   205,    34,    35,    36
};

static const short yypact[] =
{
     182,-32768,-32768,-32768,-32768,   296,-32768,-32768,   296,    -1,
     296,-32768,-32768,-32768,     8,     8,   -36,-32768,     8,   296,
  -32768,-32768,   296,-32768,     8,   296,   -28,   296,   296,   296,
  -32768,    25,   241,   539,-32768,   -21,     8,   326,    21,   296,
      32,   182,   539,    51,   -19,   539,    49,-32768,-32768,   296,
      17,    27,    53,   539,    29,    40,     7,   296,     7,   433,
     -37,   539,     5,-32768,    25,   296,   296,   296,   296,   296,
     296,   296,     8,   296,   296,   296,   296,   296,   296,   296,
       8,   296,   296,   296,   296,-32768,-32768,   296,    56,-32768,
  -32768,   539,-32768,-32768,    48,    99,    51,-32768,   478,     8,
      97,    11,-32768,-32768,   296,   494,-32768,   296,-32768,   296,
      26,   554,   590,   122,   122,   311,   311,     7,    54,   122,
     122,   311,   106,   106,    27,    27,    68,   370,   -39,   539,
     539,   539,   296,    30,   102,-32768,-32768,    55,    58,-32768,
  -32768,-32768,     4,-32768,    25,-32768,     8,    98,   108,-32768,
     114,   418,-32768,   539,   539,   296,   296,    77,-32768,   539,
  -32768,-32768,-32768,   111,   117,-32768,-32768,    25,    47,    82,
       8,-32768,   119,   125,    69,-32768,-32768,   129,    16,   539,
     296,   123,-32768,-32768,   124,   126,    60,   121,   296,    85,
  -32768,-32768,   137,   133,-32768,-32768,   539,-32768,-32768,-32768,
  -32768,   539,    51,   139,-32768,   138,    88,-32768,-32768,-32768,
     142,   143,-32768,-32768,   157,   158,-32768
};

static const short yypgoto[] =
{
  -32768,   -11,-32768,   146,-32768,   118,   131,-32768,   -30,     1,
  -32768,-32768,    31,-32768,    -8,-32768,-32768,   -80,   -93,-32768,
      33,-32768,-32768,-32768,    19,-32768,-32768,-32768,    36,-32768
};


#define	YYLAST		646


static const short yytable[] =
{
      46,    62,   128,   138,     3,    -9,    83,    84,    85,    86,
      63,    63,    54,     3,    -9,    -9,   -26,     4,   158,   107,
      49,   107,    87,   -28,    37,   108,   -10,    42,    57,    45,
     -28,     4,    63,    90,   110,   -10,   -10,    96,    51,   160,
     161,    53,    92,    -9,    56,    44,    58,    59,    61,    72,
      47,    48,    71,    63,    50,    43,   -34,   -21,    91,    97,
      55,    80,    81,    82,   -10,   102,    63,   103,    98,    72,
     -22,   142,    88,   195,   107,   178,   105,    99,   133,   134,
     104,    80,    81,    82,   111,   112,   113,   114,   115,   116,
     117,   148,   119,   120,   121,   122,   123,   124,   125,   132,
     127,    61,   129,   130,   136,   135,   131,   141,   118,   206,
     155,   156,   162,   164,   168,   165,   126,   170,   171,   173,
     180,   182,   183,   151,   163,   188,   153,   192,   154,   190,
     191,    71,   194,   197,   198,   140,   199,   186,   172,    69,
     -28,   202,   203,   204,   207,   209,    70,    71,    72,   181,
     208,   159,   212,   213,   184,    78,    79,   215,   216,    93,
      80,    81,    82,    64,    72,   193,    52,   185,    75,    76,
      77,    78,    79,   167,    61,   179,    80,    81,    82,   200,
       0,     0,   169,   174,     0,     1,     2,     3,     4,     5,
       0,     0,     0,     6,     7,     0,     0,   210,   211,   196,
       8,     9,    10,    11,    12,    13,   189,   201,     0,     0,
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       0,    23,     0,    24,     0,     0,     0,     0,     0,     0,
      25,     0,     0,    26,    27,     0,     0,     0,    28,     0,
       0,     0,     0,    29,     1,     2,     3,    63,     5,     0,
       0,     0,     6,     7,     0,     0,     0,     0,     0,     8,
       9,    10,    11,    12,    13,     0,     0,     0,     0,     0,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     0,
      23,     0,    24,     0,     0,     0,     0,     0,     0,    25,
       0,     0,    26,    27,     0,     0,     0,    28,     0,     1,
       2,     3,    29,     5,     0,     0,     0,     6,     7,     0,
       0,     0,     0,     0,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    89,    23,    71,    24,     0,    65,
      66,    67,    68,    69,    25,     0,     0,    26,    27,     0,
      70,    71,    28,    72,     0,     0,     0,    29,    76,    77,
      78,    79,     0,     0,     0,    80,    81,    82,    72,     0,
      73,    74,    75,    76,    77,    78,    79,     0,     0,     0,
      80,    81,    82,    65,    66,    67,    68,    69,     0,     0,
       0,     0,     0,     0,    70,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    72,     0,    73,    74,    75,    76,    77,    78,
      79,     0,     0,     0,    80,    81,    82,     0,     0,   157,
     176,    65,    66,    67,    68,    69,     0,     0,     0,     0,
       0,     0,    70,    71,   177,     0,    65,    66,    67,    68,
      69,     0,     0,     0,     0,     0,     0,    70,    71,     0,
      72,     0,    73,    74,    75,    76,    77,    78,    79,     0,
       0,     0,    80,    81,    82,    72,     0,    73,    74,    75,
      76,    77,    78,    79,     0,     0,     0,    80,    81,    82,
     106,    65,    66,    67,    68,    69,     0,     0,     0,     0,
       0,     0,    70,    71,     0,     0,     0,    65,    66,    67,
      68,    69,     0,     0,     0,     0,     0,     0,    70,    71,
      72,     0,    73,    74,    75,    76,    77,    78,    79,     0,
       0,     0,    80,    81,    82,   139,    72,     0,    73,    74,
      75,    76,    77,    78,    79,     0,     0,     0,    80,    81,
      82,   152,    65,    66,    67,    68,    69,     0,     0,     0,
       0,     0,     0,    70,    71,     0,     0,     0,    66,    67,
      68,    69,     0,     0,     0,     0,     0,     0,    70,    71,
       0,    72,     0,    73,    74,    75,    76,    77,    78,    79,
       0,     0,     0,    80,    81,    82,    72,     0,    73,    74,
      75,    76,    77,    78,    79,    67,    68,    69,    80,    81,
      82,     0,     0,     0,    70,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    72,     0,    73,    74,    75,    76,    77,    78,
      79,     0,     0,     0,    80,    81,    82
};

static const short yycheck[] =
{
      11,    31,    82,    96,     5,     0,    27,    28,    29,    30,
       6,     6,    23,     5,     9,    10,     5,     6,    57,    58,
      56,    58,    43,    19,     5,    62,     0,     8,    56,    10,
      19,     6,     6,    12,    64,     9,    10,    56,    19,     9,
      10,    22,    10,    38,    25,     9,    27,    28,    29,    42,
      14,    15,    25,     6,    18,    56,     5,    10,    39,    10,
      24,    54,    55,    56,    38,    12,     6,    38,    49,    42,
      10,   101,    36,    57,    58,   155,    57,    60,    89,    90,
      40,    54,    55,    56,    65,    66,    67,    68,    69,    70,
      71,   102,    73,    74,    75,    76,    77,    78,    79,    43,
      81,    82,    83,    84,     5,    57,    87,    10,    72,   202,
      56,    43,    10,    58,   144,    57,    80,    19,    10,     5,
      43,    10,     5,   104,   135,    43,   107,    58,   109,    10,
       5,    25,     3,    10,    10,    99,    10,   167,   149,    17,
      19,    56,     5,    10,     5,    57,    24,    25,    42,   160,
      12,   132,    10,    10,   165,    49,    50,     0,     0,    41,
      54,    55,    56,    32,    42,   176,    20,   166,    46,    47,
      48,    49,    50,   142,   155,   156,    54,    55,    56,   187,
      -1,    -1,   146,   150,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,   208,   209,   180,
      18,    19,    20,    21,    22,    23,   170,   188,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    39,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    51,    52,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    61,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    18,
      19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    51,    52,    -1,    -1,    -1,    56,    -1,     3,
       4,     5,    61,     7,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,    -1,    -1,    18,    19,    20,    21,    22,    23,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     8,    39,    25,    41,    -1,    13,
      14,    15,    16,    17,    48,    -1,    -1,    51,    52,    -1,
      24,    25,    56,    42,    -1,    -1,    -1,    61,    47,    48,
      49,    50,    -1,    -1,    -1,    54,    55,    56,    42,    -1,
      44,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      54,    55,    56,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56,    -1,    -1,    59,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    -1,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    -1,
      42,    -1,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    42,    -1,    44,    45,    46,
      47,    48,    49,    50,    -1,    -1,    -1,    54,    55,    56,
      57,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      42,    -1,    44,    45,    46,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    55,    56,    57,    42,    -1,    44,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    54,    55,
      56,    57,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,
      -1,    42,    -1,    44,    45,    46,    47,    48,    49,    50,
      -1,    -1,    -1,    54,    55,    56,    42,    -1,    44,    45,
      46,    47,    48,    49,    50,    15,    16,    17,    54,    55,
      56,    -1,    -1,    -1,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,    44,    45,    46,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    56
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
#line 94 "grammar.y"
{}
    break;
case 2:
#line 97 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 3:
#line 97 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 4:
#line 100 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 5:
#line 100 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 7:
#line 104 "grammar.y"
{}
    break;
case 8:
#line 105 "grammar.y"
{}
    break;
case 9:
#line 106 "grammar.y"
{}
    break;
case 10:
#line 107 "grammar.y"
{}
    break;
case 11:
#line 110 "grammar.y"
{ yyval.count = 1; }
    break;
case 12:
#line 111 "grammar.y"
{ if (yyvsp[-1].count > 0) { pushn (SX_OP_POP, 0); } yyval.count = yyvsp[-1].count + 1; }
    break;
case 16:
#line 118 "grammar.y"
{ parser_push (sx_new_block (parse_system)); }
    break;
case 17:
#line 118 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 19:
#line 122 "grammar.y"
{}
    break;
case 20:
#line 123 "grammar.y"
{}
    break;
case 21:
#line 124 "grammar.y"
{}
    break;
case 22:
#line 125 "grammar.y"
{}
    break;
case 23:
#line 128 "grammar.y"
{ yyval.count = 1; }
    break;
case 24:
#line 129 "grammar.y"
{ if (yyvsp[-1].count > 0) { pushn (SX_OP_POP, 0); } yyval.count = yyvsp[-1].count + 1; }
    break;
case 26:
#line 132 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_LOCAL)); }
    break;
case 27:
#line 132 "grammar.y"
{ pushn (SX_OP_ASSIGN, 3); }
    break;
case 28:
#line 133 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_LOCAL)); }
    break;
case 29:
#line 133 "grammar.y"
{ pushn (SX_OP_NEWFUNC, 2); pushn (SX_OP_ASSIGN, 3); }
    break;
case 30:
#line 136 "grammar.y"
{ yyval.count = 0; }
    break;
case 31:
#line 137 "grammar.y"
{ yyval.count = 1; }
    break;
case 32:
#line 138 "grammar.y"
{ yyval.count = yyvsp[-2].count + 1; }
    break;
case 33:
#line 141 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 34:
#line 142 "grammar.y"
{ parser_push (sx_new_array (parse_system, 0, NULL)); }
    break;
case 35:
#line 142 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 36:
#line 145 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 37:
#line 146 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 38:
#line 149 "grammar.y"
{ parser_push (sx_new_array (parse_system, 0, NULL)); }
    break;
case 39:
#line 149 "grammar.y"
{ temp_val = parser_top (); parser_pop (); pushv (temp_val); }
    break;
case 40:
#line 152 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[-1].name))); append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 41:
#line 153 "grammar.y"
{ append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[-1].name))); append_to_array (parser_top (), sx_new_num(sx_name_to_id (yyvsp[0].name))); }
    break;
case 42:
#line 156 "grammar.y"
{ pushn (SX_OP_ADD, 2); }
    break;
case 43:
#line 157 "grammar.y"
{ pushn (SX_OP_SUBTRACT, 2); }
    break;
case 44:
#line 158 "grammar.y"
{ pushn (SX_OP_MULTIPLY, 2); }
    break;
case 45:
#line 159 "grammar.y"
{ pushn (SX_OP_DIVIDE, 2); }
    break;
case 47:
#line 161 "grammar.y"
{ pushn (SX_OP_NEGATE, 1); }
    break;
case 48:
#line 163 "grammar.y"
{ pushn (SX_OP_NOT, 1); }
    break;
case 49:
#line 164 "grammar.y"
{ pushn (SX_OP_AND, 2); }
    break;
case 50:
#line 165 "grammar.y"
{ pushn (SX_OP_OR, 2); }
    break;
case 51:
#line 167 "grammar.y"
{ pushn (SX_OP_GT, 2); }
    break;
case 52:
#line 168 "grammar.y"
{ pushn (SX_OP_LT, 2); }
    break;
case 53:
#line 169 "grammar.y"
{ pushn (SX_OP_NEQUAL, 2); }
    break;
case 54:
#line 170 "grammar.y"
{ pushn (SX_OP_GTE, 2); }
    break;
case 55:
#line 171 "grammar.y"
{ pushn (SX_OP_LTE, 2); }
    break;
case 56:
#line 172 "grammar.y"
{ pushn (SX_OP_EQUAL, 2); }
    break;
case 57:
#line 174 "grammar.y"
{ pushn (SX_OP_ASSIGN, 2); }
    break;
case 58:
#line 175 "grammar.y"
{ pushn (SX_OP_ASSIGN, 3); }
    break;
case 59:
#line 176 "grammar.y"
{ pushn (SX_OP_SETINDEX, 3); }
    break;
case 60:
#line 177 "grammar.y"
{ pushn (SX_OP_SETMEMBER, 3); }
    break;
case 61:
#line 179 "grammar.y"
{ pushn (SX_OP_PREINCREMENT, 2); }
    break;
case 62:
#line 180 "grammar.y"
{ pushn (SX_OP_PREDECREMENT, 2); }
    break;
case 63:
#line 181 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_POSTINCREMENT, 2); }
    break;
case 64:
#line 182 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_PREINCREMENT, 2); }
    break;
case 65:
#line 183 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_POSTDECREMENT, 2); }
    break;
case 66:
#line 184 "grammar.y"
{ pushv (sx_new_num (1)); pushn (SX_OP_PREDECREMENT, 2); }
    break;
case 67:
#line 186 "grammar.y"
{ pushn (SX_OP_SIZEOF, 1); }
    break;
case 68:
#line 187 "grammar.y"
{ pushn (SX_OP_TYPEOF, 1); }
    break;
case 69:
#line 188 "grammar.y"
{ pushn (SX_OP_ISA, 2); }
    break;
case 70:
#line 190 "grammar.y"
{ pushn (SX_OP_CALL, 1 + yyvsp[-1].count); }
    break;
case 71:
#line 191 "grammar.y"
{ pushn (SX_OP_NEWFUNC, 2); pushn (SX_OP_ASSIGN, 2); }
    break;
case 72:
#line 192 "grammar.y"
{ pushn (SX_OP_NEWFUNC, 2); }
    break;
case 73:
#line 194 "grammar.y"
{ pushn (SX_OP_METHOD, 2 + yyvsp[-1].count); }
    break;
case 74:
#line 195 "grammar.y"
{ pushn (SX_OP_MEMBER, 2); }
    break;
case 75:
#line 196 "grammar.y"
{ pushn (SX_OP_NEWINSTANCE, 1); }
    break;
case 76:
#line 197 "grammar.y"
{ pushn (SX_OP_NEWCLASS, 1); pushn (SX_OP_ASSIGN, 2); }
    break;
case 77:
#line 198 "grammar.y"
{ pushn (SX_OP_LOOKUP, 1); }
    break;
case 78:
#line 198 "grammar.y"
{ pushn (SX_OP_NEWCLASS, 2); pushn (SX_OP_ASSIGN, 2); }
    break;
case 79:
#line 200 "grammar.y"
{ pushn (SX_OP_INDEX, 2); }
    break;
case 80:
#line 202 "grammar.y"
{ pushv (sx_new_nil ()); pushn (SX_OP_IF, 3); }
    break;
case 81:
#line 203 "grammar.y"
{ pushn (SX_OP_IF, 3); }
    break;
case 82:
#line 204 "grammar.y"
{ pushn (SX_OP_WHILE, 2); }
    break;
case 83:
#line 205 "grammar.y"
{ pushn (SX_OP_TRY, 3); }
    break;
case 84:
#line 206 "grammar.y"
{ pushn (SX_OP_UNTIL, 2); }
    break;
case 85:
#line 207 "grammar.y"
{ pushn (SX_OP_EVAL, 1); }
    break;
case 86:
#line 208 "grammar.y"
{ pushn (SX_OP_FOR, 3); }
    break;
case 87:
#line 209 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 88:
#line 209 "grammar.y"
{ pushn (SX_OP_FOR, 4); }
    break;
case 89:
#line 211 "grammar.y"
{ pushn (SX_OP_LOOKUP, 1); }
    break;
case 90:
#line 212 "grammar.y"
{ pushn (SX_OP_LOOKUP, 2); }
    break;
case 91:
#line 214 "grammar.y"
{ pushn (SX_OP_RETURN, 1); }
    break;
case 92:
#line 215 "grammar.y"
{ pushn (SX_OP_RETURN, 0); }
    break;
case 93:
#line 216 "grammar.y"
{ pushn (SX_OP_BREAK, 0); }
    break;
case 94:
#line 217 "grammar.y"
{ pushn (SX_OP_BREAK, 1); }
    break;
case 95:
#line 218 "grammar.y"
{ pushn (SX_OP_RAISE, 0); }
    break;
case 96:
#line 220 "grammar.y"
{ pushn (SX_OP_NEWRANGE, 2); }
    break;
case 97:
#line 221 "grammar.y"
{ pushn (SX_OP_NEWARRAY, yyvsp[-1].count); }
    break;
case 99:
#line 226 "grammar.y"
{ pushv (yyvsp[0].value);  }
    break;
case 100:
#line 227 "grammar.y"
{ pushv (yyvsp[0].value); }
    break;
case 102:
#line 229 "grammar.y"
{ pushv (sx_new_nil ()); }
    break;
case 103:
#line 232 "grammar.y"
{ pushv (sx_new_num (sx_name_to_id (yyvsp[0].name))); }
    break;
case 104:
#line 235 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_LOCAL)); }
    break;
case 105:
#line 236 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_GLOBAL)); }
    break;
case 106:
#line 237 "grammar.y"
{ pushv (sx_new_num (SX_SCOPE_THREAD)); }
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
#line 240 "grammar.y"


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
	VALUE **sx_new_stack;
	if (parser_stack_top >= parser_stack_size) {
		if (parser_stack != NULL) {
			sx_new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + COMP_STACK_SIZE) * sizeof (VALUE **));
		} else {
			sx_new_stack = sx_malloc (parse_system, (parser_stack_size + COMP_STACK_SIZE) * sizeof (VALUE **));
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


VALUE *
append_to_array (VALUE *array, VALUE *value) {
	VALUE **nlist;

	if (!SX_ISARRAY (array)) {
		return sx_new_nil ();
	}

	if (array->data.array.count > 0) {
		nlist = (VALUE **)sx_malloc (parse_system, (array->data.array.count + 1) * sizeof (VALUE *));
		if (nlist == NULL) {
			return sx_new_nil ();
		}
		memcpy (nlist, array->data.array.list, array->data.array.count * sizeof (VALUE *));
		sx_free (array->data.array.list);
		array->data.array.list = nlist;
		array->data.array.list[array->data.array.count] = value;
		array->data.array.count += 1;
	} else {
		array->data.array.list = (VALUE **)sx_malloc (parse_system, sizeof (VALUE *));
		if (array->data.array.list == NULL) {
			return sx_new_nil ();
		}
		array->data.array.list[0] = value;
		array->data.array.count = 1;
	}

	return array;
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
	free (parser_stack);
	parser_stack = NULL;
	parser_stack_top = 0;
	parser_stack_size = 0;
}

VALUE *
sx_load_file (SYSTEM *system, char *file) {
	int ret, flags;

	if (file == NULL) {
		sxin = stdin;
	} else {
		sxin = fopen (file, "r");
		if (sxin == NULL) {
			fprintf (stderr, "Could not open '%s'\n", file);
			return NULL;
		}
	}

	parse_system = system;
	parse_block = sx_new_block (system);
	if (parse_block == NULL) {
		if (sxin != NULL) {
			fclose (sxin);
		}
		return NULL;
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

	if (ret) {
		cleanup_parser ();
		return NULL;
	}

	sx_lock_value (parse_block);
	sx_run_gc (system);
	sx_unlock_value (parse_block);

	cleanup_parser ();

	return parse_block;
}
