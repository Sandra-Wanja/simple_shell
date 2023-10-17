#include "shell.h"

/**
 * _myhistory - handles the 'history' command
 * @info: A pointer to the shell information struct
 *
 * Return: 0
 */
int _myhistory(info_t *info)
{
	/* Print the command history list */
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias from the alias list
 * @info: A pointer to the shell information struct
 * @str: The alias string to unset
 *
 * Return: 1 if the alias was not found, 0 otherwise
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - adds or updates an alias in the alias list
 * @info: A pointer to the shell information struct
 * @str: The alias string to set or update
 *
 * Return: 1 if there was an error, 0 otherwise
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias entry
 * @node: A pointer to the alias list node to print
 *
 * Return: 0 if the node is valid, 1 otherwise
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - handles the 'alias' command
 * @info: A pointer to the shell information struct
 *
 * Return: 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		/* Print all alias entries */
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
