#ifndef SEM_H
#define SEM_H

#include "ast.h"        /* já traz enum Type                   */

/* Análise semântica – percorre a AST,
   emite diagnósticos e preenche vdecl.vtype. */
void sem_analyze(Node *root);

/* Número de erros detectados na última execução. */
int  sem_get_error_count(void);

#endif /* SEM_H */
