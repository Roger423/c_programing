/*
The %[set] format specifier in sscanf is used to read a sequence of characters from the input string that match a 
specific set of characters. This allows you to capture a substring of characters from the input that belong to a 
defined set.

Syntax of %[set]:
%[set]

set: A string containing a set of characters. This set defines the characters that sscanf should read. 
The set can include:
1. Individual characters: abcd1234, etc.
2. Character ranges: a-z, A-Z, 0-9, etc.
3. Negation: If the set starts with a ^, it means that sscanf will read characters not in the set.
4. Special characters: You can also include special characters in the set, such as spaces or punctuation marks.

How %[set] works:
1. %[set] tells sscanf to read characters from the input string that match any character in the set, 
stopping when it encounters a character that is not in the set. It stores the matching characters into the 
corresponding variable (which must be a character array).

2. If the set is specified with a negation (e.g., ^a-z), then %[set] will read characters that are not in the set.

*/

//Example 1: Reading a Word Using %[a-zA-Z]
#include <stdio.h>

int main() {
    const char *input = "Hello World";
    char word[10];

    int result = sscanf(input, "%[a-zA-Z]", word);
    
    if (result == 1) {
        printf("Extracted word: %s\n", word);
    } else {
        printf("Failed to extract word.\n");
    }

    return 0;
}

/*
Explanation:
Input: "Hello World"
Format string: "%[a-zA-Z]" tells sscanf to read only alphabetic characters (a-z, A-Z).
Output: The word "Hello" will be extracted and stored in the word array.
The function will stop reading when it encounters the space between "Hello" and "World".

Output:
Extracted word: Hello

*/
