#include "sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ───────── tabelas de símbolos ───────── */
typedef struct Sym {
    char        *name;
    Type         type;
    struct Sym  *next;
} Sym;

typedef struct Scope {
    Sym           *list;
    struct Scope  *parent;
} Scope;

static Scope *current   = NULL;
static int     error_cnt = 0;

/* ───────── helpers de escopo ───────── */
static void push_scope(void)
{
    Scope *s = (Scope*)calloc(1,sizeof(Scope));
    s->parent = current;
    current   = s;
}
static void pop_scope(void)
{
    if(!current) return;
    Sym *p = current->list;
    while(p){ Sym *t=p; p=p->next; free(t->name); free(t); }
    Scope *old = current; current = current->parent; free(old);
}

static Sym *lookup(const char *n)
{
    for(Scope *s = current; s; s = s->parent)
        for(Sym *p = s->list; p; p = p->next)
            if(strcmp(p->name,n)==0) return p;
    return NULL;
}
static void insert(const char *n,Type t)
{
    if(!current) push_scope();
    if(lookup(n)){
        fprintf(stderr,"Erro semântico: redeclaração de '%s'\n",n);
        error_cnt++; return;
    }
    Sym *s = (Sym*)calloc(1,sizeof(Sym));
    s->name = _strdup(n);
    s->type = t;
    s->next = current->list;
    current->list = s;
}

/* ───────── promoção de tipos ───────── */
static Type promote(Type a,Type b)            /* int ↔ float → float */
{
    if(a==T_INVALID || b==T_INVALID) return T_INVALID;
    if(a==b) return a;
    if((a==T_INT && b==T_FLOAT) || (a==T_FLOAT && b==T_INT))
        return T_FLOAT;
    return T_INVALID;
}

/* ───────── análise de expressões ───────── */
static Type infer_expr(Node*);

static Type infer_array(Node *n)
{
    if(n->v.array.count==0) return T_ARRAY;
    Type t = infer_expr(n->v.array.elems[0]);
    for(int i=1;i<n->v.array.count;i++)
        t = promote(t,infer_expr(n->v.array.elems[i]));
    return (t==T_INVALID)?T_INVALID:T_ARRAY;
}
static Type infer_pair(Node *n)
{
    if(n->v.pair.key[0] == '\0') {
        fprintf(stderr, "chave vazia em par\n");
        error_cnt++;
    }
    Type v = infer_expr(n->v.pair.value);
    if(v==T_INVALID){
        fprintf(stderr,"Erro semântico em par \"%s\"\n",n->v.pair.key);
        error_cnt++;
    }
    return T_PAIR;
}

/* ───────── verificação de chamadas npv/irr/wacc ───────── */
static Type check_call(Node *n)
{
    const char *fn = n->v.call.id->v.str;
    int argc = n->v.call.argc;

    if(!strcmp(fn,"npv")){
        if(argc!=2){
            fprintf(stderr,"npv requer 2 argumentos\n");
            error_cnt++; return T_INVALID;
        }
        if(promote(infer_expr(n->v.call.args[0]),T_FLOAT)==T_INVALID ||
           infer_expr(n->v.call.args[1])!=T_ARRAY){
            fprintf(stderr,"tipos inválidos em npv()\n"); error_cnt++;
        }
        return T_FLOAT;
    }
    if(!strcmp(fn,"irr")){
        if(argc!=1 || infer_expr(n->v.call.args[0])!=T_ARRAY){
            fprintf(stderr,"irr requer um array\n"); error_cnt++; return T_INVALID;
        }
        return T_FLOAT;
    }
    if(!strcmp(fn,"wacc")){
        if(argc!=4){ fprintf(stderr,"wacc requer 4 argumentos\n"); error_cnt++; return T_INVALID; }
        for(int i=0;i<4;i++)
            if(promote(infer_expr(n->v.call.args[i]),T_FLOAT)==T_INVALID){
                fprintf(stderr,"tipos inválidos em wacc()\n"); error_cnt++; break;
            }
        return T_FLOAT;
    }
    fprintf(stderr,"função desconhecida '%s'\n",fn);
    error_cnt++; return T_INVALID;
}

static Type infer_expr(Node *n)
{
    if(!n) return T_INVALID;

    switch(n->type){
        /* literais */
        case NODE_NUM:   return T_INT;
        case NODE_FLOAT: return T_FLOAT;
        case NODE_BOOL:  return T_BOOL;
        case NODE_STR:   return T_STRING;
        case NODE_DATE:  return T_DATE;
        case NODE_ARRAY: return infer_array(n);
        case NODE_PAIR:  return infer_pair(n);

        /* identificador */
        case NODE_IDENT:{
            Sym *s = lookup(n->v.str);
            if(!s){
                fprintf(stderr,"variável '%s' não declarada\n",n->v.str);
                error_cnt++; return T_INVALID;
            }
            return s->type;
        }

        /* unário */
        case NODE_UNOP:  return infer_expr(n->v.un.expr);

        /* binário */
        case NODE_BINOP:{
            Type l = infer_expr(n->v.bin.lhs);
            Type r = infer_expr(n->v.bin.rhs);
            return promote(l,r);
        }

        /* atribuição */
        case NODE_ASSIGN:{
            Sym *s = lookup(n->v.assign.id);
            if(!s){
                fprintf(stderr,"variável '%s' não declarada\n",n->v.assign.id);
                error_cnt++; return T_INVALID;
            }
            Type rhs = infer_expr(n->v.assign.expr);

            /* int ← float não permitido */
            if(s->type==T_INT && rhs==T_FLOAT){
                fprintf(stderr,"perda de precisão ao atribuir float a int '%s'\n",
                        n->v.assign.id);
                error_cnt++;
            }
            return s->type;
        }

        /* chamada */
        case NODE_CALL:  return check_call(n);

        default:         return T_INVALID;
    }
}

/* ───────── análise de statements ───────── */
static void sem_node(Node*); /* forward */

static void sem_block(Node *blk)
{
    push_scope();
    for(int i=0;i<blk->v.block.count;i++)
        sem_node(blk->v.block.list[i]);
    pop_scope();
}

static void sem_vardecl(Node *n)
{
    Type t = infer_expr(n->v.vdecl.init);
    if(t==T_INVALID) t = T_INT;        /* default se sem init        */

    n->v.vdecl.vtype = t;              /* grava no nó p/ backend     */
    insert(n->v.vdecl.id, t);
}

static void sem_node(Node *n)
{
    if(!n) return;

    switch(n->type){
        case NODE_BLOCK:   sem_block(n);      break;
        case NODE_VARDECL: sem_vardecl(n);    break;

        case NODE_IF:
            infer_expr(n->v.if_s.cond);
            sem_node(n->v.if_s.thenBlk);
            sem_node(n->v.if_s.elseBlk);
            break;

        case NODE_WHILE:
            infer_expr(n->v.while_s.cond);
            sem_node(n->v.while_s.body);
            break;

        case NODE_FOR:
            sem_node(n->v.for_s.init);
            infer_expr(n->v.for_s.cond);
            infer_expr(n->v.for_s.post);
            sem_node(n->v.for_s.body);
            break;

        case NODE_PRINT:
            for(int i=0;i<n->v.print.count;i++)
                infer_expr(n->v.print.items[i]);
            break;

        /* expressões “top-level” */
        case NODE_CALL:   case NODE_BINOP:  case NODE_UNOP:
        case NODE_ASSIGN: case NODE_IDENT:  case NODE_NUM:
        case NODE_FLOAT:  case NODE_BOOL:   case NODE_DATE:
        case NODE_ARRAY:  case NODE_PAIR:
            infer_expr(n); break;

        default:          break;
    }
}

/* ───────── interface pública ───────── */
void sem_analyze(Node *root)
{
    error_cnt = 0;
    push_scope();          /* escopo global */
    sem_node(root);
    pop_scope();

    if(error_cnt)
        fprintf(stderr,"Total de erros semânticos: %d\n", error_cnt);
}
int sem_get_error_count(void){ return error_cnt; }
