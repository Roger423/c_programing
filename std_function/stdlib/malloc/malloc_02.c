//Example: Allocating Memory for an Array

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;
    int *arr = (int *)malloc(n * sizeof(int)); // Allocate memory for 5 ints
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize the array
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Print the array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr); // Free the memory
    return 0;
}

/*
Size Calculation: n * sizeof(int) ensures enough bytes for n integers.
Array Access: Treat arr like a regular array with arr[i].
*/