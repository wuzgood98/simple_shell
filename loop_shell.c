#include "shell.h"

/**
 * no_comment - removes comments from the input
 * @in: input string
 *
 * Return: input with no comments
 */
char *no_comment(char *in)
{
	int limit, i;

	limit = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				limit = i;
		}
	}

	if (limit != 0)
	{
		in = _realloc(in, i, limit + 1);
		in[limit] = '\0';
	}

	return (in);
}

/**
 * loop_shell - Loop of shell
 * @data: data relevant (av, input, args)
 *
 * Return: nothing.
 */
void loop_shell(shell_data *data)
{
	char *input;
	int i, loop;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_input(&i);
		if (i != -1)
		{
			input = no_comment(input);
			if (input == NULL)
				continue;

			if (find_syntax_error(data, input) == 1)
			{
				data->status = 2;
				free(input);
				continue;
			}
			input = replc_var(input, data);
			loop = sep_commands(data, input);
			data->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
