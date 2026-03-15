#include <unistd.h>
#include <stdio.h>

int ft_popen(const char *file, char *const argv[], char type);

int main()
{
    char buffer[1000];
    int n, fd;

    // TESTE 1
    printf("TESTE 1: Executar 'ls' e capturar resultado\n");
    fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
    n = read(fd, buffer, 999);
    buffer[n] = '\0';
    printf("Resultado:\n%s\n", buffer);
    close(fd);

    // TESTE 2
    printf("\nTESTE 2: Executar 'echo OLA' e capturar resultado\n");
    fd = ft_popen("echo", (char *const[]){"echo", "OLA", NULL}, 'r');
    n = read(fd, buffer, 999);
    buffer[n] = '\0';
    printf("Resultado:\n%s\n", buffer);
    close(fd);

    // TESTE 3
    printf("\nTESTE 3: Escrever para 'cat'\n");
    fd = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
    write(fd, "TESTE ESCRITA\n", 14);
    close(fd);
    sleep(1);

    printf("\n=== SE VIU OS 3 OUTPUTS, FUNCIONOU! ===\n");
    return 0;
}
