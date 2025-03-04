#include "signal.h"

void handle_signal(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGUSR1)
        printf("Received SIGUSR1 from pid %d\n", info->si_pid);
    else if (sig == SIGUSR2)
        printf("Received SIGUSR2 from pid %d\n", info->si_pid);
}

int main()
{
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    // sigaction(SIGINT, &sa, NULL);
    printf("Process Id: %d\n", getpid());

    while (1)
        pause(); // wait for signals
    
    return 0; 
}