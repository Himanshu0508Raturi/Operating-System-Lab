// index Allocation
#include <stdio.h>
#include <stdbool.h>

struct file
{
    char name;
    int start_block;
    int no_of_blocks;
    int flag;
};
struct block
{
    int current;
    int next;
};
int main()
{
    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    struct file files[n];
    struct block sector[1000];
    for (int i = 0; i < 1000; i++)
    {
        if (i % 2 == 0)
        {
            sector[i].current = 100;
            sector[i].next = 100;
        }
        else
        {
            sector[i].current = -1;
            sector[i].next = -1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        getchar();
        printf("\nEnter file %d name: ", i + 1);
        scanf("%c", &files[i].name);
        printf("Enter starting block of file %c: ", files[i].name);
        scanf("%d", &files[i].start_block);
        printf("Enter number of blocks for file %c: ", files[i].name);
        scanf("%d", &files[i].no_of_blocks);
    }
    int p = 0;
    for (int i = 0; i < n; i++)
    {
        int req = files[i].no_of_blocks;
        int start_block = files[i].start_block;
        int index = -1;

        if (sector[start_block].current == -1)
        {
            files[i].flag = 1;
            for (int j = start_block; j < 1000 && req > 0; j++)
            {
                if (sector[j].current == -1)
                {
                    sector[j].current = p++; // assign a block number
                    req--;
                    if (index == -1)
                    {
                        files[i].start_block = j;
                    }
                    else
                    {
                        sector[index].next = j;
                    }
                    index = j;
                }
            }
        }
        else
        {
            printf("enter correct starting block\n");
            files[i].flag = 0;
        }
    }
    printf("\n\nFile Allocation Table:\n");
    printf("File\tStart\tBlocks Linked\n");
    printf("----------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        if (!files[i].flag)
            continue;
        printf("%c\t%d\t", files[i].name, files[i].start_block);
        int j = files[i].start_block;
        while (j != -1)
        {
            printf("%d ", j);
            j = sector[j].next;
        }
        printf("\n");
    }

    return 0;
}