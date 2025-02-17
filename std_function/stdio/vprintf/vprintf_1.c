/*
The vprintf function in C is a variant of the printf function that provides a way to handle formatted output using a 
va_list instead of a variable number of arguments. It is often used when working with functions that accept a variable 
number of arguments and need to delegate the printing to a standard output.

Overview of vprintf:
Function signature:
int vprintf(const char *format, va_list arg);

Parameters:

format: A C string that contains the text to be written to the standard output, with placeholders for variables that 
should be formatted. The format string uses special format specifiers (like %d, %s, %f, etc.) to determine how the 
variables should be represented.
arg: A va_list that represents a list of arguments. It is typically obtained by calling va_start in the context of a 
variadic function.

Return value:

The function returns the number of characters written (excluding the terminating null byte) on success. 
If an error occurs, it returns a negative value.

Usage of vprintf:
vprintf is usually used in situations where the exact number or types of arguments are not known ahead of time. 
It is often seen in functions that work with a variable number of arguments, as printf does.

The vprintf function is generally used in conjunction with va_start, va_arg, and va_end in variadic functions. 
These macros are part of the standard library for handling variable argument lists.
*/
/*
Example of vprintf:
Below is a simple example of how vprintf can be used within a function that accepts a variable number of arguments:
*/
#include <stdio.h>
#include <stdarg.h>

void my_printf(const char *format, ...) {
    va_list args;
    
    // Initialize the va_list with the variable arguments
    va_start(args, format);
    
    // Call vprintf to print the formatted output
    vprintf(format, args);
    
    // Clean up the va_list when done
    va_end(args);
}

int main() {
    // Example of calling the custom my_printf function
    my_printf("This is an integer: %d, and this is a string: %s\n", 42, "Hello, World!");
    return 0;
}

/*
Explanation:
Function Declaration:

my_printf is defined as a variadic function that accepts a format string and a variable number of arguments.

Initializing va_list:
va_list args: This defines a variable of type va_list to hold the list of arguments.
va_start(args, format): This macro initializes the va_list (args) to point to the variable arguments, 
starting after the format argument.

Calling vprintf:
The function vprintf(format, args) is called, where format is the format string and args is the va_list containing 
the variable arguments.
vprintf handles the formatting and prints the output to the standard output (stdout).

Cleaning Up:
va_end(args): This macro is called to clean up the va_list after it has been used. This is required to prevent memory 
leaks.

Function Call:
In the main function, my_printf is called with a format string and two arguments: an integer (42) and a 
string ("Hello, World!").

Explanation of Output:
For the example above, the output would be:
This is an integer: 42, and this is a string: Hello, World!

Format Specifiers:
Just like printf, vprintf supports a wide variety of format specifiers to control how the arguments are printed. 
Some common specifiers include:

%d – Prints an integer.
%f – Prints a floating-point number.
%s – Prints a string.
%c – Prints a single character.
%x – Prints an integer in hexadecimal format.
%p – Prints a pointer.
Important Notes:
Memory Safety: vprintf relies on the va_list being correctly initialized with va_start and cleaned up with va_end. 
Failure to do so can cause undefined behavior.

Error Handling: The return value of vprintf is the number of characters printed. If there’s an error 
(e.g., writing to stdout fails), it will return a negative value.

Usage in Variadic Functions: The primary use case for vprintf is in functions that take a variable number of 
arguments and need to pass those arguments to vprintf for formatted printing. vprintf is generally called after 
collecting the arguments with va_start.
*/

