#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if (argc < 2)
        return 1;

    pid_t pid = fork();
    if(pid < 0){
        perror("Error!!");
        return 1;
    }
    else if (pid == 0)
    {
        char *sort_args[argc + 1];
        sort_args[0] = "./sort";
        for (int i = 1; i < argc; i++)
            sort_args[i] = argv[i]; 
        sort_args[argc] = NULL;

        printf("\tChild printing\n");
        if(execv("./sort", sort_args) == -1)
            exit(1);
    }
    else{
        wait(NULL);

        char *oddeven_args[argc + 1];
        oddeven_args[0] = "./oddeven";
        for (int i = 1; i < argc; i++) {
            oddeven_args[i] = argv[i];
        }
        oddeven_args[argc] = NULL;
        
        printf("\tParent printing\n");
        if (execv("./oddeven", oddeven_args) == -1)
            exit(1);
    }
    
    
    return 0;
}