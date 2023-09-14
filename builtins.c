#include "shell.h"

/**
 * builtins - Check and execute the builtins
 *
 * @info: Information about the shell
 * @arguments: Commands and arguments
 *
 * Return: If the command passed is a builtins
 * return _TRUE if not return _FALSE
 **/
int builtins(shell_t *info, char **arguments)
{
	int status;

	status = check_builtin(info, arguments);
	if (status == _FALSE)
		return (_FALSE);

	return (_TRUE);
}


/**
 * check_builtin - Check if the actual command is a builtin_t
 * or not
 *
 * @info: General information about the shell
 * @arguments: Arguments of the command
 *
 * Return: If the command is an actual builtin, return _TRUE
 * if not _FALSE
 **/
int check_builtin(shell_t *info, char **arguments)
{
	int i, size;
	builtin_t builtins[] = {
		{"exit", shell_exit},
		{"env", shell_env}
	};

	size = sizeof(builtins) / sizeof(builtins[0]);
	for (i = 0; i < size; i++)
	{
		if (_strcmp(info->command, builtins[i].cmd) == 0)
		{
			builtins[i].func(info, arguments);
			return (_TRUE);
		}
	}

	return (_FALSE);
}
