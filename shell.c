#include "shell.h"

/**
 * set_data - Initialize data structure
 *
 * @info: info about the shell
 * @av: argument vector
 * Return: no return
 */
void set_data(shell_t *info, char **av)
{
	unsigned int i;

	info->av = av;
	info->input = NULL;
	info->args = NULL;
	info->status = 0;
	info->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	info->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		info->_environ[i] = _strdup(environ[i]);
	}

	info->_environ[i] = NULL;
	info->pid = aux_itoa(getpid());
}

/**
 * free_data - frees data structure
 *
 * @info: information about the shell
 * Return: no return
 */
void free_data(shell_t *info)
{
	unsigned int i;

	for (i = 0; info->_environ[i]; i++)
	{
		free(info->_environ[i]);
	}

	free(info->_environ);
	free(info->pid);
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	shell_t info;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&info, av);
	shell_loop(&info);
	free_data(&info);
	if (info.status < 0)
		return (255);
	return (info.status);
}
