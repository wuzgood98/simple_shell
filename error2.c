#include "shell.h"

/**
 * env_error - handle error messages for the env varibles.
 * @data: data of the type shell_data relevant (counter, arguments)
 *
 * Return: the error message.
 */
char *env_error(shell_data *data)
{
	int len;
	char *line_cnt, *err, *msg;

	line_cnt = intostr(data->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(data->arg_v[0]) + _strlen(line_cnt);
	len += _strlen(data->args[0]) + _strlen(msg) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(line_cnt);
		return (NULL);
	}

	_strcpy(err, data->arg_v[0]);
	_strcat(err, ": ");
	_strcat(err, line_cnt);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, msg);
	_strcat(err, "\0");
	free(line_cnt);
	return (err);
}

/**
 * path_126_error - handles error message for path and
 * failure denied permission.
 * @data: data of type shell_data relevant (counter, arguments).
 *
 * Return: the error message.
 */
char *path_126_error(shell_data *data)
{
	int len;
	char *line_cnt, *err;

	line_cnt = intostr(data->counter);
	len = _strlen(data->arg_v[0]) + _strlen(line_cnt);
	len += _strlen(data->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(line_cnt);
		return (NULL);
	}
	_strcpy(err, data->arg_v[0]);
	_strcat(err, ": ");
	_strcat(err, line_cnt);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(line_cnt);
	return (err);
}
