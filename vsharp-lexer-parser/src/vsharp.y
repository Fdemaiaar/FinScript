%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ast.h"

int yylex(void);
extern int yylineno;
void yyerror(const char*s);

Node *program_root;
%}

%define parse.error verbose
%union{double num;char *id;char *str;int bval;Node *node}

/* --- Tokens com valores --- */
%token<id>   IDENTIFIER
%token<num>  NUMBER
%token<str>  STRING
%token<num>  BOOL_LITERAL

/* --- Palavras-chave --- */
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

%type<node> program statement statement_list block var_decl entity_decl cap_table_decl deal_decl debt_decl cost_debt_decl cost_equity_decl valuation_decl metric_call print_stmt if_stmt while_stmt for_stmt expression expression_opt for_init arg_list arg_list_opt

%start program
%%

program
    : block                        { program_root = $1; }
    ;

block
    : LBRACE RBRACE                { $$ = new_block(); }
    | LBRACE statement_list RBRACE { $$ = $2;          }
    ;

statement_list
    : statement                    { $$ = new_block(); block_add($$, $1); }
    | statement_list statement     { block_add($1, $2); $$ = $1;          }
    ;

statement
    : var_decl SEMICOLON           { $$ = $1; }
    | entity_decl                  { $$ = $1; }
    | cap_table_decl               { $$ = $1; }
    | deal_decl                    { $$ = $1; }
    | debt_decl                    { $$ = $1; }
    | cost_debt_decl               { $$ = $1; }
    | cost_equity_decl             { $$ = $1; }
    | valuation_decl               { $$ = $1; }
    | metric_call SEMICOLON        { $$ = $1; }
    | print_stmt SEMICOLON         { $$ = $1; }
    | expression SEMICOLON         { $$ = $1; }
    | if_stmt                      { $$ = $1; }
    | while_stmt                   { $$ = $1; }
    | for_stmt                     { $$ = $1; }
    | block                        { $$ = $1; }
    ;

var_decl
    : VAR IDENTIFIER               { $$ = new_vardecl($2, NULL);                     }
    | VAR IDENTIFIER ASSIGN expression { $$ = new_vardecl($2, $4);                   }
    ;

/* Os demais decls ainda não geram semântica detalhada – retornam NOP */
entity_decl      : ENTITY IDENTIFIER block        { $$ = new_nop(); }
cap_table_decl   : CAP_TABLE IDENTIFIER block     { $$ = new_nop(); }
deal_decl        : DEAL IDENTIFIER block          { $$ = new_nop(); }
debt_decl        : DEBT_INSTRUMENT IDENTIFIER block { $$ = new_nop(); }
cost_debt_decl   : COST_OF_DEBT IDENTIFIER block  { $$ = new_nop(); }
cost_equity_decl : COST_OF_EQUITY IDENTIFIER block{ $$ = new_nop(); }
valuation_decl   : VALUATION IDENTIFIER block     { $$ = new_nop(); }

metric_call
    : NPV  LPAREN arg_list_opt RPAREN  { $$ = new_nop(); }
    | IRR  LPAREN arg_list_opt RPAREN  { $$ = new_nop(); }
    | WACC LPAREN arg_list_opt RPAREN  { $$ = new_nop(); }
    ;

print_stmt
    : PRINT LPAREN expression RPAREN   { $$ = new_print($3); }

if_stmt
    : IF LPAREN expression RPAREN statement              { $$ = new_nop(); }
    | IF LPAREN expression RPAREN statement ELSE statement { $$ = new_nop(); }
    ;

while_stmt
    : WHILE LPAREN expression RPAREN statement            { $$ = new_nop(); }
    ;

for_stmt
    : FOR LPAREN for_init SEMICOLON expression_opt SEMICOLON expression_opt RPAREN statement { $$ = new_nop(); }
    ;

for_init
    : var_decl
    | expression
    | /* vazio */                                    { $$ = new_nop(); }
    ;

expression_opt
    : expression
    | /* vazio */                                    { $$ = new_nop(); }
    ;

expression
    : expression '+' expression                      { $$ = new_bin('+', $1, $3); }
    | expression '-' expression                      { $$ = new_bin('-', $1, $3); }
    | expression '*' expression                      { $$ = new_bin('*', $1, $3); }
    | expression '/' expression                      { $$ = new_bin('/', $1, $3); }
    | expression EQ expression                       { $$ = new_bin(EQ,  $1, $3); }
    | expression NE expression                       { $$ = new_bin(NE,  $1, $3); }
    | expression GT expression                       { $$ = new_bin(GT,  $1, $3); }
    | expression LT expression                       { $$ = new_bin(LT,  $1, $3); }
    | expression GE expression                       { $$ = new_bin(GE,  $1, $3); }
    | expression LE expression                       { $$ = new_bin(LE,  $1, $3); }
    | expression AND expression                      { $$ = new_bin(AND, $1, $3); }
    | expression OR  expression                      { $$ = new_bin(OR,  $1, $3); }
    | IDENTIFIER ASSIGN expression                   { $$ = new_assign($1, $3); }
    | NOT expression                                 { $$ = new_un(NOT, $2); }
    | '-' expression %prec UMINUS                    { $$ = new_un('-', $2); }
    | LPAREN expression RPAREN                       { $$ = $2; }
    | NUMBER                                         { $$ = new_num($1); }
    | BOOL_LITERAL                                   { $$ = new_bool((int)$1); }
    | STRING                                         { $$ = new_str($1); }
    | IDENTIFIER                                     { $$ = new_ident($1); }
    | IDENTIFIER LPAREN arg_list_opt RPAREN          { $$ = new_nop(); }
    | metric_call                                    { $$ = $1; }
    ;

arg_list_opt
    : /* vazio */                                    { $$ = new_nop(); }
    | arg_list
    ;

arg_list
    : expression                                     { $$ = new_nop(); }
    | arg_list COMMA expression                      { $$ = new_nop(); }
    ;

%%

void yyerror(const char *s){
    fprintf(stderr,"Erro de sintaxe na linha %d: %s\n",yylineno,s);
}
