#include "main.h"

/**
*list_len - entry point determines the length of a linked list
*@h: pointer to the first n
*
*Return: size of the list(i).
*/
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
*bfree - entry point frees a pointer and NULLs its address
*@p: address of the pointer to free
*
*Return: 1 if freed, or 0 if not.
*/
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

/**
*list_to_strings - entry point returns an array of strings of the list->str
*@h: pointer to the first n
*
*Return: array of strings(s).
*/
char **list_to_strings(list_t *h)
{
	list_t *n = h;
	size_t i = list_len(h), j;
	char **s;
	char *str;

	if (!h || !i)
		return (NULL);
	s = malloc(sizeof(char *) * (i + 1));
	if (!s)
		return (NULL);
	for (i = 0; n; n = n->next, i++)
	{
		str = malloc(_strlen(n->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(s[j]);
			free(s);
			return (NULL);
		}

		str = _strcpy(str, n->str);
		s[i] = str;
	}
	s[i] = NULL;
	return (s);
}

/**
*free_list - entry point frees all ns of a list
*@hp: is the address of the pointer to head n
*
*Return: void
*/
void free_list(list_t **hp)
{
	list_t *n, *next_n, *h;

	if (!hp || !*hp)
		return;
	h = *hp;
	n = h;
	while (n)
	{
		next_n = n->next;
		free(n->str);
		free(n);
		n = next_n;
	}
	*hp = NULL;
}

/**
*print_list - entry ppoint prints all elements of a list_t linked list
*@h: pointer to the first n
*
*Return: size of the list(i).
*/
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
