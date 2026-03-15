#include <unistd.h>
#include <stdlib.h>

/**
 * FT_POPEN SEM TERNÁRIOS
 * LOGICA DOS INDICES:
 * Se type for 'r' (Read):
 * - Filho escreve (STDOUT_FILENO = 1). Logo, child_fd = 1.
 * - Pai lê (STDIN_FILENO = 0). Logo, parent_fd = 0.
 * Se type for 'w' (Write):
 * - Filho lê (STDIN_FILENO = 0). Logo, child_fd = 0.
 * - Pai escreve (STDOUT_FILENO = 1). Logo, parent_fd = 1.
 */

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    int pid;
    int child_fd;
    int parent_fd;

    // 1. VALIDAÇÃO DE ENTRADA
    if (!file || !argv || (type != 'r' && type != 'w'))
        return (-1);

    // 2. DETERMINAÇÃO DOS ÍNDICES
    if (type == 'r')
    {
        child_fd = 1;   // Filho escreve (STDOUT)
        parent_fd = 0;  // Pai lê
    }
    else  // type == 'w'
    {
        child_fd = 0;   // Filho lê (STDIN)
        parent_fd = 1;  // Pai escreve
    }

    // 3. CRIAÇÃO DO PIPE
    // fd[0] = leitura, fd[1] = escrita
    if (pipe(fd) == -1)
        return (-1);

    // 4. CRIAÇÃO DO PROCESSO (FORK)
    pid = fork();
    if (pid == -1)
        return (close(fd[0]), close(fd[1]), -1);

    if (pid == 0) // --- PROCESSO FILHO ---
    {
        // O filho fecha o lado que o PAI vai usar
        close(fd[parent_fd]);

        // REDIRECIONAMENTO INTELIGENTE:
        // Se type='r': dup2(fd[1], 1) -> Saída do comando vai para o pipe
        // Se type='w': dup2(fd[0], 0) -> Comando lê a entrada do pipe
        dup2(fd[child_fd], child_fd);

        // Após o dup2, o FD original não é mais necessário
        close(fd[child_fd]);

        // Executa o comando
        execvp(file, argv);
        exit(1);
    }

    // --- PROCESSO PAI ---

    // O pai fecha o lado que o FILHO usou
    close(fd[child_fd]);

    // Retorna o FD que sobrou para o pai realizar a operação
    return (fd[parent_fd]);
}
