#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * struct liststrings - linked lists
 * @num: input
 * @str: input
 * @next: input
 */

typedef struct liststrings
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
 
/**
 * struct getsdata - arguments to pass into funtions
 * @arg: input
 * @argv: input
 * @path: input
 * @argc: input
 * @line_count: input
 * @err_num: input
 * @linecount_flag: input
 * @env: input
 * @cmd_buf: input
 * @alias: input
 * @fname: input
 * @history: input
 * @environ: input
 * @histcount: input
 * @status: input
 * @env_changed: input
 * @readfd: input
 * @cmd_buf_type: input
 */

typedef struct getsdata
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
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} data_t;

/**
 * struct builtin - contains a builtin string and related function
 * @type: input
 * @func: input
 */

typedef struct builtin
{
        char *type;
        int (*func)(data_t *);
} builtin_table;

int _getline(data_t *data, char **p, size_t *len);
void *_realloc(void *p, unsigned int o_size, unsigned int n_size);
char *_strncat(char *d, char *s, int n);
char *_strchr(char *str, char ch);
void sigintHandler(__attribute__((unused))int sig);
char *_strncpy(char *d, char *s, int n);
ssize_t read_buffer(data_t *data, char *buffer, size_t *i);
void free_data(data_t *data, int all);
void set_data(data_t *data, char **av);
int hsh(data_t *data, char **av);
char *_getenv(data_t *data, const char *name);
char *find_path(data_t *data, char *pathstr, char *cmd);
int is_delim(char c, char *delim);
void find_cmd(data_t *data);
int interactive(data_t *data);
void print_error(data_t *data, char *estr);
int is_cmd(data_t *data, char *path);
void fork_cmd(data_t *data);
int find_builtin(data_t *data);
int _myexit(data_t *data);
int _myenv(data_t *data);
int _myhistory(data_t *data);
int _mysetenv(data_t *data);
int _strcmp(char *str1, char *str2);
int _myhelp(data_t *data);
int _myunsetenv(data_t *data);
int _mycd(data_t *data);
void _puts(char *str);
char *_getenv(data_t *data, const char *n);
int _putchar(char c);
void print_error(data_t *data, char *estr);
void _eputs(char *s);
int print_d(int inp, int d);
int _eputchar(char c);
int _myalias(data_t *data);
char *find_path(data_t *data, char *pathstr, char *cmd);
int _strlen(char *s);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *dup_chars(char *pathstr, int start, int end);
int populate_env_list(data_t *data);
int _setenv(data_t *data, char *var, char *val);
int _unsetenv(data_t *data, char *var);
char **get_environ(data_t *data);
ssize_t get_input(data_t *data);
int is_chain(data_t *data, char *buffer, size_t *ptr);
char **strtow2(char *str, char p);
char **strtow(char *str, char *p);
void check_chain(data_t *data, char *buffer, size_t *ptr, size_t i, size_t length);
ssize_t input_buf(data_t *data, char **buffer, size_t *length);



#endif
