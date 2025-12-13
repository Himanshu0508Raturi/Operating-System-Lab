#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int pid, at, bt, bt_remaining, start_time, ct, tat, wt, rt;
} Process;

int main()
{
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[100];
    for (int i = 0; i < n; i++)
    {
        printf("Process %d - Arrival: ", i);
        scanf("%d", &p[i].at);
        p[i].pid = i;
        printf("Burst: ");
        scanf("%d", &p[i].bt);
        p[i].bt_remaining = p[i].bt;
    }
    printf("Time quantum: ");
    scanf("%d", &tq);
    int current_time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    queue[rear++] = 0; // Start with first process

    while (completed < n)
    {
        int idx = queue[front++];

        // Set start time for first execution
        if (p[idx].bt_remaining == p[idx].bt)
            p[idx].start_time = (current_time < p[idx].at) ? p[idx].at : current_time;

        // Execute for time quantum or remaining time
        int exec_time = (p[idx].bt_remaining > tq) ? tq : p[idx].bt_remaining;
        current_time += exec_time;
        p[idx].bt_remaining -= exec_time;

        // If completed
        if (p[idx].bt_remaining == 0)
        {
            completed++;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].rt = p[idx].start_time - p[idx].at;
        }
        else
        {
            // Push back to queue
            queue[rear++] = idx;
        }

        // Add new arrivals to queue
        for (int i = 0; i < n; i++)
        {
            if (p[i].bt_remaining > 0 && p[i].at <= current_time && i != idx)
                if (front > rear || queue[rear - 1] != i) // Avoid duplicate
                    queue[rear++] = i;
        }
    }
    // Calculate metrics
    float avg_tat = 0, avg_wt = 0, avg_rt = 0, throughput = 0;
    int max_ct = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        avg_rt += p[i].rt;
        if (p[i].ct > max_ct)
            max_ct = p[i].ct;
        printf("P%d: AT=%d BT=%d ST=%d CT=%d TAT=%d WT=%d RT=%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].start_time, p[i].ct,
               p[i].tat, p[i].wt, p[i].rt);
    }

    avg_tat /= n;
    avg_wt /= n;
    avg_rt /= n;
    throughput = n / (float)max_ct;
    printf("\nAvg TAT=%.2f Avg WT=%.2f Avg RT=%.2f\n", avg_tat, avg_wt, avg_rt);
    printf("Throughput=%.2f CPU Util=%.1f%%\n", throughput,
           (max_ct - p[0].at) / (float)max_ct * 100);
    return 0;
}
