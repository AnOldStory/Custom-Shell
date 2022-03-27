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

Command cmd[100];

void run_parse(char *inputBuffer, Command *cmd, int *cmd_size) // char *args[], int *args_size
{
    init_buffer(inputBuffer);
    // printf("%p,hello\n", cmd);
    /* init parse */
    int flags = O_CREAT | O_WRONLY;

    char **args = (char **)malloc(sizeof(char *) * (MAX_LINE / 2 + 1));
    int argc = 0; /* arguments size */

    // cmd[*cmd_size] = (Command *)malloc(sizeof(Command));

    cmd[*cmd_size].fd = (FileDescriptor *)malloc(sizeof(FileDescriptor) * 2);

    cmd[*cmd_size].fd[READ_END].flag = 0;
    cmd[*cmd_size].fd[READ_END].name = NULL;

    cmd[*cmd_size].fd[WRITE_END].flag = 0;
    cmd[*cmd_size].fd[WRITE_END].name = NULL;

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

            // cmd[*cmd_size] = (Command *)malloc(sizeof(Command));

            cmd[*cmd_size].fd = (FileDescriptor *)malloc(sizeof(FileDescriptor) * 2);

            cmd[*cmd_size].fd[READ_END].flag = 0;
            cmd[*cmd_size].fd[READ_END].name = NULL;

            cmd[*cmd_size].fd[WRITE_END].flag = 0;
            cmd[*cmd_size].fd[WRITE_END].name = NULL;
            break;
        /* background */
        case S_AMP:
            /* TODO: background */
            break;
        /* handle redirection */
        case S_LT:
            // <
            cmd[*cmd_size].fd[READ_END].flag = O_RDONLY;
            cmd[*cmd_size].fd[READ_END].name = lexer()->lexptr;
            break;
        case S_LTLT:
            // <<
            /* TODO : Multi line  */
            break;
        case S_LTLTLT:
            // <<<
            cmd[*cmd_size].fd[READ_END].flag = O_RDONLY;
            cmd[*cmd_size].fd[READ_END].name = lexer()->lexptr;
            /* TODO : string */
            break;
        case S_GT:
            // >
            cmd[*cmd_size].fd[WRITE_END].flag = flags | O_EXCL;
            cmd[*cmd_size].fd[WRITE_END].name = lexer()->lexptr;
            break;
        case S_GTGT:
            // >>
            cmd[*cmd_size].fd[WRITE_END].flag = flags | O_APPEND;
            cmd[*cmd_size].fd[WRITE_END].name = lexer()->lexptr;
            break;
        case S_GTBAR:
            // >|
            cmd[*cmd_size].fd[WRITE_END].flag = flags | O_TRUNC;
            cmd[*cmd_size].fd[WRITE_END].name = lexer()->lexptr;
            break;
        default:
            args[argc++] = token.lexptr; /* assign token to args */
        }

        printf("\nf_ token : %s Type : %d Ptr: %p \n", token.lexptr, token.type, token.lexptr);
        token = *lexer();
        printf("s_ token : %s Type : %d Ptr: %p \n\n", token.lexptr, token.type, token.lexptr);
    }
}