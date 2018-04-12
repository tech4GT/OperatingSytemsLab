//
// Created by Varun Gupta on 4/12/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


int readCount = 0;
sem_t mutex, wrt;

int read() {

    printf("A reader %d is reading\n",pthread_self());

}

void *reader() {
    sem_wait(&mutex);
        readCount++;
        if(readCount == 1)
            sem_wait(&wrt);
    sem_post(&mutex);

    read();

    sem_wait(&mutex);
    readCount--;
    if(readCount==0)
        sem_post(wrt);
    sem_post(&mutex);

}
void write(){

    printf("Writer %d is writing\n",pthread_self());

}

void *writer() {
    sem_wait(&wrt);
    write();
    sem_post(&wrt);
}


void main() {
    sem_init(mutex, 0, 1);
    sem_init(wrt, 0, 1);
    pthread_t writerThread, readerThread1,readerThread2;
    pthread_create(&readerThread1, NULL, reader, NULL);
    pthread_create(&writerThread, NULL, writer, NULL);
    pthread_create(&readerThread2, NULL, reader, NULL);
    pthread_join(readerThread1, NULL);
    pthread_join(writerThread, NULL);
    pthread_join(readerThread2, NULL);
}