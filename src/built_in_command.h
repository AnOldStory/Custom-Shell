#ifndef __BUILT_IN_COMMAND_H__
#define __BUILT_IN_COMMAND_H__

#include <stdio.h>
#include <stdlib.h> /* exit */
#include <unistd.h> /* chdir */

#include "string.h"
#include "error.h"

/* built_in_commands */
int check_cmd(char *args[], int args_size);

#endif