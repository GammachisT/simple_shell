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

/**
 * error_syntax - Creates an error sms for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = aux_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}

/**
 * error_permission - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_permission(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = aux_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_get_alias - Creates an error message for shell_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_get_alias(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}
