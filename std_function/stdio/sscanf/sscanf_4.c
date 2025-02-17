/*
Using sscanf with Arrays:

You can use sscanf to read multiple items into an array, especially when reading lists of numbers or strings.

Example:
*/
#include <stdio.h>

int main() {
    const char *input = "10 20 30 40 50";
    int numbers[5];

    int result = sscanf(input, "%d %d %d %d %d", &numbers[0], &numbers[1], &numbers[2], &numbers[3], &numbers[4]);

    if (result == 5) {
        for (int i = 0; i < 5; i++) {
            printf("Number %d: %d\n", i + 1, numbers[i]);
        }
    } else {
        printf("Failed to parse the input.\n");
    }

    return 0;
}

/*
Explanation:
The input "10 20 30 40 50" contains five integers, and the format string "%d %d %d %d %d" expects five integers.
The parsed values are stored in the numbers array, and the program prints each number.
*/