#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <unistd.h> /* symbol constant pid_t */
#include <stdlib.h> /* malloc  */

/* linked_list.c */
typedef struct NodeStruct
{
    struct NodeStruct *next;
    int index;
    pid_t pid;
} Node;

Node *link_add(Node *previous, int index, int pid);

void link_remove(Node *previous);

#endif