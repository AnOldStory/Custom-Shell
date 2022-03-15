#include "global.h"
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

void run_parse(char *inputBuffer, char *args[], int *args_size)
{
    init_buffer(inputBuffer);

    struct token token; /* token */
    while ((token = *lexer()).type != S_DONE)
    {
        // printf("token : %s Type : %d Ptr: %p \n", token.lexptr, token.type, token.lexptr);
        args[*args_size] = token.lexptr; /* assign token to args */
        (*args_size)++;
    }
    // printf("token : %s Type : %d Ptr: %p \n", token.lexptr, token.type, token.lexptr);
    // args[*args_size] = token.lexptr; /* assign token to args */
    // (*args_size)++;
    args[*args_size] = 0;
}