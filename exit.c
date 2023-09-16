#include "shell.h"

/**
 * exit_shell - exits the shell
 *
 * @info: info about the shell (status and args)
 * Return: 0 on success.
 */
int exit_shell(shell_t *info)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (info->args[1] != NULL)
	{
		ustatus = _atoi(info->args[1]);
		is_digit = _isdigit(info->args[1]);
		str_len = _strlen(info->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(info, 2);
			info->status = 2;
			return (1);
		}
		info->status = (ustatus % 256);
	}
	return (0);
}

/**
 * exit_shell_error - generic error message for exit in get_exit
 * @info: info about data shell (counter, arguments)
 *
 * Return: Error message
 */
char *exit_shell_error(shell_t *info)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(info->counter);
	length = _strlen(info->av[0]) + _strlen(ver_str);
	length += _strlen(info->args[0]) + _strlen(info->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, info->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, info->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}

/**
 * help_exit - Help information fot the builint exit
 * Return: no return
 */
void help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
