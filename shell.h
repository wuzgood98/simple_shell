#ifndef _shell_
#define _shell_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>

#define BUF_SIZE 1024
#define T_LIM " \t\r\n\a"
#define T_BUF_SIZE 128

/* Pointer to an array of pointers to strings called the 'environment' */
extern char **env;

/**
 * struct shell - contains all the relevant data on runtime.
 * @arg_v: argument vector
 * @input: command line written by the user.
 * @args: token of the command line.
 * @status: last status of the shell
 * @counter: lines counter.
 * @env: environemt variable.
 * @pid: process ID of the shell.
 */
typedef struct shell
{
	char **arg_v;
	char *input;
	char **args;
	int status;
	int counter;
	char **env;
	char *pid;
} shell_data;

void free_data(shell_data *data);

#endif
