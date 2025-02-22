/*
Handling Invalid Input:
If the input doesn't match the expected format, sscanf returns a value less than the number of expected items. 
For example, if the input doesn't contain a valid integer, it won't assign a value to the int variable.

Example:
*/
#include <stdio.h>

int main() {
    const char *input = "Alice not_a_number 3.14";

    char name[20];
    int age;
    float pi;

    int result = sscanf(input, "%s %d %f", name, &age, &pi);

    if (result == 3) {
        printf("Name: %s\n", name);
        printf("Age: %d\n", age);
        printf("Pi: %.2f\n", pi);
    } else {
        printf("Failed to parse the input. Only %d values were read.\n", result);
    }

    return 0;
}

/*
Output:
Failed to parse the input. Only 2 values were read.

Explanation:
The input "Alice not_a_number 3.14" doesn't contain a valid integer after "Alice", 
so sscanf returns 2 (only the string and the float are successfully parsed).
The return value of sscanf can be checked to handle parsing errors appropriately.
*/