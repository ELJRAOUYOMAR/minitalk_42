#include "minitalk.h"

void acknowledge(int sig)
{
    if (sig == SIGUSR1)
        ft_putstr("Message received by server.\n");
}

void send_signal(int pid, char c)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if ((c >> 7 - bit) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        bit++;
    }
}

void send_message(int pid, char *str)
{
    while (*str)
        send_signal(pid, *str++);
    send_signal(pid, '\n');
}

int main(int ac, char **av)
{
    int pid;
    int i;

    if (ac != 3)
    {
        ft_putstr("Usage: ./client <PID> <Message>\n");
        return (-1);
    }
    pid = ft_atoi(av[1]);
    if (pid <= 0)
    {
        ft_putstr("Invalid PID, please enter a valid pid number\n");
        return (1);
    }
    if (kill(pid, 0) == -1)
    {
        ft_putstr("Invalid PID, no such process\n");
        return (1);
    }
    signal(SIGUSR1, acknowledge);
    send_message(pid, av[2]);
    return (0);
}
