#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    int x = fork();
    if (x == 0)
    {
        printf("child is created with id %d\n", getpid());
    }
    else if (x < 0)
    {
        printf("child not created");
    }
    else
    {
        sleep(1);
        printf("parent created\n");
    }
    return 0;
}
