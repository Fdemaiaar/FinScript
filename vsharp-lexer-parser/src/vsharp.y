/* Bison parser para V# — src/vsharp.y */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
extern int yylineno;
void yyerror(const char *s);
%}

%define parse.error verbose

%union {
    double      num;
    char       *id;
    char       *str;
}

/* --- Tokens com valores --- */
%token <id>   IDENTIFIER
%token <num>  NUMBER
%token <str>  STRING
%token <num>  BOOL_LITERAL

/* --- Palavras‑chave --- */
%token ENTITY CAP_TABLE DEAL DEBT_INSTRUMENT
%token COST_OF_DEBT COST_OF_EQUITY VALUATION
%token PRINT VAR IF ELSE WHILE FOR
%token INT_TYPE BOOL_TYPE STRING_TYPE
%token NPV IRR WACC

/* --- Operadores / pontuação --- */
%token EQ NE GT LT GE LE AND OR NOT ASSIGN
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

/* Precedência */
%left OR
%left AND
%nonassoc EQ NE GT LT GE LE
%right ASSIGN
%left '+' '-'
%left '*' '/'
%right NOT UMINUS

%type <num> expression

%% /* ===================== GRAMMAR ===================== */

program
    : /* vazio */
    | program statement
    ;

/* ---------- bloco genérico ---------- */
block
    : LBRACE RBRACE
    | LBRACE statement_list RBRACE
    ;

statement_list
    : statement
    | statement_list statement
    ;

/* ---------- statements ---------- */
statement
    : var_decl SEMICOLON
    | entity_decl
    | cap_table_decl
    | deal_decl
    | debt_decl
    | cost_debt_decl
    | cost_equity_decl
    | valuation_decl
    | metric_call SEMICOLON        /* npv()/irr()/wacc() isolado */
    | print_stmt SEMICOLON
    | expression SEMICOLON
    | if_stmt
    | while_stmt
    | for_stmt
    | block
    | error SEMICOLON              { yyerror("statement inválido"); yyclearin; }
    ;

/* ---------- declarações ---------- */
var_decl
    : VAR IDENTIFIER ASSIGN expression
    | VAR IDENTIFIER
    ;

entity_decl        : ENTITY IDENTIFIER block ;
cap_table_decl     : CAP_TABLE IDENTIFIER block ;
deal_decl          : DEAL IDENTIFIER block ;
debt_decl          : DEBT_INSTRUMENT IDENTIFIER block ;
cost_debt_decl     : COST_OF_DEBT IDENTIFIER block ;
cost_equity_decl   : COST_OF_EQUITY IDENTIFIER block ;
valuation_decl     : VALUATION IDENTIFIER block ;

/* ---------- métricas ---------- */
metric_call
    : NPV   LPAREN arg_list_opt RPAREN
    | IRR   LPAREN arg_list_opt RPAREN
    | WACC  LPAREN arg_list_opt RPAREN
    ;

/* ---------- print ---------- */
print_stmt         : PRINT LPAREN expression RPAREN ;

/* ---------- controle de fluxo ---------- */
if_stmt
    : IF LPAREN expression RPAREN statement
    | IF LPAREN expression RPAREN statement ELSE statement
    ;

while_stmt
    : WHILE LPAREN expression RPAREN statement
    ;

for_stmt
    : FOR LPAREN for_init SEMICOLON expression_opt SEMICOLON expression_opt RPAREN statement
    ;

for_init
    : var_decl
    | expression
    | /* vazio */
    ;

expression_opt
    : expression
    | /* vazio */
    ;

/* ---------- expressão ---------- */
expression
    : expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression EQ expression
    | expression NE expression
    | expression GT expression
    | expression LT expression
    | expression GE expression
    | expression LE expression
    | expression AND expression
    | expression OR expression
    | IDENTIFIER ASSIGN expression         /* atribuição simples */
    | NOT expression
    | '-' expression %prec UMINUS
    | LPAREN expression RPAREN
    | NUMBER
    | BOOL_LITERAL
    | STRING
    | IDENTIFIER
    | IDENTIFIER LPAREN arg_list_opt RPAREN
    | metric_call
    ;

/* listas de argumentos */
arg_list_opt
    : /* vazio */
    | arg_list
    ;

arg_list
    : expression
    | arg_list COMMA expression
    ;

%% /* ===================== helpers ===================== */

void yyerror(const char *s)
{
    fprintf(stderr, "Erro de sintaxe na linha %d: %s\n", yylineno, s);
}
