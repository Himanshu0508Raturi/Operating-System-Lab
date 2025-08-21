#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    pid_t id1 = fork();

    if (id1 == -1)
    {
        printf("Fork Failed.\n");
        return 1;
    }
    else if (id1 == 0)
    {
        printf("Child Process 1\n");
        printf("Child PId: %d\n", getpid());
        printf("Files are:\n");
        execlp("ls", "ls", "-l", (char *)NULL);
        exit(0);
    }
    else if (id1 > 0)
    {

        wait(NULL);
        printf("Parent Process\n");
        printf("First Child Completed\n");
        printf("Parent PId: %d\n", getpid());

        pid_t id2 = fork();
        if (id2 < 0)
        {
            printf("Fork Failed\n");
            return 1;
        }
        else if (id2 == 0)
        {
            printf("Child Process 2\n");
            sleep(5);
            printf("Child PID: %d\n", getpid());
            exit(0);
        }
        else
        {
            printf("Parent Process\n");
            printf("Parent Pid: %d\n", getpid());
            exit(0);
        }
    }
    return 0;
}