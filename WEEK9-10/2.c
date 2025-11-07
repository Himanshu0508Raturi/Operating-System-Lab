// linked_allocation.c
#include <stdio.h>
#include <stdbool.h>

#define MAX_BLOCKS 1000
#define MAX_BLOCKS_PER_FILE 10

typedef struct file
{
    char name;                       // single-character file name
    int start_block;                 // first block in the linked list
    int blocks[MAX_BLOCKS_PER_FILE]; // list of block numbers (links)
    int no_of_blocks;
} file;

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

    file files[n];

    for (int i = 0; i < n; ++i)
    {
        // read file name
        printf("\nEnter file %d name (single char): ", i + 1);
        scanf(" %c", &files[i].name); // leading space skips newline

        // read number of blocks
        printf("Enter number of blocks in file %d (max %d): ", i + 1, MAX_BLOCKS_PER_FILE);
        if (scanf("%d", &files[i].no_of_blocks) != 1 || files[i].no_of_blocks <= 0 ||
            files[i].no_of_blocks > MAX_BLOCKS_PER_FILE)
        {
            printf("Invalid block count. Setting to 0 and skipping file.\n");
            files[i].no_of_blocks = 0;
            continue;
        }

        printf("Enter block numbers for file %d (space/newline separated):\n", i + 1);
        for (int j = 0; j < files[i].no_of_blocks; ++j)
        {
            int b;
            while (1)
            {
                if (scanf("%d", &b) != 1)
                {
                    printf("Invalid input. Try again: ");
                    // clear stdin's non-numeric token
                    int c;
                    while ((c = getchar()) != EOF && c != '\n')
                        ;
                    continue;
                }
                if (b < 0 || b >= MAX_BLOCKS)
                {
                    printf("Block %d out of range (0..%d). Enter another block: ", b, MAX_BLOCKS - 1);
                    continue;
                }
                if (!blocks[b])
                {
                    printf("Block %d already occupied. Enter another block: ", b);
                    continue;
                }
                // accept the block
                files[i].blocks[j] = b;
                blocks[b] = false; // mark occupied
                break;
            }
        }

        // set start_block to the first entered block to represent the head of the linked list
        files[i].start_block = files[i].no_of_blocks > 0 ? files[i].blocks[0] : -1;
    }

    // search for file by name
    char ch;
    printf("\nEnter the file name to be searched (single char): ");
    scanf(" %c", &ch);

    bool found = false;
    for (int i = 0; i < n; ++i)
    {
        if (files[i].name == ch)
        {
            printf("\nFile Found!\n");
            printf("File Name: %c\n", files[i].name);
            printf("Start Block: %d\n", files[i].start_block);
            printf("No. of Blocks: %d\n", files[i].no_of_blocks);
            printf("Blocks Occupied (Linked): ");
            for (int j = 0; j < files[i].no_of_blocks; ++j)
            {
                printf("%d -> ", files[i].blocks[j]);
            }
            printf("NULL\n");
            found = true;
            break;
        }
    }

    if (!found)
    {
        printf("File not found.\n");
    }

    return 0;
}
