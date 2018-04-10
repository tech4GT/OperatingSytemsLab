//
// Created by Varun Gupta on 4/9/18.
//
#include<stdio.h>

void findWaitingTime(int n, int bt[], int wt[]) {
    //waiting time for process one
    wt[0] = 0;

    //waiting time calculation
    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
}

void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {

    //turn around time calculation
    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];
}

void findAvgTime(int processes[], int n, int bt[]) {

    //declaration of local variables
    int wt[n], tat[n], totalWT = 0, totalTAT = 0;

    findWaitingTime(n, bt, wt);
    findTurnAroundTime(n, bt, wt, tat);

    printf("P    WT    TAT\n");

    for (int i = 0; i < n; i++) {
        totalTAT += tat[i];
        totalWT += wt[i];
        printf("%d    %d    %d\n",processes[i],wt[i],tat[i]);
    }

    printf("average turn around time is ");
    printf("%f", (float) totalTAT / (float) n);
    printf("\naverage waiting time is ");
    printf("%f", (float) totalWT / (float) n);
}

void main() {
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[1];
    int bt[3] = {10, 5, 8};
    findAvgTime(processes, n, bt);
}

