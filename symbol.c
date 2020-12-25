#include "global.h"

#define SYMMAX 100 /* symtable size */
#define STRMAX 999 /* array lexemes size */

char lexemes[STRMAX];
int lastchar = -1; /* last lexemes */

struct symbol symtable[SYMMAX];
int lastentry = 0; /* last symtable */

int lookup(char s[]){
    int p;
    for(p = lastentry; p>0; p = p - 1)
        if (strcmp(symtable[p].lexptr,s) == 0) return p;
    return 0;
}

int getValue(int token){
    int p;
    for(p = lastentry; p>0; p = p - 1)
        if (symtable[p].token == token) return p;
    return 0;
}

int insert(char s[],int tok){
    int len;
    len = strlen(s);

    if(lastentry + 1 >= SYMMAX) error("symbol table full"); /* symtable full*/
    if(lastchar + len + 1> STRMAX) error("lexemes array full"); /* array lexemes full*/
    if(tok == S_STR) tok = lastentry + 1000;
    lastentry = lastentry + 1;
    symtable[lastentry].token = tok;
    symtable[lastentry].lexptr = &lexemes[lastchar + 1];
    lastchar = lastchar + len + 1;

    strcpy(symtable[lastentry].lexptr, s);
    return lastentry;
}