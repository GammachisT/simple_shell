#include "shell.h"

/**
 * test_patterns - Entry Point
 * @info: input
 * @arguments: input
**/

void test_patterns(shell_t *info, char **arguments)
{
	int i;

	for (i = 0; arguments[i] != NULL; i++)
		arguments[i] = pattern_handler(info, arguments[i]);
}

/**
 * pattern_handler - Entry Point
 * @info: input
 * @string: input
 * Return: string
**/

char *pattern_handler(shell_t *info, char *string)
{
	int i;

	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == '$' && string[i + 1] != '\0')
			string = replace_value(info, &i, string);
	}

	return (string);
}

/**
 * replace_value - Entry Point
 * @info: input
 * @index: input
 * @string: input
 * Return: string
**/

char *replace_value(shell_t *info, int *index, char *string)
{
	int i, new_s, old_s;
	char *value;

	i = *index;
	i++;

	value = replacement(info, index, string + i);
	if (value == NULL)
	{
		string = _strcpy(string, "");

		return (string);
		;
	}

	old_s = _strlen(string);
	new_s = _strlen(value) + 1;

	string = _realloc(string, old_s, new_s);
	string = _strcpy(string, value);

	free_memory_p(value);
	*index = i;
	return (string);
}

/**
 * replacement - Entry point
 * @info: input
 * @index: input
 * @string: input
 * Return: string
**/

char *replacement(shell_t *info, int *index, char *string)
{
	char *tmp;
	char symbol;

	(void) index;

	symbol = *string;
	if (symbol != '?' && symbol != '$')
	{
		tmp = replace_env(info, string);
		return (tmp);
	}

	tmp = (symbol == '$') ? to_string(info->pid) :
		to_string(info->status_code);

	return (tmp);
}

/**
 * replace_env - Entry Point
 * @info: input
 * @environment: input
 * Return: string
**/

char *replace_env(shell_t *info, char *environment)
{
	char *env;

	(void) info;

	env = _getenv(environment);
	if (env != NULL)
		return (env);

	return (NULL);
}
