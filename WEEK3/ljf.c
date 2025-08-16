#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int is_completed;
} process;

int main()
{
    int n;
    float swt = 0, stat = 0;
    float cu = 0, throughput = 0;
    float awt = 0, atat = 0;
    int sbt = 0;

    printf("Number Of Process: ");
    scanf("%d", &n);
    process p[n];

    printf("\nBurst time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1; // Assign process ID
        p[i].is_completed = 0;
    }

    printf("\nArrival time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].arr_time);
    }

    int completed = 0, curr_time = 0;
    float max_completion_time = 0;

    while (completed != n)
    {
        int idx = -1;
        int max_bt = -1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arr_time <= curr_time && p[i].is_completed == 0)
            {
                if (p[i].burst_time > max_bt)
                {
                    max_bt = p[i].burst_time;
                    idx = i;
                }
                if (p[i].burst_time == max_bt) 
                {
                    if (p[i].arr_time < p[idx].arr_time)
                    {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            p[idx].start_time = curr_time;
            p[idx].complete_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turn_ard_time = p[idx].complete_time - p[idx].arr_time;
            p[idx].wait_time = p[idx].turn_ard_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arr_time;

            swt += p[idx].wait_time;
            stat += p[idx].turn_ard_time;
            sbt += p[idx].burst_time;

            if (p[idx].complete_time > max_completion_time)
                max_completion_time = p[idx].complete_time;

            p[idx].is_completed = 1;
            completed++;
            curr_time = p[idx].complete_time;
        }
        else
        {
            curr_time++;
        }
    }

    awt = swt / n;
    atat = stat / n;
    cu = ((float)sbt / max_completion_time) * 100; // Cast to float for correct division
    throughput = (float)n / max_completion_time;

    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arr_time, p[i].burst_time,
               p[i].start_time, p[i].complete_time,
               p[i].turn_ard_time, p[i].wait_time, p[i].response_time);
    }

    printf("\nTotal Turn Around Time : %f\nAverage Turn Around Time : %f\n", stat, atat);
    printf("Total Waiting Time : %f\nAverage Waiting Time : %f\n", swt, awt);
    printf("CPU Utilization : %f%%\n", cu);
    printf("Throughput : %f processes/unit time\n", throughput);

    return 0;
}
