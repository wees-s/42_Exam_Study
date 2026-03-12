#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int picoshell(char **cmds[])
{
    int fd[2];
    int i;
    int prev_fd;
    pid_t pid;

    while(cmds[i])
    {
        if (cmds[i + 1])
        {
            pipe(fd);//preenchi o fd
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
            if (prev_fd != 0)
                close(prev_fd);
            exit(1);
        }
        if (pid == 0)//processo filho
        {
            if (prev_fd != -1)//checagem de primeira entrada
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds[i + 1])
            {
                dup2(fd[1], STDOUT_FILENO);
            }

            close(fd[0]);
            close(fd[1]);
            execvp(cmds[i][0], cmds[i]);
        }
        else
        {
            close(fd[1]);
            if (prev_fd != -1)
                close(prev_fd);
            prev_fd = fd[0];
            i++;
        }
    }
    return 0;
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