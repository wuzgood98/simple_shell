#include "shell.h"

/**
 * find_builtin - find builtin that pais the command
 * in the arg.
 * @command: command input of type char
 *
 * Return: a function pointer of the found builtin command.
 */
int (*find_builtin(char *command))(shell_data *)
{
	builtin_list builtin[] = {
		{ "env", _env },
		{ "exit", quit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", shell_cd },
		{ "help", find_help },
		{ NULL, NULL }
	};
	int index = 0;

	while (builtin[index].name)
	{
		if (_strcmp(builtin[index].name, command) == 0)
			break;
		index++;
	}
	return (builtin[index].func);
}
