#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
	int fd[2];
	int prev_fd = -1;
	int i = 0;
	int pid;

	if (!cmds || !cmds[0])
		return (1);
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(fd) == -1)
			{
				if (prev_fd != -1)
					close(prev_fd);
				return (1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds[i + 1])
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
