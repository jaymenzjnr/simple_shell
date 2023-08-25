#include "shell.h"

/**
 * is_executable - checks if a file is an executable command
 * @info: the information structure
 * @file_path: path to the file
 *
 * Return: 1 if the file is executable, 0 otherwise
 */
int is_executable(info_t *info, char *file_path)
{
	struct stat file_stat;

	(void)info;
	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - duplicates characters within a range
 * @source: the source string
 * @start: starting index
 * @end: ending index
 *
 * Return: pointer to the new buffer
 */
char *duplicate_characters(char *source, int start, int end)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (source[i] != ':')
			buffer[k++] = source[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * search_in_path - searches for a command in the PATH string
 * @info: the information structure
 * @path_string: the PATH string
 * @command: the command to search for
 *
 * Return: full path of the command if found, otherwise NULL
 */
char *search_in_path(info_t *info, char *path_string, char *command)
{
	int i = 0, current_pos = 0;
	char *full_path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_executable(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			full_path = duplicate_characters(path_string, current_pos, i);
			if (!*full_path)
				_strcat(full_path, command);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, command);
			}
			if (is_executable(info, full_path))
				return (full_path);
			if (!path_string[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}
