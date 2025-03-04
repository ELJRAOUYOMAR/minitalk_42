#include "minitalk_bonus.h"

/*
 * get_pid - print the pid of the process
 * handle_signal(): receive bytes from the client side
*/
static void get_pid(pid_t pid);
static void process_message(unsigned char c, int sender_pid, int *message_received);
static void handle_signal(int signum, siginfo_t *info, void *context);

int main()
{
    struct sigaction sa;
    
    get_pid(getpid());
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
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

static void process_message(unsigned char c, int sender_pid, int *message_received)
{
    ft_putchar(c);
    if (c == '\0')
    {
        ft_putchar('\n');
        kill(sender_pid, SIGUSR1);
        if (!*message_received)
        {
            ft_putstr("this is a message from: ");
            ft_putnbr(sender_pid);
            ft_putchar('\n');
            *message_received = 1;
        }
    }
}

static void handle_signal(int signum, siginfo_t *info, void *context)
{
    static unsigned char c;
    static int bit;
    static int sender_pid;
    static int message_received;

    (void)context;
    if (!sender_pid)
        sender_pid = info->si_pid;
    if (signum == SIGUSR1)
        c |= (1 << (7 - bit));
    bit++;
    if (bit == 8)
    {
        process_message(c, sender_pid, &message_received);
        c = 0;
        bit = 0;
    }
}