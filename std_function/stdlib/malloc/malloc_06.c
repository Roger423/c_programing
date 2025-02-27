//malloc(0)

#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0);  // Attempt to allocate 0 bytes

    if (ptr == NULL) {
        printf("malloc returned NULL\n");
    } else {
        printf("malloc returned a non-NULL pointer: %p\n", ptr);
    }

    free(ptr);  // Freeing the pointer
    return 0;
}

/*
1. Return Value
Most implementations of malloc() (including glibc) return a NULL pointer when the size is 0. This is because 
malloc(0) is considered an invalid request for memory allocation, as it doesn’t make sense to allocate "zero" bytes.

In some systems, however, malloc(0) might return a non-NULL pointer. This is generally a valid but 
implementation-dependent behavior, and such pointers are typically considered to be "unique" but not usable 
for accessing memory. If a non-NULL pointer is returned, dereferencing it leads to undefined behavior.

2. Standard Explanation
The C standard (ISO/IEC 9899) states that:

If the size is 0, malloc() may either return a NULL pointer or a unique pointer. In both cases, the pointer should 
not be dereferenced.

The important part is that calling free() on a pointer returned by malloc(0) is safe. The free() function will handle 
it without any issues, regardless of whether the pointer is NULL or non-NULL.

3. Behavior of free() with Zero-Byte Allocations
It is safe to call free() on a pointer that was returned by malloc(0). If the pointer is NULL (either explicitly 
or implicitly), free() does nothing. If the pointer is non-NULL (but the size allocated is zero), free() will still 
properly release the memory, even though the allocation is zero bytes.

Key Takeaways:
1. malloc(0) may return either a NULL pointer or a non-NULL pointer, depending on the system's implementation of 
   malloc(). On Linux systems with glibc, it's more common to return a non-NULL pointer for malloc(0).
2. Dereferencing a pointer returned by malloc(0) is undefined behavior, and you should avoid using the pointer for 
   any memory access.
3. free() on a malloc(0) pointer is safe.
*/