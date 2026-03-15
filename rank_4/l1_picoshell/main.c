#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int picoshell(char **cmds[]);

int main(int argc, char **argv)
{
    char ***cmds;
    int cmd_count = 0;
    int arg_count = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s command [args] [| command [args]]...\n", argv[0]);
        return (1);
    }

    // Conta quantos comandos (separados por |)
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "|") == 0)
            cmd_count++;
    }
    cmd_count++; // +1 para o último comando

    // Aloca array de comandos
    cmds = malloc(sizeof(char **) * (cmd_count + 1));
    if (!cmds)
        return (1);
    cmds[cmd_count] = NULL;

    // Preenche cada comando
    i = 1;
    for (j = 0; j < cmd_count; j++)
    {
        // Conta argumentos deste comando
        arg_count = 0;
        k = i;
        while (k < argc && strcmp(argv[k], "|") != 0)
        {
            arg_count++;
            k++;
        }

        // Aloca array de argumentos
        cmds[j] = malloc(sizeof(char *) * (arg_count + 1));
        if (!cmds[j])
        {
            // Libera tudo em caso de erro
            for (int x = 0; x < j; x++)
                free(cmds[x]);
            free(cmds);
            return (1);
        }

        // Copia argumentos
        for (k = 0; k < arg_count; k++)
        {
            cmds[j][k] = argv[i];
            i++;
        }
        cmds[j][arg_count] = NULL;
        i++; // Pula o "|"
    }

    // Executa picoshell
    int ret = picoshell(cmds);

    // Libera memória
    for (j = 0; j < cmd_count; j++)
        free(cmds[j]);
    free(cmds);

    return (ret);
}
