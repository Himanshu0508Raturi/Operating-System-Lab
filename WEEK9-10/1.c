#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    char name;
    int start;
    int blocks;
} File;

int main(void)
{
    bool disk[1000]; // true = free, false = allocated
    for (int i = 0; i < 1000; i++)
        disk[i] = true;

    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    File files[n];

    // Input files and mark blocks as allocated
    for (int i = 0; i < n; i++)
    {
        printf("File %d - Name: ", i + 1);
        scanf(" %c", &files[i].name); // space clears input buffer

        printf("Start block: ");
        scanf("%d", &files[i].start);
        printf("Number of blocks: ");
        scanf("%d", &files[i].blocks);

        // Mark blocks as occupied
        for (int j = 0; j < files[i].blocks; j++)
            disk[files[i].start + j] = false;
    }

    // Search for file
    char search;
    printf("Enter file name to search: ");
    scanf(" %c", &search);

    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (files[i].name == search)
        {
            printf("\nFile '%c' found:\n", search);
            printf("Start Block: %d\n", files[i].start);
            printf("Blocks: %d\n", files[i].blocks);
            printf("Blocks occupied: ");
            for (int j = 0; j < files[i].blocks; j++)
                printf("%d ", files[i].start + j);
            printf("\n");
            found = true;
            break;
        }
    }

    if (!found)
        printf("File '%c' not found\n", search);

    return 0;
}
