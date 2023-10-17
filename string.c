#include "shell.h"
/**
 * _strlen - Calculates the length of a null-terminated string.
 *
 * @s: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
int i = 0;
if (!s)
return (0);
while (*s++)
i++;
return (i);
}
/**
 * _strcmp - Compares two strings character by character.
 *
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return:
 *   - 0 if the strings are equal.
 *   - A negative value if s1 is less than s2.
 *   - A positive value if s1 is greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - Checks if a string starts with another string.
 * @haystack: The string to search in.
 * @needle: The string to search for at the beginning of haystack.
 *
 * Return:
 *   - A pointer to the character in 'haystack' 
 *   where 'needle' starts, if found.
 *   - NULL if 'needle' is not found at the beginning of 'haystack'.
 */
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}
/**
 * _strcat - Concatenates two strings.
 *
 * @dest: The destination string to which 'src' will be appended.
 * @src: The source string to be appended to 'dest'.
 *
 * Return: A pointer to the destination string 'dest'.
 */

char *_strcat(char *dest, char *src)
{
char *ret = dest;
while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}
