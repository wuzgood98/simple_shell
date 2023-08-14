#include "shell.h"

/**
 * char_swap - swaps & and | for non-printed chars
 * @input: input string
 * @bool: type of swap as int
 *
 * Return: the swapped string
 */
char *char_swap(char *input, int bool)
{
	int index;

	if (bool == 0)
	{
		for (index = 0; input[index]; index++)
		{
			if (input[index] == '&')
			{
				if (input[index + 1] != '&')
					input[index] = 12;
				else
					index++;
			}
			if (input[index] == '|')
			{
				if (input[index + 1] != '|')
					input[index] = 16;
				else
					index++;
			}
		}
	}
	else
	{
		for (index = 0; input[index]; index++)
		{
			input[index] = (input[index] == 16 ? '|' : input[index]);
			input[index] = (input[index] == 12 ? '&' : input[index]);
		}
	}
	return (input);
}

/**
 * add_nodes - adds separators and command lines in the lists
 * of type list_s.
 * @sep_head: the head of separator list
 * @line_head: the head of command lines list
 * @input: the input string
 *
 * Return: nothing
 */
void add_nodes(list_s **sep_head, lines **line_head, char *input)
{
	char *temp;
	int index;

	input = char_swap(input, 0);

	for (index = 0; input[index]; index++)
	{
		if (input[index] == ';')
			add_sep_end(sep_head, input[index]);
		if (input[index] == '|' || input[index] == '&')
		{
			add_sep_end(sep_head, input[index]);
			index++;
		}
	}
	temp = _strtok(input, ";|&");
	do {
		temp = char_swap(temp, 1);
		add_line_end(line_head, temp);
		temp = _strtok(NULL, ";|&");
	} while (temp != NULL);
}

/**
 * to_next - go to the next command line
 * @sep_list: separator list of type list_s
 * @line_list: command line list of type lines
 * @data: data structure of type shell_data
 *
 * Return: nothing
 */
void to_next(list_s **sep_list, lines **line_list, shell_data *data)
{
	list_s *seps;
	int sep_loop;
	lines *lns;

	seps = *sep_list;
	lns = *line_list;
	sep_loop = 1;

	while (sep_loop && seps != NULL)
	{
		if (data->status == 0)
		{
			if (seps->separator == '&' || seps->separator == ';')
				sep_loop = 0;
			if (seps->separator == '|')
				lns = lns->next, seps = seps->next;
		}
		else
		{
			if (seps->separator == '|' || seps->separator == ';')
				sep_loop = 0;
			if (seps->separator == '&')
				lns = lns->next, seps = seps->next;
		}
		if (!sep_loop && seps != NULL)
			seps = seps->next;
	}
	*sep_list = seps;
	*line_list = lns;
}

/**
 * sep_commands - splits command lines according to
 * the separators |, ; and &, and executes them.
 * @data: data structure of type shell_data
 * @input: input string
 *
 * Return: 1 to continue, 0 to exit
 */
int sep_commands(shell_data *data, char *input)
{
	lines *line_head, *line_list;
	list_s *sep_head, *sep_list;
	int line;

	line_head = NULL;
	sep_head = NULL;

	add_nodes(&sep_head, &line_head, input);

	line_list = line_head;
	sep_list = sep_head;

	while (line_list != NULL)
	{
		data->input = line_list->line;
		data->args = sep_line(data->input);
		line = find_line(data);
		free(data->args);

		if (line == 0)
			break;

		to_next(&sep_list, &line_list, data);

		if (line_list != NULL)
			line_list = line_list->next;
	}

	free_seps(&sep_head);
	free_lines(&line_head);

	if (line == 0)
		return (0);
	return (1);
}

/**
 * sep_line - tokenizes the input string
 * @input: input string.
 *
 * Return: separated string.
 */
char **sep_line(char *input)
{
	char *temp, **temps;
	size_t index = 1, buf_size;

	buf_size = T_BUF_SIZE;
	temps = malloc(sizeof(char *) * (buf_size));
	if (temps == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	temp = _strtok(input, T_LIM);
	temps[0] = temp;

	while (temp != NULL)
	{
		if (index == buf_size)
		{
			buf_size += T_BUF_SIZE;
			temps = _realloc_dp(temps, index, sizeof(char *) * (buf_size));
			if (temps == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		temp = _strtok(NULL, T_LIM);
		temps[index] = temp;
		index++;
	}
	return (temps);
}
