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
// Exemplo de script V# com variáveis genéricas, condicionais e laços

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
  type             = Equity;              
  issuer           = MyCorp;              
  amount           = 100000000;           
  price_per_share  = 10.0;                
  settlement_date  = 2025-06-15;          
  underwriters     = ["BankA", "BankB"];  
}

debt_instrument Bond2025 {
  issuer       = MyCorp;                  
  principal    = 200000000;               
  coupon_rate  = 0.075;                   
  maturity     = 2030-05-01;              
  payment_freq = semiannual;              
}

// 4. Declaração de variáveis genéricas
var npv1  = npv(0.10, [-100000000, 30000000, 35000000, 40000000]);  // NPV com taxa de 10%
var irr1  = irr([-100000000, 30000000, 35000000, 40000000]);        // IRR do fluxo de caixa
var wacc1 = wacc(400000000, 200000000, 0.10, 0.075);                // WACC com equity/debt e custos

// 5. Condicional: avaliar se o NPV é positivo
if (npv1 > 0) {
  print("NPV positivo; proceed with deal");  
} else {
  print("NPV negativo; review assumptions");  
}

// 6. Loop while: simular NPV para diferentes taxas de desconto
var rate = 0.05;                          // taxa inicial de 5%
while (rate <= 0.15) {                    // até 15%
  var npv_loop = npv(rate, [-100000000, 30000000, 35000000, 40000000]);
  print("Taxa:", rate);                  // exibe a taxa corrente
  print("NPV:", npv_loop);               // exibe o NPV calculado
  rate = rate + 0.01;                    // incremento de 1 ponto percentual
}

// 7. Impressão final de métricas
print("IRR final:", irr1);               
print("WACC final:", wacc1);             
```
* **O que o script faz**:
  - Declara a entidade MyCorp e sua cap table.
  - Registra uma oferta de equity (IPO1) e um título de dívida (Bond2025).
  - Calcula npv1, irr1 e wacc1.
  - Usa var para armazenar resultados e um if para checar o sinal do NPV.
  - Executa um while para simular NPV em taxas de 5% até 15%.
  - Imprime no console todas as métricas finais.
