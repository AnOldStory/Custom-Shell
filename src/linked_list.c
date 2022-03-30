#include "linked_list.h"

Node *link_add(Node *previous, int index, int pid)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    previous->next = newNode;
    newNode->index = index;
    newNode->pid = pid;
    newNode->next = 0;

    return newNode;
}

void link_remove(Node *current)
{
    Node *nextNode = current->next;
    current->next = nextNode->next;

    free(nextNode);
}