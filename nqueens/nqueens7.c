
#include <stdio.h>
#include <stdlib.h>

int is_valid(int line, int col, int *pos)
{
    int i = 0;
    while (i < line)
    {
        if (pos[i] == col)
            return(0);
        int check1 = pos[i] - col;
        int check2 = line - i;
        if (check1 < 0)
            check1 = check1 * -1;
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
    if (line == queens)
    {
        int i = 0;
        while (i < queens)
        {
            fprintf(stdout, "%d", pos[i]);
            if (i + 1 != queens)
                fprintf(stdout, " ");
            i++;
        }
        fprintf(stdout, "\n");
    }
    int col = 0;
    while (col < queens)
    {
        if (is_valid(line, col, pos))
        {
            pos[line] = col;
            backtrack(queens, pos, line + 1);
        }
        col++;
    }
}

int main(int argc, char **argv)
{
    int *pos;
    int queens;
    queens = atoi(argv[1]);
    pos = malloc(sizeof(int) * queens);
    backtrack(queens, pos, 0);
}