#include "./global.h"

// int size = 0; /* size of buffer */

// struct token token_list[MAX_TOK]; /* tokens */
// int lastentry = 0;                /* last token_list */

// enum STATUS /* state list */
// {
//     Normal,
//     Single_Word,
//     Double_Word
// };

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
    // printf("%s", buffer);
    // printf("buffer %c\n ", buffer[buffer_cursor]);
    // printf("%d %d \n", buffer_cursor, buffer_size);
    // printf("%c", buffer[buffer_cursor]);
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

Command *cmd[100];

Command **run_parse(char *inputBuffer, int *cmd_size) // char *args[], int *args_size
{
    init_buffer(inputBuffer);

    int flags = O_CREAT | O_WRONLY;

    cmd[*cmd_size] = (Command *)malloc(sizeof(Command));

    /* parsed info */
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    int args_size = 0;            /* arguments size */

    Token token = *lexer(); /* token */
    // args[args_size] = token.lexptr; /* argv first cmd duplicated  */
    // args_size++;

    while (1)
    {
        switch (token.type)
        {
        case S_DONE:
            args[args_size++] = NULL;
            cmd[*cmd_size]->argv = args;
            cmd[*cmd_size]->argc = args_size;
            return cmd;
        /* | */
        case S_BAR:
            args[args_size] = NULL;
            cmd[*cmd_size]->argc = args_size;
            (*cmd_size)++;
            cmd[*cmd_size] = (Command *)malloc(sizeof(Command));
            break;
        /* background */
        case S_AMP:
            /* TODO: background */
            break;
        /* handle redirection */
        case S_LT:
            // <
            cmd[*cmd_size]->file_descriptor[0].fd = O_RDONLY;
            cmd[*cmd_size]->file_descriptor[0].name = lexer()->lexptr;
            break;
        case S_LTLT:
            // <<
            /* TODO : Multi line  */
            break;
        case S_LTLTLT:
            // <<<
            cmd[*cmd_size]->file_descriptor[0].fd = O_RDONLY;
            cmd[*cmd_size]->file_descriptor[0].name = lexer()->lexptr;
            /* TODO : string */
            break;
        case S_GT:
            // >
            cmd[*cmd_size]->file_descriptor[1].fd = flags | O_EXCL;
            cmd[*cmd_size]->file_descriptor[1].name = lexer()->lexptr;
            break;
        case S_GTGT:
            // >>
            cmd[*cmd_size]->file_descriptor[1].fd = flags | O_APPEND;
            cmd[*cmd_size]->file_descriptor[1].name = lexer()->lexptr;
            break;
        case S_GTBAR:
            // >|
            cmd[*cmd_size]->file_descriptor[1].fd = flags | O_TRUNC;
            cmd[*cmd_size]->file_descriptor[1].name = lexer()->lexptr;
            break;
        default:
            args[args_size++] = token.lexptr; /* assign token to args */
        }

        printf("\nf_ token : %s Type : %d Ptr: %p \n", token.lexptr, token.type, token.lexptr);
        token = *lexer();
        printf("s_ token : %s Type : %d Ptr: %p \n\n", token.lexptr, token.type, token.lexptr);
    }
    // printf("token : %s Type : %d Ptr: %p \n", token.lexptr, token.type, token.lexptr);
    // args[*args_size] = token.lexptr; /* assign token to args */
    // (*args_size)++;
}