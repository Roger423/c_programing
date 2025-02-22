/*
Using Width and Precision with sscanf:
You can also specify a maximum width for a string input and precision for floating-point numbers.

Example:
*/
#include <stdio.h>

int main() {
    const char *input = "Hello123 45.67";

    char str[6];  // To hold up to 5 characters + null terminator
    float f;

    int result = sscanf(input, "%5s %f", str, &f);

    if (result == 2) {
        printf("String: %s\n", str);
        printf("Float: %.2f\n", f);
    } else {
        printf("Failed to parse the input.\n");
    }

    return 0;
}

/*
Explanation:
The format "%5s" limits the string input to 5 characters (plus the null terminator). 
This prevents buffer overflow if the string in the input exceeds 5 characters.
The %f specifier reads a floating-point number as usual.

Conclusion:
1. sscanf is a powerful function used for extracting formatted data from a string.
2. It allows you to specify how the input string should be parsed, and you can store the parsed values in variables.
3. Use it with caution when working with untrusted input, and ensure that your buffers are large enough to hold the 
   expected data.
4. Always check the return value of sscanf to ensure that the input matches the expected format.
*/

