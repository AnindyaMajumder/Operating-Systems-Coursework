#include <stdio.h>

void perfect_num(int num){
    int sum=0;
    for (int i = 1; i <= num/2; i++)
    {
        if(num%i == 0) 
            sum += i;
    }
    if (sum == num)
        printf("%d\n", num);
}

int main(){
    int start, end;
    
    printf("Enter starting number: ");
    scanf("%d", &start);

    printf("Enter ending number: ");
    scanf("%d", &end);

    for (int i = start; i <= end; i++)
    {
        perfect_num(i);
    }
    
}