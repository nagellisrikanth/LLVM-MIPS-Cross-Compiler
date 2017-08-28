/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2058 of yacc.c  */
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


/* Line 2058 of yacc.c  */
#line 131 "parser.h"
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
