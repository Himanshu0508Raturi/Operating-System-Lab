// #include <stdio.h>
// struct Process
// {
//     int A, B, C; // resources
// };

// int main()
// {
//     int n, A, B, C;
//     printf("Enter the Number of Process - ");
//     scanf("%d", &n);

//     struct Process allocated[n];
//     struct Process require[n];
//     struct Process Need[n];
//     int isExecute[n];
//     int ans[n];

//     for (int i = 0; i < n; i++)
//         isExecute[i] = 0;
//     int al_a = 0;
//     int al_b = 0;
//     int al_c = 0;
//     for (int i = 0; i < n; i++)
//     {
//         printf("Enter the Allocated and Required Resources of P%d - ", i);
//         scanf("%d%d%d", &allocated[i].A, &allocated[i].B, &allocated[i].C);
//         scanf("%d%d%d", &require[i].A, &require[i].B, &require[i].C);

//         al_a += allocated[i].A;
//         al_b += allocated[i].B;
//         al_c += allocated[i].C;

//         Need[i].A = require[i].A - allocated[i].A;
//         Need[i].B = require[i].B - allocated[i].B;
//         Need[i].C = require[i].C - allocated[i].C;
//     }

//     printf("Enter the Aavilable Resources = ");
//     scanf("%d%d%d", &A, &B, &C);
//     A -= al_a;
//     B -= al_b;
//     C -= al_c;

//     int idx = 0;
//     for (int i = 0; i < n; i++)
//     {
//         if (isExecute[i] == 0)
//         {
//             for (int j = 0; j < n; j++)
//             {
//                 if (isExecute[j] == 0)
//                 {
//                     if (Need[j].A <= A && Need[j].B <= B && Need[j].C <= C)
//                     {
//                         A += allocated[j].A;
//                         B += allocated[j].B;
//                         C += allocated[j].C;

//                         ans[idx] = j;
//                         idx++;
//                         isExecute[j] = 1;
//                     }
//                 }
//             }
//         }
//     }

//     for (int i = 0; i < n; i++)
//     {
//         if (isExecute[i] == 0)
//         {
//             printf("No Safe Sequence is Possible");
//             return 0;
//         }
//     }

//     printf("The Safe Sequence is - ");
//     for (int i = 0; i < n - 1; i++)
//     {
//         printf("P%d ->", ans[i]);
//     }
//     printf("P%d", ans[n - 1]);
//     return 0;
// }
#include <stdio.h>

// Structure to represent resources (3 types: a, b, c)
typedef struct Resource
{
    int a, b, c;
} Resource;

int main()
{
    int p, r;

    printf("Enter number of processes : ");
    scanf("%d", &p);

    printf("Enter number of resources : ");
    scanf("%d", &r);

    if (r != 3)
    {
        printf("This program only supports 3 resources (a, b, c)\n");
        return 0;
    }

    Resource max_need[p], already_allocated[p], remaining_need[p];
    Resource total, avail;

    // Input maximum requirement matrix
    printf("Enter maximum requirement : \n");
    for (int i = 0; i < p; i++)
    {
        scanf("%d %d %d", &max_need[i].a, &max_need[i].b, &max_need[i].c);
    }

    // Input allocated matrix
    printf("Enter allocated matrix : \n");
    for (int i = 0; i < p; i++)
    {
        scanf("%d %d %d", &already_allocated[i].a, &already_allocated[i].b, &already_allocated[i].c);
    }

    // Input total resources
    printf("Resource Vector : ");
    scanf("%d %d %d", &total.a, &total.b, &total.c);

    // Calculate Available = Total - Sum(Alloc)
    avail.a = total.a;
    avail.b = total.b;
    avail.c = total.c;
    for (int i = 0; i < p; i++)
    {
        avail.a -= already_allocated[i].a;
        avail.b -= already_allocated[i].b;
        avail.c -= already_allocated[i].c;
    }

    // Calculate Need = Max - Alloc
    for (int i = 0; i < p; i++)
    {
        remaining_need[i].a = max_need[i].a - already_allocated[i].a;
        remaining_need[i].b = max_need[i].b - already_allocated[i].b;
        remaining_need[i].c = max_need[i].c - already_allocated[i].c;
    }

    // Banker's Algorithm
    int finish[p];
    int safeSeq[p];
    for (int i = 0; i < p; i++)
        finish[i] = 0;
    int count = 0;
    int deadlock[p];
    for(int i = 0 ; i < p ; i++)
    {
        deadlock[i] = 0;
    }

    while (count < p)
    {
        int found = 0;
        for (int i = 0; i < p; i++)
        {
            if (!finish[i])
            {
                // Check if need <= avail
                if (remaining_need[i].a <= avail.a &&
                    remaining_need[i].b <= avail.b &&
                    remaining_need[i].c <= avail.c)
                {

                    // Pretend to allocate
                    avail.a += already_allocated[i].a;
                    avail.b += already_allocated[i].b;
                    avail.c += already_allocated[i].c;

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                    deadlock[i] = 1;
                }
            }
        }
        if (!found)
            break; // no process can proceed
    }

    // Output
    if (count < p)
    {
        printf("System is in UNSAFE state. No safe sequence exists.\n");
        printf("Deadlock occur due to process: ");
        for(int i = 0 ; i < p ; i++)
        {
            if(!deadlock[i])
            {
                printf("P%D", i);
            }
        }
    }
    else
    {
        printf("Request can be fulfilled\n");
        printf("Safe Sequence : ");
        for (int i = 0; i < p; i++)
        {
            printf("P%d", safeSeq[i]);
            if (i != p - 1)
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}