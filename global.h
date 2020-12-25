#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h> /* standard input output */
#include <ctype.h> /* check input type - lexer */
#include <stdlib.h> /* exit - error, main */
#include <string.h> /* strlen - symbol */

#define TSIZE 128 /* token size */
#define BSIZE 128 /* buffer size */
#define NONE -1
#define EOS '\0' /* null */

// #define S_NUM 256
// #define S_ID 257


/* lexer variable */
#define S_DONE 999 /* end of the command */
#define S_PROG 998 /* program */
#define S_PIPE 997 /* include pipe */
#define S_ARG  996 /* argument */
#define S_OPT  995 /* option */
#define S_COM  994 /* comment */
#define S_STR  993 /* string */
#define S_VAR  992 /* Variable */
#define S_NUM  991 /* number */

/* parser variable */
#define S_SQU     33  /* ' */
#define S_DQU     34  /* " */
#define S_HASH    35  /* # */
#define S_DOL     36  /* $ */
#define S_AMP     38  /* & */
#define S_SEMI    59  /* ; */
#define S_LT      60  /* < */
#define S_GT      62  /* > */
#define S_BSL     92  /* \ */
#define S_BAR     124 /* | */
#define S_AND     256 /* && */
#define S_OR      257 /* || */
#define S_LTLT    258 /* << */
#define S_LTLTLT  259 /* <<< */
#define S_GTGT    260 /* >> */
#define S_GTGTGT  261 /* >>> */

/**
 *  stdin = 0 stdout=1 stderr=2
 *  > stdout 
 *  &> both stdout and stderr
 *  >> append
 * 
 *  < file stdin
 *  << multi stdin
 *  <<< string stdin
 * 
 *  | result pass
 * 
 *  ; - 앞의 명령어가 실패해도 다음 명령어가 실행
 *  && - 앞의 명령어가 성공했을 때 다음 명령어가 실행
 *  & - 앞의 명령어를 백그라운드로 돌리고 동시에 뒤의 명령어를 실행
*/

int tokenval;

struct symbol {
    char *lexptr;
    int token;
};

struct symbol symtable[];


#endif