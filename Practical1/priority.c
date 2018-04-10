//
// Created by Varun Gupta on 4/9/18.
//
#include<stdio.h>

struct Process{
    int pid;
    int bt;
    int pri;
};

int compare(struct Process p1,struct Process p2){
    return (p1.pri - p2.pri);
};

void sort(struct Process processes[],int n){

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(compare(processes[i],processes[j])>0){
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void findWaitingTime(struct Process processes[], int n, int wt[]) {
    //waiting time for process one
    wt[0] = 0;

    //waiting time calculation
    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + processes[i - 1].bt;
}

void findTurnAroundTime(struct Process processes[],int n, int wt[], int tat[]) {

    //turn around time calculation
    for (int i = 0; i < n; i++)
        tat[i] = wt[i] + processes[i].bt;
}

void findAvgTime(struct Process processes[], int n) {

    //declaration of local variables
    int wt[n], tat[n], totalWT = 0, totalTAT = 0;

    findWaitingTime(processes,n, wt);
    findTurnAroundTime(processes,n,wt, tat);

    printf("P    WT    TAT\n");

    for (int i = 0; i < n; i++) {
        totalTAT += tat[i];
        totalWT += wt[i];
        printf("%1d%6d%7d\n",processes[i].pid,wt[i],tat[i]);
    }

    printf("average turn around time is ");
    printf("%f", (float) totalTAT / (float) n);
    printf("\naverage waiting time is ");
    printf("%f", (float) totalWT / (float) n);
}

void main() {
    struct Process processes[] = {{1,10,2}, {2,5,1}, {3,8,3}};
    int n = sizeof processes / sizeof processes[1];
    sort(processes,n);
    findAvgTime(processes, n);
}

