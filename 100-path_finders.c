#include "main.h"

/**
 * find_path - entry point looks for command in the PATH string
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
 * _strlen - entry point returns the length of a string
 * @s: input
 *
 * Return: int
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * starts_with - entry point checks if needle starts with haystack
 * @haystack: input
 * @needle: input
 *
 * Return: char
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - entry point concatenates two strings
 * @d: destination
 * @s: source
 *
 * Return: char
 */

char *_strcat(char *d, char *s)
{
	char *ptr = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (ptr);
}

/**
 * dup_chars - entry point duplicates characters
 * @pathstr: input
 * @start: input
 * @end: input
 *
 * Return: char
 */

char *dup_chars(char *pathstr, int start, int end)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}
