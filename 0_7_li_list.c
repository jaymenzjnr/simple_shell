#include "shell.h"

/**
 * insrt_node - inserts a node at the beginning of the list
 * @hd: address of the head node pointer
 * @txt: string field of the node
 * @indx: node index for history
 *
 * Return: pointer to the new head node
 */
list_t *insrt_node(list_t **hd, const char *txt, int indx)
{
	list_t *n_hd;

	if (!hd)
		return (NULL);
	n_hd = malloc(sizeof(list_t));
	if (!n_hd)
		return (NULL);
	_memset((void *)n_hd, 0, sizeof(list_t));
	n_hd->indx = indx;
	if (txt)
	{
		n_hd->str = _strdup(txt);
		if (!n_hd->str)
		{
			free(n_hd);
			return (NULL);
		}
	}
	n_hd->nxt = *hd;
	*hd = n_hd;
	return (n_hd);
}

/**
 * insrt_node_end - inserts a node at the end of the list
 * @hd: address of the head node pointer
 * @txt: string field of the node
 * @indx: node index for history
 *
 * Return: pointer to the new node
 */
list_t *insrt_node_end(list_t **hd, const char *txt, int indx)
{
	list_t *n_nd, *node;

	if (!hd)
		return (NULL);

	node = *hd;
	n_nd = malloc(sizeof(list_t));
	if (!n_nd)
		return (NULL);
	_memset((void *)n_nd, 0, sizeof(list_t));
	n_nd->indx = indx;
	if (txt)
	{
		n_nd->str = _strdup(txt);
		if (!n_nd->str)
		{
			free(n_nd);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nxt)
			node = node->nxt;
		node->nxt = n_nd;
	}
	else
		*hd = n_nd;
	return (n_nd);
}

/**
 * print_str_lst - prints only the string element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: number of nodes in the list
 */
size_t print_str_lst(const list_t *h)
{
	size_t num = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->nxt;
		num++;
	}
	return (num);
}

/**
 * del_node_at_idx - deletes a node at a given index
 * @hd: address of the head node pointer
 * @idx: index of the node to delete
 *
 * Return: (1) on success, (0) on failure
 */
int del_node_at_idx(list_t **hd, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!hd || !*hd)
		return (0);

	if (!idx)
	{
		node = *hd;
		*hd = (*hd)->nxt;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (i == idx)
		{
			prev_node->nxt = node->nxt;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->nxt;
	}
	return (0);
}

/**
 * free_str_lst - frees all nodes of a list
 * @hd_ptr: address of the head node pointer
 *
 * Return: void
 */
void free_str_lst(list_t **hd_ptr)
{
	list_t *node, *nxt_node, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		nxt_node = node->nxt;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*hd_ptr = NULL;
}
