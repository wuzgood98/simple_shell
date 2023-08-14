#include "shell.h"

/**
 * _env - prints the env variables to stdout.
 * @data: data structure of type shell_data.
 *
 * Return: 1 on success.
 */
int _env(shell_data *data)
{
	int index = 0, j = 0;

	while (data->env[index])
	{
		while (data->env[index][j])
			j++;

		write(STDOUT_FILENO, data->env[index], j);
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	data->status = 0;

	return (1);
}

/**
 * compare_env - compares env variable with the name passed.
 * @env_name: the name of the env variable to compare.
 * @value: value to compare with the env name.
 *
 * Return: a value other than 0 if equal, otherwise 0.
 */
int compare_env(const char *env_name, const char *value)
{
	int index = 0;

	while (env_name[index] != '=')
	{
		if (env_name[index] != value[index])
			return (0);
		index++;
	}
	return (index + 1);
}

/**
 * findenv - find an env variable
 * @env_name: name of the env variable
 * @env_v: env variable
 *
 * Return: the value of the found env variable,
 * otherwise NULL.
 */
char *findenv(const char *env_name, char **env_v)
{
	int index = 0, move;
	char *env_ptr;

	env_ptr = NULL;
	move = 0;

	while (env_v[index])
	{
		move = compare_env(env_v[index], env_name);
		if (move)
		{
			env_ptr = env_v[index];
			break;
		}
		index++;
	}
	return (env_ptr + move);
}
