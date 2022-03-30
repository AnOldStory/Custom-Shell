#include "lexer.h"
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

enum STATUS
{
    Normal,
    isSQU,
    isDQU,
    isCmd,
    isAmp,
    isBar,
    isLT,
    isLTLT,
    isGT,
    isHash
};

enum STATUS state = Normal; /* state manager */

Token lextable[SYMMAX];
int lextable_count = 0;

void init_lexer()
{
    lextable_count = 0;
}

Token *insert(char *s, int tok)
{
    // printf("inserted : %s %d\n", s, tok);
    state = Normal;
    int len = strlen(s);
    if (len >= STRMAX)
    {
        error_msg("over STRMAX");
        /* evoke error */
    }
    if (lextable_count + 1 >= SYMMAX)
    {
        error_msg("over lextable_count");
        /* evoke error */
    }
    lextable[lextable_count].lexptr = save_string(s);
    // (char *)malloc(1 + strlen(s))
    lextable[lextable_count].type = tok;

    return &lextable[lextable_count++];
}

#define LEXMAX 100
char lexbuf[LEXMAX];

Token *lexer()
{
    int tempint, p, buf = 0;
    while (1)
    {
        int token = get_buffer();
        // if (token == S_BSL)
        // { /* ESCAPE */
        //     insert(get_buffer(), S_STR);
        //     buf++;
        // }
        // printf("state : %d token : %d\n", state, token);
        switch (state)
        {
        case Normal:
            switch (token)
            {
            case S_SQU:
                state = isSQU;
                continue;
            case S_DQU:
                state = isDQU;
                continue;
            case S_AMP: /* & amp AND */
                state = isAmp;
                continue;
            case S_BAR: /* | pipe OR*/
                state = isBar;
                continue;
            case S_LT: /* < redirection */
                state = isLT;
                continue;
            case S_GT: /* > redirection */
                state = isGT;
                continue;
            case S_HASH: /* comment */
                state = isHash;
                continue;

            case ' ':
            case '\t':
            case '\n':
                continue;

            case EOF:
                return insert("999", S_DONE);

            default:
                put_buffer();
                state = isCmd;
                continue;
            }
        case isSQU:
            switch (token)
            {
            case S_SQU:
                lexbuf[buf] = '\0';
                return insert(lexbuf, S_STR); // string
            default:
                lexbuf[buf++] = token; // string
                continue;
            }
        case isDQU:
            switch (token)
            {
            case S_DQU:
                lexbuf[buf] = '\0';
                return insert(lexbuf, S_STR); // string
            default:
                lexbuf[buf++] = token; // string
                continue;
            }
        case isAmp:
            switch (token)
            {
            case S_AMP:
                return insert("&&", S_AND);
            default:
                put_buffer();
                return insert("&", S_AMP);
            }
        case isBar:
            switch (token)
            {
            case S_BAR:
                return insert("||", S_OR);
            default:
                put_buffer();
                return insert("|", S_BAR);
            }
        case isLT:
            switch (token)
            {
            case S_LT:
                state = isLTLT;
                continue;
            default:
                return insert("<", S_LT);
            }
        case isLTLT:
            switch (token)
            {
            case S_LT:
                return insert("<<<", S_LTLTLT);
            default:
                put_buffer();
                return insert("<<", S_LTLT);
            }
        case isGT:
            switch (token)
            {
            case S_BAR:
                put_buffer();
                return insert(">|", S_GTBAR);
            case S_GT:
                put_buffer();
                return insert(">>", S_GTGT);
            default:
                put_buffer();
                return insert(">", S_GT);
            }
        case isHash:
            switch (token)
            {
            case '\n':
                put_buffer();
            default:
                continue;
            }
        case isCmd:
            switch (token)
            {
            // case S_SEMI:
            case S_AMP:
            case S_BAR:
            case S_LT:
            case S_GT:
            case '\n':
            case ' ':
            case '\t':
                put_buffer();
                lexbuf[buf] = '\0';
                return insert(lexbuf, S_STR); // string
            default:
                lexbuf[buf++] = token;
                continue;
            }
        default:
            printf("something is wrong in lexer ");
        }
    }
}
