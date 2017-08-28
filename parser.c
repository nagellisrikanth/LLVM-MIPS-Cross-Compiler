/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.y"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <list>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include "SymbolTable.h"
#include "Type.h"
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
void yyerror(const char *s);
// Module, function, basic block, and builder
llvm::Module *module;
llvm::Function *function;
llvm::BasicBlock *basic_block;
llvm::IRBuilder<> *builder;
// Environment: stack of symbol tables. It is actually implemented as a list
// to facilitate the traversal of symbol tables.
std::list<SymbolTable *> environment;

/* Line 371 of yacc.c  */
#line 93 "parser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TokenInt = 258,
     TokenFloat = 259,
     TokenVoid = 260,
     TokenStruct = 261,
     TokenId = 262,
     TokenNumber = 263,
     TokenOpenCurly = 264,
     TokenCloseCurly = 265,
     TokenOpenSquare = 266,
     TokenCloseSquare = 267,
     TokenOpenPar = 268,
     TokenClosePar = 269,
     TokenSemicolon = 270,
     TokenComma = 271,
     TokenPoint = 272,
     TokenEqual = 273,
     TokenLogicalOr = 274,
     TokenLogicalAnd = 275,
     TokenLogicalNot = 276,
     TokenGreaterThan = 277,
     TokenLessThan = 278,
     TokenGreaterEqual = 279,
     TokenLessEqual = 280,
     TokenNotEqual = 281,
     TokenDoubleEqual = 282,
     TokenMinus = 283,
     TokenPlus = 284,
     TokenDiv = 285,
     TokenMult = 286,
     TokenIf = 287,
     TokenThen = 288,
     TokenElse = 289,
     TokenWhile = 290
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 67 "parser.y"

char *name;
llvm::Value *llvalue;
int value;
Type *type;
std::list<int> *indices;
// For LValue
struct {
Type *type;
llvm::Value *lladdress;
std::vector<llvm::Value *> *llindices;
} lvalue;
// For mid-rule actions in logical expressions
struct {
llvm::BasicBlock *lhs_basic_block;
llvm::BasicBlock *rhs_basic_block;
llvm::BasicBlock *end_basic_block;
} logical;
// For mid-rule actions in "if" statement
struct {
llvm::BasicBlock *then_basic_block;
llvm::BasicBlock *else_basic_block;
llvm::BasicBlock *end_basic_block;
} if_statement;
// For mid-rule actions in "while" statement
struct {
llvm::BasicBlock *cond_basic_block;
llvm::BasicBlock *body_basic_block;
llvm::BasicBlock *end_basic_block;
} while_statement;
// For 'FormalArguments' and 'FormalArgumentsComma'
std::vector<Symbol *> *formal_arguments;
// For 'FunctionDeclaration'
Symbol *symbol;
// For 'ActualArguments' and 'ActualArgummentsComma'
std::vector<llvm::Value *> *actual_arguments;


/* Line 387 of yacc.c  */
#line 210 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 238 "parser.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   275

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

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
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    14,    15,    22,    25,
      31,    32,    36,    37,    42,    43,    48,    50,    53,    55,
      57,    59,    60,    66,    67,    70,    73,    78,    79,    85,
      87,    88,    93,    94,    95,   103,   104,   111,   113,   115,
     119,   123,   127,   131,   135,   139,   143,   147,   151,   155,
     159,   160,   165,   166,   171,   176,   177,   180,   181,   185,
     187,   192
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    38,    -1,    -1,    38,    39,    -1,    45,
       7,    44,    15,    -1,    -1,    41,     9,    40,    38,    48,
      10,    -1,    41,    15,    -1,    45,     7,    13,    42,    14,
      -1,    -1,    43,    45,     7,    -1,    -1,    43,    45,     7,
      16,    -1,    -1,    11,     8,    12,    44,    -1,    46,    -1,
      45,    31,    -1,     3,    -1,     4,    -1,     5,    -1,    -1,
       6,     9,    47,    38,    10,    -1,    -1,    48,    49,    -1,
      56,    15,    -1,    61,    18,    56,    15,    -1,    -1,     9,
      50,    38,    48,    10,    -1,    54,    -1,    -1,    54,    34,
      51,    49,    -1,    -1,    -1,    35,    52,    13,    56,    14,
      53,    49,    -1,    -1,    32,    13,    56,    14,    55,    49,
      -1,    61,    -1,     8,    -1,    56,    29,    56,    -1,    56,
      28,    56,    -1,    56,    31,    56,    -1,    56,    30,    56,
      -1,    13,    56,    14,    -1,    56,    22,    56,    -1,    56,
      23,    56,    -1,    56,    24,    56,    -1,    56,    25,    56,
      -1,    56,    27,    56,    -1,    56,    26,    56,    -1,    -1,
      56,    19,    57,    56,    -1,    -1,    56,    20,    58,    56,
      -1,     7,    13,    59,    14,    -1,    -1,    60,    56,    -1,
      -1,    60,    56,    16,    -1,     7,    -1,    61,    11,    56,
      12,    -1,    61,    17,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   106,   106,   107,   108,   110,   144,   143,   186,   188,
     214,   217,   225,   228,   236,   239,   245,   249,   256,   261,
     266,   272,   271,   292,   293,   295,   296,   305,   304,   315,
     324,   323,   347,   368,   346,   387,   386,   413,   421,   426,
     431,   436,   441,   446,   450,   454,   458,   462,   466,   470,
     475,   474,   511,   510,   546,   564,   567,   573,   576,   582,
     610,   625
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TokenInt", "TokenFloat", "TokenVoid",
  "TokenStruct", "TokenId", "TokenNumber", "TokenOpenCurly",
  "TokenCloseCurly", "TokenOpenSquare", "TokenCloseSquare", "TokenOpenPar",
  "TokenClosePar", "TokenSemicolon", "TokenComma", "TokenPoint",
  "TokenEqual", "TokenLogicalOr", "TokenLogicalAnd", "TokenLogicalNot",
  "TokenGreaterThan", "TokenLessThan", "TokenGreaterEqual",
  "TokenLessEqual", "TokenNotEqual", "TokenDoubleEqual", "TokenMinus",
  "TokenPlus", "TokenDiv", "TokenMult", "TokenIf", "TokenThen",
  "TokenElse", "TokenWhile", "$accept", "Start", "Declarations",
  "Declaration", "$@1", "FunctionDeclaration", "FormalArguments",
  "FormalArgumentsComma", "Indices", "Pointer", "Type", "@2", "Statements",
  "Statement", "$@3", "@4", "@5", "$@6", "IfStatement", "@7", "Expression",
  "@8", "@9", "ActualArguments", "ActualArgumentsComma", "LValue", YY_NULL
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
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    40,    39,    39,    41,
      42,    42,    43,    43,    44,    44,    45,    45,    46,    46,
      46,    47,    46,    48,    48,    49,    49,    50,    49,    49,
      51,    49,    52,    53,    49,    55,    54,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    56,    58,    56,    56,    59,    59,    60,    60,    61,
      61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     4,     0,     6,     2,     5,
       0,     3,     0,     4,     0,     4,     1,     2,     1,     1,
       1,     0,     5,     0,     2,     2,     4,     0,     5,     1,
       0,     4,     0,     0,     7,     0,     6,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     0,     4,     4,     0,     2,     0,     3,     1,
       4,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,    18,    19,    20,     0,     4,     0,
       0,    16,    21,     6,     8,    14,    17,     3,     3,     0,
      12,     0,     0,    23,     0,     0,     0,     5,    22,     0,
      14,     9,     0,    59,    38,    27,     7,     0,     0,    32,
      24,    29,     0,    37,    15,    11,    57,     3,     0,    37,
       0,     0,    30,    25,    50,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    23,    43,     0,     0,     0,     0,     0,    44,
      45,    46,    47,    49,    48,    40,    39,    42,    41,     0,
      61,     0,    54,    56,     0,    35,     0,    31,    51,    53,
      60,    26,    58,    28,     0,    33,    36,     0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,    18,     9,    25,    26,    21,    10,
      11,    17,    29,    40,    47,    76,    51,   107,    41,   104,
      42,    77,    78,    70,    71,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -74
static const yytype_int16 yypact[] =
{
     -74,     5,    95,   -74,   -74,   -74,   -74,     7,   -74,     3,
       2,   -74,   -74,   -74,   -74,     4,   -74,   -74,   -74,    11,
      24,    25,   247,    95,    38,    34,    95,   -74,   -74,    36,
      55,   -74,     6,    54,   -74,   -74,   -74,    48,    56,   -74,
     -74,    39,   136,    -7,   -74,    58,    66,   -74,    83,    -9,
      48,    57,   -74,   -74,   -74,   -74,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    74,    48,   -74,
      68,    48,    95,   -74,   101,    48,    51,    48,    48,   191,
     210,   218,   233,   239,   244,    32,    32,   -74,   -74,    65,
     -74,   153,   -74,   169,    44,   -74,   119,   -74,   181,   201,
     -74,   -74,   -74,   -74,    51,   -74,   -74,    51,   -74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   -11,   -74,   -74,   -74,   -74,   -74,    42,    78,
     -74,   -74,    45,   -73,   -74,   -74,   -74,   -74,   -74,   -74,
     -36,   -74,   -74,   -74,   -74,   -29
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -56
static const yytype_int8 yytable[] =
{
      43,    48,    66,    97,    66,     3,    22,    23,    67,    15,
      67,    68,    13,    45,    74,    19,    12,    20,    14,    24,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,   106,    91,    16,   108,    93,    72,    16,   -10,    96,
      27,    98,    99,    33,    34,    35,    36,    43,    31,    37,
      30,    33,    34,    35,   103,    33,    34,    37,    33,    34,
      35,    37,    64,    65,    37,    43,    19,    46,    38,    50,
      75,    39,    44,    52,    69,    43,    38,   100,    43,    39,
     -55,    90,    92,    38,    54,    55,    39,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    73,     4,     5,
       6,     7,    54,    55,    32,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    95,     0,    94,     0,     0,
      54,    55,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   105,     0,     0,     0,     0,    54,    55,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    53,     0,     0,     0,    54,    55,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,   101,     0,
       0,     0,    54,    55,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,   102,     0,     0,    54,    55,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    55,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   -56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   -56,    58,    59,    60,    61,    62,    63,
      64,    65,   -56,    59,    60,    61,    62,    63,    64,    65,
       4,     5,     6,     7,     0,     0,     0,    28,   -56,    60,
      61,    62,    63,    64,    65,   -56,    61,    62,    63,    64,
      65,   -56,    62,    63,    64,    65
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-56)))

static const yytype_int8 yycheck[] =
{
      29,    37,    11,    76,    11,     0,    17,    18,    17,     7,
      17,    18,     9,     7,    50,    11,     9,    13,    15,     8,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,   104,    68,    31,   107,    71,    47,    31,    14,    75,
      15,    77,    78,     7,     8,     9,    10,    76,    14,    13,
      12,     7,     8,     9,    10,     7,     8,    13,     7,     8,
       9,    13,    30,    31,    13,    94,    11,    13,    32,    13,
      13,    35,    30,    34,    16,   104,    32,    12,   107,    35,
      14,     7,    14,    32,    19,    20,    35,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    14,     3,     4,
       5,     6,    19,    20,    26,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    14,    -1,    72,    -1,    -1,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    14,    -1,    -1,    -1,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    15,    -1,    -1,    -1,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    15,    -1,
      -1,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    16,    -1,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    20,    -1,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    24,    25,    26,    27,    28,    29,    30,    31,
       3,     4,     5,     6,    -1,    -1,    -1,    10,    25,    26,
      27,    28,    29,    30,    31,    26,    27,    28,    29,    30,
      31,    27,    28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    37,    38,     0,     3,     4,     5,     6,    39,    41,
      45,    46,     9,     9,    15,     7,    31,    47,    40,    11,
      13,    44,    38,    38,     8,    42,    43,    15,    10,    48,
      12,    14,    45,     7,     8,     9,    10,    13,    32,    35,
      49,    54,    56,    61,    44,     7,    13,    50,    56,    61,
      13,    52,    34,    15,    19,    20,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    11,    17,    18,    16,
      59,    60,    38,    14,    56,    13,    51,    57,    58,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
       7,    56,    14,    56,    48,    14,    56,    49,    56,    56,
      12,    15,    16,    10,    55,    14,    49,    53,    49
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
/* Line 1792 of yacc.c  */
#line 111 "parser.y"
    {
// Get top symbol table
SymbolTable *symbol_table = environment.back();
// Create new symbol
Symbol *symbol = new Symbol((yyvsp[(2) - (4)].name));
symbol->type = (yyvsp[(1) - (4)].type);
symbol->index = symbol_table->size();
// Process indices
for (int index : *(yyvsp[(3) - (4)].indices))
{
Type *type = new Type(Type::KindArray);
type->num_elem = index;
type->subtype = symbol->type;
type->lltype = llvm::ArrayType::get(symbol->type->lltype, index);
symbol->type = type;
}
// Symbol in global scope
if (symbol_table->getScope() == SymbolTable::ScopeGlobal)
symbol->lladdress = new llvm::GlobalVariable(
*module,
symbol->type->lltype,
false,
llvm::GlobalValue::ExternalLinkage,
nullptr,
symbol->getName());
// Symbol in local scope
else if (symbol_table->getScope() == SymbolTable::ScopeLocal)
symbol->lladdress = builder->CreateAlloca(symbol->type->lltype,
nullptr, Symbol::getTemp());
// Insert in symbol table
symbol_table->addSymbol(symbol);
}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 144 "parser.y"
    {
// Push new local symbol table
SymbolTable *symbol_table = new SymbolTable(SymbolTable::ScopeLocal);
environment.push_back(symbol_table);
// Current LLVM function
function = llvm::cast<llvm::Function>((yyvsp[(1) - (2)].symbol)->lladdress);
// Create entry basic block
basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
builder->SetInsertPoint(basic_block);
// Add arguments to the stack
int index = 0;
for (llvm::Function::arg_iterator it = function->arg_begin(),
end = function->arg_end();
it != end;
++it)
{
// Name argument
Symbol *argument = (*(yyvsp[(1) - (2)].symbol)->type->arguments)[index++];
it->setName(argument->getName());
// Create local symbol
Symbol *symbol = new Symbol(argument->getName());
symbol->type = argument->type;
symbol_table->addSymbol(symbol);
// Emit 'alloca' instruction
symbol->lladdress = builder->CreateAlloca(symbol->type->lltype,
nullptr, Symbol::getTemp());
// Emit 'store' instruction
builder->CreateStore(it, symbol->lladdress);
}
}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 178 "parser.y"
    {
// Return statement, if not present
if (!basic_block->getTerminator())
builder->CreateRetVoid();
// Pop local symbol table
SymbolTable *symbol_table = environment.back();
environment.pop_back();
}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 189 "parser.y"
    {
// Create type
Type *type = new Type(Type::KindFunction);
type->rettype = (yyvsp[(1) - (5)].type);
type->arguments = (yyvsp[(4) - (5)].formal_arguments);
// Create symbol
Symbol *symbol = new Symbol((yyvsp[(2) - (5)].name));
symbol->type = type;
(yyval.symbol) = symbol;
// Add to global symbol table
SymbolTable *symbol_table = environment.front();
symbol_table->addSymbol(symbol);
// Create function type
std::vector<llvm::Type *> types;
for (Symbol *symbol : *(yyvsp[(4) - (5)].formal_arguments))
types.push_back(symbol->type->lltype);
llvm::FunctionType *function_type = llvm::FunctionType::get(
(yyvsp[(1) - (5)].type)->lltype,
types,
false);
// Insert function
symbol->lladdress = module->getOrInsertFunction((yyvsp[(2) - (5)].name),
function_type);
}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 214 "parser.y"
    {
(yyval.formal_arguments) = new std::vector<Symbol *>();
}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 218 "parser.y"
    {
Symbol *symbol = new Symbol((yyvsp[(3) - (3)].name));
symbol->type = (yyvsp[(2) - (3)].type);
symbol->index = (yyvsp[(1) - (3)].formal_arguments)->size();
(yyval.formal_arguments)->push_back(symbol);
}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 225 "parser.y"
    {
(yyval.formal_arguments) = new std::vector<Symbol *>();
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 229 "parser.y"
    {
Symbol *symbol = new Symbol((yyvsp[(3) - (4)].name));
symbol->type = (yyvsp[(2) - (4)].type);
symbol->index = (yyvsp[(1) - (4)].formal_arguments)->size();
(yyval.formal_arguments)->push_back(symbol);
}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 236 "parser.y"
    {
(yyval.indices) = new std::list<int>();
}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 240 "parser.y"
    {
(yyval.indices) = (yyvsp[(4) - (4)].indices);
(yyval.indices)->push_back((yyvsp[(2) - (4)].value));
}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 246 "parser.y"
    {
(yyval.type) = (yyvsp[(1) - (1)].type);
}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 250 "parser.y"
    {
(yyval.type) = new Type(Type::KindPointer);
(yyval.type)->subtype = (yyvsp[(1) - (2)].type);
(yyval.type)->lltype = llvm::PointerType::get((yyvsp[(1) - (2)].type)->lltype, 0);
}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 257 "parser.y"
    {
(yyval.type) = new Type(Type::KindInt);
(yyval.type)->lltype = llvm::Type::getInt32Ty(llvm::getGlobalContext());
}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 262 "parser.y"
    {
(yyval.type) = new Type(Type::KindFloat);
(yyval.type)->lltype = llvm::Type::getFloatTy(llvm::getGlobalContext());
}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 267 "parser.y"
    {
(yyval.type) = new Type(Type::KindVoid);
(yyval.type)->lltype = llvm::Type::getVoidTy(llvm::getGlobalContext());
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 272 "parser.y"
    {
// Push new symbol table to environment
SymbolTable *symbol_table = new SymbolTable(SymbolTable::ScopeStruct);
environment.push_back(symbol_table);
// Create type
(yyval.type) = new Type(Type::KindStruct);
(yyval.type)->symbol_table = symbol_table;
}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 281 "parser.y"
    {
// Forward type
(yyval.type) = (yyvsp[(3) - (5)].type);
// LLVM structure
SymbolTable *symbol_table = environment.back();
std::vector<llvm::Type *> lltypes;
symbol_table->getLLVMTypes(lltypes);
(yyval.type)->lltype = llvm::StructType::create(llvm::getGlobalContext(), lltypes);
// Pop symbol table from environment
environment.pop_back();
}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 297 "parser.y"
    {
llvm::Value *lladdress = (yyvsp[(1) - (4)].lvalue).llindices->size() > 1 ?
builder->CreateGEP((yyvsp[(1) - (4)].lvalue).lladdress, *(yyvsp[(1) - (4)].lvalue).llindices,
Symbol::getTemp()) :
(yyvsp[(1) - (4)].lvalue).lladdress;
builder->CreateStore((yyvsp[(3) - (4)].llvalue), lladdress);
}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 305 "parser.y"
    {
// Push new local symbol table
SymbolTable *symbol_table = new SymbolTable(SymbolTable::ScopeLocal);
environment.push_back(symbol_table);
}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 311 "parser.y"
    {
// Pop symbol table
environment.pop_back();
}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 316 "parser.y"
    {
// Emit unconditional to 'end' basic block
builder->CreateBr((yyvsp[(1) - (1)].if_statement).end_basic_block);
// Move to 'end' basic block
basic_block = (yyvsp[(1) - (1)].if_statement).end_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 324 "parser.y"
    {
// Create separate 'else' and 'end' basic blocks
(yyval.if_statement).then_basic_block = (yyvsp[(1) - (2)].if_statement).then_basic_block;
(yyval.if_statement).else_basic_block = (yyvsp[(1) - (2)].if_statement).else_basic_block;
(yyval.if_statement).end_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
// Emit unconditional branch to 'end' basic block
builder->CreateBr((yyval.if_statement).end_basic_block);
// Move to 'else' basic block
basic_block = (yyval.if_statement).else_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 339 "parser.y"
    {
// Emit unconditional branch to 'end' basic block
builder->CreateBr((yyvsp[(3) - (4)].if_statement).end_basic_block);
// Move to 'end' basic block
basic_block = (yyvsp[(3) - (4)].if_statement).end_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 347 "parser.y"
    {
// Create 'cond', 'body', and 'end' basic blocks
(yyval.while_statement).cond_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
(yyval.while_statement).body_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
(yyval.while_statement).end_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
// Emit unconditional branch
builder->CreateBr((yyval.while_statement).cond_basic_block);
// Continue in 'cond' basic block
basic_block = (yyval.while_statement).cond_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 368 "parser.y"
    {
// Emit conditional branch
builder->CreateCondBr((yyvsp[(4) - (5)].llvalue),
(yyvsp[(2) - (5)].while_statement).body_basic_block,
(yyvsp[(2) - (5)].while_statement).end_basic_block);
// Continue in 'body' basic block
basic_block = (yyvsp[(2) - (5)].while_statement).body_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 378 "parser.y"
    {
// Emit unconditional branch
builder->CreateBr((yyvsp[(2) - (7)].while_statement).cond_basic_block);
// Continue in 'end' basic block
basic_block = (yyvsp[(2) - (7)].while_statement).end_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 387 "parser.y"
    {
// Create 'if' and 'else' basic blocks, assume 'end' is same as 'else'.
(yyval.if_statement).then_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
(yyval.if_statement).else_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
(yyval.if_statement).end_basic_block = (yyval.if_statement).else_basic_block;
// Emit conditional branch
builder->CreateCondBr((yyvsp[(3) - (4)].llvalue),
(yyval.if_statement).then_basic_block,
(yyval.if_statement).else_basic_block);
// Continue in 'then' basic block
basic_block = (yyval.if_statement).then_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 407 "parser.y"
    {
(yyval.if_statement).then_basic_block = (yyvsp[(5) - (6)].if_statement).then_basic_block;
(yyval.if_statement).else_basic_block = (yyvsp[(5) - (6)].if_statement).else_basic_block;
(yyval.if_statement).end_basic_block = (yyvsp[(5) - (6)].if_statement).end_basic_block;
}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 414 "parser.y"
    {
llvm::Value *lladdress = (yyvsp[(1) - (1)].lvalue).llindices->size() > 1 ?
builder->CreateGEP((yyvsp[(1) - (1)].lvalue).lladdress, *(yyvsp[(1) - (1)].lvalue).llindices,
Symbol::getTemp()) :
(yyvsp[(1) - (1)].lvalue).lladdress;
(yyval.llvalue) = builder->CreateLoad(lladdress, Symbol::getTemp());
}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 422 "parser.y"
    {
llvm::Type *lltype = llvm::Type::getInt32Ty(llvm::getGlobalContext());
(yyval.llvalue) = llvm::ConstantInt::get(lltype, (yyvsp[(1) - (1)].value));
}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 427 "parser.y"
    {
(yyval.llvalue) = builder->CreateBinOp(llvm::Instruction::Add, (yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue),
Symbol::getTemp());
}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 432 "parser.y"
    {
(yyval.llvalue) = builder->CreateBinOp(llvm::Instruction::Sub, (yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue),
Symbol::getTemp());
}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 437 "parser.y"
    {
(yyval.llvalue) = builder->CreateBinOp(llvm::Instruction::Mul, (yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue),
Symbol::getTemp());
}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 442 "parser.y"
    {
(yyval.llvalue) = builder->CreateBinOp(llvm::Instruction::SDiv, (yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue),
Symbol::getTemp());
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 447 "parser.y"
    {
(yyval.llvalue) = (yyvsp[(2) - (3)].llvalue);
}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 451 "parser.y"
    {
(yyval.llvalue) = builder->CreateICmpSGT((yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue), Symbol::getTemp());
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 455 "parser.y"
    {
(yyval.llvalue) = builder->CreateICmpSLT((yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue), Symbol::getTemp());
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 459 "parser.y"
    {
(yyval.llvalue) = builder->CreateICmpSGE((yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue), Symbol::getTemp());
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 463 "parser.y"
    {
(yyval.llvalue) = builder->CreateICmpSLE((yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue), Symbol::getTemp());
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 467 "parser.y"
    {
(yyval.llvalue) = builder->CreateICmpEQ((yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue), Symbol::getTemp());
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 471 "parser.y"
    {
(yyval.llvalue) = builder->CreateICmpNE((yyvsp[(1) - (3)].llvalue), (yyvsp[(3) - (3)].llvalue), Symbol::getTemp());
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 475 "parser.y"
    {
// Save current basic block
(yyval.logical).lhs_basic_block = basic_block;
// Create RHS and end basic blocks
(yyval.logical).rhs_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
(yyval.logical).end_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
// Emit conditional branch
builder->CreateCondBr((yyvsp[(1) - (2)].llvalue),
(yyval.logical).end_basic_block,
(yyval.logical).rhs_basic_block);
// Set current basic block to RHS
basic_block = (yyval.logical).rhs_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 496 "parser.y"
    {
// Emit unconditional branch
builder->CreateBr((yyvsp[(3) - (4)].logical).end_basic_block);
// Move to end basic block
basic_block = (yyvsp[(3) - (4)].logical).end_basic_block;
builder->SetInsertPoint(basic_block);
// Emit phi instruction
llvm::PHINode *phi = builder->CreatePHI(
llvm::IntegerType::getInt1Ty(llvm::getGlobalContext()),
2, Symbol::getTemp());
phi->addIncoming((yyvsp[(1) - (4)].llvalue), (yyvsp[(3) - (4)].logical).lhs_basic_block);
phi->addIncoming((yyvsp[(4) - (4)].llvalue), (yyvsp[(3) - (4)].logical).rhs_basic_block);
(yyval.llvalue) = phi;
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 511 "parser.y"
    {
// Save current basic block
(yyval.logical).lhs_basic_block = basic_block;
// Create RHS and end basic blocks
(yyval.logical).rhs_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
(yyval.logical).end_basic_block = llvm::BasicBlock::Create(
llvm::getGlobalContext(),
Symbol::getBasicBlock(),
function);
// Emit conditional branch
builder->CreateCondBr((yyvsp[(1) - (2)].llvalue),
(yyval.logical).rhs_basic_block,
(yyval.logical).end_basic_block);
// Set current basic block to RHS
basic_block = (yyval.logical).rhs_basic_block;
builder->SetInsertPoint(basic_block);
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 532 "parser.y"
    {
// Emit unconditional branch
builder->CreateBr((yyvsp[(3) - (4)].logical).end_basic_block);
// Move to end basic block
basic_block = (yyvsp[(3) - (4)].logical).end_basic_block;
builder->SetInsertPoint(basic_block);
// Emit phi instruction
llvm::PHINode *phi = builder->CreatePHI(
llvm::IntegerType::getInt1Ty(llvm::getGlobalContext()),
2, Symbol::getTemp());
phi->addIncoming((yyvsp[(1) - (4)].llvalue), (yyvsp[(3) - (4)].logical).lhs_basic_block);
phi->addIncoming((yyvsp[(4) - (4)].llvalue), (yyvsp[(3) - (4)].logical).rhs_basic_block);
(yyval.llvalue) = phi;
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 547 "parser.y"
    {
// Search function in global scope
SymbolTable *symbol_table = environment.front();
Symbol *symbol = symbol_table->getSymbol((yyvsp[(1) - (4)].name));
// Undeclared, or not a function
if (!symbol || symbol->type->getKind() != Type::KindFunction)
{
std::cerr << "Identifier is not a function: " << (yyvsp[(1) - (4)].name) << '\n';
exit(1);
}
// Invoke
(yyval.llvalue) = builder->CreateCall(symbol->lladdress,
*(yyvsp[(3) - (4)].actual_arguments),
symbol->type->rettype->getKind() == Type::KindVoid ?
"" : Symbol::getTemp());
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 564 "parser.y"
    {
(yyval.actual_arguments) = new std::vector<llvm::Value *>();
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 568 "parser.y"
    {
(yyval.actual_arguments) = (yyvsp[(1) - (2)].actual_arguments);
(yyval.actual_arguments)->push_back((yyvsp[(2) - (2)].llvalue));
}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 573 "parser.y"
    {
(yyval.actual_arguments) = new std::vector<llvm::Value *>();
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 577 "parser.y"
    {
(yyval.actual_arguments) = (yyvsp[(1) - (3)].actual_arguments);
(yyval.actual_arguments)->push_back((yyvsp[(2) - (3)].llvalue));
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 583 "parser.y"
    {
// Search symbol in environment, from the top to the bottom
Symbol *symbol = nullptr;
for (auto it = environment.rbegin();
it != environment.rend();
++it)
{
SymbolTable *symbol_table = *it;
symbol = symbol_table->getSymbol((yyvsp[(1) - (1)].name));
if (symbol)
break;
}
// Undeclared
if (!symbol)
{
std::cerr << "Undeclared identifier: " << (yyvsp[(1) - (1)].name) << '\n';
exit(1);
}
// Save info
(yyval.lvalue).type = symbol->type;
(yyval.lvalue).lladdress = symbol->lladdress;
(yyval.lvalue).llindices = new std::vector<llvm::Value *>();
// Add initial index set to 0
llvm::Type *lltype = llvm::Type::getInt32Ty(llvm::getGlobalContext());
llvm::Value *llindex = llvm::ConstantInt::get(lltype, 0);
(yyval.lvalue).llindices->push_back(llindex);
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 611 "parser.y"
    {
// Check that L-value is array
if ((yyvsp[(1) - (4)].lvalue).type->getKind() != Type::KindArray)
{
std::cerr << "L-value is not an array\n";
exit(1);
}
// Add index
(yyval.lvalue).llindices = (yyvsp[(1) - (4)].lvalue).llindices;
(yyval.lvalue).llindices->push_back((yyvsp[(3) - (4)].llvalue));
// Type and address
(yyval.lvalue).type = (yyvsp[(1) - (4)].lvalue).type->subtype;
(yyval.lvalue).lladdress = (yyvsp[(1) - (4)].lvalue).lladdress;
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 626 "parser.y"
    {
// Check that L-value is a structure
if ((yyvsp[(1) - (3)].lvalue).type->getKind() != Type::KindStruct)
{
std::cerr << "L-value is not a struct\n";
exit(1);
}
// Find symbol in structure
Symbol *symbol = (yyvsp[(1) - (3)].lvalue).type->symbol_table->getSymbol((yyvsp[(3) - (3)].name));
if (!symbol)
{
std::cerr << "Invalid field: " << (yyvsp[(3) - (3)].name) << '\n';
exit(1);
}
// Add index
llvm::Type *lltype = llvm::Type::getInt32Ty(llvm::getGlobalContext());
llvm::Value *llindex = llvm::ConstantInt::get(lltype, symbol->index);
(yyval.lvalue).llindices = (yyvsp[(1) - (3)].lvalue).llindices;
(yyval.lvalue).llindices->push_back(llindex);
// Type and address
(yyval.lvalue).type = symbol->type;
(yyval.lvalue).lladdress = (yyvsp[(1) - (3)].lvalue).lladdress;
}
    break;


/* Line 1792 of yacc.c  */
#line 2302 "parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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


/* Line 2055 of yacc.c  */
#line 649 "parser.y"

int main(int argc, char **argv)
{
// Syntax
if (argc != 2)
{
std::cerr << "Syntax: ./main <file>\n";
exit(1);
}
// Open file in 'yyin'
yyin = fopen(argv[1], "r");
if (!yyin)
{
std::cerr << "Cannot open file\n";
exit(1);
}
// LLVM context, builder, and module
llvm::LLVMContext &context = llvm::getGlobalContext();
builder = new llvm::IRBuilder<>(context);
module = new llvm::Module("TestModule", context);
// Push global symbol table to environment
SymbolTable *global_symbol_table = new SymbolTable(SymbolTable::ScopeGlobal);
environment.push_back(global_symbol_table);
// Parse input until there is no more
do
{
yyparse();
} while (!feof(yyin));
// Dump module
module->dump();
return 0;
}
void yyerror(const char *s)
{
std::cerr << s << std::endl;
exit(1);
}
