#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
	SXP_NODE *node;
	SX_VALUE *value;
	char name[SX_MAX_NAME + 1];
	sx_name_id id;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	TNUM	257
# define	TSTR	258
# define	TNAME	259
# define	TIF	260
# define	TELSE	261
# define	TWHILE	262
# define	TDO	263
# define	TAND	264
# define	TOR	265
# define	TGTE	266
# define	TLTE	267
# define	TNE	268
# define	TSTATMETHOD	269
# define	TRETURN	270
# define	TBREAK	271
# define	TLOCAL	272
# define	TGLOBAL	273
# define	TEQUALS	274
# define	TCONTINUE	275
# define	TADDASSIGN	276
# define	TSUBASSIGN	277
# define	TINCREMENT	278
# define	TDECREMENT	279
# define	TSTATIC	280
# define	TCLASS	281
# define	TNEW	282
# define	TUNTIL	283
# define	TNIL	284
# define	TRAISE	285
# define	TRESCUE	286
# define	TTRY	287
# define	TIN	288
# define	TFOR	289
# define	TISA	290
# define	TLENGTH	291
# define	TRANGE	292
# define	CUNARY	293


extern YYSTYPE sxlval;

#endif /* not BISON_Y_TAB_H */
