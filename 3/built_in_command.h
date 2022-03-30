#ifndef __BUILT_IN_COMMAND_H__
#define __BUILT_IN_COMMAND_H__

#include <unistd.h> /* chdir */

#include "string.h"
#include <stdio.h>

/* built_in_commands */
int check_cmd(char *args[], int args_size);

#endif