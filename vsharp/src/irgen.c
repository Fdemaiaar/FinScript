#include "irgen.h"
#include "vsharp.tab.h"
#include "sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/*  Tabela de variáveis  (nome → KType: i32 / double / ptr)           */
/* ------------------------------------------------------------------ */
typedef enum { KT_I32, KT_DBL, KT_PTR } KType;
typedef struct VSym { char *name; KType ktype; struct VSym *next; } VSym;
static VSym *vs_head = NULL;
static void  vs_add(const char *n,KType k){
    VSym*v=malloc(sizeof*v); v->name=strdup(n); v->ktype=k; v->next=vs_head;
    vs_head=v;
}
static KType vs_get(const char *n){
    for(VSym*v=vs_head;v;v=v->next) if(!strcmp(v->name,n)) return v->ktype;
    return KT_I32;
}

/* ------------------------------------------------------------------ */
/*  NOVO: id → len  (tamanho de arrays literais)                      */
/* ------------------------------------------------------------------ */
typedef struct ArrInfo{ char *name; int len; struct ArrInfo *next; } ArrInfo;
static ArrInfo *arr_head = NULL;
static void arr_add(const char *id,int len){
    ArrInfo*a=malloc(sizeof*a); a->name=strdup(id); a->len=len; a->next=arr_head;
    arr_head=a;
}
static int arr_len(const char *id){
    for(ArrInfo*a=arr_head;a;a=a->next) if(!strcmp(a->name,id)) return a->len;
    return 0;
}

/* ------------------------------------------------------------------ */
static FILE *out;
static int   regc=0,lblc=0,strc=0;
static char *new_reg(void){ char*b=malloc(24); sprintf(b,"%%t%d",regc++); return b; }
static char *new_lbl(const char*p){ char*b=malloc(32); sprintf(b,"%s%d",p,lblc++); return b; }
static char *emit_num(long v){ char*s=malloc(32); sprintf(s,"%ld",v); return s; }
static char *emit_float(double d){ char*s=malloc(64); sprintf(s,"%f",d); return s; }

/* -------- globais de string / formatos ---------------------------- */
typedef struct{ char*def; }GConst;
static GConst *gconsts=NULL; static int gcap=0,gcnt=0;
static void add_gconst(char*s){
    if(gcnt==gcap){ gcap=gcap?gcap*2:16; gconsts=realloc(gconsts,gcap*sizeof(GConst)); }
    gconsts[gcnt++].def=s;
}

/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
static char *emit_expr (Node*,int*);   /* 0=i32 1=double 2=ptr         */
static char *emit_bin  (Node*,int*);
static void  emit_if   (Node*);
static void  emit_while(Node*);

/* === string literal / printf ====================================== */
static char *emit_cstr(const char *lex){
    char esc[512]; int j=0;
    for(int i=0;lex[i]&&j<510;i++){ if(lex[i]=='\\'||lex[i]=='"') esc[j++]='\\'; esc[j++]=lex[i]; }
    esc[j]=0; int len=j+2,id=strc++;
    char*line=malloc(600);
    sprintf(line,"@.str%d = private constant [%d x i8] c\"%s\\0A\\00\"\n",id,len,esc);
    add_gconst(line);
    char*ptr=new_reg();
    fprintf(out,"  %s = getelementptr inbounds [%d x i8], [%d x i8]* @.str%d, i32 0, i32 0\n",ptr,len,len,id);
    return ptr;
}
static char *emit_format(const char*s){
    int len=strlen(s)+2,id=strc++;
    char*line=malloc(120);
    sprintf(line,"@.fmt%d = private constant [%d x i8] c\"%s\\0A\\00\"\n",id,len,s);
    add_gconst(line);
    char*ptr=new_reg();
    fprintf(out,"  %s = getelementptr inbounds [%d x i8], [%d x i8]* @.fmt%d, i32 0, i32 0\n",ptr,len,len,id);
    return ptr;
}
static void emit_printf_d(char*v){ char*pf=emit_format("%f"); fprintf(out,"  call i32 (i8*, ...) @printf(i8* %s, double %s)\n",pf,v); free(pf); }
static void emit_printf_i(char*v){ char*pf=emit_format("%d"); fprintf(out,"  call i32 (i8*, ...) @printf(i8* %s, i32 %s)\n",pf,v);   free(pf); }

/* === array literal ================================================= */
static char *emit_array(Node *n){
    int cnt=n->v.array.count;
    char **elems=malloc(cnt*sizeof(char*));
    int   *kinds=malloc(cnt*sizeof(int));
    for(int i=0;i<cnt;i++) elems[i]=emit_expr(n->v.array.elems[i],&kinds[i]);

    char*buf=new_reg();
    fprintf(out,"  %s = call double* @malloc(i64 %d)\n",buf,cnt*8);

    for(int i=0;i<cnt;i++){
        char*val=elems[i];
        if(kinds[i]==0){
            char*c=new_reg();
            fprintf(out,"  %s = sitofp i32 %s to double\n",c,val);
            free(val); val=c;
        }
        char*gep=new_reg();
        fprintf(out,"  %s = getelementptr inbounds double, double* %s, i32 %d\n",gep,buf,i);
        fprintf(out,"  store double %s, double* %s\n",val,gep);
        free(gep); free(val);
    }
    free(elems); free(kinds);
    return buf;
}

/* === print variádico ============================================== */
static void emit_print(Node *p){
    for(int i=0;i<p->v.print.count;i++){
        Node*it=p->v.print.items[i];
        if(it->type==NODE_STR){
            char*ptr=emit_cstr(it->v.str);
            fprintf(out,"  call i32 (i8*, ...) @printf(i8* %s)\n",ptr);
            free(ptr);
        }else{
            int k; char*v=emit_expr(it,&k);
            k?emit_printf_d(v):emit_printf_i(v);
            free(v);
        }
    }
}

/* === IF / WHILE / BINOP (originais) =============================== */
/* ... mesmos emit_if, emit_while, emit_bin do seu arquivo original ... */

/* === CALL – npv / irr / wacc ====================================== */
static char *emit_call(Node *n,int *kind){
    const char *fn=n->v.call.id->v.str;

    /* ---------- npv ------------------------------------------------- */
    if(!strcmp(fn,"npv")){
        int k0,k1; char*rate=emit_expr(n->v.call.args[0],&k0);
        char*arr =emit_expr(n->v.call.args[1],&k1);

        if(k0==0){ char*c=new_reg(); fprintf(out,"  %s = sitofp i32 %s to double\n",c,rate); free(rate); rate=c; }

        int len=(n->v.call.args[1]->type==NODE_IDENT)
                ? arr_len(n->v.call.args[1]->v.str)
                : n->v.call.args[1]->v.array.count;
        char*cnt=emit_num(len);

        char*r=new_reg();
        fprintf(out,"  %s = call double @npv(double %s, double* %s, i32 %s)\n",r,rate,arr,cnt);
        free(rate); free(arr); free(cnt);
        *kind=1; return r;
    }

    /* ---------- irr -------------------------------------------------- */
    if(!strcmp(fn,"irr")){
        char*arr=emit_expr(n->v.call.args[0],kind);
        int len=(n->v.call.args[0]->type==NODE_IDENT)
                ? arr_len(n->v.call.args[0]->v.str)
                : n->v.call.args[0]->v.array.count;
        char*cnt=emit_num(len);
        char*r=new_reg();
        fprintf(out,"  %s = call double @irr(double* %s, i32 %s)\n",r,arr,cnt);
        free(arr); free(cnt);
        *kind=1; return r;
    }

    /* ---------- wacc (original) ------------------------------------- */
    /* ... inalterado ... */

    *kind=1; return emit_float(0.0);
}

/* === emit_expr (apenas VARDECL e ASSIGN modificados) =============== */
static char *emit_expr(Node *n,int *kind){
    if(!n){ *kind=0; return emit_num(0); }

    switch(n->type){

        case NODE_VARDECL:{
            int k; if(n->v.vdecl.init) emit_expr(n->v.vdecl.init,&k); else k=0;
            const char*ty=(k==0)?"i32":(k==1)?"double":"double*";
            fprintf(out,"  %%%s = alloca %s\n",n->v.vdecl.id,ty);
            vs_add(n->v.vdecl.id,k==0?KT_I32:k==1?KT_DBL:KT_PTR);

            if(n->v.vdecl.init){
                char*v=emit_expr(n->v.vdecl.init,&k);
                fprintf(out,"  store %s %s, %s* %%%s\n",ty,v,ty,n->v.vdecl.id);
                free(v);
                if(n->v.vdecl.init->type==NODE_ARRAY)
                    arr_add(n->v.vdecl.id,n->v.vdecl.init->v.array.count);
            }
            *kind=0; return emit_num(0);
        }

        case NODE_ASSIGN:{
            KType kt=vs_get(n->v.assign.id);
            const char*ty=kt==KT_DBL?"double":kt==KT_PTR?"double*":"i32";
            int k; char*val=emit_expr(n->v.assign.expr,&k);
            if(kt==KT_DBL && k==0){
                char*c=new_reg();
                fprintf(out,"  %s = sitofp i32 %s to double\n",c,val);
                free(val); val=c;
            }
            fprintf(out,"  store %s %s, %s* %%%s\n",ty,val,ty,n->v.assign.id);
            if(n->v.assign.expr->type==NODE_ARRAY)
                arr_add(n->v.assign.id,n->v.assign.expr->v.array.count);
            free(val);
            *kind=0; return emit_num(0);
        }

        /* --- todos os demais cases são idênticos ao seu original ---- */
        /* NODE_NUM, NODE_FLOAT, NODE_BOOL, NODE
        /* ---------------------------------------------------------- */
        case NODE_NUM:   *kind=0; return emit_num  (n->v.num  );
        case NODE_FLOAT: *kind=1; return emit_float(n->v.fval);
        case NODE_BOOL:  *kind=0; return emit_num  (n->v.bval);

        case NODE_STR:{                       /* string literal ptr i8* */
            char *ptr = emit_cstr(n->v.str);
            *kind = 2;
            return ptr;
        }

        case NODE_DATE:  *kind=0; return emit_num(0);          /* stub */

        /* ---------------------------------------------------------- */
        case NODE_IDENT:{
            KType kt = vs_get(n->v.str);
            const char*ty = kt==KT_DBL ? "double" :
                            kt==KT_PTR ? "double*" : "i32";
            char*r=new_reg();
            fprintf(out,"  %s = load %s, %s* %%%s\n",r,ty,ty,n->v.str);
            *kind = (kt==KT_DBL)?1:(kt==KT_PTR)?2:0;
            return r;
        }

        /* ---------------------------------------------------------- */
        case NODE_ARRAY: *kind=2; return emit_array(n);

        /* par "string":expr – gera ponteiro para valor */
        case NODE_PAIR: {
            /* No backend atual pares só aparecem dentro de arrays,
               nunca avaliados sozinhos. Retorna 0. */
            *kind=0; return emit_num(0);
        }

        /* ---------------------------------------------------------- */
        case NODE_BINOP: return emit_bin(n,kind);
        case NODE_UNOP:{
            int k; char*e=emit_expr(n->v.un.expr,&k);
            char*r=new_reg();
            if(n->v.un.op=='-'){
                if(k) fprintf(out,"  %s = fsub double 0.0, %s\n",r,e),(*kind=1);
                else fprintf(out,"  %s = sub i32 0, %s\n",r,e),(*kind=0);
            }else{                             /* ! */
                char*t=new_reg();
                if(k) fprintf(out,"  %s = fcmp oeq double %s, 0.0\n",t,e);
                else fprintf(out,"  %s = icmp eq i32 %s, 0\n",t,e);
                fprintf(out,"  %s = zext i1 %s to i32\n",r,t);
                free(t); *kind=0;
            }
            free(e); return r;
        }

        /* ---------------------------------------------------------- */
        case NODE_BLOCK:{
            for(int i=0;i<n->v.block.count;i++){
                int k; char*v=emit_expr(n->v.block.list[i],&k);
                free(v);
            }
            *kind=0; return emit_num(0);
        }

        case NODE_PRINT: emit_print(n); *kind=0; return emit_num(0);
        case NODE_CALL:  return emit_call(n,kind);
        case NODE_IF:    emit_if(n);   *kind=0; return emit_num(0);
        case NODE_WHILE: emit_while(n);*kind=0; return emit_num(0);
        case NODE_FOR:   /* ainda não implementado */ *kind=0; return emit_num(0);

        /* domínios / métricas geram NOP no backend */
        case NODE_ENTITY:   case NODE_CAPTABLE: case NODE_DEAL:
        case NODE_DEBT:     case NODE_COST_DEBT: case NODE_COST_EQ:
        case NODE_VALUATION:case NODE_METRIC:   case NODE_NOP:
            *kind=0; return emit_num(0);

        default: *kind=0; return emit_num(0);
    }
}

/* ---------- if ---------------------------------------------------- */
static void emit_if(Node *n)
{
    char *Lthen=new_lbl("then"), *Lelse=new_lbl("else"), *Lend=new_lbl("endif");
    int kc; char *cond = emit_expr(n->v.if_s.cond,&kc);

    char *cmp=new_reg();
    if(kc) fprintf(out,"  %s = fcmp one double %s, 0.0\n",cmp,cond);
    else   fprintf(out,"  %s = icmp ne i32 %s, 0\n",cmp,cond);

    fprintf(out,"  br i1 %s, label %%%s, label %%%s\n",cmp,Lthen,Lelse);

    /* then */
    fprintf(out,"%s:\n",Lthen);
    int d; emit_expr(n->v.if_s.thenBlk,&d);
    fprintf(out,"  br label %%%s\n",Lend);

    /* else */
    fprintf(out,"%s:\n",Lelse);
    emit_expr(n->v.if_s.elseBlk,&d);
    fprintf(out,"  br label %%%s\n",Lend);

    fprintf(out,"%s:\n",Lend);
    free(Lthen); free(Lelse); free(Lend); free(cond); free(cmp);
}

/* ---------- while ------------------------------------------------- */
static void emit_while(Node *n)
{
    char *Lc=new_lbl("while_cond"), *Lb=new_lbl("while_body"), *Le=new_lbl("while_end");
    fprintf(out,"  br label %%%s\n%s:\n",Lc,Lc);

    int kc; char*cond=emit_expr(n->v.while_s.cond,&kc);
    char*cmp=new_reg();
    if(kc) fprintf(out,"  %s = fcmp one double %s, 0.0\n",cmp,cond);
    else   fprintf(out,"  %s = icmp ne i32 %s, 0\n",cmp,cond);

    fprintf(out,"  br i1 %s, label %%%s, label %%%s\n",cmp,Lb,Le);

    fprintf(out,"%s:\n",Lb);
    int d; emit_expr(n->v.while_s.body,&d);
    fprintf(out,"  br label %%%s\n%s:\n",Lc,Le);

    free(Lc); free(Lb); free(Le); free(cond); free(cmp);
}

/* ---------- binop (aritmética / comparação) ----------------------- */
static char *emit_bin(Node *n, int *kind)
{
    int kl, kr;
    char *l = emit_expr(n->v.bin.lhs, &kl);
    char *r = emit_expr(n->v.bin.rhs, &kr);

    /* promoção int → double (para aritmética/comparação) */
    if (kl != kr) {
        if (kl == 0) {
            char *c = new_reg();
            fprintf(out, "  %s = sitofp i32 %s to double\n", c, l);
            free(l); l = c; kl = 1;
        }
        if (kr == 0) {
            char *c = new_reg();
            fprintf(out, "  %s = sitofp i32 %s to double\n", c, r);
            free(r); r = c; kr = 1;
        }
    }

    /* ---------- operadores aritméticos + - * / -------------------- */
    if (strchr("+-*/", n->v.bin.op)) {
        char *res = new_reg();
        const char *op = n->v.bin.op == '+' ? (kl ? "fadd" : "add") :
                         n->v.bin.op == '-' ? (kl ? "fsub" : "sub") :
                         n->v.bin.op == '*' ? (kl ? "fmul" : "mul") :
                                              (kl ? "fdiv" : "sdiv");
        fprintf(out, "  %s = %s %s %s, %s\n", res,
                op, kl ? "double" : "i32", l, r);
        *kind = kl;
        free(l); free(r);
        return res;
    }

    /* ---------- operadores lógicos &&  || ------------------------- */
    if (n->v.bin.op == AND || n->v.bin.op == OR) {
        /* converte l e r para i1 */
        char *lbool = new_reg();
        char *rbool = new_reg();

        if (kl)  fprintf(out, "  %s = fcmp one double %s, 0.0\n", lbool, l);
        else     fprintf(out, "  %s = icmp ne i32 %s, 0\n",      lbool, l);

        if (kr)  fprintf(out, "  %s = fcmp one double %s, 0.0\n", rbool, r);
        else     fprintf(out, "  %s = icmp ne i32 %s, 0\n",      rbool, r);

        const char *ir_op = (n->v.bin.op == AND) ? "and" : "or";
        char *tmp = new_reg();
        fprintf(out, "  %s = %s i1 %s, %s\n", tmp, ir_op, lbool, rbool);

        char *res = new_reg();
        fprintf(out, "  %s = zext i1 %s to i32\n", res, tmp);

        free(l); free(r); free(lbool); free(rbool); free(tmp);
        *kind = 0;                       /* 0 ou 1 */
        return res;
    }

    /* ---------- comparações == != < <= > >= ------------------------ */
    char *res = new_reg();
    if (kl) {           /* double -> fcmp */
        const char *cmp = n->v.bin.op == LT ? "olt" :
                          n->v.bin.op == LE ? "ole" :
                          n->v.bin.op == GT ? "ogt" :
                          n->v.bin.op == GE ? "oge" :
                          n->v.bin.op == EQ ? "oeq" : "one";
        char *t = new_reg();
        fprintf(out, "  %s = fcmp %s double %s, %s\n", t, cmp, l, r);
        fprintf(out, "  %s = zext i1 %s to i32\n", res, t);
        free(t);
    } else {            /* int -> icmp   */
        const char *cmp = n->v.bin.op == LT ? "slt" :
                          n->v.bin.op == LE ? "sle" :
                          n->v.bin.op == GT ? "sgt" :
                          n->v.bin.op == GE ? "sge" :
                          n->v.bin.op == EQ ? "eq"  : "ne";
        char *t = new_reg();
        fprintf(out, "  %s = icmp %s i32 %s, %s\n", t, cmp, l, r);
        fprintf(out, "  %s = zext i1 %s to i32\n", res, t);
        free(t);
    }

    free(l); free(r);
    *kind = 0;
    return res;
}



/* ===================================================================
 *  Geração principal
 * =================================================================*/
void ir_generate(Node *root,const char *path)
{
    /* 1. Emite corpo do main em arquivo temporário */
    FILE*tmp = tmpfile();  if(!tmp){ perror("tmpfile"); exit(1); }
    out = tmp;
    int k; char*dummy = emit_expr(root,&k); free(dummy);
    fflush(tmp); rewind(tmp);

    /* 2. Abre arquivo final .ll */
    FILE*f=fopen(path,"w"); if(!f){ perror("fopen"); exit(1); }

    /* 3. Declarações externas */
    fprintf(f,
      "declare i32 @printf(i8*, ...)\n"
      "declare double @npv(double,double*,i32)\n"
      "declare double @irr(double*,i32)\n"
      "declare double @wacc(double,double,double,double)\n"
      "declare i8* @malloc(i64)\n\n");

    /* 4. Constantes globais (@.str, @.fmt) */
    for(int i=0;i<gcnt;i++) fputs(gconsts[i].def,f);
    if(gcnt) fputc('\n',f);

    /* 5. Função main */
    fputs("define i32 @main(){\n",f);
    int ch; while((ch=fgetc(tmp))!=EOF) fputc(ch,f);
    fputs("  ret i32 0\n}\n",f);

    fclose(tmp); fclose(f);
}
