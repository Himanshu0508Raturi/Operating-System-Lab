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
        p[i].pid = i + 1;
        p[i].is_completed = 0;
    }

    printf("\nArrival time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].arr_time);
    }

    int completed = 0, curr_time = 0;
    float max_completion_time = 0;
    int gantt[n];
    int g_ind = 0;
    while (completed != n)
    {
        int min_ind = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arr_time <= curr_time && p[i].is_completed == 0)
            {
                if (p[i].burst_time < min_bt)
                {
                    min_bt = p[i].burst_time;
                    min_ind = i;
                }
                else if (p[i].burst_time == min_bt)
                {
                    if (p[i].arr_time < p[min_ind].arr_time)
                        min_ind = i;
                }
            }
        }

        if (min_ind != -1)
        {
            p[min_ind].start_time = curr_time;
            p[min_ind].complete_time = p[min_ind].start_time + p[min_ind].burst_time;
            p[min_ind].turn_ard_time = p[min_ind].complete_time - p[min_ind].arr_time;
            p[min_ind].wait_time = p[min_ind].turn_ard_time - p[min_ind].burst_time;
            p[min_ind].response_time = p[min_ind].start_time - p[min_ind].arr_time;

            swt += p[min_ind].wait_time;
            stat += p[min_ind].turn_ard_time;
            sbt += p[min_ind].burst_time;

            if (p[min_ind].complete_time > max_completion_time)
                max_completion_time = p[min_ind].complete_time;

            gantt[g_ind++] = p[min_ind].pid;
            p[min_ind].is_completed = 1;
            completed++;
            curr_time = p[min_ind].complete_time;
        }
        else
        {
            curr_time++; // CPU idle
        }
    }

    awt = swt / n;
    atat = stat / n;
    cu = ((float)sbt / max_completion_time) * 100;
    throughput = (float)n / max_completion_time;

    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arr_time, p[i].burst_time,
               p[i].start_time, p[i].complete_time,
               p[i].turn_ard_time, p[i].wait_time, p[i].response_time);
    }
    printf("\nGantt Chart : ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", gantt[i]); // if you want P0, P1... instead of P1, P2...
    }
    printf("\nTotal Turn Around Time : %.2f\nAverage Turn Around Time : %.2f\n", stat, atat);
    printf("Total Waiting Time : %.2f\nAverage Waiting Time : %.2f\n", swt, awt);
    printf("CPU Utilization : %.2f%%\n", cu);
    printf("Throughput : %.2f processes/unit time\n", throughput);

    return 0;
}
