#include "string.h"

/**
 *  Memory
 * */

char *save_string(char *s)
{
    /**
     *  return string with malloc
     *  same as strcpy((char *)malloc(1 + strlen(s)), s);
     */
    return strdup(s);
}