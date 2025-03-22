#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MSG_KEY 12
#define WORKSPACE "cse321"
#define LOGIN_TO_OTP 2
#define OTP_TO_MAIL 5
#define OTP_TO_LOGIN 8
#define MAIL_TO_LOGIN 9

struct msg {
    long int type;
    char txt[6];
};

void login(int msg_id) {
    struct msg message;

    printf("Please enter the workspace name:\n");
    char input[6];
    scanf("%s", input);

    if (strcmp(input, WORKSPACE) != 0) {
        printf("Invalid workspace name\n");
        exit(0);
    }

    // Send workspace name to OTP generator
    message.type = LOGIN_TO_OTP;
    strcpy(message.txt, input);
    if (msgsnd(msg_id, &message, sizeof(message.txt), 0) == -1) {
            perror("Send OTP Failed!");
            exit(0);
    }
    printf("Workspace name sent to OTP generator from log in: %s\n\n", message.txt);

    // Fork OTP generator
    pid_t otp_pid = fork();
    if (otp_pid < 0) {
        perror("Fork Failed!");
        exit(1);
    } else if (otp_pid == 0) {
        otp_generator(msg_id);
    } else {
        int status;
        wait(&status);

        // Receive OTP from OTP generator
        if (msgrcv(msg_id, &message, sizeof(message.txt), OTP_TO_LOGIN, IPC_NOWAIT) == -1) {
            perror("Receive OTP Error!!");
            exit(1);
        }
        printf("Log in received OTP from OTP generator: %s\n", message.txt);
        char otp_from_otp[6];
        strcpy(otp_from_otp, message.txt);

        // Receive OTP from mail
        if (msgrcv(msg_id, &message, sizeof(message.txt), MAIL_TO_LOGIN, IPC_NOWAIT) == -1) {
            perror("Receive from mail Failed!");
            exit(1);
        }
        printf("Log in received OTP from mail: %s\n", message.txt);
        char otp_from_mail[6];
        strcpy(otp_from_mail, message.txt);

        // Compare OTPs
        if (strcmp(otp_from_otp, otp_from_mail) == 0) {
            printf("OTP Verified\n");
        } else {
            printf("OTP Incorrect\n");
        }

        // Cleanup message queue
        msgctl(msg_id, IPC_RMID, NULL);
    }
}

void otp_generator(int msg_id) {
    struct msg message;

    // Receive workspace name from login
    if (msgrcv(msg_id, &message, sizeof(message.txt), LOGIN_TO_OTP, IPC_NOWAIT) == -1) {
        perror("OTP receiving Failed!");
        exit(1);
    }
    printf("OTP generator received workspace name from log in: %s\n\n", message.txt);

    // Generate OTP and send to login and mail
    pid_t otp = getpid();
    snprintf(message.txt, sizeof(message.txt), "%d", otp);

    // Send OTP to login
    message.type = OTP_TO_LOGIN;
    if (msgsnd(msg_id, &message, sizeof(message.txt), 0) == -1) {
        perror("OTP send Failed!");
        exit(1);
    }
    printf("OTP sent to log in from OTP generator: %s\n", message.txt);

    // Send OTP to mail
    message.type = OTP_TO_MAIL;
    if (msgsnd(msg_id, &message, sizeof(message.txt), 0) == -1) {
        perror("OTP send to mail Failed!");
        exit(1);
    }
    printf("OTP sent to mail from OTP generator: %s\n", message.txt);

    // Fork mail
    pid_t mail_pid = fork();
    if (mail_pid < 0) {
        perror("Fork Failed!");
        exit(1);
    } else if (mail_pid == 0) {
        mail(msg_id);
    } else {
        int status;
        wait(&status);
        exit(0);
    }
}

void mail(int msg_id) {
    struct msg message;

    // Receive OTP from OTP generator
    if (msgrcv(msg_id, &message, sizeof(message.txt), OTP_TO_MAIL, IPC_NOWAIT) == -1) {
        perror("Error receiving OTP!!");
        exit(1);
    }
    printf("Mail received OTP from OTP generator: %s\n", message.txt);

    // Send OTP to login
    message.type = MAIL_TO_LOGIN;
    if (msgsnd(msg_id, &message, sizeof(message.txt), 0) == -1) {
        perror("OTP sending Failed!");
        exit(1);
    }
    printf("OTP sent to log in from mail: %s\n", message.txt);

    exit(0);
}

int main() {
    int msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("Error creating message queue");
        exit(1);
    }

    login(msg_id);
    return 0;
}
