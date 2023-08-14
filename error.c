#include "shell.h"

/**
 * cd_strcat - concats the message for cd error.
 * @data: data of type shell_data.
 * @msg: the message to print.
 * @err: the message output.
 * @line_cnt: the lines of the counter.
 *
 * Return: the error message.
 */
char *cd_strcat(shell_data *data, char *msg, char *err, char *line_cnt)
{
	char *wrong_flag;

	_strcpy(err, data->arg_v[0]);
	_strcat(err, ": ");
	_strcat(err, line_cnt);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, msg);
	if (data->args[1][0] == '-')
	{
		wrong_flag = malloc(3);
		wrong_flag[0] = '-';
		wrong_flag[1] = data->args[1][1];
		wrong_flag[2] = '\0';
		_strcat(err, wrong_flag);
		free(wrong_flag);
	}
	else
	{
		_strcat(err, data->args[1]);
	}
	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * find_cd_error - error message for cd command in find_cd
 * @data: data of type shell_data.
 *
 * Return: the error message
 */
char *find_cd_error(shell_data *data)
{
	char *err, *msg, *line_cnt;
	int len_id, len;

	line_cnt = intostr(data->counter);
	if (data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(data->args[1]);
	}

	len = _strlen(data->arg_v[0]) + _strlen(data->args[0]);
	len += _strlen(line_cnt) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(line_cnt);
		return (NULL);
	}

	err = cd_strcat(data, msg, err, line_cnt);

	free(line_cnt);

	return (err);
}

/**
 * not_found_error - the generic error message for command not found.
 * @data: data of type shell_data relevant (counter, arguments).
 *
 * Return: the error message
 */
char *not_found_error(shell_data *data)
{
	int len;
	char *line_cnt, *err;

	line_cnt = intostr(data->counter);
	len = _strlen(data->arg_v[0]) + _strlen(line_cnt);
	len += _strlen(data->args[0]) + 16;
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
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(line_cnt);
	return (err);
}

/**
 * quit_shell_error - generic error message for exit in find_exit.
 * @data: data of type shell_data relevant (counter, arguments).
 *
 * Return: the error message.
 */
char *quit_shell_error(shell_data *data)
{
	int len;
	char *line_cnt, *err;

	line_cnt = intostr(data->counter);
	len = _strlen(data->arg_v[0]) + _strlen(line_cnt);
	len += _strlen(data->args[0]) + _strlen(data->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(line_cnt);
		return (NULL);
	}
	_strcpy(err, data->arg_v[0]);
	_strcat(err, ": ");
	_strcat(err, line_cnt);
	_strcat(err, ": ");
	_strcat(err, data->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, data->args[1]);
	_strcat(err, "\n\0");
	free(line_cnt);

	return (err);
}
