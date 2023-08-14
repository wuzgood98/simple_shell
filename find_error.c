#include "shell.h"

/**
 * find_error - finds the error according to the builtin,
 * permission or syntax.
 * @data: data of type shell_data containing arguments;
 * @error_value: value of the error.
 *
 * Return: the found error.
 */
int find_error(shell_data *data, int error_value)
{
	char *error;

	switch (error_value)
	{
		case -1:
			error = env_error(data);
			break;
		case 126:
			error = path_126_error(data);
			break;
		case 127:
			error = not_found_error(data);
			break;
		case 2:
			if (_strcmp("exit", data->args[0]) == 0)
				error = quit_shell_error(data);
			else if (_strcmp("cd", data->args[0]) == 0)
				error = find_cd_error(data);
			break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}
	data->status = error_value;
	return (error_value);
}
