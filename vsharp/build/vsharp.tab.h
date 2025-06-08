/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_VSHARP_TAB_H_INCLUDED
# define YY_YY_BUILD_VSHARP_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/vsharp.y"
#include "ast.h"

#line 52 "build/vsharp.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    NUMBER = 259,                  /* NUMBER  */
    STRING = 260,                  /* STRING  */
    DATE = 261,                    /* DATE  */
    BOOL_LITERAL = 262,            /* BOOL_LITERAL  */
    ENTITY = 263,                  /* ENTITY  */
    CAP_TABLE = 264,               /* CAP_TABLE  */
    DEAL = 265,                    /* DEAL  */
    DEBT_INSTRUMENT = 266,         /* DEBT_INSTRUMENT  */
    COST_OF_DEBT = 267,            /* COST_OF_DEBT  */
    COST_OF_EQUITY = 268,          /* COST_OF_EQUITY  */
    VALUATION = 269,               /* VALUATION  */
    PRINT = 270,                   /* PRINT  */
    VAR = 271,                     /* VAR  */
    IF = 272,                      /* IF  */
    ELSE = 273,                    /* ELSE  */
    WHILE = 274,                   /* WHILE  */
    FOR = 275,                     /* FOR  */
    NPV = 276,                     /* NPV  */
    IRR = 277,                     /* IRR  */
    WACC = 278,                    /* WACC  */
    EQ = 279,                      /* EQ  */
    NE = 280,                      /* NE  */
    GT = 281,                      /* GT  */
    LT = 282,                      /* LT  */
    GE = 283,                      /* GE  */
    LE = 284,                      /* LE  */
    AND = 285,                     /* AND  */
    OR = 286,                      /* OR  */
    NOT = 287,                     /* NOT  */
    ASSIGN = 288,                  /* ASSIGN  */
    SEMICOLON = 289,               /* SEMICOLON  */
    COMMA = 290,                   /* COMMA  */
    COLON = 291,                   /* COLON  */
    LPAREN = 292,                  /* LPAREN  */
    RPAREN = 293,                  /* RPAREN  */
    LBRACE = 294,                  /* LBRACE  */
    RBRACE = 295,                  /* RBRACE  */
    LBRACKET = 296,                /* LBRACKET  */
    RBRACKET = 297,                /* RBRACKET  */
    UMINUS = 298                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "src/vsharp.y"
double num;char *id;char *str;Node *node;

#line 115 "build/vsharp.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BUILD_VSHARP_TAB_H_INCLUDED  */
