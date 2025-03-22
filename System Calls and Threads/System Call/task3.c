#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int count;
pid_t a, b, c;


int read_count() {
    FILE *file = fopen("count.txt", "r");
    if (!file) {
        perror("Error opening");
        return -1;
    }
    int count;
    fscanf(file, "%d", &count);
    fclose(file);
    return count;
}

void write_count(int count) {
    FILE *file = fopen("count.txt", "w");
    if (!file) {
        perror("Error opening");
        return;
    }
    fprintf(file, "%d", count);
    fclose(file);
}

void count_process(pid_t pid){
    if (pid==0)
    {
        count = read_count();
        count++;
        write_count(count);

        if (getpid() % 2 != 0)
        {
            // printf("\t%ld\n", getpid());
            pid_t odd = fork();
            if (odd == 0){
                count = read_count();
                count++;
                write_count(count);
            }
            else if (odd > 0)
                wait(NULL);
            else
                perror("Error!!");
        }
    }
    else if (pid > 0)
        wait(NULL);
    else
        perror("Error!!");
    
}

int main(int argc, char *argv[]){
    pid_t parent = getpid();
    write_count(1);

    a = fork();
    count_process(a);

    b = fork();
    count_process(b);

    c = fork();
    count_process(c);
    

    if (getpid() == parent){ 
        count = read_count();
        printf("Total number of processes created: %d\n", count); 
        remove("count.txt");   
    }
    return 0;
}