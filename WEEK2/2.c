#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

    // execlp(command, arg0, arg1, ..., NULL)
    // arg0 is conventionally the program name itself
    if (execlp("ls", "ls", "-l", (char *)NULL) == -1)
    {
        perror("execlp failed");
        exit(1);
    }

    // This line will NOT be executed if execlp is successful
    printf("After execlp() call\n");

    return 0;
}
