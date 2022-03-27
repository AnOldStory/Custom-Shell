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
        Command cmd[100];
        run_parse(inputBuffer, &cmd, &cmd_count); // token = *lexer()
                                                  // printf("cmd[*cmd_size].fd[1]%d\n", cmd[0].fd[1]);

        // for (int i = 0; i < cmd[0].argc + 1; i++)
        // {
        //     for (int j = 0; j < 5; j++)
        //     {
        //         printf("[%d,%d]%d \n", i, j, cmd[0].argv[i][j]);
        //     }
        // }

        for (int nth_cmd = 0; nth_cmd < cmd_count; nth_cmd++)
        {
            // printf(" %d_1: %p %s \n", nth_cmd, cmd[nth_cmd].argv[0], cmd[nth_cmd].argv[0]);
            // printf(" %d_2: %p %s \n", nth_cmd, cmd[nth_cmd].argv[1], cmd[nth_cmd].argv[1]);
            // printf(" %d_3: %p \n", nth_cmd, cmd[nth_cmd].argv[2]);
            // printf("argc %d\n", cmd[nth_cmd].argc);
            // printf("fd[0].flag %d\n", cmd[nth_cmd].fd[0].flag);
            // printf("fd[1].flag %d\n", cmd[nth_cmd].fd[1].flag);
            // printf("fd[0].name %s\n", cmd[nth_cmd].fd[0].name);
            // printf("fd[1].name %s\n", cmd[nth_cmd].fd[1].name);

            int fd[2]; // read , write
            if (pipe(fd) < 0)
            {
                printf("wrong pipe");
                // TODO:exception
            }

            cmd[nth_cmd].fd[READ_END].fd = fd[READ_END];
            cmd[nth_cmd].fd[WRITE_END].fd = fd[WRITE_END];

            /* CHILD */
            /* handle stdin to file */
            if (cmd[nth_cmd].fd[READ_END].name != NULL)
            {
                if ((cmd[nth_cmd].fd[READ_END].fd = open(cmd[nth_cmd].fd[READ_END].name,
                                                         cmd[nth_cmd].fd[READ_END].flag)) < 0)
                {
                    printf("err in fd : %s", cmd[nth_cmd].fd[READ_END].name);
                }
                dup2(cmd[nth_cmd].fd[READ_END].fd, STDIN_FILENO);
                close(cmd[nth_cmd].fd[READ_END].fd);
            }
            /* handle stdout to file*/
            if (cmd[nth_cmd].fd[WRITE_END].name != NULL)
            {
                if ((cmd[nth_cmd].fd[WRITE_END].fd = open(cmd[nth_cmd].fd[WRITE_END].name,
                                                          cmd[nth_cmd].fd[WRITE_END].flag,
                                                          FILE_PERMISSION)) < 0)
                {
                    printf("err in fd : %s\n", cmd[nth_cmd].fd[WRITE_END].name);
                }
                dup2(cmd[nth_cmd].fd[WRITE_END].fd, STDOUT_FILENO);
                close(cmd[nth_cmd].fd[WRITE_END].fd);
            }

            if (nth_cmd > 0)
            {
                close(cmd[nth_cmd].fd[READ_END].fd);
                dup2(cmd[nth_cmd].fd[READ_END].fd, cmd[nth_cmd - 1].fd[WRITE_END].fd);
                close(cmd[nth_cmd].fd[READ_END].fd);
            }
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            for (int nth_cmd = 0; nth_cmd < cmd_count; nth_cmd++)
            {
                for (int i = 0; i < nth_cmd; i++)
                {
                    close(cmd[nth_cmd].fd[READ_END].fd);
                    close(cmd[nth_cmd].fd[WRITE_END].fd);
                }
                if (execvp(cmd[nth_cmd].argv[0], cmd[nth_cmd].argv) < 0)
                {
                    exit(1);
                }
            }
        }
        else if (pid > 0)
        {
            /* parent */
            waitpid(pid, NULL, 0);
        }
        else
        {
            printf("fork err");
        }

        free_all();
    }
    free(inputBuffer);
    return 0;
}
