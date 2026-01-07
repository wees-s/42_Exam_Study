// Assignement name : n_queens

// Expected files : *.c *.h

// Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr

// -------------------------------------------------------------------------

// Write a program that will print all the solutions to the n queens problem
// for a n given as argument.
// We will not test with negative values.
// The order of the solutions is not important.

// You will display the solutions under the following format :
// <p1> <p2> <p3> ... \n
// where pn are the line index of the queen in each colum starting from 0.

// For example this should work :
// $> ./n_queens 2 | cat -e

// $> ./n_queens 4 | cat -e
// 1 3 0 2$
// 2 0 3 1$

// $> ./n_queens 7 | cat -e
// 0 2 4 6 1 3 5$
// 0 3 6 2 5 1 4$
// etc...

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int seguro(int linha, int coluna, int *pos)
{
    int i;

    i = 0;
    while (i < linha)
    {
        if (pos[i] == coluna)
            return (0);
        if (abs(pos[i] - coluna) == abs(i - linha))
            return (0);
        i++;
    }
    return (1);
}

void backtrack(int linha, int *pos, int n)
{
    int i;
    int j;
    int coluna;
    i = 0;
    j = 0;
    coluna = 0;
    if (linha == n)//se a linha chegar ate o valor de N (valor enviado pelo usuario)
    {
        i = 0;
        while(i < n)
        {
            printf("%d", pos[i]);
            if (i + 1 < n)
                printf(" ");
            i++;
        }
        printf ("\n");
    }
    while(coluna < n)
    {
        if (seguro(linha, coluna, pos))
        {
            pos[linha] = coluna;
            backtrack(linha + 1, pos, n);
        }
        coluna++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    if (!argv[1][0])
        return (1);
    int n;
    int *pos;
    n = atoi(argv[1]);
    pos = malloc(sizeof(int) * n);
    if (!pos)
        return (1);
    backtrack(0, pos, n);
    free(pos);
    return (0);
}