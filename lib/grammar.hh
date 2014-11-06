/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

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
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     DO = 265,
     AND = 266,
     OR = 267,
     TGTE = 268,
     TLTE = 269,
     TNE = 270,
     TFOREACH = 271,
     TADDASSIGN = 272,
     TSUBASSIGN = 273,
     TINCREMENT = 274,
     TDECREMENT = 275,
     TNEW = 276,
     TUNTIL = 277,
     TNIL = 278,
     TIN = 279,
     TFOR = 280,
     TCONTINUE = 281,
     TYIELD = 282,
     TPUBLIC = 283,
     TMULASSIGN = 284,
     TDIVASSIGN = 285,
     TVAR = 286,
     TDEREFERENCE = 287,
     TCONCAT = 288,
     TBREAK = 289,
     TRETURN = 290,
     TEQUALS = 291,
     CUNARY = 292,
     TCAST = 293
   };
#endif
#define NUMBER 258
#define STRING 259
#define IDENTIFIER 260
#define TYPE 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define DO 265
#define AND 266
#define OR 267
#define TGTE 268
#define TLTE 269
#define TNE 270
#define TFOREACH 271
#define TADDASSIGN 272
#define TSUBASSIGN 273
#define TINCREMENT 274
#define TDECREMENT 275
#define TNEW 276
#define TUNTIL 277
#define TNIL 278
#define TIN 279
#define TFOR 280
#define TCONTINUE 281
#define TYIELD 282
#define TPUBLIC 283
#define TMULASSIGN 284
#define TDIVASSIGN 285
#define TVAR 286
#define TDEREFERENCE 287
#define TCONCAT 288
#define TBREAK 289
#define TRETURN 290
#define TEQUALS 291
#define CUNARY 292
#define TCAST 293




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 62 "grammar.yy"
typedef union YYSTYPE {
	CompilerNode* node;
	Value* value;
	TypeInfo* type;
	NameID id;
	NameList* names;
	struct CompilerArgList args;
} YYSTYPE;
/* Line 1318 of yacc.c.  */
#line 122 "grammar.hh"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



