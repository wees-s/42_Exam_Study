#include <unistd.h>
#include <stdlib.h>

/**
 * FT_POPEN REFINADO
 * * LOGICA DOS INDICES:
 * Se type for 'r' (Read):
 * - Filho escreve (STDOUT_FILENO = 1). Logo, child_fd = 1.
 * - Pai lê (STDIN_FILENO = 0). Logo, parent_fd = 0.
 * Se type for 'w' (Write):
 * - Filho lê (STDIN_FILENO = 0). Logo, child_fd = 0.
 * - Pai escreve (STDOUT_FILENO = 1). Logo, parent_fd = 1.
 */

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2], pid;

    // 1. DETERMINAÇÃO DINÂMICA DE PAPÉIS
    // is_r será 1 (true) se for leitura, ou 0 (false) se for escrita.
    int is_r = (type == 'r');

    // Mapeamento: se is_r=1, child recebe 1. Se is_r=0, child recebe 0.
    int child_fd = is_r ? 1 : 0;

    // Mapeamento: se is_r=1, parent recebe 0. Se is_r=0, parent recebe 1.
    int parent_fd = is_r ? 0 : 1;

    // 2. VALIDAÇÃO DE ENTRADA
    if (!file || !argv || (type != 'r' && type != 'w'))
        return (-1);

    // 3. CRIAÇÃO DO PIPE
    // fd[0] = leitura, fd[1] = escrita
    if (pipe(fd) == -1)
        return (-1);

    // 4. CRIAÇÃO DO PROCESSO (FORK)
    pid = fork();
    if (pid == -1)
        return (close(fd[0]), close(fd[1]), -1); // Fecha ambos em caso de erro

    if (pid == 0) // --- PROCESSO FILHO ---
    {
        // O filho fecha o lado que o PAI vai usar (higiene de FDs)
        close(fd[parent_fd]);

        /* ** REDIRECIONAMENTO INTELIGENTE:
        ** Se is_r for 1: dup2(fd[1], 1) -> Saída do comando vai para o pipe.
        ** Se is_r for 0: dup2(fd[0], 0) -> Comando lê a entrada do pipe.
        */
        dup2(fd[child_fd], child_fd);

        // Após o dup2, o FD original não é mais necessário
        close(fd[child_fd]);

        // Executa o comando. Se funcionar, o código abaixo nunca será lido.
        execvp(file, argv);
        exit(1); // Se o execvp falhar, encerra o filho imediatamente
    }

    // --- PROCESSO PAI ---

    // O pai fecha o lado que o FILHO usou
    close(fd[child_fd]);

    // Retorna o FD que sobrou para o pai realizar a operação (ler ou escrever)
    return (fd[parent_fd]);
}
