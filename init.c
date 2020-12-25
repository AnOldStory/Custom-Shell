#include "global.h"

struct symbol keywords[]={
    "'",  S_SQU ,
    "\"", S_DQU ,
    "#",  S_HASH,
    "$",  S_DOL ,
    "&",  S_AMP ,
    ";",  S_SEMI,
    "<",  S_LT  ,
    ">",  S_GT  ,
    "\\", S_BSL ,
    "|",  S_BAR ,
    "&&", S_AND   ,
    "||", S_OR    ,
    "<<", S_LTLT  ,
    "<<<",S_LTLTLT,
    ">>", S_GTGT  ,
    ">>>",S_GTGTGT,
    0,    0
};

void compiler_init(){
    struct symbol *p;
    for (p=keywords; p->token; p++)
        insert(p->lexptr, p->token);
    printf("init end\n");
}
