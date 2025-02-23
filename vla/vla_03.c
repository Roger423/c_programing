//Example 3: Using VLA in Nested Loops (2D Arrays)
//You can use VLAs to create multi-dimensional arrays as well.

#include <stdio.h>

int main() {
    int rows, cols;

    // Get the number of rows and columns from the user
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    // Declare a VLA for a 2D array
    int matrix[rows][cols];

    // Initialize the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * j;  // Example: multiplication of indices
        }
    }

    // Print the matrix
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/*
Explanation:
The code creates a 2D matrix where both the number of rows and columns are determined at runtime.
The elements of the matrix are filled with the product of the row and column indices and printed out.
*/