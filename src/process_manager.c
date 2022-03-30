#include "process_manager.h"

Node *head;
Node *tail;
int pid_size = 0;

void init_manager()
{
    head = (Node *)malloc(sizeof(Node));
    tail = head;
}

void push_process_manager(int pid)
{
    tail = link_add(tail, pid_size++, pid);
}

void auto_process_manager()
{
    int exitcode;
    /* swap zombie process */
    Node *selected_pid = head;
    while (selected_pid->next != NULL)
    {
        if (waitpid(selected_pid->next->pid, &exitcode, 0x00000001) > 0)
        {
            if (WIFEXITED(exitcode))
            {
                printf("[%d] Done pid : %d with status %d\n", selected_pid->next->index, selected_pid->next->pid, WEXITSTATUS(exitcode));
                if (selected_pid->next->next == NULL)
                {
                    tail = selected_pid;
                }
                link_remove(selected_pid);
            }
        }
        if (selected_pid->next != NULL)
        {
            selected_pid = selected_pid->next;
        }
    }
    if (head->next == NULL)
    {
        pid_size = 0;
    }
}