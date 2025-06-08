%option noyywrap
%option nounput noinput
%option yylineno
%{
#include "vsharp.tab.h"
#include <stdlib.h>
#include <string.h>
extern int yylineno;
%}
DIGIT [0-9]
LETTER [A-Za-z_]
ID {LETTER}({LETTER}|{DIGIT})*
FLOAT {DIGIT}+"."{DIGIT}+
INT {DIGIT}+
NUMBER {FLOAT}|{INT}
DATE {DIGIT}{DIGIT}{DIGIT}{DIGIT}-{DIGIT}{DIGIT}-{DIGIT}{DIGIT}
STRING \"([^\"\\\n]|\\.)*\"
%%
[ \t\r\n]+
"//".*
"entity" {return ENTITY;}
"cap_table" {return CAP_TABLE;}
"deal" {return DEAL;}
"debt_instrument" {return DEBT_INSTRUMENT;}
"cost_of_debt" {return COST_OF_DEBT;}
"cost_of_equity" {return COST_OF_EQUITY;}
"valuation" {return VALUATION;}
"npv" {return NPV;}
"irr" {return IRR;}
"wacc" {return WACC;}
"print" {return PRINT;}
"var" {return VAR;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"for" {return FOR;}
"int" {yylval.id=_strdup(yytext);return IDENTIFIER;}
"bool" {yylval.id=_strdup(yytext);return IDENTIFIER;}
"string" {yylval.id=_strdup(yytext);return IDENTIFIER;}
"true" {yylval.num=1;return BOOL_LITERAL;}
"false" {yylval.num=0;return BOOL_LITERAL;}
{ID} {yylval.id=_strdup(yytext);return IDENTIFIER;}
{NUMBER} {yylval.num=atof(yytext);return NUMBER;}
{DATE} {yylval.str=_strdup(yytext);return DATE;}
{STRING} {yylval.str=_strdup(yytext);return STRING;}
"==" {return EQ;}
"!=" {return NE;}
">=" {return GE;}
"<=" {return LE;}
">" {return GT;}
"<" {return LT;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"=" {return ASSIGN;}
":" {return COLON;}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
";" {return SEMICOLON;}
"," {return COMMA;}
"(" {return LPAREN;}
")" {return RPAREN;}
"{" {return LBRACE;}
"}" {return RBRACE;}
"[" {return LBRACKET;}
"]" {return RBRACKET;}
. {fprintf(stderr,"Erro léxico na linha %d: '%s'\n",yylineno,yytext);}
%%
