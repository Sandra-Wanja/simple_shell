#include "shell.h"

/**
 * is_cmd - executable command of files
 * @info: struct
 * @path: file path
 *
 * Return: true 1
 */
int is_cmd(info_t *info, char *path)
{
struct stat pt;
(void)info;

if (!path || stat(path, &pt))
return (0);

if (pt.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * dup_chars - chars get duplicated
 * @pathstr: string path
 * @start: index at start
 * @stop: index at stop
 *
 * Return: pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
static char uf[1024];
int w = 0, j = 0;

for (j = 0, w = start; w < stop; w++)

if (pathstr[w] != ':')
uf[j++] = pathstr[w];
uf[j] = 0;
return (uf);
}

/**
 * find_path - finds cmd in string
 * @info: struct info
 * @pathstr: string path
 * @cmd: cmd to be found
 *
 * Return: full path
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int w = 0, rr_pos = 0;
char *p_ath;

if (!pathstr)
return (NULL);

if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}

while (1)
{
if (!pathstr[w] || pathstr[w] == ':')
{
p_ath = dup_chars(pathstr, rr_pos, w);

if (!*p_ath)
_strcat(p_ath, cmd);

else
{
_strcat(p_ath, "/");
_strcat(p_ath, cmd);
}

if (is_cmd(info, p_ath))
return (p_ath);

if (!pathstr[w])
break;
rr_pos = w;
}
w++;
}

return (NULL);
}
