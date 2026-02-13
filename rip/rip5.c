#include <stdio.h>

int is_safe(char *str)
{
    int i = 0;
    int check = 0;
    while(str[i])
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

void solve(char *str, int remOpen, int remClose, int index)
{
    if (remOpen == 0 && remClose == 0 && is_safe(str))
    {
        printf("%s\n", str);
        return ;
    }
    if (remOpen > 0 && str[index] == '(')
    {
        str[index] = ' ';
        solve(str, remOpen - 1, remClose, index + 1);
        str[index] = '(';
    }
    if (remClose > 0 && str[index] == ')')
    {
        str[index] = ' ';
        solve(str, remOpen, remClose - 1, index + 1);
        str[index] = ')';
    }
    if (str[index] != '\0')
        solve(str, remOpen, remClose, index + 1);
}

int main(int argc, char **argv)
{
    int base = 0;
    int remOpen = 0;
    int remClose = 0;
    int i = 0;
    while (argv[1][i])
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
    solve(argv[1], remOpen, remClose, 0);
    return(0);
}