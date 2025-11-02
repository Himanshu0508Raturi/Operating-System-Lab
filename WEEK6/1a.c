#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int p[2];
    int returnstatus;
    char writing[2][25] = {"hello", "world"};
    char readmsg[25];
    returnstatus = pipe(p);
    if (returnstatus == -1)
    {
        printf("Pipe not created\n");
        return 1;
    }
    printf("Writing started: %s\n", writing[0]);
    write(p[1], writing[0], strlen(writing[0]) + 1);
    read(p[0], readmsg, sizeof(readmsg));
    printf("Reading from pipe - msg1: %s\n", readmsg);
    return 0;
}
