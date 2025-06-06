#ifndef AST_H
#define AST_H
typedef enum{
    NODE_NOP,
    NODE_NUM,
    NODE_BOOL,
    NODE_STR,
    NODE_IDENT,
    NODE_BINOP,
    NODE_UNOP,
    NODE_ASSIGN,
    NODE_VARDECL,
    NODE_PRINT,
    NODE_BLOCK
}NodeType;

typedef struct Node Node;
struct Node{
    NodeType type;
    union{
        double  num;
        int     bval;
        char   *str;
        char   *id;
        struct{int op;Node *expr;}un;
        struct{int op;Node *lhs;Node *rhs;}bin;
        struct{char *id;Node *expr;}assign;
        struct{char *id;Node *init;}vdecl;
        struct{Node **list;int count;}block;
        struct{Node *expr;}print;
    }v;
};

Node *new_nop(void);
Node *new_num(double n);
Node *new_bool(int b);
Node *new_str(char *s);
Node *new_ident(char *s);
Node *new_un(int op,Node *e);
Node *new_bin(int op,Node *l,Node *r);
Node *new_assign(char *id,Node *e);
Node *new_vardecl(char *id,Node *init);
Node *new_print(Node *e);
Node *new_block(void);
void  block_add(Node *blk,Node *stmt);

#endif
