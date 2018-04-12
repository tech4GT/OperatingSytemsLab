//
// Created by Varun Gupta on 4/12/18.
//

#include<stdio.h>

#define TIME_SLICE 1

struct Process {
    int pid;
    int bt;
};

int isComplete(int rt[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (rt[i] > 0)
            return 0;
    }
    return 1;
}

void findWaitingandTurnAroundTime(struct Process processes[], int n, int wt[], int tat[], int rt[]) {
    int t = 0, i, j;
    for (i = 0; i < n; i++) {
        rt[i] = processes[i].bt;
        wt[i] = 0;
    }


    while (!isComplete(rt, n)) {

        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                rt[i] = rt[i] - TIME_SLICE;
                t = t + TIME_SLICE;

                for (j = 0; j < n; j++) {
                    if (j != i && rt[j] > 0)
                        wt[j]++;
                }

                if (rt[i] == 0)
                    tat[i] = t;
            }
        }
    }
}

void findAvgTime(struct Process processes[], int n) {
    int wt[n], tat[n], totalTAT = 0, totalWT = 0, rt[n];
    findWaitingandTurnAroundTime(processes, n, wt, tat, rt);
    printf("P    WT    TAT\n");

    for (int i = 0; i < n; i++) {
        totalTAT += tat[i];
        totalWT += wt[i];
        printf("%1d%6d%7d\n", processes[i].pid, wt[i], tat[i]);
    }

    printf("average turn around time is ");
    printf("%f", (float) totalTAT / (float) n);
    printf("\naverage waiting time is ");
    printf("%f", (float) totalWT / (float) n);
}

void main() {
    struct Process processes[] = {{1, 6},
                                  {2, 8},
                                  {3, 1}};
    int n = sizeof processes / sizeof processes[1];
    findAvgTime(processes, n);
}