// fcfs non-prremptive algo
#include <stdio.h>
#include <stdlib.h>
typedef struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int complete_time;
    int start_time;
    int response_time;
    int turn_around_time;
    int waiting_time;
} process;
int compare(const void *p1, const void *p2)
{
    int a = ((process *)p1)->arrival_time;
    int b = ((process *)p2)->arrival_time;
    if (a < b)
    {
        return -1;
    }
    else if (a > b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    float swt = 0, stat = 0;
    int sbt = 0;
    float awt = 0, atat = 0;
    int n;
    float cu = 0, throughput = 0;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    process p[n];
    printf("Burst Time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
    }
    printf("Arrival Time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].arrival_time);
    }
    qsort(p, n, sizeof(process), compare);

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            p[i].start_time = p[i].arrival_time;
        }
        else
        {
            if (p[i - 1].complete_time > p[i].arrival_time)
            {
                p[i].start_time = p[i - 1].complete_time;
            }
            else
            {
                p[i].start_time = p[i].arrival_time;
            }
        }
        p[i].complete_time = p[i].burst_time + p[i].start_time;
        p[i].turn_around_time = p[i].complete_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        swt += p[i].waiting_time;
        sbt += p[i].burst_time;
        stat += p[i].turn_around_time;
    }
    awt = swt / n;
    atat = stat / n;

    float max_ct = p[0].complete_time;
    for (int i = 1; i < n; i++)
    {
        if (p[i].complete_time > max_ct)
        {
            max_ct = p[i].complete_time;
        }
    }
    cu = ((float)sbt / max_ct) * 100;
    throughput = n / max_ct;
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].start_time, p[i].complete_time,
               p[i].turn_around_time, p[i].waiting_time, p[i].response_time);
    }
    printf("\nGantt Chart : ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", p[i].pid - 1); // if you want P0, P1... instead of P1, P2...
    }
    printf("\n");

    printf("\nSum of Turn Around Time : %.2f\nAverage Turn Around Time : %.2f\n", stat, atat);
    printf("Sum of Waiting Time : %.2f\nAverage Waiting Time : %.2f\n", swt, awt);
    printf("CPU Utilization : %.2f%%\nThroughput : %.2f\n", cu, throughput);

    return 0;
}