#include "shell.h"

/**
 * input_call - returns an input string
 * @txt: the string to be printed
 *
 * Return: Nothing
 */
void input_call(char *txt)
{
	int i = 0;

	if (!txt)
		return;
	while (txt[i] != '\0')
	{
		_eputchar(txt[i]);
		i++;
	}
}

/**
 * w_a_char -a  character written to stderr
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 returned,erno set appropriately.
 */
int w_a_char(char a)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * _wrtfd - the character a written to given az
 * @a: The character to print
 * @az: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno set appropriately.
 */
int _wrtfd(char a, int az)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(az, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * _putaz - prin a string input
 * @a: the string to be printed
 * @az: the filedescriptor to write to
 *
 * Return: number of char
 */
int _putaz(char *a, int az)
{
	int i = 0;

	if (!a)
		return (0);
	while (*a)
	{
		i += _putaz(*a++, az);
	}
	return (i);
}
