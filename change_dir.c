#include "shell.h"

/**
 * cd_to_parent - changes to the parent directory
 * @data: data of type shell_data relevant (environ)
 *
 * Return: no return
 */
void cd_to_parent(shell_data *data)
{
	char pwd[PATH_MAX];
	char *dir, *pwd_copy, *pwd_strtok_copy;

	getcwd(pwd, sizeof(pwd));
	pwd_copy = _strdup(pwd);
	set_env("OLDPWD", pwd_copy, data);
	dir = data->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", pwd_copy, data);
		free(pwd_copy);
		return;
	}
	if (_strcmp("/", pwd_copy) == 0)
	{
		free(pwd_copy);
		return;
	}
	pwd_strtok_copy = pwd_copy;
	reverse_string(pwd_strtok_copy);
	pwd_strtok_copy = _strtok(pwd_strtok_copy, "/");
	if (pwd_strtok_copy != NULL)
	{
		pwd_strtok_copy = _strtok(NULL, "\0");

		if (pwd_strtok_copy != NULL)
			reverse_string(pwd_strtok_copy);
	}
	if (pwd_strtok_copy != NULL)
	{
		chdir(pwd_strtok_copy);
		set_env("PWD", pwd_strtok_copy, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->status = 0;
	free(pwd_copy);
}

/**
 * cd_to - changes to the directory given by the user
 * @data: data of type shell_data relevant (directories)
 *
 * Return: nothing
 */
void cd_to(shell_data *data)
{
	char pwd[PATH_MAX];
	char *dir, *pwd_copy, *dir_copy;

	getcwd(pwd, sizeof(pwd));

	dir = data->args[1];
	if (chdir(dir) == -1)
	{
		find_error(data, 2);
		return;
	}

	pwd_copy = _strdup(pwd);
	set_env("OLDPWD", pwd_copy, data);

	dir_copy = _strdup(dir);
	set_env("PWD", dir_copy, data);

	free(pwd_copy);
	free(dir_copy);

	data->status = 0;

	chdir(dir);
}

/**
 * cd_to_previous - changes dir to the previous dir
 * @data: data of type shell_data relevant (environ)
 *
 * Return: nothing
 */
void cd_to_previous(shell_data *data)
{
	char pwd[PATH_MAX];
	char *prv_pwd, *prv_oldpwd, *pwd_copy, *oldpwd_copy;

	getcwd(pwd, sizeof(pwd));
	pwd_copy = _strdup(pwd);

	prv_oldpwd = findenv("OLDPWD", data->env);

	if (prv_oldpwd == NULL)
		oldpwd_copy = pwd_copy;
	else
		oldpwd_copy = _strdup(prv_oldpwd);

	set_env("OLDPWD", pwd_copy, data);

	if (chdir(oldpwd_copy) == -1)
		set_env("PWD", pwd_copy, data);
	else
		set_env("PWD", oldpwd_copy, data);

	prv_pwd = findenv("PWD", data->env);

	write(STDOUT_FILENO, prv_pwd, _strlen(prv_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(pwd_copy);
	if (prv_oldpwd)
		free(oldpwd_copy);

	data->status = 0;

	chdir(prv_pwd);
}

/**
 * cd_to_home - changes to the home directory
 * @data: data of type shell_data relevant (environ)
 *
 * Return: nothing
 */
void cd_to_home(shell_data *data)
{
	char pwd[PATH_MAX];
	char *prv_pwd, *home_dir;

	getcwd(pwd, sizeof(pwd));
	prv_pwd = _strdup(pwd);

	home_dir = findenv("HOME", data->env);

	if (home_dir == NULL)
	{
		set_env("OLDPWD", prv_pwd, data);
		free(prv_pwd);
		return;
	}

	if (chdir(home_dir) == -1)
	{
		find_error(data, 2);
		free(prv_pwd);
		return;
	}

	set_env("OLDPWD", prv_pwd, data);
	set_env("PWD", home_dir, data);
	free(prv_pwd);
	data->status = 0;
}
