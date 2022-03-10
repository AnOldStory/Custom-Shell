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

/* symbol.c */
struct symbol {
    char *lexptr;
    int token;
};

struct symbol symtable[]; /* token */

struct symbol *lexer();
struct symbol *lookup(char s[],int tok);
struct symbol *lookup_t(int tok);
void switcher(struct symbol *s, int t);

/* parser.c */

#endif