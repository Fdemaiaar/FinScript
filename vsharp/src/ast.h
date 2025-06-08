#ifndef AST_H
#define AST_H

#include <stddef.h>

/* ───── tipos primitivos conhecidos pela linguagem ───── */
typedef enum {
    T_INVALID = 0,
    T_INT,
    T_FLOAT,
    T_BOOL,
    T_STRING,
    T_ARRAY,
    T_PAIR,
    T_DATE
} Type;

/* ───── enum de nós da AST ───── */
typedef enum {
    /* literais / id */
    NODE_NUM = 1, NODE_FLOAT, NODE_BOOL, NODE_STR, NODE_DATE, NODE_IDENT,
    /* estruturas */
    NODE_ARRAY, NODE_PAIR,
    /* expressões */
    NODE_BINOP, NODE_UNOP, NODE_ASSIGN,
    /* statements */
    NODE_VARDECL, NODE_BLOCK, NODE_PRINT,
    NODE_WHILE, NODE_IF, NODE_FOR, NODE_CALL,
    /* domínio (N-ops) */
    NODE_ENTITY, NODE_CAPTABLE, NODE_DEAL, NODE_DEBT,
    NODE_COST_DEBT, NODE_COST_EQ, NODE_VALUATION, NODE_METRIC,
    NODE_NOP
} NodeType;

/* ───── struct principal ───── */
typedef struct Node Node;
struct Node{
    NodeType type;
    union{
        long    num;        double fval;   int bval;   char *str;
        struct { int y,m,d; } date;

        struct { Node **elems; int count; } array;
        struct { char *key; Node *value;  } pair;

        struct { int op; Node *lhs,*rhs; } bin;
        struct { int op; Node *expr;     } un;
        struct { char *id; Node *expr;   } assign;

        struct { char *id; Node *init; Type vtype; } vdecl;
        struct { Node **list; int count,cap; } block;
        struct { Node **items;int count,cap; } print;

        struct { Node *cond,*thenBlk,*elseBlk;     } if_s;
        struct { Node *cond,*body;                 } while_s;
        struct { Node *init,*cond,*post,*body;     } for_s;

        struct { Node *id; Node **args; int argc;  } call;
    } v;
};

/* ───── API de construção (mesma de antes) ───── */
Node *new_num(long v);                Node *new_float(double v);
Node *new_bool(int v);                Node *new_str(char *s);
Node *new_date(char *iso);            Node *new_ident(char *id);
Node *new_array(Node **elems,int cnt);
Node *new_array_one(Node *elem);      void  array_append(Node*,Node*);
Node *new_pair(char *key,Node *value);
Node *new_bin(int op,Node *a,Node *b);Node *new_un(int op,Node*);
Node *new_assign(char *id,Node*);
Node *new_vardecl(char *id,Node *init);
Node *new_block(void);                void  block_add(Node*,Node*);
Node *new_print(Node *expr);          void  print_add(Node*,Node*);
Node *new_call(Node *id,Node **args,int argc);
Node *new_if(Node *c,Node *t,Node *e);
Node *new_while(Node *c,Node *b);
Node *new_for(Node *i,Node *c,Node *p,Node *b);
Node *new_nop(void);                  void  free_node(Node*);
#endif /* AST_H */
