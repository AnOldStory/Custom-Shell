#include "init.h"

char *get_username()
{
    char *username = getlogin();
    printf("%s", username);
    struct passwd *user_pw;
    user_pw = getpwnam(username);
    return save_string(username);
}

char *get_hostname()
{
    char hostname[MAX_HOSTNAME];
    if (gethostname(hostname, MAX_HOSTNAME) < 0)
        handleErr("cant get hostname");
    return save_string(hostname);
}

char *get_cwd()
{
    char cwd[MAX_CWD];
    if (getcwd(cwd, MAX_CWD) == 0)
        handleErr("cant get cwd");
    return save_string(cwd);
}