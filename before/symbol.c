#include "global.h"

#define SYMMAX 100 /* symtable size */
#define STRMAX 999 /* array lexemes size */

char lexemes[STRMAX];
int lastchar = -1; /* last lexemes */

struct symbol symtable[SYMMAX];
int lastentry = 0; /* last symtable */

struct symbol *insert(char s[], int tok)
{
    int len = strlen(s);

    if (lastentry + 1 >= SYMMAX)
        error("symbol table full"); /* symtable full*/
    if (lastchar + len + 1 > STRMAX)
        error("lexemes array full"); /* array lexemes full*/
    lastentry = lastentry + 1;
    symtable[lastentry].token = tok;
    symtable[lastentry].lexptr = &lexemes[lastchar + 1];
    lastchar = lastchar + len + 1;

    strcpy(symtable[lastentry].lexptr, s);
    return &symtable[lastentry];
}

struct symbol *lookup(char s[], int tok)
{
    int p;
    for (p = lastentry; p > 0; p = p - 1)
        if (strcmp(symtable[p].lexptr, s) == 0)
            return &symtable[p];
    return insert(s, tok);
}

struct symbol *lookup_t(int tok)
{ /* for keyword */
    int p;
    for (p = lastentry; p > 0; p = p - 1)
        if (symtable[p].token == tok)
            return &symtable[p];
};

void switcher(struct symbol *s, int t)
{
    if (s->token > 500)
    {
        s->token = t;
    }
    else
    {
        error("switcher err in symbol");
    }
};
