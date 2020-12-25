#include "global.h"

void error(char *m) /* handle error */
{
    fprintf(stderr, "line : %s \n", m);
    exit(1);
}