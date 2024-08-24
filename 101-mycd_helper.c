#include "main.h"

/**
 * print_error - outputs an error message
 * @data: input
 * @estr: input
 *
 * Return: void
 */

void print_error(data_t *data, char *estr)
{
	_eputs(data->fname);
	_eputs(": ");
	print_d(data->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(data->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * _eputs - prints out a string
 * @s: input
 *
 * Return: void
 */

void _eputs(char *s)
{
	int i = 0;

	if (!s)
	{
		return;
	}
	while (s[i] != '\0')
	{
		_eputchar(s[i]);
		i++;
	}
}

/**
 * print_d - prints out a decimal
 * @inp: input
 * @d: input
 *
 * Return: int
 */

int print_d(int inp, int d)
{
	int (*__putchar)(char) = _putchar;
	int i, counter = 0;
	unsigned int _abs_, cur;

	if (d == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = inp;
	cur = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + cur / i);
			counter++;
		}
		cur %= i;
	}
	__putchar('0' + cur);
	counter++;

	return (counter);
}

/**
 * _eputchar - prints a character
 * @c: input
 *
 * Return: int
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}
