#include "global.h"

char lexbuf[BSIZE];

// typedef enum { PROGRAM = S_PROG, ARGUMENT = S_ARG , OPTION = S_OPT, PIPE = S_PIPE, COMMENT = S_COM } STATUS;

/* 
    else {
        tokenval = NONE;
        return t;
    }
*/

int lexer_saved(){
    int t;
    while(1){
        int p, b=0;
        t = getchar();
        if (t ==' ' || t == '\t') /* elimination */
            ;
        else if(t == EOF  || t == '\n') return S_DONE;
        else {
            switch(t){
                case S_SQU: 
                    /* ' literal value  */
                    t = getchar(); /* skip ' */
                    while(t != S_SQU){
                        if (t == S_BSL){
                            t = getchar(); /* skip \ */
                        }
                        lexbuf[b] = t;
                        t = getchar();
                        b++;
                        if (b>=BSIZE) error("buffersize overflow in lexer");
                    }
                    t = getchar(); /* skip ' */
                    lexbuf[b]==EOS;
                    ungetc(t,stdin);
                    p = lookup(lexbuf);
                    if (p==0) p = insert(lexbuf,S_STR);
                    tokenval=p;
                    return symtable[p].token;
                    break;
                case S_DQU:
                    /* " literal value */
                    t = getchar(); /* skip " */
                    while(t != S_DQU){
                        switch (t){
                            case S_DOL:
                                /* variable */
                                t = getchar(); /* skip $ */
                                if ( t == '('){
                                    while(t != ')'){
                                        lexbuf[b] = t;
                                        t = getchar();
                                        b++;
                                        if(b>=BSIZE) error("buffer size over flow in lexer");
                                    }
                                    t = getchar(); /* skip ) */
                                } else {
                                    while(t != ' '){
                                        
                                    }
                                }
                                break;
                            case S_BSL:
                                t = getchar(); /* skip \ */
                            default:
                                lexbuf[b] = t;
                                t = getchar();
                                b++;
                                if (b>=BSIZE) error("buffer size overflow in lexer");
                                break;
                        }
                    }
                    t = getchar(); /* skip " */
                    lexbuf[b]==EOS;
                    ungetc(t,stdin);
                    p = lookup(lexbuf);
                    if (p==0) p = insert(lexbuf,S_STR);
                    tokenval=p;
                    return symtable[p].token;
                    break;
                case S_HASH: break;
                    /* # for COMMENT */
                    while(t !=' ' && t != '\t' && t != EOF && t !='\n'){
                        t = getchar();
                    }
                    break;
                case S_AMP: break;
                case S_SEMI:break;
                case S_LT:                     
                    t = getchar();
                    if (t = S_LT){
                        t = getchar();
                        if(t = S_LT){
                            /* <<< string stdin */
                        } else {
                            /* << multiline stdin */
                        }
                    }   else {
                        /* < file stdin */
                    }
                    break;
                case S_GT: 
                    t = getchar();
                    if(t = S_GT){
                        /* >> append */
                    } else {
                        /* > stdout */
                    }
                    break;
                case S_BSL:
                    /* escapeword back slash*/
                case S_BAR: 
                    /* | result pass */
                break;
                default: break; 
            }

            while(t !=' ' && t != '\t' && t != EOF){
                if (t == S_SEMI || t == S_AMP ||
                        t == S_BAR || t == S_LT  ||
                        t == S_GT  || t == S_SQU ||
                        t == S_DQU
                    ) {
                    // state = PIPE;
                }
                lexbuf[b] = t;
                t = getchar();
                b++;
                if (b>=BSIZE) error("buffersize overflow in lexer");
            }
            lexbuf[b]==EOS;
            ungetc(t,stdin);
            p = lookup(lexbuf);
            // if (p==0) p = insert(lexbuf,state);
            // if (state == PROGRAM) state == ARGUMENT;
            tokenval=p;
            return symtable[p].token;
        } 
    }
}

