#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *pos;
int N;
int total = 0;

int seguro(int linha, int coluna) {
    for (int i = 0; i < linha; i++) {
        // mesma coluna
        if (pos[i] == coluna)
            return 0;

        // mesma diagonal
        if (abs(pos[i] - coluna) == abs(i - linha))
            return 0;
    }
    return 1;
}

void backtrack(int linha) {
    if (linha == N) {
        total++;
        printf("Solução %d:\n", total);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (pos[i] == j)
                    printf(" Q ");
                else
                    printf(" . ");
            }
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (int coluna = 0; coluna < N; coluna++) {
        if (seguro(linha, coluna)) {
            pos[linha] = coluna;
            backtrack(linha + 1);
        }
    }
}

int main() {
    printf("Digite N: ");
    scanf("%d", &N);

    pos = (int *)malloc(N * sizeof(int));
    if (!pos) {
        printf("Erro de memória\n");
        return 1;
    }

    backtrack(0);

    printf("Total de soluções: %d\n", total);
    free(pos);
    return 0;
}
