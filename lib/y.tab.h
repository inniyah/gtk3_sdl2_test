#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
	VALUE *value;
	NODE *node;
} yystype;
# define YYSTYPE yystype
#endif
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
# define	TISA	295
# define	CUNARY	296
# define	CPARAN	297
# define	TTYPE	298


extern YYSTYPE sxlval;

#endif /* not BISON_Y_TAB_H */
