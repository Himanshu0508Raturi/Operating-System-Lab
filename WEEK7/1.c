#include <stdio.h>

void enqueue(int q[], int *front, int *rear, int v)
{
    if (*front == -1) // first element
        *front = 0;
    q[++(*rear)] = v; // insert at rear then move rear
}

int dequeue(int q[], int *front, int *rear)
{
    int v;
    if (*front == -1) // empty
        return -1;
    v = q[*front]; // remove from front
    (*front)++;
    if (*front > *rear) // queue becomes empty
    {
        *front = -1;
        *rear = -1;
    }
    return v;
}

int isPresent(int q[], int front, int rear, int page)
{
    if (front == -1)
        return 0;
    for (int i = front; i <= rear; i++)
        if (q[i] == page)
            return 1;
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
        printf("%d ", q[i]);
    printf("\n");
}

int main(void)
{
    int frames, m;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of page requests: ");
    scanf("%d", &m);

    int pages[m];
    for (int i = 0; i < m; i++)
        scanf("%d", &pages[i]);

    int q[20];
    int front = -1, rear = -1;
    int faults = 0;

    for (int i = 0; i < m; i++)
    {
        int page = pages[i];
        printf("Request for page %d -> ", page);

        if (!isPresent(q, front, rear, page)) // MISS
        {
            faults++;

            int size = (front == -1) ? 0 : (rear - front + 1);
            if (size == frames) // full: remove oldest
                dequeue(q, &front, &rear);

            enqueue(q, &front, &rear, page); // insert new page

            printf("Page Fault Frames: ");
        }
        else // HIT
        {
            printf("Page Hit Frames: ");
        }

        display(q, front, rear);
    }

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits = %d\n", m - faults);

    return 0;
}
