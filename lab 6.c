#include <stdio.h>
#include <limits.h>

typedef struct { int id, burst, prio, rem; } Process;

void schedule(Process p[], int n) {
    int time = 0, done = 0, minP, shortP, wait[n], turn[n], totalW = 0, totalT = 0;
    for (int i = 0; i < n; i++) p[i].rem = p[i].burst;

    while (done < n) {
        minP = INT_MAX, shortP = -1;
        for (int i = 0; i < n; i++)
            if (p[i].rem > 0 && p[i].prio < minP) minP = p[i].prio, shortP = i;

        if (shortP == -1) { time++; continue; }

        p[shortP].rem--, time++;
        if (p[shortP].rem == 0) {
            done++, turn[shortP] = time, wait[shortP] = turn[shortP] - p[shortP].burst;
            totalW += wait[shortP], totalT += turn[shortP];
        }
    }

    printf("\nID Burst Prio Wait Turn\n");
    for (int i = 0; i < n; i++)
        printf("%2d %5d %4d %4d %4d\n", p[i].id, p[i].burst, p[i].prio, wait[i], turn[i]);
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
        printf("Process %d Prio: ", i + 1);
        scanf("%d", &p[i].prio);
        p[i].id = i + 1;
    }
    schedule(p, n);
    return 0;
}
