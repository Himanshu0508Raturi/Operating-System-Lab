#include <stdio.h>

int main(void)
{
    int n, head = 50, disk_size = 200;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[100];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    // Step 1: Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }

    // Step 2: Split: left (< head) vs right (>= head)
    int left[100], right[100], lcnt = 0, rcnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (requests[i] < head)
            left[lcnt++] = requests[i];
        else
            right[rcnt++] = requests[i];
    }

    int total_seek = 0;
    int pos = head;

    // Step 3: C-SCAN RIGHT FIRST
    // Right requests (head -> 199)
    for (int i = 0; i < rcnt; i++)
    {
        total_seek += abs(right[i] - pos);
        pos = right[i];
    }

    // To disk end
    total_seek += abs(199 - pos);
    pos = 199;

    // Jump to start (0)
    total_seek += 199; // 199 -> 0
    pos = 0;

    // Left requests (0 -> leftmost)
    for (int i = 0; i < lcnt; i++)
    {
        total_seek += abs(left[i] - pos);
        pos = left[i];
    }

    printf("Total seek movement: %d\n", total_seek);
    return 0;
}
