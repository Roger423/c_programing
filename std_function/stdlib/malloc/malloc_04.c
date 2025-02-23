// Using malloc() to Allocate a 2D Array

#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3, cols = 4;

    // Allocate memory for a 2D array (array of pointers to int)
    int **arr = (int **)malloc(rows * sizeof(int *));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(cols * sizeof(int));
        if (arr[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
    }

    // Initialize and print the array
    int counter = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = counter++;
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    // Free the memory
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}


/*
Explanation:
In this example, we allocate a 2D array dynamically using an array of pointers (int **arr). 
Each pointer is then used to allocate memory for each row.

We initialize the elements of the array and then print them.

After using the array, we free each row, followed by the pointer array itself.
*/