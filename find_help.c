#include "shell.h"

/**
 * find_help - retrieves help messages according builtin.
 * @data: data structure of type shell_data (input and args).
 *
 * Return: 0
*/
int find_help(shell_data *data)
{

	if (data->args[1] == 0)
		general_help();
	else if (_strcmp(data->args[1], "setenv") == 0)
		setenv_help();
	else if (_strcmp(data->args[1], "env") == 0)
		env_help();
	else if (_strcmp(data->args[1], "unsetenv") == 0)
		unsetenv_help();
	else if (_strcmp(data->args[1], "help") == 0)
		_help();
	else if (_strcmp(data->args[1], "exit") == 0)
		exit_help();
	else if (_strcmp(data->args[1], "cd") == 0)
		cd_help();
	else if (_strcmp(data->args[1], "alias") == 0)
		alias_help();
	else
		write(STDERR_FILENO, data->args[0],
		      _strlen(data->args[0]));

	data->status = 0;
	return (1);
}
