//
// Created by Varun Gupta on 4/10/18.
//

#include<stdio.h>
#include<limits.h>

struct Process{
    int pid;
    int bt;
    int pri;
    int at;
};

int findHighestPriority(struct Process processes[],int n,int rt[]){
    int min = INT_MAX,i,maxPriInd = -1;
    for(i=0;i<n;i++)
        if(processes[i].pri!=0 && processes[i].pri<min && rt[i]!=0) {
            min=processes[i].pri;
            maxPriInd = i;
        }
    return maxPriInd;
}

void findWaitingandTurnAroundTime(struct Process processes[],int n,int wt[],int tat[],int rt[]){
    int t=0,i;

    int minInd = 0;

    while(minInd != -1){

        for(i=0;i<n;i++)
            if(processes[i].at == t)
                rt[i] = processes[i].bt;

        minInd = findHighestPriority(processes,n,rt);

        if(minInd == -1) break;

        rt[minInd]--;
        t++;

        if(rt[minInd] == 0) {
            tat[minInd] = t - processes[minInd].at;
            processes[minInd].pri = 0;
        }


        for(i=0;i<n;i++){
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
    struct Process processes[] = {{1,6,3,0}, {2,8,2,1}, {3,1,1,3}};
    int n = sizeof processes / sizeof processes[1];
    findAvgTime(processes, n);
}

