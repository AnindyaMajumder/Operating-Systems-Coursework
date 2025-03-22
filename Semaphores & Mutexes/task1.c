#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 

#define MAX 10
#define BUFLEN 6
#define NUMTHREAD 2

char buffer[BUFLEN];
char source[BUFLEN];
int pCount = 0;
int cCount = 0;
int buflen;
void *consumer(int *id);
void *producer(int *id);

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_id[NUMTHREAD] = {0, 1};
int i = 0; 
int j = 0; 

int main() {
    int i;
    pthread_t thread[NUMTHREAD];
    strcpy(source, "abcdef");
    buflen = strlen(source);

    pthread_create(&thread[0], NULL, producer, &thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, &thread_id[1]);

    for (i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&nonEmpty);
    pthread_cond_destroy(&full);

    return 0;
}

void *producer(int *id) {
    int tid = *id;
    while (pCount < MAX) {
        pthread_mutex_lock(&count_mutex);
        while (pCount - cCount >= BUFLEN) {
            printf("Producer %d waiting (buffer full)\n", tid);
            pthread_cond_wait(&full, &count_mutex);
        }

        buffer[pCount % BUFLEN] = source[pCount % buflen];
        printf("%d produced %c by Thread %d\n", pCount, buffer[pCount % BUFLEN], tid);
        pCount++;

        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
        usleep(500000); 
    }
    return NULL;
}

void *consumer(int *id) {
    int tid = *id;
    while (cCount < MAX) {
        pthread_mutex_lock(&count_mutex);
        while (pCount - cCount <= 0) {
            printf("Consumer %d waiting (buffer empty)\n", tid);
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        printf("%d consumed %c by Thread %d\n", cCount, buffer[cCount % BUFLEN], tid);
        cCount++;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
        usleep(500000);
    }
    return NULL;
}