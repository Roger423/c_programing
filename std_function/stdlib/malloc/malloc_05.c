//1D Memory Allocation for a 2D Array:

#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3, cols = 4;

    // Allocate memory for a 2D array as a single contiguous block
    int *arr = (int *)malloc(rows * cols * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize and print the array (treating it as a 2D array)
    int counter = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Accessing using row-major indexing
            arr[i * cols + j] = counter++;
            printf("%d ", arr[i * cols + j]);
        }
        printf("\n");
    }

    // Free the memory
    free(arr);

    return 0;
}

/*
Explanation:
1. We allocated rows * cols * sizeof(int) bytes in a single block of memory.
2. To access the 2D array element at position (i, j), we use the formula arr[i * cols + j]. This computes the 
   correct index in the flattened array.
3. Finally, after using the array, we free the allocated memory.
*/

/*
Summary:
1. Using int **arr (separate row allocations): This is a more intuitive and natural way of thinking about 2D arrays. 
   You allocate memory for each row separately and access the array using the arr[i][j] syntax. However, 
   it may be less memory-efficient due to separate allocations.
2. Using int *arr (single contiguous block): This allocates the entire 2D array as a single large block, which is 
   more memory-efficient in terms of allocation overhead. However, it requires manually calculating the index for 
   each element using the formula i * cols + j.
*/
