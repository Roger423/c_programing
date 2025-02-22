//Example 3: Using Negation in %[set]

#include <stdio.h>

int main() {
    const char *input = "12345abc";
    char non_digits[10];

    int result = sscanf(input, "%[^0-9]", non_digits);
    
    if (result == 1) {
        printf("Extracted non-digits: %s\n", non_digits);
    } else {
        printf("Failed to extract non-digits.\n");
    }

    return 0;
}

/*
Explanation:
Input: "12345abc"
Format string: "%[^0-9]" tells sscanf to read characters that are not digits (^ negates the set 0-9).
Output: The function will read characters until it encounters a digit. Since the string starts with "12345", 
which is numeric, the output will be empty.

Output:
Extracted non-digits: abc

*/