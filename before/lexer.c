#include "global.h"

enum STATUS { Normal, isDig, isStr, isStr2, isCmd, isAmp, isBar, isLT, isLTLT, isGT, isGTGT, isHash };

char lexbuf[BSIZE];


enum STATUS state = Normal;


struct symbol *lexer(){
    int tempint,p,buf = 0;
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
                    case '\n':
						continue;

                    case EOF:
                        return lookup_t(S_DONE);

                    default:
                        ungetc(token,stdin);
                        if(isdigit(token)){ /* File Discriptor left value */
                            state = isDig;
                        } else {
                            state = isCmd;
                        }
                        continue;
                }
            case isDig:
                scanf("%d",&tempint);
                sprintf(lexbuf,"%d",tempint);
                return lookup(lexbuf,S_NUM);
            case isStr:
                switch(token){
                    case S_SQU:
                        return lookup(lexbuf,S_STR);
                    default:
                        lexbuf[buf]=token;
                        buf++;
                        continue;
                }
            case isStr2:
                switch(token){
                    case S_DQU:
                        return lookup(lexbuf,S_STR);
                    default:
                        lexbuf[buf]=token;
                        buf++;
                        continue;
                }
            case isAmp:
                switch(token){
                    case S_AMP:
                        return lookup_t(S_AND);
                    default:
                        ungetc(token,stdin);
                        return lookup_t(S_AMP);
                }
            case isBar:
                switch(token){
                    case S_BAR:
                        return lookup_t(S_OR);
                    default:
                        ungetc(token,stdin);
                        return lookup_t(S_BAR);
                }
            case isLT:
                switch(token){
                    case S_LT:
                        state = isLTLT;
                        continue;
                    default:
                        ungetc(token,stdin);
                        return lookup_t(S_LT);
                }
            case isLTLT:
                switch(token){
                    case S_LT:
                        return lookup_t(S_LTLTLT);
                    default:
                        ungetc(token,stdin);
                        return lookup_t(S_LTLT);
                }
            case isGT:
                switch(token){
                    case S_GT:
                        state = isGTGT;
                        continue;
                    default:
                        ungetc(token,stdin);
                        return lookup_t(S_GT);
                }
            case isGTGT:
                switch(token){
                    case S_GT:
                        return lookup_t(S_GTGTGT);
                    default:
                        ungetc(token,stdin);
                        return lookup_t(S_GTGT);
                }
            case isHash:
                switch(token){
                    case '\n':
                        ungetc(token,stdin);
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
                        return lookup(lexbuf,S_STR);
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