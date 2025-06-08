// Declarações básicas já reconhecidas
var invested = -100000;        // investimento inicial
var cf1 = 40000;
var cf2 = 45000;
var cf3 = 50000;

// Chamada de função financeira (ainda NOP)
var npv1 = npv(0.1, [invested, cf1, cf2, cf3]);

// Condicional + impressão
if (npv1 > 0) {
  print("Projeto OK");
} else {
  print("Projeto não passa");
}

// Loop simples
var r = 0.05;
while (r <= 0.15) {
  var n = npv(r, [invested, cf1, cf2, cf3]);
  print("Taxa:", r);
  print("NPV :", n);
  r = r + 0.02;
}
