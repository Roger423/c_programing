//Example 2: Allocating Memory for a 2D Array

#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t rows = 3, cols = 4;
    int **arr;

    // Allocating memory for a 2D array (3 rows and 4 columns)
    arr = (int **)calloc(rows, sizeof(int *));  // Allocate memory for row pointers

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < rows; i++) {
        arr[i] = (int *)calloc(cols, sizeof(int));  // Allocate memory for columns of each row
        if (arr[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    // Displaying the values (initialized to 0)
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("arr[%zu][%zu] = %d\n", i, j, arr[i][j]);  // Output will be zeroes
        }
    }

    // Freeing the allocated memory
    for (size_t i = 0; i < rows; i++) {
        free(arr[i]);  // Free memory for each row
    }
    free(arr);  // Free memory for the row pointers

    return 0;
}
