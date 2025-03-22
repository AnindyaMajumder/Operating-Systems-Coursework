#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    const char *input_file = "inp_b.txt";
    const char *output_file = "out_b.txt";

    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        printf("Error: Could not open file.\n");
        return 0;
    }

    char line[1000];
    while (fgets(line, sizeof(line), input)) {
        int i = 0, j = 0;
        while (line[i] != '\0') {
            if (!(isspace(line[i]) && (i == 0 || isspace(line[i - 1])))) {
                line[j++] = line[i];
            }
            i++;
        }
        if (j > 0 && isspace(line[j - 1])) j--;

        line[j] = '\0';
        fputs(line, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}
