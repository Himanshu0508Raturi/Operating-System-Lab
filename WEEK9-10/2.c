#include <stdio.h>
#include <stdbool.h>

typedef struct file
{
    char name;
    int start_block;
    int blocks[100];
    int no_of_blocks;
} file;

int main(void)
{
    bool blocks[1000];
    for (int i = 0; i < 1000; ++i)
    {
        blocks[i] = true; // true means free
    }

    int n;
    printf("Enter number of files: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of files.\n");
        return 1;
    }

    file files[n];

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter file %d name: ", i + 1);
        if (scanf(" %c", &files[i].name) != 1)
        {
            printf("Invalid file name input.\n");
            return 1;
        }

        printf("Enter starting block of file %d: ", i + 1);
        if (scanf("%d", &files[i].start_block) != 1)
        {
            printf("Invalid start block input.\n");
            return 1;
        }

        printf("Enter no of blocks in file %d: ", i + 1);
        if (scanf("%d", &files[i].no_of_blocks) != 1 ||
            files[i].no_of_blocks < 0 ||
            files[i].no_of_blocks > 100)
        {
            printf("Invalid number of blocks (0..%d).\n", 100);
            return 1;
        }

        if (files[i].no_of_blocks == 0)
        {
            printf("No blocks to read for file %c.\n", files[i].name);
            continue;
        }

        printf("Enter blocks for file %d: ", i + 1);
        for (int j = 0; j < files[i].no_of_blocks; j++)
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

                if (blocks[b] == false)
                {
                    printf("Block %d already occupied, enter another block: ", b);
                    continue;
                }

                // accept block
                files[i].blocks[j] = b;
                blocks[b] = false; // mark occupied
                break;
            }
        }
    }

    char ch;
    printf("\nEnter the file name to be searched: ");
    if (scanf(" %c", &ch) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }

    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (files[i].name == ch)
        {
            printf("\nFile Found!\n");
            printf("File Name: %c\n", files[i].name);
            printf("Start Block: %d\n", files[i].start_block);
            printf("No. of Blocks: %d\n", files[i].no_of_blocks);
            printf("Blocks Occupied (Linked): ");
            for (int j = 0; j < files[i].no_of_blocks; j++)
            {
                printf("%d", files[i].blocks[j]);
                if (j != files[i].no_of_blocks - 1)
                    printf(" -> ");
            }
            printf(" -> NULL\n");
            found = true;
            break;
        }
    }

    if (!found)
        printf("\nFile not found\n");

    return 0;
}
