#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[]){
    int i = 0;
    int fd[2];
    int in_fd = 0;
    pid_t pid;
    int status;
    int retorno;

    while(cmds[i])
    {
        //criando PIPE caso ainda PRECISE
        if (cmds[i + 1]) //se ainda tiver comando a ser executado vamos criar o pipe
        {
            if (pipe(fd) == -1) //criou o pipe, se pipe retornar -1, retorna 1 (erro)
                return (1);
        }
        else //se não tiver mais comandos, vamos colocar uma flag no último fd
        {
            fd[0] = -1;
            fd[1] = -1;
        }
        //criando um processo filho para execução do comando
        //lembrando que o execvp encerra o processo após a execução de algum comando
        pid = fork(); //armazenei o pID do processo dentro de PID e executei o fork
        if (pid < 0) //se PID for negativo, é um erro
        {
            if (fd[0] != -1) //se não for o último comando, vamos fazer a limpeza do fd
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);
            if (in_fd != 0)
                close(in_fd);
            return (1);
        }
        if (pid == 0)//fork ocorreu normalmente - estamos no processo filho
        {
            if (in_fd != 0)//ainda não sei o motivo
            {
                if (dup2(in_fd, 0) == -1)
                    exit(1);
                close(in_fd);
            }
            if (fd[1] != -1)
            {
                if (dup2(fd[1], 1) == -1)
                    exit(1);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        else//estamos no processo pai
        {
            if (in_fd != 0)
                close(in_fd);
            if (fd[1] != -1)
                close(fd[1]);
            in_fd = fd[0];
            i++;
        }
    }

    while (wait(&status) > 0)
    {
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            retorno = 1;
        else if (!WIFEXITED(status))
            retorno = 1;
    }

    return retorno;
}