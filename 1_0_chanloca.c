#include "shell.h"

/**
 * set_memory -this auto fills ram with a constant byte
 * @target: the pointer to the ram area
 * @byte: the byte to fill *target with
 * @count: the number of bytes to be filled
 * Return: (target) a pointer to the memory area target
 */
char *set_memory(char *target, char byte, unsigned int count)
{
	unsigned int i;

	for (i = 0; i < count; i++)
		target[i] = byte;
	return (target);
}

/**
 * free_strings - frees a string array
 * @string_array: string array
 */
void free_strings(char **string_array)
{
	char **arr = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(arr);
}

/**
 *rcate_memory - reallocates a memory block
 * @ptr: pointer to previous dynamically allocated block
 * @old_size: size of previous block
 * @new_size: size of new block
 *
 * Return: pointer to the reallocated block or NULL
 */
void *rcate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (allocate_memory(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = allocate_memory(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
