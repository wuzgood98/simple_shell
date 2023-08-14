#include "shell.h"

/**
 * add_node - adds a variable at the end
 * of a var_s list.
 * @head: the head of the linked list of type var_s.
 * @var_len: variable's length.
 * @value: variable's value.
 * @val_len: value's length.
 *
 * Return: the address of the head.
 */
var_s *add_node(var_s **head, int var_len, char *value, int val_len)
{
	var_s *temp, *new_var;

	new_var = malloc(sizeof(var_s));
	if (new_var == NULL)
		return (NULL);

	new_var->var_len = var_len;
	new_var->value = value;
	new_var->val_len = val_len;

	new_var->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_var;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_var;
	}

	return (*head);
}

/**
 * free_list - frees a list of type var_s
 * @head: the head of the linked list of type var_s.
 *
 * Return: nothing.
 */
void free_list(var_s **head)
{
	var_s *current, *temp;

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
