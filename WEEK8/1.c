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

    // -1 means not allocated
    int allocation[processes];
    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    // For each process, find BEST FIT block
    for (int i = 0; i < processes; i++)
    {
        int best_block = -1;
        int best_size = 999999; // track smallest suitable block

        // Scan all blocks for best fit
        for (int j = 0; j < blocks; j++)
        {
            if (free_blocks[j] >= proc_sizes[i] &&
                free_blocks[j] < best_size)
            {
                best_block = j;
                best_size = free_blocks[j];
            }
        }

        // Allocate if found
        if (best_block != -1)
        {
            allocation[i] = best_block;
            free_blocks[best_block] -= proc_sizes[i];
        }
    }

    // Print results
    printf("\nProcess Size | Block Number\n");
    printf("--------------------------------\n");
    for (int p = 0; p < processes; p++)
    {
        if (allocation[p] != -1)
            printf("%d          | %d\n", proc_sizes[p], allocation[p] + 1);
        else
            printf("%d          | Not Allocated\n", proc_sizes[p]);
    }

    return 0;
}
