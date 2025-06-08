#include "irgen.h"
#include "vsharp.tab.h"
#include "sem.h"          /* para o enum Type            */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ───────── helpers gerais ───────── */
static FILE *out;                     /* stream de emissão (tmpfile) */
static int   regc = 0, lblc = 0, strc = 0;

static char *new_reg(void){ char *b = malloc(24); sprintf(b,"%%t%d",regc++); return b; }
static char *new_lbl(const char *p){ char *b = malloc(32); sprintf(b,"%s%d",p,lblc++); return b; }
static char *emit_num(long v)       { char *s = malloc(32); sprintf(s,"%ld",v); return s; }
static char *emit_float(double d)   { char *s = malloc(64); sprintf(s,"%f",d); return s; }

/* ───────── constantes globais (@.strN / @.fmtN) ───────── */
typedef struct { char *def; } GConst;
static GConst *gconsts = NULL;
static int     gcap    = 0, gcnt = 0;
static void add_gconst(char *s){
    if(gcnt == gcap){ gcap = gcap? gcap*2 : 16; gconsts = realloc(gconsts,gcap*sizeof(GConst)); }
    gconsts[gcnt++].def = s;
}

/* ───────── símbolo → tipo (para geração) ───────── */
typedef struct VInfo {
    char *name;
    Type  t;
    struct VInfo *next;
} VInfo;
static VInfo *vars = NULL;
static void v_add(const char *id,Type t){
    VInfo *v = malloc(sizeof(VInfo));
    v->name = _strdup(id); v->t = t; v->next = vars; vars = v;
}
static Type v_get(const char *id){
    for(VInfo *v=vars;v;v=v->next) if(strcmp(v->name,id)==0) return v->t;
    return T_INT;                        /* fallback (não deve ocorrer) */
}

/* ───────── strings literais ───────── */
static char *emit_cstr(const char *lex)
{
    char esc[512]; int j = 0;
    for(int i=0; lex[i] && j<510; i++){
        if(lex[i]=='\\' || lex[i]=='"') esc[j++]='\\';
        esc[j++] = lex[i];
    }
    esc[j] = '\0';

    int len = j + 2;                          /* + '\n' + NUL */
    int id  = strc++;

    char *line = malloc(600);
    sprintf(line,"@.str%d = private constant [%d x i8] c\"%s\\0A\\00\"\n",
            id,len,esc);
    add_gconst(line);

    char *ptr = new_reg();
    fprintf(out,
      "  %s = getelementptr inbounds "
      "[%d x i8], [%d x i8]* @.str%d, i32 0, i32 0\n",
      ptr,len,len,id);
    return ptr;                               /* i8* */
}

/* ───────── formatos %d / %f ───────── */
static char *emit_format(const char *spec)
{
    int len = (int)strlen(spec) + 2;          /* + '\n' + NUL */
    int id  = strc++;
    char *line = malloc(120);
    sprintf(line,"@.fmt%d = private constant [%d x i8] c\"%s\\0A\\00\"\n",
            id,len,spec);
    add_gconst(line);

    char *ptr = new_reg();
    fprintf(out,
      "  %s = getelementptr inbounds "
      "[%d x i8], [%d x i8]* @.fmt%d, i32 0, i32 0\n",
      ptr,len,len,id);
    return ptr;
}
static void emit_printf_d(char *v){ char *pf=emit_format("%f"); fprintf(out,"  call i32 (i8*, ...) @printf(i8* %s, double %s)\n",pf,v); free(pf);}
static void emit_printf_i(char *v){ char *pf=emit_format("%d"); fprintf(out,"  call i32 (i8*, ...) @printf(i8* %s, i32 %s)\n",pf,v);   free(pf);}

/* ───────── protótipo ───────── */
static char *emit_expr(Node*,int*);           /* kind: 0=i32 1=double 2=ptr */

/* ───────── print variádico ───────── */
static void emit_print(Node *p)
{
    for(int i=0;i<p->v.print.count;i++){
        Node *it = p->v.print.items[i];
        if(it->type == NODE_STR){
            char *ptr = emit_cstr(it->v.str);
            fprintf(out,"  call i32 (i8*, ...) @printf(i8* %s)\n",ptr);
            free(ptr);
        }else{
            int k; char *v = emit_expr(it,&k);
            k? emit_printf_d(v) : emit_printf_i(v);
            free(v);
        }
    }
}

/* ───────── arrays alocados no heap ───────── */
static char *emit_array(Node *n)
{
    int cnt = n->v.array.count;
    char **elems = malloc(sizeof(char*)*cnt);
    int   *kinds = malloc(sizeof(int)*cnt);

    for(int i=0;i<cnt;i++) elems[i]=emit_expr(n->v.array.elems[i],&kinds[i]);

    char *buf = new_reg();
    fprintf(out,"  %s = call double* @malloc(i64 %d)\n",buf,cnt*8);

    for(int i=0;i<cnt;i++){
        char *val = elems[i];
        if(kinds[i]==0){                   /* int → double */
            char *c = new_reg();
            fprintf(out,"  %s = sitofp i32 %s to double\n",c,val);
            free(val); val = c;
        }
        char *gep = new_reg();
        fprintf(out,
          "  %s = getelementptr inbounds double, double* %s, i32 %d\n",
          gep,buf,i);
        fprintf(out,"  store double %s, double* %s\n",val,gep);
        free(gep); free(val);
    }
    free(elems); free(kinds);
    return buf;                            /* double* */
}

/* ───────── controle: if / while ───────── */
static void emit_if(Node *n)
{
    char *Lthen=new_lbl("then"),*Lelse=new_lbl("else"),*Lend=new_lbl("endif");
    int kc; char *cond = emit_expr(n->v.if_s.cond,&kc);

    char *cmp = new_reg();
    if(kc) fprintf(out,"  %s = fcmp one double %s, 0.0\n",cmp,cond);
    else   fprintf(out,"  %s = icmp ne i32 %s, 0\n",cmp,cond);

    fprintf(out,"  br i1 %s, label %%%s, label %%%s\n",cmp,Lthen,Lelse);

    fprintf(out,"%s:\n",Lthen);
    int d; emit_expr(n->v.if_s.thenBlk,&d);
    fprintf(out,"  br label %%%s\n",Lend);

    fprintf(out,"%s:\n",Lelse);
    emit_expr(n->v.if_s.elseBlk,&d);
    fprintf(out,"  br label %%%s\n",Lend);

    fprintf(out,"%s:\n",Lend);
    free(Lthen); free(Lelse); free(Lend); free(cond); free(cmp);
}
static void emit_while(Node *n)
{
    char *Lc=new_lbl("cond"),*Lb=new_lbl("body"),*Le=new_lbl("wend");
    fprintf(out,"  br label %%%s\n%s:\n",Lc,Lc);

    int kc; char *cond = emit_expr(n->v.while_s.cond,&kc);
    char *cmp = new_reg();
    if(kc) fprintf(out,"  %s = fcmp one double %s, 0.0\n",cmp,cond);
    else   fprintf(out,"  %s = icmp ne i32 %s, 0\n",cmp,cond);

    fprintf(out,"  br i1 %s, label %%%s, label %%%s\n",cmp,Lb,Le);

    fprintf(out,"%s:\n",Lb);
    int d; emit_expr(n->v.while_s.body,&d);
    fprintf(out,"  br label %%%s\n%s:\n",Lc,Le);

    free(Lc); free(Lb); free(Le); free(cond); free(cmp);
}

/* ───────── aritmética / comparação ───────── */
static char *emit_bin(Node *n,int *kind)
{
    int kl,kr; char *l = emit_expr(n->v.bin.lhs,&kl);
    char *r = emit_expr(n->v.bin.rhs,&kr);

    /* promoção int→float */
    if(kl!=kr){
        if(kl==0){ char *c=new_reg(); fprintf(out,"  %s = sitofp i32 %s to double\n",c,l); free(l); l=c; kl=1; }
        if(kr==0){ char *c=new_reg(); fprintf(out,"  %s = sitofp i32 %s to double\n",c,r); free(r); r=c; kr=1; }
    }

    char *res = new_reg();

    /* operadores aritméticos */
    if(n->v.bin.op=='+'||n->v.bin.op=='-'||n->v.bin.op=='*'||n->v.bin.op=='/'){
        const char *op  = n->v.bin.op=='+'? (kl?"fadd":"add") :
                          n->v.bin.op=='-'? (kl?"fsub":"sub") :
                          n->v.bin.op=='*'? (kl?"fmul":"mul") : (kl?"fdiv":"sdiv");
        fprintf(out,"  %s = %s %s %s, %s\n",res,op, kl?"double":"i32", l,r);
        *kind = kl; free(l); free(r); return res;
    }

    /* comparações → i32 (0/1) */
    if(kl){                                        /* double → fcmp */
        const char *cmp = n->v.bin.op==LT?"olt": n->v.bin.op==LE?"ole":
                          n->v.bin.op==GT?"ogt": n->v.bin.op==GE?"oge":
                          n->v.bin.op==EQ?"oeq":"one";
        char *t=new_reg();
        fprintf(out,"  %s = fcmp %s double %s, %s\n",t,cmp,l,r);
        fprintf(out,"  %s = zext i1 %s to i32\n",res,t);
        free(t);
    }else{                                         /* int → icmp */
        const char *cmp = n->v.bin.op==LT?"slt": n->v.bin.op==LE?"sle":
                          n->v.bin.op==GT?"sgt": n->v.bin.op==GE?"sge":
                          n->v.bin.op==EQ?"eq" :"ne";
        char *t=new_reg();
        fprintf(out,"  %s = icmp %s i32 %s, %s\n",t,cmp,l,r);
        fprintf(out,"  %s = zext i1 %s to i32\n",res,t);
        free(t);
    }
    *kind = 0; free(l); free(r); return res;
}

/* ───────── chamadas npv/irr/wacc ───────── */
static char *emit_call(Node *n,int *kind)
{
    const char *fn = n->v.call.id->v.str;

    if(!strcmp(fn,"npv")){
        int k0,k1; char *rate = emit_expr(n->v.call.args[0],&k0);
        char *arr  = emit_expr(n->v.call.args[1],&k1);

        if(k0==0){ char *c=new_reg(); fprintf(out,"  %s = sitofp i32 %s to double\n",c,rate); free(rate); rate=c; }

        char *cnt = emit_num(n->v.call.args[1]->v.array.count);
        char *r=new_reg();
        fprintf(out,"  %s = call double @npv(double %s, double* %s, i32 %s)\n",r,rate,arr,cnt);
        free(rate); free(arr); free(cnt);
        *kind=1; return r;
    }

    if(!strcmp(fn,"irr")){
        char *arr = emit_expr(n->v.call.args[0],kind);
        char *cnt = emit_num(n->v.call.args[0]->v.array.count);
        char *r=new_reg();
        fprintf(out,"  %s = call double @irr(double* %s, i32 %s)\n",r,arr,cnt);
        free(arr); free(cnt);
        *kind=1; return r;
    }

    if(!strcmp(fn,"wacc")){
        char *a[4]; int k[4];
        for(int i=0;i<4;i++) a[i] = emit_expr(n->v.call.args[i],&k[i]);

        for(int i=0;i<4;i++) if(k[i]==0){
            char *c=new_reg(); fprintf(out,"  %s = sitofp i32 %s to double\n",c,a[i]);
            free(a[i]); a[i]=c;
        }
        char *r=new_reg();
        fprintf(out,"  %s = call double @wacc(double %s, double %s, double %s, double %s)\n",
                r,a[0],a[1],a[2],a[3]);
        for(int i=0;i<4;i++) free(a[i]);
        *kind=1; return r;
    }

    *kind=1; return emit_float(0.0);          /* stub para desconhecidos */
}

/* ───────── expressão geral ───────── */
static char *emit_expr(Node *n,int *kind)
{
    if(!n){ *kind=0; return emit_num(0); }

    switch(n->type){
        /* ─ blocks: percorre filhos ─ */
        case NODE_BLOCK:{
            for(int i=0;i<n->v.block.count;i++){
                int k; char *v = emit_expr(n->v.block.list[i],&k); free(v);
            }
            *kind=0; return emit_num(0);
        }

        /* ─ literais ─ */
        case NODE_NUM:   *kind=0; return emit_num  (n->v.num );
        case NODE_FLOAT: *kind=1; return emit_float(n->v.fval);

        /* ─ identificador (load) ─ */
        case NODE_IDENT:{
            Type t = v_get(n->v.str);
            char *reg = new_reg();
            if(t==T_FLOAT){
                fprintf(out,"  %s = load double, double* %%%s\n",reg,n->v.str);
                *kind=1;
            }else{
                fprintf(out,"  %s = load i32, i32* %%%s\n",reg,n->v.str);
                *kind=0;
            }
            return reg;
        }

        /* ─ aritm/comparação ─ */
        case NODE_BINOP: return emit_bin(n,kind);
        case NODE_UNOP:{
            int k; char *e = emit_expr(n->v.un.expr,&k);
            char *r = new_reg();
            if(n->v.un.op=='-'){
                if(k) fprintf(out,"  %s = fsub double 0.0, %s\n",r,e), (*kind=1);
                else  fprintf(out,"  %s = sub i32 0, %s\n",  r,e), (*kind=0);
            }else{ /* ! */
                char *t = new_reg();
                if(k) fprintf(out,"  %s = fcmp oeq double %s, 0.0\n",t,e);
                else fprintf(out,"  %s = icmp eq i32 %s, 0\n",t,e);
                fprintf(out,"  %s = zext i1 %s to i32\n",r,t);
                free(t); *kind=0;
            }
            free(e); return r;
        }

        /* ─ atribuição ─ */
        case NODE_ASSIGN:{
            Type dt = v_get(n->v.assign.id);
            int  kt; char *val = emit_expr(n->v.assign.expr,&kt);

            if(dt==T_FLOAT){
                if(kt==0){                  /* int → double */
                    char *c=new_reg();
                    fprintf(out,"  %s = sitofp i32 %s to double\n",c,val);
                    free(val); val=c;
                }
                fprintf(out,"  store double %s, double* %%%s\n",val,n->v.assign.id);
            }else{                          /* int destino */
                if(kt==1){                  /* float → int (truncate) */
                    char *c=new_reg();
                    fprintf(out,"  %s = fptosi double %s to i32\n",c,val);
                    free(val); val=c;
                }
                fprintf(out,"  store i32 %s, i32* %%%s\n",val,n->v.assign.id);
            }
            free(val); *kind=0; return emit_num(0);
        }

        /* ─ declaração de variável ─ */
        case NODE_VARDECL:{
            Type t = n->v.vdecl.vtype;
            if(t==T_FLOAT)
                fprintf(out,"  %%%s = alloca double\n",n->v.vdecl.id);
            else
                fprintf(out,"  %%%s = alloca i32\n",   n->v.vdecl.id);

            v_add(n->v.vdecl.id, t);

            if(n->v.vdecl.init){
                int k; char *ini = emit_expr(n->v.vdecl.init,&k);

                if(t==T_FLOAT){
                    if(k==0){ char *c=new_reg(); fprintf(out,
                            "  %s = sitofp i32 %s to double\n",c,ini); free(ini); ini=c; }
                    fprintf(out,"  store double %s, double* %%%s\n",ini,n->v.vdecl.id);
                }else{
                    if(k==1){ char *c=new_reg(); fprintf(out,
                            "  %s = fptosi double %s to i32\n",c,ini); free(ini); ini=c; }
                    fprintf(out,"  store i32 %s, i32* %%%s\n",ini,n->v.vdecl.id);
                }
                free(ini);
            }
            *kind=0; return emit_num(0);
        }

        /* ─ demais tipos ─ */
        case NODE_ARRAY: *kind=2; return emit_array(n);
        case NODE_PRINT: emit_print(n); *kind=0; return emit_num(0);
        case NODE_CALL:  return emit_call(n,kind);
        case NODE_IF:    emit_if(n);   *kind=0; return emit_num(0);
        case NODE_WHILE: emit_while(n);*kind=0; return emit_num(0);

        default:         *kind=0; return emit_num(0);
    }
}

/* ───────── geração principal ───────── */
void ir_generate(Node *root,const char *path)
{
    /* Buffer temporário com corpo do main */
    FILE *body = tmpfile(); if(!body){ perror("tmpfile"); exit(1); }
    out = body;
    int k; char *dummy = emit_expr(root,&k); free(dummy);
    fflush(body); rewind(body);

    /* Arquivo final */
    FILE *f = fopen(path,"w"); if(!f){ perror("fopen"); exit(1); }

    /* declarações externas */
    fprintf(f,
      "declare i32 @printf(i8*, ...)\n"
      "declare double @npv(double,double*,i32)\n"
      "declare double @irr(double*,i32)\n"
      "declare double @wacc(double,double,double,double)\n"
      "declare i8* @malloc(i64)\n\n");

    /* globais de string/formatos */
    for(int i=0;i<gcnt;i++) fputs(gconsts[i].def,f);
    if(gcnt) fputc('\n',f);

    /* função main */
    fputs("define i32 @main(){\n",f);
    int ch; while((ch=fgetc(body))!=EOF) fputc(ch,f);
    fputs("  ret i32 0\n}\n",f);

    fclose(body); fclose(f);
}
