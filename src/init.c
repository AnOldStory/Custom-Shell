#include "init.h"

/* get username of shell */
char *get_username()
{
    char *username = getlogin();
    struct passwd *user_pw;
    return save_string(username);
}

/* get hostname of shell */
char *get_hostname()
{
    char hostname[MAX_HOSTNAME];
    if (gethostname(hostname, MAX_HOSTNAME) < 0)
        handleErr("cant get hostname");
    return save_string(hostname);
}

/* get current working directory of shell */
char *get_cwd()
{
    char cwd[MAX_CWD];
    if (getcwd(cwd, MAX_CWD) == 0)
        handleErr("cant get cwd");
    return save_string(cwd);
}