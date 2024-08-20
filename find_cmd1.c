#include "shell.h"

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

/**
*is_cmd - entry point determines if a file is an executable command
*@data: is the data struct
*@path: path to the file
*
*Return: 1 if true, or 0 if otherwise
*/
int is_cmd(data_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
	{		
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
