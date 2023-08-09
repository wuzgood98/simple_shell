#include "shell.h"

/**
 * free_data - frees the data structure
 * @data: data to free
 *
 * Return: nothing
 */
void free_data(shell_data *data)
{
	unsigned int index = 0;

	for (; data->env[index]; index++)
	{
		free(data->env[index]);
	}

	free(data->env);
	free(data->pid);
}
