#include "global.h"

struct symbol lookahead;

struct cmd
{
    int argc;
    char *argv[];
    /* data */
};

/**
 * START -> PROGRAM
 *
 * PROGRAM ->  CMD MORE || CMD
 * MORE ->  ARG || OPTION || e
 * PIPE ->  <
 *          <<
 *          <<<
 *          >
 *          >>
 *          >>>
 */

void parse()
{
    lookahead = *lexer();
    while (lookahead.token != S_DONE)
    { /* until end */
        start();
        lookahead = *lexer();
    }
}

void start()
{
    int t;
    while (1)
    {
        switch (lookahead.token)
        {
        case S_SQU: /* ' */
            match("'");
            match("'");
            continue;
        case S_DQU: /* " */
            match("\"");
            match("\"");
            continue;
        case S_SEMI:   /* ; */
        case S_LT:     /* < */
        case S_GT:     /* > */
        case S_BAR:    /* | */
        case S_AND:    /* && */
        case S_OR:     /* || */
        case S_LTLT:   /* << */
        case S_LTLTLT: /* <<< */
        case S_GTGT:   /* >> */
        case S_GTGTGT: /* >>> */

        case S_VAR:
            emit(lookahead);
        default:
            emit(lookahead);
            return;
        }
    }
}

/* default */
// void expr(){
//     int t;
//     term();
//     while(1){
//         switch(lookahead.token){
//             case '+': case '-':
//                 t = lookahead;
//                 match(lookahead); term(); emit(t, NONE);
//             continue;
//             default: return;
//         }
//     }
// }

// void term(){
//     int t;
//     factor();
//     while(1){
//         switch (lookahead){
//             case '+': case '-': case '*': case '/':
//                 t = lookahead;
//                 match(lookahead); factor(); emit(t, NONE);
//                 continue;
//             default: return;
//         }
//     }
// }

// void factor(){
//     switch(lookahead){
//         case '(':
//             match('('); expr(); match(')'); break;
//         // case NUM:
//         //     emit(NUM, tokenval); match(NUM); break;
//         // case S_ID:
//         //     emit(ID, tokenval); match(ID); break;
//         default:
//             printf("error in %d lookahead",lookahead);
//             error("syntac error in factor");
//     }
// }

void match(int t)
{
    if (lookahead.token == t)
        lookahead = *lexer();
    else
        error("syntax error in match");
}

void match_t(int t)
{
}