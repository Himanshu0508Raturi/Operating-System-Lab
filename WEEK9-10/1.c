
#include <stdio.h>
#include <stdbool.h>

typedef struct file
{
    char name;
    int start_block;
    int no_of_blocks;
} file;

int main()
{
    bool blocks[1000] = {true};
    int n;
    printf("Enter the number of files:");
    scanf("%d", &n);
    file files[n];
    for (int i = 0; i < n; i++)
    {
        getchar();
        printf("Enter the name of file %d:", i + 1);
        scanf("%c", &files[i].name);
        printf("Enter the starting block of file %d:", i + 1);
        scanf("%d", &files[i].start_block);
        printf("Enter the no of blocks of file %d:", i + 1);
        scanf("%d", &files[i].no_of_blocks);
        int st = files[i].start_block;
        for (int j = 0; j < files[i].no_of_blocks; j++)
        {
            blocks[st++] = false;
        }
    }
    char ch;
    getchar();
    printf("Enter the name of file to be searched:");
    scanf("%c", &ch);
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (files[i].name == ch)
        {
            printf("File Name      : %c\n", files[i].name);
            printf("Start Block    : %d\n", files[i].start_block);
            printf("No. of Blocks  : %d\n", files[i].no_of_blocks);
            printf("Blocks Occupied: ");
            int st = files[i].start_block;
            for (int j = 0; j < files[i].no_of_blocks; j++)
            {
                printf("%d ", st++);
            }
            found = true;
            break;
        }
    }
    if (!found)
        printf("File not found");
}