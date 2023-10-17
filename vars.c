#include "shell.h"
/**
 * is_chain - Checks if the current position in the
 * input buffer 'buf' represents a command chaining operator
 * (e.g., '|', '||', '&&', ';').
 *
 * @info: Pointer to the info_t structure.
 * @buf: The input buffer.
 * @p: Pointer to the current position in the buffer.
 *
 * Return: 1 if a command chaining operator is found, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
 * check_chain - Checks if command chaining conditions are
 * met based on the current command and status.
 *
 * @info: Pointer to the info_t structure.
 * @buf: The input buffer.
 * @p: Pointer to the current position in the buffer.
 * @i: Current index within the input buffer.
 * @len: Length of the input buffer.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
 * replace_alias - Replaces the command in 'info->argv[0]' with its
 * corresponding alias if found in the 'info->alias' list.
 *
 * @info: Pointer to the info_t structure.
 *
 * Return: 1 if the alias is replaced, 0 if not found.
 */
int replace_alias(info_t *info)
{
int i;
list_t *node;
char *p;
for (i = 0; i < 10; i++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}
/**
 * replace_vars - Replaces environment variables and special
 * variables in the 'info->argv' array with their values.
 * @info: Pointer to the info_t structure.
 *
 * Return: Always returns 0.
 */
int replace_vars(info_t *info)
{
int i = 0;
list_t *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!_strcmp(info->argv[i], "$?"))
{
replace_string(&(info->argv[i]),
_strdup(convert_number(info->status, 10, 0)));
continue;
}
if (!_strcmp(info->argv[i], "$$"))
{
replace_string(&(info->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
replace_string(&(info->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&info->argv[i], _strdup(""));
}
return (0);
}
/**
 * replace_string - Replaces the contents of the old string pointer
 * with a new string pointer and frees the old memory.
 *
 * @old: Pointer to the old string pointer.
 * @new: The new string.
 *
 * Return: Always returns 1.
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
