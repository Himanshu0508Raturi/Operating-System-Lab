// indexed_allocation.c
#include <stdio.h>
#include <stdbool.h>

typedef struct file
{
    char name;
    int start_block;  // index block (as entered)
    int no_of_blocks; // number of data blocks
    int blocks[200];  // list of data blocks
    int allocated;    // 1 if allocation succeeded
} file;

int main(void)
{
    bool occupied[1000];
    for (int i = 0; i < 1000; ++i)
        occupied[i] = false;

    int n;
    printf("Enter number of files: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of files.\n");
        return 1;
    }

    file files[n];

    for (int i = 0; i < n; ++i)
    {
        files[i].allocated = 0;
        files[i].no_of_blocks = 0;

        printf("\nEnter file %d name: ", i + 1);
        if (scanf(" %c", &files[i].name) != 1)
        {
            printf("Invalid file name input.\n");
            return 1;
        }

        printf("Enter starting block of file %c: ", files[i].name);
        if (scanf("%d", &files[i].start_block) != 1)
        {
            printf("Invalid start block input.\n");
            return 1;
        }
        if (files[i].start_block < 0 || files[i].start_block >= 1000)
        {
            printf("Start block out of range (0..%d). Skipping file %c.\n", 1000 - 1, files[i].name);
            continue;
        }
        if (occupied[files[i].start_block])
        {
            printf("Start block %d already occupied. Skipping file %c.\n", files[i].start_block, files[i].name);
            continue;
        }

        printf("Enter number of blocks for file %c: ", files[i].name);
        if (scanf("%d", &files[i].no_of_blocks) != 1 ||
            files[i].no_of_blocks < 0 ||
            files[i].no_of_blocks > 200)
        {
            printf("Invalid number of blocks (0..%d). Skipping file %c.\n", 200, files[i].name);
            continue;
        }

        if (files[i].no_of_blocks == 0)
        {
            // mark index block as allocated even if there are no data blocks (optional)
            occupied[files[i].start_block] = true;
            files[i].allocated = 1;
            continue;
        }

        printf("Enter blocks for file %c: ", files[i].name);
        for (int j = 0; j < files[i].no_of_blocks; ++j)
        {
            int b;
            while (1)
            {
                if (scanf("%d", &b) != 1)
                {
                    // clear invalid token
                    int c;
                    while ((c = getchar()) != EOF && c != '\n')
                    {
                    }
                    printf("Invalid input. Enter a valid block number: ");
                    continue;
                }
                if (b < 0 || b >= 1000)
                {
                    printf("Block %d out of range (0..%d). Enter another block: ", b, 1000 - 1);
                    continue;
                }
                if (occupied[b])
                {
                    printf("Block %d already occupied. Enter another block: ", b);
                    continue;
                }
                // block is valid & free
                files[i].blocks[j] = b;
                break;
            }
        }

        // mark index block occupied and then mark data blocks occupied
        occupied[files[i].start_block] = true;
        for (int j = 0; j < files[i].no_of_blocks; ++j)
        {
            occupied[files[i].blocks[j]] = true;
        }
        files[i].allocated = 1;
    }

    // Print allocation table similar to sample
    printf("\n\nFile Allocation Table:\n");
    printf("%-12s %-12s %-12s %s\n", "File Name", "Start block", "No. of blocks", "Blocks occupied");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < n; ++i)
    {
        if (!files[i].allocated)
            continue;
        printf("%-12c %-12d %-12d ", files[i].name, files[i].start_block, files[i].no_of_blocks);
        for (int j = 0; j < files[i].no_of_blocks; ++j)
        {
            printf("%d", files[i].blocks[j]);
            if (j != files[i].no_of_blocks - 1)
                printf(", ");
        }
        printf("\n");
    }

    // Search for a file and display its info
    char ch;
    printf("\nEnter the file name to be searched : ");
    if (scanf(" %c", &ch) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    int found = 0;
    for (int i = 0; i < n; ++i)
    {
        if (files[i].allocated && files[i].name == ch)
        {
            found = 1;
            printf("\nFile Found!\n");
            printf("File Name: %c\n", files[i].name);
            printf("Start Block: %d\n", files[i].start_block);
            printf("No. of Blocks: %d\n", files[i].no_of_blocks);
            printf("Blocks Occupied: ");
            for (int j = 0; j < files[i].no_of_blocks; ++j)
            {
                printf("%d", files[i].blocks[j]);
                if (j != files[i].no_of_blocks - 1)
                    printf(", ");
            }
            printf("\n");
            break;
        }
    }
    if (!found)
    {
        printf("File not found.\n");
    }

    return 0;
}
