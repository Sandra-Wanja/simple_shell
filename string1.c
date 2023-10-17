#include "shell.h"
/**
 * _strcpy - Copies the contents of one string to another.
 *
 * @dest: The destination string to which 'src' will be copied.
 * @src: The source string to be copied to 'dest'.
 *
 * Return: A pointer to the destination string 'dest'.
 */
char *_strcpy(char *dest, char *src)
{
int i = 0;
if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}
/**
 * _strdup - Duplicates a string by allocating memory
 * for it and copying its contents.
 *
 * @str: The input string to be duplicated.
 *
 * Return: A pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
int length = 0;
char *ret;
if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}
/**
 * _puts - Prints a string to the standard output.
 *
 * @str: The string to be printed.
 */
void _puts(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}
/**
 * _putchar - Writes a character to a buffer
 * and flushes the buffer when it's full.
 *
 * @c: The character to be written to the buffer.
 *
 * Return: 1 on success.
 */
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
