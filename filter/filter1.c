// Assignment name : filter
// Expected files  : filter.c
// Allowed functions : read, write, strlen, memmem, memmove,
//                     malloc, calloc, realloc, free,
//                     printf, fprintf, stdout, stderr, perror
// --------------------------------------------------------------------------------

// Write a program that takes one and only one argument.

// Your program must read from stdin and write to stdout all the content read,
// except that every occurrence of the given string must be replaced by '*'
// (as many '*' as the length of the string).

// Your program will be tested with random buffer sizes using a custom read
// function. Therefore, the buffer you use may be filled with a different number
// of characters on each call to read.

// Example:

// $> echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
// ***defaaa***de******d***$
// $> echo 'ababcabababc' | ./filter ababc | cat -e
// *****ab*****$

// Your program must behave the same way as the following command:

// sed 's/<string>/***/g'

// More generally, your program must be equivalent to the shell script `filter.sh`
// provided in this directory (you can compare your program with it).

// Error handling:

// - If an error occurs during a read or a memory allocation, your program must
//   write "Error: " followed by the error message to stderr and return 1.
// - If the program is called without arguments, with an empty argument, or with
//   more than one argument, it must return 1.

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 7
#endif
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

char *ft_strdup(char *str);
void filter(char *big, char *needle);
char *ft_join(char *str1, char *str2);

void filter(char *big, char *needle)
{
    char *start;
    int b_len;
    int n_len;
    b_len = strlen(big);
    n_len = strlen(needle);
    while ((start = memmem(big, b_len, needle, n_len)))
        memset(start, '*', n_len);
    printf("%s", big);
}

char *ft_join(char *str1, char *str2)
{
    char *result;
    int i;
    int j;
    j = 0;
    i = 0;
    if (!str1 && str2)
        return((result = ft_strdup(str2)));
    if (str1 && !str2)
        return((result = ft_strdup(str1)));
    result = malloc(sizeof(char) * strlen(str1) + strlen(str2) + 1);
    while (str1[i])
    {
        result[i] = str1[i];
        i++;
    }
    while (str2[j])
    {
        result[i] = str2[j];
        j++;
        i++;
    }
    result[i] = '\0';
    return (result);
}

char *ft_strdup(char *str)
{
    char *result;
    int i;
    i = 0;
    if (!str[0])
    {
        result = malloc(sizeof(char) * 1);
        result[0] = '\0';
        return (result);
    }
    result = malloc(sizeof(char) * strlen(str) + 1);
    while (str[i])
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    if (!argv[1][0])
        return (1);
    char *buffer;
    char *temp;
    char *stash;
    ssize_t rd;
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
    {
        perror("ERROR:");
        return (1);
    }
    temp = NULL;
    stash = NULL;
    while ((rd = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[rd] = '\0';
        stash = ft_join(temp, buffer);
        if (!stash)
        {
            free(buffer);
            perror("ERROR:");
            return (1);
        }
        temp = stash;
    }
    filter(stash, argv[1]);
    free(stash);
    free(buffer);
    return (0);
}