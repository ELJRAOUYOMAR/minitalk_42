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
    sa.sa_flags = SA_SIGINFO;  // SA_SIGINFO means  Use sa_sigaction instead of sa_handler.
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
        // ft_putchar('\n');
        kill(sender_pid, SIGUSR1);
        if (!*message_received)
        {
            ft_putstr("\nthis is a message from: ");
            ft_putnbr(sender_pid);
            ft_putchar('\n');
            *message_received = 1;
        }
    }
}

/*
    @bit: tracks how many bits have been received so far.
    @c: stores the binary representation of the character being received.
    @sender_pid: ensures that the server handles only one client at a time


    - If the signal is SIGUSR1, it means a 1 bit is received, so it sets the corresponding bit in c.
    - If the signal is SIGUSR2, it means a 0 bit is received, so c remains unchanged.
*/
static void handle_signal(int signum, siginfo_t *info, void *context)
{
    static unsigned char c;
    static int bit;
    static int sender_pid;
    static int message_received;

    (void)context;
    if (sender_pid == 0 || sender_pid != info->si_pid)
    {
        sender_pid = info->si_pid;
        c = 0;
        bit = 0;
        message_received = 0;  // Reset for new sender
    }
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