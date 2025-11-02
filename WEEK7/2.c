#include <stdio.h>

int isPresent(int frames[], int n, int page)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

int findLRU(int time[], int n)
{
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
    {
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void display(int frames[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int main()
{
    int n, m;
    printf("Enter number of frames: ");
    scanf("%d", &n);

    printf("Enter number of page requests: ");
    scanf("%d", &m);

    int pages[m];
    printf("Enter the page reference string: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &pages[i]);

    int frames[n], time[n];
    int counter = 0, pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        int page = pages[i];
        printf("Request for page %d -> ", page);

        if (isPresent(frames, n, page))
        {
            for (int j = 0; j < n; j++)
            {
                if (frames[j] == page)
                    time[j] = ++counter;
            }
            printf("Page Hit Frames: ");
        }
        else
        {
            pageFaults++;

            int emptyPos = -1;
            for (int j = 0; j < n; j++)
            {
                if (frames[j] == -1)
                {
                    emptyPos = j;
                    break;
                }
            }

            if (emptyPos != -1)
            {
                frames[emptyPos] = page;
                time[emptyPos] = ++counter;
            }
            else
            {
                int pos = findLRU(time, n);
                frames[pos] = page;
                time[pos] = ++counter;
            }

            printf("Page Fault Frames: ");
        }

        display(frames, n);
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", m - pageFaults);

    return 0;
}
