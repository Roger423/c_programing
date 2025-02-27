//This C program generates all permutations of a set of integers from 1 to n of length r and prints them to the console.

#include <stdio.h>

#define N_MAX (100)

int used_flag[N_MAX + 1];
int result[N_MAX];
int n, r;

void print_result(void)
{
    int i;

    for (i = 0; i < r; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

void permutaion(int nth)
{
    int i;

    if (nth == r) {
        print_result();
        return;
    }

    for (i = 1; i <= n; i++) {
        if (used_flag[i] == 0) {
            result[nth] = i;
            used_flag[i] = 1;
            permutaion(nth + 1);
            used_flag[i] = 0;
        }
    }
}

int main(int argc, char **argv)
{
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &r);

    permutaion(0);

    return 0;
}

/*
Code Explanation:

N_MAX: The maximum value of n is defined as 100. This means the program will handle permutations where n 
(the number of elements to choose from) can go up to 100.

used_flag: This array is used to track whether a particular number (from 1 to n) is already used 
in the current permutation.

result: This array stores the current permutation being generated.

n: The number of elements to choose from (inclusive).

r: The length of the permutation (how many elements in each permutation).


print_result() Function

Purpose: This function prints the current permutation stored in the result array.
It loops through the first r elements of the result array and prints them. After printing all r elements, 
it prints a newline (\n).


permutaion(int nth) Function

Purpose: This function recursively generates all permutations of length r from the set {1, 2, ..., n}.

Base Case: When nth == r, meaning that we have filled the permutation with r elements, 
it calls the print_result() function to print the current permutation.

Recursive Case:
For each number i from 1 to n, if i has not been used (checked using used_flag[i] == 0), the program:
  Sets result[nth] = i (this places i at the current position nth in the permutation).
  Marks i as used by setting used_flag[i] = 1.
  Recursively calls permutaion(nth + 1) to generate the next position in the permutation.
  After the recursive call, it "unmarks" i as used by resetting used_flag[i] = 0, 
  allowing it to be used again in a different position.


main() Function:

Purpose: The main() function is the entry point of the program.
    argc and argv are used to handle command-line arguments:
        argv[1]: The first argument is expected to be n, the size of the set {1, 2, ..., n}.
        argv[2]: The second argument is expected to be r, the length of the permutations.
    The sscanf() functions are used to read the integer values of n and r from the command-line arguments.
    After reading the values, it calls the permutaion(0) function to start the permutation generation process 
    from the first position (nth = 0).



How the Program Works
Command Line Input: The program expects two arguments from the command line:

n: The number of elements in the set {1, 2, ..., n}.
r: The length of the permutation to generate.

For example, if the input is 3 and 2, the program will generate all 2-element permutations of the set {1, 2, 3}.

Generating Permutations: The permutaion() function uses recursion to build permutations. For every position in 
the permutation (from nth = 0 to nth = r - 1), the program selects an unused element, places it in the current 
position, and then recursively calls the function to fill the next position.

Printing Results: Once a complete permutation of length r is generated (i.e., when nth == r), the print_result() 
function is called to print that permutation.
*/
