#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	pid;
	int	fd[2];
	int	child;
	int	parent;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	if (type == 'r')
	{
		child = 1;
		parent = 0;
	}
	else
	{
		child = 0;
		parent = 1;
	}
	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[parent]);
		dup2(fd[child], child);
		close(fd[child]);
		execvp(file, argv);
		exit(1);
	}
	close(fd[child]);
	return (fd[parent]);
}
