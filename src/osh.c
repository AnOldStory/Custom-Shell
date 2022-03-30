#include "osh.h"

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

    int exitcode;

    init_manager(); /* initial process manager for kill zombie process*/

    while (1)
    {
        /**
         * initialize
         */
        current_username = get_username();
        current_hostname = get_hostname();
        current_working_directory = get_cwd();
        fflush(stdout);

        printf("%s@%s:~%s$ ", current_username, current_hostname, current_working_directory); /* print username */

        /* PARSER */
        if (getline(&inputBuffer, &len, stdin) == 0)
        {
            printf("err");
        };

        Command cmd[100];
        int cmd_count = 0;

        run_parse(inputBuffer, &cmd, &cmd_count); /* parse input and put them cmd */

        for (int nth_cmd = 0; nth_cmd < cmd_count; nth_cmd++)
        {
            int fd[2]; // read , write

            if (pipe(fd) < 0)
            {
                error_msg("wrong in pipe ");
                exit(1);
            }

            cmd[nth_cmd].fd_info[READ_END].fd = fd[READ_END];
            cmd[nth_cmd].fd_info[WRITE_END].fd = fd[WRITE_END];

            pid_t pid = fork();
            if (pid == 0)
            {
                /* if this process is CHILD */

                /* handle stdin with pipe */
                if (nth_cmd > 0)
                {
                    dup2(cmd[nth_cmd - 1].fd_info[READ_END].fd, STDIN_FILENO);
                    close(cmd[nth_cmd - 1].fd_info[READ_END].fd);
                    close(cmd[nth_cmd - 1].fd_info[WRITE_END].fd);
                }

                /* handle stdin with file */
                if (cmd[nth_cmd].fd_info[READ_END].name != NULL)
                {
                    if ((cmd[nth_cmd].fd_info[READ_END].fd = open(cmd[nth_cmd].fd_info[READ_END].name,
                                                                  cmd[nth_cmd].fd_info[READ_END].flag)) < 0)
                    {
                        printf("err in fd : %s", cmd[nth_cmd].fd_info[READ_END].name);
                    }
                    dup2(cmd[nth_cmd].fd_info[READ_END].fd, STDIN_FILENO);
                    close(cmd[nth_cmd].fd_info[READ_END].fd);
                }
                /* handle stdout with file*/
                if (cmd[nth_cmd].fd_info[WRITE_END].name != NULL)
                {
                    if ((cmd[nth_cmd].fd_info[WRITE_END].fd = open(cmd[nth_cmd].fd_info[WRITE_END].name,
                                                                   cmd[nth_cmd].fd_info[WRITE_END].flag,
                                                                   FILE_PERMISSION)) < 0)
                    {
                        printf("err in fd : %s\n", cmd[nth_cmd].fd_info[WRITE_END].name);
                    }
                    dup2(cmd[nth_cmd].fd_info[WRITE_END].fd, STDOUT_FILENO);
                    close(cmd[nth_cmd].fd_info[WRITE_END].fd);
                }

                /* handle stdout with pipe */
                if (nth_cmd < (cmd_count - 1))
                {
                    dup2(cmd[nth_cmd].fd_info[WRITE_END].fd, STDOUT_FILENO);
                    close(cmd[nth_cmd].fd_info[WRITE_END].fd);
                    close(cmd[nth_cmd].fd_info[READ_END].fd);
                }

                /* check id it built in command */
                if (!check_cmd(cmd[nth_cmd].argv, cmd[nth_cmd].argc))
                {
                    if (execvp(cmd[nth_cmd].argv[0], cmd[nth_cmd].argv) < 0)
                    {
                        handleErr();
                        exit(1);
                    }
                }
            }
            else if (pid > 0)
            {
                /* if this process is PARENT */
                /* close pipe */
                if (nth_cmd > 0)
                {
                    close(cmd[nth_cmd - 1].fd_info[READ_END].fd);
                    close(cmd[nth_cmd - 1].fd_info[WRITE_END].fd);
                }

                /* check background and make it manage */
                if (cmd[nth_cmd].is_back == 1)
                {
                    printf("[%d] %d\n", nth_cmd, pid);
                    push_process_manager(pid);
                }
                else
                {
                    waitpid(pid, &exitcode, 0);
                    if (exitcode == 32512)
                    {
                        /* exit command */
                        exit(127);
                    }
                }
            }
            else
            {
                printf("fork err");
            }
        }

        auto_process_manager();
        free_all();
    }

    free(inputBuffer);
    return exitcode;
}
