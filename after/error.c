#include "global.h"

/**
 *  Memory 
 * */

/* safe calloc pointer */
void *c_p(size_t num, size_t size)
{
    void *temp = calloc(num, sizeof(size));
    if (temp == 0)
        error_c("Memory Allocation failed");
    return temp;
}

/* free calloc pointer */
void f_tok(struct token target)
{
    f_safe((void *)target.lexptr);
};

/* free pointer array char */
void f_arr_c(char *arr[], int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        f_safe((void *)arr[i]);
    }
}

/* free after null */
void f_safe(void *p)
{
    free(p);
    p = NULL;
}

/**
 *  RUNNER
 *  */

void run_i(int cmd)
{
    if (cmd < 0)
    {
        error_i(errno);
    }
}

void run_c(char *cmd)
{
    if (cmd == NULL)
    {
        error_i(errno);
    }
}

void error_i(int err) /* handle error */
{
    fprintf(stderr, "error: %s\n", strerror(err));
    // exit(1);
}

void error_c(char *s)
{
    fprintf(stderr, "error: %s\n", s);
    // exit(1);
}