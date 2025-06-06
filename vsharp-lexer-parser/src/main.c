#include<stdio.h>
#include"ast.h"

extern int yyparse(void);
extern Node *program_root;

int main(){
    int ret=yyparse();
    if(ret==0){
        puts("OK: sintaxe valida.");
        /* Nesta fase só construímos AST – ainda não executamos */
    }else{
        puts("ERRO: sintaxe invalida.");
    }
    return ret;
}
