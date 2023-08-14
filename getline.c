#include "shell.h"

/**
 * assign_line - assigns the line var for _getline
 * @lineptr: pointer to the line that store the input str
 * @buffer: string that is called to line
 * @n: the size of the line
 * @b: the size of the buffer
 *
 * Return: nothing.
 */
void assign_line(char **lineptr, size_t *n, char *buffer, size_t b)
{

	if (*lineptr == NULL)
	{
		if  (b > BUF_SIZE)
			*n = b;

		else
			*n = BUF_SIZE;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > BUF_SIZE)
			*n = b;
		else
			*n = BUF_SIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - reads input from stream.
 * @lineptr: pointer to the buffer that stores the input.
 * @n: size of lineptr.
 * @stream: the stream to read from.
 *
 * Return: the number of bytes.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t val;
	int index;
	char *buffer;
	char z = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUF_SIZE);
	if (buffer == 0)
		return (-1);
	while (z != '\n')
	{
		index = read(STDIN_FILENO, &z, 1);
		if (index == -1 || (index == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (index == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUF_SIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = z;
		input++;
	}
	buffer[input] = '\0';
	assign_line(lineptr, n, buffer, input);
	val = input;
	if (index != 0)
		input = 0;
	return (val);
}
