#include "shell.h"

/**
 * find_env - checks if the variable is an env variable
 * @head: head of the linked list
 * @in: input string
 * @data: data structure of type shell_data
 *
 * Return: nothing.
 */
void find_env(var_s **head, char *in, shell_data *data)
{
	int chr, row, len_val, j;
	char **_env;

	_env = data->env;
	for (row = 0; _env[row]; row++)
	{
		for (j = 1, chr = 0; _env[row][chr]; chr++)
		{
			if (_env[row][chr] == '=')
			{
				len_val = _strlen(_env[row] + chr + 1);
				add_node(head, j, _env[row] + chr + 1, len_val);
				return;
			}

			if (in[j] == _env[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_node(head, j, NULL, 0);
}

/**
 * find_vars - checks if the variable is $$ or $?
 * @head: the head of the linked list of type var_s
 * @in: input string
 * @stat: status of the Shell
 * @data: data of type shell_data
 *
 * Return: index of the variable
 */
int find_vars(var_s **head, char *in, char *stat, shell_data *data)
{
	int i, last, last_pid;

	last = _strlen(stat);
	last_pid = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_node(head, 2, stat, last), i++;
			else if (in[i + 1] == '$')
				add_node(head, 2, data->pid, last_pid), i++;
			else if (in[i + 1] == '\n')
				add_node(head, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_node(head, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_node(head, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_node(head, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_node(head, 0, NULL, 0);
			else
				find_env(head, in + i, data);
		}
	}

	return (i);
}

/**
 * change_input - replaces string into variables
 * @head: head of the linked list of type var_s
 * @in: input string
 * @n_in: new input string to replace with
 * @len: length
 *
 * Return: the replaced string
 */
char *change_input(var_s **head, char *in, char *n_in, int len)
{
	int i, j, k;
	var_s *index;

	index = *head;
	for (j = i = 0; i < len; i++)
	{
		if (in[j] == '$')
		{
			if (!(index->var_len) && !(index->val_len))
			{
				n_in[i] = in[j];
				j++;
			}
			else if (index->var_len && !(index->val_len))
			{
				for (k = 0; k < index->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->val_len; k++)
				{
					n_in[i] = index->value[k];
					i++;
				}
				j += (index->var_len);
				i--;
			}
			index = index->next;
		}
		else
		{
			n_in[i] = in[j];
			j++;
		}
	}

	return (n_in);
}

/**
 * replc_var - calls functions to replace string into vars
 * @input: input string
 * @data: data structure
 *
 * Return: the replaced string
 */
char *replc_var(char *input, shell_data *data)
{
	int new_len, old_len;
	var_s *index, *head;
	char *new_input, *status;

	status = intostr(data->status);
	head = NULL;

	old_len = find_vars(&head, input, status, data);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	new_len = 0;

	while (index != NULL)
	{
		new_len += (index->var_len - index->var_len);
		index = index->next;
	}

	new_len += old_len;

	new_input = malloc(sizeof(char) * (new_len + 1));
	new_input[new_len] = '\0';

	new_input = change_input(&head, input, new_input, new_len);

	free(input);
	free(status);
	free_list(&head);

	return (new_input);
}
