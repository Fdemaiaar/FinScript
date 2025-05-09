// ---------- declarações ----------
entity MyCorp {}

cap_table MyCorp {}

deal IPO_2025 {}

debt_instrument Bond2030 {}

cost_of_debt  CdCorp {}

cost_of_equity CeCorp {}

valuation ValCorp {}


// ---------- variáveis + métricas ----------
var v1   = npv();
var irr1 = irr();
var w1   = wacc();


// ---------- controle de fluxo ----------
if (v1 > 0) {
  print("NPV positivo");
} else {
  print("NPV negativo");
}

var i = 0;
while (i < 3) {
  print(i);
  i = i + 1;
}

for (var j = 0; j < 2; j = j + 1) {
  print(j);
}

print("script concluído");
