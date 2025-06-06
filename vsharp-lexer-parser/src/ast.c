#include<stdlib.h>
#include<string.h>
#include"ast.h"

static Node *alloc(NodeType t){
    Node *n=malloc(sizeof(Node));
    n->type=t;
    return n;
}
Node *new_nop(void){return alloc(NODE_NOP);}
Node *new_num(double n){Node *p=alloc(NODE_NUM);p->v.num=n;return p;}
Node *new_bool(int b){Node *p=alloc(NODE_BOOL);p->v.bval=b;return p;}
Node *new_str(char *s){Node *p=alloc(NODE_STR);p->v.str=strdup(s);return p;}
Node *new_ident(char *s){Node *p=alloc(NODE_IDENT);p->v.id=strdup(s);return p;}
Node *new_un(int op,Node *e){Node *p=alloc(NODE_UNOP);p->v.un.op=op;p->v.un.expr=e;return p;}
Node *new_bin(int op,Node *l,Node *r){Node *p=alloc(NODE_BINOP);p->v.bin.op=op;p->v.bin.lhs=l;p->v.bin.rhs=r;return p;}
Node *new_assign(char *id,Node *e){Node *p=alloc(NODE_ASSIGN);p->v.assign.id=strdup(id);p->v.assign.expr=e;return p;}
Node *new_vardecl(char *id,Node *init){Node *p=alloc(NODE_VARDECL);p->v.vdecl.id=strdup(id);p->v.vdecl.init=init;return p;}
Node *new_print(Node *e){Node *p=alloc(NODE_PRINT);p->v.print.expr=e;return p;}
Node *new_block(void){Node *p=alloc(NODE_BLOCK);p->v.block.list=NULL;p->v.block.count=0;return p;}
void block_add(Node *blk,Node *stmt){
    blk->v.block.list=realloc(blk->v.block.list,(blk->v.block.count+1)*sizeof(Node*));
    blk->v.block.list[blk->v.block.count++]=stmt;
}
