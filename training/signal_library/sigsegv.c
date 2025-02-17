#include "signal.h"

// Handling SIGSEGV 
void handle_sigint(int signum)
{
    printf("Caught signal %d (SIGINT). Exiting safely...\n", signum);
    exit(0);
}

int main()
{
    int *ptr = NULL;
    signal(SIGSEGV, handle_sigint);
    int i = 1;
    while (1)
    {
        printf("Running... %d\n", i);
        sleep(2);
        // it runs the previous lines just on time because there is a segfault here (we should dereference).
        *ptr = 0;
        i++;
    }
    return 0;
}