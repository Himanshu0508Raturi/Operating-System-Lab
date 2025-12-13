#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, head = 50, disk_size = 200;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    
    int requests[100];
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);
    
    // Step 1: Sort requests (ascending order)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (requests[j] > requests[j + 1])
            {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
    
    // Step 2: Find first request >= head
    int right_start = 0;
    while (right_start < n && requests[right_start] < head)
        right_start++;
    
    int total_seek = 0;
    int pos = head;
    
    // Step 3: SCAN RIGHT (head -> end)
    for (int i = right_start; i < n; i++)
    {
        total_seek += abs(requests[i] - pos);
        pos = requests[i];
    }
    
    // Step 4: Go to disk end
    total_seek += abs((disk_size - 1) - pos);
    pos = disk_size - 1;
    
    // Step 5: SCAN LEFT (end -> head)
    for (int i = right_start - 1; i >= 0; i--)
    {
        total_seek += abs(requests[i] - pos);
        pos = requests[i];
    }
    
    printf("Total seek movement: %d\n", total_seek);
    return 0;
}
/*
1. Sort requests: small → large
2. RIGHT: head → rightmost request → disk_end
3. LEFT:  disk_end → leftmost request
*/