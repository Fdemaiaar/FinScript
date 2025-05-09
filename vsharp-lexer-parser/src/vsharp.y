/* Bison grammar para V# */

%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex(void);
void yyerror(const char *s);
%}

%union {
    double num;
    char *id;
    char *str;
}

%token <id>    IDENTIFIER
%token <num>   NUMBER
%token <str>   STRING

%token ENTITY CAP_TABLE DEAL DEBT_INSTRUMENT COST_OF_DEBT COST_OF_EQUITY VALUATION
%token PRINT IF ELSE WHILE FOR VAR NPV IRR WACC

%token EQ NEQ GE LE
%left "||"
%left "&&"
%nonassoc EQ NEQ
%nonassoc '>' '<' GE LE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '!'

%%

program:
    /* vazio */
  | program statement
  ;

statement:
    entity_decl
  | cap_table_decl
  | equity_deal_decl
  | debt_decl
  | cost_debt_decl
  | cost_equity_decl
  | valuation_decl
  | metric_decl
  | print_stmt
  | var_decl
  | if_stmt
  | while_stmt
  | for_stmt
  ;

entity_decl:
    ENTITY IDENTIFIER '{' entity_body_list '}'
  ;

entity_body_list:
    /* vazio */
  | entity_body_list entity_body
  ;

entity_body:
    "legal_name"    '=' STRING   ';'
  | "jurisdiction"  '=' IDENTIFIER ';'
  | "share_classes" '{' share_class_list '}'
  ;

share_class_list:
    /* vazio */
  | share_class_list share_class
  ;

share_class:
    IDENTIFIER '{'
      "votes_per_share" '=' NUMBER  ';'
      "dividend_pref"    '=' NUMBER  ';'
    '}'
  ;

cap_table_decl:
    CAP_TABLE IDENTIFIER '{' cap_section_list '}'
  ;

cap_section_list:
    /* vazio */
  | cap_section_list cap_section
  ;

cap_section:
    IDENTIFIER '{'
      "holders" '=' '[' holder_list ']' ';'
    '}'
  ;

holder_list:
    holder
  | holder_list ',' holder
  ;

holder:
    STRING ':' NUMBER
  ;

equity_deal_decl:
    DEAL IDENTIFIER '{'
      "type"            '=' "Equity" ';'
      "issuer"          '=' IDENTIFIER ';'
      "amount"          '=' NUMBER ';'
      "price_per_share" '=' NUMBER ';'
      "settlement_date" '=' STRING ';'
      "underwriters"    '=' '[' string_list ']' ';'
    '}'
  ;

string_list:
    STRING
  | string_list ',' STRING
  ;

debt_decl:
    DEBT_INSTRUMENT IDENTIFIER '{'
      "issuer"       '=' IDENTIFIER ';'
      "principal"    '=' NUMBER     ';'
      "coupon_rate"  '=' NUMBER     ';'
      "maturity"     '=' STRING     ';'
      "payment_freq" '=' IDENTIFIER ';'
    '}'
  ;

cost_debt_decl:
    COST_OF_DEBT IDENTIFIER '{'
      "rating"   '=' STRING ';'
      "spread"   '=' NUMBER ';'
      "maturity" '=' STRING ';'
    '}'
  ;

cost_equity_decl:
    COST_OF_EQUITY IDENTIFIER '{'
      "beta" '=' NUMBER ';'
      "rf"   '=' NUMBER ';'
      "rm"   '=' NUMBER ';'
    '}'
  ;

valuation_decl:
    VALUATION IDENTIFIER '{'
      "cashflows" '=' '[' number_list ']' ';'
      "rate"      '=' expression      ';'
      "result"    '=' IDENTIFIER '(' argument_list ')' ';'
    '}'
  ;

number_list:
    NUMBER
  | number_list ',' NUMBER
  ;

metric_decl:
    IDENTIFIER '=' IDENTIFIER '(' argument_list ')' ';'
  ;

argument_list:
    /* vazio */
  | arg_list
  ;

arg_list:
    expression
  | arg_list ',' expression
  ;

print_stmt:
    PRINT '(' expression ')' ';'
  ;

var_decl:
    VAR IDENTIFIER '=' expression ';'
  ;

if_stmt:
    IF '(' expression ')' statement %prec IF
  | IF '(' expression ')' statement ELSE statement
  ;

while_stmt:
    WHILE '(' expression ')' statement
  ;

for_stmt:
    FOR '(' for_init ';' expression ';' expression ')' statement
  ;

for_init:
    /* vazio */
  | VAR IDENTIFIER '=' expression ';'
  | expression
  ;

expression:
    expression "||" expression
  | expression "&&" expression
  | expression EQ expression
  | expression NEQ expression
  | expression '>' expression
  | expression '<' expression
  | expression GE expression
  | expression LE expression
  | expression '+' expression
  | expression '-' expression
  | expression '*' expression
  | expression '/' expression
  | expression '%' expression
  | '!' expression
  | '-' expression   %prec UMINUS
  | '(' expression ')'
  | NUMBER
  | IDENTIFIER
  ;

%%

int main(int argc, char **argv) {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}
