#include <stdio.h>

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
    return (flag == 0);
}

void solve(char *str, int remOpen, int remClose, int index)
{
    if (str[index] == '\0')
    {
        if (remOpen == 0 && remClose == 0 && is_valid(str)) //se OPEN e CLOSE == 0 e FOR VÁLIDO, PRINTA
        {
            printf("%s\n", str);
        }
        return ;
    }
    if (str[index] == '(' && remOpen > 0)
    {
        str[index] = ' ';//troca pra espaço
        solve(str, remOpen - 1, remClose, index - 1);
        str[index] = '(';
    }
    if (str[index] == ')' && remClose > 0)
    {
        str[index] = ' ';
        solve(str, remOpen, remClose - 1, index - 1);
        str[index] = ')';
    }
    solve(str, remOpen, remClose, index + 1);
}

int main(int argc, char **argv)
{
    int i = 0;
    int balance = 0;
    int remOpen = 0;
    int remClose = 0;
    while (argv[1][i])
    {
        if (argv[1][i] == '(')
            balance++;
        else if (argv[1][i] == ')')
        {
            if (balance > 0)
                balance--;
            else
                remClose++;
        }
        i++;
    }
    remOpen = balance;
    solve(argv[1], remOpen, remClose, 0);
    return (0);
}