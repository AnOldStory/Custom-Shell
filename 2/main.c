#include "global.h"

/* main.c */
char hostname[MAX_HOSTNAME]; /* hostname */
char username[MAX_USERNAME]; /* username */
char cwd[MAX_CWD];           /* cwd */
struct token token;          /* token */

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    int args_size = 0;            /* argument size for free */
    int should_run = 1;           /* flag to determine when to exit program */
    while (should_run)            /* run until flag change */
    {
        run_i(gethostname(hostname, MAX_HOSTNAME)); /* save hostname */
        run_c(cuserid(username));                   /* save username */
        run_c(getcwd(cwd, MAX_CWD));                /* save current working directory */
        args_size = 0;                              /* clear args_size */

        printf("%s@%s:~%s$ ", username, hostname, cwd); /* print username */
        fflush(stdout);

        /* PARSER */
        while ((token = parser()).type != S_DONE)
        {
            printf("token : %s Type : %d Ptr: %p \n", token.lexptr, token.type, token.lexptr);
            args[args_size] = token.lexptr; /* assign token to args */
            args_size++;
        }
        args[args_size] = 0;

        /* Special Command Check */
        if (check_cmd(args, args_size) == 0)
        {
            /* RUNNER */
            int pid = fork();
            // printf("Pid : %d\n", pid);
            if (pid == 0)
            {
                /* child process */
                run_i(execvp(args[0], args));
            }
            else
            {
                // printf("%d", pid);
                /* parent process */
                pid = waitpid(pid);
                // printf("Wait Pid : %d", pid);
            }
        };
        f_arr_c(args, args_size);
    }
    return 0;
}

/**
 * cmd file -arg -arg -arg -arg
 *
 */