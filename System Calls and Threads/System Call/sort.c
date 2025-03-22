#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    return (*(int *)b - *(int *)a);
}

int main(int argc, char *argv[]){
    if (argc < 2)
        return 1;
    
    int num[argc-1];
    for (int i = 1; i < argc; i++)
        num[i-1] = atoi(argv[i]);
    
    qsort(num, argc-1, sizeof(int), compare);

    printf("Sorted array in decending order:\n");
    for (int i = 0; i < argc-1; i++)
        printf("%d\n",num[i]);
    
    return 0;
}