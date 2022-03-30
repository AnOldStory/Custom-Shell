#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>  /* standard input output */
#include <string.h> /* strerror()  */
#include <errno.h>  /* print error */
#include <stdlib.h>

void handleErr();
void handleErr_msg(char *msg);
void error_int(int err);
void error_msg(char *s);

#endif