// Also known as srtf(shortest remaining time first).
#include <stdio.h>
#include <limits.h>

typedef struct process
{
    int pid;
    int arr_time;
    int burst_time;
    int rem_time; // Remaining time for preemptive scheduling
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
    printf("Number of Processes: ");
    scanf("%d", &n);

    process p[n];
    int total_bt = 0;

    printf("\nBurst Time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].rem_time = p[i].burst_time; // initially remaining = burst
        p[i].is_completed = 0;
    }

    printf("\nArrival Time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].arr_time);
    }

    int completed = 0, curr_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;
    int gantt[100], g_index = 0;
    while (completed != n)
    {
        int min_ind = -1;
        int min_rt = INT_MAX;

        // Find process with smallest remaining time among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (p[i].arr_time <= curr_time && p[i].is_completed == 0)
            {
                if (p[i].rem_time < min_rt)
                {
                    min_rt = p[i].rem_time;
                    min_ind = i;
                }
                else if (p[i].rem_time == min_rt)
                {
                    if (p[i].arr_time < p[min_ind].arr_time)
                        min_ind = i;
                }
            }
        }

        if (min_ind != -1)
        {
            if (p[min_ind].rem_time == p[min_ind].burst_time)
                p[min_ind].start_time = curr_time; // First time the process is running

            gantt[g_index++] = p[min_ind].pid;
            p[min_ind].rem_time--;
            curr_time++;

            if (p[min_ind].rem_time == 0) // Process finished
            {
                p[min_ind].complete_time = curr_time;
                p[min_ind].turn_ard_time = p[min_ind].complete_time - p[min_ind].arr_time;
                p[min_ind].wait_time = p[min_ind].turn_ard_time - p[min_ind].burst_time;
                p[min_ind].response_time = p[min_ind].start_time - p[min_ind].arr_time;

                total_wt += p[min_ind].wait_time;
                total_tat += p[min_ind].turn_ard_time;
                total_rt += p[min_ind].response_time;

                p[min_ind].is_completed = 1;
                completed++;
            }
        }
        else
        {
            curr_time++; // CPU idle if no process has arrived
        }
    }

    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arr_time, p[i].burst_time,
               p[i].start_time, p[i].complete_time,
               p[i].turn_ard_time, p[i].wait_time, p[i].response_time);
    }
    printf("\nGantt Chart : ");
    printf("P%d ", gantt[0]);
    for (int i = 1; i < g_index; i++)
    {
        if (gantt[i] != gantt[i - 1])
            printf("P%d ", gantt[i]);
    }
    printf("\nAverage Turn Around Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Response Time: %.2f\n", total_rt / n);

    return 0;
}
