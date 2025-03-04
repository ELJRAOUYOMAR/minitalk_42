#include "signal.h"


/*
sigemptyset(&set) initializes set to be empty.
This ensures no signals are blocked or included in the set.
*/

int main()
{
    sigset_t set;
    if (sigemptyset(&set) == -1)  
    {
        perror("sigemptyset failed\n");
        return 1;
    }
    printf("signal set initialized and empty.\n");
    return (0);
}