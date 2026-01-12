#include <stdio.h>
#include <stdlib.h>

int is_safe(int *pos, int col, int line)
{
    int i = 0;
    while (i < line)
    {
        if (pos[i] == col)
            return (0);
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
            i++;
            if (i < queens)
                fprintf(stdout, " ");
        }
        fprintf(stdout, "\n");
        return ;
    }
    int col = 0;
    while (col < queens)
    {
        if (is_safe(pos, col, line))
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
    int *pos;
    int queens;
    queens = atoi(argv[1]);
    pos = (int *)malloc(sizeof(int) * queens);
    if (!pos)
        return (1);
    int line = 0;
    backtrack(queens, pos, line);
    return (0);
}