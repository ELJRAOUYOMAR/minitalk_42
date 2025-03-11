#include "minitalk.h"

/*
 * get_pid - print the pid of the process
 * handle_signal(): receive bytes from the client side
*/
static void get_pid(pid_t pid);

static void handle_signal(int signum, siginfo_t *info, void *context);

int main()
{
    struct sigaction sa;

    get_pid(getpid());
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
    return (0);
}

static void get_pid(pid_t pid)
{
    ft_putstr("Process Id: ");
    ft_putnbr(pid);
    ft_putchar('\n');
}

static void handle_signal(int signum, siginfo_t *info, void *context)
{
    static unsigned char c;
    static int bit;
    static pid_t client_pid;

    (void)context;
    if (client_pid == 0 || client_pid != info->si_pid)
    {
        client_pid = info->si_pid;
        c = 0;
        bit = 0;
    }
    if (signum == SIGUSR1)
        c |= (1 << (7 - bit));
    bit++;
    if (bit == 8)
    {
        ft_putchar(c);
        // if (c == '\0')
        //     ft_putchar('\n');
        c = 0;
        bit = 0;
    }
}
