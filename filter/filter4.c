#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3
#endif
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

char *ft_strdup(char *str);

void filter(char *big, char *needle)
{
    char *start;
    char b_len = strlen(big);
    char n_len = strlen(needle);
    while ((start = memmem(big, b_len, needle, n_len)))
        memset(start, '*', n_len);
    printf("%s", big);
}

char *ft_join(char *str1, char *str2)
{
    if (str1 && !str2)
    {
        return (ft_strdup(str1));
    }
    if (!str1 && str2)
    {
            return (ft_strdup(str2));
    }
    char *result = malloc(sizeof(char) * strlen(str1) + strlen(str2) + 1);
    int i = 0; int j = 0;
    while (str1[i])
    {
        result[i] = str1[i];
        i++;
    }
    while (str2[j])
    {
        result[i] = str2[j];
        i++;
        j++;
    }
    result[i] = '\0';
    return (result);
}

char *ft_strdup(char *str)
{
    if (!str[0])
    {
        char *result = malloc(1);
        result[0] = '\0';
        return (result);
    }
    int i = 0;
    char *result = malloc(sizeof(char) * strlen(str) + 1);
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
    int rd;
    char *buffer;
    char *temp;
    char *stash;
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    temp = NULL;
    stash = NULL;
    while ((rd = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[rd] = '\0';
        stash = ft_join(stash, buffer);
        temp = stash;
    }
    filter(stash, argv[1]);
    free(buffer);
    return (0);
}