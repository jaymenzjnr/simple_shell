#include "shell.h"

/**
 * _anenv - print current environ
 * @info:struct containing potential arguments.main con fun pro...
 * Return: Always 0
 */
int _anenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _pullanenv - retrieves value of environ variable
 * @info: struct containe potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *_pullanenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * varenvi_ -  Initialize new environment variable,
 *             modify existing one
 * @info:struct  containing potential arguments.
 *  Return: Always 0
 */
int varenvi_(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * rmvenv -  remove environment variable
 * @info: struct contain potential arguments. To maintain function prototype.
 * Return: Always 0
 */
int rmvenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * p_list - populates linked list for envi
 * @info: this structure containing potential arguments
 * Return: Always 0
 */
int p_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
