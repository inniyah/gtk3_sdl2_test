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
# define	TEXTEND	272
# define	TADDASSIGN	273
# define	TSUBASSIGN	274
# define	TINCREMENT	275
# define	TDECREMENT	276
# define	TNEW	277
# define	TUNTIL	278
# define	TNIL	279
# define	TRESCUE	280
# define	TIN	281
# define	TFOR	282
# define	TCONTINUE	283
# define	TYIELD	284
# define	TPUBLIC	285
# define	TBREAK	286
# define	TRETURN	287
# define	TEQUALS	288
# define	TLENGTH	289
# define	CUNARY	290
# define	TCAST	291

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
	NameID id;
	NameList* names;
	struct ParserArgList args;
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
#define YYTRANSLATE(x) ((unsigned)(x) <= 291 ? yytranslate[x] : 79)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,     2,     2,     2,    57,     2,
      51,    52,    41,    38,    56,    39,    47,    42,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    55,
      36,    34,    35,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    58,    50,     2,     2,     2,     2,     2,
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
      26,    27,    28,    29,    30,    31,    32,    33,    37,    43,
      45,    46
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     7,    10,    13,    21,    30,    31,
      41,    46,    47,    54,    62,    64,    67,    68,    70,    72,
      75,    78,    82,    85,    88,    91,    94,   100,   108,   114,
     120,   128,   136,   139,   149,   157,   161,   162,   164,   166,
     170,   171,   173,   178,   181,   183,   187,   191,   194,   198,
     202,   206,   210,   214,   218,   222,   225,   228,   232,   236,
     240,   244,   248,   252,   256,   260,   264,   271,   275,   279,
     282,   285,   288,   291,   296,   301,   304,   307,   312,   317,
     323,   327,   332,   336,   338,   340,   342,   344,   346,   348,
     350
};
static const short yyrhs[] =
{
      -1,    59,    60,     0,    59,    62,     0,    59,     1,     0,
      59,    63,     0,    77,    51,    72,    52,    53,    67,    54,
       0,    31,    77,    51,    72,    52,    53,    67,    54,     0,
       0,    77,    61,    77,    51,    72,    52,    53,    67,    54,
       0,    77,    34,    76,    55,     0,     0,    18,    78,    64,
      53,    66,    54,     0,    77,    51,    72,    52,    53,    67,
      54,     0,    65,     0,    66,    65,     0,     0,    68,     0,
      69,     0,    68,    69,     0,    70,    55,     0,    33,    75,
      55,     0,    33,    55,     0,    32,    55,     0,    29,    55,
       0,    30,    55,     0,     8,    51,    75,    52,    69,     0,
       8,    51,    75,    52,    69,     9,    69,     0,    10,    51,
      75,    52,    69,     0,    24,    51,    75,    52,    69,     0,
      11,    69,    10,    51,    75,    52,    55,     0,    11,    69,
      24,    51,    75,    52,    55,     0,    11,    69,     0,    28,
      51,    70,    55,    75,    55,    70,    52,    69,     0,    17,
      51,    77,    27,    75,    52,    69,     0,    53,    67,    54,
       0,     0,    75,     0,    75,     0,    71,    56,    75,     0,
       0,    73,     0,    73,    56,    57,    77,     0,    57,    77,
       0,    77,     0,    73,    56,    77,     0,    51,    71,    52,
       0,    51,    52,     0,    75,    38,    75,     0,    75,    39,
      75,     0,    75,    41,    75,     0,    75,    42,    75,     0,
      75,    40,    75,     0,    51,    75,    52,     0,    75,    27,
      75,     0,    39,    75,     0,    44,    75,     0,    75,    12,
      75,     0,    75,    13,    75,     0,    75,    35,    75,     0,
      75,    36,    75,     0,    75,    16,    75,     0,    75,    14,
      75,     0,    75,    15,    75,     0,    75,    37,    75,     0,
      77,    34,    75,     0,    75,    49,    75,    58,    34,    75,
       0,    77,    19,    75,     0,    77,    20,    75,     0,    77,
      21,     0,    21,    77,     0,    77,    22,     0,    22,    77,
       0,    51,    78,    52,    75,     0,    78,    51,    75,    52,
       0,    75,    74,     0,    23,    78,     0,    75,    47,    77,
      74,     0,    78,    47,    77,    74,     0,    75,    48,    77,
      34,    75,     0,    75,    48,    77,     0,    75,    49,    75,
      58,     0,    49,    71,    58,     0,    76,     0,    77,     0,
       1,     0,     3,     0,     4,     0,    25,     0,     5,     0,
       6,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    95,    96,    97,    98,    99,   102,   103,   104,   104,
     113,   116,   116,   119,   122,   123,   126,   127,   130,   131,
     134,   135,   136,   137,   138,   139,   141,   142,   143,   144,
     145,   146,   147,   149,   150,   152,   155,   156,   159,   160,
     163,   164,   165,   166,   169,   170,   173,   174,   177,   178,
     179,   180,   181,   182,   184,   186,   193,   194,   195,   197,
     198,   199,   200,   201,   202,   204,   205,   207,   208,   209,
     210,   211,   212,   214,   215,   217,   219,   220,   221,   222,
     223,   225,   226,   228,   230,   232,   236,   237,   238,   241,
     244
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "NUMBER", "STRING", "IDENTIFIER", "TYPE", 
  "TAG", "IF", "ELSE", "WHILE", "DO", "AND", "OR", "TGTE", "TLTE", "TNE", 
  "TFOREACH", "TEXTEND", "TADDASSIGN", "TSUBASSIGN", "TINCREMENT", 
  "TDECREMENT", "TNEW", "TUNTIL", "TNIL", "TRESCUE", "TIN", "TFOR", 
  "TCONTINUE", "TYIELD", "TPUBLIC", "TBREAK", "TRETURN", "'='", "'>'", 
  "'<'", "TEQUALS", "'+'", "'-'", "'@'", "'*'", "'/'", "TLENGTH", "'!'", 
  "CUNARY", "TCAST", "'.'", "':'", "'['", "'^'", "'('", "')'", "'{'", 
  "'}'", "';'", "','", "'&'", "']'", "program", "function", "@1", 
  "global", "extend", "@2", "extend_function", "extend_functions", 
  "block", "stmts", "stmt", "node", "args", "arg_names", "arg_names_list", 
  "func_args", "expr", "data", "name", "type", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    59,    59,    59,    59,    59,    60,    60,    61,    60,
      62,    64,    63,    65,    66,    66,    67,    67,    68,    68,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      72,    72,    72,    72,    73,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    76,    76,    76,    77,
      78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     2,     2,     2,     7,     8,     0,     9,
       4,     0,     6,     7,     1,     2,     0,     1,     1,     2,
       2,     3,     2,     2,     2,     2,     5,     7,     5,     5,
       7,     7,     2,     9,     7,     3,     0,     1,     1,     3,
       0,     1,     4,     2,     1,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     6,     3,     3,     2,
       2,     2,     2,     4,     4,     2,     2,     4,     4,     5,
       3,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     4,    89,     0,     0,     2,     3,     5,     8,
      90,    11,     0,     0,    40,     0,     0,    40,    86,    87,
      88,     0,     0,     0,    41,    44,     0,     0,     0,    10,
      43,     0,     0,    40,    14,     0,     0,     0,     0,     0,
      45,     0,    12,    15,    40,     0,    85,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    18,     0,    37,
      83,    84,     0,    42,     0,     0,     0,     0,     0,    32,
       0,    70,    72,    76,     0,     0,    24,    25,    23,    22,
       0,    55,    56,     0,    38,     0,     0,     0,     6,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    75,
       0,     0,    69,    71,     0,     0,     0,     0,     0,     7,
       0,     0,     0,     0,     0,     0,     0,    21,     0,    82,
      53,     0,    35,    57,    58,    62,    63,    61,    54,    59,
      60,    64,    48,    49,    52,    50,    51,     0,    80,     0,
      47,     0,    67,    68,    65,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,    73,    77,     0,
      81,    46,    78,    74,     9,     0,    26,    28,     0,     0,
       0,    29,     0,    79,     0,    13,     0,     0,     0,     0,
       0,    66,    27,    30,    31,    34,     0,     0,    33,     0,
       0
};

static const short yydefgoto[] =
{
       1,     6,    15,     7,     8,    16,    34,    35,    65,    66,
      67,    68,    93,    23,    24,   119,    69,    70,    71,    72
};

static const short yypact[] =
{
  -32768,    10,-32768,-32768,    -5,    19,-32768,-32768,-32768,   -22,
  -32768,-32768,   -37,    34,     8,    19,   -28,     8,-32768,-32768,
  -32768,   -16,    19,   -10,    23,-32768,    29,    19,    30,-32768,
  -32768,    32,    13,     8,-32768,    17,    35,    37,   177,    19,
  -32768,    43,-32768,-32768,     8,   177,-32768,    36,    56,   287,
      57,    19,    19,    -5,    58,    59,    62,    64,    76,   324,
     386,   386,   386,   386,   177,    78,   232,-32768,    79,   790,
  -32768,   132,   -11,-32768,    80,    83,    82,   386,   386,     9,
      19,-32768,-32768,-32768,   386,   349,-32768,-32768,-32768,-32768,
     466,    55,    55,    16,   790,   554,   -17,    84,-32768,-32768,
  -32768,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,    19,    19,   386,   123,-32768,
     386,   386,-32768,-32768,   386,    19,   386,   177,    86,-32768,
     572,   613,    60,    89,   115,   631,    88,-32768,   386,-32768,
  -32768,   386,-32768,   807,   807,   407,   407,   318,   407,   407,
     407,   318,    50,    50,    50,    55,    55,    98,   121,   426,
  -32768,    21,   790,   790,   790,    98,   672,   102,   177,   287,
     287,   386,   386,   386,   287,   386,   790,    55,-32768,   386,
     125,-32768,-32768,-32768,-32768,   103,   151,-32768,   690,   731,
     749,-32768,   510,   790,   386,-32768,   287,   106,   108,   287,
     380,   790,-32768,-32768,-32768,-32768,   112,   287,-32768,   165,
  -32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,   133,-32768,   -38,-32768,
     -49,   -77,    51,    -1,-32768,  -134,   -57,   157,    61,     5
};


#define	YYLAST		858


static const short yytable[] =
{
      79,    10,    90,    91,    92,    94,    95,    76,   136,    11,
     209,     2,    13,     3,    17,     3,    28,    99,     3,-32768,
     130,   131,     3,   178,     3,    27,    97,   135,     4,    14,
     125,   182,    41,-32768,   126,   141,   125,    18,    19,    29,
     126,     5,    31,    75,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,    83,    20,
     159,    94,     9,   162,   163,    22,    12,   164,    96,   166,
      39,    42,   138,   181,   139,    25,    26,   138,    25,    32,
      33,   176,    37,    30,   177,    38,    44,    77,    36,   167,
      45,   113,   114,    40,    25,    74,    36,   115,   116,   117,
      73,   118,   115,   116,   117,    25,   118,    78,    80,    84,
      85,   171,    81,    82,   188,   189,   190,    86,   192,    87,
     186,   187,   193,   206,    46,   191,    18,    19,     3,    10,
     185,    88,    98,   127,   100,   128,   129,   201,   142,   168,
     172,   134,   173,   175,    51,    52,    53,   202,    20,   118,
     205,   120,   121,   122,   123,   179,   184,   195,   208,   194,
     196,   203,    60,   204,   207,   210,   124,    61,    43,   161,
      21,     0,    62,     0,    63,   160,   157,   158,    46,     0,
      18,    19,     3,    10,     0,    47,   165,    48,    49,     0,
       0,     0,     0,     0,    50,     0,     0,     0,    51,    52,
      53,    54,    20,     0,     0,    55,    56,    57,     0,    58,
      59,     0,     0,     0,     0,     0,    60,     0,     0,     0,
       0,    61,     0,     0,     0,     0,    62,     0,    63,     0,
      64,   -16,   -36,    46,     0,    18,    19,     3,    10,     0,
      47,     0,    48,    49,     0,     0,     0,     0,     0,    50,
       0,     0,     0,    51,    52,    53,    54,    20,     0,     0,
      55,    56,    57,     0,    58,    59,     0,     0,     0,     0,
       0,    60,     0,     0,     0,     0,    61,     0,     0,     0,
       0,    62,     0,    63,     0,    64,   -17,   -36,    46,     0,
      18,    19,     3,    10,     0,    47,     0,    48,    49,     0,
       0,     0,     0,     0,    50,     0,     0,     0,    51,    52,
      53,    54,    20,     0,     0,    55,    56,    57,     0,    58,
      59,     0,     0,     0,     0,    46,    60,    18,    19,     3,
      10,    61,     0,     0,     0,     0,    62,     0,    63,     0,
      64,     0,   -36,     0,     0,    51,    52,    53,     0,    20,
      46,     0,    18,    19,     3,    10,   110,   111,   112,   113,
     114,     0,     0,    60,     0,   115,   116,   117,    61,   118,
      51,    52,    53,    62,    20,    63,     0,     0,     0,    89,
       0,    46,     0,    18,    19,     3,    10,    46,    60,    18,
      19,     3,    10,    61,     0,     0,     0,     0,    62,     0,
      63,    51,    52,    53,   -36,    20,     0,    51,    52,    53,
       0,    20,     0,     0,     0,     0,     0,     0,     0,    60,
       0,     0,     0,   105,    61,    60,     0,     0,     0,    62,
      61,    63,   -36,     0,     0,    62,     0,    63,   101,   102,
     103,   104,   105,     0,   109,   110,   111,   112,   113,   114,
       0,     0,     0,   106,   115,   116,   117,     0,   118,     0,
       0,   107,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,     0,   115,   116,   117,     0,   118,   101,   102,
     103,   104,   105,     0,   180,     0,     0,     0,     0,     0,
       0,     0,     0,   106,     0,     0,     0,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   112,   113,   114,     0,
       0,     0,     0,   115,   116,   117,     0,   118,     0,     0,
       0,   137,   101,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,     0,     0,
       0,     0,     0,     0,     0,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,   115,   116,   117,
       0,   118,     0,     0,     0,   200,   101,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,   101,   102,   103,   104,   105,   107,
     108,   109,   110,   111,   112,   113,   114,     0,     0,   106,
       0,   115,   116,   117,     0,   118,   140,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,     0,     0,   115,
     116,   117,     0,   118,   169,   101,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     106,     0,     0,   101,   102,   103,   104,   105,   107,   108,
     109,   110,   111,   112,   113,   114,     0,     0,   106,     0,
     115,   116,   117,     0,   118,   170,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,     0,     0,   115,   116,
     117,     0,   118,   174,   101,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
       0,     0,   101,   102,   103,   104,   105,   107,   108,   109,
     110,   111,   112,   113,   114,     0,     0,   106,     0,   115,
     116,   117,     0,   118,   183,   107,   108,   109,   110,   111,
     112,   113,   114,     0,     0,     0,     0,   115,   116,   117,
       0,   118,   197,   101,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   106,     0,
       0,   101,   102,   103,   104,   105,   107,   108,   109,   110,
     111,   112,   113,   114,     0,     0,   106,     0,   115,   116,
     117,     0,   118,   198,   107,   108,   109,   110,   111,   112,
     113,   114,     0,     0,     0,     0,   115,   116,   117,     0,
     118,   199,   101,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   106,     0,     0,
       0,   103,   104,   105,     0,   107,   108,   109,   110,   111,
     112,   113,   114,     0,   106,     0,     0,   115,   116,   117,
       0,   118,   107,   108,   109,   110,   111,   112,   113,   114,
       0,     0,     0,     0,   115,   116,   117,     0,   118
};

static const short yycheck[] =
{
      49,     6,    59,    60,    61,    62,    63,    45,    85,     4,
       0,     1,    34,     5,    51,     5,    17,    66,     5,    10,
      77,    78,     5,   157,     5,    53,    64,    84,    18,    51,
      47,   165,    33,    24,    51,    52,    47,     3,     4,    55,
      51,    31,    52,    44,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    53,    25,
     117,   118,     1,   120,   121,    57,     5,   124,    63,   126,
      57,    54,    56,    52,    58,    14,    15,    56,    17,    56,
      51,   138,    52,    22,   141,    53,    51,    51,    27,   127,
      53,    41,    42,    32,    33,    52,    35,    47,    48,    49,
      39,    51,    47,    48,    49,    44,    51,    51,    51,    51,
      51,    51,    51,    52,   171,   172,   173,    55,   175,    55,
     169,   170,   179,   200,     1,   174,     3,     4,     5,     6,
     168,    55,    54,    53,    55,    52,    54,   194,    54,    53,
      51,    80,    27,    55,    21,    22,    23,   196,    25,    51,
     199,    19,    20,    21,    22,    34,    54,    54,   207,    34,
       9,    55,    39,    55,    52,     0,    34,    44,    35,   118,
      13,    -1,    49,    -1,    51,    52,   115,   116,     1,    -1,
       3,     4,     5,     6,    -1,     8,   125,    10,    11,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    -1,    32,
      33,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    51,    -1,
      53,    54,    55,     1,    -1,     3,     4,     5,     6,    -1,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    -1,    32,    33,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    49,    -1,    51,    -1,    53,    54,    55,     1,    -1,
       3,     4,     5,     6,    -1,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    -1,    32,
      33,    -1,    -1,    -1,    -1,     1,    39,     3,     4,     5,
       6,    44,    -1,    -1,    -1,    -1,    49,    -1,    51,    -1,
      53,    -1,    55,    -1,    -1,    21,    22,    23,    -1,    25,
       1,    -1,     3,     4,     5,     6,    38,    39,    40,    41,
      42,    -1,    -1,    39,    -1,    47,    48,    49,    44,    51,
      21,    22,    23,    49,    25,    51,    -1,    -1,    -1,    55,
      -1,     1,    -1,     3,     4,     5,     6,     1,    39,     3,
       4,     5,     6,    44,    -1,    -1,    -1,    -1,    49,    -1,
      51,    21,    22,    23,    55,    25,    -1,    21,    22,    23,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    16,    44,    39,    -1,    -1,    -1,    49,
      44,    51,    52,    -1,    -1,    49,    -1,    51,    12,    13,
      14,    15,    16,    -1,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    27,    47,    48,    49,    -1,    51,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    -1,    51,    12,    13,
      14,    15,    16,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    -1,    47,    48,    49,    -1,    51,    -1,    -1,
      -1,    55,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    -1,    -1,    55,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    12,    13,    14,    15,    16,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    -1,    27,
      -1,    47,    48,    49,    -1,    51,    52,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    51,    52,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    12,    13,    14,    15,    16,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    27,    -1,
      47,    48,    49,    -1,    51,    52,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    47,    48,
      49,    -1,    51,    52,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    12,    13,    14,    15,    16,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    27,    -1,    47,
      48,    49,    -1,    51,    52,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    49,
      -1,    51,    52,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,
      -1,    12,    13,    14,    15,    16,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    -1,    27,    -1,    47,    48,
      49,    -1,    51,    52,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,
      51,    52,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,
      -1,    14,    15,    16,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    27,    -1,    -1,    47,    48,    49,
      -1,    51,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    -1,    -1,    47,    48,    49,    -1,    51
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

case 6:
#line 102 "grammar.yy"
{ parser->AddFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, 0, false); delete yyvsp[-4].args.args; }
    break;
case 7:
#line 103 "grammar.yy"
{ parser->AddFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, 0, true); delete yyvsp[-4].args.args; }
    break;
case 8:
#line 104 "grammar.yy"
{ 
		if (!parser->GetSystem()->ValidFunctionTag(yyvsp[0].id)) {
			yyerror ("Unregistered tag");
			YYERROR;
		}
		yyval.id = yyvsp[0].id;
	}
    break;
case 9:
#line 110 "grammar.yy"
{ parser->AddFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node, yyvsp[-7].id, false); delete yyvsp[-4].args.args; }
    break;
case 10:
#line 113 "grammar.yy"
{ parser->SetGlobal(yyvsp[-3].id, yyvsp[-1].value); }
    break;
case 11:
#line 116 "grammar.yy"
{ parser->AddExtend (parser->system->GetType(yyvsp[0].id)); }
    break;
case 13:
#line 119 "grammar.yy"
{ parser->AddExtendFunc(yyvsp[-6].id, (yyvsp[-4].args.args ? *yyvsp[-4].args.args : NameList()), yyvsp[-4].args.varg, yyvsp[-1].node); delete yyvsp[-4].args.args; }
    break;
case 16:
#line 126 "grammar.yy"
{ yyval.node = NULL; }
    break;
case 17:
#line 127 "grammar.yy"
{ yyval.node = yyvsp[0].node; }
    break;
case 18:
#line 130 "grammar.yy"
{ yyval.node = yyvsp[0].node; }
    break;
case 19:
#line 131 "grammar.yy"
{ yyval.node = yyvsp[-1].node; yyval.node->Append(yyvsp[0].node); }
    break;
case 20:
#line 134 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 21:
#line 135 "grammar.yy"
{ yyval.node = sxp_new_return (parser, yyvsp[-1].node); }
    break;
case 22:
#line 136 "grammar.yy"
{ yyval.node = sxp_new_return (parser, NULL); }
    break;
case 23:
#line 137 "grammar.yy"
{ yyval.node = sxp_new_break (parser); }
    break;
case 24:
#line 138 "grammar.yy"
{ yyval.node = sxp_new_continue (parser); }
    break;
case 25:
#line 139 "grammar.yy"
{ yyval.node = sxp_new_yield (parser); }
    break;
case 26:
#line 141 "grammar.yy"
{ yyval.node = sxp_new_if (parser, yyvsp[-2].node, yyvsp[0].node, NULL); }
    break;
case 27:
#line 142 "grammar.yy"
{ yyval.node = sxp_new_if (parser, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 28:
#line 143 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_WHILE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 29:
#line 144 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_UNTIL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 30:
#line 145 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_DOWHILE, yyvsp[-2].node, yyvsp[-5].node); }
    break;
case 31:
#line 146 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_DOUNTIL, yyvsp[-2].node, yyvsp[-5].node); }
    break;
case 32:
#line 147 "grammar.yy"
{ yyval.node = sxp_new_loop (parser, SXP_LOOP_FOREVER, NULL, yyvsp[0].node); }
    break;
case 33:
#line 149 "grammar.yy"
{ yyval.node = sxp_new_for (parser, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 34:
#line 150 "grammar.yy"
{ yyval.node = sxp_new_foreach (parser, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 35:
#line 152 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 36:
#line 155 "grammar.yy"
{ yyval.node = NULL; }
    break;
case 37:
#line 156 "grammar.yy"
{ yyval.node = sxp_new_statement (parser, yyvsp[0].node); }
    break;
case 38:
#line 159 "grammar.yy"
{ yyval.node = yyvsp[0].node; }
    break;
case 39:
#line 160 "grammar.yy"
{ yyval.node = yyvsp[-2].node; yyval.node->Append(yyvsp[0].node); }
    break;
case 40:
#line 163 "grammar.yy"
{ yyval.args.args = NULL; yyval.args.varg = 0; }
    break;
case 41:
#line 164 "grammar.yy"
{ yyval.args.args = yyvsp[0].names; yyval.args.varg = 0; }
    break;
case 42:
#line 165 "grammar.yy"
{ yyval.args.args = yyvsp[-3].names; yyval.args.varg = yyvsp[0].id; }
    break;
case 43:
#line 166 "grammar.yy"
{ yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
    break;
case 44:
#line 169 "grammar.yy"
{ yyval.names = new NameList(); yyval.names->push_back(yyvsp[0].id); }
    break;
case 45:
#line 170 "grammar.yy"
{ yyval.names->push_back(yyvsp[0].id); }
    break;
case 46:
#line 173 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 47:
#line 174 "grammar.yy"
{ yyval.node = NULL; }
    break;
case 48:
#line 177 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 49:
#line 178 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 50:
#line 179 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 51:
#line 180 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 52:
#line 181 "grammar.yy"
{ yyval.node = sxp_new_concat (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 53:
#line 182 "grammar.yy"
{ yyval.node = yyvsp[-1].node; }
    break;
case 54:
#line 184 "grammar.yy"
{ yyval.node = sxp_new_in (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 55:
#line 186 "grammar.yy"
{
			if (yyvsp[0].node->type == SXP_DATA && Value::IsA<Number>(parser->system, yyvsp[0].node->parts.value))
				yyval.node = sxp_new_data(parser,Number::Create(-Number::ToInt(yyvsp[0].node->parts.value)));
			else
				yyval.node = sxp_new_negate (parser, yyvsp[0].node); 
		}
    break;
case 56:
#line 193 "grammar.yy"
{ yyval.node = sxp_new_not (parser, yyvsp[0].node); }
    break;
case 57:
#line 194 "grammar.yy"
{ yyval.node = sxp_new_and (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 58:
#line 195 "grammar.yy"
{ yyval.node = sxp_new_or (parser, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 59:
#line 197 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_GT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 60:
#line 198 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_LT, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 61:
#line 199 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 62:
#line 200 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 63:
#line 201 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 64:
#line 202 "grammar.yy"
{ yyval.node = sxp_new_math (parser, OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
    break;
case 65:
#line 204 "grammar.yy"
{ yyval.node = sxp_new_assign (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 66:
#line 205 "grammar.yy"
{ yyval.node = sxp_new_setindex (parser, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
    break;
case 67:
#line 207 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 68:
#line 208 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[-2].id, sxp_new_negate (parser, yyvsp[0].node)); }
    break;
case 69:
#line 209 "grammar.yy"
{ yyval.node = sxp_new_postinc (parser, yyvsp[-1].id, sxp_new_data (parser, Number::Create (1))); }
    break;
case 70:
#line 210 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[0].id, sxp_new_data (parser, Number::Create (1))); }
    break;
case 71:
#line 211 "grammar.yy"
{ yyval.node = sxp_new_postinc (parser, yyvsp[-1].id, sxp_new_data (parser, Number::Create (-1))); }
    break;
case 72:
#line 212 "grammar.yy"
{ yyval.node = sxp_new_preinc (parser, yyvsp[0].id, sxp_new_data (parser, Number::Create (-1))); }
    break;
case 73:
#line 214 "grammar.yy"
{ yyval.node = sxp_new_cast (parser, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 74:
#line 215 "grammar.yy"
{ yyval.node = sxp_new_cast (parser, yyvsp[-3].id, yyvsp[-1].node); }
    break;
case 75:
#line 217 "grammar.yy"
{ yyval.node = sxp_new_invoke (parser, yyvsp[-1].node, yyvsp[0].node); }
    break;
case 76:
#line 219 "grammar.yy"
{ yyval.node = sxp_new_new (parser, yyvsp[0].id); }
    break;
case 77:
#line 220 "grammar.yy"
{ yyval.node = sxp_new_method (parser, yyvsp[-3].node, yyvsp[-1].id, yyvsp[0].node); }
    break;
case 78:
#line 221 "grammar.yy"
{ yyval.node = sxp_new_smethod (parser, yyvsp[-3].id, yyvsp[-1].id, yyvsp[0].node); }
    break;
case 79:
#line 222 "grammar.yy"
{ yyval.node = sxp_new_set_member(parser, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
    break;
case 80:
#line 223 "grammar.yy"
{ yyval.node = sxp_new_get_member (parser, yyvsp[-2].node, yyvsp[0].id); }
    break;
case 81:
#line 225 "grammar.yy"
{ yyval.node = sxp_new_getindex (parser, yyvsp[-3].node, yyvsp[-1].node); }
    break;
case 82:
#line 226 "grammar.yy"
{ yyval.node = sxp_new_array (parser, yyvsp[-1].node); }
    break;
case 83:
#line 228 "grammar.yy"
{ yyval.node = sxp_new_data (parser, yyvsp[0].value); }
    break;
case 84:
#line 230 "grammar.yy"
{ yyval.node = sxp_new_lookup (parser, yyvsp[0].id); }
    break;
case 85:
#line 232 "grammar.yy"
{ yyval.node = sxp_new_data (parser, NULL); }
    break;
case 86:
#line 236 "grammar.yy"
{ yyval.value = yyvsp[0].value;  }
    break;
case 87:
#line 237 "grammar.yy"
{ yyval.value = yyvsp[0].value; }
    break;
case 88:
#line 238 "grammar.yy"
{ yyval.value = NULL; }
    break;
case 89:
#line 241 "grammar.yy"
{ yyval.id = yyvsp[0].id; }
    break;
case 90:
#line 244 "grammar.yy"
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
#line 247 "grammar.yy"


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
		yyin = fopen (file, "rt");
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
