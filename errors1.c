#include "shell.h"

/**
 * _erratoi - Converts a string to an integer while handling errors
 * @s: The input string to convert
 *
 * Return: The integer value if successful, -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* Skip leading '+' character if present */

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1); /* Overflow detected */
		}
		else
			return (-1); /* Invalid character detected */
	}
	return (result);
}

/**
 * print_d - Prints an integer to a specified file descriptor
 * @input: The integer to print
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar; /* Use _eputchar for standard error */

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-'); /* Print a minus sign for negative numbers */
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Converts a number to a string representation
 * @num: The number to convert
 * @base: The base for conversion (e.g., 10 for decimal)
 * @flags: Conversion flags
 *
 * Return: A pointer to the string representation of the number
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Removes comments from a string by
 * replacing '#' and everything after it with '\0'
 * @buf: The input string to remove comments from
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0'; /* Replace '#' and everything after it with '\0' */
			break;
		}
}
