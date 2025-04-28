(* Comentários *)
<comment>          ::= "//" { any_char_except_newline } <newline>
                    | "/*" { any_char } "*/"

(* Programa *)
<program>          ::= { <statement> }

(* Declarações e Statements *)
<statement>        ::= <entity_decl>
                    | <cap_table_decl>
                    | <equity_deal_decl>
                    | <debt_decl>
                    | <cost_debt_decl>
                    | <cost_equity_decl>
                    | <optimize_wacc_decl>
                    | <optimize_structure_decl>
                    | <scenario_decl>
                    | <valuation_decl>
                    | <metric_decl>
                    | <report_decl>
                    | <import_decl>
                    | <export_decl>
                    | <expr_stmt>
                    | <comment>

<expr_stmt>       ::= <expression> ";" <newline>

(* Entidade e Classes de Ações *)
<entity_decl>      ::= "entity" <ident> <block_entity>
<block_entity>     ::= "{" <newline>
                         "legal_name" "=" <string> ";" <newline>
                         "jurisdiction" "=" <ident> ";" <newline>
                         "share_classes" <block_share_classes>
                       "}"
<block_share_classes> ::= "{" <newline> { <share_class_decl> } "}"
<share_class_decl> ::= <ident> <block_share_class_body>
<block_share_class_body> ::= "{" <newline>
                              "votes_per_share" "=" <number> ";" <newline>
                              "dividend_pref" "=" <number> ";" <newline>
                            "}"

(* Tabela de Capitalização *)
<cap_table_decl>   ::= "cap_table" <ident> <block_cap_table>
<block_cap_table>  ::= "{" <newline> { <cap_section> } "}"
<cap_section>      ::= <ident> "{" <newline>
                         "holders" "=" "[" <holder_list> "]" ";" <newline>
                       "}"
<holder_list>      ::= <holder> { "," <holder> }
<holder>           ::= <string> ":" <number>

(* Ofertas de Equity *)
<equity_deal_decl> ::= "deal" <ident> <block_equity_deal>
<block_equity_deal>::= "{" <newline>
                         "type" "=" "Equity" ";" <newline>
                         "issuer" "=" <ident> ";" <newline>
                         "amount" "=" <number> ";" <newline>
                         "price_per_share" "=" <number> ";" <newline>
                         "settlement_date" "=" <date> ";" <newline>
                         "underwriters" "=" "[" <string_list> "]" ";" <newline>
                       "}"

(* Instrumentos de Dívida *)
<debt_decl>        ::= "debt_instrument" <ident> <block_debt>
<block_debt>       ::= "{" <newline>
                         "issuer" "=" <ident> ";" <newline>
                         "principal" "=" <number> ";" <newline>
                         "coupon_rate" "=" <number> ";" <newline>
                         "maturity" "=" <date> ";" <newline>
                         "payment_freq" "=" <ident> ";" <newline>
                       "}"

(* Custo de Dívida e Capital *)
<cost_debt_decl>   ::= "cost_of_debt" <ident> <block_cost_debt>
<block_cost_debt>  ::= "{" <newline>
                         "rating" "=" <string> ";" <newline>
                         "spread" "=" <number> ";" <newline>
                         "maturity" "=" <date> ";" <newline>
                       "}"
<cost_equity_decl> ::= "cost_of_equity" <ident> <block_cost_equity>
<block_cost_equity>::= "{" <newline>
                         "beta" "=" <number> ";" <newline>
                         "rf" "=" <number> ";" <newline>
                         "rm" "=" <number> ";" <newline>
                       "}"

(* Otimização de WACC e Estrutura *)
<optimize_wacc_decl>      ::= "optimize_wacc" <ident> <block_opt>
<optimize_structure_decl> ::= "optimize_structure" <ident> <block_opt>
<block_opt>        ::= "{" <newline>
                         "variables" <block_vars>
                         "constraints" <block_constraints>
                         "objective" <opt_expr> ";" <newline>
                         [ "solver" <ident> ";" <newline> ]
                       "}"
<block_vars>       ::= "{" <newline> { <var_decl> } "}"
<block_constraints>::= "{" <newline> { <expr_stmt> } "}"
<var_decl>         ::= <ident> "in" "[" <number> "," <number> "]" ";" <newline>
                    | <ident> "=" <expression> ";" <newline>

(* Cenários de Sensibilidade *)
<scenario_decl>    ::= "scenario" <ident> <block_scenario>
<block_scenario>   ::= "{" <newline> { <expr_stmt> } "}"

(* Valuation *)
<valuation_decl>   ::= "valuation" <ident> <block_valuation>
<block_valuation>  ::= "{" <newline>
                         "cashflows" "=" "[" <number_list> "]" ";" <newline>
                         "rate" "=" <expression> ";" <newline>
                         "result" "=" <ident_call> ";" <newline>
                       "}"

(* Métricas Financeiras *)
<metric_decl>      ::= <ident> "=" <metric_call> ";" <newline>
<metric_call>      ::= "npv" "(" <arg_list> ")"
                    | "irr" "(" <arg_list> ")"
                    | "wacc" "(" <arg_list> ")"
                    | "capm" "(" <arg_list> ")"
                    | "interest_coverage" "(" <arg_list> ")"
                    | "dscr" "(" <arg_list> ")"
                    | "ev_ebitda" "(" <arg_list> ")"
                    | "p_to_e" "(" <arg_list> ")"
                    | "de_ratio" "(" <arg_list> ")"

(* Relatórios *)
<report_decl>      ::= "report" <ident> <block_report>
<block_report>     ::= "{" <newline> { <print_stmt> } "}"
<print_stmt>       ::= "print" "(" <print_args> ")" ";" <newline>
<print_args>       ::= <string> | <ident> | <expression>
                    { "," ( <string> | <ident> | <expression> ) }

(* Import/Export *)
<import_decl>      ::= "import" "csv" "(" <string> ")" ";" <newline>
<export_decl>      ::= "export" <ident> "to" ( "excel" | "pdf" )
                       "(" <string> ")" ";" <newline>

(* Expressões e Chamadas *)
<expression>       ::= <or_expr>
<or_expr>          ::= <and_expr> { "||" <and_expr> }
<and_expr>         ::= <cmp_expr> { "&&" <cmp_expr> }
<cmp_expr>         ::= <arith_expr> [ ( "==" | "!=" | ">" | "<" | ">=" | "<=" ) <arith_expr> ]
<arith_expr>       ::= <term> { ( "+" | "-" ) <term> }
<term>             ::= <factor> { ( "*" | "/" ) <factor> }
<factor>           ::= { "+" | "-" | "!" } ( <number> | <ident> | <ident_call> | "(" <expression> ")" )

<ident_call>       ::= <ident> "(" [ <arg_list> ] ")"
<arg_list>         ::= <expression> { "," <expression> }

<string_list>      ::= <string> { "," <string> }
<number_list>      ::= <number> { "," <number> }

(* Terminais *)
<ident>            ::= letter { letter | digit | "_" }
<number>           ::= digit { digit } [ "." digit { digit } ]
<string>           ::= "\"" { any_char_except_quote } "\""
<date>             ::= digit digit digit digit "-" digit digit "-" digit digit

<newline>          ::= "\n" | "\r\n"
letter             ::= "A" … "Z" | "a" … "z"
digit              ::= "0" … "9"
any_char_except_quote ::= qualquer caractere diferente de "\""
any_char           ::= qualquer caractere
