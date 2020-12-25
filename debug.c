#include "global.h"

void emit(int t){
    int val = getValue(t);
    switch(t){
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
            printf("%s ", symtable[val].lexptr); break;
        default:
            printf("%s[%d] ", symtable[val].lexptr, t);
    }
}