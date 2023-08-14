#include "shell.h"

/**
 * read_input - reads the input string.
 * @i: return value of getline function
 *
 * Return: input string
 */
char *read_input(int *i)
{
	char *input = NULL;
	size_t buf_size = 0;

	*i = getline(&input, &buf_size, stdin);

	return (input);
}
