#include "main.h"

/**
 * _strncpy - copies strings
 * @d: destination
 * @s: source
 * @n: input
 *
 * Return: char
 */

char *_strncpy(char *d, char *s, int n)
{
	int i, j;
	char *p = d;

	i = 0;
	while (s[i] != '\0' && i < n - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (p);
}

/**
 * _strchr - strings locator
 * @str: input
 * @ch: input
 *
 * Return: char
 */

char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * sigintHandler - funtion to prevent cntl + C
 * @sig: signale number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * input_buf - function to buffer chained command
 * @data: input
 * @buffer: input
 * @length: input
 *
 * Return: ssize_t
 */

ssize_t input_buf(data_t *data, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline(data, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			data->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(data, *buffer, data->histcount++);
			{
				*length = r;
				data->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * check_chain - checks the buffer chain
 * @data: input
 * @buffer: input
 * @ptr: input
 * @i: input
 * @length: input
 *
 * Return: void
 */

void check_chain(data_t *data, char
		*buffer, size_t *ptr, size_t i, size_t length)
{
	size_t j = *ptr;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}

	*ptr = j;
}

