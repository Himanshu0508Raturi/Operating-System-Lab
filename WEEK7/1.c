#include <stdio.h>

void enqueue(int q[], int *front, int *rear, int v, int n)
{
    if (*rear - *front + 1 == n)
    {
        printf("Queue is full\n");
        return;
    }
    else
    {
        if (*front == -1)
        {
            *front = 0;
        }
        q[++(*rear)] = v;
    }
}

int dequeue(int q[], int *front, int *rear)
{
    int v;
    if (*front == -1)
    {
        printf("Queue is empty\n");
        return -1;
    }
    else
    {
        v = q[*front];
        (*front)++;
        if (*front > *rear)
        {
            *front = -1;
            *rear = -1;
        }
    }
    return v;
}

int isPresent(int q[], int front, int rear, int page)
{
    if (front == -1)
        return 0;
    for (int i = front; i <= rear; i++)
    {
        if (q[i] == page)
            return 1;
    }
    return 0;
}

void display(int q[], int front, int rear)
{
    if (front == -1)
    {
        printf("Queue is empty\n");
        return;
    }
    for (int i = front; i <= rear; i++)
    {
        printf("%d ", q[i]);
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
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &pages[i]);
    }

    int q[20];
    int front = -1, rear = -1;
    int pageFaults = 0;
    for (int i = 0; i < m; i++)
    {
        int page = pages[i];
        printf("Request for page %d -> ", page);

        if (!isPresent(q, front, rear, page))
        {
            pageFaults++;

            if (front == -1 || rear - front + 1 < n)
                enqueue(q, &front, &rear, page, n);
            else
            {
                dequeue(q, &front, &rear);
                enqueue(q, &front, &rear, page, n);
            }

            printf("Page Fault Frames: ");
        }
        else
        {
            printf("Page Hit Frames: ");
        }
        display(q, front, rear);
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    printf("Total Page Hits = %d\n", m - pageFaults);

    return 0;
}
