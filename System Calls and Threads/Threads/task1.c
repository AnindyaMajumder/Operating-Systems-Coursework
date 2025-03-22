#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* threadFunc(void* arg){
    printf("thread-%d running\n", *(int*)arg);
    printf("thread-%d closed\n",*(int*)arg);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[5];

    for (int i = 1; i <= 5; i++)
    {
        pthread_create(&threads[i-1], NULL, threadFunc, &i);
        pthread_join(threads[i-1], NULL);
    }
    
    return 0;
}
