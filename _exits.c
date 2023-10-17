#include "shell.h"

/**
 *_strncpy - string gets copied
 *@dest: where string gets copied
 *@src: string source
 *@n: total no of chars to be copied
 *Return: string
 */

char *_strncpy(char *dest, char *src, int n)

{

int w, k;

char *p = dest;


w = 0;

while (src[w] != '\0' && w < n - 1)

{

dest[w] = src[w];

w++;

}

if (w < n)

{

k = w;

while (k < n)

{

dest[k] = '\0';

k++;

}

}

return (p);

}


/**
 *_strncat - two strings gets connected
 *@dest: string one
 *@src: string two
 *@n: max no of bytes to use
 *Return: string that has been connected
 */

char *_strncat(char *dest, char *src, int n)

{

int w, k;

char *p = dest;


w = 0;

k = 0;

while (dest[w] != '\0')

w++;

while (src[k] != '\0' && k < n)

{

dest[w] = src[k];

w++;

k++;

}

if (k < n)

dest[w] = '\0';

return (p);

}

/**
 *_strchr - specific char gets located in string
 *@s: string to parse
 *@c: char to search
 *Return: pointer
 */

char *_strchr(char *s, char c)

{

do {

if (*s == c)

return (s);

} while (*s++ != '\0');

return (NULL);
}
