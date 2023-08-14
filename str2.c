#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: pointer to the type char
 *
 * Return: duplicated string.
 */
char *_strdup(const char *str)
{
	size_t len;
	char *temp;

	len = _strlen(str);
	temp = malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (NULL);
	_memcpy(temp, str, len + 1);
	return (temp);
}

/**
 * _strlen - finds the length of a string.
 * @str: string to find its length.
 *
 * Return: the length of the string
 */
int _strlen(const char *str)
{
	if (*str == '\0')
		return (0);

	return (1 + _strlen(str + 1));
}

/**
 * cmpr_chars - compare chars of strings
 * @strs: input string.
 * @delim: delimiter.
 *
 * Return: 1 if the chars are equal, otherwise 0.
 */
int cmpr_chars(char strs[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; strs[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (strs[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by a delimiter.
 * @strs: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char strs[], const char *delim)
{
	static char *end, *splitted;
	char *start;
	unsigned int i, bool;

	if (strs != NULL)
	{
		if (cmpr_chars(strs, delim))
			return (NULL);
		splitted = strs; /* store the first address */
		i = _strlen(strs);
		end = &strs[i]; /* store the last address */
	}
	start = splitted;
	if (start == end) /* reaching the end of the strings */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == start)
					start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*strs != delim*/
			bool = 1;
	}
	if (bool == 0) /*strs == delim*/
		return (NULL);
	return (start);
}

/**
 * _isdigit - checks if a string is a number
 * @str: char to check
 *
 * Return: 1 if the string is a number, otherwise 0.
 */
int _isdigit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}
