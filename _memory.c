#include "shell.h"

/**
 * bfree - free pointer , adress NULL'ed
 * @ptr: pointer address to free
 *
 * Return: free 1, failed 0
 */

int bfree(void **ptr)

{

if (ptr && *ptr)

{

free(*ptr);

*ptr = NULL;

return (1);

}

return (0);
}
