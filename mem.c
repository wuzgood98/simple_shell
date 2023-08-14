#include "shell.h"

/**
 * _memcpy - copies data between void pointers.
 * @dest: destination pointer.
 * @src: source pointer.
 * @size: size of the destination pointer.
 *
 * Return: nothing.
 */
void _memcpy(void *dest, const void *src, unsigned int size)
{
	char *dest_char = (char *)dest;
	char *src_char = (char *)src;
	unsigned int index = 0;

	for (; index < size; index++)
	{
		dest_char[index] = src_char[index];
	}
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size of the allocated space of ptr.
 * @new_size: new size of the new memory block.
 *
 * Return: if new size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(new_ptr, ptr, new_size);
	else
		_memcpy(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}

/**
 * _realloc_dp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size of the allocated space of ptr.
 * @new_size: new size of the new memory block.
 *
 * Return: if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_realloc_dp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **new_ptr;
	unsigned int index = 0;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
		return (NULL);

	for (; index < old_size; index++)
		new_ptr[index] = ptr[index];

	free(ptr);

	return (new_ptr);
}
