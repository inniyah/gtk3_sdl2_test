#ifndef BISON_GRAMMAR_HH
# define BISON_GRAMMAR_HH

#ifndef YYSTYPE
typedef union {
	ParserNode* node;
	Value* value;
	sx_name_id id;
	sx_name_id* name_list;
	struct _sxp_arg_list args;
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
# define	TADDASSIGN	272
# define	TSUBASSIGN	273
# define	TINCREMENT	274
# define	TDECREMENT	275
# define	TNEW	276
# define	TUNTIL	277
# define	TNIL	278
# define	TRESCUE	279
# define	TIN	280
# define	TFOR	281
# define	TCONTINUE	282
# define	TYIELD	283
# define	TPUBLIC	284
# define	TBREAK	285
# define	TRETURN	286
# define	TEQUALS	287
# define	TCAST	288
# define	TLENGTH	289
# define	TRANGE	290
# define	CUNARY	291
# define	TSTATMETHOD	292


extern YYSTYPE yylval;

#endif /* not BISON_GRAMMAR_HH */
