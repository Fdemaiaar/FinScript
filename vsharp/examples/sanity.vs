// Sanity – teste mínimo cobrindo variáveis, arrays, loops, funções financeiras
// 1 · Variáveis e aritmética simples
var x = 5 + 3           ;   // 8
var y = x * 2           ;   // 16
print("y =", y)         ;

// 2 · Array literal + chamada npv
var cf  = [ -100 , 40 , 40 , 40 ]          ;
var r   = 0.10                            ;
var val = npv(r, cf)                      ;
print("NPV =", val)                       ;

// 3 · Loop while – contagem regressiva
var c = 3 ;
while (c > 0) {
  print("count:", c)  ;
  c = c - 1           ;
}

// 4 · print variádico
print("done") ;
