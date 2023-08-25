#include "custom_shell.h"

/**
 * custom_str_copy - copies a custom string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *custom_str_copy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = 0;
	return (destination);
}

/**
 * custom_str_duplicate - duplicates a custom string
 * @string: the custom string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *custom_str_duplicate(const char *string)
{
	int length = 0;
	char *result;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--string;
	return (result);
}

/**
 * custom_print_string - prints a custom input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void custom_print_string(char *string)
{
	int index = 0;

	if (!string)
		return;
	while (string[index] != '\0')
	{
		custom_write_character(string[index]);
		index++;
	}
}

/**
 * custom_write_character - writes the character c to stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_write_character(char character)
{
	static int currentIndex;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || currentIndex >= WRITE_BUF_SIZE)
	{
		write(1, buffer, currentIndex);
		currentIndex = 0;
	}
	if (character != BUF_FLUSH)
		buffer[currentIndex++] = character;
	return (1);
}
