#include "shell.h"
/**
 * get_history_file - gets file history
 * @info: struct parameter
 * Return: string
 */
char *get_history_file(info_t *info)
{
char *uf, *ir;
ir = _getenv(info, "HOME=");

if (!ir)
return (NULL);

uf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!uf)
return (NULL);

uf[0] = 0;
_strcpy(uf, ir);
_strcat(uf, "/");
_strcat(uf, HIST_FILE);

return (uf);
}
/**
 * write_history - file is created and appended
 * @info: struct parameter
 * Return: success 1
 */
int write_history(info_t *info)
{
ssize_t d;
char *fn = get_history_file(info);
list_t *node = NULL;

if (!fn)
return (-1);

d = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(fn);

if (d == -1)
return (-1);

for (node = info->history; node; node = node->next)
{
_putsfd(node->str, d);
_putfd('\n', d);
}
_putfd(BUF_FLUSH, d);
close(d);

return (1);
}
/**
 * read_history - history from a file gets read
 * @info: struct parameter
 * Return: success (history)
 */
int read_history(info_t *info)
{
int w, last = 0, linecount = 0;
ssize_t d, rdlen, fsize = 0;
struct stat st;
char *uf = NULL, *fn = get_history_file(info);

if (!fn)
return (0);
d = open(fn, O_RDONLY);
free(fn);
if (d == -1)
return (0);
if (!fstat(d, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
uf = malloc(sizeof(char) * (fsize + 1));
if (!uf)
return (0);
rdlen = read(d, uf, fsize);
uf[fsize] = 0;
if (rdlen <= 0)
return (free(uf), 0);
close(d);
for (w = 0; w < fsize; w++)
if (uf[w] == '\n')
{
uf[w] = 0;
build_history_list(info, uf + last, linecount++);
last = w + 1;
}
if (last != w)
build_history_list(info, uf + last, linecount++);
free(uf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);
renumber_history(info);
return (info->histcount);
}
/**
 * build_history_list - entry gets added
 * @info: Struct
 * @buf: the buffer
 * @linecount: linecount of history
 * Return: Always 0 (success)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
list_t *node = NULL;

if (info->history)
node = info->history;
add_node_end(&node, buf, linecount);

if (!info->history)
info->history = node;

return (0);
}
/**
 * renumber_history - after changes history gets re-numbered
 * @info: Struct
 * Return: new (historycount)
 */
int renumber_history(info_t *info)
{
list_t *node = info->history;
int w = 0;

while (node)
{
node->num = w++;
node = node->next;
}
return (info->histcount = w);
}
