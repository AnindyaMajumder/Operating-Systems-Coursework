#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

struct shared {
    int b;
    char sel[100];
};

void get_user_input(struct shared *shared_data) {
    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money\n");
    printf("2. Type w to Withdraw Money\n");
    printf("3. Type c to Check Balance\n");
    printf("Enter your choice: ");
    scanf("%s", (*shared_data).sel);
    printf("Your selection: %s\n", (*shared_data).sel);
}

void handle_child_process(int pipe_fd[], int shmid) {
    close(pipe_fd[0]);

    struct shared *child_data = (struct shared *)shmat(shmid, NULL, 0);
    if (child_data == (void *)-1) {
        perror("shmat (child)");
        exit(0);
    }

    int amount;
    if (strcmp((*child_data).sel, "a") == 0) {
        printf("Enter amount to add: ");
        scanf("%d", &amount);
        if (amount > 0) {
            (*child_data).b += amount;
            printf("Balance added successfully.\n");
            printf("Updated balance: %d\n", (*child_data).b);
        } else {
            printf("Adding failed. Invalid amount.\n");
        }
    } else if (strcmp((*child_data).sel, "w") == 0) {
        printf("Enter amount to withdraw: ");
        scanf("%d", &amount);
        if (amount > 0 && amount <= (*child_data).b) {
            (*child_data).b -= amount;
            printf("Withdrawal successful.\n");
            printf("Updated balance: %d\n", (*child_data).b);
        } else {
            printf("Withdrawal failed. Invalid amount.\n");
        }
    } else if (strcmp((*child_data).sel, "c") == 0) {
        printf("Your current balance: %d\n", (*child_data).b);
    } else {
        printf("Invalid selection.\n");
    }

    char message[] = "Thank you for using";
    write(pipe_fd[1], message, strlen(message) + 1);
    close(pipe_fd[1]);

    shmdt(child_data);
    exit(1);
}

void handle_parent_process(int pipe_fd[], int shmid, struct shared *shared_data) {
    close(pipe_fd[1]);

    wait(NULL); 

    char buffer[200];
    read(pipe_fd[0], buffer, sizeof(buffer));
    printf("%s\n", buffer);
    close(pipe_fd[0]);

    shmdt(shared_data);
    shmctl(shmid, IPC_RMID, NULL);
}

int main() {
    // Create Pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Setup shared memory
    int shmid = shmget(IPC_PRIVATE, sizeof(struct shared), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    struct shared *shared_data = (struct shared *)shmat(shmid, NULL, 0);
    if (shared_data == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    (*shared_data).b = 1000;
    get_user_input(shared_data);

    // IPC implementation
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } 
    else if (pid == 0) 
        handle_child_process(pipe_fd, shmid);
    else 
        handle_parent_process(pipe_fd, shmid, shared_data);
    

    return 0;
}
