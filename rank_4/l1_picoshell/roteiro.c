#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int picoshell(char **cmds[])
{
    // 1. DECLARAÇÃO (O que eu preciso para o ritual?)
    // [Seu código aqui: fd, prev_fd, i, pid]

    // 2. PROTEÇÃO INICIAL
    // [Seu código aqui: if (!cmds...)]

    while (cmds[i])
    {
        // 3. CRIAR O FUTURO (Se tem próximo...)
        // [Seu código aqui: pipe(fd)]

        // 4. DIVIDIR O MUNDO
        // [Seu código aqui: pid = fork()]

        // --- BLOCO DO FILHO ---
        if (pid == 0)
        {
            // 5. OLHAR PARA O PASSADO (Se alguém soprou antes...)
            // [Seu código aqui: dup2(prev_fd, 0) e close]

            // 6. OLHAR PARA O FUTURO (Se alguém vai ouvir depois...)
            // [Seu código aqui: close(fd[0]), dup2(fd[1], 1), close(fd[1])]

            // 7. EXECUTAR
            // [Seu código aqui: execvp e exit]
        }

        // --- BLOCO DO PAI ---

        // 8. LIMPAR O PASSADO (Já entreguei a chave para o filho...)
        // [Seu código aqui: close(prev_fd)]

        // 9. PREPARAR A PRÓXIMA RODADA
        // [Seu código aqui: close(fd[1]) e prev_fd = fd[0] OU -1]

        i++;
    }

    // 10. ENCERRAMENTO (Limpeza final e Maestro espera a banda)
    // [Seu código aqui: close final e loop do wait]

    return (0);
}

/*
	Desafio Final de Memorização:
	Se você conseguir responder essas 3 perguntas, o roteiro está gravado:

	Por que o Filho fecha o fd[0] antes de dar o dup2(fd[1], 1)? (Resposta: Porque o filho atual só quer SOPRAR para o futuro, ele não vai sugar do próprio pipe que acabou de criar).

	Por que o Pai fecha o fd[1] logo após o fork? (Resposta: Para que o próximo comando receba o sinal de Fim de Arquivo (EOF) quando o comando atual terminar de escrever).

	Qual o valor de prev_fd no primeiríssimo comando? (Resposta: -1, porque não existe passado antes do primeiro).
*/
