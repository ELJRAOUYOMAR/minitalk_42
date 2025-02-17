#include "signal.h"


// Handling SIGINT (CTRL + C)
void handle_sigint(int signum)
{
    printf("Caught signal %d (SIGINT). Exiting safely...\n", signum);
    exit(0);
}

int main()
{
    // syntax of sinal : void (*signal(int signum, void (*handler)(int)))(int);
    // signal(2, handle_sigint);
    signal(SIGINT, handle_sigint);
    while (1)
    {
        printf("Running... Press Ctrl+C to exit.\n");
        sleep(2);
    }
    return 0;
}