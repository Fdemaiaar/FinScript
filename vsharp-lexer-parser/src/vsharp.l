%option noyywrap
%{
#include "vsharp.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

[ \t\r\n]+              ;   /* ignora espaços e quebras */
"//".*                  ;   /* ignora comentários de linha */

"entity"                return ENTITY;
"cap_table"             return CAP_TABLE;
"deal"                  return DEAL;
"debt_instrument"       return DEBT_INSTRUMENT;
"cost_of_debt"          return COST_OF_DEBT;
"cost_of_equity"        return COST_OF_EQUITY;
"valuation"             return VALUATION;
"npv"                   return NPV;
"irr"                   return IRR;
"wacc"                  return WACC;
"print"                 return PRINT;
"if"                    return IF;
"else"                  return ELSE;
"while"                 return WHILE;
"for"                   return FOR;
"var"                   return VAR;

"=="                    return EQ;
"!="                    return NEQ;
">="                    return GE;
"<="                    return LE;
">"                     return '>';
"<"                     return '<';

"="                     return '=';
";"                     return ';';
","                     return ',';
"{"                     return '{';
"}"                     return '}';
"("                     return '(';
")"                     return ')';
"["                     return '[';
"]"                     return ']';

\"[^\"]*\"              { yylval.str = strdup(yytext); return STRING; }
[0-9]+(\.[0-9]+)?       { yylval.num = atof(yytext);     return NUMBER; }
[A-Za-z_][A-Za-z0-9_]*  { yylval.id  = strdup(yytext);   return IDENTIFIER; }

.                       ;   /* ignora qualquer outro caractere */

%%
