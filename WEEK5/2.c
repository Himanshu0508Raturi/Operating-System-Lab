#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, m;
    printf("Processes, Resources: ");
    scanf("%d %d", &n, &m);

    int alloc[10][10], req[10][10];

    printf("Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    // Build Wait-For Graph: Pi -> Pj if Pi requests resource held by Pj
    bool graph[10][10] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            for (int r = 0; r < m; r++)
            {
                if (req[i][r] > 0 && alloc[j][r] > 0)
                {
                    graph[i][j] = 1;
                    break;
                }
            }
        }
    }

    // Simple DFS cycle detection
    bool visited[10] = {0}, stack[10] = {0};
    bool deadlocked[10] = {0};

    for (int start = 0; start < n; start++)
    {
        if (!visited[start])
        {
            if (hasCycle(graph, start, visited, stack, deadlocked, n))
                deadlocked[start] = 1;
        }
    }

    printf("\nDeadlocked: ");
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (deadlocked[i])
        {
            printf("P%d ", i);
            count++;
        }
    }
    printf("\nTotal: %d processes\n", count);
    return 0;
}

bool hasCycle(bool g[][10], int u, bool vis[], bool st[], bool dead[], int n)
{
    vis[u] = st[u] = 1;

    for (int v = 0; v < n; v++)
    {
        if (g[u][v])
        {
            if (!vis[v])
            {
                if (hasCycle(g, v, vis, st, dead, n))
                    return dead[u] = 1;
            }
            else if (st[v])
                return dead[u] = 1; // BACK EDGE = CYCLE
        }
    }
    st[u] = 0;
    return 0;
}
