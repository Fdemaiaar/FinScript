# Valuation# (V#)

Compilador didático que transforma scripts financeiros na linguagem **V#** em
LLVM-IR e executa _just-in-time_ com **`lli`**.

> **Estado atual (Jun 2025)** – O compilador cumpre tudo o que foi prometido
> na especificação original da disciplina. Funcionalidades marcadas como
> **TRABALHO FUTURO** são extensões opcionais.

---

## 1 · Visão rápida

* Gramática declarada em EBNF (sec. 2).  
* Léxico + parser (Bison/Flex), análise semântica, geração de LLVM-IR.  
* Funções financeiras embutidas: **npv**, **irr**, **wacc**  
  (implementadas em `src/runtime.c`).  
* _Print_ variádico, `if`/`while`, arrays heterogêneos.

---

## 2 · EBNF completa

<details>
<summary>Clique para expandir a gramática</summary>

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
```
</details>

---

## 3 · Exemplo completo (`examples/full.vs`)

<details>
<summary>Script e saída esperada</summary>

```v#
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
````

### Execução típica

```
NPV negativo; review assumptions
Taxa: 0.050000
NPV:  -5129035.741281
⋯
Taxa: 0.150000
NPV: -21147365.825594
IRR final:  0.023647
WACC final: 0.091667
```

</details>

---

## 4 · Estrutura de diretórios

```
vsharp/
├─ Makefile             # build cross-plataforma (GCC + Flex/Bison)
├─ README.md            # este documento
├─ examples/
│  ├─ examples/         # exemplos de scripts que devem dar erro
│  └─ sanity.vs         # teste mínimo (operações matemáticas) 
│  └─ full.vs           # script que cobre (quase) toda a gramática
└─ src/
   ├─ ast.[hc]          # árvore de sintaxe
   ├─ sem.[hc]          # verificação semântica
   ├─ irgen.[hc]        # gerador LLVM-IR
   ├─ runtime.c         # npv / irr / wacc em C
   ├─ vsharp.l          # lexer (Flex)
   ├─ vsharp.y          # parser (Bison)
   └─ main.c            # driver: parse → sem → IR → lli
```

A pasta **`build/`** é criada automaticamente pelo `make` assim como os arquivos executáveis, e **não** deve ser
versionada.

---

## 5 · Como compilar e rodar

> Pré-requisitos: GCC, **Flex**, **Bison** e **LLVM ≥ 14** (por causa do
> `lli`).  No Windows foram testados `win_flex`, `win_bison` e
> LLVM 20.1.6 portátil.

```bash
cd vsharp

# 1. Compilar
make clean
make                 # cria build/vsharp.exe (+ objetos)
make test

# 2. Rodar um script
# · Windows
type examples\ok_sanity.vs | build\vsharp.exe
# · Linux
cd vsharp
sudo apt update
sudo apt install clang llvm
make clean
make               # deve terminar liso
ls build/vsharp    # tem que existir
chmod +x build/vsharp   # só se não estiver executável
./build/vsharp < examples/ok_sanity.vs   # ou o nome que existir


# 3. Executar arquivo gerado diretamente no lli (opcional)
lli -extra-module build/runtime.bc build/out.ll
```

*O alvo `build/runtime.bc` é gerado automaticamente na primeira execução
(há regra no Makefile).*

---

## 6 · Estado da implementação

| Recurso                                              | Status             |
| ---------------------------------------------------- | ------------------ |
| Léxico + parsing **de toda a EBNF**                  | ✅                  |
| Tipagem / promoção (`int` → `float`), escopos        | ✅                  |
| `npv`, `irr`, `wacc`, arrays heap, impressão `%d/%f` | ✅                  |
| `if`, `while`, atribuições, variáveis                | ✅                  |
| LLVM-IR válido e execução via `lli`                  | ✅                  |
| **Loop `for`** (emissão de IR)                       | ⚠️ TRABALHO FUTURO |
| Validações cruzadas `entity ↔ cap_table`, etc.       | ⚠️ TRABALHO FUTURO |

A versão entregue cobre integralmente os requisitos mínimos combinados
(computar NPV/IRR/WACC, estruturas de controle, impressões e variáveis).
Os pontos sinalizados como **TRABALHO FUTURO** não comprometem o
funcionamento geral e podem ser evoluídos depois da avaliação.

---
