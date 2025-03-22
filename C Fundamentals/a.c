#include <stdio.h>
int main()
{
    double a, b;
    
    printf("Enter First No: ");
    scanf("%lf", &a);
    
    printf("Enter Second No: ");
    scanf("%lf", &b);
    
    if(a>b) printf("%.2lf - %.2lf = %.2lf\n", a, b, a-b);
    else if (a<b) printf("%.2lf + %.2lf = %.2lf\n", a, b, a+b);
    else printf("%.2lf * %.2lf = %.2lf\n", a, b, a*b);
    
    return 0;
}