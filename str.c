#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 *
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int index;
	int j;

	for (index = 0; dest[index] != '\0'; index++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[index] = src[j];
		index++;
	}

	dest[index] = '\0';
	return (dest);
}

/**
 * _strcpy - Copies the string pointed to by src.
 * @dest: pointer to the dest of the copied str
 * @src: pointer to the source of str
 *
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t c;

	for (c = 0; src[c] != '\0'; c++)
	{
		dest[c] = src[c];
	}
	dest[c] = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings.
 * @str1: type str compared
 * @str2: type str compared
 *
 * Return: Always 0.
 */
int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}

/**
 * _strchr - locates a character in a string,
 * @str: string.
 * @c: character to locate.
 *
 * Return: pointer to the first occurrence of the character c, otherwise NULL.
 */
char *_strchr(char *str, char c)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
		if (*(str + i) == c)
			return (str + i);
	if (*(str + i) == c)
		return (str + i);
	return ('\0');
}

/**
 * _strspn - finds the length of a prefix substring.
 * @str: initial segment.
 * @accept: bytes accepted.
 *
 * Return: number of bytes accepted.
 */
int _strspn(char *str, char *accept)
{
	int bool, i, j;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(str + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
