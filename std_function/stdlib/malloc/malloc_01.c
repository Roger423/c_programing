/*
What is malloc?
malloc stands for "memory allocation." It’s a standard library function in C, declared in <stdlib.h>, 
that allocates a block of memory on the heap at runtime. Unlike stack-allocated variables (automatic storage), 
memory allocated with malloc persists until explicitly freed using free, giving you control over its lifetime.

Function Prototype:

void *malloc(size_t size);

Parameter: 
size_t size — The number of bytes to allocate. size_t is an unsigned integer type defined in <stddef.h> 
              (and included via <stdlib.h>), ensuring it can represent the size of any object in memory.

Return Value: 
On success: A void* pointer to the beginning of the allocated memory block.
On failure (e.g., insufficient memory): NULL.

Key Characteristics
1. Uninitialized Memory: The memory allocated by malloc is not initialized. It contains whatever garbage values 
   were previously in that memory location.
2. Dynamic Sizing: The size is determined at runtime, unlike static arrays (e.g., int arr[10]).
3. Heap Allocation: Memory comes from the heap, not the stack, so it’s available beyond the scope of the function 
   where it’s allocated.

Usage Guide:
Here’s a step-by-step breakdown of how to use malloc, with examples and best practices.
1. Include the Header
Always include <stdlib.h> to use malloc.

#include <stdlib.h>

2. Basic Syntax
To allocate memory for a single variable or an array, pass the number of bytes you need. Typically, 
you use sizeof to calculate this based on the data type.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int)); // Allocate memory for 1 int
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    *ptr = 42; // Use the allocated memory
    printf("Value: %d\n", *ptr);

    free(ptr); // Free the memory when done
    return 0;
}

/*
Casting: The (int *) cast converts the void* return type to the desired pointer type. In C (unlike C++), 
this cast is optional but often used for clarity.
Error Check: Always check if ptr is NULL to handle allocation failure.
*/