#include "global.h"

void emit(struct symbol t){
    switch(t.token){
        /* parser variable */
        case S_SQU   :
        case S_DQU   :
        case S_HASH  :
        case S_DOL   :
        case S_AMP   :
        case S_SEMI  :
        case S_LT    :
        case S_GT    :
        case S_BSL   :
        case S_BAR   :
        case S_AND   :
        case S_OR    :
        case S_LTLT  :
        case S_LTLTLT:
        case S_GTGT  :
        case S_GTGTGT:
            printf("%s ", t.lexptr); break;
        case S_DONE:
            break;
        case S_PROG:
        case S_PIPE:
        case S_ARG :
        case S_OPT :
        case S_COM :
        case S_STR :
        case S_VAR :
        case S_NUM :

        default:
            printf("%s[%d] ", t.lexptr, t.token);
    }
}