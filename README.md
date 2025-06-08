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

[conteúdo completo da EBNF – idêntico ao enviado ao professor]
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
│  ├─ sanity.vs         # teste mínimo
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

A pasta **`build/`** é criada automaticamente pelo `make` e **não** deve ser
versionada.

---

## 5 · Como compilar e rodar

> Pré-requisitos: GCC, **Flex**, **Bison** e **LLVM ≥ 14** (por causa do
> `lli`).  No Windows foram testados `win_flex`, `win_bison` e
> LLVM 20.1.6 portátil.

```bash
# 1. Compilar
make                 # cria build/vsharp.exe (+ objetos)

# 2. Rodar um script
# · Windows
type examples\sanity.vs | build\vsharp.exe
# · Unix / macOS
cat  examples/sanity.vs | ./build/vsharp

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
