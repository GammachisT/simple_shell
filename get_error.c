#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @info: information data of the shell that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(shell_t *info, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = env_error(info);
		break;
	case 126:
		error = path_error_126(info);
		break;
	case 127:
		error = error_not_found(info);
		break;
	case 2:
		if (_strcmp("exit", info->args[0]) == 0)
			error = exit_shell_error(info);
		else if (_strcmp("cd", info->args[0]) == 0)
			error = get_cd_error(info);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	info->status = eval;
	return (eval);
}
