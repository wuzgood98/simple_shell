#include "shell.h"

/**
 * general_help - the entry point for help information for the help builtin
 *
 * Return: nothing
 */
void general_help(void)
{
	char *msg = "$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "unsetenv [variable]\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * setenv_help - help information for the builtin setenv.
 *
 * Return: nothing
 */
void setenv_help(void)
{

	char *msg = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "int replace)\n\t";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * env_help - help information for the builtin env
 *
 * Return: nothing
 */
void env_help(void)
{
	char *msg = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));

}

/**
 * unsetenv_help - help information for the builtin unsetenv
 *
 * Return: nothing
 */
void unsetenv_help(void)
{
	char *msg = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * exit_help - help information fot the builint exit
 *
 * Return: nothing
 */
void exit_help(void)
{
	char *msg = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
