//Example 5: Multiple Items with %[set]

#include <stdio.h>

int main() {
    const char *input = "Hello World 123";
    char word1[20], word2[20];

    int result = sscanf(input, "%[a-zA-Z] %[0-9]", word1, word2);

    if (result == 2) {
        printf("Word 1: %s\n", word1);
        printf("Word 2: %s\n", word2);
    } else {
        printf("Failed to extract both words.\n");
    }

    return 0;
}

/*
Explanation:
Input: "Hello World 123"
Format string: "%[a-zA-Z] %[0-9]" tells sscanf to first read alphabetic characters and store them in word1, 
               and then read digits to store them in word2.
Output:
The string "Hello" is extracted into word1.
The string "123" is extracted into word2.
The function stops reading when it encounters the space between "World" and "123".

Output:
Word 1: Hello
Word 2: 123

*/

/*
Summary of %[set]:
1. The %[set] specifier reads characters from the input string that match any character in the set. 
   It continues reading until it encounters a character that is not in the set.
2. The set can include individual characters, character ranges, and can use negation (^) to match characters 
   not in the set.
3. If no matching characters are found, sscanf returns 0, and if the format doesn't match, it will return a 
   negative number.
4. %[set] is useful for extracting strings, numbers, and other sequences of characters when you have a defined set 
   of characters to read.
*/