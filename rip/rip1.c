#include <stdio.h>
#include <string.h>

int is_valid(char *str)
{
    int i;
    int flag;

    flag = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '(')
            flag++;
        else if (str[i] == ')')
            flag--;
        if (flag < 0)
            return (0);
        i++;
    }
    return (flag == 0); //true, deu certo.
}
void solve(int remopen, int remclose, char *str, int index)
{
    if (str[index] == '\0')
    {
        if (remclose == 0 && remopen == 0 && is_valid(str))
        {
            printf("%s\n", str);
        }
        return ;
    }
    if (str[index] == '(')
    {
        if (remopen > 0)
        {
            str[index] = ' ';
            solve(remopen - 1, remclose, str, index + 1);
            str[index] = '(';
        }
    }
    else if (str[index] == ')')
    {
        if (remclose> 0)
        {
            str[index] = ' ';
            solve(remopen, remclose - 1, str, index + 1);
            str[index] = ')';
        }
    }
    solve(remopen, remclose, str, index + 1);
}

int main(int argc, char **argv)
{
    int remopen;
    int remclose;
    int balance;
    int i;

    remopen = 0;
    remclose = 0;
    balance = 0;
    i = 0;
    while(argv[1][i])
    {
        if (argv[1][i] == '(')
            balance++;
        else if (argv[1][i] == ')')
        {
            if (balance > 0)
                balance--;
            else
                remclose++;
        }
        i++;
    }
    remopen = balance;
    solve(remopen, remclose, argv[1], 0);
    return(0);
}