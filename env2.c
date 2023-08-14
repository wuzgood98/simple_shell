#include "shell.h"

/**
 * props_copy - copies the info to create a new alias or env
 * @name: name (alias or env)
 * @value: value (alias or env)
 *
 * Return: the new alias or env.
 */
char *props_copy(char *name, char *value)
{
	char *data;
	int len, name_len, value_len;

	name_len = _strlen(name);
	value_len = _strlen(value);
	len = name_len + value_len + 2;
	data = malloc(sizeof(char) * (len));
	_strcpy(data, name);
	_strcat(data, "=");
	_strcat(data, value);
	_strcat(data, "\0");

	return (data);
}

/**
 * set_env - sets an env variable
 * @name: the name of the env variable
 * @value: the value of the env variable
 * @data: data structure of type shell_data
 *
 * Return: nothing.
 */
void set_env(char *name, char *value, shell_data *data)
{
	char *env_var, *env_name;
	int i = 0;

	while (data->env[i])
	{
		env_var = _strdup(data->env[i]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, name) == 0)
		{
			free(data->env[i]);
			data->env[i] = props_copy(env_name, value);
			free(env_var);
			return;
		}
		free(env_var);
		i++;
	}

	data->env = _realloc_dp(data->env, i, sizeof(char *) * (i + 2));
	data->env[i] = props_copy(name, value);
	data->env[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * @data: data of type shell_data relevant (env value and env name)
 *
 * Return: 1 on success.
 */
int _setenv(shell_data *data)
{

	if (data->args[1] == NULL || data->args[2] == NULL)
	{
		find_error(data, -1);
		return (1);
	}

	set_env(data->args[1], data->args[2], data);

	return (1);
}

/**
 * _unsetenv - removes an env variable
 * @data: data of type shell_data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shell_data *data)
{
	int i, j, k;
	char **env_realloc;
	char *env_name, *env_var;

	if (data->args[1] == NULL)
	{
		find_error(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->env[i]; i++)
	{
		env_var = _strdup(data->env[i]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, data->args[1]) == 0)
		{
			k = i;
		}
		free(env_var);
	}
	if (k == -1)
	{
		find_error(data, -1);
		return (1);
	}
	env_realloc = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->env[i]; i++)
	{
		if (i != k)
		{
			env_realloc[j] = data->env[i];
			j++;
		}
	}
	env_realloc[j] = NULL;
	free(data->env[k]);
	free(data->env);
	data->env = env_realloc;
	return (1);
}
