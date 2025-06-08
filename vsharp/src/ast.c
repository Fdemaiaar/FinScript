#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static Node *alloc_node(NodeType t){
    Node *n=(Node*)calloc(1,sizeof(Node));
    n->type=t;
    return n;
}
Node *new_num(long v){
    Node *n=alloc_node(NODE_NUM);
    n->v.num=v;
    return n;
}
Node *new_float(double v){
    Node *n=alloc_node(NODE_FLOAT);
    n->v.fval=v;
    return n;
}
Node *new_bool(int b){
    Node *n=alloc_node(NODE_BOOL);
    n->v.bval=b;
    return n;
}

Node *new_str(char *raw){
    size_t len=strlen(raw);
    char *clean=(char*)malloc(len-1);           /* tira aspas */
    memcpy(clean,raw+1,len-2);
    clean[len-2]='\0';
    free(raw);
    Node *n=alloc_node(NODE_STR);
    n->v.str=clean;
    return n;
}

Node *new_ident(char *id){
    Node *n=alloc_node(NODE_IDENT);
    n->v.str=id;
    return n;
}
Node *new_date(char *iso){
    Node *n=alloc_node(NODE_DATE);
    sscanf(iso,"%4d-%2d-%2d",&n->v.date.y,&n->v.date.m,&n->v.date.d);
    free(iso);
    return n;
}
Node *new_array(Node **elems,int cnt){
    Node *n=alloc_node(NODE_ARRAY);
    n->v.array.elems=elems;
    n->v.array.count=cnt;
    return n;
}
Node *new_array_one(Node *elem){
    Node **v=(Node**)malloc(sizeof(Node*));
    v[0]=elem;
    return new_array(v,1);
}
void array_append(Node *arr,Node *elem){
    if(!arr||arr->type!=NODE_ARRAY)return;
    int c=arr->v.array.count;
    arr->v.array.elems=(Node**)realloc(arr->v.array.elems,sizeof(Node*)*(c+1));
    arr->v.array.elems[c]=elem;
    arr->v.array.count++;
}
Node *new_pair(char *key,Node *value){
    Node *n=alloc_node(NODE_PAIR);
    n->v.pair.key=key;
    n->v.pair.value=value;
    return n;
}
Node *new_bin(int op,Node *a,Node *b){
    Node *n=alloc_node(NODE_BINOP);
    n->v.bin.op=op;
    n->v.bin.lhs=a;
    n->v.bin.rhs=b;
    return n;
}
Node *new_un(int op,Node *e){
    Node *n=alloc_node(NODE_UNOP);
    n->v.un.op=op;
    n->v.un.expr=e;
    return n;
}
Node *new_assign(char *id,Node *expr){
    Node *n=alloc_node(NODE_ASSIGN);
    n->v.assign.id=id;
    n->v.assign.expr=expr;
    return n;
}
Node *new_vardecl(char *id,Node *init){
    Node *n=alloc_node(NODE_VARDECL);
    n->v.vdecl.id=id;
    n->v.vdecl.init=init;
    return n;
}
Node *new_block(void){
    Node *n=alloc_node(NODE_BLOCK);
    n->v.block.cap=4;
    n->v.block.count=0;
    n->v.block.list=(Node**)malloc(sizeof(Node*)*n->v.block.cap);
    return n;
}
void block_add(Node *blk,Node *stmt){
    if(!blk||blk->type!=NODE_BLOCK)return;
    if(blk->v.block.count>=blk->v.block.cap){
        blk->v.block.cap*=2;
        blk->v.block.list=(Node**)realloc(blk->v.block.list,sizeof(Node*)*blk->v.block.cap);
    }
    blk->v.block.list[blk->v.block.count++]=stmt;
}
Node *new_print(Node *expr){
    Node *n=alloc_node(NODE_PRINT);
    n->v.print.cap=4;
    n->v.print.count=0;
    n->v.print.items=(Node**)malloc(sizeof(Node*)*n->v.print.cap);
    n->v.print.items[n->v.print.count++]=expr;
    return n;
}
void print_add(Node *p,Node *expr){
    if(!p||p->type!=NODE_PRINT)return;
    if(p->v.print.count>=p->v.print.cap){
        p->v.print.cap*=2;
        p->v.print.items=(Node**)realloc(p->v.print.items,sizeof(Node*)*p->v.print.cap);
    }
    p->v.print.items[p->v.print.count++]=expr;
}
Node *new_call(Node *id,Node **args,int argc){
    Node *n=alloc_node(NODE_CALL);
    n->v.call.id=id;
    n->v.call.args=args;
    n->v.call.argc=argc;
    return n;
}
Node *new_if(Node *c,Node *t,Node *e){
    Node *n=alloc_node(NODE_IF);
    n->v.if_s.cond=c;
    n->v.if_s.thenBlk=t;
    n->v.if_s.elseBlk=e;
    return n;
}
Node *new_while(Node *c,Node *b){
    Node *n=alloc_node(NODE_WHILE);
    n->v.while_s.cond=c;
    n->v.while_s.body=b;
    return n;
}
Node *new_for(Node *i,Node *c,Node *p,Node *b){
    Node *n=alloc_node(NODE_FOR);
    n->v.for_s.init=i;
    n->v.for_s.cond=c;
    n->v.for_s.post=p;
    n->v.for_s.body=b;
    return n;
}
Node *new_nop(void){
    return alloc_node(NODE_NOP);
}
static void free_node_rec(Node *n){
    if(!n)return;
    switch(n->type){
        case NODE_STR:case NODE_IDENT:
            free(n->v.str);
            break;
        case NODE_ARRAY:
            for(int i=0;i<n->v.array.count;i++)free_node_rec(n->v.array.elems[i]);
            free(n->v.array.elems);
            break;
        case NODE_PAIR:
            free(n->v.pair.key);
            free_node_rec(n->v.pair.value);
            break;
        case NODE_BINOP:
            free_node_rec(n->v.bin.lhs);
            free_node_rec(n->v.bin.rhs);
            break;
        case NODE_UNOP:
            free_node_rec(n->v.un.expr);
            break;
        case NODE_ASSIGN:
            free(n->v.assign.id);
            free_node_rec(n->v.assign.expr);
            break;
        case NODE_VARDECL:
            free(n->v.vdecl.id);
            free_node_rec(n->v.vdecl.init);
            break;
        case NODE_BLOCK:
            for(int i=0;i<n->v.block.count;i++)free_node_rec(n->v.block.list[i]);
            free(n->v.block.list);
            break;
        case NODE_PRINT:
            for(int i=0;i<n->v.print.count;i++)free_node_rec(n->v.print.items[i]);
            free(n->v.print.items);
            break;
        case NODE_CALL:
            free_node_rec(n->v.call.id);
            for(int i=0;i<n->v.call.argc;i++)free_node_rec(n->v.call.args[i]);
            free(n->v.call.args);
            break;
        case NODE_IF:
            free_node_rec(n->v.if_s.cond);
            free_node_rec(n->v.if_s.thenBlk);
            free_node_rec(n->v.if_s.elseBlk);
            break;
        case NODE_WHILE:
            free_node_rec(n->v.while_s.cond);
            free_node_rec(n->v.while_s.body);
            break;
        case NODE_FOR:
            free_node_rec(n->v.for_s.init);
            free_node_rec(n->v.for_s.cond);
            free_node_rec(n->v.for_s.post);
            free_node_rec(n->v.for_s.body);
            break;
        default:
            break;
    }
    free(n);
}
void free_node(Node *n){
    free_node_rec(n);
}
