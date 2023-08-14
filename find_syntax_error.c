#include "shell.h"

/**
 * repeated_char_cnt - counts the repetitions of a char
 * @input: input string
 * @i: index
 *
 * Return: the number of repetitions of the char
 */
int repeated_char_cnt(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char_cnt(input - 1, i + 1));

	return (i);
}

/**
 * error_op - finds syntax errors
 * @input: input string
 * @i: index
 * @last: last char read
 *
 * Return: the index of error, otherwise 0.
 */
int error_op(char *input, int i, char last)
{
	int cnt;

	cnt = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			cnt = repeated_char_cnt(input, 0);
			if (cnt == 0 || cnt > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			cnt = repeated_char_cnt(input, 0);
			if (cnt == 0 || cnt > 1)
				return (i);
		}
	}

	return (error_op(input + 1, i + 1, *input));
}

/**
 * first_char_idx - finds index of the first char
 * @input: input string
 * @i: index
 *
 * Return: 1 if there is an error, otherwise 0.
 */
int first_char_idx(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * display_syntax_error - prints when a syntax error is found
 * @data: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 *
 * Return: no return
 */
void display_syntax_error(shell_data *data, char *input, int i, int bool)
{
	int len;
	char *msg, *msg2, *msg3, *error, *counter;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = intostr(data->counter);
	len = _strlen(data->arg_v[0]) + _strlen(counter);
	len += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, data->arg_v[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, len);
	free(error);
	free(counter);
}

/**
 * find_syntax_error - intermediate function to
 * find and print a syntax error
 * @data: data structure of type shell_data
 * @input: input string
 *
 * Return: 1 if there is an error, otherwise 0.
 */
int find_syntax_error(shell_data *data, char *input)
{
	int start = 0;
	int first_char = 0;
	int i = 0;

	first_char = first_char_idx(input, &start);
	if (first_char == -1)
	{
		display_syntax_error(data, input, start, 0);
		return (1);
	}

	i = error_op(input + start, 0, *(input + start));
	if (i != 0)
	{
		display_syntax_error(data, input, start + i, 1);
		return (1);
	}

	return (0);
}
