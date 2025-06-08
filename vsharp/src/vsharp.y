%code requires {#include "ast.h"}
%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
int yylex(void);
extern int yylineno;
void yyerror(const char *s);
Node *program_root;
%}
%define parse.error verbose
%union {double num;char *id;char *str;Node *node;}

%token <id>  IDENTIFIER
%token <num> NUMBER
%token <str> STRING
%token <str> DATE
%token <num> BOOL_LITERAL

%token ENTITY CAP_TABLE DEAL DEBT_INSTRUMENT
%token COST_OF_DEBT COST_OF_EQUITY VALUATION
%token PRINT VAR IF ELSE WHILE FOR
%token NPV IRR WACC

%token EQ NE GT LT GE LE AND OR NOT ASSIGN
%token SEMICOLON COMMA COLON
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

%left  OR
%left  AND
%nonassoc EQ NE GT LT GE LE
%right ASSIGN
%left  '+' '-'
%left  '*' '/'
%right NOT UMINUS

/* ——— tipos associados ——— */
%type <node> program statement statement_list block
%type <node> var_decl entity_decl cap_table_decl cap_item cap_item_list
%type <node> deal_decl debt_decl cost_debt_decl cost_equity_decl valuation_decl
%type <node> metric_call print_stmt if_stmt while_stmt for_stmt
%type <node> expression expression_opt for_init
%type <node> array_lit expr_list expr_list_opt date_lit
%type <node> arg_list arg_list_opt print_args

%start program
%%                              /* ——— GRAMMAR ——— */
program
    :                           { program_root = new_block(); }
    | program statement         { block_add(program_root,$2); }
    ;

block
    : LBRACE RBRACE             { $$ = new_block(); }
    | LBRACE statement_list RBRACE { $$ = $2; }
    ;

statement_list
    : statement                 { $$ = new_block(); block_add($$,$1); }
    | statement_list statement  { block_add($1,$2); $$ = $1; }
    ;

/* —— statements top-level —— */
statement
    : var_decl  SEMICOLON                       { $$ = $1; }
    | entity_decl                               { $$ = $1; }
    | cap_table_decl                            { $$ = $1; }
    | deal_decl                                 { $$ = $1; }
    | debt_decl                                 { $$ = $1; }
    | cost_debt_decl                            { $$ = $1; }
    | cost_equity_decl                          { $$ = $1; }
    | valuation_decl                            { $$ = $1; }
    | metric_call SEMICOLON                     { $$ = $1; }
    | print_stmt SEMICOLON                      { $$ = $1; }
    | IDENTIFIER block                          { $$ = new_nop(); }
    | expression SEMICOLON                      { $$ = $1; }
    | if_stmt                                   { $$ = $1; }
    | while_stmt                                { $$ = $1; }
    | for_stmt                                  { $$ = $1; }
    | block                                     { $$ = $1; }
    ;

/* —— var —— */
var_decl
    : VAR IDENTIFIER                            { $$ = new_vardecl($2,NULL); }
    | VAR IDENTIFIER ASSIGN expression          { $$ = new_vardecl($2,$4); }
    ;

/* —— entity —— (NOP) */
entity_decl      : ENTITY IDENTIFIER block                          { $$ = new_nop(); };

/* —— cap_table ——  */
cap_table_decl
    : CAP_TABLE IDENTIFIER LBRACE cap_item_list RBRACE              { $$ = new_nop(); }
    ;

cap_item_list
    : cap_item
    | cap_item_list cap_item
    ;

cap_item          : IDENTIFIER block                                { $$ = new_nop(); };

/* —— outros blocos de domínio (NOP) —— */
deal_decl         : DEAL IDENTIFIER block                           { $$ = new_nop(); };
debt_decl         : DEBT_INSTRUMENT IDENTIFIER block                { $$ = new_nop(); };
cost_debt_decl    : COST_OF_DEBT IDENTIFIER block                   { $$ = new_nop(); };
cost_equity_decl  : COST_OF_EQUITY IDENTIFIER block                 { $$ = new_nop(); };
valuation_decl    : VALUATION IDENTIFIER block                      { $$ = new_nop(); };

/* —— métricas financeiras —— */
metric_call
    : NPV  LPAREN arg_list_opt RPAREN   { $$ = new_call(new_ident("npv"), $3->v.array.elems, $3->v.array.count); }
    | IRR  LPAREN arg_list_opt RPAREN   { $$ = new_call(new_ident("irr"), $3->v.array.elems, $3->v.array.count); }
    | WACC LPAREN arg_list_opt RPAREN   { $$ = new_call(new_ident("wacc"),$3->v.array.elems, $3->v.array.count); }
    ;

/* —— print variádico —— */
print_stmt : PRINT LPAREN print_args RPAREN           { $$ = $3; };
print_args
    : expression                                      { $$ = new_print($1); }
    | print_args COMMA expression                     { print_add($1,$3); $$ = $1; }
    ;

/* —— controle de fluxo —— */
if_stmt
    : IF LPAREN expression RPAREN statement                          { $$ = new_if($3,$5,new_nop()); }
    | IF LPAREN expression RPAREN statement ELSE statement           { $$ = new_if($3,$5,$7); }
    ;

while_stmt        : WHILE LPAREN expression RPAREN statement         { $$ = new_while($3,$5); };
for_stmt
    : FOR LPAREN for_init SEMICOLON expression_opt SEMICOLON expression_opt RPAREN statement
        { $$ = new_for($3,$5,$7,$9); }
    ;

for_init          : var_decl        { $$ = $1; }
                  | expression      { $$ = $1; }
                  |                 { $$ = new_nop(); }
                  ;

expression_opt    : expression      { $$ = $1; }
                  |                 { $$ = new_nop(); }
                  ;

/* —— EXPRESSÕES —— */
expression
    : expression '+' expression                     { $$ = new_bin('+',$1,$3); }
    | expression '-' expression                     { $$ = new_bin('-',$1,$3); }
    | expression '*' expression                     { $$ = new_bin('*',$1,$3); }
    | expression '/' expression                     { $$ = new_bin('/',$1,$3); }
    | expression EQ expression                      { $$ = new_bin(EQ,$1,$3); }
    | expression NE expression                      { $$ = new_bin(NE,$1,$3); }
    | expression GT expression                      { $$ = new_bin(GT,$1,$3); }
    | expression LT expression                      { $$ = new_bin(LT,$1,$3); }
    | expression GE expression                      { $$ = new_bin(GE,$1,$3); }
    | expression LE expression                      { $$ = new_bin(LE,$1,$3); }
    | expression AND expression                     { $$ = new_bin(AND,$1,$3); }
    | expression OR  expression                     { $$ = new_bin(OR,$1,$3); }
    | IDENTIFIER ASSIGN expression                  { $$ = new_assign($1,$3); }
    | NOT expression                                { $$ = new_un(NOT,$2); }
    | '-' expression %prec UMINUS                   { $$ = new_un('-', $2); }
    | LPAREN expression RPAREN                      { $$ = $2; }
    | NUMBER {
        /* se tem parte fracionária, vira NODE_FLOAT; senão NODE_NUM */
        long as_int = (long)$1;
        if ( (double)as_int == $1 )
            $$ = new_num  (as_int);   /* 42 -> int  */
        else
            $$ = new_float($1);       /* 3.14, 0.05 */
      }
    | BOOL_LITERAL                                  { $$ = new_bool((int)$1); }
    | STRING                                        { $$ = new_str($1); }
    | date_lit                                      { $$ = $1; }
    | array_lit                                     { $$ = $1; }
    | IDENTIFIER                                    { $$ = new_ident($1); }
    | IDENTIFIER LPAREN arg_list_opt RPAREN         { $$ = new_call(new_ident($1),$3->v.array.elems,$3->v.array.count); }
    | metric_call                                   { $$ = $1; }
    | STRING COLON expression                       { $$ = new_pair($1,$3); }
    ;

/* —— literal ARRAY —— */
array_lit        : LBRACKET expr_list_opt RBRACKET                 { $$ = $2; };
expr_list_opt    :                                                { $$ = new_array(NULL,0); }
                 | expr_list;
expr_list        : expression                                     { $$ = new_array_one($1); }
                 | expr_list COMMA expression                     { array_append($1,$3); $$ = $1; };

/* —— literal DATE —— */
date_lit         : DATE                                           { $$ = new_date($1); };

/* —— lista de argumentos —— */
arg_list_opt     :                                                { $$ = new_array(NULL,0); }
                 | arg_list;
arg_list         : expression                                     { $$ = new_array_one($1); }
                 | arg_list COMMA expression                      { array_append($1,$3); $$ = $1; };


%%
void yyerror(const char *s){fprintf(stderr,"Erro de sintaxe na linha %d: %s\n",yylineno,s);}
