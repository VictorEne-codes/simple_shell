#include "main.h"

/**
 * add_node - add nodes to linked list
 * @head: input
 * @s: input
 * @n: input
 *
 * Return: list_t
 */

list_t *add_node(list_t **head, const char *s, int n)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = n;
	if (s)
	{
		new_h->str = _strdup(s);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * get_node_index - gets nodes at index
 * @head: inpur
 * @n: input
 *
 * Return: size_t
 */

size_t get_node_index(list_t *head, list_t *n)
{
	size_t i = 0;

	while (head)
	{
		if (head == n)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * delete_node_at_index - delets a node at index
 * @head: input
 * @ind: input
 *
 * Return: int
 */

int delete_node_at_index(list_t **head, unsigned int ind)
{
	list_t *n, *prev_n;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		n = *head;
		*head = (*head)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *head;
	while (n)
	{
		if (i == ind)
		{
			prev_n->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		i++;
		prev_n = n;
		n = n->next;
	}
	return (0);
}

/**
 * _strdup - duplicates strings
 * @s: input
 *
 * Return: char
 */

char *_strdup(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
	{
		return (NULL);
	}
	while (*s++)
	{
		len++;
	}
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
	{
		ret[len] = *--s;
	}
	return (ret);
}

/**
 * _memset - sets a memory
 * @s: input
 * @b: input
 * @n: input
 *
 * Return: char
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}
