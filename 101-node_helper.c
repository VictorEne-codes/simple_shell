#include "main.h"

/**
 * ffree - frees a memory set
 * @ptr: input
 *
 * Return: void
 */

void ffree(char **ptr)
{
	char **a = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(a);
}

/**
 * add_node_end - adds a node at the end
 * @head: input
 * @s: input
 * @n: input
 *
 * Return: list_t
 */

list_t *add_node_end(list_t **head, const char *s, int n)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = n;
	if (s)
	{
		new_node->str = _strdup(s);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * _putsfd - writes char to fd
 * @s: input
 * @fd: input
 *
 * Return: int
 */

int _putsfd(char *s, int fd)
{
	int i = 0;

	if (!s)
	{
		return (0);
	}
	while (*s)
	{
		i += _putfd(*s++, fd);
	}
	return (i);
}

/**
 * node_starts_with - beginning of a node
 * @node: input
 * @p: input
 * @c: input
 *
 * Return: list_t
 */

list_t *node_starts_with(list_t *node, char *p, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, p);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _putfd - pus char in fd
 * @c: input
 * @fd: input
 *
 * Return: int
 */

int _putfd(char c, int fd)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}
