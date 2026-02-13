#include <string.h>
#include <stdio.h>

void order(char *str, int i)
{
    int j;
    while (str[i])
    {
        j = i + 1;
        while(str[j])
        {
            if (str[i] > str[j])
            {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
            j++;
        }
        i++;
    }
}

void solve(char *str)
{
    puts(str);
    int pivo = strlen(str) - 2;
    int sucessor = strlen(str) - 1;
    char temp;
    while (pivo >= 0)
    {
        sucessor = strlen(str) - 1;
        if (str[pivo] < str[pivo + 1])
        {
            while (str[sucessor] < str[pivo])
                sucessor--;
            temp = str[pivo];
            str[pivo] = str[sucessor];
            str[sucessor] = temp;
            order(str, pivo + 1);
            puts(str);
            pivo = strlen(str) - 2;
        }
        else
            pivo--;
    }
}

int main (int argc, char **argv)
{
    order(argv[1], 0);
    solve(argv[1]);
    return (0);
}