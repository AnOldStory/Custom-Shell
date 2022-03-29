#include "./global.h"

int buffer_cursor;
int buffer_size;
char *buffer;

/* handle input like buffer */
void init_buffer(char *init_buffer)
{
    buffer_cursor = 0;
    buffer_size = strlen(init_buffer);
    buffer = init_buffer;
}

int get_buffer()
{
    if (buffer_cursor < buffer_size)
        return buffer[buffer_cursor++];
    else
        return EOF;
}

void put_buffer()
{
    if (buffer_cursor > 0)
        buffer_cursor--;
}

void run_parse(char *inputBuffer, Command *cmd, int *cmd_size) // char *args[], int *args_size
{
    init_buffer(inputBuffer);
    init();

    /* init parse */
    int flags = O_CREAT | O_WRONLY;

    char **args = (char **)malloc(sizeof(char *) * (MAX_LINE / 2 + 1));
    int argc = 0; /* arguments size */

    cmd[*cmd_size].fd_info = (FileDescriptor *)malloc(sizeof(FileDescriptor) * 2);

    cmd[*cmd_size].fd_info[READ_END].flag = 0;
    cmd[*cmd_size].fd_info[READ_END].name = NULL;

    cmd[*cmd_size].fd_info[WRITE_END].flag = 0;
    cmd[*cmd_size].fd_info[WRITE_END].name = NULL;

    cmd[*cmd_size].is_back = 0;

    Token token = *lexer(); /* token */

    while (1)
    {
        switch (token.type)
        {
        case S_DONE:
            args[argc] = NULL;
            cmd[*cmd_size].argv = args;
            cmd[*cmd_size].argc = argc;
            (*cmd_size)++;
            return;
        /* | */
        case S_BAR:
            args[argc] = NULL;
            cmd[*cmd_size].argv = args;
            cmd[*cmd_size].argc = argc;
            (*cmd_size)++;

            /* init parse */
            flags = O_CREAT | O_WRONLY;

            args = (char **)malloc(sizeof(char *) * (MAX_LINE / 2 + 1));
            argc = 0; /* arguments size */

            cmd[*cmd_size].fd_info = (FileDescriptor *)malloc(sizeof(FileDescriptor) * 2);

            cmd[*cmd_size].fd_info[READ_END].flag = 0;
            cmd[*cmd_size].fd_info[READ_END].name = NULL;

            cmd[*cmd_size].fd_info[WRITE_END].flag = 0;
            cmd[*cmd_size].fd_info[WRITE_END].name = NULL;

            cmd[*cmd_size].is_back = 0;
            break;
        /* background */
        case S_AMP:
            cmd[*cmd_size].is_back = 1;
            args[argc] = NULL;
            cmd[*cmd_size].argv = args;
            cmd[*cmd_size].argc = argc;
            (*cmd_size)++;

            /* init parse */
            flags = O_CREAT | O_WRONLY;

            args = (char **)malloc(sizeof(char *) * (MAX_LINE / 2 + 1));
            argc = 0; /* arguments size */

            cmd[*cmd_size].fd_info = (FileDescriptor *)malloc(sizeof(FileDescriptor) * 2);

            cmd[*cmd_size].fd_info[READ_END].flag = 0;
            cmd[*cmd_size].fd_info[READ_END].name = NULL;

            cmd[*cmd_size].fd_info[WRITE_END].flag = 0;
            cmd[*cmd_size].fd_info[WRITE_END].name = NULL;

            cmd[*cmd_size].is_back = 0;
            /* TODO: background */
            break;
        /* handle redirection */
        case S_LT:
            // <
            cmd[*cmd_size].fd_info[READ_END].flag = O_RDONLY;
            cmd[*cmd_size].fd_info[READ_END].name = lexer()->lexptr;
            break;
        case S_LTLT:
            // <<
            /* TODO : Multi line  */
            break;
        case S_LTLTLT:
            // <<<
            cmd[*cmd_size].fd_info[READ_END].flag = O_RDONLY;
            cmd[*cmd_size].fd_info[READ_END].name = lexer()->lexptr;
            /* TODO : string */
            break;
        case S_GT:
            // >
            cmd[*cmd_size].fd_info[WRITE_END].flag = flags | O_EXCL;
            cmd[*cmd_size].fd_info[WRITE_END].name = lexer()->lexptr;
            break;
        case S_GTGT:
            // >>
            cmd[*cmd_size].fd_info[WRITE_END].flag = flags | O_APPEND;
            cmd[*cmd_size].fd_info[WRITE_END].name = lexer()->lexptr;
            break;
        case S_GTBAR:
            // >|
            cmd[*cmd_size].fd_info[WRITE_END].flag = flags | O_TRUNC;
            cmd[*cmd_size].fd_info[WRITE_END].name = lexer()->lexptr;
            break;
        default:
            args[argc++] = token.lexptr; /* assign token to args */
        }
        // printf("%s %d \n", token.lexptr, token.type);
        token = *lexer();
    }
}