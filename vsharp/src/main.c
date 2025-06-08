/*
 *  Driver – ValuationSharp
 *
 *  Etapas:
 *    1.  Parsing (Flex/Bison)  → AST
 *    2.  Análise semântica     → validação
 *    3.  Geração de IR LLVM    → build/out.ll
 *    4.  Execução JIT (opcional) via `lli`, carregando runtime.bc
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #include <io.h>
  #define ACCESS _access
  #define F_OK    0
#else
  #include <unistd.h>
  #define ACCESS access
#endif

#include "vsharp.tab.h"   /* yyparse + tokens */
#include "ast.h"
#include "sem.h"
#include "irgen.h"

/* protótipos gerados pelo Bison */
extern int   yyparse(void);
extern Node *program_root;

/* ------------------------------------------------------------ */
static int has_lli(void)
{
#ifdef _WIN32
    return system("where lli >nul 2>&1") == 0;
#else
    return system("command -v lli >/dev/null 2>&1") == 0;
#endif
}
/* ------------------------------------------------------------ */
int main(void)
{
    /* 1. Parsing -------------------------------------------------- */
    if (yyparse() != 0) {
        fprintf(stderr, "Falha de parsing.\n");
        return EXIT_FAILURE;
    }

    /* 2. Semântica ------------------------------------------------ */
    sem_analyze(program_root);
    int errs = sem_get_error_count();
    if (errs) {
        fprintf(stderr,
                "Compilação abortada – %d erro(s) semânticos.\n", errs);
        return EXIT_FAILURE;
    }

    /* 3. Geração de IR ------------------------------------------- */
    const char *llfile = "build/out.ll";
    ir_generate(program_root, llfile);
    printf("IR gerado em %s\n", llfile);

    /* 4. Execução JIT -------------------------------------------- */
    if (has_lli()) {
        /* runtime.bc deve ter sido gerado pelo Makefile              */
        if (ACCESS("build/runtime.bc", F_OK) != 0) {
            fprintf(stderr,
                    "Aviso: build/runtime.bc não encontrado – "
                    "npv/irr/wacc podem falhar ao rodar.\n");
        }
        char cmd[512];
        snprintf(cmd, sizeof(cmd),
                 "lli -extra-module build/runtime.bc %s", llfile);
        printf("Executando JIT com LLVM…\n");
        int rc = system(cmd);
        if (rc) fprintf(stderr, "lli retornou código %d\n", rc);
    } else {
        printf("⚠  'lli' não encontrado no PATH – IR não executado.\n");
    }

    /* liberação --------------------------------------------------- */
    free_node(program_root);
    return EXIT_SUCCESS;
}
