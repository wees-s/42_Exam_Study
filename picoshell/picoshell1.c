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
    int in_file;
    int prev_fd = -1;
    while (cmds[i])
    {
        //pipe
        //fork
        //dup2
        //execvp
        if (cmds[i + 1]) //se houver comando ainda para rodar
        {
            pipe(fd); //faça o pipe
        }
        else //caso não tenha um proximo comando para rodar, fd[0] e fd[1] passam a ser negativos (flagzinha)
        {
            fd[0] = -1;
            fd[1] = -1;
        }
        pid = fork();
        if (pid == 0)//to no filho
        {
            if (prev_fd != -1)//se não é a primeira vez dentro do pipe
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds[i + 1])//se estou no filho e ainda tiver um comando vindo pela frente
            {
                dup2(fd[1], STDOUT_FILENO);//A SAÍDA DE ESCRITA PASSA A SER A ENTRADA
                //trocar a saída 
            }
            close(fd[0]);
            close(fd[1]);
            execvp(cmds[i][0], cmds[i]);
            exit(1);
            // a execução precisa accontecer aqui especificamente
        }
        else if (pid == -1) //erro
        {
            if (fd[0] != -1)
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);
            if (prev_fd != 0)
                close(prev_fd);
            exit(1);
        }
        else //to no pai
        {
            close(fd[1]);
            if (prev_fd != -1)
            {
                close(prev_fd);
            }
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