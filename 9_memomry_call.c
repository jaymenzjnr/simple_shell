#include "shell.h"

/**
 * fre - releases  pointer thus nuls address
 * @pt: address of  pointer to be freed
 *
 * Return: 1 if released, otherwise 0.
 */
int fre(void **pt)
{
	if (pt && *pt)
	{
		fre(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
