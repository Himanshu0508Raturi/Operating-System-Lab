/* cscan.c
   C-SCAN (circular-scan) disk scheduling
   Disk tracks assumed 0..199
   Compile: gcc cscan.c -o cscan
   Run: ./cscan
*/

#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int x = *(int *)a, y = *(int *)b;
    return (x > y) - (x < y);
}

int main()
{
    const int START = 0, END = 199;
    int n;
    printf("Enter number of disk requests : ");
    if (scanf("%d", &n) != 1 || n < 0)
        return 0;

    int *req = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &req[i]);

    int head;
    printf("Enter initial head position : ");
    if (scanf("%d", &head) != 1)
        head = 0;

    char dir[16];
    printf("Enter initial direction (left/right) : ");
    scanf("%15s", dir);

    qsort(req, n, sizeof(int), cmp);

    // Separate requests
    int leftCount = 0, rightCount = 0;
    for (int i = 0; i < n; ++i)
    {
        if (req[i] < head)
            leftCount++;
        else
            rightCount++;
    }

    int *left = (int *)malloc(sizeof(int) * leftCount);
    int *right = (int *)malloc(sizeof(int) * rightCount);
    int li = 0, ri = 0;
    for (int i = 0; i < n; ++i)
    {
        if (req[i] < head)
            left[li++] = req[i];
        else
            right[ri++] = req[i];
    }

    long total_seek = 0;
    int current = head;

    if (dir[0] == 'l' || dir[0] == 'L')
    {
        // Move left: service left in descending order
        for (int i = leftCount - 1; i >= 0; --i)
        {
            total_seek += abs(current - left[i]);
            current = left[i];
        }
        // go to start (0)
        if (current != START)
        {
            total_seek += abs(current - START);
            current = START;
        }
        // jump from start to end (this movement is typically counted as seek)
        total_seek += abs(END - START);
        current = END;
        // service right (those > head) in descending order from end -> ... -> head side
        for (int i = rightCount - 1; i >= 0; --i)
        {
            total_seek += abs(current - right[i]);
            current = right[i];
        }
    }
    else
    {
        // Move right: service right in ascending order
        for (int i = 0; i < rightCount; ++i)
        {
            total_seek += abs(current - right[i]);
            current = right[i];
        }
        // go to end (199)
        if (current != END)
        {
            total_seek += abs(current - END);
            current = END;
        }
        // jump from end to start (counted)
        total_seek += abs(END - START);
        current = START;
        // service left in ascending order
        for (int i = 0; i < leftCount; ++i)
        {
            total_seek += abs(current - left[i]);
            current = left[i];
        }
    }

    printf("Total seek movement : %ld\n", total_seek);

    free(req);
    free(left);
    free(right);
    return 0;
}
