#include <unistd.h>    // fork, alarm, close
#include <sys/wait.h>  // waitpid e macros W...
#include <signal.h>    // SIGALRM, strsignal
#include <stdio.h>     // printf
#include <stdlib.h>    // exit
#include <stdbool.h>   // bool
#include <string.h>    // strsignal (em alguns ambientes Unix)

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid;
	int		status;
	int		code;
	int		sig;

	pid = fork();
	if (pid == -1) // Falha na criação do processo
		return (-1);

	/* --- PROCESSO FILHO --- */
	if (pid == 0)
	{
		// Configura o timer. Se estourar, o Kernel envia SIGALRM e mata o filho.
		alarm(timeout);
		f();    // Executa a função a ser testada
		exit(0); // Se f() terminar sem crash/exit, retorna sucesso (0)
	}

	/* --- PROCESSO PAI --- */
	// Espera o filho terminar e captura o relatório de status
	if (waitpid(pid, &status, 0) == -1)
		return (-1);

	// CASO 1: O filho terminou via exit() ou return
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		if (code == 0) // Único caso de função "Nice"
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		// Se code != 0, é considerada "Bad"
		if (verbose)
			printf("Bad function: exited with code %d\n", code);
		return (0);
	}

	//

	// CASO 2: O filho foi interrompido por um Sinal (Crash ou Timeout)
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status); // Extrai qual sinal matou o filho
		if (verbose)
		{
			// Agrupamos o verbose para decidir O QUE dizer de forma limpa
			if (sig == SIGALRM)
				printf("Bad function: timed out after %u seconds\n", timeout);
			else
				// strsignal converte o sinal (ex: 11) em texto (ex: "Segmentation fault")
				printf("Bad function: %s\n", strsignal(sig));
		}
		return (0);
	}

	// Caso de segurança (se não entrar em EXITED nem em SIGNALED)
	return (-1);
}
