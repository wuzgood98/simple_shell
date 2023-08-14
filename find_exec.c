#include "shell.h"

/**
 * find_exec - finds commands and builtins.
 * @data: relevant data of type shell_data.
 *
 * Return: 1 on success.
 */
int find_exec(shell_data *data)
{
	int (*builtin)(shell_data *data);

	if (data->args[0] == NULL)
		return (1);

	builtin = find_builtin(data->args[0]);

	if (builtin != NULL)
	{
		return (builtin(data));
	}
	return (exec_cmd(data));
}
