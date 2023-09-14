#include "shell.h"

/**
 * analyze - Analyze	the arguments
 *
 * @arguments: Commands and arguments to execute
 * @info: General information about the shell
 * @buff: Line readed
 **/
void analyze(char **arguments, shell_t *info, char *buff)
{
	char *cmd;
	int status;

	if (*arguments == NULL || arguments == NULL)
		return;

	cmd = arguments[0];
	info->command = cmd;
	if (check_builtin(info, arguments) == _TRUE)
		return;

	status = is_file(cmd);
	if (status == NON_PERMISSIONS)
	{
		info->status_code = 126;
		info->error_code = _CODE_EACCES;
		error(info);
		return;
	}

	if (status == 1)
	{
		execute(cmd, arguments, info, buff);
		return;
	}

	if (current_directory(cmd, arguments, buff, info) == _TRUE)
		return;

	info->utility_path = find_dir(cmd, info);
	if (info->utility_path != NULL)
	{
		execute(info->utility_path, arguments, info, buff);
		free_memory_p((void *) info->utility_path);
		return;
	}

	info->status_code = 127;
	info->error_code = _CODE_CMD_NOT_EXISTS;
	error(info);
}
