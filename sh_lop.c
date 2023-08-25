#include "custom_shell.h"

/**
 * main_loop - main shell loop
 * @shell_data: the parameter & return shell data
 * @args: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_loop(shell_data_t *shell_data, char **args)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_shell_data(shell_data);
		if (is_interactive(shell_data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_result = get_user_input(shell_data);
		if (input_result != -1)
		{
			set_shell_data(shell_data, args);
			builtin_result = search_builtin(shell_data);
			if (builtin_result == -1)
				find_executable(shell_data);
		}
		else if (is_interactive(shell_data))
			_putchar('\n');
		free_shell_data(shell_data, 0);
	}
	write_history(shell_data);
	free_shell_data(shell_data, 1);
	if (!is_interactive(shell_data) && shell_data->status)
		exit(shell_data->status);
	if (builtin_result == -2)
	{
		if (shell_data->error_code == -1)
			exit(shell_data->status);
		exit(shell_data->error_code);
	}
	return (builtin_result);
}

/**
 * search_builtin - finds a builtin command
 * @shell_data: the parameter & return shell data
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int search_builtin(shell_data_t *shell_data)
{
	int i, builtin_result = -1;
	builtin_table custom_builtins[] = {
		{"exit", custom_exit},
		{"env", custom_env},
		{"help", custom_help},
		{"history", custom_history},
		{"setenv", custom_setenv},
		{"unsetenv", custom_unsetenv},
		{"cd", custom_cd},
		{"alias", custom_alias},
		{NULL, NULL}
	};

	for (i = 0; custom_builtins[i].type; i++)
		if (_strcmp(shell_data->arguments[0], custom_builtins[i].type) == 0)
		{
			shell_data->line_count++;
			builtin_result = custom_builtins[i].function(shell_data);
			break;
		}
	return (builtin_result);
}

/**
 * find_executable - finds an executable in PATH
 * @shell_data: the parameter & return shell data
 *
 * Return: void
 */
void find_executable(shell_data_t *shell_data)
{
	char *path = NULL;
	int i, k;

	shell_data->executable_path = shell_data->arguments[0];
	if (shell_data->linecount_flag == 1)
	{
		shell_data->line_count++;
		shell_data->linecount_flag = 0;
	}
	for (i = 0, k = 0; shell_data->arg[i]; i++)
		if (!is_delimiter(shell_data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(shell_data, _get_env_variable(shell_data, "PATH="), shell_data->arguments[0]);
	if (path)
	{
		shell_data->executable_path = path;
		fork_executable(shell_data);
	}
	else
	{
		if ((is_interactive(shell_data) || _get_env_variable(shell_data, "PATH=")
					|| shell_data->arguments[0][0] == '/') && is_executable(shell_data, shell_data->arguments[0]))
			fork_executable(shell_data);
		else if (*(shell_data->arg) != '\n')
		{
			shell_data->status = 127;
			print_error(shell_data, "not found\n");
		}
	}
}

/**
 * fork_executable - forks an exec thread to run the executable
 * @shell_data: the parameter & return shell data
 *
 * Return: void
 */
void fork_executable(shell_data_t *shell_data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shell_data->executable_path, shell_data->arguments, get_environ(shell_data)) == -1)
		{
			free_shell_data(shell_data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(shell_data->status));
		if (WIFEXITED(shell_data->status))
		{
			shell_data->status = WEXITSTATUS(shell_data->status);
			if (shell_data->status == 126)
				print_error(shell_data, "Permission denied\n");
		}
	}
}
