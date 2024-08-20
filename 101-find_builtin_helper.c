#include "main.h"

/**
 * _mysetenv - sets a new environment
 * @data: input
 *
 * Return: int
 */

int _mysetenv(data_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _strcmp - compares two strings
 * @str1: input
 * @str2: input
 *
 * Return: int
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
	{
		return (0);
	}
	else
	{
		return (*str1 < *str2 ? -1 : 1);
	}
}

/**
 * _myhelp - changes current directory of any given provess
 * @data: input
 *
 * Return: int
 */

int _myhelp(data_t *data)
{
	char **arg;

	arg = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
	{
		_puts(*arg);
	}
	return (0);
}

/**
 * _myunsetenv - deletes an environment
 * @data: input
 *
 * Return: int
 */

int _myunsetenv(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
	{
		_unsetenv(data, data->argv[i]);
	}
	return (0);
}
