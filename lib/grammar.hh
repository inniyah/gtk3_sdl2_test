/* A Bison parser, made by GNU Bison 1.875a.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

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
     TADDASSIGN = 273,
     TSUBASSIGN = 274,
     TINCREMENT = 275,
     TDECREMENT = 276,
     TNEW = 277,
     TUNTIL = 278,
     TNIL = 279,
     TRESCUE = 280,
     TIN = 281,
     TFOR = 282,
     TCONTINUE = 283,
     TYIELD = 284,
     TPUBLIC = 285,
     TRETURN = 286,
     TBREAK = 287,
     TEQUALS = 288,
     TCAST = 289,
     TLENGTH = 290,
     TRANGE = 291,
     CUNARY = 292,
     TSTATMETHOD = 293
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
#define TADDASSIGN 273
#define TSUBASSIGN 274
#define TINCREMENT 275
#define TDECREMENT 276
#define TNEW 277
#define TUNTIL 278
#define TNIL 279
#define TRESCUE 280
#define TIN 281
#define TFOR 282
#define TCONTINUE 283
#define TYIELD 284
#define TPUBLIC 285
#define TRETURN 286
#define TBREAK 287
#define TEQUALS 288
#define TCAST 289
#define TLENGTH 290
#define TRANGE 291
#define CUNARY 292
#define TSTATMETHOD 293




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 57 "grammar.yy"
typedef union YYSTYPE {
	ParserNode* node;
	Value* value;
	sx_name_id id;
	sx_name_id* name_list;
	struct _sxp_arg_list args;
} YYSTYPE;
/* Line 1240 of yacc.c.  */
#line 121 "grammar.hh"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



