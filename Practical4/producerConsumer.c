//
// Created by Varun Gupta on 4/12/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t mutex, full, embty;

int produce() {
    int random =  rand() % 100;
    printf("Produced value is %d\n",random);
    return random;
}

void *producer() {
    int val,semFull = 0;
    printf("Staring producer\n");
    while (1) {
        val = produce();
        sem_wait(&embty);
        sem_wait(&mutex);
        sem_getvalue(&full,semFull);
        buffer[semFull] = val;
        sem_post(&mutex);
        sem_post(&full);
    }
}
void consume(int val){
    printf("Consumed value is %d\n",val);
}

void *consumer() {
    int val,semFull;
    printf("Starting Consumer");
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);
        sem_getvalue(&full,semFull);
        val = buffer[semFull];
        sem_post(&mutex);
        sem_post(&embty);
        consume(val);
    }
}


void main() {
    sem_init(mutex, 0, 1);
    sem_init(full, 0, BUFFER_SIZE);
    sem_init(mutex, 0, 0);
    pthread_t prodThread, consThread;
    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);
    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);
}