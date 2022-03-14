#include "global.h"

/**
 *  Memory
 * */

/* safe calloc pointer */
void *c_p(size_t num, size_t size)
{
    void *temp = calloc(num, sizeof(size));
    if (temp == 0)
        error_msg("Memory Allocation failed");
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

char *save_string(char *s)
{
    // return strcpy((char *)malloc(1 + strlen(s)), s);
    // if (strdup(s) == NULL)
    // {
    //     handleErr_msg("cant alloc -> saveString");
    // }
    return strdup(s);
}