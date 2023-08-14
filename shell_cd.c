#include "shell.h"

/**
 * shell_cd - changes the current directory
 * @data: data of type shell_data relevant
 *
 * Return: 1 on success
 */
int shell_cd(shell_data *data)
{
	int is_d_home, is_tilde, is_db_dash;
	char *dir;

	dir = data->args[1];

	if (dir != NULL)
	{
		is_d_home = _strcmp("$HOME", dir);
		is_tilde = _strcmp("~", dir);
		is_db_dash = _strcmp("--", dir);
	}

	if (!is_d_home || !is_tilde || !is_db_dash || dir == NULL)
	{
		cd_to_home(data);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_to_previous(data);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_to_parent(data);
		return (1);
	}

	cd_to(data);

	return (1);
}
