#include "shell.h"

/**
 * prompt - Print the prompt
 *
 * @info: Struct of general information
 **/
void prompt(shell_t *info)
{
	if (info->mode == NON_INTERACTIVE)
		return;

	print("$ ");
}

/**
 * read_prompt - Read lines in the prompt
 *
 * Return: Buffer readed or NULL if EOF was found
 **/
char *read_prompt()
{
	char *buf;
	int res;
	size_t size;

	buf = NULL;

	res = getline(&buf, &size, stdin);

	if (res == EOF)
	{
		free_memory_p((void *) buf);
		return (NULL);
	}

	return (buf);
}

/**
 * get_prompt - Loop reading text
 *
 * @info: Struct of general information
 *
 * Return: Buffer readed or NULL if EOF was found
 **/
void get_prompt(shell_t *info)
{
	char *buff;
	char **arguments;
	char *path;

	signal(SIGINT, sigHandler);
	while (1)
	{
		prompt(info);

		path = _getenv("PATH");
		current_path(path, info);

		info->environment = path;
		buff = read_prompt();
		if (buff == NULL)
		{
			print(info->mode == INTERACTIVE ? "exit\n" : "");
			free(path);
			break;
		}

		info->n_commands++;
		if (buff[0] != '\n')
		{
			arguments = tokenize(buff, " \t\n");

			info->arguments = arguments;
			info->buffer = buff;
			test_patterns(info, arguments);
			analyze(arguments, info, buff);

			free_memory_pp((void *) arguments);
		}

		free_memory_p((void *) buff);
		free_memory_p((void *) path);
	}

}

/**
 * sigHandler - Handler for SIGINT
 *
 * @sig_num: Unused parameter
 **/
void sigHandler(int sig_num)
{
	(void) sig_num;

	signal(SIGINT, sigHandler);
	print("\n$ ");
	fflush(stdout);
}
