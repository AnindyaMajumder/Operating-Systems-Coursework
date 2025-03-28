#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h> 

#define MaxCrops 5
#define warehouseSize 5
sem_t empty;
sem_t full;
int in = 0;
int out = 0;

char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'};
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'};
pthread_mutex_t mutex;

void *Farmer(void *farmerNumber) {
    int farmerID = *(int *)farmerNumber;
    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        warehouse[in] = crops[i];
        printf("Farmer %d: Insert crops %c at %d\n", farmerID, crops[i], in);
        in = (in + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1); 
    }
    printf("Farmer%d: ", farmerID);
    for (int j = 0; j < warehouseSize; j++) 
        printf("%c", warehouse[j]);

    printf("\n");
    pthread_exit(NULL);
}

void *ShopOwner(void *shopOwnerNumber) {
    int shopOwnerID = *(int *)shopOwnerNumber;
    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        char crop = warehouse[out];
        printf("Shop owner %d: Remove crops %c from %d\n", shopOwnerID, crop, out);
        warehouse[out] = 'N';
        out = (out + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1); 
    }
    printf("ShopOwner%d: ", shopOwnerID);
    for (int j = 0; j < warehouseSize; j++) 
        printf("%c", warehouse[j]);
    
    printf("\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t farmers[5], shopOwners[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize); 
    sem_init(&full, 0, 0);              

    int farmerIDs[5] = {1, 2, 3, 4, 5};
    int shopOwnerIDs[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_create(&farmers[i], NULL, Farmer, &farmerIDs[i]);
        pthread_create(&shopOwners[i], NULL, ShopOwner, &shopOwnerIDs[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(farmers[i], NULL);
        pthread_join(shopOwners[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}