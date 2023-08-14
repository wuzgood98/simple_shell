#include "shell.h"

int num_len(int num);

/**
 * intostr - converts int to string.
 * @num: int to convert.
 *
 * Return: converted int.
 */
char *intostr(int num)
{
	int len = num_len(num);
	unsigned int num1;
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		*(buffer + len) = (num1 % 10) + '0';
		num1 = num1 / 10;
		len--;
	}
	while (num1 > 0)
		;
	return (buffer);
}

/**
 * num_len - Find the length of a number.
 * @num: number to find its length.
 *
 * Return: the length of the number.
 */
int num_len(int num)
{
	int len = 1;
	unsigned int num1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}

	while (num1 > 9)
	{
		len++;
		num1 = num1 / 10;
	}

	return (len);
}

/**
 * _atoi - converts a string to an integer.
 * @str: input string.
 * Return: integer.
 */
int _atoi(char *str)
{
	unsigned int count = 0, size = 0, item = 0, temp = 1, n = 1, index;

	while (*(str + count) != '\0')
	{
		if (size > 0 && (*(str + count) < '0' || *(str + count) > '9'))
			break;

		if (*(str + count) == '-')
			temp *= -1;

		if ((*(str + count) >= '0') && (*(str + count) <= '9'))
		{
			if (size > 0)
				n *= 10;
			size++;
		}
		count++;
	}

	for (index = count - size; index < count; index++)
	{
		item = item + ((*(str + index) - 48) * n);
		n /= 10;
	}
	return (item * temp);
}
