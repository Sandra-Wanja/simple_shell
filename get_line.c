#include "shell.h"

/**
 * input_buf - commands that are chained get buffered
 * @info: struct parameter
 * @buf: buffer address
 * @len: len variable address
 *
 * Return: read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t m = 0;
size_t lenp = 0;

if (!*len) /* if nothing in buffer, fill it */
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);

#if USE_GETLINE
m = getline(buf, &lenp, stdin);
#else
m = _getline(info, buf, &lenp);
#endif

if (m > 0)
{
if ((*buf)[m - 1] == '\n')
{
(*buf)[m - 1] = '\0'; /* rm trailing line */
m--;
}

info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);

{
*len = m;
info->cmd_buf = buf;
}
}
}

return (m);
}

/**
 * get_input - function to get line -(minus) nwline
 * @info: struct parameter
 *
 * Return: read bytes
 */
ssize_t get_input(info_t *info)
{
static char *buf; /* the ';' command chain buffer */
static size_t w, k, len;
ssize_t m = 0;
char **buf_p = &(info->arg), *p;
_putchar(BUF_FLUSH);
m = input_buf(info, &buf, &len);

if (m == -1) /* E.O.F */
return (-1);

if (len) /* commands left in chain buffer */
{
k = w; /* iterator t0 current buf position */
p = buf + w; /* get return pointer */
check_chain(info, buf, &k, w, len);

while (k < len) /* iterate to end or semicolon */
{
if (is_chain(info, buf, &k))
break;
k++;
}

w = k + 1; /* increment past NULLed ';'' */

if (w >= len) /* end of buffer reached */
{
w = len = 0; /* length and position reset */
info->cmd_buf_type = CMD_NORM;
}

*buf_p = p; /* pass pointer back to the current command position */
return (_strlen(p)); /* current command length returned */
}

*buf_p = buf;

return (m);
}

/**
 * read_buf - function to read buffer
 * @info: struct parameter
 * @buf: buffer to read
 * @i: size of buffer
 *
 * Return: m
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t m = 0;

if (*i)
return (0);

m = read(info->readfd, buf, READ_BUF_SIZE);

if (m >= 0)
*i = m;

return (m);
}

/**
 * _getline - gets input from standard input
 * @info: struct parameter
 * @ptr: buffer pointer address
 * @length: pointer to pre-allocated buffer
 *
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t w, len;
size_t j;
ssize_t m = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;

if (p && length)
s = *length;

if (w == len)
w = len = 0;
m = read_buf(info, buf, &len);

if (m == -1 || (m == 0 && len == 0))
return (-1);

c = _strchr(buf + w, '\n');
j = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + j : j + 1);

if (!new_p)
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + w, j - w);

else
_strncpy(new_p, buf + w, j - w + 1);

s += j - w;
w = j;
p = new_p;

if (length)
*length = s;
*ptr = p;

return (s);
}

/**
 * sigintHandler - control c is blocked
 * @sig_num: signal no
 *
 * Return: nothing
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
