/*
Introduction: A Variable Length Array (VLA) is an array in C where the size of the array is determined at 
runtime (i.e., during program execution), rather than at compile time. This feature was introduced in the C99 
standard of the C programming language. Unlike regular arrays, whose size must be known at compile time, 
VLAs allow you to specify the array's size dynamically using variables.

In C99 and later, VLAs can be declared within functions, and their size can be calculated based on input values, 
function parameters, or other runtime data.

Key Concepts:
1. Dynamic Array Size: VLAs allow the size of the array to be specified by a variable, which can be set during runtime.

2. Scope of VLAs: VLAs are local to the function in which they are defined, and they behave similarly to regular 
   local arrays in terms of scope and lifetime. However, the difference is that their size is not fixed at compile time.

3. Memory Management: The memory for a VLA is automatically allocated on the stack. When the function returns, 
   the VLA memory is automatically freed.

4. Limitations: VLAs are not supported in C90 or earlier versions of C (prior to C99). Some compilers also may 
   not support VLAs or may disable them by default for compatibility reasons. In addition, excessive use of VLAs 
   can cause a stack overflow because stack space is limited.


Basic Syntax:
To declare a VLA, you can use the following syntax:

type array_name[size];
Where size is a variable (or an expression) whose value is known at runtime.
*/

/*
Key Points to Remember:

1. Scope:
VLAs are allocated on the stack, and their size is determined during runtime.
They cannot be returned from functions directly (unlike dynamically allocated arrays using malloc).

2. Memory Limitations:
VLAs are stored on the stack, so excessive use of large arrays might cause stack overflow. If the array size is 
too large, consider using malloc for dynamic memory allocation.

3. C99 and Beyond:
VLAs are part of C99 and later standards. In older standards (e.g., C89), they are not supported. 
If your compiler doesn't support VLAs, you can consider using malloc and free for dynamic memory management.

4. Compiler Support:
Not all compilers support VLAs. Some compilers may allow them as an option or might disable them by default 
for compatibility. Always check the documentation of the compiler you're using.

5. Alternative (Dynamic Memory Allocation):
If your application needs flexible memory management or works with very large arrays, using malloc and free for 
dynamic memory allocation is a better alternative.

Conclusion:
1. VLAs in C provide a way to define arrays whose sizes are determined at runtime. They are convenient when the 
size of an array is not known at compile time. However, VLAs should be used carefully, particularly with large arrays, 
as they are allocated on the stack, and stack memory is limited. For larger data or more flexible memory management, 
dynamic memory allocation using malloc is recommended.

2. By using the examples and explanations above, you can take advantage of VLAs when needed, and you should understand 
when to choose VLAs versus dynamically allocated arrays based on your program's needs and constraints.
*/

//Example 1: Simple Usage
#include <stdio.h>

int main() {
    int n;

    // Get the array size from the user
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    // Declare a VLA with size 'n'
    int arr[n];

    // Initialize the array
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }

    // Print the array elements
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

/*
Explanation:
The size of the array arr is determined by the value of the variable n, which is read from user input.
The array elements are then initialized, and the result is printed.

*/
