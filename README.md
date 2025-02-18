# MiniTalk Project

## Signals
### Introduction to Signals in C
Signals are asynchronous notifications sent to a process by the kernel or another process to notify it of an event. Some common signals include:

`SIGINT` (Interrupt): Sent when the user presses `Ctrl+C`.
`SIGTERM` (Terminate): Requests program termination.
`SIGSEGV` (Segmentation Fault): Sent when a program accesses an invalid memory location.
`SIGKILL` (Kill): Immediately terminates a process (cannot be caught or ignored).
`SIGALRM` (Alarm): Triggered when a timer set by `alarm()` expires.
`SIGCHLD` (Child): Sent to a parent process when a child process terminates.

### types of signals 
##### 1. Synchronous Signals (Errors in execution)
Caused by the process itself
- `SIGSEGV` (Segmentation fault) → Invalid memory access
- `SIGFPE` (Floating point exception) -> Division by zero
##### 2. Asynchronous Signals (External events)
Geerated by external sources, e.g.:
- `SIGINT` (Interrupt) → User presses Ctrl+C
- `SIGTERM` (Termination) → Another process requests termination

### How the kernel delivers signals
- **Queued?**Most signals are not queued; if the same signal is sent twice before being handled, the process only receives it once.
- **Handling Mode:** The kernel sets a flag for a signal and delivers it when the process resumes execution.
- **Blocked Signals:** If a process blocks a signal, it remains pending until unblocked.

### SIgnal lifecycle
1. Signal is generated (by a user, OS, or another process).
2. Kernel delivers the signal.
3. The process either
- Ignores the signal.
- Handles it with a custom handler.
- Uses the default action (exit, dump core, etc.).

## Registering Signal Handlers: signal() vs. sigaction()

### Handling signals with `signal()`  **(Simple but Unreliable)**
The signal() function allows you to specify how your program responds to signals. Its syntax:
```C
void (*signal(int signum, void (*handler)(int)))(int);
```
- `signum`: The signal number.
- `handler`: The function to handle the signal.

```C
#include <stdio.h>
#include <signal.h>

void handler(int signum) {
    printf("Caught signal %d\n", signum);
}

int main() {
    signal(SIG2INT, handler);
    while (1); // Infinite loop
}
```
**Problems with** signal()
- **Non-reentrant:** The handler can be interrupted before completing.
- **No control over signal masking** (if another signal arrives, it might interrupt the handler).


### Using sigaction() for Advanced Signal Handling **(Recommended)**
The `sigaction` function in C is used to examine and change the action associated with a specific signal. It is a more powerful and flexible alternative to signal(), as it allows precise control over signal handling behavior.
##### 1. Function prototype
```C
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
##### 2. Parameters 
- `signum`: The signal number to be modified (e.g., SIGINT, SIGTERM, etc.).
- `act`: A pointer to a struct sigaction that specifies the new action for the signal.
- `oldact`: A pointer to a struct sigaction where the previous action for the signal is stored (can be NULL if not needed).

##### 3. Return Values
. Return `0` on success.
. Return `-1` on failure and sets `errno` to indicate the error.

##### 4. The sigaction structure
the `struct sigaction` defines how a signal should be handled.
```C
struct sigaction {
    void (*sa_handler)(int);     /* Pointer to a signal handler function */
    void (*sa_sigaction)(int, siginfo_t *, void *); /* Used if SA_SIGINFO flag is set */
    sigset_t sa_mask;            /* Signals to be blocked during handler execution */
    int sa_flags;                /* Flags to modify behavior */
};
```
- `sa_handler`
    - `SIG_DFL` → Default action.
    - `SIG_IGN` → Ignore the signal.
    - A custom function → User-defined signal handler.
- `sa_sigaction`
    - Used instead of `sa_handler` when `SA_SIGINFO` flag is set.
    - Provides additional context through a `siginfo_t` structure.
- `sa_mask`
    - Specifies signals to block while the handler is running.
- `sa_flags` 
    - `SA_RESTART`: Restart interrupted system calls.
    - `SA_NOCLDWAIT`: Prevent zombie processes for child termination (`SIGCHLD`).
    - `SA_NOCLDSTOP`: Ignore `SIGCHLD` when a child stops.
    - `SA_NODEFER`: Do not block the signal while it is being handled.
    - `SA_SIGINFO`: Use `sa_sigaction` instead of `sa_handler`.

#### `SIGEMPTYSET` 
sigemptyset is a function used to initialize a signal set to be empty. It ensures that the signal set does not contain any signals, which is useful when configuring signal handlers with `sigaction()`.
##### 1. Prototype function
```C
#include <signal.h>

int sigemptyset(sigset_t *set);
```

##### 2. Parameters
- `set`: A pointer to a `sigset_t` (signal set) that will be initialized as empty.

##### 3. Return values
- Returns `0` on success.
- Returns `-1` on failure and sets errno.

##### 4. Example of usage [(see training/signal_library/sigemptyset.c file)](training\signal_library\sigemptyset.c)

##### 5. When to Use `sigemptyset`
- Before adding signals to a set using `sigaddset()`.
- When configuring `sigaction()` to specify `sa_mask` (signals blocked during handler execution).
- Before setting up signal blocking using `sigprocmask()`.

#### 6. [Example: Using sigemptyset with sigaction(training\signal_library\sigaction.c)](training\signal_library\sigaction.c)


### SIGUSR1 && SIGUSR2
in C, and SIGUSR2 are user-defined signals used for inter-process communication (IPC). They allow processes to send custom signals to each other. These signals are commonly handled using the signal() or sigaction() functions.

1. Understanding SIGUSR1 and SIGUSR2
SIGUSR1 (Signal 10 on most systems) and SIGUSR2 (Signal 12) are reserved for user-defined purposes.
They can be sent using kill() or raise().
Processes can define custom handlers to perform specific actions when receiving these signals.
2. Handling SIGUSR1 and SIGUSR2
You can set up a signal handler using signal():
```C
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handle_signal(int sig)
{
    if (sig == SIGUSR1)
        printf("Received SIGUSR1\n");
    else if (sig == SIGUSR2)
        printf("Received SIGUSR2\n");
}

int main()
{
    // Register signal handlers
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    printf("Process ID: %d\n", getpid());

    // Keep the process running to receive signals
    while (1)
        pause(); // Wait for signals

    return 0;
}
```

3. Sending Signals
From another terminal, send signals to the running process:
```sh
kill -SIGUSR1 <PID>
kill -SIGUSR2 <PID>
```
Or from within another C program:
```C
#include <signal.h>
#include <unistd.h>

int main()
{
    pid_t pid = 1234; // Replace with the target process ID
    kill(pid, SIGUSR1); // Send SIGUSR1
    return 0;
}
```

4. Using sigaction() Instead of signal()sigaction() is preferred for more reliable signal handling:
```C
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void handle_signal(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGUSR1)
        printf("Received SIGUSR1 from PID %d\n", info->si_pid);
    else if (sig == SIGUSR2)
        printf("Received SIGUSR2 from PID %d\n", info->si_pid);
}

int main()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("Process ID: %d\n", getpid());
    
    while (1)
        pause(); // Wait for signals

    return 0;
}
```

5. Key Points
- `SIGUSR1` and `SIGUSR2` are user-defined signals.
- Use `signal()` or `sigaction()` to handle them.
- Use `kill(pid, SIGUSR1)` or `kill(pid, SIGUSR2) to send signals.
- `sigaction()` provides better control, such as retrieving sender info.

### sigaddset()
sigaddset() is a function in the POSIX signal handling API that is used to add a signal to a signal set (a sigset_t structure). It is part of a group of functions that help manipulate sets of signals, which are used when blocking, unblocking, or masking signals.
```C 
#include <signal.h>

int sigaddset(sigset_t *set, int signum);
```
#### Parameters
- set → Pointer to a signal set (sigset_t) where the signal should be added.
- signum → The signal number to add (e.g., SIGINT, SIGTERM, SIGUSR1).
#### Return Value
- Returns 0 on success.
- Returns -1 on failure, with errno set to indicate the error.

#### Example: Using sigaddset()

### Why kill() and not sigaction() or signal() in minitalk to send signal
The main reason is that `kill()` is designed to send signals, while `sigaction()` is designed to handle them. Here's why:
- `kill()` is a direct way to send a signal to a specific process.
- It requires only a `PID` and the signal type.
- The OS handles the delivery of the signal immediately.

- `sigaction()` is useful for defining a callback function (handler) that is executed when a signal is received.
- It doesn’t send a signal but instead waits until a signal arrives.

#### Conclusion
- `kill(pid, signal)` is the correct choice for sending signals.
- `sigaction()` is the correct choice for receiving and handling signals.
- Minitalk uses `kill()` in the client and `sigaction()` in the server for effective signal-based IPC.
