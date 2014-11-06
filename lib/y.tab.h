#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

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


extern YYSTYPE sxlval;

#endif /* not BISON_Y_TAB_H */
