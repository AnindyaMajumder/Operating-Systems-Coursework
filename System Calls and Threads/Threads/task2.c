#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int prints = 1;

void* thread(void* arg){
    for (int i = 0; i < 5; i++) {
        printf("Thread %d prints %d\n", *(int*)arg, prints);
        prints++;

        //sleep(1);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    int thread_id[5];
    pthread_t threads[5];

    for (int i = 0; i < 5; i++)
    {
        thread_id[i]=i;
        pthread_create(&threads[i], NULL, thread, &thread_id[i]);
        pthread_join(threads[i], NULL);
    }

    return 0;
}