/*
Example 4: VLA with Function Return Values
You can use VLAs to allocate memory dynamically inside functions and return the array to the caller. 
However, VLAs are limited to being local to the function and can't be returned as a direct reference to the array.
*/

#include <stdio.h>
#include <stdlib.h>

// Function that returns a dynamically allocated array (VLA-like)
int* create_array(int size) {
    int* arr = malloc(size * sizeof(int)); // Dynamically allocate memory for array
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);  // Exit if memory allocation fails
    }
    // Initialize the array with some values
    for (int i = 0; i < size; i++) {
        arr[i] = i * 5;
    }
    return arr;  // Return the pointer to the allocated array
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    // Create the array using the function
    int* arr = create_array(n);

    // Print the array
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}

/*
Explanation:
The create_array function allocates memory for an array using malloc and initializes it with values based on 
the index (i * 5).

The array is dynamically created and returned by the function as a pointer.

After using the array, we free the memory allocated by malloc to avoid memory leaks.
*/
