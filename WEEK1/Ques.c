// Given an array , the parent process should count even numbers while child process should count odd numbers in an array. The parent
// process should executes first then child process. 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    pid_t id = fork();
    int arr[5] = {2, 4, 5, 67, 43};
    int n = 5;

    if (id < 0)
    {
        printf("Fork Failed\n");
    }
    else if (id == 0)
    {
        sleep(1);
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] % 2 != 0)
            {
                cnt++;
            }
        }
        printf("From Child Process Odd count: %d\n", cnt);
    }
    else if (id > 0)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] % 2 == 0)
            {
                cnt++;
            }
        }
        printf("From Parent Process Even count: %d\n", cnt);
        wait(NULL);
    }
    return 0;
}