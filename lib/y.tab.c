#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define yyparse sxparse
#define yylex sxlex
#define yyerror sxerror
#define yychar sxchar
#define yyval sxval
#define yylval sxlval
#define yydebug sxdebug
#define yynerrs sxnerrs
#define yyerrflag sxerrflag
#define yyss sxss
#define yyssp sxssp
#define yyvs sxvs
#define yyvsp sxvsp
#define yylhs sxlhs
#define yylen sxlen
#define yydefred sxdefred
#define yydgoto sxdgoto
#define yysindex sxsindex
#define yyrindex sxrindex
#define yygindex sxgindex
#define yytable sxtable
#define yycheck sxcheck
#define yyname sxname
#define yyrule sxrule
#define yysslim sxsslim
#define yystacksize sxstacksize
#define YYPREFIX "sx"
#line 29 "grammar.y"
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
typedef union {
	SXP_NODE *node;
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	sx_name_id id;
	struct _sxp_arg_list args;
} YYSTYPE;
#line 69 "y.tab.c"
#define YYERRCODE 256
#define TNUM 257
#define TSTR 258
#define TNAME 259
#define TIF 260
#define TELSE 261
#define TWHILE 262
#define TDO 263
#define TAND 264
#define TOR 265
#define TGTE 266
#define TLTE 267
#define TNE 268
#define TSTATMETHOD 269
#define TRETURN 270
#define TBREAK 271
#define TLOCAL 272
#define TEQUALS 273
#define TCONTINUE 274
#define TSUPER 275
#define TYIELD 276
#define TADDASSIGN 277
#define TSUBASSIGN 278
#define TINCREMENT 279
#define TDECREMENT 280
#define TSTATIC 281
#define TCLASS 282
#define TNEW 283
#define TUNTIL 284
#define TNIL 285
#define TRAISE 286
#define TRESCUE 287
#define TTRY 288
#define TIN 289
#define TFOR 290
#define TISA 291
#define TLENGTH 292
#define TRANGE 293
#define CUNARY 294
const short sxlhs[] = {                                        -1,
    0,    0,    0,   15,   13,   17,   13,   16,   16,   18,
   18,   18,   14,    3,    3,    4,    4,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    1,
    1,    6,    6,    6,    6,    6,    6,    6,    2,    2,
    2,   12,   12,   12,   12,    8,    8,    9,    9,    9,
    7,    7,    7,    7,    7,    7,    7,    7,    7,    7,
    7,    7,    7,    7,    7,    7,    7,    7,    7,    7,
    7,    7,    7,    7,    7,    7,    7,    7,    7,    7,
    7,    7,    7,    7,    7,    7,    7,   10,   10,   10,
   11,
};
const short sxlen[] = {                                         2,
    0,    2,    2,    0,    6,    0,    8,    1,    2,    7,
    8,    2,    7,    0,    1,    1,    2,    2,    2,    5,
    7,    5,    5,    7,    7,   11,    6,    9,    3,    0,
    1,    2,    1,    1,    1,    2,    3,    1,    0,    1,
    3,    0,    1,    4,    2,    1,    3,    0,    2,    4,
    3,    3,    3,    3,    3,    2,    2,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    4,    6,    5,    3,
    3,    2,    2,    2,    2,    3,    4,    4,    6,    6,
    3,    5,    4,    3,    1,    1,    2,    1,    1,    1,
    1,
};
const short sxdefred[] = {                                      1,
    0,   91,    0,    0,    2,    3,    0,    0,    0,    0,
    0,    0,   46,    0,    6,    0,   45,    0,    0,    0,
    0,    0,    0,    8,    0,   47,    0,    0,    0,    0,
   12,    5,    9,   44,   88,   89,    0,    0,    0,    0,
   34,    0,   35,    0,   38,    0,    0,    0,    0,   90,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   16,    0,    0,   85,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   73,   75,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   18,
   13,   17,   19,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   72,   74,    0,    0,    7,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   84,   55,   29,    0,    0,    0,    0,    0,    0,
    0,    0,   76,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   78,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   77,    0,    0,    0,   22,    0,    0,   82,
   23,    0,    0,    0,    0,    0,    0,    0,    0,   10,
    0,    0,    0,    0,    0,   27,   80,    0,   79,   11,
   21,   24,   25,    0,    0,    0,    0,    0,   49,    0,
    0,    0,   28,    0,   50,   26,
};
const short sxdgoto[] = {                                       1,
   59,   86,   60,   61,   62,   63,   64,   12,  204,   65,
   66,   14,    5,    6,   10,   23,   20,   24,
};
const short sxsindex[] = {                                      0,
 -244,    0, -256,   -9,    0,    0,  -28,  -11, -256,  -79,
 -256,   11,    0,   50,    0, -235,    0,  -10,  -24,  -13,
 -256,   21, -123,    0, -256,    0,    2, -235,   43,  -11,
    0,    0,    0,    0,    0,    0,   55,   86,    2,   36,
    0, -256,    0,   99,    0, -256, -256, -256,  109,    0,
 -256,   32,   -1,   36,   36,   36,   36,    2,   97,   53,
    2,    0,   98,  811,    0,  313, -111,  -11,  138,   36,
   36, -219,  811,  119,   36,    0,    0,  154,   36,   36,
    2,   36, -108,  -29,  -29,  -40,  811,  382,   71,    0,
    0,    0,    0,   36,   36,   36,   36,   36,   36,   36,
   36, -256,   36,   36,   36,   36, -256,   36, -256,   36,
   36,    0,    0,   36,   36,    0,  156,   72,  410,  420,
  158,  159,   36,  -12,   36,  442,  811,   77,  145,   36,
   36,    0,    0,    0,  694,  819,  -37,  -37,   42,   42,
  -37,  -37,    0,   31,   31,  -29,  -29,   67,  579,  165,
  811,  811,  811,   79,   83,    2,    2,    2,   36,   36,
  811,    0,   90,    2,  -80,   36,  685,  811,   36,   36,
  147,   36,    0,    2,   84,  -51,    0,  452,  493,    0,
    0,  171,  778,    2,  811,   96,   36,  110,   87,    0,
    2,  160,  163, -256,   36,    0,    0,  811,    0,    0,
    0,    0,    0,  123, -256,  172,  105, -256,    0,    2,
    2, -256,    0,  150,    0,    0,
};
const short sxrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,  140,  239,    0,    0,
    0,  242,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -46,    0,    0,  239,
    0,    0,    0,    0,    0,    0,    0,    0,  225,  230,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -25,    0,  -46,    0,    0,
  -43,    0,    0,    8,    0,   59,    0,  239,    0,    0,
    0,    0,  232,   70,  124,    0,    0,    0,    0,  237,
  -46,  225,    0,  141,  173,    0,  -21,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  124,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  124,    0,  238,    0,    0,    0,
    0,    0,    0,    0,  -19,   94,    4,  755,  539,  568,
  767,  831,    0,  507,  527,  258,  340,  100,    0,    0,
  -23,   -7,   16,    0,    0,  -46,  225,  225,    0,    0,
  269,    0,    0,  225,    0,    0,    0,   15,    0,  124,
  130,  124,    0,  -46,    0,  -33,    0,    0,    0,    0,
    0,    0,    0,  225,  375,    0,    0,    0,    0,    0,
  225,    0,    0,  125,  257,    0,    0,  437,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  225,
  -46,    0,    0,    0,    0,    0,
};
const short sxgindex[] = {                                      0,
  -71,  -74,  334,    0,  725,    0, 1114,    0,    0,    0,
 1098,    3,    0,    0,    0,  276,    0,   27,
};
#define YYTABLESIZE 1310
const short sxtable[] = {                                      20,
  124,   32,    2,  131,  105,  103,   20,  104,  107,  106,
  129,   20,   30,  116,    2,   30,  107,   70,   39,   40,
   70,   58,   40,    2,   58,   20,   11,   25,  162,    9,
    8,  131,   69,   71,   55,   70,   71,    3,   82,   58,
  154,   57,  121,   16,   63,   21,   54,   63,   31,   33,
  163,   71,  132,  108,   18,   41,   66,   20,   41,   66,
   30,  108,   63,   63,  122,   63,   31,   39,   55,   70,
  117,   40,  105,   58,   66,   57,  107,  106,   14,   31,
   54,   15,   68,  105,  103,   71,  104,  107,  106,   20,
   19,   20,   56,   33,   70,  186,   63,  188,   27,   86,
   86,   86,   86,   86,   86,   86,  170,   41,   66,   28,
   87,   87,   87,   87,   87,   87,   87,   86,   86,  173,
   86,  108,  131,  206,   58,   71,   56,  169,   87,   87,
  180,   87,  108,  131,   59,    2,  197,   59,   75,  131,
   81,   81,   81,   81,   81,   81,   81,    2,   79,   86,
  199,   86,   59,  131,   81,   90,   93,   21,   81,   81,
   87,   81,   87,  207,   39,   48,  208,   39,   48,   21,
   83,   83,   83,   83,   83,   83,   83,   91,  118,  123,
  130,   56,   56,   56,   56,   56,   59,   56,   83,   83,
   81,   83,   81,  125,  156,  134,  155,  159,  160,   56,
   56,  165,   56,  166,  172,  174,  182,  187,  190,  191,
  194,  200,  210,   57,   57,   57,   57,   57,  202,   57,
   83,  203,   83,   20,   20,   20,   20,  211,   20,   20,
   98,   57,   57,   56,   57,   99,   20,   20,   20,   70,
   20,   20,   20,   58,   58,   20,   20,    2,    2,   20,
   20,   20,   20,  102,   20,   71,   20,    2,   35,   36,
    2,   37,    4,   38,   39,   57,   63,   63,   63,   63,
   63,   40,   41,   42,  216,   43,   44,   45,   66,   42,
   46,   47,   43,   30,   48,   49,   50,   51,   33,   52,
   32,   53,   35,   36,    2,   36,   37,   30,   53,   53,
   53,   53,   53,   67,   53,    0,    0,   42,    0,   67,
   44,    0,   67,    0,   46,   47,   53,   53,   48,   53,
   50,   86,   86,   86,   86,   86,   86,   67,    0,    0,
    0,   86,   87,   87,   87,   87,   87,   87,    0,    0,
    0,    0,   87,    0,    0,    0,    0,    0,    0,   86,
   53,    0,  115,    0,    0,    0,   59,   59,   59,    0,
   87,   67,   81,   81,   81,   81,   81,   81,    0,    0,
    0,    0,   81,  114,    0,    0,    0,    0,    0,    0,
   54,   54,   54,   54,   54,    0,   54,    0,    0,    0,
   81,   89,   83,   83,   83,   83,   83,   83,   54,   54,
    0,   54,   83,   56,   56,   56,   56,   56,   56,    0,
    0,    0,    0,   56,  128,   69,    0,    0,   69,    0,
   83,    0,  133,  105,  103,    0,  104,  107,  106,    0,
    0,   56,   54,   69,    0,   57,   57,   57,   57,   57,
   57,  101,    0,  100,    0,   57,    0,    0,    0,    0,
  157,  105,  103,    0,  104,  107,  106,    0,    0,    0,
  158,  105,  103,   57,  104,  107,  106,   69,    0,  101,
    0,  100,  108,    0,    0,    0,    0,   68,    0,  101,
   68,  100,  164,  105,  103,    0,  104,  107,  106,  175,
    0,    0,  192,  105,  103,   68,  104,  107,  106,    0,
  108,  101,    0,  100,    0,    0,    0,  189,    0,    0,
  108,  101,    0,  100,    0,    0,    0,    0,    0,    0,
   53,   53,   53,   53,   53,   53,    0,    0,    0,   68,
   53,   67,  108,  193,  105,  103,    0,  104,  107,  106,
    0,    0,  108,    0,  214,    0,    0,   51,   53,   51,
   51,   51,  101,    0,  100,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   51,   51,   52,   51,   52,
   52,   52,    0,    0,    0,    0,    0,    0,    0,   62,
    0,  109,   62,  108,    0,   52,   52,    0,   52,  110,
  111,  112,  113,    0,    0,    0,    0,   62,   62,   51,
   62,    0,   54,   54,   54,   54,   54,   54,   65,    0,
    0,   65,   54,    0,    0,    0,    0,    0,    0,   52,
  105,  103,    0,  104,  107,  106,   65,   65,    0,   65,
   54,   62,    0,    0,    0,    0,    0,   69,  101,    0,
  100,    0,    0,    0,    0,   94,   95,   96,   97,   98,
    0,    0,    0,    0,   99,    0,    0,    0,    0,    0,
   65,    0,    0,    0,    0,    0,    0,    0,    0,  108,
    0,  171,  102,   94,   95,   96,   97,   98,    0,    0,
    0,    0,   99,   94,   95,   96,   97,   98,    0,    0,
    0,    0,   99,    0,    0,    0,    0,    0,    0,   68,
  102,    0,    0,    0,    0,   94,   95,   96,   97,   98,
  102,    0,    0,    0,   99,   94,   95,   96,   97,   98,
    0,    0,    0,    0,   99,    0,  105,  103,    0,  104,
  107,  106,  102,    0,    0,  105,  103,    0,  104,  107,
  106,    0,  102,    0,  101,    0,  100,    0,    0,    0,
    0,    0,    0,  101,    0,  100,   94,   95,   96,   97,
   98,    0,    0,   72,    0,   99,    0,    0,    0,   51,
   51,   51,   51,   51,   51,  108,    0,    0,    0,   51,
    0,    0,    0,  102,  108,   92,    0,    0,    0,   52,
   52,   52,   52,   52,   52,   64,    0,   51,   64,   52,
    0,   62,   62,   62,   62,   62,   62,   60,    0,    0,
   60,   62,    0,   64,   64,    0,   64,   52,    0,  105,
  103,    0,  104,  107,  106,   60,   60,    0,   60,   62,
   65,   65,   65,   65,   65,   65,  195,  101,    0,  100,
   65,    0,   94,   95,   96,   97,   98,   64,    0,    0,
    0,   99,  105,  103,    0,  104,  107,  106,   65,   60,
  105,  103,    0,  104,  107,  106,    0,    0,  108,  102,
  101,   61,  100,    0,   61,    0,    0,    0,  101,    0,
  100,  176,  177,    0,    0,    0,    0,    0,  181,   61,
   61,    0,   61,    0,    0,    0,    0,    0,    0,    0,
    0,  108,    0,    0,    0,    0,    0,    0,  196,  108,
    0,    0,    0,    0,    0,  201,    0,    0,    0,    0,
    0,    0,    0,   61,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  213,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  184,   94,   95,
   96,   97,   98,    0,    0,    0,    0,   99,   95,   96,
   97,   98,    0,    0,    0,    0,   99,    0,    0,    0,
    0,    0,    0,    0,    0,  102,    0,    0,    0,    0,
    0,    0,    0,    0,  102,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   64,   64,   64,
   64,   64,    0,    0,    0,    0,    0,    0,    0,   60,
   60,   60,   60,   60,    0,    0,    0,    0,    0,    0,
    0,   94,   95,   96,   97,   98,    0,    0,    0,    0,
   99,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  102,    0,
    0,    0,    0,    0,   94,   95,   96,   97,   98,    0,
    0,    0,    0,   99,   96,   97,   98,    0,    0,    0,
    0,   99,    0,   61,   61,   61,   61,   61,    4,    0,
    7,  102,    0,    0,    0,   13,   15,    0,   17,  102,
    0,    0,    0,   22,    0,   26,    0,    0,   29,    0,
   22,    0,   34,    0,    0,   22,    0,   13,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   74,
    0,    0,    0,   76,   77,   78,    0,    0,   80,    0,
   83,    0,    0,   73,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   22,   13,    0,   84,   85,   87,
   88,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  119,  120,    0,    0,    0,   87,    0,
    0,    0,  126,  127,    0,    0,    0,    0,    0,  143,
    0,    0,    0,    0,  148,    0,  150,  135,  136,  137,
  138,  139,  140,  141,  142,    0,  144,  145,  146,  147,
    0,  149,    0,  151,  152,    0,    0,  153,   87,    0,
    0,    0,    0,    0,    0,    0,  161,    0,   87,    0,
    0,    0,    0,  167,  168,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  178,  179,    0,    0,    0,    0,    0,  183,
    0,    0,  185,   87,    0,   87,    0,    0,    0,    0,
    0,  205,    0,    0,    0,    0,    0,    0,    0,    0,
  198,    0,  209,    0,    0,  212,    0,    0,    0,  215,
};
const short sxcheck[] = {                                      33,
   75,  125,  259,   44,   42,   43,   40,   45,   46,   47,
   82,   45,   59,  125,  259,   59,   46,   41,   44,   41,
   44,   41,   44,  259,   44,   59,   38,   38,   41,   58,
   40,   44,   30,   41,   33,   59,   44,  282,   40,   59,
  115,   40,  262,  123,   41,  281,   45,   44,   41,   23,
  125,   59,   93,   91,   44,   41,   41,   91,   44,   44,
   40,   91,   59,   60,  284,   62,   59,   93,   33,   93,
   68,   93,   42,   93,   59,   40,   46,   47,  125,   59,
   45,  125,   40,   42,   43,   93,   45,   46,   47,  123,
   41,  125,   91,   67,   40,  170,   93,  172,  123,   41,
   42,   43,   44,   45,   46,   47,   40,   93,   93,  123,
   41,   42,   43,   44,   45,   46,   47,   59,   60,   41,
   62,   91,   44,  195,  123,   40,   91,   61,   59,   60,
   41,   62,   91,   44,   41,  259,   41,   44,   40,   44,
   41,   42,   43,   44,   45,   46,   47,  259,   40,   91,
   41,   93,   59,   44,  123,   59,   59,  281,   59,   60,
   91,   62,   93,   41,   41,   41,   44,   44,   44,  281,
   41,   42,   43,   44,   45,   46,   47,  125,   41,   61,
  289,   41,   42,   43,   44,   45,   93,   47,   59,   60,
   91,   62,   93,   40,  123,  125,   41,   40,   40,   59,
   60,  125,   62,   59,   40,  123,  287,   61,  125,  261,
   40,  125,   41,   41,   42,   43,   44,   45,   59,   47,
   91,   59,   93,  257,  258,  259,  260,  123,  262,  263,
  268,   59,   60,   93,   62,  273,  270,  271,  272,  263,
  274,  275,  276,  263,  264,  279,  280,  259,  259,  283,
  284,  285,  286,  291,  288,  263,  290,  259,  257,  258,
  259,  260,  123,  262,  263,   93,  263,  264,  265,  266,
  267,  270,  271,  272,  125,  274,  275,  276,  263,   41,
  279,  280,   41,   59,  283,  284,  285,  286,   59,  288,
   59,  290,  257,  258,  259,   59,   59,   41,   41,   42,
   43,   44,   45,   28,   47,   -1,   -1,  272,   -1,   41,
  275,   -1,   44,   -1,  279,  280,   59,   60,  283,   62,
  285,  263,  264,  265,  266,  267,  268,   59,   -1,   -1,
   -1,  273,  263,  264,  265,  266,  267,  268,   -1,   -1,
   -1,   -1,  273,   -1,   -1,   -1,   -1,   -1,   -1,  291,
   93,   -1,   40,   -1,   -1,   -1,  263,  264,  265,   -1,
  291,   93,  263,  264,  265,  266,  267,  268,   -1,   -1,
   -1,   -1,  273,   61,   -1,   -1,   -1,   -1,   -1,   -1,
   41,   42,   43,   44,   45,   -1,   47,   -1,   -1,   -1,
  291,   58,  263,  264,  265,  266,  267,  268,   59,   60,
   -1,   62,  273,  263,  264,  265,  266,  267,  268,   -1,
   -1,   -1,   -1,  273,   81,   41,   -1,   -1,   44,   -1,
  291,   -1,   41,   42,   43,   -1,   45,   46,   47,   -1,
   -1,  291,   93,   59,   -1,  263,  264,  265,  266,  267,
  268,   60,   -1,   62,   -1,  273,   -1,   -1,   -1,   -1,
   41,   42,   43,   -1,   45,   46,   47,   -1,   -1,   -1,
   41,   42,   43,  291,   45,   46,   47,   93,   -1,   60,
   -1,   62,   91,   -1,   -1,   -1,   -1,   41,   -1,   60,
   44,   62,   41,   42,   43,   -1,   45,   46,   47,  156,
   -1,   -1,   41,   42,   43,   59,   45,   46,   47,   -1,
   91,   60,   -1,   62,   -1,   -1,   -1,  174,   -1,   -1,
   91,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,
  263,  264,  265,  266,  267,  268,   -1,   -1,   -1,   93,
  273,  263,   91,   41,   42,   43,   -1,   45,   46,   47,
   -1,   -1,   91,   -1,  211,   -1,   -1,   41,  291,   43,
   44,   45,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   60,   41,   62,   43,
   44,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   41,
   -1,  269,   44,   91,   -1,   59,   60,   -1,   62,  277,
  278,  279,  280,   -1,   -1,   -1,   -1,   59,   60,   93,
   62,   -1,  263,  264,  265,  266,  267,  268,   41,   -1,
   -1,   44,  273,   -1,   -1,   -1,   -1,   -1,   -1,   93,
   42,   43,   -1,   45,   46,   47,   59,   60,   -1,   62,
  291,   93,   -1,   -1,   -1,   -1,   -1,  263,   60,   -1,
   62,   -1,   -1,   -1,   -1,  264,  265,  266,  267,  268,
   -1,   -1,   -1,   -1,  273,   -1,   -1,   -1,   -1,   -1,
   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   91,
   -1,   93,  291,  264,  265,  266,  267,  268,   -1,   -1,
   -1,   -1,  273,  264,  265,  266,  267,  268,   -1,   -1,
   -1,   -1,  273,   -1,   -1,   -1,   -1,   -1,   -1,  263,
  291,   -1,   -1,   -1,   -1,  264,  265,  266,  267,  268,
  291,   -1,   -1,   -1,  273,  264,  265,  266,  267,  268,
   -1,   -1,   -1,   -1,  273,   -1,   42,   43,   -1,   45,
   46,   47,  291,   -1,   -1,   42,   43,   -1,   45,   46,
   47,   -1,  291,   -1,   60,   -1,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   60,   -1,   62,  264,  265,  266,  267,
  268,   -1,   -1,   39,   -1,  273,   -1,   -1,   -1,  263,
  264,  265,  266,  267,  268,   91,   -1,   -1,   -1,  273,
   -1,   -1,   -1,  291,   91,   61,   -1,   -1,   -1,  263,
  264,  265,  266,  267,  268,   41,   -1,  291,   44,  273,
   -1,  263,  264,  265,  266,  267,  268,   41,   -1,   -1,
   44,  273,   -1,   59,   60,   -1,   62,  291,   -1,   42,
   43,   -1,   45,   46,   47,   59,   60,   -1,   62,  291,
  263,  264,  265,  266,  267,  268,   59,   60,   -1,   62,
  273,   -1,  264,  265,  266,  267,  268,   93,   -1,   -1,
   -1,  273,   42,   43,   -1,   45,   46,   47,  291,   93,
   42,   43,   -1,   45,   46,   47,   -1,   -1,   91,  291,
   60,   41,   62,   -1,   44,   -1,   -1,   -1,   60,   -1,
   62,  157,  158,   -1,   -1,   -1,   -1,   -1,  164,   59,
   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,  184,   91,
   -1,   -1,   -1,   -1,   -1,  191,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   93,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  210,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  263,  264,  265,
  266,  267,  268,   -1,   -1,   -1,   -1,  273,  265,  266,
  267,  268,   -1,   -1,   -1,   -1,  273,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  291,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  291,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  263,  264,  265,
  266,  267,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  263,
  264,  265,  266,  267,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  264,  265,  266,  267,  268,   -1,   -1,   -1,   -1,
  273,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  291,   -1,
   -1,   -1,   -1,   -1,  264,  265,  266,  267,  268,   -1,
   -1,   -1,   -1,  273,  266,  267,  268,   -1,   -1,   -1,
   -1,  273,   -1,  263,  264,  265,  266,  267,    1,   -1,
    3,  291,   -1,   -1,   -1,    8,    9,   -1,   11,  291,
   -1,   -1,   -1,   16,   -1,   18,   -1,   -1,   21,   -1,
   23,   -1,   25,   -1,   -1,   28,   -1,   30,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   42,
   -1,   -1,   -1,   46,   47,   48,   -1,   -1,   51,   -1,
   53,   -1,   -1,   40,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   67,   68,   -1,   54,   55,   56,
   57,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   70,   71,   -1,   -1,   -1,   75,   -1,
   -1,   -1,   79,   80,   -1,   -1,   -1,   -1,   -1,  102,
   -1,   -1,   -1,   -1,  107,   -1,  109,   94,   95,   96,
   97,   98,   99,  100,  101,   -1,  103,  104,  105,  106,
   -1,  108,   -1,  110,  111,   -1,   -1,  114,  115,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,  125,   -1,
   -1,   -1,   -1,  130,  131,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  159,  160,   -1,   -1,   -1,   -1,   -1,  166,
   -1,   -1,  169,  170,   -1,  172,   -1,   -1,   -1,   -1,
   -1,  194,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  187,   -1,  205,   -1,   -1,  208,   -1,   -1,   -1,  212,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 294
#if YYDEBUG
const char * const sxname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,"'&'",0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,
0,0,0,0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'['",0,"']'","'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TNUM","TSTR","TNAME","TIF",
"TELSE","TWHILE","TDO","TAND","TOR","TGTE","TLTE","TNE","TSTATMETHOD","TRETURN",
"TBREAK","TLOCAL","TEQUALS","TCONTINUE","TSUPER","TYIELD","TADDASSIGN",
"TSUBASSIGN","TINCREMENT","TDECREMENT","TSTATIC","TCLASS","TNEW","TUNTIL",
"TNIL","TRAISE","TRESCUE","TTRY","TIN","TFOR","TISA","TLENGTH","TRANGE",
"CUNARY",
};
const char * const sxrule[] = {
"$accept : program",
"program :",
"program : program class",
"program : program function",
"$$1 :",
"class : TCLASS name $$1 '{' cblock '}'",
"$$2 :",
"class : TCLASS name ':' name $$2 '{' cblock '}'",
"cblock : cstmt",
"cblock : cblock cstmt",
"cstmt : name '(' arg_names ')' '{' block '}'",
"cstmt : TSTATIC name '(' arg_names ')' '{' block '}'",
"cstmt : name ';'",
"function : name '(' arg_names ')' '{' block '}'",
"block :",
"block : stmts",
"stmts : stmt",
"stmts : stmts stmt",
"stmt : node ';'",
"stmt : control ';'",
"stmt : TIF '(' expr ')' stmt",
"stmt : TIF '(' expr ')' stmt TELSE stmt",
"stmt : TWHILE '(' expr ')' stmt",
"stmt : TUNTIL '(' expr ')' stmt",
"stmt : TDO stmt TWHILE '(' expr ')' ';'",
"stmt : TDO stmt TUNTIL '(' expr ')' ';'",
"stmt : TTRY '{' block '}' TRESCUE '(' errors ')' '{' block '}'",
"stmt : TFOR name TIN expr TDO stmt",
"stmt : TFOR '(' node ';' expr ';' node ')' stmt",
"stmt : '{' block '}'",
"node :",
"node : expr",
"control : TRETURN expr",
"control : TRETURN",
"control : TBREAK",
"control : TCONTINUE",
"control : TRAISE name",
"control : TRAISE name expr",
"control : TYIELD",
"args :",
"args : expr",
"args : args ',' expr",
"arg_names :",
"arg_names : arg_names_list",
"arg_names : arg_names_list ',' '&' name",
"arg_names : '&' name",
"arg_names_list : name",
"arg_names_list : arg_names_list ',' name",
"errors :",
"errors : name name",
"errors : errors ',' name name",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : '(' expr ')'",
"expr : '-' expr",
"expr : '!' expr",
"expr : expr TAND expr",
"expr : expr TOR expr",
"expr : expr '>' expr",
"expr : expr '<' expr",
"expr : expr TNE expr",
"expr : expr TGTE expr",
"expr : expr TLTE expr",
"expr : expr TEQUALS expr",
"expr : name '=' expr",
"expr : TLOCAL name '=' expr",
"expr : expr '[' expr ']' '=' expr",
"expr : expr '.' name '=' expr",
"expr : name TADDASSIGN expr",
"expr : name TSUBASSIGN expr",
"expr : name TINCREMENT",
"expr : TINCREMENT name",
"expr : name TDECREMENT",
"expr : TDECREMENT name",
"expr : expr TISA name",
"expr : name '(' args ')'",
"expr : TSUPER '(' args ')'",
"expr : name TSTATMETHOD name '(' args ')'",
"expr : expr '.' name '(' args ')'",
"expr : expr '.' name",
"expr : TNEW name '(' args ')'",
"expr : expr '[' expr ']'",
"expr : '[' args ']'",
"expr : data",
"expr : name",
"expr : TLOCAL name",
"data : TNUM",
"data : TSTR",
"data : TNIL",
"name : TNAME",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 228 "grammar.y"

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
sxp_load_file (SX_MODULE *module, const char *file) {
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
sxp_load_string (SX_MODULE *module, const char *buf) {
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
#line 722 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 4:
#line 90 "grammar.y"
{ sxp_new_class (sxp_parser_info, yyvsp[0].id, 0); }
break;
case 6:
#line 91 "grammar.y"
{ sxp_new_class (sxp_parser_info, yyvsp[-2].id, yyvsp[0].id); }
break;
case 10:
#line 98 "grammar.y"
{ sxp_add_method (sxp_parser_info->classes, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
break;
case 11:
#line 99 "grammar.y"
{ sxp_add_static_method (sxp_parser_info->classes, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
break;
case 12:
#line 100 "grammar.y"
{ 
		if (sxp_parser_info->classes->members == NULL) {
			sxp_parser_info->classes->members = (SX_ARRAY *)sx_new_array (sxp_parser_info->system, 0, NULL);
		}
		sx_append (sxp_parser_info->system, (SX_VALUE *)sxp_parser_info->classes->members, sx_new_num (yyvsp[-1].id));
	}
break;
case 13:
#line 108 "grammar.y"
{ sxp_new_func (sxp_parser_info, yyvsp[-6].id, (SX_ARRAY *)yyvsp[-4].args.args, yyvsp[-4].args.varg, yyvsp[-1].node); }
break;
case 14:
#line 111 "grammar.y"
{ yyval.node = NULL; }
break;
case 15:
#line 112 "grammar.y"
{ yyval.node = yyvsp[0].node; }
break;
case 16:
#line 115 "grammar.y"
{ yyval.node = yyvsp[0].node; }
break;
case 17:
#line 116 "grammar.y"
{ yyval.node = yyvsp[-1].node; sxp_append (yyval.node, yyvsp[0].node); }
break;
case 18:
#line 119 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 19:
#line 120 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 20:
#line 121 "grammar.y"
{ yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, NULL); }
break;
case 21:
#line 122 "grammar.y"
{ yyval.node = sxp_new_if (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
break;
case 22:
#line 123 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_WD); }
break;
case 23:
#line 124 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node, SXP_W_UD); }
break;
case 24:
#line 125 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DW); }
break;
case 25:
#line 126 "grammar.y"
{ yyval.node = sxp_new_whil (sxp_parser_info, yyvsp[-2].node, yyvsp[-5].node, SXP_W_DU); }
break;
case 26:
#line 128 "grammar.y"
{ yyval.node = sxp_new_try (sxp_parser_info, yyvsp[-4].value, yyvsp[-8].node, yyvsp[-1].node); }
break;
case 27:
#line 130 "grammar.y"
{ yyval.node = sxp_new_for (sxp_parser_info, yyvsp[-4].id, yyvsp[-2].node, yyvsp[0].node); }
break;
case 28:
#line 131 "grammar.y"
{ yyval.node = sxp_new_cfor (sxp_parser_info, yyvsp[-6].node, yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node); }
break;
case 29:
#line 133 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 30:
#line 136 "grammar.y"
{ yyval.node = NULL; }
break;
case 31:
#line 137 "grammar.y"
{ yyval.node = sxp_new_stmt (sxp_parser_info, yyvsp[0].node); }
break;
case 32:
#line 140 "grammar.y"
{ yyval.node = sxp_new_retr (sxp_parser_info, yyvsp[0].node); }
break;
case 33:
#line 141 "grammar.y"
{ yyval.node = sxp_new_retr (sxp_parser_info, NULL); }
break;
case 34:
#line 142 "grammar.y"
{ yyval.node = sxp_new_brak (sxp_parser_info); }
break;
case 35:
#line 143 "grammar.y"
{ yyval.node = sxp_new_cont (sxp_parser_info); }
break;
case 36:
#line 144 "grammar.y"
{ yyval.node = sxp_new_rais (sxp_parser_info, yyvsp[0].id, NULL); }
break;
case 37:
#line 145 "grammar.y"
{ yyval.node = sxp_new_rais (sxp_parser_info, yyvsp[-1].id, yyvsp[0].node); }
break;
case 38:
#line 146 "grammar.y"
{ yyval.node = sxp_new_yeld (sxp_parser_info); }
break;
case 39:
#line 149 "grammar.y"
{ yyval.node = NULL; }
break;
case 40:
#line 150 "grammar.y"
{ yyval.node = yyvsp[0].node; }
break;
case 41:
#line 151 "grammar.y"
{ yyval.node = yyvsp[-2].node; sxp_append (yyval.node, yyvsp[0].node); }
break;
case 42:
#line 154 "grammar.y"
{ yyval.args.args = NULL; yyval.args.varg = 0; }
break;
case 43:
#line 155 "grammar.y"
{ yyval.args.args = yyvsp[0].value; yyval.args.varg = 0; }
break;
case 44:
#line 156 "grammar.y"
{ yyval.args.args = yyvsp[-3].value; yyval.args.varg = yyvsp[0].id; }
break;
case 45:
#line 157 "grammar.y"
{ yyval.args.args = NULL; yyval.args.varg = yyvsp[0].id; }
break;
case 46:
#line 160 "grammar.y"
{ yyval.value = sx_append (sxp_parser_info->system, sx_new_array (sxp_parser_info->system, 0, NULL), sx_new_num (yyvsp[0].id)); }
break;
case 47:
#line 161 "grammar.y"
{ yyval.value = sx_append (sxp_parser_info->system, yyvsp[-2].value, sx_new_num (yyvsp[0].id)); }
break;
case 48:
#line 164 "grammar.y"
{ yyval.value = NULL; }
break;
case 49:
#line 165 "grammar.y"
{ yyval.value = sx_append (sxp_parser_info->system, sx_append (sxp_parser_info->system, sx_new_array (sxp_parser_info->system, 0, NULL), sx_new_num (yyvsp[-1].id)), sx_new_num (yyvsp[0].id)); }
break;
case 50:
#line 166 "grammar.y"
{ yyval.value = sx_append (sxp_parser_info->system, sx_append (sxp_parser_info->system, sx_new_array (sxp_parser_info->system, 0, NULL), sx_new_num (yyvsp[-1].id)), sx_new_num (yyvsp[0].id)); }
break;
case 51:
#line 169 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_ADD, yyvsp[-2].node, yyvsp[0].node); }
break;
case 52:
#line 170 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_SUBTRACT, yyvsp[-2].node, yyvsp[0].node); }
break;
case 53:
#line 171 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_MULTIPLY, yyvsp[-2].node, yyvsp[0].node); }
break;
case 54:
#line 172 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_DIVIDE, yyvsp[-2].node, yyvsp[0].node); }
break;
case 55:
#line 173 "grammar.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 56:
#line 175 "grammar.y"
{ yyval.node = sxp_new_nega (sxp_parser_info, yyvsp[0].node); }
break;
case 57:
#line 177 "grammar.y"
{ yyval.node = sxp_new_not (sxp_parser_info, yyvsp[0].node); }
break;
case 58:
#line 178 "grammar.y"
{ yyval.node = sxp_new_and (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
break;
case 59:
#line 179 "grammar.y"
{ yyval.node = sxp_new_or (sxp_parser_info, yyvsp[-2].node, yyvsp[0].node); }
break;
case 60:
#line 181 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GT, yyvsp[-2].node, yyvsp[0].node); }
break;
case 61:
#line 182 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LT, yyvsp[-2].node, yyvsp[0].node); }
break;
case 62:
#line 183 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_NEQUAL, yyvsp[-2].node, yyvsp[0].node); }
break;
case 63:
#line 184 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_GTE, yyvsp[-2].node, yyvsp[0].node); }
break;
case 64:
#line 185 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_LTE, yyvsp[-2].node, yyvsp[0].node); }
break;
case 65:
#line 186 "grammar.y"
{ yyval.node = sxp_new_math (sxp_parser_info, SX_OP_EQUAL, yyvsp[-2].node, yyvsp[0].node); }
break;
case 66:
#line 188 "grammar.y"
{ yyval.node = sxp_new_assi (sxp_parser_info, yyvsp[-2].id, SX_SCOPE_DEF, yyvsp[0].node); }
break;
case 67:
#line 189 "grammar.y"
{ yyval.node = sxp_new_assi (sxp_parser_info, yyvsp[-2].id, SX_SCOPE_LOCAL, yyvsp[0].node); }
break;
case 68:
#line 190 "grammar.y"
{ yyval.node = sxp_new_set (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].node, yyvsp[0].node); }
break;
case 69:
#line 191 "grammar.y"
{ yyval.node = sxp_new_setm (sxp_parser_info, yyvsp[-4].node, yyvsp[-2].id, yyvsp[0].node); }
break;
case 70:
#line 193 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, yyvsp[0].node); }
break;
case 71:
#line 194 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[-2].id, sxp_new_nega (sxp_parser_info, yyvsp[0].node)); }
break;
case 72:
#line 195 "grammar.y"
{ yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
break;
case 73:
#line 196 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (1))); }
break;
case 74:
#line 197 "grammar.y"
{ yyval.node = sxp_new_poic (sxp_parser_info, yyvsp[-1].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
break;
case 75:
#line 198 "grammar.y"
{ yyval.node = sxp_new_pric (sxp_parser_info, yyvsp[0].id, sxp_new_data (sxp_parser_info, sx_new_num (-1))); }
break;
case 76:
#line 200 "grammar.y"
{ yyval.node = sxp_new_isa (sxp_parser_info, yyvsp[-2].node, yyvsp[0].id); }
break;
case 77:
#line 201 "grammar.y"
{ yyval.node = sxp_new_call (sxp_parser_info, yyvsp[-3].id, yyvsp[-1].node); }
break;
case 78:
#line 202 "grammar.y"
{ yyval.node = sxp_new_supr (sxp_parser_info, yyvsp[-1].node); }
break;
case 79:
#line 204 "grammar.y"
{ yyval.node = sxp_new_smet (sxp_parser_info, yyvsp[-5].id, yyvsp[-3].id, yyvsp[-1].node); }
break;
case 80:
#line 205 "grammar.y"
{ yyval.node = sxp_new_meth (sxp_parser_info, yyvsp[-5].node, yyvsp[-3].id, yyvsp[-1].node); }
break;
case 81:
#line 206 "grammar.y"
{ yyval.node = sxp_new_memb (sxp_parser_info, yyvsp[-2].node, yyvsp[0].id); }
break;
case 82:
#line 207 "grammar.y"
{ yyval.node = sxp_new_newc (sxp_parser_info, yyvsp[-3].id, yyvsp[-1].node); }
break;
case 83:
#line 209 "grammar.y"
{ yyval.node = sxp_new_indx (sxp_parser_info, yyvsp[-3].node, yyvsp[-1].node); }
break;
case 84:
#line 210 "grammar.y"
{ yyval.node = sxp_new_arry (sxp_parser_info, yyvsp[-1].node); }
break;
case 85:
#line 212 "grammar.y"
{ yyval.node = sxp_new_data (sxp_parser_info, yyvsp[0].value); }
break;
case 86:
#line 214 "grammar.y"
{ yyval.node = sxp_new_name (sxp_parser_info, yyvsp[0].id, SX_SCOPE_DEF); }
break;
case 87:
#line 215 "grammar.y"
{ yyval.node = sxp_new_name (sxp_parser_info, yyvsp[0].id, SX_SCOPE_LOCAL); }
break;
case 88:
#line 219 "grammar.y"
{ yyval.value = yyvsp[0].value;  }
break;
case 89:
#line 220 "grammar.y"
{ yyval.value = yyvsp[0].value; }
break;
case 90:
#line 221 "grammar.y"
{ yyval.value = NULL; }
break;
case 91:
#line 224 "grammar.y"
{ yyval.id = sx_name_to_id (yyvsp[0].name); }
break;
#line 1258 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
