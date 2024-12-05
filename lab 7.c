#include <stdio.h>
#include <limits.h>

typedef struct { int id, burst, wait, turn; } Process;

void schedule(Process p[], int n) {
    int completed = 0, time = 0, minBurst, shortest, totalW = 0, totalT = 0;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    while (completed < n) {
        minBurst = INT_MAX, shortest = -1;
        for (int i = 0; i < n; i++)
            if (!done[i] && p[i].burst < minBurst) minBurst = p[i].burst, shortest = i;

        if (shortest == -1) { time++; continue; }

        time += p[shortest].burst;
        p[shortest].turn = time;
        p[shortest].wait = p[shortest].turn - p[shortest].burst;
        totalW += p[shortest].wait;
        totalT += p[shortest].turn;
        done[shortest] = 1;
        completed++;
    }

    printf("\nID Burst Wait Turn\n");
    for (int i = 0; i < n; i++)
        printf("%2d %5d %4d %4d\n", p[i].id, p[i].burst, p[i].wait, p[i].turn);
    printf("\nAvg Wait: %.2f, Avg Turn: %.2f\n", (float)totalW / n, (float)totalT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d Burst: ", i + 1);
        scanf("%d", &p[i].burst);
        p[i].id = i + 1;
    }
    schedule(p, n);
    return 0;
}
