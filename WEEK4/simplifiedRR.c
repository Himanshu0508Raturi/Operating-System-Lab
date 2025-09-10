#include <stdio.h>

typedef struct
{
    int pid;      // Process ID
    int at;       // Arrival Time
    int bt;       // Burst Time
    int rem_time; // rem_time Burst Time
    int st;       // Start Time (first execution)
    int ct;       // Completion Time
    int tat;      // Turnaround Time
    int wt;       // Waiting Time
    int rt;       // Response Time
    int finished; // Flag if process is finished
} Process;

int main()
{
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter Arrival Time of P%d: ", i);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time of P%d: ", i);
        scanf("%d", &p[i].bt);
        p[i].pid = i;
        p[i].rem_time = p[i].bt;
        p[i].finished = 0;
        p[i].st = -1; // not started yet
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    float totalWT = 0, totalTAT = 0, totalRT = 0;

    // Ready queue implemented as simple array
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};

    // First process into queue
    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n)
    {
        int idx = queue[front++]; // dequeue

        // If first time execution, set start time
        if (p[idx].st == -1)
        {
            // p[idx].st = (time < p[idx].at) ? p[idx].at : time;
            if(time < p[idx].at)
            {
                p[idx].st = p[idx].at;
            }else
            {
                p[idx].st = time;   
            }
            time = p[idx].st;
        }

        // Run for min(time quantum, rem_time time)
        // int exec = (p[idx].rem_time > tq) ? tq : p[idx].rem_time;
        int exec;
        if(p[idx].rem_time > tq)
        {
            exec = tq;
        }else
        {
            exec = p[idx].rem_time;
        }
        p[idx].rem_time -= exec;
        time += exec;

        // If finished
        if (p[idx].rem_time == 0)
        {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].st - p[idx].at;

            totalWT += p[idx].wt;
            totalTAT += p[idx].tat;
            totalRT += p[idx].rt;
            p[idx].finished = 1;
            completed++;
        }

        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[i].at <= time)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If current process is not finished, push it back to queue
        if (!p[idx].finished)
        {
            queue[rear++] = idx;
        }

        // If queue empty but processes left → add next process
        if (front == rear && completed < n)
        {
            for (int i = 0; i < n; i++)
            {
                if (!p[i].finished)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    // Print results
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Response Time = %.2f\n", totalRT / n);

    return 0;
}
