// Este script tem erros de sintaxe e semântica
entity Foo {
  legal_name   = "Foo SA"
  jurisdiction = BR
  share_classes {      // falta ponto-e-vírgula e chaves mal fechadas
    common {
      votes_per_share = 1
      dividend_pref   = 0.05;
  }
}

cap_table Foo {
  common { holders = ["Alice":1000, Bob:500]; }  // Bob sem aspas
}

var x = irr([100, -50, 60]);   // sinal invertido nos fluxos de caixa
print(x)
