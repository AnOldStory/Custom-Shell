#include "built_in_command.h"

/* Special Commnads */
int check_cmd(char *args[], int args_size)
{
    int flag = 0; /* */

    if (args_size > 0)
    {
        if (strcmp(args[0], "exit") == 0)
        {
            /* Quit program */
            flag = 1;
            exit(0);
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            /* Move directory with path */
            flag = 1;
            if (args_size == 1)
            {
                if (chdir(getenv("HOME")) < 0)
                    printf("err");
            }
            else if (args_size == 2)
            {
                if (chdir(args[1]) < 0)
                    printf("err2");
            }
            else
            {
                handleErr_msg("too many arguments");
            }
        }
        else
        {
            flag = 0;
        }
    }

    return flag;
}
