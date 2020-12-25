#include "global.h"

enum STATUS { Normal, isStr, isStr2, isCmd, isAmp, isBar, isLT, isLTLT, isGT, isGTGT, isHash };

char lexbuf[BSIZE];

int lexer(){
    enum STATUS state = Normal;
    enum STATUS prestate = Normal;

    int p,buf = 0;
    while(1){
        int token = getchar();
        if (token == S_BSL){ /* ESCAPE */
            token = getchar();
            lexbuf[buf]=token;
            buf++;
        }
        switch(state){
            case Normal:  
                switch (token){
                    case S_SQU:
                        state = isStr;
                        continue;
                    case S_DQU:
                        state = isStr2;
                        continue;
                    case S_AMP: /* & amp AND */
                        state = isAmp;
                        continue;
                    case S_BAR: /* | pipe OR*/
                        state = isBar;
                        continue;
                    case S_LT: /* < redirection */
                        state = isLT;
                        continue;
                    case S_GT: /* > redirection */
                        state = isGT;
                        continue;
                    case S_HASH: /* comment */
                        state = isHash;
                        continue;

					case ' ' :
					case '\t':
						continue;

                    case EOF:
                    case '\n':
                        return S_DONE;

                    default:
                        state = isCmd;
                        ungetc(token,stdin);
                        continue;
                }
            case isStr:
                switch(token){
                    case S_SQU:
                        p=lookup(lexbuf);
                        if (p==0) p = insert(lexbuf,S_STR);
                        return symtable[p].token;
                    default:
                        lexbuf[buf]=token;
                        buf++;
                        continue;
                }
            case isStr2:
                switch(token){
                    case S_DQU:
                        p=lookup(lexbuf);
                        if (p==0) p = insert(lexbuf,S_STR);
                        return symtable[p].token;
                    default:
                        lexbuf[buf]=token;
                        buf++;
                        continue;
                }
            case isAmp:
                switch(token){
                    case S_AMP:
                        return S_AND;
                    default:
                        ungetc(token,stdin);
                        return S_AMP;
                }
            case isBar:
                switch(token){
                    case S_BAR:
                        return S_OR;
                    default:
                        ungetc(token,stdin);
                        return S_BAR;
                }
            case isLT:
                switch(token){
                    case S_LT:
                        state = isLTLT;
                        continue;
                    default:
                        ungetc(token,stdin);
                        return S_LT;
                }
            case isLTLT:
                switch(token){
                    case S_LT:
                        return S_LTLTLT;
                    default:
                        ungetc(token,stdin);
                        return S_LTLT;
                }
            case isGT:
                switch(token){
                    case S_GT:
                        state = isGTGT;
                        continue;
                    default:
                        ungetc(token,stdin);
                        return S_GT;
                }
            case isGTGT:
                switch(token){
                    case S_GT:
                        return S_GTGTGT;
                    default:
                        ungetc(token,stdin);
                        return S_GTGT;
                }
            case isHash:
                switch(token){
                    case '\n':
                        ungetc(token,stdin);
                        return ' ';
                    default:
                        continue;
                }
            case isCmd:
                switch(token){
					case S_SEMI :
					case S_AMP :
					case S_BAR :
					case S_LT :
					case S_GT :
					case '\n':
					case ' ' :
					case '\t': 
                        ungetc(token,stdin);
                        p=lookup(lexbuf);
                        if (p==0) p = insert(lexbuf,S_STR);
                        return symtable[p].token;
                    default:
                        lexbuf[buf]=token;
                        buf++;
                        continue;
                }
            default:
                printf("something is wrong in lexer ");
        }
    }
}