#include "main.h"

/**
 * _mycd - changes current directory of an process
 * @data: input
 *
 * Return: int
 */

int _mycd(data_t *data)
{
	char *p, *d, buf[1024];
	int chdir_ret;

	p = getcwd(buffer, 1024);
	if (!p)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		d = _getenv(data, "HOME=");
		if (!d)
			chdir_ret =
				chdir((d = _getenv(data, "PWD=")) ? d : "/");
		else
			chdir_ret = chdir(d);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(p);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((d = _getenv(data, "OLDPWD=")) ? d : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _puts - prints out a string
 * @str: input
 *
 * Return: void
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _getenv - returns the value on an environment
 * @data: input
 * @n: input
 *
 * Return: char
 */

char *_getenv(data_t *data, const char *n)
{
	list_t *node = data->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, n);
		if (ptr && *ptr)
		{
			return (ptr);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _putchar - prints out a character
 * @c: input
 *
 * Return: int
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
