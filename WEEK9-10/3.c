// index_allocation.c
#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 1000
#define MAX_BLOCKS_PER_FILE 20 // max data blocks a file can have

typedef struct
{
    char name;                       // single-char file name
    int index_block;                 // block number that acts as index block
    int blocks[MAX_BLOCKS_PER_FILE]; // list of data block numbers
    int no_of_blocks;                // number of data blocks
    bool allocated;                  // was allocation successful?
} File;

int main(void)
{
    bool blocks[MAX_BLOCKS]; // true = free, false = occupied
    for (int i = 0; i < MAX_BLOCKS; ++i)
        blocks[i] = true;

    int n;
    printf("Enter number of files: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of files.\n");
        return 1;
    }

    File files[n];

    for (int i = 0; i < n; ++i)
    {
        // read file name
        printf("\nEnter file %d name (single char): ", i + 1);
        scanf(" %c", &files[i].name);

        // read index block (the block that will store the pointers)
        printf("Enter index block number for file %c (0..%d): ", files[i].name, MAX_BLOCKS - 1);
        if (scanf("%d", &files[i].index_block) != 1)
        {
            printf("Invalid input. Skipping file.\n");
            files[i].allocated = false;
            continue;
        }

        if (files[i].index_block < 0 || files[i].index_block >= MAX_BLOCKS)
        {
            printf("Index block out of range. Skipping file %c.\n", files[i].name);
            files[i].allocated = false;
            continue;
        }

        if (!blocks[files[i].index_block])
        {
            printf("Index block %d already occupied. Skipping file %c.\n", files[i].index_block, files[i].name);
            files[i].allocated = false;
            continue;
        }

        // read number of data blocks
        printf("Enter number of data blocks for file %c (1..%d): ", files[i].name, MAX_BLOCKS_PER_FILE);
        if (scanf("%d", &files[i].no_of_blocks) != 1 ||
            files[i].no_of_blocks <= 0 || files[i].no_of_blocks > MAX_BLOCKS_PER_FILE)
        {
            printf("Invalid number of blocks. Skipping file %c.\n", files[i].name);
            files[i].allocated = false;
            continue;
        }

        // Check if enough free blocks exist (excluding index block, which we'll occupy)
        int free_count = 0;
        for (int b = 0; b < MAX_BLOCKS; ++b)
            if (blocks[b] && b != files[i].index_block)
                free_count++;
        if (free_count < files[i].no_of_blocks)
        {
            printf("Not enough free blocks to allocate file %c. Needed %d, free %d. Skipping.\n",
                   files[i].name, files[i].no_of_blocks, free_count);
            files[i].allocated = false;
            continue;
        }

        // Reserve the index block
        blocks[files[i].index_block] = false;

        // Auto-allocate data blocks: find first free blocks
        int allocated = 0;
        for (int b = 0; b < MAX_BLOCKS && allocated < files[i].no_of_blocks; ++b)
        {
            if (blocks[b] && b != files[i].index_block)
            {
                files[i].blocks[allocated++] = b;
                blocks[b] = false; // mark as occupied
            }
        }

        if (allocated == files[i].no_of_blocks)
        {
            files[i].allocated = true;
            printf("File %c allocated. Index block = %d. Data blocks allocated: %d\n",
                   files[i].name, files[i].index_block, files[i].no_of_blocks);
        }
        else
        {
            // should not happen because we prechecked free_count, but handle gracefully
            printf("Allocation failed unexpectedly for file %c; freeing any partial allocation.\n", files[i].name);
            // free any allocated data blocks and index block
            for (int k = 0; k < allocated; ++k)
                blocks[files[i].blocks[k]] = true;
            blocks[files[i].index_block] = true;
            files[i].allocated = false;
        }
    }

    // Print Allocation Table
    printf("\nFile Allocation Table (Index Allocation)\n");
    printf("File | Index Block | No. Data Blocks | Data Blocks (list)\n");
    printf("-----+-------------+-----------------+--------------------\n");
    for (int i = 0; i < n; ++i)
    {
        if (!files[i].allocated)
            continue;
        printf("  %c  |     %4d    |       %3d      | ",
               files[i].name, files[i].index_block, files[i].no_of_blocks);
        for (int j = 0; j < files[i].no_of_blocks; ++j)
        {
            printf("%d", files[i].blocks[j]);
            if (j + 1 < files[i].no_of_blocks)
                printf(" -> ");
        }
        printf("\n");
    }

    return 0;
}
