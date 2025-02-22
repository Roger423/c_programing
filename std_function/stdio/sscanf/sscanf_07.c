//Example 2: Reading a String of Digits Using %[0-9]

#include <stdio.h>

int main() {
    const char *input = "12345 abc";
    char digits[10];

    int result = sscanf(input, "%[0-9]", digits);
    
    if (result == 1) {
        printf("Extracted digits: %s\n", digits);
    } else {
        printf("Failed to extract digits.\n");
    }

    return 0;
}
/*
Explanation:
Input: "12345 abc"
Format string: "%[0-9]" tells sscanf to read only numeric digits (0-9).
Output: The string "12345" will be extracted and stored in the digits array.
The function stops when it encounters the space between the digits and the alphabetic characters.

Output:
Extracted digits: 12345

*/