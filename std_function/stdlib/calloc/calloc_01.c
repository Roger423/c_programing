/*
calloc Function in C: Detailed Guide
The calloc function in C is used to allocate memory dynamically for an array of elements and initializes that memory 
to zero. It is part of the standard library (stdlib.h) and is typically used for allocating memory for large arrays 
where you require both memory allocation and initialization to zero.

Syntax:

void *calloc(size_t num, size_t size);

num: The number of elements to be allocated.
size: The size of each element.

Description:
calloc allocates memory for an array of num elements, each of size bytes.
The function initializes the entire block of memory to zero (unlike malloc, which does not initialize the memory).
It returns a pointer to the allocated memory block, or NULL if the allocation fails.

Return Value:
A pointer to the allocated memory if successful.
NULL if memory allocation fails.

Important Notes:
Memory allocated by calloc is zeroed, meaning each byte in the allocated block is initialized to 0.
If num or size is 0, then calloc will return a NULL pointer in some implementations (even though it is technically 
allowed to return a valid non-NULL pointer to a zero-byte block in some implementations).

Advantages of calloc:
1. Zero-Initialization: Memory is initialized to zero, which is helpful when you want to ensure that there are no 
   garbage values in your array.
2. Safety: The memory allocated by calloc is safer to use compared to malloc because there are no uninitialized values.

Disadvantages of calloc:
1. Performance: Since calloc initializes the memory to zero, it may be slightly slower than malloc when you don't 
   need zero initialization.
2. Memory Consumption: Initializing memory takes time and can consume more CPU resources when dealing with large 
   allocations.

When to Use calloc:
When allocating an array or memory block where you want all elements initialized to zero (e.g., arrays, matrices, etc.).
When you want to ensure the memory is in a known state, which helps prevent bugs caused by using uninitialized memory.

Important Notes:
Memory Leak: Always remember to free the memory allocated by calloc to avoid memory leaks.
calloc(0, size) behavior: If the first argument (num) is zero, calloc(0, size) is allowed to return a NULL pointer 
or a valid pointer to zero bytes, depending on the system. Always check the return value for NULL before using it.

Conclusion:
calloc is a useful function when you need to allocate zero-initialized memory, especially for large data structures or 
arrays. It combines the functionality of malloc with the added benefit of memory initialization, which can help 
prevent bugs related to uninitialized memory. However, you should be mindful of its potential performance overhead 
compared to malloc, especially when zero-initialization isn't required.

*/

//Example 1: Allocating Memory for an Array of Integers

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    size_t num_elements = 5;

    // Allocating memory for an array of 5 integers and initializing to zero
    arr = (int *)calloc(num_elements, sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Displaying values of the array
    for (size_t i = 0; i < num_elements; i++) {
        printf("arr[%zu] = %d\n", i, arr[i]);  // Output will be zeroes
    }

    // Freeing the allocated memory
    free(arr);

    return 0;
}
