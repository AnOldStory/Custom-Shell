#include "process_manager.h"

Node *head;
Node *tail;
int pid_size = 0;

/* Initialization process manager */
void init_manager()
{
    head = (Node *)malloc(sizeof(Node));
    tail = head;
    pid_size = 0;
}

/* Add managed pid in manager */
void push_process_manager(int pid)
{
    tail = link_add(tail, pid_size++, pid);
}

/* Kill zombie process */
void auto_process_manager()
{
    int exitcode;
    Node *selected_pid = head;
    while (selected_pid->next != NULL)
    {
        if (waitpid(selected_pid->next->pid, &exitcode, 0x00000001) > 0)
        {
            if (WIFEXITED(exitcode))
            {
                printf("[%d] Done pid : %d with status %d\n", selected_pid->next->index, selected_pid->next->pid, WEXITSTATUS(exitcode));
                if (selected_pid->next->next == NULL) // this pid is same as tail
                {
                    tail = selected_pid;
                }
                link_remove(selected_pid);
            }
        }
        if (selected_pid->next != NULL) // jump to next pid if not tail
        {
            selected_pid = selected_pid->next;
        }
    }
    if (head->next == NULL) // initial manager when list is empty
    {
        pid_size = 0;
    }
}