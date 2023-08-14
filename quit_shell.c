#include "shell.h"

/**
 * quit_shell - quits or exits the shell.
 * @data: data of type shell_data.
 *
 * Return: 0 on success, otherwise 1.
 */
int quit_shell(shell_data *data)
{
	int is_digit, len, num;
	unsigned int stat;

	if (data->args[1] != NULL)
	{
		stat = _atoi(data->args[1]);
		is_digit = _isdigit(data->args[1]);
		len = _strlen(data->args[1]);
		num = stat > (unsigned int)INT_MAX;
		if (len > 10 || !is_digit || num)
		{
			find_error(data, 2);
			data->status = 2;
			return (1);
		}
		data->status = (stat % 256);
	}
	return (0);
}
