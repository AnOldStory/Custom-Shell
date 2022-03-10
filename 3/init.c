#include "global.h"

char hostname[MAX_HOSTNAME]; /* hostname */
char username[MAX_USERNAME]; /* username */
char cwd[MAX_CWD];           /* cwd */

char *init_hostname()
{
    /* hostname */
    if (gethostname(hostname, MAX_HOSTNAME) < 0)
        handleErr("cant get hostname");
    else if (save_string(hostname) == NULL)
        handleErr("cant alloc -> hostname ");
}

char *init_username()
{
    /* username */
    if (cuserid(username) == NULL)
        handleErr("cant get username");
    else if (save_string(username) == NULL)
        handleErr("cant alloc -> username");
}