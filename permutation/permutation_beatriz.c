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


// C program to print all permutations 
// // with duplicates allowed 
// #include <stdio.h> 
// #include <string.h> 

// /* Function to swap values at 
//    two pointers */
// void swap(char *x, char *y) 
// { 
//     char temp; 
//     temp = *x; 
//     *x = *y; 
//     *y = temp; 
// } 

// void permute(char *a, int l, int r) 
// { 
//     int i; 
//     if (l == r) 
//         printf("%s\n", a); 
//     else
//     { 
//         i = l;
//         while (i <= r)
//         {
//             swap((a + l), (a + i)); 
//             permute(a, l + 1, r); 
//             swap((a + l), (a + i)); 
//             i++;
//         }
//     } 
// } 

// int main() 
// { 
//     char str[] = "BACD"; 
//     int n = strlen(str); 
//     permute(str, 0, n-1); 
//     return 0; 
// }

#include <stdio.h>

void sort_str(char *str, int i)
{
    int j;
    j = 0;
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
#include <string.h>
void permutation(char *str)
{
    puts(str);
    int i;
    int pivo;
    char temp;
    i = strlen(str) - 2;
    while(i >= 0)
    {
        if (str[i + 1] > str[i])
        {
            pivo = i;
            int sucessor = strlen(str) - 1;
            while (str[sucessor] <= str[pivo])
                sucessor--;
            temp = str[pivo];
            str[pivo] = str[sucessor];
            str[sucessor] = temp;
            sort_str(str, pivo + 1);
            puts(str);
            i = strlen(str) - 2;
        }
        else
            i--;
    }   
}

int main(int argc, char **argv)
{
    sort_str(argv[1], 0);
    permutation(argv[1]);
    return (0);
}