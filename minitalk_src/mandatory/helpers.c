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
        ft_putchar(*s++);
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
    while (ln > 0)
    {
        digits[i] = ln % 10 + 48;
        ln /= 10;
        i++;
    }
    while (i--)
        write(1, &digits[i], 1);
}

int ft_atoi(const char *str)
{
    int (sign), res;

    res = 0;
    sign = 1;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++; 
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign *= -1;
        str++;    
    }
    while (*str >= '0' && *str <= '9')
    {
        // if (*str < '0' || *str > '9')
        //     return (-1);
        res = res * 10 + (*str - '0');
        str++; 
    }
    if (!*str)
        return (0);
    return (res * sign);
}