#include "global.h"

char lexbuf[BSIZE];

int tokenval = NONE;

int lexer(){
    printf("\n");
    int t;
    while(1){
        t = getchar();
        if (t ==' ' || t == '\t') /* elimination */
            ;
        else if(t == '\n') return S_DONE;
        else if(isdigit(t)) {
            ungetc(t,stdin);
            scanf("%d",&tokenval);
            /* check fd */
            t = getchar();
            return S_NUM;
        }
        else if(isalpha(t)) {
            int p, b=0;
            while(isalnum(t)){
                lexbuf[b] = t;
                t = getchar();
                b++;
                if (b>=BSIZE) error("buffersize overflow in lexer");
            }
            lexbuf[b]=EOS;
            ungetc(t,stdin);
            p = lookup(lexbuf);
            if (p==0) p = insert(lexbuf,S_VAR);
            tokenval=p;
            return symtable[p].token;
        } else if(t == EOF){
            return S_DONE;
        } else {
            int p;
            lexbuf[0]=t;
            lexbuf[1]=EOS;
            p = lookup(lexbuf);
            if (p==0){
                /* not keyword in*/
                tokenval = NONE;
                return t;
            } else {
                /* keyword in */
                tokenval = p;
                return symtable[p].token;
            }
        }
    }
}