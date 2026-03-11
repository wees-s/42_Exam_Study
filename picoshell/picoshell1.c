#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int picoshell(char **cmds[])
{
    int ret;
    int fd[2];
    int i = 0;
    pid_t pid;
    /*
    char **cmds[] = {
        cmds[0] = char *cmd1[] = {"wc", "-l", NULL};,
        cmds[1] = char *cmd2[] = {"wc", "-l", NULL};,
        cmds[2] = NULL
        };*/
    while (cmds[i])//array de array de strings
    {
        /*if (cmds[i + 1])
        {
            
        }*/
        pid = fork();
        if (pid == 0)
        {
            execvp(cmds[i][0], cmds[i]);
        }
        i++;
    }
    ret = 0;
    return (ret);
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