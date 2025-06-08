/*====================================================================
 *  runtime.c ― Biblioteca-padrão da linguagem V#
 *
 *  • make_array ― aloca/duplica vetor de double no heap
 *  • npv        ― Valor Presente Líquido
 *  • irr        ― Taxa Interna de Retorno  (Newton + bissecção)
 *  • wacc       ― Weighted Average Cost of Capital
 *
 *  Compile como bitcode (para lli):
 *      clang -emit-llvm -c -o build/runtime.bc src/runtime.c
 *===================================================================*/
#include <stdlib.h>
#include <math.h>

/*---------------------------------------------------------------
 *  make_array - copia um vetor de double para o heap
 *--------------------------------------------------------------*/
double *make_array(const double *src, int n)
{
    if (!src || n <= 0) return NULL;

    double *dst = (double *)malloc((size_t)n * sizeof(double));
    if (!dst) return NULL;

    for (int i = 0; i < n; ++i)
        dst[i] = src[i];

    return dst;
}

/*---------------------------------------------------------------
 *  npv ― Desconto de fluxo de caixa discreto
 *--------------------------------------------------------------*/
double npv(double rate, const double *cash, int n)
{
    double acc = 0.0;

    for (int t = 0; t < n; ++t)
        acc += cash[t] / pow(1.0 + rate, (double)t);

    return acc;
}

/*---------------------------------------------------------------
 *  irr ― Newton-Raphson com bissecção de reforço
 *         (requer cash[0] < 0 e raiz em (-0.9, 1.0))
 *  Retorna −99.0 se não convergir
 *--------------------------------------------------------------*/
double irr(const double *cash, int n)
{
    double lo = -0.9, hi = 1.0;

    /* checa se há raiz no intervalo                           */
    if (npv(lo, cash, n) * npv(hi, cash, n) > 0.0)
        return -99.0;

    double r = 0.5 * (lo + hi);

    for (int iter = 0; iter < 128; ++iter) {
        /* f(r) e f’(r)                                          */
        double f  = 0.0,
               fp = 0.0,
               den = 1.0 + r;

        for (int t = 0; t < n; ++t) {
            double disc = pow(den, (double)t);
            f  += cash[t] / disc;
            fp -= t * cash[t] / (disc * den);
        }

        /* passo de Newton se derivada não for degenerada        */
        if (fabs(fp) > 1e-12) {
            double nr = r - f / fp;
            if (nr > lo && nr < hi)
                r = nr;
        }

        /* bissecção como “airbag”                               */
        double fr = npv(r, cash, n);
        if (fabs(fr) < 1e-8)
            return r;

        (fr > 0.0) ? (lo = r) : (hi = r);
        r = 0.5 * (lo + hi);
    }
    return -99.0;        /* não convergiu                       */
}

/*---------------------------------------------------------------
 *  wacc ― Custo Médio Ponderado de Capital
 *--------------------------------------------------------------*/
double wacc(double E, double D, double Ce, double Cd)
{
    double V = E + D;
    return (V == 0.0) ? 0.0 : (E * Ce + D * Cd) / V;
}
