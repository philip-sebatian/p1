#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f1, *f2;
    f1 = fopen("inp.txt", "r");
    f2 = fopen("out.txt", "w");
    if (f1 == NULL || f2 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[50], strtadd[7], buffer[3];
    int i, j, add;

    // Read and discard the first line
    fscanf(f1, "%s", line);
    // Start reading from the second line
    fscanf(f1, "%s", line);

    while (line[0] != 'E') {
        // Extract address (characters from index 2 to 7)
        for (i = 0, j = 2; i < 6; i++, j++) {
            strtadd[i] = line[j];
        }
        strtadd[i] = '\0'; // Null-terminate the address string

        // Convert address to integer
        add = atoi(strtadd);

        // Parse the rest of the line starting from index 12
        j = 12;
        while (j < strlen(line)) {
            if (line[j] != '^') {
                buffer[0] = line[j];
                buffer[1] = line[j + 1];
                buffer[2] = '\0'; // Null-terminate to make it a valid string

                // Print and write to output
                printf("%d\t%s\n", add, buffer);
                fprintf(f2, "%d\t%s\n", add, buffer);
                add++; // Increment address for each pair of characters

                j += 2; // Move to the next pair
            } else {
                j++; // Skip '^' character
            }
        }

        // Read the next line from the input file
        fscanf(f1, "%s", line);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
