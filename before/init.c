#include "global.h"

struct symbol tokens[]={
    "T_DONE", S_DONE,
    "T_PROG", S_PROG,
    "T_PIPE", S_PIPE,
    "T_ARG", S_ARG ,
    "T_OPT", S_OPT ,
    // "T_COM", S_COM ,
    // "T_STR", S_STR ,
    // "T_VAR", S_VAR ,
    // "T_NUM", S_NUM ,
    0,    0
};

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

    printf("lexer variable setting \n");
    for (p=keywords; p->token; p++)
        insert(p->lexptr, p->token);

    printf("parser variable setting \n");
    for (p=tokens; p->token; p++)
        insert(p->lexptr, p->token);
    
    printf("init end\n");
}
