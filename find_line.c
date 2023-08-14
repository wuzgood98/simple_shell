#include "shell.h"

/**
 * find_line - finds commands and builtins.
 * @data: data of type shell_data relevant (args).
 *
 * Return: 1 on success.
 */
int find_line(shell_data *data)
{
	int (*builtin)(shell_data *data);

	if (data->args[0] == NULL)
		return (1);

	builtin = find_builtin(data->args[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (exec_cmd(data));
}
