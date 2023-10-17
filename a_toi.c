#include "shell.h"


/**
 * interactive - if shell is on interective mode, returns true
 * @info: address of struct
 *
 * Return: 1 (success) interactive mode is on
 */

int interactive(info_t *info)

{

return (isatty(STDIN_FILENO) && info->readfd <= 2);

}


/**
 * is_delim - checks for delimeter characters
 * @c: character to be checked
 * @delim: string for the delimeter
 * Return: true 1, false 0
 */

int is_delim(char c, char *delim)

{

while (*delim)

if (*delim++ == c)

return (1);

return (0);

}


/**
 * _isalpha - checks if letters are present
 * @c: char provided for checking
 * Return: letter present 1
 */


int _isalpha(int c)

{

if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

return (1);

else

return (0);

}


/**
 * _atoi - string gets converted to integer
 * @s: string to convert
 * Return: string that has been converted
 */


int _atoi(char *s)

{

int n, gn = 1, lg = 0, tp;

unsigned int su = 0;

for (n = 0; s[n] != '\0' && lg != 2; n++)

{

if (s[n] == '-')

gn *= -1;

if (s[n] >= '0' && s[n] <= '9')

{

lg = 1;

su *= 10;

su += (s[n] - '0');

}

else if (lg == 1)

lg = 2;

}

if (gn == -1)

tp = -su;

else

tp = su;

return (tp);
}



