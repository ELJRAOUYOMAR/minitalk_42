#include "minitalk.h"
void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putstr(char *s)
{
    if (!s)
        return ;
    while (*s)
        putchar(*s++);
}

void ft_putnbr(int n)
{
    long ln;
    char digits[11];
    int i;

    ln = n;
    if (n == 0)
        ft_putchar('0');
    else if (n < 0)
    {
        putchar('-');
        ln = -ln;
    }
    i = 0;
    while (n > 0)
    {
        digits[i] = ln % 10 + 48;
        ln /= 10;
        i++;
    }
    while (i--)
        write(1, &digits[i], 1);
}