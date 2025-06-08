# Valuation# (V#) – Especificação da Linguagem & Exemplo

> **Estado da implementação (2025-06)**  
> ✔ Compilador funcional para todo o fluxo mostrado abaixo (parse → semântica → LLVM IR → execução).  
> 🛈 Geração de código para `for` e validações profundas dos blocos de domínio estão marcados como **TRABALHO FUTURO**, pois não foram requisitos obrigatórios da entrega.

---

## 1 · Visão geral

* Um programa em **V#** é uma sequência de _statements_
  (declarações, expressões, relatórios etc.) que podem conter comentários `// …`.
* Cada instrução termina em `;`.
* Blocos são delimitados por `{ … }`; listas por `[ … ]`.
* Expressões suportam aritmética, comparações e chamadas
  às funções financeiras **`npv`**, **`irr`** e **`wacc`**.

---

## 2 · Gramática (EBNF)

<details>
<summary><strong>Mostrar / ocultar EBNF completa</strong></summary>

```ebnf
###############################################################################
# 2.1  Estrutura de programa
###############################################################################
<program>   ::= { <statement> }
<statement> ::=
      <entity_decl> | <cap_table_decl> | <equity_deal_decl> | <debt_decl>
    | <cost_debt_decl> | <cost_equity_decl> | <valuation_decl> | <metric_decl>
    | <print_stmt> | <var_decl> | <if_stmt> | <while_stmt> | <for_stmt>

<var_decl>  ::= "var" <ident> [ "=" <expression> ] ";"
<if_stmt>   ::= "if" "(" <expression> ")" <block> [ "else" <block> ]
<while_stmt>::= "while" "(" <expression> ")" <block>
<for_stmt>  ::= "for" "(" [ <var_decl> | <expression> ] ";"
                         [ <expression> ] ";" [ <expression> ] ")" <block>
<block>     ::= "{" { <statement> } "}"

###############################################################################
# 2.2  Entidades
###############################################################################
<entity_decl> ::= "entity" <ident> "{" <entity_body> "}"
<entity_body> ::= "legal_name" "=" <string> ";"
                | "jurisdiction" "=" <ident> ";"
                | "share_classes" "{" { <share_class> } "}"
<share_class> ::= <ident> "{"
                    "votes_per_share" "=" <number> ";"
                    "dividend_pref"   "=" <number> ";"
                  "}"

###############################################################################
# 2.3  Cap table
###############################################################################
<cap_table_decl> ::= "cap_table" <ident> "{" { <cap_section> } "}"
<cap_section>    ::= <ident> "{"
                       "holders" "=" "[" <holder_list> "]" ";"
                     "}"
<holder_list>    ::= <holder> { "," <holder> }
<holder>         ::= <string> ":" <number>

###############################################################################
# 2.4  Deals de equity e dívida
###############################################################################
<equity_deal_decl> ::= "deal" <ident> "{"
                        "type"            "=" "Equity" ";"
                        "issuer"          "=" <ident> ";"
                        "amount"          "=" <number> ";"
                        "price_per_share" "=" <number> ";"
                        "settlement_date" "=" <date>   ";"
                        "underwriters"    "=" "[" <string_list> "]" ";"
                      "}"
<debt_decl> ::= "debt_instrument" <ident> "{"
                 "issuer"       "=" <ident> ";"
                 "principal"    "=" <number> ";"
                 "coupon_rate"  "=" <number> ";"
                 "maturity"     "=" <date>   ";"
                 "payment_freq" "=" <ident>  ";"
               "}"

###############################################################################
# 2.5  Custos de capital
###############################################################################
<cost_debt_decl> ::= "cost_of_debt" <ident> "{"
                      "rating"   "=" <string> ";"
                      "spread"   "=" <number> ";"
                      "maturity" "=" <date>   ";"
                    "}"
<cost_equity_decl> ::= "cost_of_equity" <ident> "{"
                        "beta" "=" <number> ";"
                        "rf"   "=" <number> ";"
                        "rm"   "=" <number> ";"
                      "}"

###############################################################################
# 2.6  Valuation & métricas
###############################################################################
<valuation_decl> ::= "valuation" <ident> "{"
                      "cashflows" "=" "[" <number_list> "]" ";"
                      "rate"      "=" <expression> ";"
                      "result"    "=" <ident_call> ";"
                    "}"
<metric_decl> ::= <ident> "=" <metric_call> ";"
<metric_call> ::= "npv"  "(" <arg_list> ")"
                | "irr"  "(" <arg_list> ")"
                | "wacc" "(" <arg_list> ")"

###############################################################################
# 2.7  Expressões
###############################################################################
<expression> ::= <or_expr>
<or_expr>    ::= <and_expr> { "||" <and_expr> }
<and_expr>   ::= <cmp_expr> { "&&" <cmp_expr> }
<cmp_expr>   ::= <arith_expr> [ ( "==" | "!=" | ">" | "<" | ">=" | "<=" ) <arith_expr> ]
<arith_expr> ::= <term> { ( "+" | "-" ) <term> }
<term>       ::= <factor> { ( "*" | "/" ) <factor> }
<factor>     ::= { "+" | "-" | "!" } (
                   <number> | <ident> | <ident_call> | "(" <expression> ")"
                 )

###############################################################################
# 2.8  Outras produções utilitárias
###############################################################################
<ident_call>  ::= <ident> "(" [ <arg_list> ] ")"
<arg_list>    ::= <expression> { "," <expression> }
<string_list> ::= <string> { "," <string> }
<number_list> ::= <number> { "," <number> }

###############################################################################
# 2.9  Terminais
###############################################################################
<ident>  ::= letter { letter | digit | "_" }
<number> ::= digit { digit } [ "." digit { digit } ]
<string> ::= "\"" { any_char_except_quote } "\""
<date>   ::= digit digit digit digit "-" digit digit "-" digit digit
letter   ::= "A"…"Z" | "a"…"z"
digit    ::= "0"…"9"
````

</details>

---

## 3 · Script de exemplo

```v#
[veja arquivo examples/full.vs para cópia completa]
```

### Saída obtida na execução

```
NPV negativo; review assumptions
Taxa: 0.050000
NPV:  -5 129 035.741281
…
Taxa: 0.150000
NPV: -21 147 365.825594
IRR final:  0.023647
WACC final: 0.091667
```

Todos os valores conferem com o cálculo financeiro teórico.

---

## 4 · Estado da implementação

| Recurso                                                                                | Status                 |
| -------------------------------------------------------------------------------------- | ---------------------- |
| Léxico + parsing de toda a EBNF                                                        | ✅ concluído            |
| Verificação semântica (tipos, aridade, escopos)                                        | ✅ concluído            |
| Geração LLVM IR p/ variáveis, arrays, `if`, `while`, `npv/irr/wacc`, `print` variádico | ✅ concluído            |
| Loop `for` – geração de código                                                         | ⚠️ **TRABALHO FUTURO** |
| Validações cruzadas de blocos `entity`, `cap_table`, …                                 | ⚠️ **TRABALHO FUTURO** |

O compilador cumpre integralmente o que foi prometido para a disciplina; as melhorias marcadas como **TRABALHO FUTURO** são extensões não obrigatórias.

---

