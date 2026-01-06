// Assignment name  : permutations
// Expected files   : *.c *.h
// Allowed functions: puts, malloc, calloc, realloc, free, write
// ---------------------------------------------------------------

// Write a program that will print all the permutations of a string given as argument.

// The solutions must be given in alphabetical order.

// We will not try your program with strings containing duplicates (eg: 'abccd').

// For example this should work:

// $> ./permutations a | cat -e
// a$

// $> ./permutations ab | cat -e
// ab$
// ba$

//$> ./permutations abc | cat -e
//abc$
//acb$
//bac$
//bca$
//cab$
//cba$

#include <stdio.h>
#include <string.h>
void order(char *str, int i);
void permutation(char *str);

void permutation(char *str)
{
    puts(str);
    int pivo;
    int sucessor;
    char temp;

    pivo = strlen(str) - 2;
    while (pivo >= 0)
    {
        if (str[pivo] <= str[pivo + 1])
        {
            sucessor = strlen(str) - 1;
            while(str[sucessor] <= str[pivo])
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
    int     j;
    char    temp;

    j = i + 1;
    while (str[i])
    {
        j = i + 1;
        while(str[j])
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
    if (argc != 2)
        return (1);
    if (!argv[1][0])
        return (1);
    order(argv[1], 0);
    permutation(argv[1]);
    return (0);
}