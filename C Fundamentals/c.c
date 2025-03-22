#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[100];

    printf("Enter a password: ");
    scanf("%s", password);

    int has_lowercase = 0, has_uppercase = 0, has_digit = 0, has_special = 0;

    for (int i = 0; password[i] != '\0'; i++) {
        if (islower(password[i]))
            has_lowercase = 1;
        else if (isupper(password[i]))
            has_uppercase = 1;
        else if (isdigit(password[i]))
            has_digit = 1;
        else if (strchr("_@$#", password[i]))
            has_special = 1;
    }

    if (has_lowercase && has_uppercase && has_digit && has_special) {
        printf("OK\n");
    } 
    else {
        if (!has_lowercase)
            printf("Lowercase character missing\n");
        if (!has_uppercase)
            printf("Uppercase character missing\n");
        if (!has_digit)
            printf("Digit missing\n");
        if (!has_special)
            printf("Special character missing\n");
    }

    return 0;
}
