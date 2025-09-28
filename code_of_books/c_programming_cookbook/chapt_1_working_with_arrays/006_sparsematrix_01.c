#include <stdio.h>

#define MAX 100

int main() 
{
    int r, c;
    int m[MAX][MAX];

    printf("Enter the number of rows and columns of the matrix:");
    scanf("%d %d", &r, &c);

    int ctr = 0;
    printf("Enter the elements of the matix:\n");
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            scanf(" %d", &m[i][j]);
            if (m[i][j] == 0) ++ctr;
        }
    
    printf("There are %d number of zeros in the matirx\n", ctr);
    if (ctr > r * c /2) {
        printf("The given matix is a sparse matix\n");
    } else {
        printf("The given matrix is not a sparse matix\n");
    }

    return 0;
}