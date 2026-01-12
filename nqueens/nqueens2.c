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

void backtrack(int queens, int *pos, int line);
int seguro(int linha, int coluna, int *pos);

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

void backtrack(int queens, int *pos, int line)
{
    int col;
    int i;

    i = 0;
    col = 0;
    if (line == queens)
    {
        while (i < queens)
        {
            printf("%d ", pos[i]);
            i++;
        }
        printf("\n");
    }
    while(col < queens)
    {
        if (seguro(line, col, pos))
        {
            pos[line] = col;
            backtrack(queens, pos, line + 1);
        }
        col++;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    if (!argv[1][0])
        return (1);
    int queens;
    int *pos;
    int line = 0;

    queens = atoi(argv[1]);
    if (queens < 1)
        return (0);
    pos = (int *)malloc(sizeof(int) * queens);
    backtrack(queens, pos, line);
    return (0);
}