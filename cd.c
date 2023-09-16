#include "shell.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @info: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(shell_t *info)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, info);
	dir = info->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, info);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, info);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", info);
	}
	info->status = 0;
	free(cp_pwd);
}

/**
 * cd_to_dir - changes to a directory given
 * by the user
 *
 * @info: Information data about the shell(directories)
 * Return: no return
 */
void cd_to_dir(shell_t *info)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = info->args[1];
	if (chdir(dir) == -1)
	{
		get_error(info, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, info);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, info);

	free(cp_pwd);
	free(cp_dir);

	info->status = 0;

	chdir(dir);
}

/**
 * cd_to_pre - changes to the previous directory
 *
 * @info: data relevant (environ)
 * Return: no return
 */
void cd_to_pre(shell_t *info)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", info->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, info);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, info);
	else
		set_env("PWD", cp_oldpwd, info);

	p_pwd = _getenv("PWD", info->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	info->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @info: data relevant (environ)
 * Return: no return
 */
void cd_to_home(shell_t *info)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", info->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, info);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(info, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, info);
	set_env("PWD", home, info);
	free(p_pwd);
	info->status = 0;
}

/**
 * change_cd - changes current directory
 *
 * @info: data relevant
 * Return: 1 on success
 */
int change_cd(shell_t *info)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = info->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(info);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_to_pre(info);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(info);
		return (1);
	}

	cd_to_dir(info);

	return (1);
}
