/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "pcat.y"


extern int lineno;
extern int columnno;

#include "ast.h"

#include "pcat.tab.h"
#include "pcat.yy.c"

void yyerror(const char* s);  // error handler defined in pcat.lex



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 246 "pcat.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 271 "pcat.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   588

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNRULES -- Number of states.  */
#define YYNSTATES  220

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,    10,    15,    19,    23,    27,    28,
      31,    38,    39,    42,    47,    48,    51,    53,    54,    57,
      61,    66,    73,    74,    77,    82,    83,    86,    91,    94,
      95,    99,   104,   109,   113,   117,   121,   130,   137,   142,
     154,   157,   161,   162,   165,   166,   172,   173,   176,   177,
     180,   181,   183,   188,   189,   193,   198,   201,   202,   206,
     208,   210,   212,   214,   218,   221,   224,   227,   231,   235,
     239,   243,   247,   251,   255,   259,   263,   267,   271,   275,
     279,   283,   286,   289,   292,   294,   299,   303,   308,   311,
     312,   316,   323,   324,   330,   335,   336,   340,   342,   346,
     348,   350,   352,   354,   355
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      65,     0,    -1,    66,    -1,     7,     8,    67,    46,    -1,
      69,     9,    85,    10,    -1,    11,    70,    71,    -1,    12,
      72,    73,    -1,    13,    77,    78,    -1,    -1,    69,    68,
      -1,   106,   107,    75,    48,    95,    46,    -1,    -1,    71,
      70,    -1,    74,     8,    76,    46,    -1,    -1,    73,    72,
      -1,   106,    -1,    -1,    44,    74,    -1,    14,    35,    74,
      -1,    15,    79,    80,    10,    -1,   106,    81,    75,     8,
      67,    46,    -1,    -1,    78,    77,    -1,   106,    44,    74,
      46,    -1,    -1,    80,    79,    -1,    38,    83,    82,    39,
      -1,    38,    39,    -1,    -1,    82,    46,    83,    -1,   106,
     107,    44,    74,    -1,    96,    48,    95,    46,    -1,   106,
      97,    46,    -1,    18,    90,    46,    -1,    19,    92,    46,
      -1,    20,    95,    21,    85,    86,    87,    10,    46,    -1,
      24,    95,    25,    85,    10,    46,    -1,    26,    85,    10,
      46,    -1,    27,    96,    48,    95,    30,    95,    88,    25,
      85,    10,    46,    -1,    28,    46,    -1,    29,    89,    46,
      -1,    -1,    85,    84,    -1,    -1,    86,    23,    95,    21,
      85,    -1,    -1,    22,    85,    -1,    -1,    31,    95,    -1,
      -1,    95,    -1,    38,    96,    91,    39,    -1,    -1,    91,
      47,    96,    -1,    38,    94,    93,    39,    -1,    38,    39,
      -1,    -1,    93,    47,    94,    -1,   105,    -1,    95,    -1,
     104,    -1,    96,    -1,    38,    95,    39,    -1,    49,    95,
      -1,    50,    95,    -1,    34,    95,    -1,    95,    49,    95,
      -1,    95,    50,    95,    -1,    95,    51,    95,    -1,    95,
      52,    95,    -1,    95,    36,    95,    -1,    95,    37,    95,
      -1,    95,    33,    95,    -1,    95,    32,    95,    -1,    95,
      58,    95,    -1,    95,    56,    95,    -1,    95,    54,    95,
      -1,    95,    59,    95,    -1,    95,    57,    95,    -1,    95,
      55,    95,    -1,   106,    97,    -1,   106,    99,    -1,   106,
     101,    -1,   106,    -1,    96,    40,    95,    41,    -1,    96,
      45,   106,    -1,    38,    95,    98,    39,    -1,    38,    39,
      -1,    -1,    98,    47,    95,    -1,    42,   106,    48,    95,
     100,    43,    -1,    -1,   100,    47,   106,    48,    95,    -1,
      60,   103,   102,    61,    -1,    -1,   102,    47,   103,    -1,
      95,    -1,    95,    35,    95,    -1,     4,    -1,     5,    -1,
       6,    -1,     3,    -1,    -1,   107,    47,   106,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    97,    97,    99,   101,   103,   104,   105,   106,   107,
     109,   110,   111,   113,   114,   115,   117,   118,   119,   121,
     122,   124,   125,   126,   128,   129,   130,   132,   133,   134,
     135,   137,   139,   140,   141,   142,   143,   157,   158,   159,
     170,   171,   173,   174,   176,   177,   179,   180,   182,   183,
     185,   186,   188,   189,   190,   192,   193,   194,   195,   197,
     198,   200,   201,   202,   204,   205,   206,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   226,   227,   228,   230,   231,   232,
     233,   235,   236,   237,   239,   240,   241,   243,   244,   246,
     247,   248,   250,   251,   252
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "EOFF", "error", "$undefined", "IDENTIFIER", "INTEGERT", "REALT",
  "STRINGT", "PROGRAM", "IS", "BEGINT", "END", "VAR", "TYPE", "PROCEDURE",
  "ARRAY", "RECORD", "IN", "OUT", "READ", "WRITE", "IF", "THEN", "ELSE",
  "ELSIF", "WHILE", "DO", "LOOP", "FOR", "EXIT", "RETURN", "TO", "BY",
  "AND", "OR", "NOT", "OF", "DIV", "MOD", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "LBRACE", "RBRACE", "COLON", "DOT", "SEMICOLON", "COMMA",
  "ASSIGN", "PLUS", "MINUS", "STAR", "SLASH", "BACKSLASH", "EQ", "NEQ",
  "LT", "LE", "GT", "GE", "LABRACKET", "RABRACKET", "ERROR", "UOPT",
  "$accept", "start", "program", "body", "declaration",
  "declaration_array", "var_decl", "var_decl_array", "type_decl",
  "type_decl_array", "type_name", "opt_typename", "compound_type",
  "procedure_decl", "procedure_decl_array", "field_decl",
  "field_decl_array", "formal_params", "formal_params_optext",
  "formal_section", "statement", "statement_array",
  "statement_if_opt_elseif", "statement_if_opt_else",
  "statement_for_opt_by", "statement_return_opt_expr", "read_args",
  "read_args_optext", "write_args", "write_args_optext", "write_expr",
  "expression", "l_value", "arguments", "arguments_optext", "field_inits",
  "field_inits_optext", "array_values", "array_values_optext",
  "array_value", "number", "string", "id", "id_array_optext", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    66,    67,    68,    68,    68,    69,    69,
      70,    71,    71,    72,    73,    73,    74,    75,    75,    76,
      76,    77,    78,    78,    79,    80,    80,    81,    81,    82,
      82,    83,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    89,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    96,    96,    96,    97,    97,    98,
      98,    99,   100,   100,   101,   102,   102,   103,   103,   104,
     104,   105,   106,   107,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     4,     3,     3,     3,     0,     2,
       6,     0,     2,     4,     0,     2,     1,     0,     2,     3,
       4,     6,     0,     2,     4,     0,     2,     4,     2,     0,
       3,     4,     4,     3,     3,     3,     8,     6,     4,    11,
       2,     3,     0,     2,     0,     5,     0,     2,     0,     2,
       0,     1,     4,     0,     3,     4,     2,     0,     3,     1,
       1,     1,     1,     3,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     1,     4,     3,     4,     2,     0,
       3,     6,     0,     5,     4,     0,     3,     1,     3,     1,
       1,     1,     1,     0,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     8,     1,     0,     0,     3,    42,
       0,     0,     0,     9,     0,   102,    11,   103,    14,     0,
      16,    22,     0,     4,     0,     0,     0,     0,    42,     0,
       0,    50,    43,     0,    84,     5,    17,     6,     0,     7,
       0,    17,     0,     0,     0,     0,    99,   100,     0,     0,
       0,     0,     0,    62,    61,    84,     0,     0,     0,    84,
      40,     0,    51,     0,     0,     0,     0,     0,    12,     0,
       0,     0,    15,     0,     0,     0,    23,    28,    29,   103,
       0,    53,    34,   101,    56,    57,    60,    59,    35,    66,
       0,    64,    65,    42,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      81,    82,    83,    42,     0,     0,    41,     0,    86,     0,
      88,    89,    33,    18,   104,     0,     0,    25,     0,    13,
       0,     0,     8,     0,     0,    63,    44,    74,    73,    71,
      72,    67,    68,    69,    70,    77,    80,    76,    79,    75,
      78,     0,    97,    95,     0,    38,     0,    85,    32,     0,
       0,    19,     0,     0,    27,     0,     0,     0,    52,     0,
      55,     0,    46,     0,     0,     0,     0,     0,    87,     0,
      10,    20,    26,     0,    30,    31,    21,    54,    58,    42,
       0,     0,    92,    98,     0,    94,    37,    48,    90,    24,
      47,     0,     0,     0,    96,     0,     0,    42,    36,    91,
       0,    49,    42,    45,     0,     0,     0,     0,    93,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,    13,     7,    16,    35,    18,    37,
      19,    71,    75,    21,    39,   127,   162,    41,   130,    78,
      32,    14,   172,   191,   206,    61,    43,   133,    45,   134,
      85,    86,    53,    67,   159,   111,   203,   112,   175,   153,
      54,    87,    55,    36
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -65
static const yytype_int16 yypact[] =
{
      19,    32,    49,   -65,   -65,   -65,    17,    81,   -65,   -65,
      53,    53,    53,   -65,   121,   -65,   -65,   -65,   -65,    65,
     -65,   -65,    47,   -65,    67,    73,    63,    63,   -65,    53,
      45,    63,   -65,    10,    76,    53,   -30,    53,    57,    53,
       9,    71,    53,    77,     3,    82,   -65,   -65,    63,    63,
      63,    63,   159,    -1,   -65,   -27,   267,   209,    34,   -65,
     -65,    83,   458,    63,    53,    63,    31,    84,   -65,    53,
      53,    79,   -65,    98,    53,    90,   -65,   -65,   -65,   -65,
     129,    -1,   -65,   -65,   -65,   -65,   458,   -65,   -65,   -65,
     335,   -65,   -65,   -65,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    53,    63,
     -65,   -65,   -65,   -65,    92,    63,   -65,   363,   -65,   391,
     -65,   458,   -65,   -65,   -65,    63,    53,   -65,   102,   -65,
     -23,    39,   -65,   -26,   -19,   -65,   538,   -65,    52,   -65,
     -65,    52,    52,   -65,   -65,   536,   536,   536,   536,   536,
     536,    94,   419,   -65,   508,   -65,   278,   -65,   -65,     4,
     447,   -65,    35,    53,   -65,    53,    53,   105,   -65,    53,
     -65,    72,    86,    63,    63,   -37,   108,    63,   -65,    63,
     -65,   -65,   -65,   111,   -65,   -65,   -65,    -1,   -65,   -65,
      63,   150,   458,   458,    63,   -65,   -65,   307,   458,   -65,
     538,   232,   115,    14,   -65,    63,   137,   -65,   -65,   -65,
      53,   458,   -65,   538,   131,   520,    63,   135,   458,   -65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   -65,    50,   -65,   -65,   142,   -65,   148,   -65,
     -64,   145,   -65,   149,   -65,    25,   -65,   -65,   -65,    28,
     -65,    -6,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
      26,    69,   -11,   143,   -65,   -65,   -65,   -65,   -65,     5,
     -65,   -65,   -10,   128
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      17,    20,    22,    33,    34,   123,    15,    46,    47,    83,
     194,    66,    15,   168,    69,   108,   164,    70,    58,    59,
     170,   169,    57,   165,   195,    17,     1,    20,   171,    22,
      79,    81,    59,   109,    15,    46,    47,    48,    15,    63,
       4,    49,    84,   178,    64,   181,    33,    34,    77,     5,
      63,   179,    50,    51,   118,    64,    15,   209,    65,    20,
     124,   210,   161,     8,   128,    48,    15,    46,    47,    49,
     120,    73,    74,    38,    63,    15,    46,    47,    83,    64,
      50,    51,   115,   166,    94,    40,    70,   136,    96,    97,
       9,    60,    10,    11,    12,    52,    56,    48,   151,   183,
      62,    49,   185,   100,   101,    42,    48,   154,   189,   190,
      49,    44,    50,    51,    66,    69,    20,    89,    90,    91,
      92,    50,    51,    82,    15,    33,    34,   125,    88,   116,
     122,    23,   117,   126,   119,   121,   129,   132,   155,    24,
      25,    26,   173,    33,    34,    27,   163,    28,    29,    30,
      31,   186,   128,    20,   196,    79,    20,   199,   187,    59,
     202,   208,   212,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    68,   152,   216,
      93,   219,   167,   200,   156,    72,    80,   182,    76,    33,
      34,    94,    95,   184,   160,    96,    97,   188,   110,   204,
     214,   213,    33,    34,    33,    34,   215,   131,    98,    99,
     100,   101,    15,   102,   103,   104,   105,   106,   107,   114,
       0,     0,     0,     0,     0,     0,     0,    24,    25,    26,
       0,     0,     0,    27,     0,    28,    29,    30,    31,     0,
       0,     0,   192,   193,     0,     0,   197,     0,   198,     0,
       0,     0,     0,   207,     0,     0,     0,     0,     0,   201,
       0,     0,     0,   152,    94,    95,     0,     0,    96,    97,
       0,     0,     0,     0,   211,     0,     0,     0,     0,     0,
       0,    98,    99,   100,   101,   218,   102,   103,   104,   105,
     106,   107,   113,     0,     0,     0,     0,     0,     0,    94,
      95,     0,     0,    96,    97,     0,     0,     0,   177,     0,
      94,    95,     0,     0,    96,    97,    98,    99,   100,   101,
       0,   102,   103,   104,   105,   106,   107,    98,    99,   100,
     101,     0,   102,   103,   104,   105,   106,   107,   205,    94,
      95,     0,     0,    96,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    98,    99,   100,   101,
       0,   102,   103,   104,   105,   106,   107,    94,    95,     0,
       0,    96,    97,     0,   135,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    98,    99,   100,   101,     0,   102,
     103,   104,   105,   106,   107,    94,    95,     0,     0,    96,
      97,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,    98,    99,   100,   101,     0,   102,   103,   104,
     105,   106,   107,    94,    95,     0,     0,    96,    97,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
      98,    99,   100,   101,     0,   102,   103,   104,   105,   106,
     107,    94,    95,     0,   174,    96,    97,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,    99,
     100,   101,     0,   102,   103,   104,   105,   106,   107,    94,
      95,     0,     0,    96,    97,     0,     0,     0,     0,     0,
      94,    95,     0,   180,    96,    97,    98,    99,   100,   101,
       0,   102,   103,   104,   105,   106,   107,    98,    99,   100,
     101,    15,   102,   103,   104,   105,   106,   107,   176,     0,
       0,     0,     0,    15,     0,     0,    24,    25,    26,     0,
     217,     0,    27,     0,    28,    29,    30,    31,    24,    25,
      26,    15,     0,     0,    27,     0,    28,    29,    30,    31,
       0,     0,     0,     0,     0,     0,    24,    25,    26,     0,
       0,     0,    27,     0,    28,    29,    30,    31,    94,    95,
       0,     0,    96,    97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    98,    99,   100,   101
};

static const yytype_int16 yycheck[] =
{
      10,    11,    12,    14,    14,    69,     3,     4,     5,     6,
      47,    38,     3,    39,    44,    42,    39,    47,    29,    29,
      39,    47,    28,    46,    61,    35,     7,    37,    47,    39,
      40,    42,    42,    60,     3,     4,     5,    34,     3,    40,
       8,    38,    39,    39,    45,    10,    57,    57,    39,     0,
      40,    47,    49,    50,    64,    45,     3,    43,    48,    69,
      70,    47,   126,    46,    74,    34,     3,     4,     5,    38,
      39,    14,    15,     8,    40,     3,     4,     5,     6,    45,
      49,    50,    48,    44,    32,    38,    47,    93,    36,    37,
       9,    46,    11,    12,    13,    26,    27,    34,   108,   163,
      31,    38,   166,    51,    52,    38,    34,   113,    22,    23,
      38,    38,    49,    50,    38,    44,   126,    48,    49,    50,
      51,    49,    50,    46,     3,   136,   136,    48,    46,    46,
      46,    10,    63,    35,    65,    66,    46,     8,    46,    18,
      19,    20,    48,   154,   154,    24,    44,    26,    27,    28,
      29,    46,   162,   163,    46,   165,   166,    46,   169,   169,
      10,    46,    25,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,    35,   109,    48,
      21,    46,   132,   189,   115,    37,    41,   162,    39,   200,
     200,    32,    33,   165,   125,    36,    37,   171,    55,   194,
     210,   207,   213,   213,   215,   215,   212,    79,    49,    50,
      51,    52,     3,    54,    55,    56,    57,    58,    59,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    19,    20,
      -1,    -1,    -1,    24,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,   173,   174,    -1,    -1,   177,    -1,   179,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,   190,
      -1,    -1,    -1,   194,    32,    33,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,   205,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,   216,    54,    55,    56,    57,
      58,    59,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    -1,    -1,    36,    37,    -1,    -1,    -1,    30,    -1,
      32,    33,    -1,    -1,    36,    37,    49,    50,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    49,    50,    51,
      52,    -1,    54,    55,    56,    57,    58,    59,    31,    32,
      33,    -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    32,    33,    -1,
      -1,    36,    37,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    -1,    54,
      55,    56,    57,    58,    59,    32,    33,    -1,    -1,    36,
      37,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    -1,    54,    55,    56,
      57,    58,    59,    32,    33,    -1,    -1,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    -1,    54,    55,    56,    57,    58,
      59,    32,    33,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    -1,    54,    55,    56,    57,    58,    59,    32,
      33,    -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,    46,    36,    37,    49,    50,    51,    52,
      -1,    54,    55,    56,    57,    58,    59,    49,    50,    51,
      52,     3,    54,    55,    56,    57,    58,    59,    10,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    18,    19,    20,    -1,
      10,    -1,    24,    -1,    26,    27,    28,    29,    18,    19,
      20,     3,    -1,    -1,    24,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    19,    20,    -1,
      -1,    -1,    24,    -1,    26,    27,    28,    29,    32,    33,
      -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    65,    66,     8,     0,    67,    69,    46,     9,
      11,    12,    13,    68,    85,     3,    70,   106,    72,    74,
     106,    77,   106,    10,    18,    19,    20,    24,    26,    27,
      28,    29,    84,    96,   106,    71,   107,    73,     8,    78,
      38,    81,    38,    90,    38,    92,     4,     5,    34,    38,
      49,    50,    95,    96,   104,   106,    95,    85,    96,   106,
      46,    89,    95,    40,    45,    48,    38,    97,    70,    44,
      47,    75,    72,    14,    15,    76,    77,    39,    83,   106,
      75,    96,    46,     6,    39,    94,    95,   105,    46,    95,
      95,    95,    95,    21,    32,    33,    36,    37,    49,    50,
      51,    52,    54,    55,    56,    57,    58,    59,    42,    60,
      97,    99,   101,    25,    10,    48,    46,    95,   106,    95,
      39,    95,    46,    74,   106,    48,    35,    79,   106,    46,
      82,   107,     8,    91,    93,    39,    85,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,   106,    95,   103,    85,    46,    95,    41,    46,    98,
      95,    74,    80,    44,    39,    46,    44,    67,    39,    47,
      39,    47,    86,    48,    35,   102,    10,    30,    39,    47,
      46,    10,    79,    74,    83,    74,    46,    96,    94,    22,
      23,    87,    95,    95,    47,    61,    46,    95,    95,    46,
      85,    95,    10,   100,   103,    31,    88,    21,    46,    43,
      47,    95,    25,    85,   106,    85,    48,    10,    95,    46
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 97 "pcat.y"
    { printf("[Accepted]\n"); print_ast((yyvsp[(1) - (1)].Tast)); printf("\n"); ;}
    break;

  case 3:
#line 99 "pcat.y"
    { (yyval.Tast) = (yyvsp[(3) - (4)].Tast) ;}
    break;

  case 4:
#line 101 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), body_node, clst(2, mk_node(&((yylsp[(1) - (4)])), genr_node, reverse((yyvsp[(1) - (4)].Tast_list))), mk_statblock(&((yylsp[(3) - (4)])), (yyvsp[(3) - (4)].Tast_list)))); ;}
    break;

  case 5:
#line 103 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), var_decls, cons((yyvsp[(2) - (3)].Tast), reverse((yyvsp[(3) - (3)].Tast_list)))); ;}
    break;

  case 6:
#line 104 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)),type_decls, cons((yyvsp[(2) - (3)].Tast), reverse((yyvsp[(3) - (3)].Tast_list)))); ;}
    break;

  case 7:
#line 105 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)),proc_decls, cons((yyvsp[(2) - (3)].Tast), reverse((yyvsp[(3) - (3)].Tast_list)))); ;}
    break;

  case 8:
#line 106 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 9:
#line 107 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(2) - (2)].Tast), (yyvsp[(1) - (2)].Tast_list)); ;}
    break;

  case 10:
#line 109 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), var_decl, clst(3, mk_idlist(&((yylsp[(1) - (6)])), &((yylsp[(2) - (6)])), (yyvsp[(1) - (6)].Tast), (yyvsp[(2) - (6)].Tast_list)), (yyvsp[(3) - (6)].Tast), (yyvsp[(5) - (6)].Tast))); ;}
    break;

  case 11:
#line 110 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 12:
#line 111 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(2) - (2)].Tast), (yyvsp[(1) - (2)].Tast_list)); ;}
    break;

  case 13:
#line 113 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), type_decl, clst(1, (yyvsp[(3) - (4)].Tast))); ;}
    break;

  case 14:
#line 114 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 15:
#line 115 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(2) - (2)].Tast), (yyvsp[(1) - (2)].Tast_list)); ;}
    break;

  case 17:
#line 118 "pcat.y"
    { (yyval.Tast) = NULL; ;}
    break;

  case 18:
#line 119 "pcat.y"
    { (yyval.Tast) = (yyvsp[(2) - (2)].Tast);}
    break;

  case 19:
#line 121 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), arr_type, clst(1, (yyvsp[(3) - (3)].Tast))); ;}
    break;

  case 20:
#line 122 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), rec_type, cons((yyvsp[(2) - (4)].Tast), reverse((yyvsp[(3) - (4)].Tast_list)))); ;}
    break;

  case 21:
#line 124 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), proc_decl, clst(4, (yyvsp[(1) - (6)].Tast), (yyvsp[(2) - (6)].Tast), (yyvsp[(3) - (6)].Tast), (yyvsp[(5) - (6)].Tast))); ;}
    break;

  case 22:
#line 125 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 23:
#line 126 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(2) - (2)].Tast), (yyvsp[(1) - (2)].Tast_list)); ;}
    break;

  case 24:
#line 128 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), field_decl, clst(2, (yyvsp[(1) - (4)].Tast), (yyvsp[(3) - (4)].Tast))); ;}
    break;

  case 25:
#line 129 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 26:
#line 130 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(2) - (2)].Tast), (yyvsp[(1) - (2)].Tast_list)); ;}
    break;

  case 27:
#line 132 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), param_node, cons((yyvsp[(2) - (4)].Tast), reverse((yyvsp[(3) - (4)].Tast_list)))); ;}
    break;

  case 28:
#line 133 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), param_node, NULL); ;}
    break;

  case 29:
#line 134 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 30:
#line 135 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(3) - (3)].Tast), (yyvsp[(1) - (3)].Tast_list)); ;}
    break;

  case 31:
#line 137 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), param_sec, clst(2, mk_idlist(&((yylsp[(1) - (4)])), &((yylsp[(2) - (4)])), (yyvsp[(1) - (4)].Tast), (yyvsp[(2) - (4)].Tast_list)), (yyvsp[(4) - (4)].Tast))); ;}
    break;

  case 32:
#line 139 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), asgn_stat, clst(2, (yyvsp[(1) - (4)].Tast), (yyvsp[(3) - (4)].Tast))); ;}
    break;

  case 33:
#line 140 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), fcall_exp, clst(2, (yyvsp[(1) - (3)].Tast), (yyvsp[(2) - (3)].Tast))); ;}
    break;

  case 34:
#line 141 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), read_stat, clst(1, (yyvsp[(2) - (3)].Tast))); ;}
    break;

  case 35:
#line 142 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), write_stat, clst(1, (yyvsp[(2) - (3)].Tast))); ;}
    break;

  case 36:
#line 147 "pcat.y"
    { 
                                                                                    (yyval.Tast) = mk_node(&((yyloc)), if_stat, 
                                                                                        clst
                                                                                        (
                                                                                            3, mk_noder(&((yylsp[(1) - (8)])), &((yylsp[(4) - (8)])), if_node, clst(2, (yyvsp[(2) - (8)].Tast), (yyvsp[(4) - (8)].Tast_list))),
                                                                                            mk_statblock(&((yylsp[(5) - (8)])), (yyvsp[(5) - (8)].Tast_list)),
                                                                                            (yyvsp[(6) - (8)].Tast)
                                                                                        )
                                                                                    ); 
                                                                                ;}
    break;

  case 37:
#line 157 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), while_stat, clst(2, (yyvsp[(2) - (6)].Tast), mk_statblock(&((yylsp[(4) - (6)])), (yyvsp[(4) - (6)].Tast_list)))); ;}
    break;

  case 38:
#line 158 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)),  loop_stat, clst(1, mk_statblock(&((yylsp[(2) - (4)])), (yyvsp[(2) - (4)].Tast_list)))); ;}
    break;

  case 39:
#line 161 "pcat.y"
    { 
                                                                                    (yyval.Tast) = mk_node(&((yyloc)), for_stat, 
                                                                                        clst
                                                                                        (
                                                                                            5, (yyvsp[(2) - (11)].Tast), (yyvsp[(4) - (11)].Tast), (yyvsp[(6) - (11)].Tast), (yyvsp[(7) - (11)].Tast),
                                                                                            mk_statblock(&((yylsp[(9) - (11)])), (yyvsp[(9) - (11)].Tast_list))
                                                                                        )
                                                                                    ); 
                                                                                ;}
    break;

  case 40:
#line 170 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), exit_stat, NULL); ;}
    break;

  case 41:
#line 171 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), retn_stat, clst(1, (yyvsp[(2) - (3)].Tast))); ;}
    break;

  case 42:
#line 173 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 43:
#line 174 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(2) - (2)].Tast), (yyvsp[(1) - (2)].Tast_list)); ;}
    break;

  case 44:
#line 176 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 45:
#line 177 "pcat.y"
    { (yyval.Tast_list) = cons(mk_noder(&((yylsp[(3) - (5)])), &((yylsp[(5) - (5)])), if_node, clst(2, (yyvsp[(3) - (5)].Tast), (yyvsp[(5) - (5)].Tast_list))), (yyvsp[(1) - (5)].Tast_list)); ;}
    break;

  case 46:
#line 179 "pcat.y"
    { (yyval.Tast) = NULL; ;}
    break;

  case 47:
#line 180 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), else_node, clst(1, (yyvsp[(2) - (2)].Tast_list))); ;}
    break;

  case 48:
#line 182 "pcat.y"
    { (yyval.Tast) = NULL; ;}
    break;

  case 49:
#line 183 "pcat.y"
    { (yyval.Tast) = (yyvsp[(2) - (2)].Tast); ;}
    break;

  case 50:
#line 185 "pcat.y"
    { (yyval.Tast) = NULL; ;}
    break;

  case 51:
#line 186 "pcat.y"
    { (yyval.Tast) = (yyvsp[(1) - (1)].Tast); ;}
    break;

  case 52:
#line 188 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), io_node, cons((yyvsp[(2) - (4)].Tast), reverse((yyvsp[(3) - (4)].Tast_list)))); ;}
    break;

  case 53:
#line 189 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 54:
#line 190 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(3) - (3)].Tast), (yyvsp[(1) - (3)].Tast_list)); ;}
    break;

  case 55:
#line 192 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), io_node, cons((yyvsp[(2) - (4)].Tast), reverse((yyvsp[(3) - (4)].Tast_list)))); ;}
    break;

  case 56:
#line 193 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), io_node, NULL); ;}
    break;

  case 57:
#line 194 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 58:
#line 195 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(3) - (3)].Tast), (yyvsp[(1) - (3)].Tast_list)); ;}
    break;

  case 59:
#line 197 "pcat.y"
    { (yyval.Tast) = (yyvsp[(1) - (1)].Tast); ;}
    break;

  case 60:
#line 198 "pcat.y"
    { (yyval.Tast) = (yyvsp[(1) - (1)].Tast); ;}
    break;

  case 61:
#line 200 "pcat.y"
    { (yyval.Tast) = (yyvsp[(1) - (1)].Tast); ;}
    break;

  case 62:
#line 201 "pcat.y"
    { (yyval.Tast) = (yyvsp[(1) - (1)].Tast); ;}
    break;

  case 63:
#line 202 "pcat.y"
    { (yyval.Tast) = (yyvsp[(2) - (3)].Tast); ;}
    break;

  case 64:
#line 204 "pcat.y"
    { (yyval.Tast) = mk_unaryexp(&((yyloc)), pos_exp, (yyvsp[(2) - (2)].Tast)); ;}
    break;

  case 65:
#line 205 "pcat.y"
    { (yyval.Tast) = mk_unaryexp(&((yyloc)), neg_exp, (yyvsp[(2) - (2)].Tast)); ;}
    break;

  case 66:
#line 206 "pcat.y"
    { (yyval.Tast) = mk_unaryexp(&((yyloc)), not_exp, (yyvsp[(2) - (2)].Tast)); ;}
    break;

  case 67:
#line 208 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),  plus_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 68:
#line 209 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)), minus_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 69:
#line 210 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)), times_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 70:
#line 211 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),  fdiv_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 71:
#line 212 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),   div_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 72:
#line 213 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),   mod_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 73:
#line 214 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),    or_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 74:
#line 215 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),   and_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 75:
#line 216 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),    gt_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 76:
#line 217 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),    lt_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 77:
#line 218 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),    eq_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 78:
#line 219 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),    ge_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 79:
#line 220 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),    le_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 80:
#line 221 "pcat.y"
    { (yyval.Tast) = mk_binexp(&((yyloc)),   neq_exp, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast)); ;}
    break;

  case 81:
#line 222 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), fcall_exp, clst(2, (yyvsp[(1) - (2)].Tast), (yyvsp[(2) - (2)].Tast))); ;}
    break;

  case 82:
#line 223 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), finit_exp, clst(2, (yyvsp[(1) - (2)].Tast), (yyvsp[(2) - (2)].Tast))); ;}
    break;

  case 83:
#line 224 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), ainit_exp, clst(2, (yyvsp[(1) - (2)].Tast), (yyvsp[(2) - (2)].Tast))); ;}
    break;

  case 85:
#line 227 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), idx_exp, clst(2, (yyvsp[(1) - (4)].Tast), (yyvsp[(3) - (4)].Tast))); ;}
    break;

  case 86:
#line 228 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), mem_exp, clst(2, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast))); ;}
    break;

  case 87:
#line 230 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), args_node, cons((yyvsp[(2) - (4)].Tast), reverse((yyvsp[(3) - (4)].Tast_list)))); ;}
    break;

  case 88:
#line 231 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), args_node, NULL); ;}
    break;

  case 89:
#line 232 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 90:
#line 233 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(3) - (3)].Tast), (yyvsp[(1) - (3)].Tast_list)); ;}
    break;

  case 91:
#line 235 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), fasg_node, cons(mk_noder(&((yylsp[(2) - (6)])), &((yylsp[(4) - (6)])), fasg_exp, clst(2, (yyvsp[(2) - (6)].Tast), (yyvsp[(4) - (6)].Tast))), reverse((yyvsp[(5) - (6)].Tast_list)))); ;}
    break;

  case 92:
#line 236 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 93:
#line 237 "pcat.y"
    { (yyval.Tast_list) = cons(mk_noder(&((yylsp[(3) - (5)])), &((yylsp[(5) - (5)])), fasg_exp, clst(2, (yyvsp[(3) - (5)].Tast), (yyvsp[(5) - (5)].Tast))), (yyvsp[(1) - (5)].Tast_list)); ;}
    break;

  case 94:
#line 239 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), aval_node, cons((yyvsp[(2) - (4)].Tast), reverse((yyvsp[(3) - (4)].Tast_list)))); ;}
    break;

  case 95:
#line 240 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 96:
#line 241 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(3) - (3)].Tast), (yyvsp[(1) - (3)].Tast_list)); ;}
    break;

  case 97:
#line 243 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), aval_exp, clst(1, (yyvsp[(1) - (1)].Tast))); ;}
    break;

  case 98:
#line 244 "pcat.y"
    { (yyval.Tast) = mk_node(&((yyloc)), aval_exp, clst(2, (yyvsp[(1) - (3)].Tast), (yyvsp[(3) - (3)].Tast))); ;}
    break;

  case 99:
#line 246 "pcat.y"
    { (yyval.Tast) = mk_int(&((yyloc)), yylval.Tint); ;}
    break;

  case 100:
#line 247 "pcat.y"
    { (yyval.Tast) = mk_real(&((yyloc)), yylval.Treal); ;}
    break;

  case 101:
#line 248 "pcat.y"
    { (yyval.Tast) = mk_str(&((yyloc)), yylval.Tstring); ;}
    break;

  case 102:
#line 250 "pcat.y"
    { (yyval.Tast) = mk_var(&((yyloc)), yylval.Tstring); ;}
    break;

  case 103:
#line 251 "pcat.y"
    { (yyval.Tast_list) = NULL; ;}
    break;

  case 104:
#line 252 "pcat.y"
    { (yyval.Tast_list) = cons((yyvsp[(3) - (3)].Tast), (yyvsp[(1) - (3)].Tast_list)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2288 "pcat.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 255 "pcat.y"


