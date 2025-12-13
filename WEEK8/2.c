#include <stdio.h>

int main(void)
{
    int blocks, processes;

    printf("Enter number of free blocks: ");
    scanf("%d", &blocks);

    int free_blocks[blocks];
    for (int i = 0; i < blocks; i++)
        scanf("%d", &free_blocks[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);

    int proc_sizes[processes];
    for (int i = 0; i < processes; i++)
        scanf("%d", &proc_sizes[i]);

    int allocation[processes];
    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    // FIRST FIT: take first block that fits
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < blocks; j++)
        {
            if (free_blocks[j] >= proc_sizes[i])
            {
                allocation[i] = j;
                free_blocks[j] -= proc_sizes[i];
                break; // stop at FIRST match
            }
        }
    }

    // Print results
    printf("\nProcess | Block\n");
    printf("--------|------\n");
    for (int p = 0; p < processes; p++)
    {
        if (allocation[p] != -1)
            printf("%d     | %d\n", proc_sizes[p], allocation[p] + 1);
        else
            printf("%d     | Not allocated\n", proc_sizes[p]);
    }

    return 0;
}
