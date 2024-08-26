#include "main.h"

/**
 * renumber_history - renumbers a linked list
 * @data: input
 *
 * Return: int
 */

int renumber_history(data_t *data)
{
	list_t *n = data->history;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (data->histcount = i);
}

/**
 * read_history -function to  read historys from file
 * @data: input
 *
 * Return: int
 */

int read_history(data_t *data)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(data, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(data, buffer + last, linecount++);
	free(buffer);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		delete_node_at_index(&(data->history), 0);
	renumber_history(data);
	return (data->histcount);
}
