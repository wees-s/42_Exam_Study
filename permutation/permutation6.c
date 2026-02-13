#include <stdio.h>
#include <string.h>
void order(char *str, int i);
void solve(char *str)
{
    puts(str);
    char temp; int pivo = strlen(str) - 2; int sucessor = strlen(str) - 1;
    while (pivo >= 0)
    {
        sucessor = strlen(str) - 1;
        if (str[pivo] < str[pivo + 1])
        {
            if (str[sucessor] < str[pivo])
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

void order(char *str, int i)
{
    int j = i + 1;
    char temp;
    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] > str[j])
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    order(argv[1], 0);
    solve(argv[1]);
    return (0);
}