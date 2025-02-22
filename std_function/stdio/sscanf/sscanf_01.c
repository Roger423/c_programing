/*
The sscanf function in C is used to read formatted input from a string. It is part of the C standard library (stdio.h) 
and works similarly to scanf, but instead of reading input from standard input (usually the keyboard), sscanf reads 
from a provided string.

Overview of sscanf:
Function signature:

int sscanf(const char *str, const char *format, ...);

Parameters:
str: A pointer to the string from which the input will be read.
format: A C string that specifies how to interpret the input. It contains format specifiers (like %d, %s, %f, etc.) 
that specify the types of data expected in the input string.
...: A variable number of arguments. Each argument corresponds to a format specifier in the format string, 
and these arguments must be pointers to variables where the extracted values will be stored.

Return value:
The function returns the number of items successfully read (i.e., the number of successfully assigned values).
If the function encounters an error (e.g., invalid input), it returns a negative value.
If no items are assigned (i.e., the format doesn't match), the return value is 0.

Usage of sscanf:
The sscanf function can be used to parse strings based on specific formats. Each format specifier in the format string 
corresponds to a variable that will receive the extracted value.

Example of sscanf:
Let's consider an example where we parse a string representing an integer and a floating-point number:
*/
#include <stdio.h>

int main() {
    const char *input = "123 45.67";
    int i;
    float f;

    // Parse the string using sscanf
    int result = sscanf(input, "%d %f", &i, &f);

    // Check if both values were successfully read
    if (result == 2) {
        printf("Integer: %d\n", i);
        printf("Float: %.2f\n", f);
    } else {
        printf("Failed to parse the input.\n");
    }

    return 0;
}

/*
Explanation:
Input String:
The input string is "123 45.67", which consists of an integer and a floating-point number, separated by a space.

Format String:
The format string "%d %f" tells sscanf how to interpret the input. The %d specifier expects an integer, 
and the %f specifier expects a floating-point number.

Output:
The variables i and f will store the values parsed from the string.
sscanf returns 2 because two values were successfully parsed (an integer and a float).

Format Specifiers for sscanf:
The format string used with sscanf follows the same conventions as the one used with printf and scanf. 
Here are some common format specifiers:

%d: Reads an integer (decimal).
%f: Reads a floating-point number.
%lf: Reads a double.
%s: Reads a string (stops at the first whitespace).
%c: Reads a single character.
%x: Reads a hexadecimal number.
%o: Reads an octal number.
%u: Reads an unsigned integer.
%p: Reads a pointer value (useful for debugging).
%[set]: Reads a sequence of characters from the input that match the specified set.
*/
