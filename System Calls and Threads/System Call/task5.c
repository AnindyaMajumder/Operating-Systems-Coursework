#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid_child, pid_grandchild1, pid_grandchild2, pid_grandchild3;

    printf("Parent process ID: %ld\n", getpid());

    pid_child = fork();
    if (pid_child < 0)
        exit(1);
    else if (pid_child == 0)
    {
        printf("Child process ID: %ld\n", getpid());

        pid_grandchild1 = fork();
        if (pid_grandchild1 < 0)
            exit(1);
        else if (pid_grandchild1 == 0)
            printf("Grandchild 1 process ID: %ld\n", getpid());
        else
            wait(NULL);
        
        pid_grandchild2 = fork();
        if (pid_grandchild2 < 0)
            exit(1);
        else if (pid_grandchild2 == 0)
            printf("Grandchild 2 process ID: %ld\n", getpid());
            
        else
            wait(NULL);

        pid_grandchild3 = fork();
        if (pid_grandchild3 < 0)
            exit(1);
        else if (pid_grandchild3 == 0)
            printf("Grandchild 3 process ID: %ld\n", getpid());
        else
            wait(NULL);
    }
    else
        wait(NULL);
    
    return 0;
}