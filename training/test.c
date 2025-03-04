#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    write(STDOUT_FILENO, "I won't die\n", 13);
}
void seghandler(int sig)
{
    printf("seg fault\t");
}
int main()
{
    int *ptr = NULL;
    signal(SIGINT, handler);
    signal(SIGTERM, handler); // SIGTERM -> requests program termination
    signal(SIGSEGV, seghandler);

    while (1)
    {
        printf("Wasting your cycle %d\n",getpid());
        sleep(1);
        // segfault here, because not derefrence 
        *ptr = 42;
    }
}