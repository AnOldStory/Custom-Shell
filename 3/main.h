#ifndef __MAIN_H__
#define __MAIN_H__

#include <unistd.h> /* symbol constant pid_t */

#include "init.h"
#include "parser.h"
#include "error.h"
#include "process_manager.h"
#include "built_in_command.h"

#define READ_END 0  /* file descriptor IN */
#define WRITE_END 1 /* file descriptor OUT */

#define MAX_LINE 80 /* The maximum length command */

void free_all();

#endif