#include "shell.h"

/**
 *add_fre -this releases the pointer thus, nuls the address
 * @pointt: address of the pointer to free
 *
 * Return: 1 if released, otherwise 0.
 */
int add_fre(void **pointt)
{
	if (ptr && *pointt)
	{
		add_fre(*pointt);
		*pointt = NULL;
		return (1);
	}
	return (0);
}
