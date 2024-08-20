#include "main.h"


/**
* find_cmd - entry point finds a command in PATH
* @data: input
*
*Return: void
*/

void find_cmd(data_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
		if (!is_delim(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((interactive(data) || _getenv(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
* is_delim - entry point checks if a character is a delimeter
* @c: input
* @delim: input
*
* Return: int
*/

int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		return (1);
	}
	return (0);
}

/**
* find_path - entry point finds the given command in the PATH string
* @data: input
* @pathstr: input
* @cmd: input
*
* Return: char
*/

char *find_path(data_t *data, char *pathstr, char *cmd)
{
	int i = 0, cur_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, cur_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(data, path))
				return (path);
			if (!pathstr[i])
				break;
			cur_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
* _getenv - entry point gets the value of an environ variable
* @data: input
* @name: input
*
* Return: char
*/

char *_getenv(data_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
