#include "shell.h"

/**
 * reverse_string - reverses a string.
 * @str: string to reverse.
 *
 * Return: nothing.
 */
void reverse_string(char *str)
{
	char *string, temp_str;
	int i, j, cnt = 0;

	while (cnt >= 0)
	{
		if (str[cnt] == '\0')
			break;
		cnt++;
	}

	string = str;

	for (i = 0; i < (cnt - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp_str = *(string + j);
			*(string + j) = *(string + (j - 1));
			*(string + (j - 1)) = temp_str;
		}
	}
}
