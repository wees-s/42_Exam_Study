<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>

int is_valid(int *pos, int line, int col)
{
    int i = 0;
=======
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

int is_safe(int *pos, int col, int line)
{
    int i;

    i = 0;
>>>>>>> 6e3f22816845ee6dea65300685546e2e9249c0ea
    while (i < line)
    {
        if (pos[i] == col)
            return (0);
        int check1 = pos[i] - col;
<<<<<<< HEAD
        int check2 = line - i;
        if (check1 < 0)
            check1 = check1 * -1;
        if (check2 < 0)
            check2 = check2 * -1;
=======
        if (check1 < 0)
        {
            check1 = check1 * -1;
        }
        int check2 = i - line;
        if (check2 < 0)
        {
            check2 = check2 * -1;
        }
>>>>>>> 6e3f22816845ee6dea65300685546e2e9249c0ea
        if (check1 == check2)
            return (0);
        i++;
    }
    return (1);
}

<<<<<<< HEAD
void  backtrack(int *pos, int queens, int line)
{
    if (line == queens)
    {
        int i = 0;
        while (i + 1 < queens)
        {
            fprintf(stdout, "%d", pos[i]);
            if (i < queens)
=======
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
            fprintf(stdout, "%d", pos[i]);
            if (i + 1 != queens)
>>>>>>> 6e3f22816845ee6dea65300685546e2e9249c0ea
                fprintf(stdout, " ");
            i++;
        }
        fprintf(stdout, "\n");
        return ;
    }
<<<<<<< HEAD
    int col = 0;
    while (col < queens)
    {
        if (is_valid(pos, line, col))
        {
            pos[line] = col;
            backtrack(pos, queens, line + 1);
=======
    while (col < queens)
    {
        if (is_safe(pos, col, line))
        {
            pos[line] = col;
            backtrack(queens, pos, line + 1);
>>>>>>> 6e3f22816845ee6dea65300685546e2e9249c0ea
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
    queens = atoi(argv[1]);
    pos = (int *)malloc(sizeof(int) * queens);
<<<<<<< HEAD
    backtrack(pos, queens, 0);
    return (0);
}   
=======
    backtrack(queens, pos, 0);
    return (0);
}
>>>>>>> 6e3f22816845ee6dea65300685546e2e9249c0ea
