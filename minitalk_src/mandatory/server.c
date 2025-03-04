#include "minitalk.h"

/*
 * get_pid - print the pid of the process
 * handle_signal(): receive bytes from the client side
*/
static void get_pid(pid_t pid);

static void handle_signal(int signum);

int main()
{
    get_pid(getpid());
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
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

static void handle_signal(int signum)
{
    static unsigned char c;
    static int bit;

    if (signum == SIGUSR1)
        c |= (1 << (7 - bit));
    // else if (signum == SIGUSR2)
    //     c &= ~(1 << (7 - bit)); // Set the bit to 0 for SIGUSR2
    bit++;
    if (bit == 8)
    {
        ft_putchar(c);
        if (c == '\0')
            ft_putchar('\n');
        c = 0;
        bit = 0;
    }
}
