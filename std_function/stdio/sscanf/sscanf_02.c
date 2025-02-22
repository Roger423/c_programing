/*
Example of parsing different types:
*/

#include <stdio.h>

int main() {
    const char *input = "Alice 25 3.14";

    char name[20];
    int age;
    float pi;

    // Parse the string using sscanf
    int result = sscanf(input, "%s %d %f", name, &age, &pi);

    if (result == 3) {
        printf("Name: %s\n", name);
        printf("Age: %d\n", age);
        printf("Pi: %.2f\n", pi);
    } else {
        printf("Failed to parse the input.\n");
    }

    return 0;
}

/*
Explanation:

Input String:
"Alice 25 3.14" is a string containing a name, an age, and a floating-point number.

Format String:
"%s %d %f": The format string expects a string (%s), an integer (%d), and a floating-point number (%f).

Output:
The variables name, age, and pi will store the parsed values.
sscanf returns 3 because all three values were successfully parsed.
*/