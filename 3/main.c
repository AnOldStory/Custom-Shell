#include "global.h"

char *current_host_name = (char *)NULL;         /* hostname */
char *current_user_name = (char *)NULL;         /* username */
char *current_working_directory = (char *)NULL; /* working directory */

int main(void)
{
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    int args_size = 0;            /* argument size for free */
    int should_run = 1;           /* flag to determine when to exit program */



    /**
     * initialize
     */



    /* */

    while (should_run) /* run until flag change */
    {
    }
}