#include "shell.h"

/**
 * _eputs - string inpted gets printed
 * @str: string to print
 *
 * Return: void
 */

void _eputs(char *str)

{

int w = 0;


if (!str)

return;

while (str[w] != '\0')

{

_eputchar(str[w]);

w++;

}

}

/**
 * _eputchar - char c gets written to stderr
 * @c: char to print
 *
 * Return: success 1
 */

int _eputchar(char c)

{

static int w;

static char buf[WRITE_BUF_SIZE];


if (c == BUF_FLUSH || w >= WRITE_BUF_SIZE)

{

write(2, buf, w);

w = 0;

}

if (c != BUF_FLUSH)

buf[w++] = c;

return (1);

}

/**
 * _putfd - prints character c
 * @c: char to print
 * @fd: file descriptor
 *
 * Return: 1 success
 */

int _putfd(char c, int fd)

{

static int w;

static char buf[WRITE_BUF_SIZE];


if (c == BUF_FLUSH || w >= WRITE_BUF_SIZE)

{

write(fd, buf, w);

w = 0;

}

if (c != BUF_FLUSH)

buf[w++] = c;

return (1);

}

/**
 * _putsfd - string inputed gets printed
 * @str: string to print
 * @fd: file descriptor
 *
 * Return: printed string
 */

int _putsfd(char *str, int fd)

{

int w = 0;


if (!str)

return (0);

while (*str)

{

w += _putfd(*str++, fd);

}

return (w);

}
