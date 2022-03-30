#ifndef __LEXER_H__
#define __LEXER_H__

#include "string.h"
#include "error.h"

/* lexer variable */
#define S_DONE 999 /* end of the command */
#define S_STR 998  /* String */

#define S_PROG 998 /* program */
#define S_PIPE 997 /* include pipe */
#define S_ARG 996  /* argument */
#define S_OPT 995  /* option */
#define S_COM 994  /* comment */
#define S_VAR 992  /* Variable */
#define S_NUM 991  /* number */

/* lexer string */
#define S_DQU 34     /* " */
#define S_HASH 35    /* # */
#define S_DOL 36     /* $ */
#define S_AMP 38     /* & */
#define S_SQU 39     /* ' */
#define S_SEMI 59    /* ; */
#define S_LT 60      /* < */
#define S_GT 62      /* > */
#define S_BSL 92     /* \ */
#define S_BAR 124    /* | */
#define S_AND 256    /* && */
#define S_OR 257     /* || */
#define S_LTLT 258   /* << */
#define S_LTLTLT 259 /* <<< */
#define S_GTGT 260   /* >> */
// #define S_GTGTGT 261 /* >>> */
#define S_GTBAR 262 /* >| */

#define EOF (-1)

/* table of token */
#define SYMMAX 999 /* symtable size */
#define STRMAX 999 /* array lexemes size */

typedef struct TokenStruct
{
    char *lexptr;
    int type;
} Token;

void init_lexer();
Token *lexer();
Token *insert(char s[], int tok);

#endif