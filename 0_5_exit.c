#include "shell.h"

/**
 **custom_strncpy - copies a string
 *@destination: the destination string to copy to
 *@source: the source string
 *@max_chars: the maximum number of characters to copy
 *Return: the pointer to the copied string
 */
char *custom_strncpy(char *destination, char *source, int max_chars)
{
	int iterator_dest, iterator_src;
	char *result = destination;

	iterator_dest = 0;
	while (source[iterator_src] != '\0' && iterator_dest < max_chars - 1)
	{
		destination[iterator_dest] = source[iterator_src];
		iterator_dest++;
	}
	if (iterator_dest < max_chars)
	{
		iterator_src = iterator_dest;
		while (iterator_src < max_chars)
		{
			destination[iterator_src] = '\0';
			iterator_src++;
		}
	}
	return (result);
}

/**
 **custom_strncat - concatenates two strings
 *@first_string: the first string
 *@second_string: the second string
 *@max_bytes: the maximum number of bytes to use
 *Return: the concatenated string
 */
char *custom_strncat(char *first_string, char *second_string, int max_bytes)
{
	int iterator_first, iterator_second;
	char *result = first_string;

	iterator_first = 0;
	iterator_second = 0;
	while (first_string[iterator_first] != '\0')
		iterator_first++;
	while (second_string[iterator_second] != '\0' && iterator_second < max_bytes)
	{
		first_string[iterator_first] = second_string[iterator_second];
		iterator_first++;
		iterator_second++;
	}
	if (iterator_second < max_bytes)
		first_string[iterator_first] = '\0';
	return (result);
}

/**
 **custom_strchr - locates a character in a string
 *@string: the string to search in
 *@character: the character to locate
 *Return: a pointer to the memory area of the string
 */
char *custom_strchr(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}
