#include "main.h"

/**
 * find_path - entry point looks for command in the PATH string
 * @data: is the data structure
 * @pathstr: is the PATH string
 * @cmd: is the command to look for
 *
 * Return: full path of cmd if found or NULL if not.
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
 * Return: length of string
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
 * Return: address of next char of haystack or NULL
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
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ptr);
}
