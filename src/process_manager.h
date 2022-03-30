#ifndef __PROCESS_MANAGER_H__
#define __PROCESS_MANAGER_H__

#include <stdio.h>
#include <stdlib.h> /* malloc */

#include "linked_list.h"

void init_manager();
void push_process_manager(int pid);
void auto_process_manager();

#endif