#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
    int i = 0;
    int fd[2];
    pid_t pid;
    int infile = -1;

    while (cmds[i])
    {
        if (cmds[i + 1])
        {
            pipe(fd);
        }
        else
        {
            fd[0] = -1;
            fd[1] = -1;
        }
        pid = fork();
        if (pid < 0)
        {
            if (infile != -1)
                close(infile);
            if (fd[0] != -1)
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);
            exit(1);
        }
        if (pid == 0)
        {
            if (cmds[i + 1])
            {
                dup2(fd[1], STDOUT_FILENO);
            }
            if (infile != -1)
            {
                dup2(infile, STDIN_FILENO);
                close(infile);
            }
            close(fd[0]);
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
}

#include <stdio.h>

int main(void)
{
    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"grep", ".c", NULL};
    char *cmd3[] = {"wc", "-l", NULL};

    char **cmds[] = {
        cmd1,
        cmd2,
        cmd3,
        NULL
    };

    int ret = picoshell(cmds);
    printf("Return value: %d\n", ret);
    return ret;
}