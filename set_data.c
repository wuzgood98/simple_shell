#include "shell.h"

/**
 * set_data - initializes data
 * @data: data to free
 * @argv: argument vector.
 *
 * Return: nothing
 */
void set_data(shell_data *data, char **argv)
{
	unsigned int index = 0;

	data->arg_v = argv;
	data->input = NULL;
	data->args = NULL;
	data->status = 0;
	data->counter = 1;

	for (; environ[index]; index++)
		;

	data->env = malloc(sizeof(char *) * (index + 1));

	for (index = 0; environ[index]; index++)
	{
		data->env[index] = _strdup(environ[index]);
	}

	data->env[index] = NULL;
	data->pid = intostr(getpid());
}
