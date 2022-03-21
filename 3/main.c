#include "global.h"

#define FILE_PERMISSION 0644

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
                                  /* arguments size */

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
        int args_size = 0;

        printf("%s@%s:~%s$ ", current_username, current_hostname, current_working_directory); /* print username */

        /* PARSER */
        if (getline(&inputBuffer, &len, stdin) == 0)
        {
            printf("err");
        };

        int cmd_count = 0;
        Command **cmd = run_parse(inputBuffer, &cmd_count); // token = *lexer()

        printf(" 1: %p \n", cmd[0]->argv[0]);
        printf(" 2: %p \n", cmd[0]->argv[1]);
        printf(" 3: %p \n", cmd[0]->argv[2]);
        // for (int i = 0; i < cmd[0]->argc + 1; i++)
        // {
        //     for (int j = 0; j < 5; j++)
        //     {
        //         printf("[%d,%d]%d \n", i, j, cmd[0]->argv[i][j]);
        //     }
        // }

        pid_t parent_pid = fork();
        if (parent_pid > 0)
        {
            /* parents */
            wait();
        }
        else if (parent_pid == 0)
        {

            for (int nth_cmd = 0; nth_cmd < cmd_count; nth_cmd++)
            {
                // pid_t pid = fork();
                // if (pid == 0)
                // {
                int fd_in, fd_out; // read , write

                /* handle stdin to file */
                if (cmd[nth_cmd]->file_descriptor[0].name != NULL)
                {
                    printf("들어가요옷 %s\n", cmd[nth_cmd]->file_descriptor[0].name);
                    if (fd_in = open(cmd[nth_cmd]->file_descriptor[0].name, cmd[nth_cmd]->file_descriptor[0].fd) < 0)
                    {
                        printf("err in fd : %s", cmd[nth_cmd]->file_descriptor[0].name);
                    }
                    dup2(fd_in, STDIN_FILENO);
                    close(fd_in);
                }
                /* handle stdout to file*/
                if (cmd[nth_cmd]->file_descriptor[1].name != NULL)
                {
                    printf("나와요옷\n");
                    if (fd_out = open(cmd[nth_cmd]->file_descriptor[1].name, cmd[nth_cmd]->file_descriptor[1].fd, FILE_PERMISSION) < 0)
                    {
                        printf("err in fd : %s", cmd[nth_cmd]->file_descriptor[1].name);
                    }
                    dup2(fd_out, STDOUT_FILENO);
                    close(fd_out);
                }

                // if (pipe(fd) == -1)
                // {
                //     /* pipe error */
                //     perror("pipe");
                //     exit(1);
                // }
                printf("실행한다잇\n");
                if (execvp(cmd[nth_cmd]->argv[0], cmd[nth_cmd]->argv) < 0)
                    exit(1);
                //     }
                //     waitpid(pid, NULL, 0);
            }
        }
        else
        {
            printf("fork error");
        }
        free_all();
    }
    free(inputBuffer);
    return 0;
}
