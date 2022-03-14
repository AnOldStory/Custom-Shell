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
        printf("token : %s Type : %d Ptr: %p \n", token.lexptr, token.type, token.lexptr);
        args[*args_size] = token.lexptr; /* assign token to args */
        *args_size++;
    }
    args[*args_size] = 0;
}

// struct token lexer()
// {
//     char lexbuf[MAX_BUF]; /* lexer buffer */
//     int type = NONE;      /* lexer type  */

//     size = 0;       /* clear buffer size */
//     state = Normal; /* clear state */

//     while (1)
//     {
//         switch (state)
//         {
//         case Normal:
//             switch (redoLex(lexbuf, get_buffer())) /* read one letter */
//             {
//             /* escape word */
//             case '\'': /* ' */
//                 state = Single_Word;
//                 skipLex(lexbuf); /* feedback to for string */
//                 continue;
//             case '"': /* " */
//                 state = Double_Word;
//                 skipLex(lexbuf); /* feedback to for string */
//                 continue;
//             /* delimeter */
//             case ' ':
//             case '\t':
//                 skipLex(lexbuf); /* skip trash letter */
//                 return insert(lexbuf, S_STR);
//             case '\n':
//             case EOS:
//                 if (size == 1) /* check single token */
//                 {
//                     skipLex(lexbuf);
//                     return insert(lexbuf, S_DONE);
//                 }
//                 else
//                 {
//                     undoLex(lexbuf);
//                     return insert(lexbuf, S_STR);
//                 }
//             case '>':
//             case '<':
//             case '|':
//             case '&':
//             case ';':
//             case '(':
//             case ')':
//             case '{':
//             case '}':

//             default:
//                 continue;
//             }
//             break;
//         case Single_Word:
//             switch (redoLex(lexbuf, get_buffer()))
//             {
//             case '\'': /* ' */
//                 state = Normal;
//                 skipLex(lexbuf);
//                 continue;
//             default:
//                 continue;
//             }
//             break;
//         case Double_Word:
//             switch (redoLex(lexbuf, get_buffer()))
//             {
//             case '"': /* "" */
//                 state = Normal;
//                 skipLex(lexbuf);
//                 continue;
//             default:
//                 continue;
//             }
//             break;
//         default:
//             error_c("Unexepected parser state");
//         }
//     }
// }

// if (token & 0x80)
//     redoLex(get_buffer()); /* if unicode */

// /* Read One Letter */
// int redoLex(char lexbuf[], int token)
// {
//     lexbuf[size] = token;
//     size++;
//     return token;
// }

// /* Skip Trash Letter */
// void skipLex(char lexbuf[])
// {
//     size--;
//     lexbuf[size] = NONE;
// }

// /* Feedback one Letter */
// void undoLex(char lexbuf[])
// {
//     size--;
//     put_buffer();
//     lexbuf[size] = NONE;
// }

// struct token insert(char s[], int stype)
// {
//     // printf("insert : %s",s);
//     int len = strlen(s);                             /* input s's length */
//     char *lexeme_p = (char *)c_p(len, sizeof(char)); /* lexeme (token.lexptr) */

//     if (lastentry + 1 >= MAX_TOK)
//         error_c("token array full"); /* token array full*/

//     lastentry = lastentry + 1;
//     token_list[lastentry].type = stype; /* token type */
//     token_list[lastentry].lexptr = lexeme_p;

//     strcpy(token_list[lastentry].lexptr, s);
//     return token_list[lastentry];
// }