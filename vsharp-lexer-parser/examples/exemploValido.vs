// Exemplo V# válido
entity MyCorp {
  legal_name   = "My Corp Ltda.";  
  jurisdiction = BR;                 
  share_classes {
    common {
      votes_per_share = 1;
      dividend_pref   = 0;
    }
  }
}

cap_table MyCorp {
  common { holders = ["Alice":1000, "Bob":500]; }
}

deal IPO1 {
  type             = Equity;
  issuer           = MyCorp;
  amount           = 1000000;
  price_per_share  = 10.0;
  settlement_date  = 2025-12-01;
  underwriters     = ["BankA"];
}

var npv1 = npv(0.10, [-1000000, 300000, 400000, 500000]);
print(npv1);
