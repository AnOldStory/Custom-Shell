#ifndef __GLOBAL_H__
#define __GLOBAL_H__

// #pragma pack(8)

#include <stdio.h>     /* standard input output */
char *cuserid(char *); /* avoid compiler warning  */
#include <ctype.h>     /* check input type - lexer */
#include <fcntl.h>     /* open */
#include <stdlib.h>    /* exit - error, main */
#include <string.h>    /* strlen - symbol */
#include <unistd.h>    /* symbol constant */
// #include <sys/wait.h>  /* wait pid  exit code */
int waitpid();     /* avoid compiler warning */
#include <errno.h> /* print error */

#define MAX_LINE 80      /* The maximum length command */
#define MAX_HOSTNAME 256 /* maximum length hostname */
#define MAX_USERNAME 256 /* maxumum length username */
#define MAX_CWD 256      /* maximum length Current Working Directory */

#define MAX_BUF 999 /* array lexemes size */
#define MAX_TOK 100 /* token counter size */

#define NONE '\0' /* NUL */
#define EOS '\0'  /* NUL */

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

/* main.c */
#define READ_END 0
#define WRITE_END 1

/* lexer.c */
typedef struct TokenStruct
{
    char *lexptr;
    int type;
} Token;

/* parser.c */
typedef struct FileDescriptorStruct
{
    char *name;
    int flag;
    int fd;
} FileDescriptor;

typedef struct CommandStruct
{
    FileDescriptor *fd_info;
    char **argv;
    int argc;
    int is_back;
} Command;

/* string.c */
char *save_string(char *);

/* error.c */
void handleErr();
void handleErr_msg(char *msg);
void error_int(int);
void error_msg(char *);

/* parser.c */
void init_buffer(char *init_buffer);
int get_buffer();
void put_buffer();
void run_parse(char *inputBuffer, Command *cmd, int *cmd_size); // , char *args[], int *args_size

/* lexer.c */
void init();
Token *lexer();
Token *insert(char s[], int tok);

/* init.c */
char *get_username();
char *get_hostname();
char *get_cwd();

/* built_in_commands */
int check_cmd(char *args[], int args_size);

/* linked_list.c */
typedef struct NodeStruct
{
    struct Node *next;
    int index;
    pid_t pid;
} Node;

Node *link_add(Node *previous, int index, int pid);

void link_remove(Node *previous);

#endif