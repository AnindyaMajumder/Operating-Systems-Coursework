#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc < 2)
        return 1;
    
    int num[argc-1];
    for (int i = 1; i < argc; i++){
        num[i-1] = atoi(argv[i]);

        if (num[i-1] % 2 == 0)
            printf("%d is even\n", num[i-1]);
        else
            printf("%d is odd\n", num[i-1]);
        
    }
    
    
    return 0;
}