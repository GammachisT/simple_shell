#include "shell.h"

/**
 * exec_cmd - finds builtins and commands
 *
 * @info: info about shell (args)
 * Return: 1 on success.
 */

int exec_cmd(shell_t *info)
{
	int (*builtin)(shell_t *info);

	if (info->args[0] == NULL)
		return (1);

	builtin = get_builtin(info->args[0]);

	if (builtin != NULL)
		return (builtin(info));

	return (cmd_exec(info));
}
