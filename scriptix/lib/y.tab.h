/* A Bison parser, made from grammar.y, by GNU bison 1.75.  */

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
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TNUM = 258,
     TSTR = 259,
     TNAME = 260,
     TTYPE = 261,
     TFUNCTAG = 262,
     TIF = 263,
     TELSE = 264,
     TWHILE = 265,
     TDO = 266,
     TAND = 267,
     TOR = 268,
     TGTE = 269,
     TLTE = 270,
     TNE = 271,
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
     TPUBLIC = 284,
     TRETURN = 285,
     TBREAK = 286,
     TEQUALS = 287,
     TCAST = 288,
     TLENGTH = 289,
     TRANGE = 290,
     CUNARY = 291,
     TSTATMETHOD = 292
   };
#endif
#define TNUM 258
#define TSTR 259
#define TNAME 260
#define TTYPE 261
#define TFUNCTAG 262
#define TIF 263
#define TELSE 264
#define TWHILE 265
#define TDO 266
#define TAND 267
#define TOR 268
#define TGTE 269
#define TLTE 270
#define TNE 271
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
#define TPUBLIC 284
#define TRETURN 285
#define TBREAK 286
#define TEQUALS 287
#define TCAST 288
#define TLENGTH 289
#define TRANGE 290
#define CUNARY 291
#define TSTATMETHOD 292




#ifndef YYSTYPE
#line 50 "grammar.y"
typedef union {
	SXP_NODE* node;
	SX_VALUE value;
	sx_name_id id;
	sx_name_id* name_list;
	struct _sxp_arg_list args;
	struct _scriptix_tag* tag;
} yystype;
/* Line 1281 of /usr/share/bison/yacc.c.  */
#line 123 "y.tab.h"
# define YYSTYPE yystype
#endif

extern YYSTYPE sxlval;


#endif /* not BISON_Y_TAB_H */

