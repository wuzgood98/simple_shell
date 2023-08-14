#include "shell.h"

/**
 * add_sep_end - adds a separator at the end
 * of a list_s.
 * @head: the head of the linked list of type list_s.
 * @sep: the separator found (; | &).
 *
 * Return: the address of the head.
 */
list_s *add_sep_end(list_s **head, char sep)
{
	list_s *temp, *new_seps;

	new_seps = malloc(sizeof(list_s));
	if (new_seps == NULL)
		return (NULL);

	new_seps->separator = sep;
	new_seps->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_seps;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_seps;
	}
	return (*head);
}

/**
 * free_seps - frees the separator list of type lists_s.
 * @head: the head of the linked list of type lists_s.
 *
 * Return: nothing.
 */
void free_seps(list_s **head)
{
	list_s *current, *temp;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_end - adds a command line at the end
 * of a lines.
 * @head: the head of the linked list.
 * @line: the tcommand line.
 *
 * Return: the address of the head.
 */
lines *add_line_end(lines **head, char *line)
{
	lines *temp, *new_line;

	new_line = malloc(sizeof(lines));
	if (new_line == NULL)
		return (NULL);

	new_line->line = line;
	new_line->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_line;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_line;
	}

	return (*head);
}

/**
 * free_lines - frees a list of type lines
 * @head: the head of the linked list of type lines.
 *
 * Return: nothing.
 */
void free_lines(lines **head)
{
	lines *current, *temp;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
