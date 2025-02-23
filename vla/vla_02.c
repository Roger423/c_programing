//Example 2: VLA as Function Parameters
//You can also pass VLAs as function parameters. The size of the VLA is determined by the argument passed when 
//calling the function.

#include <stdio.h>

void print_array(int n, int arr[n]) {
    // Print the array elements
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    // Get the array size from the user
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    // Declare a VLA
    int arr[n];

    // Initialize the array
    for (int i = 0; i < n; i++) {
        arr[i] = i * 3;
    }

    // Call the function and pass the VLA
    print_array(n, arr);

    return 0;
}

/*
Explanation:

The function print_array takes a VLA as a parameter. The size n is passed as the first argument, and the array arr is 
passed as the second argument.

This allows you to create and pass VLAs dynamically to functions.
*/