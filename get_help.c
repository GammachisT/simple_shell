#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @info: info about the shell (args and input)
 * Return: Return 0
*/
int get_help(shell_t *info)
{

	if (info->args[1] == 0)
		general_help();
	else if (_strcmp(info->args[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(info->args[1], "env") == 0)
		help_env();
	else if (_strcmp(info->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(info->args[1], "help") == 0)
		help();
	else if (_strcmp(info->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(info->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(info->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, info->args[0],
		      _strlen(info->args[0]));

	info->status = 0;
	return (1);
}

/**
 * general_help - Entry point for help information
 * for the help builtin
 * Return: no return
 */
void general_help(void)
{
	char *help = "$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_alias - Help information for the builtin alias.
 * Return: no return
 */
void help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
