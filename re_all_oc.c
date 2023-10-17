#include "shell.h"


/**
 * _memset - puts constant byte to fill memry
 * @s: pointer to memory
 * @b: byte used to fill memory
 * @n: total no of byts
 * Return: pointer to memry
 */

char *_memset(char *s, char b, unsigned int n)

{

unsigned int p;


for (p = 0; p < n; p++)

s[p] = b;

return (s);

}


/**
 * ffree - sets free string in strings
 * @pp: string to be freed from strings
 */

void ffree(char **pp)

{

char **k = pp;


if (!pp)

return;

while (*pp)

free(*pp++);

free(k);

}


/**
 * _realloc - memory gets reallocated
 * @ptr: the previously alloctaed memory pointer
 * @old_size: the size of previously allocated memory
 * @new_size: the size of newly allocated memory
 *
 * Return: pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)

{

char *pointer;


if (!ptr)

return (malloc(new_size));

if (!new_size)

return (free(ptr), NULL);

if (new_size == old_size)

return (ptr);


pointer = malloc(new_size);

if (!pointer)

return (NULL);


old_size = old_size < new_size ? old_size : new_size;

while (old_size--)

pointer[old_size] = ((char *)ptr)[old_size];

free(ptr);

return (pointer);

}
