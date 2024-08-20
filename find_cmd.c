#include "shell.h"

/**
*find_cmd - entry point finds a command in PATH
*@data: is the parameter & return data struct
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
*fork_cmd - entry point forks an exec thread to run cmd
*@data: is the parameter & return data struct
*
*Return: void
*/
void fork_cmd(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
