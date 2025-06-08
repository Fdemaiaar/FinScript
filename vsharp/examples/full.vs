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