#ifndef __PARSER_H__
#define __PARSER_H__

#include <fcntl.h>  /* open */
#include <stdlib.h> /* malloc */

#include "lexer.h"

#define READ_END 0  /* file descriptor IN */
#define WRITE_END 1 /* file descriptor OUT */

#define MAX_LINE 80 /* The maximum length command */

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

void init_buffer(char *init_buffer);
int get_buffer();
void put_buffer();
void run_parse(char *inputBuffer, Command *cmd, int *cmd_size); // , char *args[], int *args_size

#endif