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
# define	TTYPE	260
# define	TIF	261
# define	TELSE	262
# define	TWHILE	263
# define	TDO	264
# define	TAND	265
# define	TOR	266
# define	TGTE	267
# define	TLTE	268
# define	TNE	269
# define	TADDASSIGN	270
# define	TSUBASSIGN	271
# define	TINCREMENT	272
# define	TDECREMENT	273
# define	TUNTIL	274
# define	TNIL	275
# define	TRESCUE	276
# define	TIN	277
# define	TFOR	278
# define	TCONTINUE	279
# define	TYIELD	280
# define	TBREAK	281
# define	TRETURN	282
# define	TEQUALS	283
# define	TCAST	284
# define	TLENGTH	285
# define	TRANGE	286
# define	CUNARY	287
# define	TSTATMETHOD	288

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

	int sxerror (const char *);
	int sxlex (void);
	int sxparse (void);

	SXP_INFO *sxp_parser_info = NULL;

#line 48 "grammar.y"
#ifndef YYSTYPE
typedef union {
	SXP_NODE *node;
	SX_VALUE value;
	sx_name_id id;
	struct _sxp_arg_list args;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		166
#define	YYFLAG		-32768
#define	YYNTBASE	54

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 288 ? yytranslate[x] : 68)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,     2,     2,     2,    52,     2,
      45,    47,    35,    33,    51,    34,    42,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      31,    29,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    53,    46,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    49,     2,     2,     2,     2,
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
      26,    27,    28,    32,    37,    38,    39,    41,    43
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,    12,    13,    15,    17,    20,    23,
      26,    32,    40,    46,    52,    60,    68,    76,    86,    90,
      96,   100,   101,   103,   106,   108,   110,   112,   114,   115,
     117,   121,   122,   124,   129,   132,   134,   138,   142,   146,
     150,   154,   158,   162,   165,   168,   172,   176,   180,   184,
     188,   192,   196,   200,   204,   211,   217,   221,   225,   228,
     231,   234,   237,   242,   247,   254,   261,   265,   270,   274,
     276,   278,   280,   282,   284,   286
};
static const short yyrhs[] =
{
      -1,    54,    55,     0,    66,    45,    62,    47,    48,    56,
      49,     0,     0,    57,     0,    58,     0,    57,    58,     0,
      59,    50,     0,    60,    50,     0,     7,    45,    64,    47,
      58,     0,     7,    45,    64,    47,    58,     8,    58,     0,
       9,    45,    64,    47,    58,     0,    20,    45,    64,    47,
      58,     0,    10,    58,     9,    45,    64,    47,    50,     0,
      10,    58,    20,    45,    64,    47,    50,     0,    24,    45,
      66,    23,    64,    47,    58,     0,    24,    45,    59,    50,
      64,    50,    59,    47,    58,     0,    67,    66,    50,     0,
      67,    66,    29,    64,    50,     0,    48,    56,    49,     0,
       0,    64,     0,    28,    64,     0,    28,     0,    27,     0,
      25,     0,    26,     0,     0,    64,     0,    61,    51,    64,
       0,     0,    63,     0,    63,    51,    52,    66,     0,    52,
      66,     0,    66,     0,    63,    51,    66,     0,    64,    33,
      64,     0,    64,    34,    64,     0,    64,    35,    64,     0,
      64,    36,    64,     0,    45,    64,    47,     0,    64,    23,
      64,     0,    34,    64,     0,    40,    64,     0,    64,    11,
      64,     0,    64,    12,    64,     0,    64,    30,    64,     0,
      64,    31,    64,     0,    64,    15,    64,     0,    64,    13,
      64,     0,    64,    14,    64,     0,    64,    32,    64,     0,
      66,    29,    64,     0,    64,    44,    64,    53,    29,    64,
       0,    64,    42,    66,    29,    64,     0,    66,    16,    64,
       0,    66,    17,    64,     0,    66,    18,     0,    18,    66,
       0,    66,    19,     0,    19,    66,     0,    45,    67,    47,
      64,     0,    66,    45,    61,    47,     0,    67,    42,    66,
      45,    61,    47,     0,    64,    42,    66,    45,    61,    47,
       0,    64,    42,    66,     0,    64,    44,    64,    53,     0,
      44,    61,    53,     0,    65,     0,    66,     0,     3,     0,
       4,     0,    21,     0,     5,     0,     6,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    83,    84,    87,    90,    91,    94,    95,    98,    99,
     100,   101,   102,   103,   104,   105,   107,   108,   110,   111,
     113,   116,   117,   120,   121,   122,   123,   124,   127,   128,
     129,   132,   133,   134,   135,   138,   139,   142,   143,   144,
     145,   146,   148,   150,   152,   153,   154,   156,   157,   158,
     159,   160,   161,   163,   164,   165,   167,   168,   169,   170,
     171,   172,   174,   175,   177,   178,   179,   181,   182,   184,
     186,   190,   191,   192,   195,   198
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "TNUM", "TSTR", "TNAME", "TTYPE", "TIF", 
  "TELSE", "TWHILE", "TDO", "TAND", "TOR", "TGTE", "TLTE", "TNE", 
  "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", "TDECREMENT", "TUNTIL", 
  "TNIL", "TRESCUE", "TIN", "TFOR", "TCONTINUE", "TYIELD", "TBREAK", 
  "TRETURN", "'='", "'>'", "'<'", "TEQUALS", "'+'", "'-'", "'*'", "'/'", 
  "TCAST", "TLENGTH", "TRANGE", "'!'", "CUNARY", "'.'", "TSTATMETHOD", 
  "'['", "'('", "'^'", "')'", "'{'", "'}'", "';'", "','", "'&'", "']'", 
  "program", "function", "block", "stmts", "stmt", "node", "control", 
  "args", "arg_names", "arg_names_list", "expr", "data", "name", "type", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    54,    54,    55,    56,    56,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    60,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    65,    66,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     7,     0,     1,     1,     2,     2,     2,
       5,     7,     5,     5,     7,     7,     7,     9,     3,     5,
       3,     0,     1,     2,     1,     1,     1,     1,     0,     1,
       3,     0,     1,     4,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     6,     5,     3,     3,     2,     2,
       2,     2,     4,     4,     6,     6,     3,     4,     3,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,    74,     2,     0,    31,     0,     0,    32,    35,
      34,     0,     0,     4,     0,    36,    71,    72,    75,     0,
       0,    21,     0,     0,     0,    73,     0,    26,    27,    25,
      24,     0,     0,    28,     0,     4,     0,     5,     6,     0,
       0,    22,    69,    70,     0,    33,     0,     0,     0,    59,
      61,     0,    21,    23,     0,    43,    44,     0,    29,     0,
       0,     0,     3,     7,     8,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    60,     0,    28,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,    68,    41,     0,
      20,    45,    46,    50,    51,    49,    42,    47,    48,    52,
      37,    38,    39,    40,    66,     0,    56,    57,    53,     0,
       0,     0,    18,    21,    21,     0,     0,    21,     0,     0,
      30,    62,     0,    28,    67,    63,    28,     0,    10,    12,
       0,     0,    13,     0,     0,    55,     0,     0,     0,    19,
      21,     0,     0,    21,    21,    65,    54,    64,    11,    14,
      15,     0,    16,    21,    17,     0,     0
};

static const short yydefgoto[] =
{
       1,     3,    36,    37,    38,    39,    40,    57,     7,     8,
      41,    42,    43,    54
};

static const short yypact[] =
{
  -32768,     9,-32768,-32768,   -34,    -2,    15,   -35,    -3,-32768,
  -32768,    12,     1,   152,    15,-32768,-32768,-32768,-32768,    37,
      56,   200,    15,    15,    57,-32768,    67,-32768,-32768,-32768,
     246,   246,   246,   246,   246,   152,     8,   152,-32768,    39,
      43,   504,-32768,    14,     2,-32768,   246,   246,    -4,-32768,
  -32768,   246,   246,   504,    76,    44,    44,    62,   504,   322,
     -32,    60,-32768,-32768,-32768,-32768,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,    15,
     246,   246,   246,-32768,-32768,   246,   246,    15,   -16,   348,
     374,    74,    77,   400,    79,   166,   246,-32768,-32768,   246,
  -32768,   528,   528,     3,     3,    64,     3,     3,     3,    64,
      48,    48,    44,    44,    11,   224,   504,   504,   504,   -28,
      81,   246,-32768,   200,   200,   246,   246,   200,   246,   246,
     504,    44,   246,   246,   103,-32768,   246,   270,   125,-32768,
     426,   452,-32768,   296,   478,   504,     4,   246,     7,-32768,
     200,    85,    86,   246,   200,-32768,   504,-32768,-32768,-32768,
  -32768,    91,-32768,   200,-32768,   139,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,   105,-32768,   -20,   -48,-32768,   -84,-32768,-32768,
      -5,-32768,    73,   -13
};


#define	YYLAST		572


static const short yytable[] =
{
      44,    48,   119,     2,    94,    91,     2,     2,    44,   165,
      87,     5,    11,   121,     2,    99,    92,    63,    70,   135,
       2,    60,    44,    96,    44,    53,    55,    56,    58,    59,
      81,    82,    83,    84,   122,    74,    75,    76,    77,    78,
     132,    89,    90,    85,    87,    79,    93,    80,    12,   146,
       6,   155,   148,    14,   157,    96,   133,    62,    96,    86,
      13,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     4,   115,   116,   117,     9,    10,
     118,    58,    46,    77,    78,    15,    79,    45,    80,    64,
      79,   130,    80,    65,   131,    49,    50,    75,    76,    77,
      78,    47,    51,   138,   139,   161,    79,   142,    80,   100,
      44,    44,    52,    96,    44,    97,   137,    88,    87,   125,
     140,   141,   126,   143,   144,    95,   136,   145,    58,   128,
     158,    58,   147,   150,   162,   159,   160,    44,   163,   166,
      61,    44,   156,   164,     0,     0,     0,     0,     0,     0,
      44,     0,   114,     0,     0,    16,    17,     2,    18,    19,
     120,    20,    21,     0,     0,     0,     0,     0,     0,     0,
      22,    23,    24,    25,     0,     0,    26,    27,    28,    29,
      30,     0,    81,    82,    83,    84,    31,     0,     0,   129,
       0,     0,    32,     0,     0,    85,    33,    34,     0,     0,
      35,     0,   -21,    16,    17,     2,    18,    19,     0,    20,
      21,    86,     0,     0,     0,     0,     0,     0,    22,    23,
      24,    25,     0,     0,    26,    27,    28,    29,    30,     0,
       0,     0,     0,     0,    31,    66,    67,    68,    69,    70,
      32,     0,     0,     0,    33,    34,     0,    71,    35,    16,
      17,     2,    18,     0,    72,    73,    74,    75,    76,    77,
      78,     0,     0,     0,    22,    23,    79,    25,    80,     0,
       0,     0,     0,     0,     0,     0,     0,   134,     0,     0,
      31,    66,    67,    68,    69,    70,    32,     0,     0,     0,
      33,    34,     0,    71,     0,     0,     0,     0,     0,     0,
      72,    73,    74,    75,    76,    77,    78,    66,    67,    68,
      69,    70,    79,     0,    80,     0,     0,     0,     0,    71,
     149,     0,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    78,    66,    67,    68,    69,    70,    79,     0,
      80,     0,     0,     0,     0,    71,   153,     0,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    66,
      67,    68,    69,    70,    79,     0,    80,     0,     0,    98,
       0,    71,     0,     0,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    78,    66,    67,    68,    69,    70,
      79,     0,    80,     0,     0,   123,     0,    71,     0,     0,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      78,    66,    67,    68,    69,    70,    79,     0,    80,     0,
       0,   124,     0,    71,     0,     0,     0,     0,     0,     0,
      72,    73,    74,    75,    76,    77,    78,    66,    67,    68,
      69,    70,    79,     0,    80,     0,     0,   127,     0,    71,
       0,     0,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    78,    66,    67,    68,    69,    70,    79,     0,
      80,     0,     0,   151,     0,    71,     0,     0,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    66,
      67,    68,    69,    70,    79,     0,    80,     0,     0,   152,
       0,    71,     0,     0,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    78,    66,    67,    68,    69,    70,
      79,     0,    80,     0,     0,   154,     0,    71,     0,     0,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      78,    68,    69,    70,     0,     0,    79,     0,    80,     0,
       0,    71,     0,     0,     0,     0,     0,     0,    72,    73,
      74,    75,    76,    77,    78,     0,     0,     0,     0,     0,
      79,     0,    80
};

static const short yycheck[] =
{
      13,    21,    86,     5,    52,     9,     5,     5,    21,     0,
      42,    45,    47,    29,     5,    47,    20,    37,    15,    47,
       5,    34,    35,    51,    37,    30,    31,    32,    33,    34,
      16,    17,    18,    19,    50,    32,    33,    34,    35,    36,
      29,    46,    47,    29,    42,    42,    51,    44,    51,   133,
      52,    47,   136,    52,    47,    51,    45,    49,    51,    45,
      48,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,     1,    80,    81,    82,     5,     6,
      85,    86,    45,    35,    36,    12,    42,    14,    44,    50,
      42,    96,    44,    50,    99,    22,    23,    33,    34,    35,
      36,    45,    45,   123,   124,   153,    42,   127,    44,    49,
     123,   124,    45,    51,   127,    53,   121,    44,    42,    45,
     125,   126,    45,   128,   129,    52,    45,   132,   133,    50,
     150,   136,    29,     8,   154,    50,    50,   150,    47,     0,
      35,   154,   147,   163,    -1,    -1,    -1,    -1,    -1,    -1,
     163,    -1,    79,    -1,    -1,     3,     4,     5,     6,     7,
      87,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    19,    20,    21,    -1,    -1,    24,    25,    26,    27,
      28,    -1,    16,    17,    18,    19,    34,    -1,    -1,    23,
      -1,    -1,    40,    -1,    -1,    29,    44,    45,    -1,    -1,
      48,    -1,    50,     3,     4,     5,     6,     7,    -1,     9,
      10,    45,    -1,    -1,    -1,    -1,    -1,    -1,    18,    19,
      20,    21,    -1,    -1,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    -1,    -1,    34,    11,    12,    13,    14,    15,
      40,    -1,    -1,    -1,    44,    45,    -1,    23,    48,     3,
       4,     5,     6,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    -1,    18,    19,    42,    21,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      34,    11,    12,    13,    14,    15,    40,    -1,    -1,    -1,
      44,    45,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    11,    12,    13,
      14,    15,    42,    -1,    44,    -1,    -1,    -1,    -1,    23,
      50,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    11,    12,    13,    14,    15,    42,    -1,
      44,    -1,    -1,    -1,    -1,    23,    50,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    11,
      12,    13,    14,    15,    42,    -1,    44,    -1,    -1,    47,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    11,    12,    13,    14,    15,
      42,    -1,    44,    -1,    -1,    47,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    11,    12,    13,    14,    15,    42,    -1,    44,    -1,
      -1,    47,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    11,    12,    13,
      14,    15,    42,    -1,    44,    -1,    -1,    47,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    11,    12,    13,    14,    15,    42,    -1,
      44,    -1,    -1,    47,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    11,
      12,    13,    14,    15,    42,    -1,    44,    -1,    -1,    47,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    11,    12,    13,    14,    15,
      42,    -1,    44,    -1,    -1,    47,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    13,    14,    15,    -1,    -1,    42,    -1,    44,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    44
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

case 3:
#line 87 "grammar.y"
{ sxp_new_func (sxp_parser_info, yyvsp[-6].id, (SX_ARRAY )yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
    break;
case 4:
#line 90 "grammar.y"
{ yyval.node = NULL; }
    break;
case 5:
#line 91 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 6:
#line 94 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 7:
#line 95 "grammar.y"
{ yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;
case 8:
#line 98 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 9:
#line 99 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 10:
#line 100 "grammar.y"
{ yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;
case 11:
#line 101 "grammar.y"
{ yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 12:
#line 102 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_WD); }
    break;
case 13:
#line 103 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_UD); }
    break;
case 14:
#line 104 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DW); }
    break;
case 15:
#line 105 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DU); }
    break;
case 16:
#line 107 "grammar.y"
{ yyval.node = sxp_new_for (sxp_parser_info, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 17:
#line 108 "grammar.y"
{ yyval.node = sxp_new_cfor (sxp_parser_info, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 18:
#line 110 "grammar.y"
{}
    break;
case 19:
#line 111 "grammar.y"
{}
    break;
case 20:
#line 113 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 21:
#line 116 "grammar.y"
{ yyval.node = NULL; }
    break;
case 22:
#line 117 "grammar.y"
{ yyval.node = sxp_new_stmt (sxp_parser_info, yyvsp[0].node); }
    break;
case 23:
#line 120 "grammar.y"
{ yyval.node = sxp_new_retr (sxp_parser_info, yyvsp[0].node); }
    break;
case 24:
#line 121 "grammar.y"
{ yyval.node = sxp_new_retr (sxp_parser_info, NULL); }
    break;
case 25:
#line 122 "grammar.y"
{ yyval.node = sxp_new_brak (sxp_parser_info); }
    break;
case 26:
#line 123 "grammar.y"
{ yyval.node = sxp_new_cont (sxp_parser_info); }
    break;
case 27:
#line 124 "grammar.y"
{ yyval.node = sxp_new_yeld (sxp_parser_info); }
    break;
case 28:
#line 127 "grammar.y"
{ yyval.node = NULL; }
    break;
case 29:
#line 128 "grammar.y"
{ yyval.node = yyvsp[0].node; }
    break;
case 30:
#line 129 "grammar.y"
{ yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
    break;
case 31:
#line 132 "grammar.y"
{ yyval.args.args = NULL; yyval.args.varg = 0; }
    break;
case 32:
#line 133 "grammar.y"
{ yyval.args.args = yyvsp[0].value; yyval.args.varg = 0; }
    break;
case 33:
#line 134 "grammar.y"
{ yyval.args.args = yyvsp[-3].value; yyval.args.varg = yyvsp[0].id; }
    break;
case 34:
#line 135 "grammar.y"
{ yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;
case 35:
#line 138 "grammar.y"
{ yyval.value = sx_append (sxp_parser_info->system, sx_new_array (sxp_parser_info->system, 0, NULL), sx_new_num (yyvsp[0].id)); }
    break;
case 36:
#line 139 "grammar.y"
{ yyval.value = sx_append (sxp_parser_info->system, yyvsp[-2].value, sx_new_num (yyvsp[0].id)); }
    break;
case 37:
#line 142 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 38:
#line 143 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 39:
#line 144 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 40:
#line 145 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 41:
#line 146 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
    break;
case 42:
#line 148 "grammar.y"
{ yyval.node = sxp_new_in (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 43:
#line 150 "grammar.y"
{ yyval.node = sxp_new_nega (sxp_parser_info, yyvsp[0].node); }
    break;
case 44:
#line 152 "grammar.y"
{ yyval.node = sxp_new_not (sxp_parser_info, yyvsp[0].node); }
    break;
case 45:
#line 153 "grammar.y"
{ yyval.node = sxp_new_and (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 46:
#line 154 "grammar.y"
{ yyval.node = sxp_new_or (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 47:
#line 156 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 48:
#line 157 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 49:
#line 158 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 50:
#line 159 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 51:
#line 160 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 52:
#line 161 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 53:
#line 163 "grammar.y"
{ yyval.node = sxp_new_assi (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 54:
#line 164 "grammar.y"
{ yyval.node = sxp_new_set (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;
case 55:
#line 165 "grammar.y"
{ yyval.node = sxp_new_setm (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 56:
#line 167 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 57:
#line 168 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, sxp_new_nega (sxp_parser_info, yyvsp[0].node)); }
    break;
case 58:
#line 169 "grammar.y"
{ yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
    break;
case 59:
#line 170 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
    break;
case 60:
#line 171 "grammar.y"
{ yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
    break;
case 61:
#line 172 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
    break;
case 62:
#line 174 "grammar.y"
{ yyval.node = sxp_new_cast (sxp_parser_info, yyvsp[0].node, yyvsp[-2].id); }
    break;
case 63:
#line 175 "grammar.y"
{ yyval.node = sxp_new_call (sxp_parser_info, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 64:
#line 177 "grammar.y"
{ yyval.node = sxp_new_smet (sxp_parser_info, yyvsp[-5].id, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 65:
#line 178 "grammar.y"
{ yyval.node = sxp_new_meth (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 66:
#line 179 "grammar.y"
{ yyval.node = sxp_new_getm (sxp_parser_info, yyvsp[-2].node, yyvsp[0].id); }
    break;
case 67:
#line 181 "grammar.y"
{ yyval.node = sxp_new_indx (sxp_parser_info, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 68:
#line 182 "grammar.y"
{ yyval.node = sxp_new_arry (sxp_parser_info, yyvsp[-1].node); }
    break;
case 69:
#line 184 "grammar.y"
{ yyval.node = sxp_new_data (sxp_parser_info, yyvsp[0].value); }
    break;
case 70:
#line 186 "grammar.y"
{ yyval.node = sxp_new_name (sxp_parser_info, yyvsp[0].id); }
    break;
case 71:
#line 190 "grammar.y"
{ yyval.value = yyvsp[0].value;  }
    break;
case 72:
#line 191 "grammar.y"
{ yyval.value = yyvsp[0].value; }
    break;
case 73:
#line 192 "grammar.y"
{ yyval.value = NULL; }
    break;
case 74:
#line 195 "grammar.y"
{ yyval.id = yyvsp[0].id; }
    break;
case 75:
#line 198 "grammar.y"
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
#line 201 "grammar.y"


int
sxerror (const char *str) {
	if (sxp_parser_info->system->error_hook != NULL) {
		char buffer[512];
		snprintf (buffer, 512, "File %s, line %d: %s", sxp_parser_info->file ? SX_TOSTRING (sxp_parser_info->file)->str : "<input>", sxp_parser_info->line, str);
		sxp_parser_info->system->error_hook (buffer);
	} else {
		fprintf (stderr, "Scriptix Error: File %s, line %d: %s\n", sxp_parser_info->file ? SX_TOSTRING (sxp_parser_info->file)->str : "<input>", sxp_parser_info->line, str);
	}
	return 1;
}

int
sxwrap (void) {
	return 1;
}

int
sxp_load_file (SX_MODULE module, const char *file) {
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

	sxp_parser_info = sxp_new_info (module);
	if (sxp_parser_info == NULL) {
		if (file != NULL)
			fclose (sxin);
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}
	if (file != NULL)
		sxp_parser_info->file = sx_new_str (module->system, file);

	sxp_parser_inbuf = NULL;
	flags = module->system->flags;
	module->system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	module->system->flags = flags;

	if (file != NULL) {
		fclose (sxin);
	}

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (module->system);

	return ret;
}

int
sxp_load_string (SX_MODULE module, const char *buf) {
	int ret, flags;

	if (buf == NULL) {
		return 1;
	}

	sxp_parser_info = sxp_new_info (module);
	if (sxp_parser_info == NULL) {
		fprintf (stderr, "Failed to create info\n");
		return 1;
	}

	sxin = NULL;
	sxp_parser_inbuf = buf;
	flags = module->system->flags;
	module->system->flags |= SX_SFLAG_GCOFF;

	ret = sxparse ();

	module->system->flags = flags;

	if (!ret) {
		ret = sxp_compile (sxp_parser_info);
	}

	sxp_del_info (sxp_parser_info);

	sx_run_gc (module->system);

	return ret;
}
