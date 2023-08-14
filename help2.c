#include "shell.h"

/**
 * _help - help information for the builtin help.
 *
 * Return: nothing.
 */
void _help(void)
{
	char *msg = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * cd_help - help information for the builtin alias.
 *
 * Return: nothing.
 */
void cd_help(void)
{
	char *msg = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * alias_help - Help information for the builtin alias.
 *
 * Return: nothing
 */
void alias_help(void)
{
	char *msg = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
