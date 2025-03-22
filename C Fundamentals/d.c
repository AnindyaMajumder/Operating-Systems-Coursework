#include <stdio.h>
#include <string.h>

void checkEmail(char email[]) {
    char oldDomain[] = "@kaaj.com";
    char newDomain[] = "@sheba.xyz";

    if (strstr(email, oldDomain) != NULL) {
        printf("Email address is outdated\n");
    }
    else if (strstr(email, newDomain) != NULL) {
        printf("Email address is okay\n");
    } else {
        printf("Invalid email address\n");
    }
}

int main() {
    char email[100];

    printf("Enter email address: ");
    scanf("%s", email);

    checkEmail(email);

    return 0;
}
