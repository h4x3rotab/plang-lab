/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EOFF = 0,
     IDENTIFIER = 258,
     INTEGERT = 259,
     REALT = 260,
     STRINGT = 261,
     PROGRAM = 262,
     IS = 263,
     BEGINT = 264,
     END = 265,
     VAR = 266,
     TYPE = 267,
     PROCEDURE = 268,
     ARRAY = 269,
     RECORD = 270,
     IN = 271,
     OUT = 272,
     READ = 273,
     WRITE = 274,
     IF = 275,
     THEN = 276,
     ELSE = 277,
     ELSIF = 278,
     WHILE = 279,
     DO = 280,
     LOOP = 281,
     FOR = 282,
     EXIT = 283,
     RETURN = 284,
     TO = 285,
     BY = 286,
     AND = 287,
     OR = 288,
     NOT = 289,
     OF = 290,
     DIV = 291,
     MOD = 292,
     LPAREN = 293,
     RPAREN = 294,
     LBRACKET = 295,
     RBRACKET = 296,
     LBRACE = 297,
     RBRACE = 298,
     COLON = 299,
     DOT = 300,
     SEMICOLON = 301,
     COMMA = 302,
     ASSIGN = 303,
     PLUS = 304,
     MINUS = 305,
     STAR = 306,
     SLASH = 307,
     BACKSLASH = 308,
     EQ = 309,
     NEQ = 310,
     LT = 311,
     LE = 312,
     GT = 313,
     GE = 314,
     LABRACKET = 315,
     RABRACKET = 316,
     ERROR = 317,
     UOPT = 318
   };
#endif
/* Tokens.  */
#define EOFF 0
#define IDENTIFIER 258
#define INTEGERT 259
#define REALT 260
#define STRINGT 261
#define PROGRAM 262
#define IS 263
#define BEGINT 264
#define END 265
#define VAR 266
#define TYPE 267
#define PROCEDURE 268
#define ARRAY 269
#define RECORD 270
#define IN 271
#define OUT 272
#define READ 273
#define WRITE 274
#define IF 275
#define THEN 276
#define ELSE 277
#define ELSIF 278
#define WHILE 279
#define DO 280
#define LOOP 281
#define FOR 282
#define EXIT 283
#define RETURN 284
#define TO 285
#define BY 286
#define AND 287
#define OR 288
#define NOT 289
#define OF 290
#define DIV 291
#define MOD 292
#define LPAREN 293
#define RPAREN 294
#define LBRACKET 295
#define RBRACKET 296
#define LBRACE 297
#define RBRACE 298
#define COLON 299
#define DOT 300
#define SEMICOLON 301
#define COMMA 302
#define ASSIGN 303
#define PLUS 304
#define MINUS 305
#define STAR 306
#define SLASH 307
#define BACKSLASH 308
#define EQ 309
#define NEQ 310
#define LT 311
#define LE 312
#define GT 313
#define GE 314
#define LABRACKET 315
#define RABRACKET 316
#define ERROR 317
#define UOPT 318




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "pcat.y"
{
    char*       Tstring;
    int         Tint;
    double      Treal;
    ast*        Tast;
    ast_list*   Tast_list;
}
/* Line 1529 of yacc.c.  */
#line 185 "pcat.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
