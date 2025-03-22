#include <stdio.h>
#include <string.h>

struct Item
{
    int unit_price;
    int quantity;
};

int main(){
    struct Item paratha, veg, water;
    int people;

    float total_bill, payment;

    printf("Quantity of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%d", &paratha.unit_price);

    printf("Quantity of Vegetables: ");
    scanf("%d", &veg.quantity);
    printf("Unit Price: ");
    scanf("%d", &veg.unit_price);

    printf("Quantity of Mineral water: ");
    scanf("%d", &water.quantity);
    printf("Unit Price: ");
    scanf("%d", &water.unit_price);

    printf("Number of People: ");
    scanf("%d", &people);

    total_bill = (paratha.quantity * paratha.unit_price) +
                 (veg.quantity * veg.unit_price) +
                 (water.quantity * water.unit_price);
    
    payment = total_bill / people;
    printf("Individual people will pay: %.2f tk\n", payment);

    return 0;
}