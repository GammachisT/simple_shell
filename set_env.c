#include "shell.h"

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @info: General info about the data
 * structure of shell (environ)
 * Return: no return
 */
void set_env(char *name, char *value, shell_t *info)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; info->_environ[i]; i++)
	{
		var_env = _strdup(info->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(info->_environ[i]);
			info->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	info->_environ = _reallocdp(info->_environ, i, sizeof(char *) * (i + 2));
	info->_environ[i] = copy_info(name, value);
	info->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @info: info about the data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(shell_t *info)
{

	if (info->args[1] == NULL || info->args[2] == NULL)
	{
		get_error(info, -1);
		return (1);
	}

	set_env(info->args[1], info->args[2], info);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @info: info aboout data shell (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shell_t *info)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (info->args[1] == NULL)
	{
		get_error(info, -1);
		return (1);
	}
	k = -1;
	for (i = 0; info->_environ[i]; i++)
	{
		var_env = _strdup(info->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, info->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(info, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; info->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = info->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(info->_environ[k]);
	free(info->_environ);
	info->_environ = realloc_environ;
	return (1);
}
