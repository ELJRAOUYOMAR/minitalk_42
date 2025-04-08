#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*
 * int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
 * @signum: The signal number (e.g., SIGINT, SIGTERM, etc.)
 * @act: A pointer to a struct sigaction that defines the new action to be taken when the signal is received.
 * @ldact: A pointer to a struct sigaction where the previous action is saved. This parameter can be NULL if you're not interested in saving the old action.
 *
 * oldact allows you to:
 * Restore the old signal handler later.
 * Inspect what the current signal handler is.
 * Chain or temporarily override handlers. 
*/

void handler(int sig)
{
    printf("Custom handler: Caught signal %d\n", sig);
}

// int main()
// {
//     struct sigaction new_act;
//     struct sigaction old_act;

//     // Set new action
//     new_act.sa_handler = handler;
//     new_act.sa_flags = 0;
//     sigemptyset(&new_act.sa_mask); // No signal blocked during handler
    
//     // Set the signal handler and save the old one
//     if (sigaction(SIGINT, &new_act, &old_act) == -1)
//     {
//         perror("sigaction - restore");
//         return 1;
//     }

//     printf("Custom SIGINT hanlder set. Press CTRL+C\n");
//     // sleep(5);
//     pause(); // don't do anything just if a signal send 

//     //restore old handler
//     if (sigaction(SIGINT, &old_act, NULL) == -1)
//     {
//         perror("sigaction - restore");
//         return 1;
//     }

//     printf("Old SIGINT handler restore. Press Ctrl+C again\n");
//     // sleep(5);
//     pause();

//     return 0;
// }

int main()
{
    struct sigaction new_act;
    struct sigaction old_act;

    new_act.sa_handler = handler;
    new_act.sa_flags = 0;
    sigemptyset(&new_act.sa_mask);

    if (sigaction(2, &new_act, &old_act) == -1 )
    {
        perror("wdf");
        return 1;
    }

    printf("press ctrl+c");
    // fflush(stdout); // if you write the message without \n you can use fflush(stdout)
    pause();

    if (sigaction(2, &old_act, NULL) == -1)
    {
        perror("wdf");
        return 1;
    }
    printf("click other\n");
    pause();

    return 0;

}

