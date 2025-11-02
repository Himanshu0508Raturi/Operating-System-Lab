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
        int bestIdx = -1;
        for (int j = 0; j < b; j++)
        {
            if (block[j] >= process[i])
            {
                if (bestIdx == -1 || block[j] < block[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocated[i] = bestIdx;
            block[bestIdx] -= process[i];
        }
    }

    for (int i = 0; i < p; i++)
    {
        if (allocated[i] != -1)
            printf("%d - %d\n", process[i], allocated[i] + 1);
        else
            printf("%d no free block allocated\n", process[i]);
    }

    return 0;
}
