#include "shell.h"

/**
 * strcat_cderror - function that concatenates the message for cd error
 *
 * @info: data relevant (directory)
 * @sms: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cderror(shell_t *info, char *sms, char *error, char *ver_str)
{
	char *ensign;

	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, sms);
	if (info->args[1][0] == '-')
	{
		ensign = malloc(3);
		ensign[0] = '-';
		ensign[1] = info->args[1][1];
		ensign[2] = '\0';
		_strcat(error, ensign);
		free(ensign);
	}
	else
	{
		_strcat(error, info->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * get_cd_error - error message for cd command in get_cd
 * @info: Info about the shell data relevant (directory)
 * Return: Error message
 */
char *get_cd_error(shell_t *info)
{
	int length, len_id;
	char *error, *ver_str, *sms;

	ver_str = aux_itoa(info->counter);
	if (info->args[1][0] == '-')
	{
		sms = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		sms = ": can't cd to ";
		len_id = _strlen(info->args[1]);
	}

	length = _strlen(info->av[0]) + _strlen(info->args[0]);
	length += _strlen(ver_str) + _strlen(sms) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cderror(info, sms, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @info: info about data shell (counter, arguments)
 * Return: Error message
 */
char *error_not_found(shell_t *info)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(info->counter);
	length = _strlen(info->av[0]) + _strlen(ver_str);
	length += _strlen(info->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * env_error - error message for env in get_env.
 * @info: info about data shell (counter, arguments)
 * Return: error message.
 */
char *env_error(shell_t *info)
{
	int length;
	char *error;
	char *ver_str;
	char *sms;

	ver_str = aux_itoa(info->counter);
	sms = ": Unable to add/remove from environment\n";
	length = _strlen(info->av[0]) + _strlen(ver_str);
	length += _strlen(info->args[0]) + _strlen(sms) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, sms);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * path_error_126 - error message for path and failure denied permission.
 * @info: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *path_error_126(shell_t *info)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(info->counter);
	length = _strlen(info->av[0]) + _strlen(ver_str);
	length += _strlen(info->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
