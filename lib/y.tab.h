#ifndef YYERRCODE
#define YYERRCODE 256
#endif

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
typedef union {
	SXP_NODE *node;
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	sx_name_id id;
	struct _sxp_arg_list args;
} YYSTYPE;
extern YYSTYPE sxlval;
