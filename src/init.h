#ifndef __INIT_H__
#define __INIT_H__

#include <stdio.h>  /* cuserid */
#include <unistd.h> /* gethostname getcwd */
#include <pwd.h>

#include "error.h"
#include "string.h"

#define MAX_HOSTNAME 256 /* maximum length hostname */
#define MAX_USERNAME 256 /* maximum length username */
#define MAX_CWD 256      /* maximum length Current Working Directory */

char *get_username();
char *get_hostname();
char *get_cwd();

#endif