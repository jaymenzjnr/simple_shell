#include "shell.h"

/**
 * l_len - computes length of linked list
 * @a: pointer to first node
 *
 * Return: size of list
 */
size_t l_len(const list_t *a)
{
	size_t n = 0;

	while (a)
	{
		a = a->nxt;
		n++;
	}
	return (n);
}

/**
 * l_to_strs - generates an array of strings from the list->str
 * @az: pointer to first node
 *
 * Return: array of strings
 */
char **l_to_strs(list_t *az)
{
	list_t *node = az;
	size_t n = l_len(az), i, j;
	char **strings;
	char *string;

	if (!az || !n)
		return (NULL);
	strings = malloc(sizeof(char *) * (n + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->nxt, i++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, node->str);
		strings[i] = string;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * p_list - prints all elements of a list_t linked list
 * @a: pointer to first node
 *
 * Return: size of list
 */
size_t p_list(const list_t *a)
{
	size_t n = 0;

	while (a)
	{
		_puts(convert_number(a->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? a->str : "(nil)");
		_puts("\n");
		a = a->nxt;
		n++;
	}
	return (n);
}

/**
 * node_starts_w - returns the node with string starting with prefix
 * @node: pointer to list head
 * @pref: string to match
 * @c: the next character after prefix to match
 *
 * Return: matched node or null
 */
list_t *node_starts_w(list_t *node, char *pref, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, pref);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->nxt;
	}
	return (NULL);
}

/**
 * get_ndx - gets the index of a node
 * @hd: pointer to list head
 * @nd: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_ndx(list_t *hd, list_t *nd)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == nd)
			return (i);
		hd = hd->nxt;
		i++;
	}
	return (-1);
}
