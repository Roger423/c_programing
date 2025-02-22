//Example 4: Reading Mixed Characters Using a Set

#include <stdio.h>

int main() {
    const char *input = "Hello,123";
    char output[10];

    int result = sscanf(input, "%[a-zA-Z,]", output);
    
    if (result == 1) {
        printf("Extracted characters: %s\n", output);
    } else {
        printf("Failed to extract characters.\n");
    }

    return 0;
}

/*
Explanation:
Input: "Hello,123"
Format string: "%[a-zA-Z,]" tells sscanf to read alphabetic characters (a-z, A-Z) and commas (,).
Output: The string "Hello," will be extracted and stored in the output array.
The function will stop reading when it encounters the numeric part "123" because digits are not in the set.

Output:
Extracted characters: Hello,

*/