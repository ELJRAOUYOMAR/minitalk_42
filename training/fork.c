#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> // for pid_t
int main()
{
    pid_t pid = fork();
    
    if (pid < 0)
    {
        perror("fork failed");
    }
    else if (pid > 0)
    {
        printf("this is the parent process, child process: %d, parent process: %d, the pid: %d\n", pid, getpid(), pid);
    }
    else if (pid == 0)
    {
        printf("this is the child process, child process: %d, parent process: %d, the pid: %d\n", getpid(), getppid(), pid);
    }
    return (0);
}