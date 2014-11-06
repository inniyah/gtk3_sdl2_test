/* A Bison parser, made from grammar.y, by GNU bison 1.50.  */

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

#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

/* Tokens.  */
#ifndef YYTOKENTYPE
# if defined (__STDC__) || defined (__cplusplus)
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TNUM = 258,
     TSTR = 259,
     TNAME = 260,
     TTYPE = 261,
     TIF = 262,
     TELSE = 263,
     TWHILE = 264,
     TDO = 265,
     TAND = 266,
     TOR = 267,
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
     TRESCUE = 279,
     TIN = 280,
     TFOR = 281,
     TCONTINUE = 282,
     TYIELD = 283,
     TRETURN = 284,
     TBREAK = 285,
     TEQUALS = 286,
     TCAST = 287,
     TLENGTH = 288,
     TRANGE = 289,
     CUNARY = 290,
     TSTATMETHOD = 291
   };
# endif
  /* POSIX requires `int' for tokens in interfaces.  */
# define YYTOKENTYPE int
#endif /* !YYTOKENTYPE */
#define TNUM 258
#define TSTR 259
#define TNAME 260
#define TTYPE 261
#define TIF 262
#define TELSE 263
#define TWHILE 264
#define TDO 265
#define TAND 266
#define TOR 267
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
#define TRESCUE 279
#define TIN 280
#define TFOR 281
#define TCONTINUE 282
#define TYIELD 283
#define TRETURN 284
#define TBREAK 285
#define TEQUALS 286
#define TCAST 287
#define TLENGTH 288
#define TRANGE 289
#define CUNARY 290
#define TSTATMETHOD 291




#ifndef YYSTYPE
#line 48 "grammar.y"
typedef union {
	SXP_NODE *node;
	SX_VALUE value;
	sx_name_id id;
	struct _sxp_arg_list args;
} yystype;
/* Line 1304 of /usr/share/bison/yacc.c.  */
#line 122 "y.tab.h"
# define YYSTYPE yystype
#endif

extern YYSTYPE sxlval;


#endif /* not BISON_Y_TAB_H */

