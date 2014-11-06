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
# define	TISA	296
# define	CUNARY	297
# define	CPARAN	298
# define	TTYPE	299

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

	int parser_node_stack_size = 0;
	int parser_node_stack_top = 0;
	NODE **parser_node_stack = NULL;

	__INLINE__ NODE *parser_node_top (void);
	__INLINE__ void parser_node_pop (void);
	void parser_node_push (NODE *node);

	VALUE *name_list[20];
	int name_ptr = 0;
	VALUE *get_dup_name (VALUE *name);

	VALUE *append_to_array (VALUE *array, VALUE *value);
	NODE *append_to_expr (NODE *expr, NODE *node);

	int sxerror (char *);
	int sxlex (void);

	SYSTEM *parse_system = NULL;
	VALUE *parse_block = NULL;

	extern FILE *sxin;
	int sxparse (void);

#line 70 "grammar.y"
#ifndef YYSTYPE
typedef union {
	VALUE *value;
	NODE *node;
} yystype;
# define YYSTYPE yystype
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		198
#define	YYFLAG		-32768
#define	YYNTBASE	63

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 299 ? yytranslate[x] : 84)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,     2,     2,     2,     2,     2,
      56,    57,    48,    46,    60,    47,    54,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,     2,
      44,    42,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
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
      36,    37,    38,    39,    40,    41,    45,    51,    52,    53
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     3,     6,     8,    12,    13,    15,    16,
      19,    21,    25,    26,    34,    41,    45,    46,    51,    52,
      54,    58,    59,    62,    64,    68,    72,    76,    80,    84,
      88,    91,    94,    98,   102,   106,   110,   114,   118,   122,
     126,   130,   135,   142,   148,   152,   156,   159,   162,   165,
     168,   173,   178,   182,   183,   189,   197,   204,   205,   213,
     217,   220,   225,   232,   237,   243,   251,   257,   263,   269,
     273,   281,   283,   286,   289,   291,   293,   296,   299,   301,
     303,   305,   307,   311,   317,   324,   326,   330,   332,   334,
     336
};
static const short yyrhs[] =
{
      64,     0,     0,    65,    66,     0,    67,     0,    66,     6,
      67,     0,     0,    78,     0,     0,    69,    70,     0,    71,
       0,    70,     6,    71,     0,     0,    19,    82,    56,    75,
      57,    64,    10,     0,    19,    82,    56,    57,    64,    10,
       0,    82,    42,    78,     0,     0,    58,    73,    74,    59,
       0,     0,    78,     0,    74,    60,    78,     0,     0,    76,
      77,     0,    82,     0,    77,    60,    82,     0,    78,    46,
      78,     0,    78,    47,    78,     0,    56,    78,    57,     0,
      78,    48,    78,     0,    78,    49,    78,     0,    47,    78,
       0,    50,    78,     0,    78,    13,    78,     0,    78,    14,
      78,     0,    78,    43,    78,     0,    78,    44,    78,     0,
      78,    17,    78,     0,    78,    15,    78,     0,    78,    16,
      78,     0,    78,    24,    78,     0,    82,    42,    78,     0,
      83,    82,    42,    78,     0,    78,    55,    78,    61,    42,
      78,     0,    78,    54,    82,    42,    78,     0,    82,    26,
      78,     0,    82,    27,    78,     0,    82,    28,     0,    28,
      82,     0,    82,    29,     0,    29,    82,     0,    30,    56,
      78,    57,     0,    53,    56,    78,    57,     0,    78,    45,
      78,     0,     0,    78,    56,    79,    74,    57,     0,    19,
      82,    56,    75,    57,    64,    10,     0,    19,    82,    56,
      57,    64,    10,     0,     0,    78,    41,    82,    56,    80,
      74,    57,     0,    78,    54,    82,     0,    33,    78,     0,
      32,    82,    68,    10,     0,    32,    82,    62,    82,    68,
      10,     0,    78,    55,    78,    61,     0,     7,    78,     8,
      64,    10,     0,     7,    78,     8,    64,     9,    64,    10,
       0,    11,    78,    12,    64,    10,     0,    34,    78,    12,
      64,    10,     0,    38,    64,    37,    64,    10,     0,    12,
      64,    10,     0,    40,    82,    39,    78,    12,    64,    10,
       0,    82,     0,    83,    82,     0,    18,    78,     0,    18,
       0,    20,     0,    20,    78,     0,    36,    78,     0,    81,
       0,    72,     0,     3,     0,     4,     0,    21,    64,    10,
       0,    19,    56,    57,    64,    10,     0,    19,    56,    75,
      57,    64,    10,     0,    35,     0,     3,    25,     3,     0,
       5,     0,    22,     0,    23,     0,    31,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    98,   101,   101,   104,   105,   108,   109,   112,   112,
     115,   116,   119,   120,   121,   122,   125,   125,   128,   129,
     130,   133,   133,   136,   137,   140,   141,   142,   143,   144,
     145,   147,   148,   149,   151,   152,   153,   154,   155,   156,
     158,   159,   160,   161,   163,   164,   165,   166,   167,   168,
     171,   172,   173,   175,   175,   176,   177,   179,   179,   180,
     181,   182,   183,   185,   187,   188,   189,   190,   191,   192,
     193,   195,   196,   198,   199,   200,   201,   202,   204,   205,
     209,   210,   211,   212,   213,   214,   215,   218,   221,   222,
     223
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
  "'='", "'>'", "'<'", "TISA", "'+'", "'-'", "'*'", "'/'", "'!'", 
  "CUNARY", "CPARAN", "TTYPE", "'.'", "'['", "'('", "')'", "'{'", "'}'", 
  "','", "']'", "':'", "program", "block", "@1", "stmts", "stmt", 
  "cblock", "@2", "cstmts", "cstmt", "array", "@3", "array_list", "args", 
  "@4", "arg_list", "node", "@5", "@6", "data", "name", "scope", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    63,    65,    64,    66,    66,    67,    67,    69,    68,
      70,    70,    71,    71,    71,    71,    73,    72,    74,    74,
      74,    76,    75,    77,    77,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    78,    78,    78,    80,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      81,    81,    81,    81,    81,    81,    81,    82,    83,    83,
      83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     0,     2,     1,     3,     0,     1,     0,     2,
       1,     3,     0,     7,     6,     3,     0,     4,     0,     1,
       3,     0,     2,     1,     3,     3,     3,     3,     3,     3,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     4,     6,     5,     3,     3,     2,     2,     2,     2,
       4,     4,     3,     0,     5,     7,     6,     0,     7,     3,
       2,     4,     6,     4,     5,     7,     5,     5,     5,     3,
       7,     1,     2,     2,     1,     1,     2,     2,     1,     1,
       1,     1,     3,     5,     6,     1,     3,     1,     1,     1,
       1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       2,     1,     6,    80,    81,    87,     0,     0,     2,    74,
       0,    75,     2,    88,    89,     0,     0,     0,    90,     0,
       0,     0,    85,     0,     2,     0,     0,     0,     0,     0,
      16,     3,     4,    79,     7,    78,    71,     0,     0,     0,
       0,     0,    73,    21,     0,    76,     0,    47,    49,     0,
       8,    60,     0,    77,     0,     0,    30,    31,     0,     0,
      18,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    53,     0,
       0,    46,    48,     0,    72,    86,     2,     2,    69,     2,
       0,     0,    21,    82,     0,     0,     0,    12,     2,     2,
       0,     0,    27,     0,    19,     5,    32,    33,    37,    38,
      36,    39,     0,    34,    35,    52,    25,    26,    28,    29,
      59,     0,    18,    44,    45,    40,     0,     0,     0,     0,
       2,    22,    23,     2,     0,    50,     8,    61,     0,     9,
      10,     0,     0,     0,     0,    51,    17,     0,    57,     0,
      63,     0,    41,     2,    64,    66,    83,     0,     0,     0,
       2,     0,     0,    12,     0,    67,    68,     2,    20,    18,
      43,     0,    54,     0,    84,    24,    56,     0,    62,    21,
      11,    15,     0,     0,    42,    65,    55,     2,     0,    70,
      58,     0,     2,    14,     0,    13,     0,     0,     0
};

static const short yydefgoto[] =
{
     196,     1,     2,    31,    32,    96,    97,   139,   140,    33,
      60,   103,    90,    91,   131,   104,   122,   169,    35,    36,
      37
};

static const short yypact[] =
{
  -32768,-32768,   200,   -22,-32768,-32768,   200,   200,-32768,   200,
      -3,   200,-32768,-32768,-32768,    15,    15,   -20,-32768,    15,
     200,   200,-32768,   200,-32768,    15,   200,   200,   -17,   200,
  -32768,    28,-32768,-32768,   463,-32768,   -21,    15,    32,   120,
     278,    33,   463,   -12,   -10,   463,    37,-32768,-32768,   200,
     -13,   -28,   294,   463,    13,    16,   -28,   -28,   200,   338,
     200,   200,   200,   200,   200,   200,   200,   200,    15,   200,
     200,   200,   200,   200,   200,   200,    15,   200,-32768,   200,
     200,-32768,-32768,   200,    14,-32768,-32768,-32768,-32768,-32768,
       2,    15,     5,-32768,   356,    15,    53,    10,-32768,-32768,
     200,   401,-32768,   -50,   463,-32768,   479,   514,   526,   526,
     -24,   -24,     8,   526,   526,   -24,   142,   142,   -28,   -28,
      23,   228,   200,   463,   463,   463,   200,     9,    58,    59,
  -32768,    11,-32768,-32768,    17,-32768,-32768,-32768,    15,    66,
  -32768,    35,    63,    65,   419,-32768,-32768,   200,-32768,   200,
      40,   -46,   463,-32768,-32768,-32768,-32768,    73,    15,    74,
  -32768,    75,    30,    10,   200,-32768,-32768,-32768,   463,   200,
     463,   200,-32768,    77,-32768,-32768,-32768,    97,-32768,    52,
  -32768,   463,   102,   -16,   463,-32768,-32768,-32768,    56,-32768,
  -32768,   105,-32768,-32768,   106,-32768,   117,   118,-32768
};

static const short yypgoto[] =
{
  -32768,    -8,-32768,-32768,    60,    -7,-32768,-32768,   -43,-32768,
  -32768,  -121,   -80,-32768,-32768,    31,-32768,-32768,-32768,    51,
  -32768
};


#define	YYLAST		582


static const short yytable[] =
{
      41,   151,     5,    38,    46,    79,    80,    81,    82,   146,
     147,   172,   134,    68,   147,     5,    54,    68,   153,   154,
       5,    83,    72,    73,    74,    75,    76,    77,    78,   138,
      76,    77,    78,    34,    61,    85,    49,    39,    40,    58,
      42,   190,    45,    88,   147,    89,    92,    93,   183,    95,
      99,    51,    52,    43,    53,   100,   126,    56,    57,   130,
      59,    44,   133,   137,   148,   149,    47,    48,   155,   156,
      50,   158,   163,   165,   160,   166,    55,   164,   127,   128,
      94,   129,   171,   174,   176,   178,   179,   185,    84,   101,
     142,   143,    34,   106,   107,   108,   109,   110,   111,   188,
     113,   114,   115,   116,   117,   118,   119,   186,   121,   187,
     123,   124,   189,   192,   125,   193,   195,   197,   198,   112,
     180,   105,   157,     0,     0,   159,     0,   120,    86,   161,
       0,   144,     0,    62,    63,    64,    65,    66,     0,     0,
       0,     0,   132,     0,    67,   173,   136,     0,   141,     0,
       0,     0,   177,     0,     0,     0,     0,   152,     0,   182,
       0,    68,     0,    69,    70,    71,    72,    73,    74,    75,
       0,     0,     0,     0,    76,    77,    78,     0,   168,   191,
     170,     0,     0,    68,   194,     0,     0,     0,     0,   162,
      74,    75,     0,     0,     0,   181,    76,    77,    78,     0,
       0,     0,   184,     3,     4,     5,     0,     6,     0,   175,
       0,     7,     8,     0,   141,     0,     0,     0,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,     0,    24,     0,
      25,    62,    63,    64,    65,    66,     0,    26,     0,     0,
      27,     0,    67,    28,     0,     0,    29,     0,    30,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    68,
       0,    69,    70,    71,    72,    73,    74,    75,     0,     0,
       0,     0,    76,    77,    78,     0,     0,     0,     0,   150,
      87,    62,    63,    64,    65,    66,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,    98,    62,    63,    64,
      65,    66,     0,     0,     0,     0,     0,     0,    67,    68,
       0,    69,    70,    71,    72,    73,    74,    75,     0,     0,
       0,     0,    76,    77,    78,    68,     0,    69,    70,    71,
      72,    73,    74,    75,     0,     0,     0,     0,    76,    77,
      78,    62,    63,    64,    65,    66,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,     0,     0,    62,
      63,    64,    65,    66,     0,     0,     0,     0,     0,    68,
      67,    69,    70,    71,    72,    73,    74,    75,     0,     0,
       0,     0,    76,    77,    78,   102,     0,    68,     0,    69,
      70,    71,    72,    73,    74,    75,     0,     0,     0,     0,
      76,    77,    78,   135,    62,    63,    64,    65,    66,     0,
       0,     0,     0,     0,     0,    67,     0,     0,     0,     0,
       0,   167,    62,    63,    64,    65,    66,     0,     0,     0,
       0,     0,    68,    67,    69,    70,    71,    72,    73,    74,
      75,     0,     0,     0,     0,    76,    77,    78,   145,     0,
      68,     0,    69,    70,    71,    72,    73,    74,    75,     0,
       0,     0,     0,    76,    77,    78,    62,    63,    64,    65,
      66,     0,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,    63,    64,    65,    66,     0,     0,     0,
       0,     0,     0,    67,    68,     0,    69,    70,    71,    72,
      73,    74,    75,     0,     0,     0,     0,    76,    77,    78,
      68,     0,    69,    70,    71,    72,    73,    74,    75,    64,
      65,    66,     0,    76,    77,    78,     0,     0,    67,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,    68,     0,    69,    70,    71,
      72,    73,    74,    75,     0,     0,     0,    68,    76,    77,
      78,    71,    72,    73,    74,    75,     0,     0,     0,     0,
      76,    77,    78
};

static const short yycheck[] =
{
       8,   122,     5,    25,    12,    26,    27,    28,    29,    59,
      60,    57,    92,    41,    60,     5,    24,    41,     9,    10,
       5,    42,    46,    47,    48,    49,    54,    55,    56,    19,
      54,    55,    56,     2,     6,     3,    56,     6,     7,    56,
       9,    57,    11,    10,    60,    57,    56,    10,   169,    62,
      37,    20,    21,    56,    23,    39,    42,    26,    27,    57,
      29,    10,    57,    10,    56,    42,    15,    16,    10,    10,
      19,    60,     6,    10,    57,    10,    25,    42,    86,    87,
      49,    89,    42,    10,    10,    10,    56,    10,    37,    58,
      98,    99,    61,    62,    63,    64,    65,    66,    67,   179,
      69,    70,    71,    72,    73,    74,    75,    10,    77,    57,
      79,    80,    10,    57,    83,    10,    10,     0,     0,    68,
     163,    61,   130,    -1,    -1,   133,    -1,    76,     8,   136,
      -1,   100,    -1,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    91,    -1,    24,   153,    95,    -1,    97,    -1,
      -1,    -1,   160,    -1,    -1,    -1,    -1,   126,    -1,   167,
      -1,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    -1,    -1,    54,    55,    56,    -1,   147,   187,
     149,    -1,    -1,    41,   192,    -1,    -1,    -1,    -1,   138,
      48,    49,    -1,    -1,    -1,   164,    54,    55,    56,    -1,
      -1,    -1,   171,     3,     4,     5,    -1,     7,    -1,   158,
      -1,    11,    12,    -1,   163,    -1,    -1,    -1,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    38,    -1,
      40,    13,    14,    15,    16,    17,    -1,    47,    -1,    -1,
      50,    -1,    24,    53,    -1,    -1,    56,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    54,    55,    56,    -1,    -1,    -1,    -1,    61,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    41,
      -1,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    54,    55,    56,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    -1,    54,    55,
      56,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    41,
      24,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    -1,    41,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    41,    24,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    -1,
      41,    -1,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    54,    55,    56,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    41,    -1,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    -1,    -1,    54,    55,    56,
      41,    -1,    43,    44,    45,    46,    47,    48,    49,    15,
      16,    17,    -1,    54,    55,    56,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    41,    54,    55,
      56,    45,    46,    47,    48,    49,    -1,    -1,    -1,    -1,
      54,    55,    56
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
#line 98 "grammar.y"
{ parse_block = yyvsp[0].value; }
    break;
case 2:
#line 101 "grammar.y"
{ parser_push (new_block (parse_system)); }
    break;
case 3:
#line 101 "grammar.y"
{ yyval.value = parser_top (); parser_pop (); }
    break;
case 4:
#line 104 "grammar.y"
{ if (yyvsp[0].node != NULL) { add_stmt (parser_top (), yyvsp[0].node); }}
    break;
case 5:
#line 105 "grammar.y"
{ if (yyvsp[0].node != NULL) { add_stmt (parser_top (), yyvsp[0].node); }}
    break;
case 6:
#line 108 "grammar.y"
{ yyval.node = NULL; }
    break;
case 7:
#line 109 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 8:
#line 112 "grammar.y"
{ parser_push (new_block (parse_system)); }
    break;
case 9:
#line 112 "grammar.y"
{ yyval.value = parser_top (); parser_pop (); }
    break;
case 10:
#line 115 "grammar.y"
{ if (yyvsp[0].node != NULL) { add_stmt (parser_top (), yyvsp[0].node); }}
    break;
case 11:
#line 116 "grammar.y"
{ if (yyvsp[0].node!= NULL) { add_stmt (parser_top (), yyvsp[0].node); }}
    break;
case 12:
#line 119 "grammar.y"
{ yyval.node = NULL; }
    break;
case 13:
#line 120 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, yyvsp[-5].value), new_node (parse_system, new_func (parse_system, yyvsp[-3].value, yyvsp[-1].value))); }
    break;
case 14:
#line 121 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, yyvsp[-4].value), new_node (parse_system, new_func (parse_system, new_nil (), yyvsp[-1].value))); }
    break;
case 15:
#line 122 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, yyvsp[-2].value), yyvsp[0].node); }
    break;
case 16:
#line 125 "grammar.y"
{ parser_node_push (new_expr (parse_system, OP_NEWARRAY, 0)); }
    break;
case 17:
#line 125 "grammar.y"
{ yyval.node = parser_node_top (); parser_node_pop (); }
    break;
case 19:
#line 129 "grammar.y"
{ append_to_expr (parser_node_top  (), yyvsp[0].node); }
    break;
case 20:
#line 130 "grammar.y"
{ append_to_expr (parser_node_top (), yyvsp[0].node); }
    break;
case 21:
#line 133 "grammar.y"
{ parser_push (new_array (parse_system, 0, NULL)); }
    break;
case 22:
#line 133 "grammar.y"
{ yyval.value = parser_top (); parser_pop (); }
    break;
case 23:
#line 136 "grammar.y"
{ append_to_array (parser_top (), yyvsp[0].value); }
    break;
case 24:
#line 137 "grammar.y"
{ append_to_array (parser_top (), yyvsp[0].value); }
    break;
case 25:
#line 140 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ADD, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 26:
#line 141 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_SUBTRACT, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 27:
#line 142 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 28:
#line 143 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_MULTIPLY, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 29:
#line 144 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_DIVIDE, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 30:
#line 145 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_NEGATE, 1, yyvsp[0].node); }
    break;
case 31:
#line 147 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_NOT, 1, yyvsp[0].node); }
    break;
case 32:
#line 148 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_AND, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 33:
#line 149 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_OR, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 34:
#line 151 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_GT, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 35:
#line 152 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_LT, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 36:
#line 153 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_NEQUAL, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 37:
#line 154 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_GTE, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 38:
#line 155 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_LTE, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 39:
#line 156 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_EQUAL, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 40:
#line 158 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 3, new_node (parse_system, yyvsp[-2].value), yyvsp[0].node, new_node (parse_system, new_num (SCOPE_DEF))); }
    break;
case 41:
#line 159 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 3, new_node (parse_system, yyvsp[-2].value), yyvsp[0].node, new_node (parse_system, yyvsp[-3].value)); }
    break;
case 42:
#line 160 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_SETINDEX, 3, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;
case 43:
#line 161 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_SETMEMBER, 3, yyvsp[-4].node, new_node (parse_system, yyvsp[-2].value), yyvsp[0].node); }
    break;
case 44:
#line 163 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_PREINCREMENT, 2, new_node (parse_system, yyvsp[-2].value), yyvsp[0].node); }
    break;
case 45:
#line 164 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_PREDECREMENT, 2, new_node (parse_system, yyvsp[-2].value), yyvsp[0].node); }
    break;
case 46:
#line 165 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_POSTINCREMENT, 2, new_node (parse_system, yyvsp[-1].value), new_node (parse_system, new_num (1))); }
    break;
case 47:
#line 166 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_PREINCREMENT, 2, new_node (parse_system, yyvsp[0].value), new_node (parse_system, new_num (1))); }
    break;
case 48:
#line 167 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_POSTDECREMENT, 2, new_node (parse_system, yyvsp[-1].value), new_node (parse_system, new_num (1))); }
    break;
case 49:
#line 168 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_PREDECREMENT, 2, new_node (parse_system, yyvsp[0].value), new_node (parse_system, new_num (1))); }
    break;
case 50:
#line 171 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_SIZEOF, 1, yyvsp[-1].node); }
    break;
case 51:
#line 172 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_TYPEOF, 1, yyvsp[-1].node); }
    break;
case 52:
#line 173 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ISA, 2, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 53:
#line 175 "grammar.y"
{ parser_node_push (new_expr (parse_system, OP_CALL, 2, yyvsp[-1].node, NULL)); }
    break;
case 54:
#line 175 "grammar.y"
{ yyval.node = parser_node_top (); parser_node_pop (); }
    break;
case 55:
#line 176 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, yyvsp[-5].value), new_node (parse_system, new_func (parse_system, yyvsp[-3].value, yyvsp[-1].value))); }
    break;
case 56:
#line 177 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, yyvsp[-4].value), new_node (parse_system, new_func (parse_system, new_nil (), yyvsp[-1].value))); }
    break;
case 57:
#line 179 "grammar.y"
{ parser_node_push (new_expr (parse_system, OP_CALL, 2, new_expr (parse_system, OP_MEMBER, 2, yyvsp[-3].node, new_node (parse_system, yyvsp[-1].value)), yyvsp[-3].node)); }
    break;
case 58:
#line 179 "grammar.y"
{ yyval.node = parser_node_top (); parser_node_pop (); }
    break;
case 59:
#line 180 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_MEMBER, 2, yyvsp[-2].node, new_node (parse_system, yyvsp[0].value)); }
    break;
case 60:
#line 181 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_NEWINSTANCE, 1, yyvsp[0].node); }
    break;
case 61:
#line 182 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, yyvsp[-2].value), new_expr (parse_system, OP_NEWCLASS, 2, NULL, new_node (parse_system, yyvsp[-1].value))); }
    break;
case 62:
#line 183 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_ASSIGN, 2, new_node (parse_system, yyvsp[-4].value), new_expr (parse_system, OP_NEWCLASS, 2, new_expr (parse_system, OP_LOOKUP, 2, new_node (parse_system, yyvsp[-2].value), new_node (parse_system, new_num (SCOPE_DEF))), new_node (parse_system, yyvsp[-1].value))); }
    break;
case 63:
#line 185 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_INDEX, 2, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 64:
#line 187 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_IF, 2, yyvsp[-3].node, new_node (parse_system, yyvsp[-1].value)); }
    break;
case 65:
#line 188 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_IF, 3, yyvsp[-5].node, new_node (parse_system, yyvsp[-3].value), new_node (parse_system, yyvsp[-1].value)); }
    break;
case 66:
#line 189 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_WHILE, 2, yyvsp[-3].node, new_node (parse_system, yyvsp[-1].value)); }
    break;
case 67:
#line 190 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_WHILE, 2, new_expr (parse_system, OP_NOT, 1, yyvsp[-3].node), new_node (parse_system, yyvsp[-1].value)); }
    break;
case 68:
#line 191 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_TRY, 2, new_node (parse_system, yyvsp[-3].value), new_node (parse_system, yyvsp[-1].value)); }
    break;
case 69:
#line 192 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_EVAL, 1, new_node (parse_system, yyvsp[-1].value)); }
    break;
case 70:
#line 193 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_FOR, 3, new_node (parse_system, yyvsp[-5].value), yyvsp[-3].node, new_node (parse_system, yyvsp[-1].value)); }
    break;
case 71:
#line 195 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_LOOKUP, 2, new_node (parse_system, yyvsp[0].value), new_node (parse_system, new_num (SCOPE_DEF))); }
    break;
case 72:
#line 196 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_LOOKUP, 2, new_node (parse_system, yyvsp[0].value), new_node (parse_system, yyvsp[-1].value)); }
    break;
case 73:
#line 198 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_RETURN, 1, yyvsp[0].node); }
    break;
case 74:
#line 199 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_RETURN, 0);  }
    break;
case 75:
#line 200 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_BREAK, 0); }
    break;
case 76:
#line 201 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_BREAK, 1, yyvsp[0].node); }
    break;
case 77:
#line 202 "grammar.y"
{ yyval.node = new_expr (parse_system, OP_RAISE, 1, yyvsp[0].node); }
    break;
case 78:
#line 204 "grammar.y"
{ yyval.node = new_node (parse_system, yyvsp[0].value);  }
    break;
case 79:
#line 205 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 80:
#line 209 "grammar.y"
{ yyval.value = yyvsp[0].value;  }
    break;
case 81:
#line 210 "grammar.y"
{ yyval.value = yyvsp[0].value; }
    break;
case 82:
#line 211 "grammar.y"
{ yyval.value = yyvsp[-1].value;  }
    break;
case 83:
#line 212 "grammar.y"
{ yyval.value = new_func (parse_system, new_nil (), yyvsp[-1].value); }
    break;
case 84:
#line 213 "grammar.y"
{ yyval.value = new_func (parse_system, yyvsp[-3].value, yyvsp[-1].value); }
    break;
case 85:
#line 214 "grammar.y"
{ yyval.value = new_nil (); }
    break;
case 86:
#line 215 "grammar.y"
{ yyval.value = new_range (parse_system, TO_INT(yyvsp[-2].value), TO_INT(yyvsp[0].value), 1); }
    break;
case 87:
#line 218 "grammar.y"
{ yyval.value = get_dup_name (yyvsp[0].value); }
    break;
case 88:
#line 221 "grammar.y"
{ yyval.value = new_num (SCOPE_LOCAL); }
    break;
case 89:
#line 222 "grammar.y"
{ yyval.value = new_num (SCOPE_GLOBAL); }
    break;
case 90:
#line 223 "grammar.y"
{ yyval.value = new_num (SCOPE_THREAD); }
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
#line 226 "grammar.y"


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
			new_stack = sx_dupmem (parse_system, parser_stack, (parser_stack_size + STACK_CHUNK_SIZE) * sizeof (VALUE **));
		} else {
			new_stack = sx_malloc (parse_system, (parser_stack_size + STACK_CHUNK_SIZE) * sizeof (VALUE **));
		}
		if (new_stack == NULL) {
			/* FIXME: error */
			return;
		}
		sx_free (parser_stack);
		parser_stack = new_stack;
		parser_stack_size += STACK_CHUNK_SIZE;
	}

	parser_stack[parser_stack_top ++] = value;
}

void
parser_pop (void) {
	if (parser_stack_top > 0) {
		-- parser_stack_top;
	}
}

/* node stack */
NODE *
parser_node_top (void) {
	if (parser_node_stack_top > 0) {
		return parser_node_stack[parser_node_stack_top - 1];
	}

	return NULL;
}

void
parser_node_push (NODE *node) {
	NODE **new_stack;
	if (parser_node_stack_top >= parser_node_stack_size) {
		if (parser_node_stack != NULL) {
			new_stack = sx_dupmem (parse_system, parser_node_stack, (parser_node_stack_size + STACK_CHUNK_SIZE) * sizeof (NODE **));
		} else {
			new_stack = sx_malloc (parse_system, (parser_node_stack_size + STACK_CHUNK_SIZE) * sizeof (NODE **));
		}
		if (new_stack == NULL) {
			/* FIXME: error */
			return;
		}
		sx_free (parser_node_stack);
		parser_node_stack = new_stack;
		parser_node_stack_size += STACK_CHUNK_SIZE;
	}

	parser_node_stack[parser_node_stack_top ++] = node;
}

void
parser_node_pop (void) {
	if (parser_node_stack_top > 0) {
		-- parser_node_stack_top;
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

NODE *
append_to_expr (NODE *expr, NODE *node) {
	NODE **nnodes;

	if (expr->data.expr.count > 0) {
		nnodes = (NODE **)sx_malloc (parse_system, (expr->data.expr.count + 1) * sizeof (NODE *));
		if (nnodes == NULL) {
			return NULL;
		}
		memcpy (nnodes, expr->data.expr.nodes, expr->data.expr.count * sizeof (NODE *));
		sx_free (expr->data.expr.nodes);
		expr->data.expr.nodes = nnodes;
		expr->data.expr.nodes[expr->data.expr.count] = node;
		expr->data.expr.count += 1;
	} else {
		expr->data.expr.nodes = (NODE **)sx_malloc (parse_system, sizeof (NODE *));
		if (expr->data.expr.nodes == NULL) {
			return NULL;
		}
		expr->data.expr.nodes[0] = node;
		expr->data.expr.count = 1;
	}

	return expr;
}

VALUE *
get_dup_name (VALUE *name) {
	int i;
	for (i = 0; i < 20; ++ i) {
		if (name == name_list[i]) {
			return name;
		}
		if (are_equal (name, name_list[i])) {
			return name_list[i];
		}
	}
	name_list[name_ptr] = name;
	if (++ name_ptr >= 20) {
		name_ptr = 0;
	}
	return name;
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
	parse_block = NULL;

	flags = system->flags;
	system->flags |= SFLAG_GCOFF;
	ret = sxparse ();
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
