#include <stdio.h>
#include <stdbool.h>

typedef struct file
{
    char name;
    int index_block;
    int data_blocks[200];
    int count;
} File;

int main(void)
{
    bool disk[1000] = {false}; // false = free

    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    File files[n];

    // Read files
    for (int f = 0; f < n; f++)
    {
        printf("\nFile %d:\n", f + 1);
        scanf(" %c", &files[f].name);

        printf("Index block: ");
        scanf("%d", &files[f].index_block);
        disk[files[f].index_block] = true; // occupy index block

        printf("Number of data blocks: ");
        scanf("%d", &files[f].count);

        printf("Data blocks: ");
        for (int i = 0; i < files[f].count; i++)
        {
            scanf("%d", &files[f].data_blocks[i]);
            disk[files[f].data_blocks[i]] = true; // occupy data blocks
        }
    }
    // Show allocation table
    printf("\nFile Allocation Table:\n");
    printf("%-8s %-10s %-10s %s\n", "Name", "Index", "Blocks", "Data Blocks");
    printf("----------------------------------------------------\n");
    for (int f = 0; f < n; f++)
    {
        printf("%-8c %-10d %-10d ", files[f].name, files[f].index_block, files[f].count);
        for (int i = 0; i < files[f].count; i++)
            printf("%d ", files[f].data_blocks[i]);
        printf("\n");
    }

    // Search file
    char find;
    printf("\nEnter file name to search: ");
    scanf(" %c", &find);

    for (int f = 0; f < n; f++)
    {
        if (files[f].name == find)
        {
            printf("\nFile '%c' found:\n", find);
            printf("Index block: %d\n", files[f].index_block);
            printf("Data blocks: ");
            for (int i = 0; i < files[f].count; i++)
                printf("%d ", files[f].data_blocks[i]);
            printf("\n");
            return 0;
        }
    }

    printf("File not found\n");
    return 0;
}
