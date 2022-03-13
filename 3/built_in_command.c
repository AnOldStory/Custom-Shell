#include "global.h"

/* Special Commnads */
int check_cmd(char *args[], int args_size)
{
    int flag = 0; /* */

    if (args_size > 0)
    {
        if (strcmp(args[0], "exit") == 0)
        {
            flag = 1;
            /* exit */
            free_all();
            exit(0);
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            flag = 1;
            /* cd */
            if (args_size == 1)
            {
                run_i(chdir(getenv("HOME")));
            }
            else if (args_size == 2)
            {
                run_i(chdir(args[1]));
            }
            else
            {
                error_c("too many arguments");
            }
        }
        else
        {
            flag = 0;
        }
    }

    return flag;
}
