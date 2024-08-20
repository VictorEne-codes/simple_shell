#include "main.h"

/**
 * _strncpy - copies strings
 * @d: destination
 * @s: source
 * @n: input
 *
 * Return: char
 */

char *_strncpy(char *d, char *s, int n)
{
	int i, j;
	char *p = d;

	i = 0;
	while (s[i] != '\0' && i < n - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (p);
}

/**
 * _strchr - strings locator
 * @str: input
 * @ch: input
 *
 * Return: char
 */

char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * sigintHandler - funtion to prevent cntl + C
 * @sig: signale number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
