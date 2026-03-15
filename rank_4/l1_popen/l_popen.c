#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    int pid;
    int child_fd;
    int parent_fd;

    if (!file || !argv || (type != 'r' && type != 'w'))
        return (-1);
    if (type == 'r')
    {
        child_fd = 1;
        parent_fd = 0;
    }
    else
    {
        child_fd = 0;
        parent_fd = 1;
    }
    if (pipe(fd) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (close(fd[0]), close(fd[1]), -1);
    if (pid == 0)
    {
        close(fd[parent_fd]);
        dup2(fd[child_fd], child_fd);
        close(fd[child_fd]);
        execvp(file, argv);
        exit(1);
    }
    close(fd[child_fd]);
    return (fd[parent_fd]);
}
