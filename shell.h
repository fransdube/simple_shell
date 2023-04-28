#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* _numsfuncs.c */
int _erratoi(char *);
char *convert_number(long int, int, int);

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string  from getline containing arguments
 *@argv: an array of strings from arg
 *@path: a string path for the current list command
 *@argc:  argument count
 *@line_count: the error line count
 *@err_num: the error code for exit(s
 *@linecount_flag: if on count this line of input
 *@fname: the filename
 *@env: copy of environment
 *@environ: custom modified copy of environ from LL env
 *@history: hist node
 *@alias: alias node
 *@env_changed: on environmentchanged
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* Reading,writing and flushiNg buffers */
#define READNG_BUFFER_SIZE 1024
#define WRITNG_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* shell.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* duplicate_chars.c */
char *duplicate_chars(char *, int, int);
char *starts_with(const char *, const char *);

/* parser_funcs.c */
int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);

/* for command chaining */
#define COMMAND_NORM	0
#define COMMAND_OR		1
#define COMMAND_AND		2
#define COMMAND_CHAIN	3

/* err.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*stringfunc.c */
int _strlength(char *);
int _strcompare(char *, char *);
char *_strconcat(char *, char *);

/* stringfuncs.c */
char *_strcopy(char *, char *);
char *_strduplicate(const char *);
void _puts(char *);
int _putchar(char);

/* stringfunctions.c */
char *_stringcopy(char *, char *, int);
char *_stringconcat(char *, char *, int);
char *_strcharacter(char *, char);

/* tokens.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* _realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* free_mem.c */
int mfree(void **);

/* _atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errs.c */
void print_error(info_t *, char *);
int print_d(int, int);
void remove_comments(char *);

/* for convert_Int */
#define CONVERT_TO_LOWERCASE	1
#define CONVERT_TO_UNSIGNED	2

/* my_commands.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* alias.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*environment.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* _getenvironment.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/*hist.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

#define HISTORY_FILE	".simple_shell_history"
#define HISTORY_MAX	4096

/*list.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/*variables.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
