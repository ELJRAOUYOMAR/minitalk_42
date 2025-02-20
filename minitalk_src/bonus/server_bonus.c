#include "minitalk_bonus.h"

/*
 * get_pid - print the pid of the process
 * handle_signal(): receive bytes from the client side
*/
static void get_pid(pid_t pid);
void handle_signal(int signum, siginfo_t *info, void *context);

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

void handle_signal(int signum, siginfo_t *info, void *context)
{
    static unsigned char c;
    static int bit;
    static pid_t sender_pid;
    static int message_received;

    (void)context;
    sender_pid = 0;
    message_received = 0;
    if (sender_pid == 0)
        sender_pid = info->si_pid;
    if (signum == SIGUSR1)
        c |= (1 << (7 - bit));
    bit++;
    if (bit == 8)
    {
        ft_putchar(c);
        if (c == '\0')
        {
            ft_putchar('\n');
            kill(sender_pid, SIGUSR1); // Send acknowledgment to client
            if (!message_received)  // Print only once after the message
            {
                ft_putstr("this is message from: ");
                ft_putnbr(sender_pid);
                ft_putchar('\n');
                message_received = 1;  // Set flag to prevent further printing
            }
            sender_pid = 0;
            message_received = 0;
        }
        c = 0;
        bit = 0;
    }
}
