#include "signal.h"

void handle_signal(int sig, siginfo_t *info, void *context)
{
    printf("signal %d received from process %d\n", sig, info->sa_pid);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIG)
}