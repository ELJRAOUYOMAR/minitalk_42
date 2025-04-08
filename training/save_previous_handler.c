#include <stdio.h>
#include <signal.h>

void my_handler(int sig) {
    printf("Custom handler for signal %d\n", sig);
}

int main() {
    // Set the new handler and store the old one
    void (*old_handler)(int);
    old_handler = signal(SIGINT, my_handler);

    if (old_handler == SIG_ERR) {
        perror("signal error");
    } else {
        printf("Signal handler set successfully.\n");
    }

    while (1);
    return 0;
}