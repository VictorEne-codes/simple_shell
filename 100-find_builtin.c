#include "main.h"

/**
 * find_builtin - searches for builtin commands
 * @data: input
 *
 * Return: int
 */

int find_builtin(data_t *data)
{
	int i, built_in_return = -1;
	builtin_table builtint[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtint[i].type; i++)
		if (_strcmp(data->argv[0], builtint[i].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtint[i].func(data);
			break;
		}
	return (built_in_return);
}

/**
 * _myexit - command to exit the shell
 * @data: input
 *
 * Return: int
 */

int _myexit(data_t *data)
{
	int exitch;

	if (data->argv[1])
	{
		exitch = _erratoi(data->argv[1]);
		if (exitch == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->err_num = _erratoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * _myenv - displays the current environment
 * @data: input
 *
 * Return: int
 */

int _myenv(data_t *data)
{
	print_list_str(data->env);
	return (0);
}

/**
 * _myhistory - shows history list
 * @data: input
 *
 * Return: int
 */

int _myhistory(data_t *data)
{
	print_list(data->history);
	return (0);
}

