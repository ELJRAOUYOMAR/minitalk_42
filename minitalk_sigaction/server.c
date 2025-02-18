#include "minitalk.h"

void sig_handler(int sig, siginfo_t *info, void *context)
{
    static char c;
    static int bit;

    (void)context;
    if (sig == SIGUSR1)
        c |= (1 << (7 - bit));
    bit++;
    if(bit == 8)
    {
        ft_putchar(c);
        if (c == '\0')
            kill(info->si_pid, SIGUSR1);
        c = 0;
        bit = 0;
    }
}

int main(void)
{
    struct sigaction sa;
    
    ft_putstr("Server PID: ");
    ft_putnbr(getpid());
    ft_putchar('\n');
    sa.sa_sigaction = sig_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
    return (0);
}