/*
Assignment name: picoshell Expected files: picoshell.c Allowed functions: close, fork, wait, exit, execvp, dup2, pipe
___________________________________________________________________
Write the following function:
int picoshell(char **cmds[]);

The goal of this function is to execute a pipeline.

It must execute each commands of cmds and connect the output of one to the input of the next command (just like a shell).
Cmds contains a null-terminated list of valid commands.
Each rows of cmds are an argv array directly usable for a call to execvp.
The first arguments of each command is the command name or path and can be passed directly as the first argument of execvp.
If any error occur, The function must return 1 (you must of course close all the open fds before).
Otherwise the function must wait all child processes and return 0.
You will find in this directory a file main.c which contain something to help you test your function.

Examples: ./picoshell /bin/ls "|" /usr/bin/grep picoshell
picoshell
./picoshell echo 'squalala' "|" cat "|" sed 's/a/b/g'
squblblb
___________________________________________________________________ 
Old summary by a student: You are given a main function.
It converts received arguments into cmds array of strings.
When there is a pipe the commands after the pipe are in the next array of strings.
You have to create a pipeline using the cmds you receive from the main, and execute them.
If there is any error the function should return 1. Close all FFS before returning.
If the cmds executed successfully wait all child processes and return 0.
*/

#include <unistd.h>
#include <sys/wait.h>

int picoshell(char **cmds[]){
    int i = 0;
    int prev_fd = -1; //checagem para ver se estou no filho
    int fd[2];
    pid_t pid;

    while (cmds[i])
    {
        if (cmds[i + 1] && pipe(fd) == -1) //primeira checagem de erro
            return (1); //erro
        pid = fork(); //criando processo filho e pegando o pID em pid
        if (pid < 0) //se pid for negativo, retorne erro
            return (1); // erro
        if (pid == 0) //se pid é 0, EXECUTE.
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, 0);
                close(prev_fd);
            }
            if (cmds[i + 1])
            {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]); //execução de comando
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
    while (wait(NULL) > 0);
    return (0);
}