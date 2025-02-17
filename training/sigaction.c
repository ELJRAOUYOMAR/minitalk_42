#include "signal.h"

void handle_signal(int sig)
{
    printf("Caught signal %d\n", sig);
    // signal(SIGINT, SIG_DFL); // Restore default behavior
    exit(0);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    printf("Process ID: %d\n", getpid());
    while (1)
    {
        printf("Running... Press CTRL+C to trigger SIGINT.\n");
        sleep(2);
    }
    return 0;
}