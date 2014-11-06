#ifndef BISON_GRAMMAR_HH
# define BISON_GRAMMAR_HH

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


extern YYSTYPE yylval;

#endif /* not BISON_GRAMMAR_HH */
