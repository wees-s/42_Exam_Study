#include <unistd.h>     // pipe, fork, dup2, execvp, close
#include <stdlib.h>     // exit
#include <sys/wait.h>   // wait

/**
 * PICOSHELL - Executor de pipeline de comandos
 *
 * FLUXO GERAL:
 * cmd1 | cmd2 | cmd3
 *   ↓     ↓     ↓
 * [stdin] → pipe1 → pipe2 → [stdout]
 *
 * Cada comando:
 * - LÊ do prev_fd (pipe anterior)
 * - ESCREVE no fd[1] (pipe atual)
 */
int picoshell(char **cmds[])
{
	int fd[2];      // [0]=leitura, [1]=escrita (criado por pipe())
	int i = 0;          // Índice do comando atual
	int pid;        // PID do processo filho (0=filho, >0=pai)
	int prev_fd = -1;    // FD de leitura do pipe ANTERIOR (memória entre loops) Primeiro comando não tem pipe anterior

	/* Validação básica */
	if (!cmds || !cmds[0])
		return (1);

	// loop enquanto ainda tiver comandos no array
	while (cmds[i])
	{
		/* PIPE: Só cria se houver próximo comando
		   Por quê? O último comando escreve direto no terminal */
		if (cmds[i + 1])
		{
			if (pipe(fd) == -1)
			{
				if (prev_fd != -1)
					close(prev_fd);  // Limpa leak
				return (1);
			}
		}

		/* FORK: Cria processo filho para executar o comando */
		pid = fork();
		if (pid == -1)
		{
			/* Erro no fork: fecha tudo que foi aberto */
			if (prev_fd != -1)
				close(prev_fd);
			if (cmds[i + 1])
			{
				close(fd[0]);
				close(fd[1]);
			}
			return (1);
		}

		/* ═══════════════════════════════════════════════════
		   PROCESSO FILHO (executa o comando)
		   ═══════════════════════════════════════════════════ */
		if (pid == 0)
		{
			/* ENTRADA: Redireciona stdin se NÃO for o primeiro comando
			   Exemplo: em "ls | grep", o grep lê do pipe, não do teclado */
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);   // stdin (0) agora lê do pipe anterior
				close(prev_fd);     // Fecha FD original (já clonado)
			}

			/* SAÍDA: Redireciona stdout se NÃO for o último comando
			   Exemplo: em "ls | grep", o ls escreve no pipe, não na tela */
			if (cmds[i + 1])
			{
				close(fd[0]);       // Filho nunca lê do pipe ATUAL
				dup2(fd[1], 1);     // stdout (1) agora escreve no pipe
				close(fd[1]);       // Fecha FD original (já clonado)
			}

			/* Executa o comando (substitui o processo) */
			execvp(cmds[i][0], cmds[i]);
			exit(1);  // Só chega aqui se execvp falhar
		}

		/* ═══════════════════════════════════════════════════
		   PROCESSO PAI (gerencia os pipes)
		   ═══════════════════════════════════════════════════ */

		/* Fecha o pipe anterior (filho já herdou, pai não precisa mais) */
		if (prev_fd != -1)
			close(prev_fd);

		/* Prepara para o próximo comando */
		if (cmds[i + 1])
		{
			/* Fecha escrita: Pai nunca escreve no pipe
			   IMPORTANTE: Se não fechar, o próximo comando nunca recebe EOF! */
			close(fd[1]);

			/* Guarda leitura: Será passado para o próximo filho */
			prev_fd = fd[0];
		}

		i++;  // Avança para o próximo comando
	}

	/* Aguarda TODOS os filhos terminarem */
	while (wait(NULL) > 0)
		;

	return (0);
}
