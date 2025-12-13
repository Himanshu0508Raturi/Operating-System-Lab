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

    // WORST FIT: take LARGEST block that fits
    for (int p = 0; p < processes; p++)
    {
        int worst_block = -1;
        int max_size = 0; // track largest suitable block

        // Scan all blocks for worst fit
        for (int b = 0; b < blocks; b++)
        {
            if (free_blocks[b] >= proc_sizes[p] &&
                free_blocks[b] > max_size)
            {
                worst_block = b;
                max_size = free_blocks[b];
            }
        }

        // Allocate if found
        if (worst_block != -1)
        {
            allocation[p] = worst_block;
            free_blocks[worst_block] -= proc_sizes[p];
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
