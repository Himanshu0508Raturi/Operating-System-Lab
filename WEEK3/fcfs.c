#include <stdio.h>
#include <stdlib.h>
typedef struct process
{
    int pid;
    int arr_time;
    int burst_time;
    int start_time;
    int complete_time;
    int turn_ard_time;
    int wait_time;
    int response_time;
} process;
int comapre(const void *p1, const void *p2)
{
    int a = ((struct process *)p1)->arr_time;
    int b = ((struct process *)p2)->arr_time;
    if (a < b)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
int main()
{
    int n;
    float swt = 0, stat = 0;
    float cu = 0, throughput = 0;
    float awt = 0, atat = 0;
    int sbt = 0;

    printf("Number Of Process:");
    scanf("%d", &n);
    process p[n];
    printf("\nBurst time: ");
    for (int i = 0; i < n; i++)
    {
        int bt;
        scanf("%d", &p[i].burst_time);
    }
    printf("\nArrival time: ");
    for (int i = 0; i < n; i++)
    {
        int bt;
        scanf("%d", &p[i].arr_time);
    }
    qsort((void *)p, n, sizeof(struct process), comapre);
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            p[i].complete_time = p[i].arr_time + p[i].burst_time;
        }
        else if (p[i - 1].complete_time <= p[i].arr_time)
        {
            p[i].complete_time = p[i].arr_time + p[i].burst_time;
        }
        else
        {
            p[i].complete_time = p[i - 1].complete_time - p[i].burst_time;
        }
        p[i].turn_ard_time = p[i].complete_time - p[i].arr_time;
        p[i].wait_time = p[i].turn_ard_time - p[i].burst_time;

        sbt += p[i].burst_time;
        swt += p[i].wait_time;
        stat += p[i].turn_ard_time;
        p[i].response_time = p[i].wait_time;
    }
    awt = swt / n;
    atat = stat / n;
    float max;
    for (int i = 0; i < n; i++)
    {
        p[i].start_time = p[i].response_time + p[i].arr_time;
        max = 0;
        if (p[i].complete_time > max)
        {
            max = p[i].complete_time;
        }
    }

    cu = (sbt / max) * 100;
    throughput = n / max;
    printf("\nPID\tAT\tBT\tST\tCT\tTAT\t\tWT\t\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P % d\t % d\t % d\t % d\t % d\t % f\t % f\t % d\n", p[i].pid, p[i].arr_time, p[i].burst_time, p[i].start_time, p[i].complete_time, p[i].turn_ard_time, p[i].wait_time, p[i].response_time);
    }
    printf("\nSum of Turn Around Time : % f\nAverage of Turn Around Time : % f\n", stat, atat);
    printf("Sum of Waiting Time : % f\nAverage of Waiting Time : % f\nCPU utilization is : % f\nThroughput : % f", swt, awt, cu, throughput);
    return 0;
}
