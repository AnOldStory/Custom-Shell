#include "global.h"

char *current_hostname;          // = (char *)NULL;          /* hostname */
char *current_username;          // = (char *)NULL;          /* username */
char *current_working_directory; // = (char *)NULL; /* working directory */

void free_all()
{
    free(current_hostname);
    free(current_username);
    free(current_working_directory);
}

int main(int argc, char *argv[])
{
    /* input */
    size_t len = MAX_LINE;                                       /* length of line */
    char *inputBuffer = (char *)malloc(sizeof(char) * MAX_LINE); /* need free */

    /* parsed info */
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    int args_size = 0;            /* arguments size */

    int should_run = 1; /* flag to determine when to exit program */
    while (should_run)  /* run until flag change */
    {
        /**
         * initialize
         */
        current_username = get_username();
        current_hostname = get_hostname();
        current_working_directory = get_cwd();
        fflush(stdout);
        args_size = 0;

        printf("%s@%s:~%s$ ", current_username, current_hostname, current_working_directory); /* print username */

        /* PARSER */
        getline(&inputBuffer, &len, stdin);

        run_parse(inputBuffer, args, &args_size);
        // printf("%d asdfasdf", args_size);
        for (int i = 0; i < args_size; i++)
        {
            printf("[%d]%s ", i, args[i]);
        }
        printf("\n");

        // int fds[2];
        // pipe(fds);

        // pid_t pid = fork();
        // if (pid > 0)
        // {
        //     /* parents */
        //     // dprinf(fds[1],"%s\n")
        // }
        // else if (pid == 0)
        // {
        //     /* child */
        //     dups(fds[0], STDIN_FILENO);
        //     close(fds[0]);
        //     clost(fds[1]);

        //     if (execvp(args[0], args) < 0)
        //         exit(0);
        // }
        // else
        // {
        //     printf("fork error");
        // }
        free_all();
    }
    free(inputBuffer);
    return 0;
}
