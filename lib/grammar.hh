/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     STRING = 259,
     IDENTIFIER = 260,
     TYPE = 261,
     TAG = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     DO = 266,
     AND = 267,
     OR = 268,
     TGTE = 269,
     TLTE = 270,
     TNE = 271,
     TFOREACH = 272,
     TEXTEND = 273,
     TADDASSIGN = 274,
     TSUBASSIGN = 275,
     TINCREMENT = 276,
     TDECREMENT = 277,
     TNEW = 278,
     TSTATIC = 279,
     TUNTIL = 280,
     TNIL = 281,
     TRESCUE = 282,
     TIN = 283,
     TFOR = 284,
     TCONTINUE = 285,
     TYIELD = 286,
     TPUBLIC = 287,
     TMULASSIGN = 288,
     TDIVASSIGN = 289,
     TRETURN = 290,
     TBREAK = 291,
     TEQUALS = 292,
     TLENGTH = 293,
     CUNARY = 294,
     TCAST = 295
   };
#endif
#define NUMBER 258
#define STRING 259
#define IDENTIFIER 260
#define TYPE 261
#define TAG 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define DO 266
#define AND 267
#define OR 268
#define TGTE 269
#define TLTE 270
#define TNE 271
#define TFOREACH 272
#define TEXTEND 273
#define TADDASSIGN 274
#define TSUBASSIGN 275
#define TINCREMENT 276
#define TDECREMENT 277
#define TNEW 278
#define TSTATIC 279
#define TUNTIL 280
#define TNIL 281
#define TRESCUE 282
#define TIN 283
#define TFOR 284
#define TCONTINUE 285
#define TYIELD 286
#define TPUBLIC 287
#define TMULASSIGN 288
#define TDIVASSIGN 289
#define TRETURN 290
#define TBREAK 291
#define TEQUALS 292
#define TLENGTH 293
#define CUNARY 294
#define TCAST 295




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 61 "grammar.yy"
typedef union YYSTYPE {
	ParserNode* node;
	Value* value;
	Type* type;
	NameID id;
	NameList* names;
	struct ParserArgList args;
} YYSTYPE;
/* Line 1240 of yacc.c.  */
#line 125 "grammar.hh"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



