#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int choice;
    printf("Enter Choice\n");
    printf("1. Orphan Process\n");
    printf("2. Zombie Process\n");
    scanf("%d", &choice);
    pid_t pid;
    if (choice == 1)
    {
        printf("\nOrphan Process\n");
        pid = fork();

        if (pid < 0)
        {
            printf("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process (Orphan demo)
            printf("Orphan Child started. PID: %d, Parent PID: %d\n", getpid(), getppid());
            sleep(5); // parent will exit first
            printf("Orphan Child still running. PID: %d, New Parent PID: %d \n",
                   getpid(), getppid());
            exit(0);
        }
        else
        {
            // Parent exits immediately
            printf("Parent exiting, leaving child as orphan. PID: %d\n", getpid());
            exit(0);
        }
    }
    else if (choice == 2)
    {
        printf("\nZombie Process\n");
        pid = fork();
        if (pid < 0)
        {
            printf("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process (Zombie demo)
            printf("Zombie Child started. PID: %d\n", getpid());
            exit(0); // Child exits quickly
        }
        else
        {
            // Parent does NOT call wait()
            printf("Parent (PID: %d) sleeping, Child will become zombie.\n", getpid());
            sleep(20); // check with "ps -elf" during this time
            printf("Parent exiting, zombie cleared.\n");
        }
    }
    return 0;
}
