# Valuation# (V#) – Gramática EBNF

## Visão Geral
Um programa em V# é uma sequência de statements (declarações, expressões, relatórios etc.), podendo incluir comentários. Cada bloco ou declaração possui sua sintaxe própria, delimitada por chaves {} e finalizada por ponto-e-vírgula ; onde indicado.
* **Programa** : sequência de declarações e comandos.
* **Blocos** : delimitados por { … }.
* **Listas** : delimitadas por [ … ].
* **Términos**: cada instrução termina em ;.
* **Expressões**: suportam aritmética, comparações, chamadas de funções financeiras (npv, irr, wacc).

1. Estrutura do Programa
```ebnf
<program>   ::= { <statement> }
<statement> ::= 
      <entity_decl>         (* definição de entidade *)
    | <cap_table_decl>      (* cap table *)
    | <equity_deal_decl>    (* oferta de equity *)
    | <debt_decl>           (* instrumente de dívida *)
    | <cost_debt_decl>      (* custo de dívida *)
    | <cost_equity_decl>    (* custo de equity *)
    | <valuation_decl>      (* valuation NPV/IRR/WACC *)
    | <metric_decl>         (* métricas financeiras *)
    | <print_stmt>          (* comando de impressão *)

<var_decl> ::= "var" <ident> [ "=" <expression> ] ";"
<if_stmt>  ::= "if" "(" <expression> ")" <block> [ "else" <block> ]
<block>    ::= "{" { <statement> } "}"
<while_stmt> ::= "while" "(" <expression> ")" <block>
<for_stmt> ::= "for" "(" [ <var_decl> | <expr_stmt> ] [ <expression> ] ";" [ <expression> ] ")" <block>
```

2. Declaração de Entidades
- Cada `entity` define o nome jurídico, jurisdição e classes de ações:
```ebnf
<entity_decl>   ::= "entity" <ident> "{" <entity_body> "}"
<entity_body>   ::= 
      "legal_name" "=" <string> ";" 
    | "jurisdiction" "=" <ident> ";" 
    | "share_classes" "{" { <share_class> } "}"
<share_class>   ::= <ident> "{" 
                       "votes_per_share" "=" <number> ";" 
                       "dividend_pref"    "=" <number> ";" 
                   "}"

```
* **legal_name**: nome completo da empresa.
* **jurisdiction**: país ou código (ex: “BR”).
* **share_classes**: cada classe indica votos e preferência de dividendos.

3. Tabela de Capitalização
- Lista quantidades por holder em cada classe de ações:
```ebnf
<cap_table_decl> ::= "cap_table" <ident> "{" { <cap_section> } "}"
<cap_section>    ::= <ident> "{" 
                         "holders" "=" "[" <holder_list> "]" ";" 
                     "}"
<holder_list>    ::= <holder> { "," <holder> }
<holder>         ::= <string> ":" <number>
```
* <**ident**>: nome da classe (ex: common, preferred).
* **holders**: lista de pares "Nome": quantidade.


4. Ofertas de Equity & Dívida
- *Equity* :
```ebnf
<equity_deal_decl> ::= "deal" <ident> "{" 
                         "type"            "=" "Equity" ";" 
                         "issuer"          "=" <ident> ";" 
                         "amount"          "=" <number> ";" 
                         "price_per_share" "=" <number> ";" 
                         "settlement_date" "=" <date> ";" 
                         "underwriters"    "=" "[" <string_list> "]" ";" 
                     "}"
```
- *Dívida*:
```ebnf
<debt_decl> ::= "debt_instrument" <ident> "{" 
                   "issuer"       "=" <ident> ";" 
                   "principal"    "=" <number> ";" 
                   "coupon_rate"  "=" <number> ";" 
                   "maturity"     "=" <date> ";" 
                   "payment_freq" "=" <ident> ";" 
               "}"
```
* **underwriters**: lista de bancos coordenadores.
* **payment_freq**: por ex. annual, semiannual.

5. Custos de Capital
```ebnf
<cost_debt_decl>   ::= "cost_of_debt" <ident> "{" 
                         "rating"   "=" <string> ";" 
                         "spread"   "=" <number> ";" 
                         "maturity" "=" <date> ";" 
                     "}"
<cost_equity_decl> ::= "cost_of_equity" <ident> "{" 
                         "beta" "=" <number> ";" 
                         "rf"   "=" <number> ";" 
                         "rm"   "=" <number> ";" 
                     "}"
```
* **CAPM**: usa beta, rf (risk-free), rm (market return).
* **Debt**: rating e spread para calcular custo efetivo.

6. Valuation
- Define fluxos de caixa e calcula resultados via funções financeiras:
```ebnf
<valuation_decl> ::= "valuation" <ident> "{" 
                        "cashflows" "=" "[" <number_list> "]" ";" 
                        "rate"      "=" <expression> ";" 
                        "result"    "=" <ident_call> ";" 
                    "}"
```
* **cashflows**: lista de valores (negativos para investimento).
* **result**: chamada típica npv(rate, cashflows).

7. Métricas Financeiras
```ebnf
<metric_decl>  ::= <ident> "=" <metric_call> ";"
<metric_call>  ::= "npv" "(" <arg_list> ")" 
                | "irr" "(" <arg_list> ")" 
                | "wacc" "(" <arg_list> ")"
```
* **npv**: valor presente líquido.
* **irr**: taxa interna de retorno.
* **wacc**: custo médio ponderado de capital.

8. Impressão
```ebnf
<print_stmt> ::= "print" "(" <expression> ")" ";"
```
* Exibe qualquer expressão no console.

9. Expressões
```ebnf
<expression> ::= <or_expr>
<or_expr>    ::= <and_expr> { "||" <and_expr> }
<and_expr>   ::= <cmp_expr> { "&&" <cmp_expr> }
<cmp_expr>   ::= <arith_expr> [ ( "==" | "!=" | ">" | "<" | ">=" | "<=" ) <arith_expr> ]
<arith_expr> ::= <term> { ( "+" | "-" ) <term> }
<term>       ::= <factor> { ( "*" | "/" ) <factor> }
<factor>     ::= { "+" | "-" | "!" } ( 
                   <number> 
                 | <ident> 
                 | <ident_call> 
                 | "(" <expression> ")" 
               )
```
* **precedência**: unários > *// > +/- > comparações > booleanos.

10. Chamadas e Listas
```ebnf
<ident_call>   ::= <ident> "(" [ <arg_list> ] ")"
<arg_list>     ::= <expression> { "," <expression> }
<string_list>  ::= <string> { "," <string> }
<number_list>  ::= <number> { "," <number> }
```

11. Terminais
```ebnf
<ident>      ::= letter { letter | digit | "_" }
<number>     ::= digit { digit } [ "." digit { digit } ]
<string>     ::= "\"" { any_char_except_quote } "\""
<date>       ::= digit digit digit digit "-" digit digit "-" digit digit
<newline>    ::= "\n" | "\r\n"
letter       ::= "A"… "Z" | "a"… "z"
digit        ::= "0"… "9"
```

## Exemplo de Script da Linguagem:
```bash
// Exemplo de script V# com comentários explicativos

// 1. Definição de entidade e classes de ações
entity MyCorp {
  legal_name    = "My Corporate S.A.";  // Nome jurídico completo da empresa
  jurisdiction  = BR;                   // Código do país/jurisdição
  share_classes {
    common {
      votes_per_share = 1;              // Votos por ação da classe comum
      dividend_pref   = 0;              // Preferência de dividendos (0 = sem preferência)
    }
    preferred {
      votes_per_share = 0;              // Classe preferencial sem direito a voto
      dividend_pref   = 0.08;           // 8% de preferência ao receber dividendos
    }
  }
}

// 2. Definição da tabela de capitalização (cap table)
cap_table MyCorp {
  common {
    holders = ["Alice": 5000000, "Bob": 3000000];  // Quantidades de ações ordinárias
  }
  preferred {
    holders = ["FIPX": 2000000];                   // Quantidades de ações preferenciais
  }
}

// 3. Ofertas de Equity e Dívida
deal IPO1 {
  type             = Equity;              // Tipo da oferta
  issuer           = MyCorp;              // Entidade emissora
  amount           = 100000000;           // Montante total da oferta
  price_per_share  = 10.0;                // Preço por ação
  settlement_date  = 2025-06-15;          // Data de liquidação
  underwriters     = ["BankA", "BankB"];  // Coordenadores da oferta
}

debt_instrument Bond2025 {
  issuer       = MyCorp;                  // Entidade emissora da dívida
  principal    = 200000000;               // Valor principal emitido
  coupon_rate  = 0.075;                   // Taxa de cupom anual (7.5%)
  maturity     = 2030-05-01;              // Data de vencimento
  payment_freq = semiannual;              // Frequência de pagamentos
}

// 4. Cálculo de métricas financeiras
npv1  = npv(0.10, [-100000000, 30000000, 35000000, 40000000]);  // NPV com taxa de 10%
irr1  = irr([-100000000, 30000000, 35000000, 40000000]);        // IRR do fluxo de caixa
wacc1 = wacc(400000000, 200000000, 0.10, 0.075);                // WACC com equity/debt e custos

// 5. Impressão dos resultados no console
print(npv1);  // Exibe o valor presente líquido
print(irr1);  // Exibe a taxa interna de retorno
print(wacc1); // Exibe o custo médio ponderado de capital
```
* **O que o script faz**:
  - Define uma entidade MyCorp com suas classes de ações.
  - Monta a capitalização em cap_table.
  - Registra uma oferta de equity (deal IPO1) e um instrumento de dívida (Bond2025
  - Calcula NPV, IRR e WACC usando listas de fluxos de caixa e parâmetros estáticos
  - Exibe os resultados no console com print().
