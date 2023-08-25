#include "shell.h"

/**
 * interactive code will return true if shell in interactive mode
 * @info: struct address
 *
 * sehll will return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * variable my_day - checks if character is a delimeter
 * @c: the char to check
 * @day: the delimeter string
 * Return: 1 if true, 0 if false
 */
int my_day(char c, char *day)
{
	while (*day)
		if (*day++ == c)
			return (1);
	return (0);
}

/**
 * _abcde - checks for alphabets
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _abcde(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * sting_int - convert string to integers
 * @s: the string to be converted
 * Return: 0 if no numbers in string, convert number otherws
 */

int string_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
