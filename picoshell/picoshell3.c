#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
    int fd[2];
    int i = 0;
    pid_t pid;
    int in_fd = -1;

    while (cmds[i])
    {
        //pipe
        //fork
        //dup2
        //execvp
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
            if (fd[0] != -1)
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);
            if (in_fd != -1)
                close(in_fd);
            exit(1);
        }
        if (pid == 0)//filho, execucao aqui
        {
            if (cmds[i + 1])
            {
                dup2(fd[1], STDOUT_FILENO);
            }
            if (in_fd != -1)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            close(fd[0]);
            close(fd[1]);
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        else//processo pai, somente fechamento
        {
            close(fd[1]);
            if (in_fd != -1)
                close(in_fd);
            in_fd = fd[0];
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