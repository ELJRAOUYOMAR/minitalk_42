#include "minitalk.h"

/*
 * send_signal - send signal to the server.
 * @pid: the process id of the signal.
 * @c: the character to be sent to the server(we send charachter by character).
 * 
 * SIGUSR1 = Bit 1 (1)
 * SIGUSR2 = Bit 0 (0)
 * kill(pid, SIGUSR1): send SIGUSR1 signal to process with PID `pid`. 
 * Return:  
*/
static void send_signal(pid_t pid, char c);

static void send_massage(pid_t pid, char *str);

int main(int ac, char **av)
{
    int pid;

    if (ac != 3)
    {
        ft_putstr("Usage: ./client <PID> <Message>\n");
        return (1);   // EXIT_FAILURE in stdlib
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
    send_massage(pid, av[2]);
    return (0);
}

static void send_signal(pid_t pid, char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
        if ((c >> bit) & 1)
            kill(pid, SIGUSR1);
        else 
            kill(pid, SIGUSR2);
        usleep(500);
        bit--;
    }
}

static void send_massage(pid_t pid, char *str)
{
    int i;

    i = 0;
    while (str[i])
        send_signal(pid, str[i++]);
    send_signal(pid, '\0');
}