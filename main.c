#include "shell.h"

/**
 * main - checks the code
 * @ac: arguments count.
 * @av: NULL terminated array of strings.
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	shell_data data;
	(void) ac;

	signal(SIGINT, sig_int);
	set_data(&data, av);
	loop_shell(&data);
	free_data(&data);
	if (data.status < 0)
		return (255);
	return (data.status);
}
