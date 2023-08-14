#include "shell.h"

/**
 * sig_int - Handle the crtl + c call in prompt
 * @signal: Signal handler
 *
 * Return: nothing.
 */
void sig_int(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 5);
}
