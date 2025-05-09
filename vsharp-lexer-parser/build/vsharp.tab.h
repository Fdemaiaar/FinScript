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
    BOOL_LITERAL = 261,            /* BOOL_LITERAL  */
    ENTITY = 262,                  /* ENTITY  */
    CAP_TABLE = 263,               /* CAP_TABLE  */
    DEAL = 264,                    /* DEAL  */
    DEBT_INSTRUMENT = 265,         /* DEBT_INSTRUMENT  */
    COST_OF_DEBT = 266,            /* COST_OF_DEBT  */
    COST_OF_EQUITY = 267,          /* COST_OF_EQUITY  */
    VALUATION = 268,               /* VALUATION  */
    PRINT = 269,                   /* PRINT  */
    VAR = 270,                     /* VAR  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    WHILE = 273,                   /* WHILE  */
    FOR = 274,                     /* FOR  */
    INT_TYPE = 275,                /* INT_TYPE  */
    BOOL_TYPE = 276,               /* BOOL_TYPE  */
    STRING_TYPE = 277,             /* STRING_TYPE  */
    NPV = 278,                     /* NPV  */
    IRR = 279,                     /* IRR  */
    WACC = 280,                    /* WACC  */
    EQ = 281,                      /* EQ  */
    NE = 282,                      /* NE  */
    GT = 283,                      /* GT  */
    LT = 284,                      /* LT  */
    GE = 285,                      /* GE  */
    LE = 286,                      /* LE  */
    AND = 287,                     /* AND  */
    OR = 288,                      /* OR  */
    NOT = 289,                     /* NOT  */
    ASSIGN = 290,                  /* ASSIGN  */
    SEMICOLON = 291,               /* SEMICOLON  */
    COMMA = 292,                   /* COMMA  */
    LPAREN = 293,                  /* LPAREN  */
    RPAREN = 294,                  /* RPAREN  */
    LBRACE = 295,                  /* LBRACE  */
    RBRACE = 296,                  /* RBRACE  */
    LBRACKET = 297,                /* LBRACKET  */
    RBRACKET = 298,                /* RBRACKET  */
    UMINUS = 299                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "src/vsharp.y"

    double      num;
    char       *id;
    char       *str;

#line 114 "build/vsharp.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BUILD_VSHARP_TAB_H_INCLUDED  */
