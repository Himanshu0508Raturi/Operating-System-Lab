#include <stdio.h>
#include <limits.h>

typedef struct process
{
    int pid;
    int arr_time;
    int burst_time;
    int rem_time; // Remaining time for preemption
    int priority;
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
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    process p[n];
    printf("\nBurst time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].burst_time);
        p[i].pid = i;
        p[i].rem_time = p[i].burst_time;
        p[i].is_completed = 0;
    }

    printf("\nArrival time: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].arr_time);
    }

    printf("\nPriority (higher number = higher priority): ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i].priority);
    }

    int completed = 0, curr_time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    // For Gantt Chart
    int gantt[1000], g_index = 0;

    while (completed != n)
    {
        int idx = -1;
        int highest_priority = INT_MIN;

        // Find highest priority among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (p[i].arr_time <= curr_time && p[i].is_completed == 0)
            {
                if (p[i].priority > highest_priority)
                {
                    highest_priority = p[i].priority;
                    idx = i;
                }
                else if (p[i].priority == highest_priority)
                {
                    if (p[i].arr_time < p[idx].arr_time)
                        idx = i;
                }
            }
        }

        if (idx != -1)
        {
            if (p[idx].rem_time == p[idx].burst_time)
                p[idx].start_time = curr_time; // first execution

            gantt[g_index++] = p[idx].pid;

            p[idx].rem_time--;
            curr_time++;

            if (p[idx].rem_time == 0)
            {
                p[idx].complete_time = curr_time;
                p[idx].turn_ard_time = p[idx].complete_time - p[idx].arr_time;
                p[idx].wait_time = p[idx].turn_ard_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arr_time;

                total_wt += p[idx].wait_time;
                total_tat += p[idx].turn_ard_time;
                total_rt += p[idx].response_time;

                p[idx].is_completed = 1;
                completed++;
            }
        }
        else
        {
            curr_time++; // CPU idle
        }
    }

    printf("\nPID\tAT\tBT\tPRI\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arr_time, p[i].burst_time, p[i].priority,
               p[i].start_time, p[i].complete_time,
               p[i].turn_ard_time, p[i].wait_time, p[i].response_time);
    }

    // Print compressed Gantt Chart
    printf("\nGantt Chart : ");
    printf("P%d ", gantt[0]);
    for (int i = 1; i < g_index; i++)
    {
        if (gantt[i] != gantt[i - 1])
            printf("P%d ", gantt[i]);
    }

    printf("\n\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    
    return 0;
}
