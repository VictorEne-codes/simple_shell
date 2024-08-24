#include "main.h"

/**
* get_history_file - entry point gets the history file
* @data: input
*
* Return: char
*/

char *get_history_file(data_t *data)
{
	char *buf, *dir;

	dir = _getenv(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
* write_history - entry point creates a file, or appends to an existing file
* @data: input
*
* Return: int
*/

int write_history(data_t *data)
{
	ssize_t fd;
	char *filename = get_history_file(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}


/**
* build_history_list - entry point adds entry to a history linked list
* @data: input
* @buf: buffer
* @linecount: is the history count
*
* Return: Always 0
*/

int build_history_list(data_t *data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->history)
	{
		node = data->history;
	}
	add_node_end(&node, buf, linecount);

	if (!data->history)
	{
		data->history = node;
	}
	return (0);
}

/**
* _strcpy - entry point copies a string from a source to a destination
* @dest: input
* @src: input
*
* Return: char
*/

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
