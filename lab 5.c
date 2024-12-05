#include <stdio.h>

typedef struct {
    int id, burstTime, priority;
} Process;

void sortByPriority(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void priorityScheduling(Process p[], int n) {
    int wait[n], turn[n], totalWait = 0, totalTurn = 0;
    wait[0] = 0;
    for (int i = 1; i < n; i++) wait[i] = wait[i - 1] + p[i - 1].burstTime;
    for (int i = 0; i < n; i++) {
        turn[i] = wait[i] + p[i].burstTime;
        totalWait += wait[i];
        totalTurn += turn[i];
    }
    printf("\nID  Burst  Priority  Wait  Turn\n");
    for (int i = 0; i < n; i++)
        printf("%2d %6d %8d %5d %5d\n", p[i].id, p[i].burstTime, p[i].priority, wait[i], turn[i]);
    printf("\nAvg Wait: %.2f, Avg Turn: %.2f\n", (float)totalWait / n, (float)totalTurn / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d Burst Time: ", i + 1);
        scanf("%d", &p[i].burstTime);
        printf("Process %d Priority: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].id = i + 1;
    }
    sortByPriority(p, n);
    priorityScheduling(p, n);
    return 0;
}

