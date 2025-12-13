#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char name;
    int blocks[100];
    int count;
} File;

int main(void)
{
    bool disk[1000] = {true};  // true = free
    
    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);
    
    File files[n];
    
    // Read files and allocate blocks
    for (int f = 0; f < n; f++)
    {
        printf("\nFile %d:\n", f+1);
        scanf(" %c", &files[f].name);
        
        printf("Number of blocks: ");
        scanf("%d", &files[f].count);
        
        printf("Enter %d block numbers: ", files[f].count);
        for (int i = 0; i < files[f].count; i++)
        {
            scanf("%d", &files[f].blocks[i]);
            disk[files[f].blocks[i]] = false;  // mark occupied
        }
    }
    
    // Search file
    char find;
    printf("\nEnter file name to find: ");
    scanf(" %c", &find);
    
    for (int f = 0; f < n; f++)
    {
        if (files[f].name == find)
        {
            printf("\nFile '%c':\n", find);
            printf("Blocks: ");
            for (int i = 0; i < files[f].count; i++)
            {
                printf("%d", files[f].blocks[i]);
                if (i < files[f].count - 1)
                    printf(" -> ");
            }
            printf(" -> NULL\n");
            return 0;
        }
    }
    
    printf("File not found\n");
    return 0;
}
