#include "main.h"

/**
 * _strncat - concatenates strings
 * @d: destination
 * @s: source
 * @n: input
 *
 * Return: char
 */

char *_strncat(char *d, char *s, int n)
{
	int i, j;
	char *p = dest;

	i = 0;
	j = 0;
	while (d[i] != '\0')
	{
		i++;
	}
	while (s[j] != '\0' && j < n)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < n)
	{
		d[i] = '\0';
	}
	return (p);
}

/**
 * _realloc - reallocates memory
 * @p: input
 * @o_size: input
 * @n_size: input
 *
 * Return: void
 */

void *_realloc(void *p, unsigned int o_size, unsigned int n_size)
{
	char *ptr;

	if (!p)
		return (malloc(n_size));
	if (!n_size)
		return (free(p), NULL);
	if (n_size == o_size)
		return (p);

	ptr = malloc(n_size);
	if (!ptr)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		ptr[o_size] = ((char *)p)[o_size];
	free(p);
	return (ptr);
}

/**
 * _getline - gets input from STDIN
 * @data: input
 * @p: input
 * @len: input
 *
 * Return: int
 */

int _getline(data_t *data, char **p, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, l;
	size_t k;
	ssize_t r = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *ch;

	ptr = *p;
	if (ptr && len)
		s = *len;
	if (i == l)
		i = l = 0;

	r = read_buf(info, buf, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);

	ch = _strchr(buf + i, '\n');
	k = ch ? 1 + (unsigned int)(ch - buf) : l;
	new_ptr = _realloc(ptr, s, s ? s + k : k + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		_strncat(new_ptr, buf + i, k - i);
	else
		_strncpy(new_ptr, buf + i, k - i + 1);

	s += k - i;
	i = k;
	ptr = new_ptr;

	if (len)
		*len = s;
	*p = ptr;
	return (s);
}
