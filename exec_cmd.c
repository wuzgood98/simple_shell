#include "shell.h"

/**
 * colon_in_dir - checks ":" if it is in the current directory.
 * @path: pointer of path of type char.
 * @index: pointer of index of type int.
 *
 * Return: 1 if the path is searchable in the cd, otherwise 0.
 */
int colon_in_dir(char *path, int *index)
{
	if (path[*index] == ':')
		return (1);

	while (path[*index] != ':' && path[*index])
	{
		*index += 1;
	}

	if (path[*index])
		*index += 1;

	return (0);
}

/**
 * _which - locate a command.
 * @cmd: name of the command.
 * @env_v: env variable
 *
 * Return: the location of the command.
 */
char *_which(char *cmd, char **env_v)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = findenv("PATH", env_v);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (colon_in_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - checks if it is an executable
 * @data: data structure of type shell_data
 *
 * Return: 0 if is not an executable, otherwise other number
 * if it does.
 */
int is_executable(shell_data *data)
{
	struct stat st;
	char *input;
	int i;

	input = data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	find_error(data, 127);
	return (-1);
}

/**
 * cmd_error_check - checks if the user has permissions to access
 * @dir: the destination directory
 * @data: data structure of type shell_data
 *
 * Return: 1 if there is an error, otherwise 0.
 */
int cmd_error_check(char *dir, shell_data *data)
{
	if (dir == NULL)
	{
		find_error(data, 127);
		return (1);
	}

	if (_strcmp(data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			find_error(data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(data->args[0], X_OK) == -1)
		{
			find_error(data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_cmd - executes command lines
 * @data: data of type shell_data relevant
 * (args and input).
 *
 * Return: 1 on success.
 */
int exec_cmd(shell_data *data)
{
	pid_t w_pd, pd;
	int state, exec;
	char *dir;
	(void) w_pd;

	exec = is_executable(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(data->args[0], data->env);
		if (cmd_error_check(dir, data) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(data->args[0], data->env);
		else
			dir = data->args[0];
		execve(dir + exec, data->args, data->env);
	}
	else if (pd < 0)
	{
		perror(data->arg_v[0]);
		return (1);
	}
	else
	{
		do {
			w_pd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	data->status = state / 256;
	return (1);
}
