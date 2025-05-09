#include <stdio.h>

/* protótipo do parser gerado pelo Bison */
int yyparse(void);

int main(int argc, char **argv)
{
    int ret = yyparse();      /* executa análise léxico‑sintática */
    if (ret == 0)
        puts("OK: sintaxe valida.");
    else
        puts("ERRO: sintaxe invalida.");
    return ret;
}
