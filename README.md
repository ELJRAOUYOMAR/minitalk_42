# MiniTalk Project

## Signals
### Introduction to Signals in C
A signal is a software interrupt delivered to a process. Some common signals include:

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
    signal(SIGINT, handler);
    while (1); // Infinite loop
}
```
**Problems with** signal()
- **Non-reentrant:** The handler can be interrupted before completing.
- **No control over signal masking** (if another signal arrives, it might interrupt the handler).


#### Using sigaction() for Advanced Signal Handling **(Recommended)**
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
- `sa_handel`
    - `SIG_DFL` → Default action.
    - `SIG_IGN` → Ignore the signal.
    - A custom function → User-defined signal handler.
- `sa_siaction`
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

#### 6. [Example: Using sigemptyset with sigaction](training\signal_library\sigaction.c)


