#include "main.h"

/**
 * replace_alias - replace alias in token string
 * @data: input
 *
 * Return: int
 */

int replace_alias(data_t *data)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * print_list_str - prints lists in stringa
 * @h: input
 *
 * Return: size_t
 */

size_t print_list_str(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * replace_string - function to replace strings
 * @old_str: input
 * @new_str: input
 *
 * Return: int
 */

int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

/**
 * _isalpha - checks for an alphabet
 * @c: input
 *
 * Return: int
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * replace_vars - replace var in token string
 * @data: input
 *
 * Return: int
 */

int replace_vars(data_t *data)
{
	int n = 0;
	list_t *node;

	for (n = 0; data->argv[n]; n++)
	{
		if (data->argv[n][0] != '$' || !data->argv[n][1])
			continue;

		if (!_strcmp(data->argv[n], "$?"))
		{
			replace_string(&(data->argv[n]),
				_strdup(convert_number(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[n], "$$"))
		{
			replace_string(&(data->argv[n]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(data->env, &data->argv[n][1], '=');
		if (node)
		{
			replace_string(&(data->argv[n]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[n], _strdup(""));

	}
	return (0);
}
