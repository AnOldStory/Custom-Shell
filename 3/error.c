#include "global.h"

/**
 *  RUNNER
 **/

void run_i(int cmd)
{
    if (cmd < 0)
    {
        error_i(errno);
    }
}

void run_c(char *cmd)
{
    if (cmd == NULL)
    {
        error_i(errno);
    }
}

void handleErr()
{
    perror("Error");
    // exit(1);
}

void handleErr(char *msg)
{
    fprintf(stderr, "error: %s\n", strerror(errno));
    // exit(1);
}

void error_i(int err) /* handle error */
{
    fprintf(stderr, "error: %s\n", strerror(err));
    // exit(1);
}

void error_c(char *s)
{
    fprintf(stderr, "error: %s\n", s);
    // exit(1);
}