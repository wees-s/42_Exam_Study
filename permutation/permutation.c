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
#include <unistd.h>
#include <string.h>
void order(char *str, int index);
void permutation(char *str);

void permutation(char *str)
{
    puts(str);
    int index_pivo;
    int last_index;
    char temp;
    index_pivo = strlen(str) - 2;
    last_index = strlen(str) - 1;
    while (index_pivo >= 0)
    {
        if (str[index_pivo] > str[index_pivo + 1])
            index_pivo--;
        else
        {
            last_index = strlen(str) - 1;
            while (str[last_index] <= str[index_pivo])
                last_index--;
            temp = str[index_pivo];
            str[index_pivo] = str[last_index];
            str[last_index] = temp;
            order(str, index_pivo + 1);
            puts(str);
            index_pivo = strlen(str) - 2;
        }
    }
}

void order(char *str, int index)
{
    int j;
    char temp;

    j = index + 1;
    while (str[index])
    {
        j = index + 1;
        while (str[j])
        {
            if (str[index] > str[j])
            {
                temp = str[index];
                str[index] = str[j];
                str[j] = temp;
            }
            j++;
        }
        index++;
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