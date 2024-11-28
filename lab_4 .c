#include <stdio.h>

int main() {
    int n, i, j, completed = 0, currentTime = 0, shortest;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n], done[n];
    for (i = 0; i < n; i++) {
        printf("P%d burst time: ", i + 1);
        scanf("%d", &bt[i]);
        done[i] = 0; // Initialize as incomplete
    }

    while (completed < n) {
        shortest = -1;
        for (i = 0; i < n; i++)
            if (!done[i] && (shortest == -1 || bt[i] < bt[shortest]))
                shortest = i;
        wt[shortest] = currentTime;
        tat[shortest] = wt[shortest] + bt[shortest];
        currentTime += bt[shortest];
        done[shortest] = 1;
        completed++;
    }

    printf("\nP\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);

    return 0;
}


Enter number of processes: 4
P1 burst time: 6
P2 burst time: 8
P3 burst time: 7
P4 burst time: 3


P	BT	WT	TAT
P1	6	3	9
P2	8	16	24
P3	7	9	16
P4	3	0	3
