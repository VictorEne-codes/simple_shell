#include "main.h"

/**
 * get_environ - entry point returns the string array copy of our environ
 * @data: input
 *
 * Return: char
 */

char **get_environ(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * _unsetenv - entry point removes an environment variable
 * @data: input
 * @var: input
 *
 * Return: int
 */

int _unsetenv(data_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = delete_node_at_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}

/**
 * _setenv - entry point initializes a new environment
 * @data: input
 * @var: input
 * @val: input
 *
 * Return: int
 */

int _setenv(data_t *data, char *var, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = data->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return (0);
}

/**
 * populate_env_list - entry point populates environment linked list
 * @data: input
 *
 * Return: int
 */

int populate_env_list(data_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	data->env = node;
	return (0);
}
