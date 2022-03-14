#include "global.h"

char *get_hostname()
{
    char hostname[MAX_HOSTNAME];
    if (gethostname(hostname, MAX_HOSTNAME) < 0)
        handleErr("cant get hostname");
    printf("%s", save_string(hostname));
    return save_string(hostname);
}

char *get_username()
{
    char username[MAX_USERNAME];
    if (cuserid(username) == 0)
        handleErr("cant get username");
    return save_string(&username[0]);
}

char *get_cwd()
{
    char *cwd;
    if (getcwd(cwd, MAX_CWD) == NULL)
        handleErr("cant get cwd");
    return save_string(cwd);
}