#include <stdio.h>

int main()
{
    int b, p;
    printf("Enter number of free blocks available : ");
    scanf("%d", &b);

    int block[b];
    for (int i = 0; i < b; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes : ");
    scanf("%d", &p);

    int process[p];
    for (int i = 0; i < p; i++)
        scanf("%d", &process[i]);

    int allocated[p];
    for (int i = 0; i < p; i++)
        allocated[i] = -1;

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (block[j] >= process[i])
            {
                allocated[i] = j;
                block[j] -= process[i];
                break;
            }
        }
    }

    for (int i = 0; i < p; i++)
    {
        if (allocated[i] != -1)
            printf("%d - %d\n", process[i], allocated[i] + 1);
        else
            printf("%d  no free block allocated\n", process[i]);
    }

    return 0;
}
