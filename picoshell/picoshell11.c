#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i = 0;
	int fd[2];
	pid_t pid;
	int infile = -1;

	if (!cmds || !cmds[0][0])
		exit(1);
	while (cmds[i])
	{
		if (cmds[i + 1])
			pipe(fd);
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		pid = fork();
		if (pid < 0)
		{
			if (fd[0] != -1)
				close(fd[0]);
			if (fd[1] != -1)
				close(fd[1]);
			if (infile != -1)
				close(infile);
			exit(1);
		}
		if (pid == 0)
		{
			if (cmds[i + 1])
				dup2(fd[1], STDOUT_FILENO);
			if (infile != -1)
			{
				dup2(infile, STDIN_FILENO);
				close(infile);
			}
			if (fd[0] != -1)
				close(fd[0]);
			if (fd[1] != -1)
				close(fd[1]);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			close(fd[1]);
			if (infile != -1)
				close(infile);
			infile = fd[0];
			i++;
		}
	}
	return (0);
}

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int cmds_size = 1;

	for (int i=1; i < argc; i++)
		if (!strcmp(argv[i], "|"))
			cmds_size++;

	char ***cmds = calloc(cmds_size + 1, sizeof(char **));
	if (!cmds)
	{
		dprintf(2, "Malloc error: %m\n");
		return 1;
	}

	cmds[0] = argv + 1;
	int cmds_i = 1;
	for (int i=1; i < argc; i++)
		if (!strcmp(argv[i], "|"))
		{
			cmds[cmds_i] = argv + i + 1;
			argv[i] = NULL;
			cmds_i++;
		}

	int ret = picoshell(cmds);
	if (ret)
		perror("picoshell");
	free(cmds);
	return (ret);
}