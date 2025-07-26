#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t id = fork();
    if (id < 0)
    {
        printf("Forked Failed\n");
        return 1;
    }
    else if (id == 0)
    {
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else
    {
        printf("Parent Process\n");
        printf("Child PID: %d\n", id);
        printf("Parent PID: %d\n", getpid());
    }
    return 0;
}