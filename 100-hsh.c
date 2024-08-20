#include "shell.h"

/**
*hsh - entry point is the main shell loop
*@data: is the parameter & return data struct
*@av: is the argument vector from main function
*
*Return: 0 if  success, or 1 on error, or return error code
*/
int hsh(data_t *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_data(data);
		if (interactive(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(data);
		if (r != -1)
		{
			set_data(data, av);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
*clear_data - initializes data_t struct
*@data: struct address
*/
void clear_data(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
*set_data - initializes data_t struct
*@data: struct address
*@av: argument vector from main
*/
void set_data(data_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = strtow(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		replace_alias(data);
		replace_vars(data);
	}
}

/**
*free_data - frees data_t struct fields
*@data: struct address
*@all: returns true if all fields are freed
*/
void free_data(data_t *data, int all)
{
	ffree(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		ffree(data->environ);
			data->environ = NULL;
		bfree((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}
