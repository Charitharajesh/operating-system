#include <stdio.h>

typedef struct { int id, burst, remaining, wait, turn; } Process;

void roundRobin(Process p[], int n, int quantum) {
    int time = 0, completed = 0, totalW = 0, totalT = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (p[i].remaining <= quantum) {
                    time += p[i].remaining;
                    p[i].remaining = 0;
                    p[i].turn = time;
                    p[i].wait = p[i].turn - p[i].burst;
                    totalW += p[i].wait;
                    totalT += p[i].turn;
                    completed++;
                } else {
                    time += quantum;
                    p[i].remaining -= quantum;
                }
            }
        }
    }

    printf("\nID Burst Wait Turn\n");
    for (int i = 0; i < n; i++)
        printf("%2d %5d %4d %4d\n", p[i].id, p[i].burst, p[i].wait, p[i].turn);
    printf("\nAvg Wait: %.2f, Avg Turn: %.2f\n", (float)totalW / n, (float)totalT / n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d Burst: ", i + 1);
        scanf("%d", &p[i].burst);
        p[i].id = i + 1;
        p[i].remaining = p[i].burst;
    }

    roundRobin(p, n, quantum);
    return 0;
}
