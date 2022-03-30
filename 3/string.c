#include "string.h"

/**
 *  Memory
 * */

char *save_string(char *s)
{
    // return strcpy((char *)malloc(1 + strlen(s)), s);
    // if (strdup(s) == NULL)
    // {
    //     handleErr_msg("cant alloc -> saveString");
    // }
    return strdup(s);
}