//
// Created by Varun Gupta on 4/12/18.
//

#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>

int var = 10;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void *thread1(){

    printf("\nNow running thread 1");
    pthread_mutex_lock(&lock);
    printf("\nLock acquired by thread 1");
    var = 100;
    printf("\nUpdate var in thread 1 \nValue of var %d",var);
    pthread_mutex_unlock(&lock);
    printf("\nLock released by thread 1");

}

void *thread2(){

    printf("\nNow running thread 2");
    pthread_mutex_lock(&lock);
    printf("\nLock acquired by thread 2");
    var = 200;
    printf("\nUpdate var in thread 2 \nValue of var %d",var);
    pthread_mutex_unlock(&lock);
    printf("\nLock released by thread 2");

}


void main(){
    pthread_t tId1,tId2;
    printf("Initial value of var is %d",var);
    pthread_create(&tId1,NULL,thread1,NULL);
    pthread_create(&tId2,NULL,thread2,NULL);
    pthread_join(tId1,NULL);
    pthread_join(tId2,NULL);
    printf("\nFinal value of var is %d",var);
}