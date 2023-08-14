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
extern char **environ;

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

/**
 * struct var_data - single linked list
 * @var_len: length of the variable
 * @val_len: length of the value
 * @value: value of the variable
 * @next: next node
 *
 * Description: single linked list to store variables
 */
typedef struct var_data
{
	int var_len;
	int val_len;
	char *value;
	struct var_data *next;
} var_s;

/**
 * struct list_sep - single linked list
 * @separator: & | ;
 * @next: the next node
 *
 * Description: singly linked list to store the separators
 */
typedef struct list_sep
{
	char separator;
	struct list_sep *next;
} list_s;

/**
 * struct lines_l - single linked list
 * @line: the command line
 * @next: the next node
 *
 * Description: singly linked list to store command lines
 */
typedef struct lines_l
{
	char *line;
	struct lines_l *next;
} lines;

/**
 * struct builtins - builtin struct for command arguments.
 * @name: name of the command builtin i.e cd, exit, env
 * @func: function pointer pointer.
 */
typedef struct builtins
{
	char *name;
	int (*func)(shell_data *data);
} builtin_list;

void free_data(shell_data *data);
void set_data(shell_data *data, char **argv);

/* stdlib.c */
int num_len(int num);
char *intostr(int num);
int _atoi(char *str);

/* str2.c */
int _strlen(const char *str);
char *_strdup(const char *str);
int _isdigit(const char *str);
int cmpr_chars(char strs[], const char *delim);
char *_strtok(char strs[], const char *delim);

/* mem.c */
void _memcpy(void *dest, const void *src, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_realloc_dp(char **ptr, unsigned int old_size, unsigned int new_size);

/* sig_int.c */
void sig_int(int signal);

/* loop_shell.c */
char *no_comment(char *in);
void loop_shell(shell_data *data);

/* read_input */
char *read_input(int *i);

/* check_syntax_error.c */
int repeated_char_cnt(char *input, int i);
int error_op(char *input, int i, char last);
int first_char_idx(char *input, int *i);
void display_syntax_error(shell_data *data, char *input, int i, int bool);
int find_syntax_error(shell_data *data, char *input);

/* str.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *src1, char *src2);
char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);

/* replc_var.c */
char *change_input(var_s **head, char *in, char *n_in, int len);
int find_vars(var_s **head, char *in, char *stat, shell_data *data);
void find_env(var_s **head, char *in, shell_data *data);
char *replc_var(char *input, shell_data *data);

/* lists2.c */
var_s *add_node(var_s **head, int var_len, char *value, int val_len);
void free_list(var_s **head);

/* splits_func.c */
char *char_swap(char *input, int bool);
void add_nodes(list_s **sep_head, lines **line_head, char *input);
void to_next(list_s **sep_list, lines **line_list, shell_data *data);
int sep_commands(shell_data *data, char *input);
char **sep_line(char *input);

/* lists.c */
list_s *add_sep_end(list_s **head, char sep);
lines *add_line_end(lines **head, char *line);
void free_lines(lines **head);
void free_seps(list_s **head);

/* find_exec.c */
int find_exec(shell_data *data);

/* find_builtin.c */
int (*find_builtin(char *command))(shell_data *);

/* env.c */
int _env(shell_data *data);
int compare_env(const char *env_name, const char *value);
char *findenv(const char *env_name, char **env_v);

/* env2.c */
char *props_copy(char *name, char *value);
void set_env(char *name, char *value, shell_data *data);
int _setenv(shell_data *data);
int _unsetenv(shell_data *data);

/* quit_shell.c */
int quit_shell(shell_data *data);

/* find_error.c */
int find_error(shell_data *data, int error_value);

/* error.c */
char *quit_shell_error(shell_data *data);
char *not_found_error(shell_data *data);
char *find_cd_error(shell_data *data);
char *cd_strcat(shell_data *data, char *msg, char *err, char *line_cnt);

/* error2.c */
char *env_error(shell_data *data);
char *path_126_error(shell_data *data);

/* change_dir.c */
void cd_to_parent(shell_data *data);
void cd_to(shell_data *data);
void cd_to_previous(shell_data *data);
void cd_to_home(shell_data *data);


/* reverse_string.c */
void reverse_string(char *str);

/* help.c */
void general_help(void);
void setenv_help(void);
void env_help(void);
void unsetenv_help(void);
void exit_help(void);

/* help2.c */
void _help(void);
void cd_help(void);
void alias_help(void);

/* shell_cd.c */
int shell_cd(shell_data *data);

/* find_help.c */
int find_help(shell_data *data);

/* exec.cmd.c */
int colon_in_dir(char *path, int *index);
char *_which(char *cmd, char **env_v);
int is_executable(shell_data *data);
int cmd_error_check(char *dir, shell_data *data);
int exec_cmd(shell_data *data);

/* find_line.c */
int find_line(shell_data *data);

/* getline.c */
void assign_line(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif
