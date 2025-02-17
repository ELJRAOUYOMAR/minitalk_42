#include "signal.h"

int main() {
    sigset_t set;

    // Initialize the signal set to empty
    sigemptyset(&set);

    // Add SIGINT (Ctrl+C) and SIGTERM to the signal set
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    // Block these signals
    sigprocmask(SIG_BLOCK, &set, NULL);
    printf("SIGINT and SIGTERM are now blocked. Press Ctrl+C, but nothing will happen!\n");

    // Sleep for 10 seconds to demonstrate blocking
    sleep(2);

    // Unblock signals
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("SIGINT and SIGTERM are now unblocked. Press Ctrl+C now!\n");

    // Infinite loop to allow checking behavior
    while (1) {
        sleep(1);
    }

    return 0;
}
