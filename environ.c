#include "shell.h"

/**
 * bin_env - Implementation for the env builtin
 *
 * @info: General information about the shell
 * @arguments: Command
 **/
void shell_env(shell_t *info, char **arguments)
{
	(void) info;
	(void) arguments;

	get_environment();
}

/**
 * _getenv - Get a environment variable
 *
 * @name: Environment variable to get
 *
 * Return: On success value of @name
 * On error, NULL
 **/
char *_getenv(const char *name)
{
	char **env;
	char *aux, *token, *value;
	int size;

	size = _strlen((char *) name);

	for (env = environ; *env; ++env)
	{
		aux = _strdup(*env);

		token = strtok(aux, "=");
		if (token == NULL)
		{
			free(aux);
			return (NULL);
		}

		if (_strlen(token) != size)
		{
			free(aux);
			continue;
		}

		if (_strcmp((char *) name, aux) == 0)
		{
			token = strtok(NULL, "=");
			value = _strdup(token);

			free(aux);
			return (value);
		}

		free(aux);
	}

	return (NULL);
}

/**
 * find_dir - Find the directory needed
 *
 * @filename: Command received
 * @info: General info about the shell
 *
 * Return: pointer string with found path or NULL in failure.
 */
char *find_dir(char *filename, shell_t *info)
{
	char *path, *tmp_path, *token;
	char *slash;
	int size;

	(void) info;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	token = strtok(path, ":");

	size = _strlen(filename) + 2;
	slash = malloc(size * sizeof(char));
	slash = _strcpy(slash, "/");
	slash = _strcat(slash, filename);

	while (token != NULL)
	{
		tmp_path = malloc(_strlen(token) + size);
		tmp_path = _strcpy(tmp_path, token);
		tmp_path = _strcat(tmp_path, slash);

		if (executable(tmp_path) == PERMISSIONS)
		{
			free(slash);
			free(path);
			return (tmp_path);
		}
		token = strtok(NULL, ":");

		free(tmp_path);
	}

	free(path);
	free(slash);

	return (NULL);
}

/**
 * current_path -	Check the order of the path
 *
 * @path: PATH to check
 * @info: General infor about the shell
 **/
void current_path(char *path, shell_t *info)
{
	info->current_path = _FALSE;

	if (path == NULL)
		return;

	if (path[0] == ':')
		info->current_path = _TRUE;
}

/**
 * get_environment - Get all the environment
 **/
void get_environment(void)
{
	char **tmp;
	int i;

	for (i = 0, tmp = environ; tmp[i] != NULL; i++)
	{
		print(tmp[i]);
		_putchar('\n');
	}
}
