#include "custom_shell.h"

/**
 * custom_strlen - returns the length of a custom string
 * @str: the custom string whose length to check
 *
 * Return: integer length of custom string
 */
int custom_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;
	return (length);
}

/**
 * custom_strcmp - performs lexicographic comparison of two custom strings.
 * @str1: the first custom string
 * @str2: the second custom string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int custom_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * custom_starts_with - checks if a custom string starts with another custom string
 * @str: custom string to search
 * @prefix: the prefix to find
 *
 * Return: address of next char of str or NULL
 */
char *custom_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * custom_strcat - concatenates two custom strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *custom_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
