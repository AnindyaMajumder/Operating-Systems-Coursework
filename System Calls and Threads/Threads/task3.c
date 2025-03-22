#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

char username[3][10] = {"Rahim", "Jashim", "Kahim"};
int thread_responses[3];

int ASCII_sum(char user[1000]) {
    int sum = 0;
    for (int i = 0; user[i] != '\0'; i++) { 
        sum += (int)user[i];
    }
    return sum;
}

void* thread(void* arg) {
    int index = *(int*)arg;
    thread_responses[index] = ASCII_sum(username[index]);
    printf("Thread %d ASCII sum: %d\n", index, thread_responses[index]); 
    return NULL;
}

int main(int argc, char const* argv[]) {
    pthread_t threads[3];
    int thread_idx[3]; 

    for (int i = 0; i < 3; i++) {
        thread_idx[i] = i; 
        pthread_create(&threads[i], NULL, thread, &thread_idx[i]); 
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    if (thread_responses[0] == thread_responses[1] && thread_responses[1] == thread_responses[2]) 
        printf("Youreka\n");
    else if (thread_responses[0] == thread_responses[1] || thread_responses[1] == thread_responses[2] || thread_responses[0] == thread_responses[2])
        printf("Miracle\n");
    else 
        printf("Hasta la vista\n");
    

    return 0;
}
