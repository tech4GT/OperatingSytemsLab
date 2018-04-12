//
// Created by Varun Gupta on 4/10/18.
//

#include<stdio.h>
#include<limits.h>

struct Process{
    int pid;
    int bt;
    int at;
};

int findShortestRemainingTime(int rt[],int n){
    int min = INT_MAX;
    int minInd = -1;
    for(int i=0;i<n;i++)
        if(rt[i]!=0 && rt[i]<min) {
        min=rt[i];
        minInd = i;
    }
    return minInd;
}

void findWaitingandTurnAroundTime(struct Process processes[],int n,int wt[],int tat[],int rt[]){
    int t=0;

    int minInd = 0;

    while(minInd != -1){

        for(int i=0;i<n;i++)
            if(processes[i].at == t)
                rt[i] = processes[i].bt;

        minInd = findShortestRemainingTime(rt,n);
        if(minInd == -1) break;
        rt[minInd]--;
        t++;

        if(rt[minInd] == 0)
            tat[minInd] = t - processes[minInd].at;


        for(int i=0;i<n;i++){
            if(rt[i]!=0 && i!=minInd)
                wt[i]++;
        }

    }
}
void findAvgTime(struct Process processes[], int n){
    int wt[n],tat[n],totalTAT=0,totalWT=0,rt[n];
    findWaitingandTurnAroundTime(processes,n,wt,tat,rt);
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


void main(){
    struct Process processes[] = {{1,6,0}, {2,8,0}, {3,1,2}};
    int n = sizeof processes / sizeof processes[1];
    findAvgTime(processes, n);
}

