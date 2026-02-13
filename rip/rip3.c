#include <stdio.h>

int is_safe(char *str)
{
    int i = 0;
    int check = 0;
    while (str[i])
    {
        if (str[i] == '(')
            check++;
        if (str[i] == ')')
            check--;
        if (check < 0)
            return (0);
        i++;
    }
    return (check == 0);
}

void solve(int remOpen, int remClose, char *str, int index)
{
    if (remOpen == 0 && remClose == 0 && is_safe(str))
    {
        printf("%s\n", str);
        return ;
    }
    if (remOpen > 0 && str[index] == '(')
    {
        str[index] = ' ';
        solve(remOpen - 1, remClose, str, index + 1);
        str[index] = '(';
    }
    if (remClose > 0 && str[index] == ')')
    {
        str[index] = ' ';
        solve(remOpen, remClose - 1, str, index + 1);
        str[index] = ')';
    }
    if (str[index] != '\0')
        solve(remOpen, remClose, str, index + 1);
}

int main(int argc, char **argv)
{
    int remOpen; int remClose; int base; int i;
    i = 0;
    remOpen = 0;
    remClose = 0;
    base = 0;
    while(argv[1][i])
    {
        if (argv[1][i] == '(')
            base++;
        if (argv[1][i] == ')')
        {
            if (base > 0)
                base--;
            else
                remClose++;
        }
        i++;
    }
    remOpen = base;
    solve(remOpen, remClose, argv[1], 0);
    return (0);
}