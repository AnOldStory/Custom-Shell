#include "global.h"

/**
 *  RUNNER
 **/

void handleErr()
{
    perror("Error");
    // exit(1);
}

void handleErr_msg(char *msg)
{
    fprintf(stderr, "error: %s\n", strerror(errno));
    // exit(1);
}

void error_int(int err) /* handle error */
{
    fprintf(stderr, "error: %s\n", strerror(err));
    // exit(1);
}

void error_msg(char *s)
{
    fprintf(stderr, "error: %s\n", s);
    // exit(1);
}