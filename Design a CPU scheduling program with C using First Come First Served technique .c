#include <stdio.h>

int main() {
    int n, i, totalWT = 0, totalTAT = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n]; // Burst time, Waiting time, Turnaround time

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0; // First process has zero waiting time
    for (i = 1; i < n; i++) 
        wt[i] = wt[i - 1] + bt[i - 1]; // Calculate waiting time

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i]; // Turnaround time = Waiting time + Burst time
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
        printf("P%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT / n);

    return 0;
}




Enter the number of processes: 3
Enter burst times:
P1: 5
P2: 3
P3: 8


Process Burst Time  Waiting Time  Turnaround Time
P1         5              0              5
P2         3              5              8
P3         8              8             16

Average Waiting Time: 4.33
Average Turnaround Time: 9.67
