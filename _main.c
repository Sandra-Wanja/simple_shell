#include "shell.h"
/**
 * main - point of entry
 * @ac: argument count
 * @av: argument vector
 * Return: success 0, error 1
 */
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };
int pu = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (pu)
: "r" (pu));

if (ac == 2)
{
pu = open(av[1], O_RDONLY);

if (pu == -1)
{
if (errno == EACCES)
exit(126);

if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}

return (EXIT_FAILURE);
}

info->readfd = pu;
}

populate_env_list(info);
read_history(info);
hsh(info, av);

return (EXIT_SUCCESS);
}
