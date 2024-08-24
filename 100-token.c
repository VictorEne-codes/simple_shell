#include "main.h"

/**
 * strtow - splits strings into words
 * @str: input
 * @p: input
 *
 * Return: char
 */

char **strtow(char *str, char *p)
{
	int i, j, k, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!p)
		p = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], p) && (is_delim(str[i + 1], p) || !str[i + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (is_delim(str[i], p))
			i++;
		k = 0;
		while (!is_delim(str[i + k], p) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * strtow2 - splits strings into words
 * @str: input
 * @p: input
 *
 * Return: vhar
 */

char **strtow2(char *str, char p)
{
	int i, j, k, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != p && str[i + 1] == p) ||
		    (str[i] != p && !str[i + 1]) || str[i + 1] == p)
			nw++;
	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (str[i] == p && str[i] != p)
			i++;
		k = 0;
		while (str[i + k] != p && str[i + k] && str[i + k] != p)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * is_chain - checks for a chain delimeter
 * @data: input
 * @buffer: input
 * @ptr: input
 *
 * Return: int
 */

int is_chain(data_t *data, char *buffer, size_t *ptr)
{
	size_t j = *ptr;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * get_input - gets line without newline
 * @data: input
 *
 * Return: ssize_t
 */

ssize_t get_input(data_t *data)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t r = 0;
	char **buf_p = &(data->arg), *ptr;

	_putchar(BUF_FLUSH);
	r = input_buf(data, &buffer, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		ptr = buffer + i;

		check_chain(data, buffer, &j, i, length);
		while (j < length)
		{
			if (is_chain(data, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			data->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr;
		return (_strlen(ptr));
	}

	*buf_p = buffer;
	return (r);
}

