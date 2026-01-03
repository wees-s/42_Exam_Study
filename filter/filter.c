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

// Notes:

// - To use memmem:
//       #define _GNU_SOURCE
//       #include <string.h>

// - To use perror:
//       #include <errno.h>

// - To use read:
//       #include <fcntl.h>



/*****************************************************************************************/
// NOTES:
// memmem includes:
//              #define _GNU_SOURCE
// 			    #include <string.h>

// perror includes:
//                 #include <errno.h>

// read includes:
//                 #include <fcntl.h>
/*****************************************************************************************/
#define _GNU_SOURCE
#define BUFFER_SIZE 1
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*****************************************************************************************/
// Write a program that will take one and only one argument.
// If the program is called without arguments or with an empty argument or with multiple
// arguments, it must return 1.
/*****************************************************************************************/

char *filter(char *str1, char *str2)
{
    return(NULL);
}

char *join(char *str1, char *str2)
{
    char *result;
    if (str1[0] && str2[0])
    {
        write(1, "a", 1);
        result = malloc(sizeof(char) * (strlen(str1) + strlen(str2)) + 1);
    }
    if (str1[0] && str2[0] != '\0')
    {
        write(1, "b", 1);
        result = malloc(sizeof(char) * strlen(str1) + 1);
        result[strlen(str1)] = '\0';
        return (result);
    }
    if (str2[0] && str1[0] != '\0')
    {
        write(1, "c", 1);
        result = malloc(sizeof(char) * strlen(str2) + 1);
        result[strlen(str2)] = '\0';
        return(result);
    }
    write(1, "d", 1);
    int i = 0;
    int j = 0;
    while (str1[j] != '\0')
    {
        result[i] = str1[j];
        j++;
        i++;
    }
    j = 0;
    while (str2[j] != '\0')
    {
        result[i] = str2[j];
        j++;
        i++;
    }
    result[i] = '\0';
    return(result);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    if (!argv[1][0])
        return (1);
    ssize_t fd;
    char    *buffer;
    char    *temp;
    char    *stash;
    temp = malloc(sizeof(char) * 1);
    stash = malloc(sizeof(char) * 1);
    buffer = malloc(sizeof(char) * strlen(buffer) + 1);
    while ((fd = read(0, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[fd] = '\0';
        stash = join(temp, buffer);
        temp = stash;
        free(stash);
    }
    printf("%s\n", temp);
    return (0);
}
