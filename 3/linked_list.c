#include "global.h"

Node *link_add(Node *previous, int index, int pid)
{
    Node *newNode = malloc(sizeof(Node));

    previous->next = newNode;
    newNode->index = index;
    newNode->pid = pid;
    newNode->next = NULL;

    return newNode;
}

void link_remove(Node *current)
{
    Node *nextNode = current->next;
    current->next = nextNode->next;

    free(nextNode);
}