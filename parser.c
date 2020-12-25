#include "global.h"

int lookahead;

void expr();
void term();
void factor();
void match();

/**
 * START -> PROGRAM || PROGRAM PIPE || e
 * PROGRAM -> CMD MORE || CMD
 * MORE -> ARG || OPTION || e
 * PIPE
*/

void parse(){
    lookahead = lexer();
    while (lookahead != S_DONE){ /* until end */
        start();
        lookahead = lexer();
    }
}

void start(){
    int t;
    switch(lookahead){
        // case S_VAR:
        //     emit(S_VAR,tokenval);
        // case S_PROG:
        //     break;
        // case S_OPT:
        //     break;
        // case S_PIPE:
        //     break;
        default:
            emit(lookahead,tokenval);
            return;
    }
}



/* default */
void expr(){
    int t;
    term();
    while(1){
        switch(lookahead){
            case '+': case '-':
                t = lookahead;
                match(lookahead); term(); emit(t, NONE);
            continue;
            default: return;
        }
    }
}

void term(){
    int t;
    factor();
    while(1){
        switch (lookahead){
            case '+': case '-': case '*': case '/':
                t = lookahead;
                match(lookahead); factor(); emit(t, NONE);
                continue;
            default: return;
        }
    }
}

void factor(){
    switch(lookahead){
        case '(': 
            match('('); expr(); match(')'); break;
        // case NUM:
        //     emit(NUM, tokenval); match(NUM); break;
        // case S_ID:
        //     emit(ID, tokenval); match(ID); break;
        default:
            printf("error in %d lookahead",lookahead);
            error("syntac error in factor");
    }
}

void match(int t){
    if(lookahead == t) lookahead = lexer();
    else error("syntax error in match");
}