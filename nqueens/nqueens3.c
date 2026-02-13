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

int is_safe(int *pos, int line, int col)
{
    int i;

    i = 0;
    while (i < line)
    {
        if (pos[i] == col)
            return (0);
        int check1 = pos[i] - col;
        if (check1 < 0)
            check1 = check1 * -1;
        int check2 = i - line;
        if (check2 < 0)
            check2 = check2 * -1;
        if (check1 == check2)
            return (0);
        i++;
    }
    return (1);
}

void backtrack(int queens, int *pos, int line)
{
    int i;
    int col;

    col = 0;
    i = 0;
    if (line == queens)
    {
        while (i < queens)
        {
            fprintf(stdout, "%d ", pos[i]);
            i++;
        }
        fprintf(stdout, "\n");
        return ;
    }
    while (col < queens)
    {
        if (is_safe(pos, line, col))
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
    queens = atoi(argv[1]);
    int *pos;
    pos = (int *)malloc(sizeof(int) * queens);
    backtrack(queens, pos, 0);
    return (0);
}