#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Filename is Missing\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Enter the text (\"-1\" to exit):\n");
    while (1) {
        char temp[2000];
        printf(">> ");
        fgets(temp, sizeof(temp), stdin); 

        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') {
            temp[len - 1] = '\0';
        }

        if (strcmp(temp, "-1") == 0) break; 
        fprintf(file, "%s\n", temp);       
    }

    fclose(file);
    printf("Data written successfully.\n");

    return 0;
}