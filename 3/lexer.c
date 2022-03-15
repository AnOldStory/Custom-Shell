#include "global.h"

enum STATUS
{
    Normal,
    isDig,
    isSQU,
    isDQU,
    isCmd,
    isAmp,
    isBar,
    isLT,
    isLTLT,
    isGT,
    isGTGT,
    isHash
};

enum STATUS state = Normal; /* state manager */

/* table of token */
#define SYMMAX 100 /* symtable size */
#define STRMAX 999 /* array lexemes size */

struct token lextable[SYMMAX];
int lextable_count = 0;

struct token *insert(char *s, int tok)
{
    state = Normal;
    int len = strlen(s);
    if (len >= STRMAX)
    {
        /* evoke error */
    }
    if (lextable_count + 1 >= SYMMAX)
    {
        /* evoke error */
    }
    lextable[lextable_count].lexptr = save_string(s);
    lextable[lextable_count].type = tok;

    return &lextable[lextable_count++];
}

#define LEXMAX 100
char lexbuf[LEXMAX];

struct token *lexer()
{
    int tempint, p, buf = 0;
    while (1)
    {
        int token = get_buffer();
        if (token == S_BSL)
        { /* ESCAPE */
            insert(get_buffer(), S_STR);
            buf++;
        }
        printf("state : %d token : %d\n", state, token);
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
                if (isdigit(token))
                { /* File Discriptor left value */
                    state = isDig;
                }
                else
                {
                    state = isCmd;
                }
                continue;
            }
        case isDig:
            if (isdigit(token))
            {
                return insert(lexbuf, S_NUM);
            }
            else
            {
                lexbuf[buf++] = token;
                continue;
            }
        case isSQU:
            switch (token)
            {
            case S_SQU:
                lexbuf[buf] = '\0';
                return insert(save_string(lexbuf), S_STR); // string
            default:
                lexbuf[buf++] = token; // string
                continue;
            }
        case isDQU:
            switch (token)
            {
            case S_DQU:
                lexbuf[buf] = '\0';
                return insert(save_string(lexbuf), S_STR); // string
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
                put_buffer(token);
                return insert("&", S_AMP);
            }
        case isBar:
            switch (token)
            {
            case S_BAR:
                return insert("||", S_OR);
            default:
                put_buffer(token);
                return insert("|", S_BAR);
            }
        case isLT:
            switch (token)
            {
            case S_LT:
                state = isLTLT;
                continue;
            default:
                put_buffer(token);
                return insert("<", S_LT);
            }
        case isLTLT:
            switch (token)
            {
            case S_LT:
                return insert("<<<", S_LTLTLT);
            default:
                put_buffer(token);
                return insert("<<", S_LTLT);
            }
        case isGT:
            switch (token)
            {
            case S_GT:
                state = isGTGT;
                continue;
            default:
                put_buffer(token);
                return insert(">", S_GT);
            }
        case isGTGT:
            switch (token)
            {
            case S_GT:
                return insert(">>>", S_GTGTGT);
            default:
                put_buffer(token);
                return insert(">>", S_GTGT);
            }
        case isHash:
            switch (token)
            {
            case '\n':
                put_buffer(token);
            default:
                continue;
            }
        case isCmd:
            switch (token)
            {
            case S_SEMI:
            case S_AMP:
            case S_BAR:
            case S_LT:
            case S_GT:
            case '\n':
            case ' ':
            case '\t':
                put_buffer(token);
                state = Normal;
                lexbuf[buf] = '\0';
                return insert(save_string(lexbuf), S_STR); // string
            default:
                lexbuf[buf++] = token;
                continue;
            }
        default:
            printf("something is wrong in lexer ");
        }
    }
}
