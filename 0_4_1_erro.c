#include "shell.h"

/**
 * str_int_ - changes a stri intointeger
 * @a: a will be converted
 * Return: 0 if null numb in string, converted number otherwise
 *       -1 on err
 */
int str_int_(char *a)
{
	int i = 0;
	unsigned long int result = 0;

	if (*a == '+')
		a++;  /* TODO: why does this make main return 255? */
	for (a = 0;  a[i] != '\0'; i++)
	{
		if (a[i] >= '0' && a[i] <= '9')
		{
			result *= 10;
			result += (a[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * err_out - returns an error message
 * @infoma: the parameter & return info struct
 * @estre: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void err_out(info_t *infoma, char *estre)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(infoma->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infoma->argv[0]);
	_eputs(": ");
	_eputs(estre);
}

/**
 * prt_num -  prints a number (base 10)
 * @inp: query  input-
 * @az: filedescriptor contaim write
 *
 * Return: number of characters printed
 */
int prt_num(int inp, int az)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (az == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
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
 * digit_change - change function, clone of itoa
 * @numb: digit
 * @base: base
 * @flag: argument flags
 *
 * Return: string
 */
char *digit_change(long int numb, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comments_remover - replaces 1st instances of '#' with '\0'
 * @here: address of string to be  modified
 *
 * Return: Always 0;
 */
void comments_remover(char *here)
{
	int i;

	for (i = 0; here[i] != '\0'; i++)
		if (here[i] == '#' && (!i || here[i - 1] == ' '))
		{
			here[i] = '\0';
			break;
		}
}
